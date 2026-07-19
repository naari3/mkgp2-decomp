#!/usr/bin/env python3
"""On-demand CW 1.3.2 internal-state dumps for a production TU.

Wraps the Phase 2f instrumentation (docs/notes/cw132-allocator-phase2f-research.md)
into a single side-band tool: given a TU source path, re-runs the compiler with
the TU's EXACT production flags (extracted from build.ninja via `ninja -t
commands`) against instrumented PRIVATE copies of mwcceppc, and collects:

  --ir       IR-optimizer per-pass dump (53 passes, named webs / flowgraph).
             1-byte gate patch, see tools/compiler_probe/enable_ir_dump.py.
             Output: tmp/dump/<base>.ir.log
  --colorer  register-colorer visit order + home registers (web key / degree /
             assigned reg), via frida hook on the Coloring.c select step.
             COLOR steps are labeled `=== FUNCTION x ===` (fn names captured
             from the IR-dump progress markers). Requires `pip install frida`.
             Output: tmp/dump/<base>.colorer.log
  --regdiff  no-frida register-web permutation report: aligns our compile
             against the TARGET object (build/<ver>/obj/...) instruction by
             instruction and prints `ours rX -> target rY` per web with the
             first defining instruction (which usually identifies the source
             variable, e.g. `lwz r24, 0x18(r30)` = the itemSelection load).
             Distinguishes pure-coloring residues from structural diffs.

--ir + --colorer by default. The build graph is never touched: the shipped compiler stays
untouched (SHA-verified), instrumented copies live in tmp_probe/ (gitignored),
logs land in tmp/dump/. With --ir the tool also compiles the TU once with the
SHIPPED compiler and asserts the instrumented .o is byte-identical (proof the
instrumentation did not perturb codegen).

Usage:
  python tools/mwcc_dump.py src/game/clFlowItem.c
  python tools/mwcc_dump.py src/game/clFlowItem.c --colorer
  python tools/mwcc_dump.py src/game/clFlowItem.c --ir --keep-obj

Typical use: a matching task hits a register-identity residue -> run with
--colorer, grep the fn's webs for key/home vs target, and check the
phase2f closed-class table before burning builds.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import shlex
import shutil
import subprocess
import sys
import time
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
SHIPPED = REPO / "build" / "compilers" / "GC" / "1.3.2" / "mwcceppc.exe"
LMGR = SHIPPED.parent / "lmgr326b.dll"
SHIPPED_SHA1 = "d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5"
SCRATCH = REPO / "tmp_probe"
DUMPDIR = REPO / "tmp" / "dump"
PROBE_DIR = REPO / "tools" / "compiler_probe"
COLORER_JS = PROBE_DIR / "frida_colorer_probe.js"

sys.path.insert(0, str(PROBE_DIR))
from enable_ir_dump import patch as irdump_patch  # noqa: E402


def sha1(p: Path) -> str:
    return hashlib.sha1(p.read_bytes()).hexdigest()


def extract_flags(src_rel: str, version: str) -> list[str]:
    """Pull the TU's production mwcc flags out of build.ninja."""
    obj = f"build/{version}/src/{src_rel.removeprefix('src/').removesuffix('.c')}.o"
    out = subprocess.run(
        ["ninja", "-t", "commands", obj.replace("/", os.sep)],
        capture_output=True, text=True, cwd=REPO, check=True,
    ).stdout
    line = next(
        (l for l in out.splitlines()
         if "mwcceppc.exe" in l and src_rel.replace("/", "\\") in l),
        None,
    )
    if line is None:
        sys.exit(f"no mwcc command for {obj} in build.ninja (run configure.py?)")
    cmd = line.split(" && ")[0]
    flag_str = cmd.split("mwcceppc.exe", 1)[1].split(" -c ", 1)[0].strip()
    toks = shlex.split(flag_str, posix=False)
    return [t[1:-1] if t.startswith('"') and t.endswith('"') else t for t in toks]


def prep_scratch() -> tuple[Path, Path, Path]:
    """Create private plain + IR-dump-patched compiler copies in tmp_probe/.

    Returns (priv, irdump_verbose, irdump_quiet). The quiet variant (patch A
    only) keeps the fn-name progress markers on without the 4MB IR body; the
    colorer run uses it so COLOR steps get `=== FUNCTION x ===` labels."""
    assert sha1(SHIPPED) == SHIPPED_SHA1, "shipped mwcceppc.exe SHA-1 mismatch!"
    SCRATCH.mkdir(exist_ok=True)
    priv = SCRATCH / "mwcceppc_priv.exe"
    irdump = SCRATCH / "mwcceppc_irdump.exe"
    irdumpq = SCRATCH / "mwcceppc_irdumpq.exe"
    if not priv.exists() or sha1(priv) != SHIPPED_SHA1:
        shutil.copy2(SHIPPED, priv)
    if not irdump.exists():
        irdump_patch(str(priv), str(irdump), verbose=True)
    if not irdumpq.exists():
        irdump_patch(str(priv), str(irdumpq), verbose=False)
    dll = SCRATCH / "lmgr326b.dll"
    if not dll.exists():
        shutil.copy2(LMGR, dll)
    return priv, irdump, irdumpq


def elf_sections(data: bytes) -> dict[str, bytes]:
    import struct
    shoff = struct.unpack_from(">I", data, 0x20)[0]
    shentsize = struct.unpack_from(">H", data, 0x2E)[0]
    shnum = struct.unpack_from(">H", data, 0x30)[0]
    shstrndx = struct.unpack_from(">H", data, 0x32)[0]
    shstr_off = struct.unpack_from(">I", data, shoff + shstrndx * shentsize + 0x10)[0]
    out = {}
    for i in range(shnum):
        h = shoff + i * shentsize
        name_off = struct.unpack_from(">I", data, h)[0]
        name = data[shstr_off + name_off:data.index(b"\0", shstr_off + name_off)].decode()
        typ = struct.unpack_from(">I", data, h + 4)[0]
        off = struct.unpack_from(">I", data, h + 0x10)[0]
        size = struct.unpack_from(">I", data, h + 0x14)[0]
        if typ == 1:  # PROGBITS
            out[f"{i}:{name}"] = data[off:off + size]
    return out


def same_codegen(a: Path, b: Path) -> bool:
    """Byte-compare all PROGBITS sections except extab (CW writes
    nondeterministic uninitialized junk into extab pad bytes run-to-run --
    the same C702-class bytes dtk extab clean exists to normalize)."""
    sa, sb = elf_sections(a.read_bytes()), elf_sections(b.read_bytes())
    if sa.keys() != sb.keys():
        return False
    return all(
        sa[k] == sb[k] for k in sa
        if not k.split(":")[1].startswith("extab")
    )


def compile_with(exe: Path, flags: list[str], src: Path, outdir: Path) -> Path:
    outdir.mkdir(parents=True, exist_ok=True)
    obj = outdir / (src.stem + ".o")
    if obj.exists():
        obj.unlink()
    r = subprocess.run(
        [str(exe), *flags, "-c", str(src), "-o", str(outdir)],
        capture_output=True, text=True, cwd=REPO,
    )
    if r.returncode != 0 or not obj.exists():
        sys.exit(f"compile failed ({exe.name}):\n{r.stdout}\n{r.stderr}")
    return obj


def run_ir(irdump_exe: Path, shipped_flags: list[str], src: Path) -> Path:
    # The dump FILE* opens "<source-path-minus-ext>.log" -> lands next to src.
    side_log = src.with_suffix(".log")
    if side_log.exists():
        side_log.unlink()
    obj_i = compile_with(irdump_exe, shipped_flags, src, SCRATCH / "ir")
    # verify instrumentation did not perturb codegen (extab junk bytes are
    # nondeterministic run-to-run even with the shipped compiler, so they
    # are excluded from the comparison)
    obj_s = compile_with(SHIPPED, shipped_flags, src, SCRATCH / "ref")
    identical = same_codegen(obj_i, obj_s)
    dst = DUMPDIR / (src.stem + ".ir.log")
    if side_log.exists():
        DUMPDIR.mkdir(parents=True, exist_ok=True)
        shutil.move(str(side_log), dst)
    else:
        sys.exit("IR dump log did not appear next to the source")
    print(f"[ir] {dst}  ({dst.stat().st_size} bytes)")
    print(f"[ir] instrumented .o byte-identical to shipped: {identical}")
    if not identical:
        print("[ir] WARNING: do not trust this dump for codegen conclusions")
    return dst


def dtk_disasm(obj: Path, out: Path) -> None:
    dtk = REPO / "build" / "tools" / "dtk.exe"
    r = subprocess.run([str(dtk), "elf", "disasm", str(obj), str(out)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"dtk disasm failed for {obj}:\n{r.stderr}")


def parse_disasm_fns(path: Path) -> dict[str, list[str]]:
    """fn name -> list of instruction texts (labels normalized away)."""
    import re
    fns: dict[str, list[str]] = {}
    cur = None
    for line in path.read_text(encoding="utf-8").splitlines():
        s = line.strip()
        if s.startswith(".fn "):
            cur = s.split()[1].rstrip(",")
            fns[cur] = []
        elif s.startswith(".endfn"):
            cur = None
        elif cur is not None:
            m = re.match(r"/\*.*?\*/\s+(.*)", line)
            if m:
                ins = re.sub(r"\.L_[0-9A-Fa-f]+", "LBL", m.group(1).strip())
                fns[cur].append(ins)
    return fns


REG_RE = None


def run_regdiff(flags: list[str], src: Path, src_rel: str, version: str) -> None:
    """Instruction-align our compile against the target object and report the
    register-web permutation with defining-instruction annotations.

    This automates the manual '1:1 dump with <<< markers' comparison: for every
    position where only register NUMBERS differ, collect the ours->target
    correspondence, then summarize per register pair with the first defining
    instruction (which usually identifies the source variable, e.g.
    `lwz r24, 0x18(r30)` = the itemSelection load)."""
    import re
    obj_t = REPO / "build" / version / "obj" / Path(src_rel.removeprefix("src/")).with_suffix(".o")
    if not obj_t.is_file():
        sys.exit(f"target obj not found: {obj_t} (build the project once)")
    obj_o = compile_with(SHIPPED, flags, src, SCRATCH / "regdiff")
    da, db = SCRATCH / "regdiff_tgt.s", SCRATCH / "regdiff_ours.s"
    dtk_disasm(obj_t, da)
    dtk_disasm(obj_o, db)
    tgt_fns, our_fns = parse_disasm_fns(da), parse_disasm_fns(db)
    reg_re = re.compile(r"\b([rf]\d+)\b")

    # Our object is pre-postprocess: apply the extab_user_renames flat map
    # (mangled C++ -> existing C names) textually so fn/callee names line up
    # with the target side.
    import json as _json
    renames_path = REPO / "tools" / "extab_user_renames.json"
    flat: dict[str, str] = {}
    if renames_path.is_file():
        for tu, mapping in _json.loads(renames_path.read_text(encoding="utf-8")).items():
            if isinstance(mapping, dict):
                flat.update(mapping)
    def apply_renames(s: str) -> str:
        for k, v in flat.items():
            if k in s:
                s = s.replace(k, v)
        return s
    our_fns = {apply_renames(k): [apply_renames(x) for x in v]
               for k, v in our_fns.items()}
    # Anonymous sdata2 literals ("@N") are renamed by postprocess_sdata2 at
    # build time; for shape comparison treat any @sda21 symbol as equal.
    sda_re = re.compile(r'(?:"[^"]+"|[\w$.]+)@sda21')
    def shape(x: str) -> str:
        return sda_re.sub("SDAREF", reg_re.sub("R", x))

    for fn in tgt_fns:
        if fn not in our_fns:
            print(f"[regdiff] {fn}: MISSING in our object")
            continue
        t, o = tgt_fns[fn], our_fns[fn]
        if [shape(x) for x in t] != [shape(x) for x in o]:
            nt, no = len(t), len(o)
            fi = next((i for i in range(min(nt, no))
                       if shape(t[i]) != shape(o[i])), min(nt, no))
            print(f"[regdiff] {fn}: instruction streams differ STRUCTURALLY "
                  f"(target {nt} vs ours {no} insns, first at #{fi}):")
            print(f"    target: {t[fi] if fi < nt else '<end>'}")
            print(f"    ours:   {o[fi] if fi < no else '<end>'}")
            print("    -> not a pure coloring residue; fix the shape first")
            continue
        # same shape: collect per-position register correspondences
        pairs: dict[tuple[str, str], dict] = {}
        ndiff = 0
        for i, (ti, oi) in enumerate(zip(t, o)):
            tr, orr = reg_re.findall(ti), reg_re.findall(oi)
            if tr == orr:
                continue
            ndiff += 1
            for a, b in zip(orr, tr):
                if a == b:
                    continue
                e = pairs.setdefault((a, b), {"n": 0, "first": i, "ins": ti, "ours": oi})
                e["n"] += 1
        if not pairs:
            print(f"[regdiff] {fn}: IDENTICAL (100%)")
            continue
        print(f"[regdiff] {fn}: shape identical, {ndiff} insns with register-only "
              f"diffs, {len(pairs)} reg correspondences:")
        for (a, b), e in sorted(pairs.items(), key=lambda kv: kv[1]["first"]):
            print(f"    ours {a:>4} -> target {b:>4}  x{e['n']:<3} first@#{e['first']}"
                  f"  tgt: {e['ins']}")
        print("    -> pure coloring residue; check the phase2f closed-class table"
              " before probing (SKILL CW132 section)")


def run_colorer(priv_exe: Path, flags: list[str], src: Path) -> Path:
    try:
        import frida
    except ImportError:
        sys.exit("--colorer needs `pip install frida`")
    DUMPDIR.mkdir(parents=True, exist_ok=True)
    dst = DUMPDIR / (src.stem + ".colorer.log")
    outdir = SCRATCH / "colorer"
    outdir.mkdir(exist_ok=True)
    obj = outdir / (src.stem + ".o")
    if obj.exists():
        obj.unlink()

    # The compiler is the quiet IR-patched copy, so the "Starting function"
    # markers fire and the probe labels COLOR steps with fn names. A side
    # <base>.log lands next to the source; remove it afterwards.
    side_log = src.with_suffix(".log")
    argv = [str(priv_exe), *flags, "-c", str(src), "-o", str(outdir)]
    lines: list[str] = []

    device = frida.get_local_device()
    pid = device.spawn(argv, cwd=str(REPO))
    session = device.attach(pid)
    script = session.create_script(COLORER_JS.read_text(encoding="utf-8"), runtime="v8")

    def on_message(message, data):
        if message["type"] == "send":
            lines.append(str(message["payload"]))
        elif message["type"] == "error":
            lines.append("[frida-error] " + message.get("stack", str(message)))

    script.on("message", on_message)
    script.set_log_handler(lambda level, text: lines.append(text))
    script.load()
    device.resume(pid)

    deadline = time.time() + 120
    while time.time() < deadline:
        time.sleep(0.2)
        if obj.exists():
            time.sleep(0.5)
            break
    try:
        session.detach()
    except Exception:
        pass
    if side_log.exists():
        side_log.unlink()
    dst.write_text("\n".join(lines) + "\n", encoding="utf-8")
    nfn = sum(1 for l in lines if l.startswith("=== FUNCTION"))
    print(f"[colorer] {dst}  ({len(lines)} events, {nfn} fn labels, "
          f"obj produced: {obj.exists()})")
    return dst


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("source", help="TU path, e.g. src/game/clFlowItem.c")
    ap.add_argument("--ir", action="store_true", help="IR-optimizer per-pass dump")
    ap.add_argument("--colorer", action="store_true", help="frida colorer dump")
    ap.add_argument("--regdiff", action="store_true",
                    help="register-web permutation report vs target obj")
    ap.add_argument("--version", default="GNLJ82")
    args = ap.parse_args()
    if not args.ir and not args.colorer and not args.regdiff:
        args.ir = args.colorer = True

    src_rel = args.source.replace("\\", "/")
    src = (REPO / src_rel).resolve()
    if not src.is_file():
        sys.exit(f"not found: {src}")

    flags = extract_flags(src_rel, args.version)
    print(f"[flags] {' '.join(flags)}")
    priv, irdump_exe, irdumpq_exe = prep_scratch()

    if args.ir:
        run_ir(irdump_exe, flags, src)
    if args.colorer:
        run_colorer(irdumpq_exe, flags, src)
    if args.regdiff:
        run_regdiff(flags, src, src_rel, args.version)
    # shipped compiler must remain untouched
    assert sha1(SHIPPED) == SHIPPED_SHA1
    print("[ok] shipped compiler untouched (SHA-1 verified)")


if __name__ == "__main__":
    main()

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
             Requires `pip install frida`. Output: tmp/dump/<base>.colorer.log

Both by default. The build graph is never touched: the shipped compiler stays
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


def prep_scratch() -> tuple[Path, Path]:
    """Create private plain + IR-dump-patched compiler copies in tmp_probe/."""
    assert sha1(SHIPPED) == SHIPPED_SHA1, "shipped mwcceppc.exe SHA-1 mismatch!"
    SCRATCH.mkdir(exist_ok=True)
    priv = SCRATCH / "mwcceppc_priv.exe"
    irdump = SCRATCH / "mwcceppc_irdump.exe"
    if not priv.exists() or sha1(priv) != SHIPPED_SHA1:
        shutil.copy2(SHIPPED, priv)
    if not irdump.exists():
        irdump_patch(str(priv), str(irdump), verbose=True)
    for exe_dir in {priv.parent}:
        dll = exe_dir / "lmgr326b.dll"
        if not dll.exists():
            shutil.copy2(LMGR, dll)
    return priv, irdump


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
    dst.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"[colorer] {dst}  ({len(lines)} lines, obj produced: {obj.exists()})")
    return dst


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("source", help="TU path, e.g. src/game/clFlowItem.c")
    ap.add_argument("--ir", action="store_true", help="IR-optimizer per-pass dump")
    ap.add_argument("--colorer", action="store_true", help="frida colorer dump")
    ap.add_argument("--version", default="GNLJ82")
    args = ap.parse_args()
    if not args.ir and not args.colorer:
        args.ir = args.colorer = True

    src_rel = args.source.replace("\\", "/")
    src = (REPO / src_rel).resolve()
    if not src.is_file():
        sys.exit(f"not found: {src}")

    flags = extract_flags(src_rel, args.version)
    print(f"[flags] {' '.join(flags)}")
    priv, irdump_exe = prep_scratch()

    if args.ir:
        run_ir(irdump_exe, flags, src)
    if args.colorer:
        run_colorer(priv, flags, src)
    # shipped compiler must remain untouched
    assert sha1(SHIPPED) == SHIPPED_SHA1
    print("[ok] shipped compiler untouched (SHA-1 verified)")


if __name__ == "__main__":
    main()

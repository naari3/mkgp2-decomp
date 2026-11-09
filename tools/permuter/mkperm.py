#!/usr/bin/env python3
"""Set up a decomp-permuter (github.com/simonlindholm/decomp-permuter) directory
for one function of this project.

    python3 tools/permuter/mkperm.py src/game/Foo.c FnName [--out DIR] [--cc 2.6]

Run from the repo root after a normal `ninja`. Creates DIR (default
build/permuter/<FnName>) with:
  base.c       gcc-cpp'd TU (pragmas kept), other fn bodies stripped,
               inline fns kept. For C++ TUs everything but the kept fns is
               wrapped in PERM_IGNORE() and PERM_PRETEND typedefs are added
               so pycparser can parse the target fn (see README.md).
  compile.sh   the exact ninja mwcc command (+ symbol rename for C++ manglings)
  target.o     dtk's split of the original object (build/GNLJ82/obj/<unit>.o)
  settings.toml  compiler_type=mwcc, objdump limited to the one fn
Then: python3 <decomp-permuter>/permuter.py DIR -j8
"""
import argparse
import os
import re
import shlex
import stat
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
OBJDUMP = REPO / "build/binutils/powerpc-eabi-objdump"


def ninja_cmd(src: Path) -> list:
    rel = src.relative_to("src").with_suffix(".o")
    out = f"build/GNLJ82/src/{rel}"
    txt = subprocess.check_output(["ninja", "-t", "commands", out], cwd=REPO, text=True)
    line = txt.strip().splitlines()[-1]
    first = line.split(" && ")[0]
    toks = shlex.split(first)
    res = []
    skip = False
    for i, t in enumerate(toks):
        if skip:
            skip = False
            continue
        if t in ("-MMD",):
            continue
        if t in ("-c", "-o"):
            skip = True
            continue
        res.append(t)
    return res


def cpp_flags(cmd: list) -> list:
    flags = []
    it = iter(range(len(cmd)))
    for i in it:
        t = cmd[i]
        if t == "-i":
            flags.append("-I" + cmd[i + 1])
            next(it)
        elif t.startswith("-D"):
            flags.append(t)
    return flags


HDR_RE = re.compile(r"(~?[\w:]+|operator\s*\S+)\s*\(([^;{}]*)\)\s*(const\s*)?(:[^;{}]*)?$", re.S)


def split_top(text: str):
    """Yield (kind, chunk, name) for top-level items: kind fn/other."""
    i = 0
    n = len(text)
    start = 0
    depth_stack = []  # transparent scopes (extern "C" {, namespace X {)
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j + 1
            continue
        if c == "#" and (i == 0 or text[i - 1] == "\n"):
            j = text.find("\n", i)
            j = n if j < 0 else j
            if start < i:
                yield ("other", text[start:i], None)
            yield ("pp", text[i:j + 1], None)
            i = start = j + 1
            continue
        if c == "}" and depth_stack:
            if start < i:
                yield ("other", text[start:i], None)
            depth_stack.pop()
            yield ("other", "}", None)
            i = start = i + 1
            continue
        if c == ";":
            yield ("other", text[start:i + 1], None)
            i = start = i + 1
            continue
        if c == "{":
            head = text[start:i]
            hs = head.strip()
            if re.fullmatch(r'(extern\s+"C(\+\+)?"|namespace(\s+\w+)?)', hs):
                yield ("other", text[start:i + 1], None)
                depth_stack.append(1)
                i = start = i + 1
                continue
            # find matching brace
            d = 0
            j = i
            while j < n:
                ch = text[j]
                if ch == '"' or ch == "'":
                    k = j + 1
                    while k < n and text[k] != ch:
                        k += 2 if text[k] == "\\" else 1
                    j = k + 1
                    continue
                if ch == "{":
                    d += 1
                elif ch == "}":
                    d -= 1
                    if d == 0:
                        break
                j += 1
            m = HDR_RE.search(hs)
            isfn = (m is not None and "=" not in hs.split("(")[0]
                    and not re.match(r"(typedef\s+)?(struct|union|enum|class)\b", hs))
            if isfn:
                name = m.group(1).split("::")[-1]
                yield ("fn", (head, text[i:j + 1]), name)
                i = start = j + 1
            else:
                i = j + 1  # struct body etc: continue to the ';'
            continue
        i += 1
    if start < n:
        yield ("other", text[start:], None)


def strip_fns(text: str, fn: str, keep_bodies: bool = False):
    out = []
    kept = []
    for kind, chunk, name in split_top(text):
        if kind != "fn":
            out.append(("o", chunk))
            continue
        head, body = chunk
        if name == fn or re.search(r"\binline\b", head):
            out.append(("k", head + body))
            kept.append(name)
        elif keep_bodies:
            out.append(("o", head + body))
        else:
            h = re.sub(r"\basm\b", "", head).rstrip()
            out.append(("o", h + ";"))
    return out, kept


def _insert_pretend(parts, pretend):
    out = []
    done = False
    for p in parts:
        if not done and not p.startswith("PERM_IGNORE("):
            out.append(pretend)
            done = True
        out.append(p)
    return "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("fn")
    ap.add_argument("--unit", help="unit name (default: src path without ext)")
    ap.add_argument("--out")
    ap.add_argument("--cc", help="override compiler version, e.g. 2.6")
    ap.add_argument("--base", help="use this (already preprocessed) base.c instead")
    ap.add_argument("--check", action="store_true", help="compile base.c once and diff vs target")
    ap.add_argument("--show-inlines", action="store_true",
                    help="C++: leave inline helpers visible to the permuter (they must be C-parsable)")
    a = ap.parse_args()

    os.chdir(REPO)
    src = Path(a.src)
    unit = a.unit or str(src.relative_to("src").with_suffix(""))
    out = Path(a.out or f"build/permuter/{a.fn}").resolve()
    out.mkdir(parents=True, exist_ok=True)
    cmd = ninja_cmd(src)
    if a.cc:
        cmd = [re.sub(r"GC/[^/]+/", f"GC/{a.cc}/", t) for t in cmd]
    cxx = "-lang=c++" in cmd or src.suffix == ".cpp"
    target = REPO / f"build/GNLJ82/obj/{unit}.o"
    if not target.exists():
        sys.exit(f"no target object {target}")
    os.system(f"cp '{target}' '{out}/target.o'")

    if a.base:
        base = Path(a.base).read_text()
    else:
        pp = ["cpp", "-P", "-nostdinc", "-undef", "-D__MWERKS__=0x4302", "-D__PPCGEKKO__"]
        if cxx:
            pp += ["-x", "c++"]
        pp += cpp_flags(cmd) + [str(src)]
        text = subprocess.check_output(pp, text=True)
        # C++: out-of-class member decls are illegal, so keep every body there
        chunks, kept = strip_fns(text, a.fn, keep_bodies=cxx)
        if cxx and not a.show_inlines:
            chunks = [("k" if (k == "k" and re.search(r"\b%s\s*\(" % re.escape(a.fn), c.split("{")[0])) else ("o" if k == "k" else k), c) for k, c in chunks]
        if a.fn not in kept:
            sys.exit(f"{a.fn} not found in {src}")
        if cxx:
            # pycparser can't read C++: hide everything but the kept fns.
            parts = []
            buf = []
            for k, c in chunks:
                if k == "k":
                    if buf:
                        parts.append("PERM_IGNORE(\n" + "".join(buf) + "\n)\n")
                        buf = []
                    parts.append(c)
                else:
                    buf.append(c)
            if buf:
                parts.append("PERM_IGNORE(\n" + "".join(buf) + "\n)\n")
            hidden = "".join(c for k, c in chunks if k != "k")
            visible = "".join(c for k, c in chunks if k == "k")
            names = set(re.findall(r"\b(?:struct|class|union|enum)\s+(\w+)", hidden))
            names |= set(re.findall(r"typedef[^;{}]*?(\w+)\s*;", hidden))
            names |= set(re.findall(r"typedef\s+(?:struct|union|enum)\s*\w*\s*\{.*?\}\s*(\w+)\s*;", hidden, re.S))
            used = sorted(n for n in names if re.search(r"\b%s\b" % n, visible))
            pretend = "".join(f"PERM_PRETEND(typedef struct {n} {n};)\n" for n in used)
            base = ("/* C++ TU: PERM_IGNORE hides C++ from pycparser; PERM_PRETEND typedefs\n"
                    " * make the visible fn parsable. Edit if parsing fails. */\n"
                    + _insert_pretend(parts, pretend))
        else:
            base = "".join(c for _, c in chunks)
            base = re.sub(r"__declspec\s*\(\s*\w+\s*\)", "", base)
    (out / "base.c").write_text(base)

    # mangled name of the fn in our object (C++): rename to the plain name
    wibo = [str(REPO / t) if (REPO / t).exists() else t for t in cmd]
    cs = ["#!/bin/bash", "# usage: compile.sh in.c -o out.o",           'IN="$(realpath "$1")"; OUT="$(realpath "$3")"; T="$(mktemp --suffix=.o)"',
          f"cd '{REPO}'",
          shlex.join(wibo) + ' -c "$IN" -o "$T" >/dev/null || { rm -f "$T"; exit 1; }']
    if cxx:
        cs.append(f"SYM=$({REPO}/build/binutils/powerpc-eabi-nm \"$T\" | awk '$3 ~ /^{a.fn}__/ {{print $3; exit}}')")
        cs.append(f'[ -n "$SYM" ] && {REPO}/build/binutils/powerpc-eabi-objcopy --redefine-sym "$SYM={a.fn}" "$T"')
    cs.append('mv "$T" "$OUT"')
    (out / "compile.sh").write_text("\n".join(cs) + "\n")
    os.chmod(out / "compile.sh", 0o755)
    (out / "settings.toml").write_text(
        f'func_name = "{a.fn}"\ncompiler_type = "mwcc"\n'
        f'objdump_command = "{OBJDUMP} -drz --disassemble={a.fn}"\n')
    if a.check:
        check(out, a.fn)
    print(out)


def unperm(text: str) -> str:
    """What the permuter feeds the compiler: PERM_IGNORE(x) -> x, PERM_PRETEND(x) -> ''."""
    text = re.sub(r"PERM_PRETEND\((typedef[^;]*;)\)\n?", "", text)
    out, i = [], 0
    while True:
        j = text.find("PERM_IGNORE(", i)
        if j < 0:
            out.append(text[i:])
            return "".join(out)
        out.append(text[i:j])
        k, d = j + len("PERM_IGNORE("), 1
        st = k
        while d:
            if text[k] == "(":
                d += 1
            elif text[k] == ")":
                d -= 1
            k += 1
        out.append(text[st:k - 1])
        i = k


def disasm(o: Path, fn: str) -> list:
    txt = subprocess.check_output([str(OBJDUMP), "-dr", f"--disassemble={fn}", str(o)], text=True)
    rows = []
    for l in txt.splitlines():
        m = re.match(r"\s*[0-9a-f]+:\t(?:[0-9a-f]{2} ){4}\t(.*)", l)
        if m:
            rows.append(re.sub(r"\s+", " ", m.group(1)).strip())
    return rows


def check(out: Path, fn: str):
    import difflib
    tmp = out / ".check"
    tmp.mkdir(exist_ok=True)
    (tmp / "base.c").write_text(unperm((out / "base.c").read_text()))
    r = subprocess.run([str(out / "compile.sh"), str(tmp / "base.c"), "-o", str(tmp / "base.o")])
    if r.returncode:
        sys.exit("check: base.c does not compile")
    a, b = disasm(tmp / "base.o", fn), disasm(out / "target.o", fn)
    nd = sum(1 for l in difflib.unified_diff(a, b, n=0, lineterm="") if l[:1] in "+-" and l[:3] not in ("+++", "---"))
    print(f"check: {len(a)} vs {len(b)} insns, {nd} differing lines")


if __name__ == "__main__":
    main()

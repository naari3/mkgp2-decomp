"""Show per-row target||mine diff for one fn in the ONKARTHIT TU.
Usage: python tools/compiler_probe/rowdiff.py <FnName> [--all]
By default only shows rows that differ.
"""
import json
import subprocess
import sys

OBJDIFF = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp\build\tools\objdiff-cli.exe"
OBJ = "build/GNLJ82/obj/game/auto_ONKARTHIT_block.o"
SRC = "build/GNLJ82/src/game/auto_ONKARTHIT_block.o"


def fmt(ins):
    if ins is None:
        return "---"
    inner = ins.get("instruction")
    if inner is None:
        return "(gap)"
    return inner.get("formatted", "?")


def get_sym(side, name):
    for s in side["symbols"]:
        if s.get("name") == name:
            return s
    return None


def main():
    name = sys.argv[1]
    show_all = "--all" in sys.argv
    out = subprocess.run(
        [OBJDIFF, "diff", "-1", OBJ, "-2", SRC, "-o", "-", "--format", "json-pretty"],
        capture_output=True,
        text=True,
    )
    d = json.loads(out.stdout)
    lsym = get_sym(d["left"], name)
    rsym = get_sym(d["right"], name)
    if lsym is None:
        print("target sym not found")
        return
    lins = lsym.get("instructions", [])
    rins = rsym.get("instructions", []) if rsym else []
    n = max(len(lins), len(rins))
    print(f"{name}: target rows={len(lins)} mine rows={len(rins)} match={lsym.get('match_percent')}")
    for i in range(n):
        li = lins[i] if i < len(lins) else None
        ri = rins[i] if i < len(rins) else None
        lt = fmt(li)
        rt = fmt(ri)
        lk = li.get("diff_kind") if li else "None"
        rk = ri.get("diff_kind") if ri else "None"
        diff = (lk not in (None, "None")) or (rk not in (None, "None")) or (lt != rt)
        if diff or show_all:
            mark = "  " if not diff else "XX"
            print(f"{mark} {i:4d}  {lt:36s} || {rt}")


if __name__ == "__main__":
    main()

"""Measure objdiff match_percent for named fns in the ONKARTHIT TU.
Usage: python tools/compiler_probe/measure_fns.py [fn1 fn2 ...]
"""
import json
import subprocess
import sys

OBJDIFF = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp\build\tools\objdiff-cli.exe"
OBJ = "build/GNLJ82/obj/game/auto_ONKARTHIT_block.o"
SRC = "build/GNLJ82/src/game/auto_ONKARTHIT_block.o"

DEFAULT = (
    "CarObject_Init",
    "CarObject_ProcessWarpAndDash",
    "KartItem_ApplyImpactReflectAndDampVelocity",
)


def main():
    wanted = sys.argv[1:] or list(DEFAULT)
    out = subprocess.run(
        [OBJDIFF, "diff", "-1", OBJ, "-2", SRC, "-o", "-", "--format", "json-pretty"],
        capture_output=True,
        text=True,
    )
    d = json.loads(out.stdout)
    rows = {}
    for s in d["left"]["symbols"]:
        if "target_symbol" in s and "match_percent" in s:
            rows[s["name"]] = (s["match_percent"], s.get("size", 0))
    for n in wanted:
        if n in rows:
            p, sz = rows[n]
            print(f"{n}: {p:.2f}% ({sz})")
        else:
            print(f"{n}: NOT FOUND")


if __name__ == "__main__":
    main()

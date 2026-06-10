import os
from probe_fp import probe, ROOT

CC = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
SRC = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fpnum_struct.c")

lines = []
lines.append(probe("struct:default", CC, src=SRC))
for p in [
    "gprfloatcopy off",
    "gprfloatcopy on",
    "block_assign on",
    "block_assign off",
    "gprfloatcopy off\n#pragma block_assign on",
]:
    tag = "struct:pragma:" + p.replace("\n#pragma ", " + ")
    prelude = "#pragma warn_illpragma on\n#pragma " + p
    lines.append(probe(tag, CC, src=SRC, prelude=prelude))

with open("results_fp_axis4.tsv", "w") as f:
    f.write("\n".join(lines) + "\n")

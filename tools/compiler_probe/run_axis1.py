import os
from probe import probe, ROOT

GC = ["1.0", "1.1", "1.1p1", "1.2.5", "1.2.5n", "1.3", "1.3.2", "1.3.2r",
      "2.0", "2.0p1", "2.5", "2.6", "2.7",
      "3.0a3", "3.0a3.2", "3.0a3.3", "3.0a3.4", "3.0a3p1", "3.0a5", "3.0a5.2"]
WII = ["0x4201_127", "1.0", "1.0a", "1.0RC1", "1.1", "1.3", "1.5", "1.6", "1.7"]

lines = []
for v in GC:
    cc = os.path.join(ROOT, "build", "compilers", "GC", v, "mwcceppc.exe")
    lines.append(probe(f"GC/{v} base", cc))
for v in WII:
    cc = os.path.join(ROOT, "build", "compilers", "Wii", v, "mwcceppc.exe")
    lines.append(probe(f"Wii/{v} base", cc))

with open("results_axis1.tsv", "w") as f:
    f.write("\n".join(lines) + "\n")

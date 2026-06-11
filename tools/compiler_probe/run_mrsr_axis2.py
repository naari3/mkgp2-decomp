#!/usr/bin/env python3
# mr-SR-init axis 2: (a) which -opt sub-pass folds the off=i copy (research
# only; TU-wide flags are fixed in production so this is for understanding),
# (b) compiler revision sweep with production flags.
import os
from run_mrsr_axis1 import probe, BASE_FLAGS, ROOT, HERE

lines = []
cc132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")

# (a) pass isolation on 1.3.2: -O4,p then -opt overrides appended
for sub in ["noprop", "nocse", "nostrength", "noloopinvariants", "nopeephole",
            "nodeadstore", "nolifetimes"]:
    lines += probe(f"GC/1.3.2 -opt {sub}", cc132, extra_flags=["-opt", sub],
                   fn_filter=lambda n: n in ("v01_baseline", "v02_plainidx"))

# (b) compiler sweep, production flags, v01/v02 only
GC = ["1.0", "1.1", "1.1p1", "1.2.5", "1.2.5n", "1.3", "1.3.2", "1.3.2r",
      "2.0", "2.0p1", "2.5", "2.6", "2.7"]
for v in GC:
    cc = os.path.join(ROOT, "build", "compilers", "GC", v, "mwcceppc.exe")
    if not os.path.exists(cc):
        continue
    lines += probe(f"GC/{v} prod", cc,
                   fn_filter=lambda n: n in ("v01_baseline", "v02_plainidx"))

with open(os.path.join(HERE, "results_mrsr_axis2.tsv"), "w") as f:
    f.write("\n".join(lines) + "\n")

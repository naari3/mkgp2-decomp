#!/usr/bin/env python3
# Phase 2b axis 1: robustness of the loop-copy frsp store-forward recipe
# (f34/f35/f36) across language modes, flags, and compiler versions.
import os
from probe_frsp import probe, ROOT, BASE_FLAGS

CC = os.path.join(ROOT, "build", "compilers", "GC", "{}", "mwcceppc.exe")

lines = []

# --- flag axis on 1.3.2 (production compiler for this TU) ---
cc132 = CC.format("1.3.2")
lines.append(probe("1.3.2 C base(-O4,p exc-on)", cc132))
lines.append(probe("1.3.2 C++ base", cc132, ["-lang", "c++"]))
lines.append(probe("1.3.2 C exc-off", cc132,
                   ["-Cpp_exceptions", "off"]))
lines.append(probe("1.3.2 C++ exc-off", cc132,
                   ["-lang", "c++", "-Cpp_exceptions", "off"]))
lines.append(probe("1.3.2 C++ RTTI-on", cc132, ["-lang", "c++", "-RTTI", "on"]))
lines.append(probe("1.3.2 C -O4,s", cc132, ["-O4,s"]))
lines.append(probe("1.3.2 C -O4", cc132, ["-O4"]))
lines.append(probe("1.3.2 C -O3", cc132, ["-O3"]))
lines.append(probe("1.3.2 C -O2", cc132, ["-O2"]))
lines.append(probe("1.3.2 C inline-noauto", cc132, ["-inline", "noauto"]))
lines.append(probe("1.3.2 C fp_contract-off", cc132, ["-fp_contract", "off"]))
lines.append(probe("1.3.2 C lmw-off", cc132, ["-use_lmw_stmw", "off"]))

# --- compiler version axis (base production flags) ---
for v in ["1.0", "1.1", "1.2.5", "1.3", "1.3.2r", "2.0", "2.5", "2.6", "2.7"]:
    lines.append(probe(f"GC/{v} C base", CC.format(v)))

out = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                   "results_frsp_axis1.tsv")
with open(out, "w") as f:
    f.write("\n".join(lines) + "\n")

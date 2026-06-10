import os
from probe_fp import probe, ROOT, BASE_FLAGS

CC = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")

# replace the -O4,p slot with explicit -opt spellings / suboption toggles
def flags_with(opt_repl):
    f = []
    for x in BASE_FLAGS:
        if x == "-O4,p":
            f.extend(opt_repl)
        else:
            f.append(x)
    return f

CASES = [
    ("base+nolifetimes", flags_with(["-O4,p", "-opt", "nolifetimes"])),
    ("base+nocse", flags_with(["-O4,p", "-opt", "nocse"])),
    ("base+nodeadstore", flags_with(["-O4,p", "-opt", "nodeadstore"])),
    ("base+nodeadcode", flags_with(["-O4,p", "-opt", "nodeadcode"])),
    ("base+noprop", flags_with(["-O4,p", "-opt", "noprop"])),
    ("base+nostrength", flags_with(["-O4,p", "-opt", "nostrength"])),
    ("base+noloop", flags_with(["-O4,p", "-opt", "noloop"])),
    ("base+nopeephole", flags_with(["-O4,p", "-opt", "nopeephole"])),
    ("base+nospace", flags_with(["-O4,p", "-opt", "nospace"])),
    ("base+nospeed", flags_with(["-O4,p", "-opt", "nospeed"])),
    ("base+sched_off", flags_with(["-O4,p", "-schedule", "off"])),
    ("base+sched_on", flags_with(["-O4,p", "-schedule", "on"])),
    ("opt_explicit_all", flags_with(["-opt", "speed,level=4,peephole,schedule"])),
    ("opt_l4_speed_peep", flags_with(["-opt", "speed,level=4,peephole"])),
    ("opt_l4_speed_sched", flags_with(["-opt", "speed,level=4,schedule"])),
    ("opt_l4_speed", flags_with(["-opt", "speed,level=4"])),
    ("opt_l4", flags_with(["-opt", "level=4,peephole,schedule"])),
    ("opt_l3_speed", flags_with(["-opt", "speed,level=3,peephole,schedule"])),
    ("opt_l2_speed", flags_with(["-opt", "speed,level=2,peephole,schedule"])),
    ("opt_l1_speed", flags_with(["-opt", "speed,level=1,peephole,schedule"])),
    ("opt_l0_speed", flags_with(["-opt", "speed,level=0,peephole,schedule"])),
    ("O3p", flags_with(["-O3,p"])),
    ("O2p", flags_with(["-O2,p"])),
    ("O1", flags_with(["-O1"])),
    ("O4s", flags_with(["-O4,s"])),
    ("O4", flags_with(["-O4"])),
    ("base+lifetimes_on", flags_with(["-O4,p", "-opt", "lifetimes"])),
    ("base+nolife_nocse", flags_with(["-O4,p", "-opt", "nolifetimes,nocse"])),
    ("base+nolife_nosched", flags_with(["-O4,p", "-opt", "nolifetimes", "-schedule", "off"])),
    ("base+nodead", flags_with(["-O4,p", "-opt", "nodead"])),
]

lines = []
for tag, fl in CASES:
    lines.append(probe("opt:" + tag, CC, flags=fl))

with open("results_fp_axis3.tsv", "w") as f:
    f.write("\n".join(lines) + "\n")

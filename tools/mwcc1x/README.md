# Reverse-engineering the GC/1.x (1.0 .. 1.2.5n) compilers

No source exists for the GC/1.x backend (mweppc covers GC/2.0..2.7; 1.3.x is
the same generation as 2.0). Findings are in docs/mwcc_internals.md, section
"GC/1.x backend". This folder holds the Ghidra scripts used to get them.

Setup (about 10 minutes, needs JDK 21 and github.com):

    curl -sSLo g.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_11.4.2_build/ghidra_11.4.2_PUBLIC_20250826.zip
    unzip -q g.zip
    G=ghidra_11.4.2_PUBLIC/support/analyzeHeadless
    cp build/compilers/GC/1.2.5/mwcceppc.exe /tmp/mwcc125.exe
    # full analysis + every function decompiled into one file (~6 MB, ~8 min)
    $G /tmp/gproj p125 -import /tmp/mwcc125.exe -scriptPath tools/mwcc1x \
       -postScript DumpAll.java /tmp/mwcc125.c
    # functions reached only through pointers (machine-model tables) are not
    # found by auto-analysis: create and decompile them by address
    $G /tmp/gproj p125 -process mwcc125.exe -noanalysis -scriptPath tools/mwcc1x \
       -postScript DecAt.java /tmp/out.c 0x52ec90 0x52ea80

Finding a 2.x function in 1.2.5: take a `"File.c"` assert string, find the
`push imm32` references to its address (each is an assert inside that file),
and compare the decompiled neighbours with mweppc's version of the file.
Struct offsets differ from 2.x (PCode flags at +0x16, op at +0x14, args at
+0x1C with 12-byte operands; read = 8, write = 0x10, pointer access = 0x40).

To see PCode for a 1.2.5 function, `python3 tools/mwccdbg.py UNIT FN` runs
mwcc-debugger with GC/1.1, which has the same backend.

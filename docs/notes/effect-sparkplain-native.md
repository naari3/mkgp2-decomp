# SparkPlain native callback

## 2026-10-23 — actual context-mode decomp trial

`Effect_SparkPlain_Update` at `800C57E4..800C59E0`: direct nested Rand_RangeFloat arguments reproduce the initialization/ABI shape, including f30/f31 saves. Sequencing the double-returning `fn_8027E9E8` result and the polynomial removes a cross-call constant hoist: text95.74803% becomes98.89764%. Explicit default at the switch beginning or end does not recreate the target-only dead branch at +0x44; both final candidates remain504 versus508 target bytes. Automatic EH8 matches100%; index12 matches91.66667% because the function length differs. Three structural approaches were exhausted; retain NonMatching rather than blindly retrying or treating target fallback as genuine C.

This work actually used context-mode1.0.169 MCP for target ASM and objdiff/build-log inspection. The other arm implements a different nearby function, so output-byte and time differences do not establish a causal matching advantage. The source uses only a narrow target-observed local view; no live Ghidra type discovery was performed.

Main independently rebuilt the unchanged native body with actual source input and no fallback: CHECK exited1 with SHA-1 `e6a5ded7440dc7673133aa6172362430f76c6886`, reproducing the worker's final source trial. Direct objdiff independently confirmed text98.89764%, automatic EH100%, and index91.66667%. The NonMatching declaration preserves target fallback and must not be counted as genuine matched progress.

Final independent foreground `all_source progress build/GNLJ82/report.json build/GNLJ82/ok` exited0 with target SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`. Actual main input is the target object, not the compiled source. Aggregate matched1057/7614 did not increase; genuine gain remains0.

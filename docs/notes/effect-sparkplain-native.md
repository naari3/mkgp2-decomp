# SparkPlain native callback

## 2026-10-23 — actual context-mode decomp trial

`Effect_SparkPlain_Update` at `800C57E4..800C59E0`: direct nested Rand_RangeFloat arguments reproduce the initialization/ABI shape, including f30/f31 saves. Sequencing the double-returning `fn_8027E9E8` result and the polynomial removes a cross-call constant hoist: text95.74803% becomes98.89764%. Explicit default at the switch beginning or end does not recreate the target-only dead branch at +0x44; both final candidates remain504 versus508 target bytes. Automatic EH8 matches100%; index12 matches91.66667% because the function length differs. Three structural approaches were exhausted; retain NonMatching rather than blindly retrying or treating target fallback as genuine C.

This work actually used context-mode1.0.169 MCP for target ASM and objdiff/build-log inspection. The other arm implements a different nearby function, so output-byte and time differences do not establish a causal matching advantage. The source uses only a narrow target-observed local view; no live Ghidra type discovery was performed.

Main independently rebuilt the unchanged native body with actual source input and no fallback: CHECK exited1 with SHA-1 `e6a5ded7440dc7673133aa6172362430f76c6886`, reproducing the worker's final source trial. Direct objdiff independently confirmed text98.89764%, automatic EH100%, and index91.66667%. The NonMatching declaration preserves target fallback and must not be counted as genuine matched progress.

Final independent foreground `all_source progress build/GNLJ82/report.json build/GNLJ82/ok` exited0 with target SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`. Actual main input is the target object, not the compiled source. Aggregate matched1057/7614 did not increase; genuine gain remains0.

## c15_u31_20261106
Source: Codex worker c15_u31_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u31: explicit case 2: break; default: break; before case 0 (as in neighboring EffectStarBurst) restores target-only dead switch branch at +0x44. Text improves 98.89764/504B to 99.685036/508B; extab8/index12 both100. FP residual remains lifetime f4 vs source f2 and wave f2 vs source f4/f3 at 800C5968..5980 (five rows). Declaration reorder invariant; inline polynomial helper99.6063 reverted. Singleton stays NonMatching; coordinator fallback full DOL SHA1 exact, zero native gain.

## c16_u134_20261106
Source: Codex worker c16_u134_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 508 B.

c16_u134: compound scale = lifetime * (((1.0f + float-rounded sin(angle))/2.0f)/2.0f +0.5f) resolves all five residual FP register rows. Staged literal polynomial alone regresses99.6063 (operand reversal). Compound division form yields100% text508/extab8/index12. Existing Matching flag promotion needs no split/data/EH changes. Final source-linked full build SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65, gain1fn/508B.

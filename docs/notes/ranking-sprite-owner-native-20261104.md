# Ranking sprite owner / sprite browser (anon_801D286C) — 2026-11-04

Source: Codex worker cx_a2_sprite286c_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

## Observed
- Native exact (text/extab/extabindex 100%, source-linked): fn_801D3480 (340B), fn_801D35D4 (888B), fn_801D3B7C (1140B, parameter browser, first compile), fn_801D4118 (684B, unlock snapshot).
- fn_801D35D4: putting the increment/decrement inside the range test reproduces the target compare-before-store sequence.
- fn_801D4118: a chained assignment makes the loop counter and cleared fields share the target zero register.
- Honest NonMatching: fn_801D286C placement-constructor draft 55.76% (emits 1728B vs 1696B target, one approach); EH group 2F0C/3118/3354/3364 (anon_801D2F0C.cpp) text 99.71% (3354/3364 100%, 2F0C 99.91%, 3118 99.37%) but EH order and the C++ cleanup-symbol bridge are unresolved. The group must stay one TU. Next attempt should start from per-TU mangled bridges (tools/extab_user_renames.json, see cpp-ctor-retrofit-mangled-bridge.md) and the EH order, not from register permutations.
- No ASM, manual EH or payload.

## c17_u20_20261107
Source: Codex worker c17_u20_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u20_20261107: fn_801D286C placement-new wrapper introduces a non-target null guard. A genuine out-of-line ctor plus per-TU bridges improves measured 55.759434% to 88.27358%; typed table-pool view/cache, int fn_80231B94 return/evaluation order, and matrix declaration layout reach 90.68868% (1708 B vs 1696 B). Target uses entry-retained lbl_8039BF88 base r21, self r30, allocation temporary r19; draft caches base after text initialization, self r28, temporary r20, frame 0x130 rather than 0x140. Branch-return helper for variant==1 still becomes branchless arithmetic. Reconstructed separate float/string/table definitions failed to restore pool shape (89.353775%) and were removed. Primary EH cleanup symbols now resolve but registers/PCs remain non-exact. Single-function TU cannot rescue via B. Honest NonMatching, coordinator full build exit0, original DOL SHA-1 OK, source_input false, +0 native.

## c17_u66_20261107
Source: Codex worker c17_u66_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u66: all four functions already defined; no native gain. Added per-TU ResCtrl ctor/dtor bridges, anonymous @58/59/95/96/139/140 EH symbol bridges and explicit extab order 3364,2F0C,3118 (index address order; weak ResCtrl last). Owned extab144/index36 raw prefixes and relocations exact, objdiff EH100/100. Text99.72206: 2F0C99.908394 has only z/y translation-load order at305C/3060; 3118 improves99.37063->99.405594 solely from ctor bridge and retains final label scale/z/x/y FP home cycle. Combined Show+SetScale helper invariant; SetScale-before-Show90.60839 and direct fieldwise setup90.23077 reverted. Scalar z capture invariant; Vec translation aggregate91.183205 reverted. Whole four-function reversed group cannot isolate exact3354/3364. Source bodies unchanged; retain NonMatching. Full fallback DOL SHA1 exact.

## c19_u124_20261107
Source: Codex worker c19_u124_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u124: complete native separate float[255], fixed-width character names, placement and animation tables restore entry-retained pool base r21, allocation r19 and target frame0x140. Measured90.68868->96.24764; owned rodataBF88..C55C. C-language inline name-offset getter fixes language branch polarity/default scheduling; C statement mode helper gives desired branch but receiver restore remains, return/ternary folds branchlessly. Explicit pool payload check isolates exactly12 zero bytes C468..C474 between final name and placements; no filler retained, source1480 vs target1492. All other pool bytes exact. Add27 own-key pool/EH/cookie aliases. Primary1704 vs1696; self/parameter homes, mode arithmetic, table offsets and translation y/z load order persist. EH93.181816/index95; singleton TU cannot B split. RemainsNM/source_inputfalse; coordinator full fallback DOL SHA1 exact; zero native gain.

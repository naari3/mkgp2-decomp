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

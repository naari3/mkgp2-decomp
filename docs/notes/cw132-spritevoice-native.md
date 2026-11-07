# cw132-spritevoice-native

Source: Codex worker c6_nt1_801a1714_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 9560 B.

fn_801A24B8 (3588 B) matches using canonical SpriteVoice helpers and priority 14: first current-player even voice is 0x1E2, first odd 0x1D1; other-player even 0x1E3, odd 0x1E4. fn_801A32BC (5972 B) needs g_bgmStateId=0 before current=&g_raceEntryArray[lbl_806D1775] to reproduce the target zero web/prologue schedule; all later logic and all EH then match. These two singleton groups are independently split-safe. The current countdown/goal NonMatching sources expose persistent base-register and pooled table-address differences; do not promote on fuzzy similarity.

## c14_u61_20261106
Source: Codex worker c14_u61_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u61: fn_801AECF4 native draft improves raw objdiff 89.88308 -> 98.45942 with TU-local Goal_Select(base,character,id), capturing normal=base+14 and special=base+94 before range checks. Removes eight extra instructions / 32 B; now exact 2908 B text size and extab8/index12 100%. Residual goal-line base+0x98C association/ccClass stride plus volatile rank/distance GPR homes. Multidimensional line view 98.39752; large inline rank-switch helper not inlined (12.984869), both reverted. Singleton remains NM; full fallback-linked DOL SHA-1 OK.

## c16_u13_20261106
Source: Codex worker c16_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u13 fn_801A4F38: fresh 88.909676 -> 97.15161%. TU-local Goal_SelectOther(base,char,id) capturing normal=base+14 and special=base+94 restores pooled lhax access. First selection helper normal=base/special=base+42 improves but zero-offset normal pointer still folds into r31; struct-array representation is byte-invariant. Indexed Goal_Progress helper with shared base g_raceEntryArray+0x44 restores first progress comparison instructions; second retains scratch/scheduling differences. Final source3688 vs target3720B, extab100/index91.66667. Singleton remains NM; full fallback-linked DOL SHA1 OK.

## c18_u84_20261107
Source: Codex worker c18_u84_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u84 fn_801A4F38: explicit signed byte offset playerOffset = g_goalFanfarePlayerIndex * (int)sizeof(SpriteVoiceRaceEntry), used both for the player field and Goal_ProgressOffset(playerOffset), fixes player setup and second progress comparison, 97.15161 -> 98.07635, source3684 vs target3720, EH100/index91.66667. Nine remaining missing addi-zero instructions are caused by external base-pointer folding. Six real short array definitions in target .data order (14,14,14,52,52,52 entries) restore pooled addi base,0; together with offset reuse the diagnostic is3720B with all instruction mnemonics/registers/order exact, objdiff99.98387 with ppc_calculate_pool_relocations=false (base ...data.0 vs lbl_80496C38 and timestamp +4 aliases only), EH/index100. Actual pool split80496C38..80496DC4 fails: fn_801A1828 -> 19FC -> 1BD0 -> 1D98 -> 24B8 -> 32BC -> 4A10 -> 4F38 -> auto_07_80496DC4_data -> fn_801A1798. fn_801A1798 text801A1798..1828 owns later .data jumptable8049A060..A094, pinning opposite order. Need coordinated broader TU/pool-boundary work including that existing matched owner; cannot solve within this claim. Pool/header/split experiment fully reverted; only offset improvement retained. Full coordinator build fallback DOL SHA-1 exact, native gain0. Diagnostic source/build outputs remain under build/c18_pool_offset.*, not acceptance sources.

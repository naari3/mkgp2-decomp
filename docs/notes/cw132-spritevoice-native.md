# cw132-spritevoice-native

Source: Codex worker c6_nt1_801a1714_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 9560 B.

fn_801A24B8 (3588 B) matches using canonical SpriteVoice helpers and priority 14: first current-player even voice is 0x1E2, first odd 0x1D1; other-player even 0x1E3, odd 0x1E4. fn_801A32BC (5972 B) needs g_bgmStateId=0 before current=&g_raceEntryArray[lbl_806D1775] to reproduce the target zero web/prologue schedule; all later logic and all EH then match. These two singleton groups are independently split-safe. The current countdown/goal NonMatching sources expose persistent base-register and pooled table-address differences; do not promote on fuzzy similarity.

## c14_u61_20261106
Source: Codex worker c14_u61_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u61: fn_801AECF4 native draft improves raw objdiff 89.88308 -> 98.45942 with TU-local Goal_Select(base,character,id), capturing normal=base+14 and special=base+94 before range checks. Removes eight extra instructions / 32 B; now exact 2908 B text size and extab8/index12 100%. Residual goal-line base+0x98C association/ccClass stride plus volatile rank/distance GPR homes. Multidimensional line view 98.39752; large inline rank-switch helper not inlined (12.984869), both reverted. Singleton remains NM; full fallback-linked DOL SHA-1 OK.

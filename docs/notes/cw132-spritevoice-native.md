# cw132-spritevoice-native

Source: Codex worker c6_nt1_801a1714_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 9560 B.

fn_801A24B8 (3588 B) matches using canonical SpriteVoice helpers and priority 14: first current-player even voice is 0x1E2, first odd 0x1D1; other-player even 0x1E3, odd 0x1E4. fn_801A32BC (5972 B) needs g_bgmStateId=0 before current=&g_raceEntryArray[lbl_806D1775] to reproduce the target zero web/prologue schedule; all later logic and all EH then match. These two singleton groups are independently split-safe. The current countdown/goal NonMatching sources expose persistent base-register and pooled table-address differences; do not promote on fuzzy similarity.

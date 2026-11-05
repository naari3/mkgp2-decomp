# clstream-updateall-string-pool

Source: Codex worker c10_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1708 B.

ClStream_UpdateAll 80194214: external StreamMessages pointer causes an extra address-materialization instruction. Real readonly string literals reproduce pooled r31 prologue and addi r3,r31,0 for first print. Own 84B .rodata 8037D178..8037D1CC. Refine aggregate symbol into three strings at D178/D190/D1A8 for objdiff R_PPC_NONE identity. Removing +4 text discrepancy also lets existing sdata2 postprocessor resolve unsigned-conversion double lbl_806D9548. Text/EH/index/rodata all 100%, source-linked full DOL SHA-1 OK.

## c12_u29_20261106
Source: Codex worker c12_u29_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 632 B.

c12_u29: ClStream_PlayStereo 80194DD8 (632B) 98.974686 -> 100% by TU-local static inline ClStream *GetStream(unsigned int i) { return &g_ClStreams[i]; }, used for s/t lookups. Direct address expressions produce identical instruction count but save r24-r31 and allocate separate j byte offset r25 / t r30; accessor inline expansion restores target r25-r31, j byte offset r30 / t r26 and all other pointer homes. Text632/extab8/index12 all100; unchanged flags/splits, Matching source link full DOL SHA-1 OK.

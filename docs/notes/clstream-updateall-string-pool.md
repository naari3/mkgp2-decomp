# clstream-updateall-string-pool

Source: Codex worker c10_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1708 B.

ClStream_UpdateAll 80194214: external StreamMessages pointer causes an extra address-materialization instruction. Real readonly string literals reproduce pooled r31 prologue and addi r3,r31,0 for first print. Own 84B .rodata 8037D178..8037D1CC. Refine aggregate symbol into three strings at D178/D190/D1A8 for objdiff R_PPC_NONE identity. Removing +4 text discrepancy also lets existing sdata2 postprocessor resolve unsigned-conversion double lbl_806D9548. Text/EH/index/rodata all 100%, source-linked full DOL SHA-1 OK.

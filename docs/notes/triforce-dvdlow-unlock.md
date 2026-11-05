# triforce-dvdlow-unlock

Source: Codex worker c3_u15_dvdlow_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 37 fn / 4448 B.

AlarmHandlerForTimeout requires volatile OSTime LastCommandIssued to reproduce high-word-first load, 0x2F0 frame, r26..r31 saves. __DIKey tentative global is emitted after static sbss by CW; a separate data-only TU at 806D1DA8..806D1DB0 preserves natural alignment and lets exact main text link natively. Odd key generation must truncate fn_802867B8 result to u16 before key=key*2+1; this improves the remaining helper to 95.65%, but scratch-web and reload residuals remain.

## c13_u41_20261106
Source: Codex worker c13_u41_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u41: fn_8028625C improves 95.652176 -> 98.91304 by combining snapshot load/XOR into v[0]=((key<<16)|cmd)^__DIKey->cmd; v[1]=offset^__DIKey->offset; v[2]=length^__DIKey->length. This eliminates the redundant command load and restores 184-byte target size. Residual is loaded command/result r8 vs target r7, multiplier r7 vs target r8, and command XOR operand order. Staging command into v[0] before key XOR regresses to 95.434784 (r9 result, lis/xor schedule). Remains NonMatching; full coordinator build SHA-1 OK.

# triforce-dvdlow-unlock

Source: Codex worker c3_u15_dvdlow_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 37 fn / 4448 B.

AlarmHandlerForTimeout requires volatile OSTime LastCommandIssued to reproduce high-word-first load, 0x2F0 frame, r26..r31 saves. __DIKey tentative global is emitted after static sbss by CW; a separate data-only TU at 806D1DA8..806D1DB0 preserves natural alignment and lets exact main text link natively. Odd key generation must truncate fn_802867B8 result to u16 before key=key*2+1; this improves the remaining helper to 95.65%, but scratch-web and reload residuals remain.

# set-course-params-unlock

Source: Codex worker c16_u74_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u74: fresh SetCourseParams 71.84677% (reported 73.66%). Rank loop compiles into two iterations of four resets; eight explicit inline ResetRankSlot calls remove bdnz and improve to 87.69758% (0x3CC vs target0x3E0). BSS first-use pool remains wrong (scores0xC0/rank0x184 vs target0x26338/0x26348); moving definitions after function in reverse order loses pooling and regresses to65.93145. Typed helper access across all resets is identical to rank-only final. Keep NonMatching; full fallback DOL SHA-1 verified. BSS100% content score does not imply symbol layout match.

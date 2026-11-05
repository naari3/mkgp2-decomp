# Scene functions 0x8016219C..0x80163C68 — 2026-11-05

Source: Codex worker cxc_u1_scene162_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, SHA-1 OK, actual main.elf ranges).

## Native (source-linked), 3 fn / 2760 B
- fn_8016303C (1160 B, game/Scene_8016303C.cpp): needs `mw_version="GC/2.7"` + `restrict` self + literal `1.0f`; its early interleaved loads/prologue distinguish it from nearby GC/1.3.2 matches.
- fn_801638B4 (948 B): int-return unref helper — `unsigned char permanent = (refs == (unsigned short)-1); if (permanent) return permanent; return refs-- == 0;`.
- fn_80163C68 (652 B): canonical DemoKartScene.h plus a private int-alpha declaration for fn_80181790.

## Honest NonMatching drafts
- fn_80162D90 99.82 %: credit-tick predicate must be `credits <= 0` (not `== 0`); six remaining r30/r31 operands did not move with a real member conversion.
- fn_8016219C 79.85 %: exception-pointer web; fn_8016234C 94.28 %: transition comparison / FP scheduling.
No asm / manual EH.

## c3_n3_scene16_20261105
Source: Codex worker c3_n3_scene16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 5568 B.

2026-11-05 c3_n3_scene16: fn_8016234C matched: float literals; a function-scope float t shared by cases 1 and 3; the repeated credit draw block is a static inline helper (s, alpha) called with t / lbl_806D8888 / 1.0f - t (case 2 keeps the extern const so scale * 1.0 is not folded); inside it `int special = (s->item >= 159) ? 1 : 0;` materializes the srawi/srwi/subfc/adde bool (a direct bool/int/uchar compare is forwarded and does not).

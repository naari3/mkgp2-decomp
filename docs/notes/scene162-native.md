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

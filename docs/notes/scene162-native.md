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

## c16_u57_20261106
Source: Codex worker c16_u57_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u57 fn_8016219C: expand ClStr to ptr+refs and add an intervening std::SceneString wrapper with native ctor/dtor declaration. This restores independent r27 member base, r28 exception base, 0x30 frame, stmw/lmw and exact48B EH/12B index; 79.85333 ->97.2 at target300B. Residual mr r3,r30 before lwz r4,0(r31) (target reverse) plus compiler throw type descriptor @23 vs lbl_8036924C. -rostr DOES move generated55B exception type string to .rodata, offering a valid future ownership route; flag reverted here because text still nonexact. Placement-new+explicit __throw produces null guard/304B83.68%; inline fill helper swaps destination/value r4/r5 (95.6%); both rejected. Singleton remains NM; full fallback DOL SHA1 exact.

## c18_u81_20261107
Source: Codex worker c18_u81_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u81: fn_8016219C remains97.333336%,300B, with only+0xB4/+0xB8 mr r3,r30 versus lwz r4,0(r31) swapped. Fresh unbridged baseline97.2. Own .rodata80369238..80369284 with actual file-static20B vector length error message and -rostr compiler55B exception type string at4C. Add @23->global:lbl_8036924C and lbl_80369238->global:lbl_80369238 to own bridge. Pool/EH/index100; natural38 base removes4C-only8-byte alignment warning, no filler. Full-storage inline helper swaps fill r4/r5 (95.6); incoming count reuse invariant; scalar placement construction adds null guard/removes unrolling (77.653336/248B). All reverted. No single-function B cut; NonMatching retained; final coordinator fallback DOL SHA-1 OK; zero native gain.

VSMode_Init C++ draft inside the merged VS/Battle TU (gaveup-retry, 2026-11-08 ~09:50Z), 99.04% / 62 diff lines (d7 file is the latest).
File: VSMode_FrameUpdate_d6.c = whole src/game/VSMode_FrameUpdate.c with the `#if 0` draft switched on (#if 1).
renames.diff: the ctor renames (__ct__10VSInput_p2Fv -> InputManager_Init, ...).
Wins over the old 92% draft: use_lmw_stmw on; VSPeer team as bitfield `teamTop:1, teamId:3, teamLow:4` (cmplw/extrwi)
and charId:4; `VSPeer* table = lbl_805A6154;` local before the stores (r30 base); host flag bitfield (rlwimi);
`int cc = g_ccClass;` + round/cup/mode locals before the GetEnemyParam() calls; cup table as
`VSRaceRow (*row)[3][2] = (VSRaceRow (*)[3][2])VS_MODE + g_cupId; row[-1][cc][long]`; shared `slot`; for(int i) on loop 6.
Left: loop-variable register numbering; camera ctor arg scheduling; 4 bytes too long.
TODO to land: the switch jumptable needs .data 0x8040E728..0x8040E780 owned by the TU (RTTI 8040E728, vtables 8040E734/8040E76C:
`python3 -I tools/data2c.py .data 0x8040E728 0x8040E780`), drop the manual extab for VSMode_Init and rename the auto @N extab.

v3 (2026-11-08 ~11:05Z, gaveup-retry): full_v3.diff = apply on main 122d9dbc+ (`git apply full_v3.diff`). VSMode_Init 99.60%,
extab/extabindex/.data 100% (TU owns .data 0x8040E728..0x8040E780: RTTI+vtable defined before the fn, base vtable after; the switch
table @N lands between them). Wins: VSCamera ctor is (float, int, float, int, void*) (f1,r4,f2,r5,r6 order); packet as `signed char*`.
Auto extab renames: "@436"->@etb_8000963C, "@437"->@eti_80022250 (the @N shifts when objects are added before it - recheck with llvm-objdump -t).
Left (all reg numbering, same insn count except 1 extra mr): peers r20/cpus-loop i r21 (ours +1); car loop slot r21/human r24 swapped
(ours copies slot via mr); path loop ptr r20/i r23; item loop slot r20; row address temps; preload loop item r20/i r21; AI loop i r23
after round/cup/mode r20-22. Tried: exhaustive for(int i) x 10 loops x decl order of i/peers/slot (6144 variants, declsweep_vsinit.py): no gain;
cperm 22 min 80->59 (perm_best59.c, noise only); shared round/cup/mode, int item, (item = ...) != 0, cc at fn scope: no gain.

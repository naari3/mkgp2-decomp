clsound 19-TU merge, v2 (gaveup-retry, 2026-11-08 09:25Z)
Apply: git apply merge_v2.diff, then delete the 18 merged-away sources
(game/clsound/fn_801915DC.c .. fn_80192F04.c and game/SoundMgr_Play.c, list in sndfiles.txt).
State: main.dol FAILED only because fn_801913B0 is 99.46% (register swap r5/r6:
surround value vs &lbl_80678378[index]). Everything else in the unit is 100%,
including extab/extabindex (tools/extab_order.json key) and .data.
What fixed the rest:
- listener objects lbl_80495F20/F2C/F38 are `static` and the inline reads the three
  objects directly (section anchor r30 + 0x0/0xC/0x18); symbols.txt splits F20 into F20+F2C.
- far branch `volume=0; surround=pan=64;` (target `li r28,0x40; li r29,0; mr r5,r28`).
- callers of fn_801913B0 must call it as an EXTERNAL symbol: `#define fn_801913B0 fn_801913B0_extN`
  + `extern int fn_801913B0(int, void *)`, json renames _extN back. A cast macro gives an indirect
  call (mtctr/bctrl) and a direct call gets auto-inlined (auto_inline off did not help).
Tried for the last swap: decl orders, pragma push regions, unsigned char vars, voice pointer,
inverted branch, cperm 12 min. None.
- 10:30Z re-applied on fresh main (still 99.46, everything else 100%); tried decl perms, separate far-branch stores, reversed compares, a voice pointer, a non-inline body.

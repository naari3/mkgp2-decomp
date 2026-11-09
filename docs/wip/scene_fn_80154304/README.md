# fn_80154304 (CourseScene update) C++ draft, R5, 2026-11-08

Scene_8014E0C4.cpp here = main bebabda-era file + fn_80154304 as C++ (also has the ctor already). Its rodata.inc split (PairPos/lbl_80366E74/E88/ED8, lbl_80364BE0[7], lbl_80367590/9C strings) is in Scene_8014E0C4_rodata.inc.pre_kd (before RaceKartDescR became u8 enabled; re-apply that on top). extab_user_renames: add "__ct__7PairObjFPCci": "fn_8013D800".
Status: probe NOLBL DIFF 326 / 811 lines, ALL callee-saved register numbering (loop counters r25 in target vs r26/r27 mine; joint loop i r30; pair/cache loop regs; VObjPair ctor scheduling). Two cperm runs (25 min) found nothing.
Lesson from fn_80151F08 (landed bebabda): a separate block-local loop counter / indexing the static table (lbl_X[i].field instead of a walking pointer) fixed exactly this kind of swap. Try that on each loop here.
bebabda Scene_8014E0C4: fn_80151F08 (race scene ctor) asm -> C++
## 09:33Z update (R5): DIFF 326 -> 184
- fn_80154304.patch applies to main bebabda (cpp + rodata.inc + extab_user_renames.json).
- Joint loop fixed by declaring `void *jobj;` FIRST at function top (not block-local).
- VObjPair ctor: per-field copy `vel[k]=0; pos[k].x=..x; pos[k].y=..y` gives the target's direct anchor load; FPR scheduling left.
- Left: phase-address temp (r25 vs r26) near fn_8014E028 calls; pair loop p/k regs (p=r28,k=r30 target); hunk at ~750 (r26/r27).

## 11:05Z update (R1): DIFF 184 -> 30 lines (26 without the anchor reloc-name lines)
- fn_80154304_r1_on_f83c2f9.patch applies to main f83c2f9 (after fn_8014D88C/fn_8014E118 landed; rodata types PairPos/CourseCamKey kept, DemoPhase dropped).
- VObjPair ctor: copy the DemoCream ctor shape from fn_8014E118 (on/pos.x/pos.y/vel per k, aPos.x/.y from lbl_806D7F68[0]/[1], lbl_806D8064 not 0.0f) -> ctor block exact.
- Pair update moved into `inline void VObjPair::Tick()` (defined after the rodata include) -> phase-temp r25 and pair loop regs exact.
- Left: (1) `addi r30,r31,0xEB0` (event table ptr) scheduled before `lfs f31,0.0f` in ours, after in target; loop-shape variants did nothing. (2) sprite-cache purge loop: target spr r28 / node r31, ours r26 / r27 (block-local decls or a static inline helper: no gain / worse).

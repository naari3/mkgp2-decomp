# SetCourseParams: RaceData merge WIP (2026-11-07)

`racedata_merge.patch` applies against main at b00b0233 or later. It does three things:
- merges 7 TUs (RaceSys_8009B98C, RaceScene_GetPerspFovyForCup, RaceSys_8009BAC4, RankSlot_AppendOrUpdate, VSMode_SeedRandomItemSequence, RaceData_8009BEF4, SetCourseParams) into `game/RaceData.c`;
- compiles that TU as C++ (`-lang=c++`, everything in `extern "C"`, `-Cpp_exceptions on`);
- gives it the extab 0x80009598..95B0, extabindex 0x80022190..21B4, .text 0x8009B98C..0x8009CFDC, .data 0x80401118..0x8040DE94 and .bss 0x805AC600..0x805D2AA8.

What works:
- **.bss order:** pooled .bss needs definition order, and C++ gives it. C uses first-use order, and ItemUse_ResetAllKartUseSlots touches SetCourseParams_bss_805D2948 first, so C can never lay it out like the target. With C++, .bss/.data/extab are all 100%.
- **55 of the 56 functions at 100%.** Two changes were needed for that:
  - SetCourseParams_data_8040B90C has to be typed `CourseData[17][2]` (floats as literals). A void* array plus cast macros gives regalloc diffs in the accessors.
  - GetCoinSpawnTable needs `int cc = (g_ccClass == 2) ? 1 : 0;`, because a C++ bool gives extrwi.
- **SetCourseParams (122 diff lines, down from 357):**
  - `((int *)RaceSlot_ResetAll_bss_805D2938)[i] = 0` makes the stores alias, so g_cupId/g_longRoundFlag are reloaded as in the target.
  - The ranks are reset via `RankSlot *rk = SetCourseParams_bss_805D2948; ResetRankSlot(&rk[0..7])`.
  - The first loop is now `RaceSlot_ResetAll();`.

What is left:
- In the lap reset block, the target stores `lap[0].a = 0` before the `lfs` of 0.0f/1000.0f. Register numbering also differs: zero is r5, the rank base r7, the B256C base r4.
- Tried with no luck: an inline SetLap helper, a single 10-entry loop, swapping a/b, the lbl names, literals, and 15 min of cperm.

Do not land this while SetCourseParams is NonMatching: the 6 merged TUs are Matching on main today.

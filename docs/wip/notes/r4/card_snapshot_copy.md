# g_playerData -> lbl_80598A60.player snapshot copy (R4, 2026-11-07)

Shared by card_save_trigger, card_rw_state_machine(_short), card_read_state_machine,
card_force_backup_now (CardForceBackup.c 57%), CardSavedata_LoadShadow_TriggerUnused (94%),
RankLog_InitStartRace (68%). Asm-only: CardSave_Tick_CaptureAndStart.

Struct assignment `lbl_80598A60.player = g_playerData` (CardLoadShadowPrivate.h) gives the right
memberwise shape (packed words force memberwise + __copy for the two byte arrays).
Remaining problem = which address is kept in a nonvolatile reg + load grouping:
- target: lbl_80598A60 base kept in a nonvolatile reg (r31/r15) across both __copy calls,
  g_playerData base rematerialized (lis/addi) after each call; head fields 0..0xa4 one group
  (0x50,0x58..0xa4 spilled through stack), captured=1 stored inside that group.
- plain globals: grouping right, but dest base volatile + rematerialized (frame too small).
- dest via pointer / `*(T*)&lbl.player` cast / non-POD struct (ctor): dest kept in r31 but the
  head copy splits into two chunks (0..0x4c, 0x50..0xa4) when captured=1 is before the copy.
- dest via pointer with captured=1 AFTER the copy: grouped + spilled + dest kept, but spill set
  and src base reg (nonvolatile instead of r4) differ.
- GC/1.2.5n turns it into a block-copy loop (wrong); 1.3/2.x same as 1.3.2.
WIP TU: src/game/card_save_trigger.cpp (not committed; see card_save_trigger_wip.cpp here).

## 2026-11-07 17:30 R4 second pass (card_force_backup_now, 82.5% baseline from R1 d5ddcad)
Target detail: captured=1 is `li r29,1` + `stb r29,0x64(r31)` INSIDE the head group (before the
first __copy), src base in volatile r4, __copy arg setup (addi r3/r4, li r5) after the stores.
Mine (pointer-local, captured after): src base in r28, __copy args hoisted to top, captured via
spilled &lbl. Captured-before forms (pointer, whole-struct pointer, inline helpers, comma expr,
const src) all split the head copy into chunks 0..0x4c / 0x50..0xa4 (262-412 diff lines vs 248).
No change from GC 1.3/2.0/2.6/2.7, opt_common_subs/lifetimes/propagation/strength_reduction/
loop_invariants off, global_optimizer off, optimization_level 3. peephole off: 230 lines but
wrong shape. int-array / nested-struct layouts for 0x1C..0xA4: worse (array -> loop).
2x12 min cperm: nothing (only reorders card_backup).

# Permuter shard 3 thread (2026-11-07) — WIP
- Landed: 0195f28 (tobj_* 10 TUs merged into tobj_nm.c, +TObjInfoInit +HSD_TObjSetup), a962eac (docs/gave_up.md notes).
- No permuter matches in shard 3/4 (22 fns), round-2 shard 3/4 (4 fns), or the extra 15-min batch
  (PathManager_RegisterCarObject 68, ItemSelectState_Init 264, SpriteGroup_CreateOrInit 20, fn_80225124 49).
- BackupWriteRecord_best31_gc13.c: permuter best (score 31) with mw_version GC/1.3 (TU's only fn; current main 64).
- fn_80286864_best.c: permuter best (84 -> 56).
- Diagnoses for the rest are in docs/gave_up.md.

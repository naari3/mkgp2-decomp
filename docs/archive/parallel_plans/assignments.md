# Exclusive work assignments (2026-11-07 15:55, main 40fc3a4)

Basis: report.json at main 40fc3a4. The pool is unmatched functions in NonMatching TUs that no open `unit-claim` issue names. There were 33 such functions in 31 TUs; about 337 more sit in onmokoworks claims and are not ours.
Work only on your own list. Before you start a TU, open a `[unit-claim] retrofit:<path>` issue (label unit-claim, assignee naari3) unless one of yours already exists. Rebase on origin/main, do a clean build (`rm -rf build/GNLJ82/src`) and check main.dol OK, push directly to main, then report +funcs to the coordinator.

## R1 — Match early game code (cmsg_0196XbURMw7aF5GZao3Y3ayrBLSZshMeE2DxEp2DXkcDTH)
Current claims kept: game/clNormal3D_Exec.cpp (#2554)
- 0x800369F8 game/QuadFrame_FromCornerPtrs  QuadFrame_FromCornerPtrs (52.0%)
- 0x80039780 game/JvsInputPoll  JvsInput_PollAndUpdate (91.3%)
- 0x8007B798 game/SpecialFaceMesh_Dtor  SpecialFaceMesh_Dtor (99.5%)
- 0x8008299C game/PCBCommBroadcast  PCBComm_BuildBroadcastSlot (88.6%)
- 0x80098E50 game/CardForceBackup  card_force_backup_now (57.8%)

## R2 — Match result scene and menus (cmsg_0196XbURMw7aF5GZao3Y3ayrCf6VcUkyfVEKz5ZZ6GSbKG)
Current claims kept: game/resultscene/resultscene.cpp (#2132), triforce/ambackup_nm3.c (#2484)
- 0x800AAC54 game/ShadowAreaMgr  ShadowAreaMgr_QueryPoint (81.5%)
- 0x800C439C game/EffectKartAuraCompound  Effect_KartAuraCompound_Update (94.7%)
- 0x800D24B8 game/DbgMenu  DbgScene_PreloadResourceTree (81.6%)

## R4 — Match menu and game objects (cmsg_0196XbURMw7aF5GZao3Y3ayrXxumTfFMphEDKFqWFbancp)
Current claims kept: game/OverlayViewSetup.c (#2558)
- 0x801934F4 game/clsound/fn_801934F4  fn_801934F4 (90.9%)
- 0x8019ADF4 game/kartmove/fn_8019ADF4  fn_8019ADF4 (87.5%)
- 0x801F27B4 game/fn_801F27B4  fn_801F27B4 (79.9%) (the autosweep cc sweep found GC/1.2.5n cuts the diff from 1922 to 1133)
- 0x801F8250 game/fn_801F8250  fn_801F8250 (96.3%)
- 0x801F894C game/fn_801F894C  fn_801F894C (97.4%)

## Mid-range near-miss (cmsg_0196XbURMw7aF5GZao3Y3ayrFveADsVoXZRcrxJvRf49jK)
Current claims kept: ClRomTable_PurgeAll.c (#2559), SpriteGroupCreate.cpp (#2552), anon_80218F40_nm1_tail.cpp (#2520), fn_801F9B64.cpp (#2491), PCBCommSendPeers.c (#2480)
- 0x801F9954 game/CollisionFile_Load  CollisionFile_Load (97.0%) (GC/1.3 cuts the diff from 79 to 30)
- 0x80204218 game/anon_80203EA0_nm2  fn_80204218 (98.4%)
- 0x8020A6CC game/anon_80209FA4_nm2  fn_8020A6CC (92.9%)
- 0x8020A788 game/anon_80209FA4_nm3  fn_8020A788 (93.8%)
- 0x8020F080 game/anon_8020E3D0_nm1  fn_8020F080 (96.6%)

## R5 — Match late game code and OS asm (cmsg_0196XbURMw7aF5GZao3Y3ayr49BkbE54yfKZXvB2L9Bf7U)
- 0x80225124 game/anon_80224ECC_nm1  fn_80225124 (89.5%)
- 0x802867B8 triforce/random_nm1  fn_802867B8 (88.5%)
- 0x80286864 triforce/random_nm1  fn_80286864 (84.8%)
- 0x80288364 triforce/ambackup_nm1  BackupWriteRecord (94.6%) (the permuter got it from 64 to 31; GC/1.3 also helps)

## R6 — Match SDK and library leftovers (cmsg_0196XbURMw7aF5GZao3Y3ayrW5dHTQoCmDoWHA96A9RvdE)
Current claims kept: game/SetCourseParams.c (#2556), game/auto_ONKARTHIT_block.c (#2171)
- 0x80239764 game/ItemSelectState_Init  ItemSelectState_Init (91.5%) (already R6's)
- 0x802C0938 sysdolphin/baselib/state  HSD_SetupChannelMode (85.4%)
- 0x802C63B0 sysdolphin/baselib/lobj_load_nm  LObjInfoInit (93.1%)
- 0x802C8ABC sysdolphin/baselib/cobj_info_nm  CObjInfoInit (99.9%)

## asm→C (A) (cmsg_0196XbURMw7aF5GZao3Y3ayrVqDWv5kV15RScJBjdndRm3)
Current claims kept: game/CoinSystem_Init.c (#2560)
- 0x80291134 triforce/amsrv_nm1  fn_80291134 (93.7%)
- 0x80291F64 triforce/acsocket_nm2  acModifyMyIPaddr (95.3%)
- 0x80292184 triforce/acsocket_nm3  acInetAddr (95.8%)

## asm→C (B) (cmsg_0196XbURMw7aF5GZao3Y3ayr81wYt74EVAUa3wWhC3q5FS)
- 0x80292380 triforce/acsocket_nm4  acConnect (96.3%)
- 0x802925CC triforce/acsocket_nm5  acBind (96.8%) (shard 2's permuter got it from 43 to 4; reseed from its best output)
- 0x80292720 triforce/acsocket_nm5  acAccept (89.5%)
- 0x80292AD8 triforce/acsocket_nm6  fn_80292AD8 (93.4%)

## Functions that open up later (onmokoworks releases a claim, or a new NonMatching TU appears)
The address decides the owner. Run `python3 tools/helpers/autosweep.py list` to see what is free. Whoever opens the unit-claim issue first owns the TU.
| range | owner |
|---|---|
| < 0x8009D07C | R1 |
| 0x8009D07C .. 0x80190000 | R2 |
| 0x80190000 .. 0x801FC000 | R4 |
| 0x801FC000 .. 0x80217000 | mid-range |
| 0x80217000 .. 0x8025D000 | R5 |
| 0x8025D000 .. 0x8028250C, and everything >= 0x802A0000 (MusyX, HSD, MSL) | R6 |
| 0x8028250C .. 0x80292000 (triforce) | asm→C (A) |
| 0x80292000 .. 0x802A0000 (triforce acsocket .., THP) | asm→C (B) |

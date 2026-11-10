# Per-TU struct copies: census (tools/struct_dedup.py scan)

Regenerate with `python3 tools/struct_dedup.py scan`. How the tool decides: docs/notes/struct_dedup.md.

| Item | Count |
|---|---|
| Files scanned (src/game, src/ui, src/sound, src/util, src/resource, include/game) | 3104 |
| struct/union/class definitions at file scope | 6650 in 1567 files |
| Distinct type names | 5275 |
| Names defined in more than one file | 466 |
| Types already in `include/game/types` | 439 |
| Class A groups (same name, same members, 2+ files) | 80 groups, 211 definitions |
| ... of which movable right now | 30 groups, 82 definitions |
| Definitions whose byte layout the tool can compute | 4120 (not computable: 231) |
| Class B (same name, same layout, different member spelling) | 75 name/layout pairs, 163 spellings |
| Class C (same layout of 16+ bytes and 3+ fields, different names) | 174 layouts, 697 definitions |

## Why a definition is not movable yet

| Reason | Definitions |
|---|---|
| non-plain member (method, nested type, access label) | 1431 |
| needs another type (not shared yet) | 770 |
| has base class | 586 |
| has storage/qualifier prefix | 259 |
| class | 204 |
| needs another type (file has its own) | 121 |
| forward declaration in file | 44 |
| name defined twice in file | 37 |
| separate typedef in file | 32 |
| anonymous typedef in C++ (name mangling) | 31 |
| typedef without exactly one plain name | 21 |
| tag differs from typedef name | 13 |
| preprocessor in body | 10 |
| empty | 4 |
| typedef with extra declarators | 1 |
| variable definition | 1 |

## Most duplicated names

| Name | Definitions | Distinct member lists | Largest identical group | Movable now |
|---|---|---|---|---|
| HSD_JObj | 54 | 36 | 13 | 13 |
| Obj | 41 | 28 | 3 | 3 |
| ResCtrl | 30 | 2 | 1 | 1 |
| ScopedTimer | 30 | 0 | 0 | 0 |
| clNormal3D | 27 | 0 | 0 | 0 |
| Sprite | 21 | 5 | 1 | 1 |
| InputPlayer | 20 | 0 | 0 | 0 |
| __va_list_struct | 18 | 0 | 0 | 0 |
| GameModeBase | 16 | 1 | 2 | 0 |
| SndSlot | 16 | 10 | 4 | 1 |
| VObj | 15 | 0 | 0 | 0 |
| KartDriver | 15 | 13 | 2 | 2 |
| TextManager | 14 | 0 | 0 | 0 |
| PlayerData | 12 | 11 | 2 | 2 |
| ObjView | 12 | 10 | 2 | 2 |
| Vec | 12 | 1 | 3 | 0 |
| JObj | 11 | 8 | 2 | 2 |
| PtrVecBase | 11 | 0 | 0 | 0 |
| Scene3D | 10 | 2 | 1 | 1 |
| PtrVec | 10 | 0 | 0 | 0 |
| VfxSlot | 10 | 7 | 4 | 4 |
| InputState | 9 | 7 | 2 | 2 |
| CarObject | 9 | 1 | 1 | 0 |
| PtrVecData | 9 | 0 | 0 | 0 |
| FireFuncs | 9 | 1 | 9 | 0 |
| clDNBress | 9 | 0 | 0 | 0 |
| KartRender | 8 | 5 | 2 | 1 |
| GXChannel | 8 | 2 | 1 | 0 |
| Normal3D | 8 | 2 | 2 | 0 |
| SpriteSlot | 8 | 8 | 1 | 1 |
| WeatherSystem | 8 | 4 | 1 | 1 |
| Particle | 8 | 8 | 1 | 1 |
| Owner | 8 | 8 | 1 | 0 |
| Vec3 | 8 | 1 | 3 | 0 |
| ClStream | 8 | 6 | 2 | 2 |
| ListNode | 7 | 4 | 1 | 1 |
| PathCursor | 7 | 4 | 1 | 1 |
| SceneBase | 7 | 0 | 0 | 0 |
| KartAudioChannel | 7 | 6 | 1 | 1 |
| InputView | 7 | 4 | 3 | 3 |
| ItemObject | 7 | 7 | 1 | 1 |
| Kart | 7 | 7 | 1 | 1 |
| NokoNoko | 7 | 7 | 1 | 1 |
| CoinPopupDetail | 6 | 0 | 0 | 0 |
| FlowPanel | 6 | 2 | 1 | 1 |
| SpriteAnim | 6 | 2 | 3 | 3 |
| RaceScene | 6 | 5 | 1 | 1 |
| KartStatus | 6 | 4 | 2 | 2 |
| ItemKart | 6 | 5 | 1 | 1 |
| TexMgr | 6 | 3 | 1 | 1 |
| PcbSlot | 6 | 5 | 1 | 1 |
| SpriteObj | 6 | 1 | 1 | 1 |
| FlowController | 6 | 1 | 6 | 0 |
| Group | 6 | 2 | 1 | 1 |
| PathEntry | 5 | 4 | 2 | 1 |
| YesNoButtonL | 5 | 0 | 0 | 0 |
| ModeBase | 5 | 0 | 0 | 0 |
| JumpDistanceMode | 5 | 2 | 1 | 1 |
| LakituStart | 5 | 0 | 0 | 0 |
| SpriteBox | 5 | 1 | 1 | 1 |

## Class C: largest same-layout sets with different names (candidates only)

| Size | Fields | Definitions | Names |
|---|---|---|---|
| 0x278 | 12 | 32 | TestPage, TestPage_p1, TestPage_p10, TestPage_p11, TestPage_p12, TestPage_p13, TestPage_p14, TestPage_p15 ... |
| 0x40 | 16 | 23 | Anim5AMatrix, ArmMtx, BurnMtx, C7Matrix, ChildPairMatrix, Drift79Matrix, DriftMtx, FxMatrix ... |
| 0x10 | 4 | 17 | BootDescriptor, DrawFormatS56, GridSlot, HudSelectionStep, ItemCatEntry16, ItemDescriptor, ItemSpriteResource, JDCoins ... |
| 0x38 | 3 | 14 | BiribiriLightInfo, CoinHsdClassInfo, HSDClassInfo, HSDObjMethods, HsdClass, HsdClassInfo, RCLightInfo, RRLightInfo ... |
| 0x10 | 4 | 13 | CoinQuat, CoinSpark, CourseObjTrail, FaceRayBounds, ItemColor, ItemTransform162, MenuRect801F, Obj987Position ... |
| 0x18 | 6 | 13 | (anon), DemoEntry163, VtxDesc |
| 0x18 | 6 | 12 | CardBitpackState, CardPackedWords, CardPackedWords_p14, ItemRemapEntry, PackedWords, RankDispControls, RepairPackedWords_p16, ResultPackedWords ... |
| 0x10 | 4 | 12 | AssetRow, CardPointers, CourseObj8016AABC, HSD_DObj, ItemSelectSlotLabels, JointTable, ModelDesc, ObjView ... |
| 0x68 | 13 | 11 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p14, SpriteVoiceRaceEntry_p15, SpriteVoiceRaceEntry_p16, SpriteVoiceRaceEntry_p17, SpriteVoiceRaceEntry_p18, SpriteVoiceRaceEntry_p19, SpriteVoiceRaceEntry_p20 ... |
| 0x2C | 11 | 11 | CSAnimKey, CSPartsResultRank_rodata_80360C70_Row, ShowAnimCommand, lbl_80360FE0_Row, lbl_803610E8_Row, lbl_803611F0_Row, lbl_80361274_Row, lbl_80361400_Row ... |
| 0x20 | 3 | 10 | C8Input, CoinProgress, FKInput, FlowInputView, InputRec, InputState, InputView, RoundInfo ... |
| 0x18 | 6 | 9 | FloatSix, ItemPose, ParticleEmitter, RoundArrow, ShardAngles, SuspensionParam, TaBookend, TextureRect801F ... |
| 0x20 | 8 | 9 | ArchiveHeader, CarrotUvIdx, DebugTexObj, FlowAdvance1C, LapTable_p37, NamCamFdSet, RibbonUvIdx, RingOrder ... |
| 0x20 | 4 | 9 | Entry_806792D8, InputState, InputState_p14, InputState_p15, InputState_p17, PopupInputState |
| 0x1FC | 3 | 9 | CarrotKart, RaceVoiceDriver, RaceVoiceDriver_p11, RaceVoiceDriver_p13, RaceVoiceDriver_p34, RaceVoiceDriver_p47, RaceVoiceDriver_p50, RaceVoiceDriver_p52 ... |
| 0x2C | 11 | 9 | CSPartsResultStage_rodata_80361970_Row, lbl_80360D78_Row, lbl_80360DFC_Row, lbl_80360EAC_Row, lbl_80360F30_Row, lbl_803619F4_Row, lbl_80361A78_Row, lbl_803622CC_Row ... |
| 0x10 | 4 | 8 | CoinEntry, CoinSpawn, ItemBoxSpawnEntry, ParticleDirection, SpawnEntry, SpawnPoint, Trace162, TraceInput163 |
| 0x14 | 5 | 8 | RaceVoiceCourseLine, RaceVoiceCourseLine_p11, RaceVoiceCourseLine_p13, RaceVoiceCourseLine_p34, RaceVoiceCourseLine_p47, RaceVoiceCourseLine_p50, RaceVoiceCourseLine_p52, lbl_80499F98_Row |
| 0x20 | 8 | 8 | PaceKey, RCQuadPts, RankingPlacement, RingAngles, ScalarCurve4, Spark, TerrainWall, ViewBillboardParticle |
| 0x30 | 12 | 8 | BallProbes, DListQuad, DirTable, EffectJointMatrix, GoalLinePair, Mtx34, SpriteNodeInfo |
| 0x1DC | 62 | 7 | CardPlayerSnapshot, CardPlayerSnapshot_p14, PlayerData, RepairPlayerData_p16, ResultPlayerSnapshot, SetupPlayerSnapshot, ShadowPlayerSnapshot |
| 0x10 | 4 | 7 | Checkpoint163, CoinTrail, DebrisSpawn, PropKind, RYSub, RivalWaypoint, Waypoint |
| 0x1540 | 330 | 7 | RaceVoiceData, RaceVoiceData_p11, RaceVoiceData_p13, RaceVoiceData_p34, RaceVoiceData_p47, RaceVoiceData_p50, RaceVoiceData_p52 |
| 0x68 | 12 | 7 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p10, SpriteVoiceRaceEntry_p12, SpriteVoiceRaceEntry_p5, SpriteVoiceRaceEntry_p6, SpriteVoiceRaceEntry_p7, SpriteVoiceRaceEntry_p8 |
| 0x14 | 3 | 7 | Label, Obj, Pair, Sprite, SpriteObj_p10, SpriteObj_p9 |
| 0x1C | 7 | 6 | GPSpeedParams, GtItemPose, KartPose, ParamEntry, ParamValues, ScaleVec |
| 0x28 | 10 | 6 | CardCheckSettings, CardCheckSettings_p18, CardCheckSettings_p21, OSCalendarTime_p1, OSCalendarTime_p10, OSCalendarTime_p27 |
| 0x14 | 5 | 6 | CardUnlockRule, FKParams, FlowAdvance10, FrameStatBlock, Int5, ItemUnlockEntry |
| 0x14 | 5 | 6 | CardTaskManager, ItemDisplay, ModelEntry, RoundSlot, SceneWords |
| 0x48 | 18 | 6 | BurstPos, ObjParticle, Particle, PulseKey, ScaleKey |
| 0x118C | 327 | 6 | RaceVoiceTables, RaceVoiceTables_p14, RaceVoiceTables_p15, RaceVoiceTables_p16, RaceVoiceTables_p19, RaceVoiceTables_p9 |
| 0x68 | 14 | 6 | RaceVoiceEntry, RaceVoiceEntry_p11, RaceVoiceEntry_p13, RaceVoiceEntry_p34, RaceVoiceEntry_p50, RaceVoiceEntry_p52 |
| 0x2C | 10 | 6 | NMRaceWideRow, RaceEntry, RaceWideRow, RankSlot |
| 0x18 | 6 | 6 | KartSlot, NMKartSlot, RaceKartSlot, RaceSlot |
| 0x14 | 5 | 6 | TDrawVecBlk, rodata_8036DD8C_rodata_8036DD8C_Row, rodata_8036DD8C_rodata_8036DE2C_Row, rodata_8036DD8C_rodata_8036DE90_Row, rodata_8036DD8C_rodata_8036DEE0_Row, rodata_8036DD8C_rodata_8036DF30_Row |
| 0x10 | 4 | 5 | AISpeedOwner, Entry, GrowSet, JointSetDesc, Obj987Entry |
| 0x308 | 5 | 5 | BurnKart, Kart, KartRender |
| 0x14 | 5 | 5 | NokoKind, lbl_8037754C_Row, lbl_80377588_Row, lbl_803775C4_Row |
| 0x38 | 14 | 4 | BtModeView, RefVtable162, VSOwner, VsScene |
| 0x3C | 4 | 4 | CollisionDVDFileInfo, DVDFileInfo |

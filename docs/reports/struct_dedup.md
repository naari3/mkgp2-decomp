# Per-TU struct copies: census (tools/struct_dedup.py scan)

Regenerate with `python3 tools/struct_dedup.py scan`. How the tool decides: docs/notes/struct_dedup.md.

| Item | Count |
|---|---|
| Files scanned (src/game, src/ui, src/sound, src/util, src/resource, include/game) | 2840 |
| struct/union/class definitions at file scope | 5980 in 1558 files |
| Distinct type names | 4201 |
| Names defined in more than one file | 581 |
| Types already in `include/game/types` | 201 |
| Class A groups (same name, same members, 2+ files) | 85 groups, 223 definitions |
| ... of which movable right now | 27 groups, 65 definitions |
| Definitions whose byte layout the tool can compute | 2956 (not computable: 239) |
| Class B (same name, same layout, different member spelling) | 65 name/layout pairs, 145 spellings |
| Class C (same layout of 16+ bytes and 3+ fields, different names) | 170 layouts, 683 definitions |

## Why a definition is not movable yet

| Reason | Definitions |
|---|---|
| non-plain member (method, nested type, access label) | 1754 |
| needs another type (not shared yet) | 909 |
| has base class | 700 |
| has storage/qualifier prefix | 259 |
| class | 253 |
| needs another type (file has its own) | 90 |
| forward declaration in file | 43 |
| name defined twice in file | 37 |
| separate typedef in file | 32 |
| anonymous typedef in C++ (name mangling) | 29 |
| typedef without exactly one plain name | 21 |
| tag differs from typedef name | 13 |
| preprocessor in body | 10 |
| empty | 4 |
| typedef with extra declarators | 1 |
| variable definition | 1 |

## Most duplicated names

| Name | Definitions | Distinct member lists | Largest identical group | Movable now |
|---|---|---|---|---|
| HSD_JObj | 54 | 36 | 13 | 3 |
| clNormal3D | 44 | 0 | 0 | 0 |
| Obj | 41 | 28 | 3 | 3 |
| InputPlayer | 33 | 0 | 0 | 0 |
| ResCtrl | 33 | 2 | 1 | 1 |
| ScopedTimer | 33 | 0 | 0 | 0 |
| VObj | 27 | 0 | 0 | 0 |
| GXChannel | 26 | 2 | 1 | 0 |
| Sprite | 23 | 5 | 1 | 1 |
| GameModeBase | 23 | 1 | 2 | 0 |
| clMapEffectParts | 21 | 0 | 0 | 0 |
| TextManager | 20 | 0 | 0 | 0 |
| __va_list_struct | 18 | 0 | 0 | 0 |
| SndSlot | 16 | 10 | 4 | 1 |
| SceneBase | 15 | 0 | 0 | 0 |
| KartDriver | 15 | 13 | 2 | 2 |
| Scene3D | 14 | 2 | 1 | 1 |
| PlayerData | 12 | 11 | 2 | 2 |
| ObjView | 12 | 10 | 2 | 2 |
| Vec | 12 | 1 | 3 | 0 |
| CarObject | 12 | 1 | 1 | 0 |
| WeatherSystem | 12 | 4 | 1 | 1 |
| JObj | 11 | 8 | 2 | 2 |
| Normal3D | 11 | 2 | 2 | 0 |
| PtrVecBase | 11 | 0 | 0 | 0 |
| SpriteSlot | 10 | 9 | 2 | 2 |
| PtrVec | 10 | 0 | 0 | 0 |
| VfxSlot | 10 | 7 | 4 | 4 |
| InputState | 9 | 7 | 2 | 2 |
| LakituStart | 9 | 0 | 0 | 0 |
| TextSprite | 9 | 0 | 0 | 0 |
| PtrVecData | 9 | 0 | 0 | 0 |
| AnimCtrl | 9 | 0 | 0 | 0 |
| FireFuncs | 9 | 1 | 9 | 0 |
| clDNBress | 9 | 0 | 0 | 0 |
| ItemMsgWnd | 8 | 0 | 0 | 0 |
| KartRender | 8 | 5 | 2 | 1 |
| ModeBase | 8 | 0 | 0 | 0 |
| Particle | 8 | 8 | 1 | 1 |
| Owner | 8 | 8 | 1 | 0 |
| Vec3 | 8 | 1 | 3 | 0 |
| ChallengeGoalCamera | 8 | 2 | 1 | 0 |
| TexMgr | 8 | 3 | 1 | 1 |
| SpriteObj | 8 | 1 | 1 | 1 |
| Tween | 8 | 0 | 0 | 0 |
| FadeKeyBase | 8 | 0 | 0 | 0 |
| FadeKey | 8 | 0 | 0 | 0 |
| FadeSeq | 8 | 0 | 0 | 0 |
| FlowBase | 8 | 0 | 0 | 0 |
| ClStream | 8 | 6 | 2 | 2 |
| ListNode | 7 | 4 | 1 | 1 |
| PathCursor | 7 | 4 | 1 | 1 |
| KartAudioChannel | 7 | 6 | 1 | 1 |
| HUD | 7 | 1 | 1 | 1 |
| Camera | 7 | 3 | 1 | 1 |
| InputView | 7 | 4 | 3 | 3 |
| ItemObject | 7 | 7 | 1 | 1 |
| Kart | 7 | 7 | 1 | 1 |
| NokoNoko | 7 | 7 | 1 | 1 |
| FlowSceneHost | 6 | 0 | 0 | 0 |

## Class C: largest same-layout sets with different names (candidates only)

| Size | Fields | Definitions | Names |
|---|---|---|---|
| 0x278 | 12 | 32 | TestPage, TestPage_p1, TestPage_p10, TestPage_p11, TestPage_p12, TestPage_p13, TestPage_p14, TestPage_p15 ... |
| 0x40 | 16 | 25 | Anim5AMatrix, ArmMtx, BurnMtx, C7Matrix, ChildPairMatrix, Drift79Matrix, DriftMtx, FxMatrix ... |
| 0x10 | 4 | 21 | BootDescriptor, DrawFormatS56, Entry10, GridSlot, HudSelectionStep, ItemCatEntry16, ItemDescriptor, ItemList ... |
| 0x10 | 4 | 15 | CoinQuat, CoinSpark, CourseObjTrail, FaceRayBounds, ItemColor, ItemTransform162, MenuRect801F, Obj987Position ... |
| 0x38 | 3 | 14 | BiribiriLightInfo, CoinHsdClassInfo, HSDClassInfo, HSDObjMethods, HsdClass, HsdClassInfo, RCLightInfo, RRLightInfo ... |
| 0x18 | 6 | 13 | (anon), DemoEntry163, VtxDesc |
| 0x18 | 6 | 12 | CardBitpackState, CardPackedWords, CardPackedWords_p14, ItemRemapEntry, PackedWords, RankDispControls, RepairPackedWords_p16, ResultPackedWords ... |
| 0x18 | 6 | 12 | ChargePlacement, CupSide, FloatSix, ItemPose, ParticleEmitter, RayColors, RoundArrow, ShardAngles ... |
| 0x10 | 4 | 12 | AssetRow, CardPointers, CourseObj8016AABC, HSD_DObj, ItemSelectSlotLabels, JointTable, ModelDesc, ObjView ... |
| 0x68 | 13 | 11 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p14, SpriteVoiceRaceEntry_p15, SpriteVoiceRaceEntry_p16, SpriteVoiceRaceEntry_p17, SpriteVoiceRaceEntry_p18, SpriteVoiceRaceEntry_p19, SpriteVoiceRaceEntry_p20 ... |
| 0x20 | 3 | 10 | C8Input, CoinProgress, FKInput, FlowInputView, InputRec, InputState, InputView, RoundInfo ... |
| 0x20 | 8 | 10 | ChainScaleKey, PaceKey, RCQuadPts, RCQuadPtsC, RankingPlacement, RingAngles, ScalarCurve4, Spark ... |
| 0x20 | 8 | 9 | ArchiveHeader, CarrotUvIdx, DebugTexObj, FlowAdvance1C, LapTable_p37, NamCamFdSet, RibbonUvIdx, RingOrder ... |
| 0x20 | 4 | 9 | Entry_806792D8, InputState, InputState_p14, InputState_p15, InputState_p17, PopupInputState |
| 0x10 | 4 | 9 | CoinEntry, CoinSpawn, ItemBoxSpawnEntry, ParticleDirection, SpawnEntry, SpawnPoint, SpawnRow, Trace162 ... |
| 0x1FC | 3 | 9 | CarrotKart, RaceVoiceDriver, RaceVoiceDriver_p11, RaceVoiceDriver_p13, RaceVoiceDriver_p34, RaceVoiceDriver_p47, RaceVoiceDriver_p50, RaceVoiceDriver_p52 ... |
| 0x24 | 9 | 9 | CamVecs, ClSoundListener, DustCurve, HornBlastCurve, MarkerPath, PCPathSeg, Path, SparkOffsets ... |
| 0x10 | 4 | 8 | Checkpoint163, CoinTrail, DebrisSpawn, PropKind, RYSub, RivalWaypoint, ScrollEntry, Waypoint |
| 0x30 | 12 | 8 | BallProbes, DListQuad, DirTable, EffectJointMatrix, GoalLinePair, Mtx34, Quad, SpriteNodeInfo |
| 0x28 | 10 | 7 | CardCheckSettings, CardCheckSettings_p18, CardCheckSettings_p21, DigitMap, OSCalendarTime_p1, OSCalendarTime_p10, OSCalendarTime_p27 |
| 0x1DC | 62 | 7 | CardPlayerSnapshot, CardPlayerSnapshot_p14, PlayerData, RepairPlayerData_p16, ResultPlayerSnapshot, SetupPlayerSnapshot, ShadowPlayerSnapshot |
| 0x1540 | 330 | 7 | RaceVoiceData, RaceVoiceData_p11, RaceVoiceData_p13, RaceVoiceData_p34, RaceVoiceData_p47, RaceVoiceData_p50, RaceVoiceData_p52 |
| 0x14 | 5 | 7 | RaceVoiceCourseLine, RaceVoiceCourseLine_p11, RaceVoiceCourseLine_p13, RaceVoiceCourseLine_p34, RaceVoiceCourseLine_p47, RaceVoiceCourseLine_p50, RaceVoiceCourseLine_p52 |
| 0x68 | 12 | 7 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p10, SpriteVoiceRaceEntry_p12, SpriteVoiceRaceEntry_p5, SpriteVoiceRaceEntry_p6, SpriteVoiceRaceEntry_p7, SpriteVoiceRaceEntry_p8 |
| 0x14 | 3 | 7 | Label, Obj, Pair, Sprite, SpriteObj_p10, SpriteObj_p9 |
| 0x1C | 7 | 6 | GPSpeedParams, GtItemPose, KartPose, ParamEntry, ParamValues, ScaleVec |
| 0x14 | 5 | 6 | CardUnlockRule, FKParams, FlowAdvance10, FrameStatBlock, Int5, ItemUnlockEntry |
| 0x14 | 5 | 6 | CardTaskManager, ItemDisplay, ModelEntry, RoundSlot, SceneWords |
| 0x118C | 327 | 6 | RaceVoiceTables, RaceVoiceTables_p14, RaceVoiceTables_p15, RaceVoiceTables_p16, RaceVoiceTables_p19, RaceVoiceTables_p9 |
| 0x68 | 14 | 6 | RaceVoiceEntry, RaceVoiceEntry_p11, RaceVoiceEntry_p13, RaceVoiceEntry_p34, RaceVoiceEntry_p50, RaceVoiceEntry_p52 |
| 0x10 | 4 | 5 | AISpeedOwner, Entry, GrowSet, JointSetDesc, Obj987Entry |
| 0x48 | 18 | 5 | BurstPos, ObjParticle, Particle, PulseKey, ScaleKey |
| 0x308 | 5 | 5 | BurnKart, Kart, KartRender |
| 0x2C | 10 | 5 | RaceEntry, RaceWideRow, RankSlot |
| 0x18 | 6 | 5 | KartSlot, RaceKartSlot, RaceSlot |
| 0x38 | 14 | 4 | BtModeView, RefVtable162, VSOwner, VsScene |
| 0x3C | 4 | 4 | CollisionDVDFileInfo, DVDFileInfo |
| 0x14 | 5 | 4 | DrawSlot, RaceScriptEntry, RoundTileSlot, TDrawSlot |
| 0x1C | 4 | 4 | DampArmSlot, PlaceE4Group, SprayInitGroup, WheelWork |
| 0x14 | 4 | 4 | FlowDispatcher, JObjLinkView, JObjView, SparkJoint |

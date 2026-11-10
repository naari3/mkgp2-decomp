# Per-TU struct copies: census (tools/struct_dedup.py scan)

Regenerate with `python3 tools/struct_dedup.py scan`. How the tool decides: docs/notes/struct_dedup.md.

| Item | Count |
|---|---|
| Files scanned (src/game, src/ui, src/sound, src/util, src/resource, include/game) | 2840 |
| struct/union/class definitions at file scope | 6921 in 1813 files |
| Distinct type names | 4329 |
| Names defined in more than one file | 731 |
| Types already in `include/game/types` | 6 |
| Class A groups (same name, same members, 2+ files) | 283 groups, 1153 definitions |
| ... of which movable right now | 179 groups, 848 definitions |
| Definitions whose byte layout the tool can compute | 3879 (not computable: 245) |
| Class B (same name, same layout, different member spelling) | 81 name/layout pairs, 180 spellings |
| Class C (same layout of 16+ bytes and 3+ fields, different names) | 178 layouts, 804 definitions |

## Why a definition is not movable yet

| Reason | Definitions |
|---|---|
| non-plain member (method, nested type, access label) | 1754 |
| needs another type (not shared yet) | 1095 |
| has base class | 705 |
| class | 260 |
| has storage/qualifier prefix | 259 |
| needs another type (file has its own) | 218 |
| forward declaration in file | 45 |
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
| Vec3 | 179 | 1 | 174 | 171 |
| Vec | 101 | 1 | 92 | 89 |
| Vec3f | 59 | 1 | 58 | 58 |
| HSD_JObj | 58 | 37 | 13 | 4 |
| Obj | 45 | 29 | 4 | 4 |
| clNormal3D | 44 | 0 | 0 | 0 |
| InputPlayer | 33 | 0 | 0 | 0 |
| ResCtrl | 33 | 2 | 1 | 1 |
| ScopedTimer | 33 | 0 | 0 | 0 |
| VObj | 27 | 0 | 0 | 0 |
| GXChannel | 26 | 2 | 1 | 0 |
| SpriteAnim | 25 | 3 | 19 | 0 |
| SpriteAnimData | 24 | 2 | 23 | 23 |
| Sprite | 23 | 5 | 1 | 1 |
| GameModeBase | 23 | 1 | 2 | 0 |
| KartDriver | 22 | 14 | 7 | 7 |
| clMapEffectParts | 21 | 0 | 0 | 0 |
| TextManager | 21 | 0 | 0 | 0 |
| __va_list_struct | 18 | 0 | 0 | 0 |
| KartRender | 17 | 6 | 9 | 9 |
| Particle | 17 | 9 | 9 | 1 |
| InputView | 16 | 5 | 9 | 9 |
| SndSlot | 16 | 10 | 4 | 1 |
| SceneBase | 15 | 0 | 0 | 0 |
| ObjView | 15 | 11 | 3 | 3 |
| SpriteSlot | 15 | 10 | 5 | 5 |
| GXColor | 15 | 3 | 10 | 10 |
| PlayerData | 14 | 12 | 2 | 2 |
| Scene3D | 14 | 2 | 1 | 1 |
| VfxSlot | 14 | 8 | 4 | 4 |
| InputState | 13 | 8 | 4 | 4 |
| JObj | 13 | 9 | 2 | 2 |
| Buf256 | 13 | 2 | 9 | 9 |
| CarObject | 12 | 1 | 1 | 0 |
| WeatherSystem | 12 | 4 | 1 | 1 |
| ListNode | 11 | 5 | 4 | 4 |
| Normal3D | 11 | 2 | 2 | 0 |
| PtrVecBase | 11 | 0 | 0 | 0 |
| WGPipe | 10 | 2 | 7 | 7 |
| Vec2 | 10 | 1 | 9 | 9 |
| PtrVec | 10 | 0 | 0 | 0 |
| KartCond | 10 | 1 | 10 | 10 |
| ClStream | 10 | 7 | 2 | 2 |
| LakituStart | 9 | 0 | 0 | 0 |
| TextSprite | 9 | 0 | 0 | 0 |
| PtrVecData | 9 | 0 | 0 | 0 |
| DVDFileInfo | 9 | 5 | 4 | 4 |
| AnimCtrl | 9 | 0 | 0 | 0 |
| FireFuncs | 9 | 1 | 9 | 0 |
| clDNBress | 9 | 0 | 0 | 0 |
| Node | 9 | 3 | 5 | 5 |
| ItemMsgWnd | 8 | 0 | 0 | 0 |
| ListIter | 8 | 1 | 4 | 0 |
| ModeBase | 8 | 0 | 0 | 0 |
| Owner | 8 | 8 | 1 | 0 |
| KartStatus | 8 | 5 | 2 | 2 |
| ItemKartFlag | 8 | 1 | 8 | 8 |
| ItemKart | 8 | 6 | 2 | 0 |
| ChallengeGoalCamera | 8 | 2 | 1 | 0 |
| TexMgr | 8 | 3 | 1 | 1 |

## Class C: largest same-layout sets with different names (candidates only)

| Size | Fields | Definitions | Names |
|---|---|---|---|
| 0x278 | 12 | 32 | TestPage, TestPage_p1, TestPage_p10, TestPage_p11, TestPage_p12, TestPage_p13, TestPage_p14, TestPage_p15 ... |
| 0x40 | 16 | 30 | Anim5AMatrix, ArmMtx, BurnMtx, C7Matrix, ChildPairMatrix, Drift79Matrix, DriftMtx, FxMatrix ... |
| 0x10 | 4 | 26 | BootDescriptor, DrawFormatS56, Entry10, GlyphInfo, GridSlot, HudSelectionStep, Int4, ItemCatEntry16 ... |
| 0x10 | 4 | 25 | BoxShadow, CoinQuat, CoinSpark, CourseObjTrail, FaceRayBounds, ItemColor, ItemTransform162, MenuRect801F ... |
| 0x20 | 3 | 21 | C8Input, CoinProgress, FKInput, FlowInputView, InputRec, InputState, InputView, RaceResult ... |
| 0x18 | 6 | 16 | ChargePlacement, CupSide, FloatSix, ItemPose, ModelParam, ParticleEmitter, RayColors, RoundArrow ... |
| 0x10 | 4 | 15 | AnimRow, AssetRow, CardPointers, CourseObj8016AABC, HSD_DObj, ItemSelectSlotLabels, JointTable, ModelDesc ... |
| 0x38 | 3 | 14 | BiribiriLightInfo, CoinHsdClassInfo, HSDClassInfo, HSDObjMethods, HsdClass, HsdClassInfo, RCLightInfo, RRLightInfo ... |
| 0x20 | 4 | 13 | Entry_806792D8, InputState, InputState_p14, InputState_p15, InputState_p17, PopupInputState |
| 0x18 | 6 | 13 | (anon), DemoEntry163, VtxDesc |
| 0x18 | 6 | 12 | CardBitpackState, CardPackedWords, CardPackedWords_p14, ItemRemapEntry, PackedWords, RankDispControls, RepairPackedWords_p16, ResultPackedWords ... |
| 0x20 | 8 | 12 | ArchiveHeader, CarrotUvIdx, DebugTexObj, FlowAdvance1C, GXTexObj, LapTable_p37, NamCamFdSet, RibbonUvIdx ... |
| 0x10 | 4 | 12 | Checkpoint163, CoinTrail, DebrisSpawn, PropKind, RYSub, RivalWaypoint, ScrollEntry, Trail ... |
| 0x28 | 10 | 11 | CardCheckSettings, CardCheckSettings_p18, CardCheckSettings_p21, DigitMap, OSCalendarTime, OSCalendarTime_p1, OSCalendarTime_p10, OSCalendarTime_p27 |
| 0x10 | 4 | 11 | CoinEntry, CoinSpawn, ItemBoxSpawnEntry, ParticleDirection, Spark, SpawnEntry, SpawnPoint, SpawnRow ... |
| 0x68 | 13 | 11 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p14, SpriteVoiceRaceEntry_p15, SpriteVoiceRaceEntry_p16, SpriteVoiceRaceEntry_p17, SpriteVoiceRaceEntry_p18, SpriteVoiceRaceEntry_p19, SpriteVoiceRaceEntry_p20 ... |
| 0x1FC | 3 | 11 | CarrotKart, KartVariant, RaceVoiceDriver, RaceVoiceDriver_p11, RaceVoiceDriver_p13, RaceVoiceDriver_p34, RaceVoiceDriver_p47, RaceVoiceDriver_p50 ... |
| 0x8C | 4 | 11 | BoostCamera, BurnCamera, Camera, CameraView, CoinJumpCamera, RingCameraView, YawPitchCamera |
| 0x20 | 8 | 10 | ChainScaleKey, PaceKey, RCQuadPts, RCQuadPtsC, RankingPlacement, RingAngles, ScalarCurve4, Spark ... |
| 0x1C | 7 | 9 | GPSpeedParams, GtItemPose, KartPose, ParamEntry, ParamValues, ScaleVec, ShowXform |
| 0x24 | 9 | 9 | CamVecs, ClSoundListener, DustCurve, HornBlastCurve, MarkerPath, PCPathSeg, Path, SparkOffsets ... |
| 0x14 | 5 | 8 | CardUnlockRule, FKParams, FlowAdvance10, FrameStatBlock, Int5, ItemUnlockEntry, UnlockGrant |
| 0x30 | 12 | 8 | BallProbes, DListQuad, DirTable, EffectJointMatrix, GoalLinePair, Mtx34, Quad, SpriteNodeInfo |
| 0x1DC | 62 | 7 | CardPlayerSnapshot, CardPlayerSnapshot_p14, PlayerData, RepairPlayerData_p16, ResultPlayerSnapshot, SetupPlayerSnapshot, ShadowPlayerSnapshot |
| 0x28 | 10 | 7 | CoinInputView, CourseInputImpl, CourseInputImpl_p17, InputImpl |
| 0x1540 | 330 | 7 | RaceVoiceData, RaceVoiceData_p11, RaceVoiceData_p13, RaceVoiceData_p34, RaceVoiceData_p47, RaceVoiceData_p50, RaceVoiceData_p52 |
| 0x14 | 5 | 7 | RaceVoiceCourseLine, RaceVoiceCourseLine_p11, RaceVoiceCourseLine_p13, RaceVoiceCourseLine_p34, RaceVoiceCourseLine_p47, RaceVoiceCourseLine_p50, RaceVoiceCourseLine_p52 |
| 0x68 | 12 | 7 | SpriteVoiceRaceEntry, SpriteVoiceRaceEntry_p10, SpriteVoiceRaceEntry_p12, SpriteVoiceRaceEntry_p5, SpriteVoiceRaceEntry_p6, SpriteVoiceRaceEntry_p7, SpriteVoiceRaceEntry_p8 |
| 0x14 | 3 | 7 | Label, Obj, Pair, Sprite, SpriteObj_p10, SpriteObj_p9 |
| 0x10 | 4 | 7 | BitpackEntry, CardTaskManager, Countdown |
| 0x14 | 5 | 6 | CardTaskManager, ItemDisplay, ModelEntry, RoundSlot, SceneWords |
| 0x28 | 10 | 6 | CourseSprKey, FlameCurve, JointTransform, KoopaFlame, ScaleKey |
| 0x118C | 327 | 6 | RaceVoiceTables, RaceVoiceTables_p14, RaceVoiceTables_p15, RaceVoiceTables_p16, RaceVoiceTables_p19, RaceVoiceTables_p9 |
| 0x68 | 14 | 6 | RaceVoiceEntry, RaceVoiceEntry_p11, RaceVoiceEntry_p13, RaceVoiceEntry_p34, RaceVoiceEntry_p50, RaceVoiceEntry_p52 |
| 0x14 | 5 | 6 | CoursePropData, PropData, SlotDesc, TransitionTextureVertex |
| 0x10 | 4 | 5 | AISpeedOwner, Entry, GrowSet, JointSetDesc, Obj987Entry |
| 0x10 | 4 | 5 | NameCharacterSets, SceneItem, TerrainCell |
| 0x48 | 18 | 5 | BurstPos, ObjParticle, Particle, PulseKey, ScaleKey |
| 0x308 | 5 | 5 | BurnKart, Kart, KartRender |
| 0x2C | 10 | 5 | RaceEntry, RaceWideRow, RankSlot |


/* sdata symbols referenced from asm */
extern char lbl_806D7174[7];
extern char lbl_806D717C[5];
/*
 * 0x8012BF5C..0x801313D0: coin game, boss Koopa, shells and coin particles.
 */
#pragma cplusplus on

#include "game/singleton.h"

struct CoinVObj {
    virtual ~CoinVObj();
    virtual unsigned char Begin();
    virtual void Draw();
};

class GXChannel {
public:
    GXChannel(void *jobj, void *dobj, int flags, int bind);
    ~GXChannel();
    unsigned char data[0x14];
};

extern "C" {
extern void *Archive_GetRootJObj(void *);
extern void CObj_DebugVizPathFlush(void *);
extern float (*CObj_GetProjMatrix_Cached(void *))[4];
extern void CourseEnvironment_RenderObjects_Timed(void *);
extern void DrawEffect_TickAndCull(void);
extern void GXChannel_PushTransform(GXChannel *, float (*)[4]);
extern void *GetCourseScene3D(void);
extern void *HSD_JObjGetDObj(void *);
extern void ItemObjectManager_Render(void);
extern void KartItem_DispatchEffectRenderByState(void *);
extern void KartItem_FlushPendingRender_v2(void *);
extern void Object_DriveAnimMatrix(void *);
extern void Object_RenderJObjIfWithinRange(void *);
extern void Object_RenderJObjTree(void *, int);
extern void Object_SetAnimBinding(void *, void *, int);
extern void Object_SetColorAlphaOnly(void *, int, float);
extern void PSMTXConcat(float (*)[4], float (*)[4], float (*)[4]);
extern void PSMTXRotRad(float (*)[4], char, float);
extern void PSMTXScale(float (*)[4], float, float, float);
extern void Subsystem36c_DispatchPass2_Timed(void *);
extern void Subsystem36c_DispatchPass4_Timed(void *);
extern void TransitionEffect_RenderPass(CoinVObj *, int);
extern void TransparentDraw_SortAndDispatch(void);
extern void clDrawMan_Buckets_Dispatch(CoinVObj *);
extern void clDrawMan_Buckets_Reset(CoinVObj *);
extern void clDrawMan_EndFrame_NoOp(CoinVObj *);
extern void fn_8012A61C(void *);
extern void fn_8016B0C4(void);
extern void fn_8016DA30(void *);
extern void fn_8016EACC(void *);
extern void fn_8017218C(void *);
extern float CGameCoin_8012BF5C_data_806CF58C;
extern float CGameCoin_8012BF5C_data_806CF590;
extern float CGameCoin_8012BF5C_data_806CF594;
extern float CGameCoin_8012BF5C_data_806CF598;
extern CoinVObj *lbl_806D109C;
extern CoinVObj *lbl_806D10AC;
extern unsigned int lbl_806D7138;
extern const float lbl_806D7140;
extern const float lbl_806D7150;
extern unsigned int lbl_806D7154;
extern unsigned int lbl_806D7158;
extern void HSD_StateInvalidate(int);
extern void fn_80253448(void *, unsigned int);
extern void fn_802535D4(void *);
extern const unsigned int lbl_806DC1B8;
#ifdef NON_MATCHING
extern void CObj_ApplyScissor(void *, void *);
#else
extern void CObj_ApplyScissor();
#endif
#ifdef NON_MATCHING
extern void CObj_ApplyViewport(void *, void *);
#else
extern void CObj_ApplyViewport();
#endif
#ifdef NON_MATCHING
extern void CObj_LoadIntoGX(void *, void *);
#else
extern void CObj_LoadIntoGX();
#endif
#ifdef NON_MATCHING
extern void CObj_LoadProjMatrix(void *, void *);
#else
extern void CObj_LoadProjMatrix();
#endif
#ifdef NON_MATCHING
extern void ChallengeGoalCamera_Update(void *, void *, float (*)[4]);
#else
extern void ChallengeGoalCamera_Update();
#endif
#ifdef NON_MATCHING
extern float Cosf_LUT_Wrap(float);
#else
extern void Cosf_LUT_Wrap();
#endif
#ifdef NON_MATCHING
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *);
#else
extern void CourseEnvironment_UpdateAndCullZones_Timed();
#endif
#ifdef NON_MATCHING
extern void DebugPrintf(const char *, ...);
#else
extern void DebugPrintf();
#endif
#ifdef NON_MATCHING
extern void Fog_UpdateFromCourseScene3D(void);
#else
extern void Fog_UpdateFromCourseScene3D();
#endif
int GetDisplayBufferIndex(void);
extern void *GetInputManager(void);
extern void *GetRaceContextPtr(void);
extern void HSD_JObjSetMtxDirtySub(struct CoinJObj *);
extern void HSD_JObjSetupMatrixSub(struct CoinJObj *);
#ifdef NON_MATCHING
extern void HUD_FrameUpdate(void *);
#else
extern void HUD_FrameUpdate();
#endif
#ifdef NON_MATCHING
extern unsigned char InputCmd_GetDetectedFlag(void *);
#else
extern void InputCmd_GetDetectedFlag();
#endif
#ifdef NON_MATCHING
extern void InputCmd_PushSample(void *, int, float, float, float);
#else
extern void InputCmd_PushSample();
#endif
#ifdef NON_MATCHING
extern void InputCmd_TickAndDetectAndClear(void *);
#else
extern void InputCmd_TickAndDetectAndClear();
#endif
extern struct CoinInputPlayer *InputMgr_GetPlayer(void *, int);
#ifdef NON_MATCHING
extern unsigned char Input_IsItemButtonPressed(unsigned int);
#else
extern void Input_IsItemButtonPressed();
#endif
#ifdef NON_MATCHING
extern unsigned char IsCardValid(void);
#else
extern void IsCardValid();
#endif
extern unsigned char IsRaceStarted(void);
#ifdef NON_MATCHING
extern void ItemEffectBus_ApplyItemEventClear(void *, int);
#else
extern void ItemEffectBus_ApplyItemEventClear();
#endif
#ifdef NON_MATCHING
extern void ItemEffectBus_ApplyItemEventSet(void *, int, int);
#else
extern void ItemEffectBus_ApplyItemEventSet();
#endif
#ifdef NON_MATCHING
extern void ItemEffectBus_SnapshotAndFullReset(void *);
#else
extern void ItemEffectBus_SnapshotAndFullReset();
#endif
#ifdef NON_MATCHING
extern void ItemEffectBus_TickTornadoCooldown(void *);
#else
extern void ItemEffectBus_TickTornadoCooldown();
#endif
#ifdef NON_MATCHING
extern void ItemObjectManager_PerFrameUpdate(void *);
#else
extern void ItemObjectManager_PerFrameUpdate();
#endif
#ifdef NON_MATCHING
extern void ItemObjectManager_Update(void);
#else
extern void ItemObjectManager_Update();
#endif
extern float LUT_Sin12Bit(float);
#ifdef NON_MATCHING
extern void LakituStart_UpdateCountdown(void *);
#else
extern void LakituStart_UpdateCountdown();
#endif
#ifdef NON_MATCHING
extern void *NokoNokoChallenge_CalcResultText(struct CGameCoin *, int, int);
#else
extern void NokoNokoChallenge_CalcResultText();
#endif
#ifdef NON_MATCHING
extern int *NokoNokoChallenge_GetCoinDivisor(void);
#else
extern void NokoNokoChallenge_GetCoinDivisor();
#endif
#ifdef NON_MATCHING
extern void NokoNokoChallenge_SaveResult(struct CGameCoin *, int, int);
#else
extern void NokoNokoChallenge_SaveResult();
#endif
#ifdef NON_MATCHING
extern int NokoNokoChallenge_TransitionToResult(struct CGameCoin *);
#else
extern void NokoNokoChallenge_TransitionToResult();
#endif
#ifdef NON_MATCHING
extern void Object_SetByte10_Return1(void *, int);
#else
extern void Object_SetByte10_Return1();
#endif
extern void PSMTXCopy(float (*)[4], float (*)[4]);
#ifdef NON_MATCHING
extern void PSMTXTrans(float (*)[4], float, float, float);
#else
extern void PSMTXTrans();
#endif
#ifdef NON_MATCHING
extern float PSVECSquareMag(struct CoinVec *);
#else
extern void PSVECSquareMag();
#endif
#ifdef NON_MATCHING
extern void RenderObj_ItemStateMachine_Timed(void *, int, float, float);
#else
extern void RenderObj_ItemStateMachine_Timed();
#endif
#ifdef NON_MATCHING
extern void RumbleUpdate(void);
#else
extern void RumbleUpdate();
#endif
#ifdef NON_MATCHING
extern void SetCoinCount(int);
#else
extern void SetCoinCount();
#endif
extern void SetCourseScene3D(void *);
#ifdef NON_MATCHING
extern void SetRumbleMode(int, int, int);
#else
extern void SetRumbleMode();
#endif
#ifdef NON_MATCHING
extern float Sinf_LUT_Wrap(float);
#else
extern void Sinf_LUT_Wrap();
#endif
extern void SoundMgr_Play(int);
extern void SoundMgr_PlaySE(int);
#ifdef NON_MATCHING
extern void SoundObj_PlaySE(void *, int);
#else
extern void SoundObj_PlaySE();
#endif
#ifdef NON_MATCHING
extern void SoundObj_PlaySE_Direct(void *, int);
#else
extern void SoundObj_PlaySE_Direct();
#endif
#ifdef NON_MATCHING
extern void SoundVolumePan_Update(void *);
#else
extern void SoundVolumePan_Update();
#endif
#ifdef NON_MATCHING
extern void TornadoEffect_ApplyItemVisual_Primary(void *, int);
#else
extern void TornadoEffect_ApplyItemVisual_Primary();
#endif
#ifdef NON_MATCHING
extern void TornadoEffect_ApplyItemVisual_Secondary(void *, int, int);
#else
extern void TornadoEffect_ApplyItemVisual_Secondary();
#endif
#ifdef NON_MATCHING
extern void TornadoEffect_ClearFlagC0AndSetC4(void *, float);
#else
extern void TornadoEffect_ClearFlagC0AndSetC4();
#endif
#ifdef NON_MATCHING
extern void TornadoEffect_SetFlagC0(void *);
#else
extern void TornadoEffect_SetFlagC0();
#endif
#ifdef NON_MATCHING
extern void TornadoEffect_Tick(void *, int);
#else
extern void TornadoEffect_Tick();
#endif
#ifdef NON_MATCHING
extern void TransitionEffect_Tick(CoinVObj *);
#else
extern void TransitionEffect_Tick();
#endif
extern void Vec3_Normalize(struct CoinVec *, struct CoinVec *);
#ifdef NON_MATCHING
extern void Vec3_Subtract(struct CoinVec *, struct CoinVec *, struct CoinVec *);
#else
extern void Vec3_Subtract();
#endif
#ifdef NON_MATCHING
extern void VfxSlotMgr_Update(struct CoinVec *, struct CoinVec *);
#else
extern void VfxSlotMgr_Update();
#endif
extern void __assert(const char *, int, const char *);
#ifdef NON_MATCHING
extern void fn_8012A71C(void *, float);
#else
extern void fn_8012A71C();
#endif
#ifdef NON_MATCHING
extern void fn_8012B924(void *);
#else
extern void fn_8012B924();
#endif
#ifdef NON_MATCHING
extern unsigned char fn_8012B9AC(void *);
#else
extern void fn_8012B9AC();
#endif
#ifdef NON_MATCHING
extern unsigned char fn_8012BA38(void *);
#else
extern void fn_8012BA38();
#endif
#ifdef NON_MATCHING
extern void fn_8012BAC4(void *);
#else
extern void fn_8012BAC4();
#endif
#ifdef NON_MATCHING
extern void fn_8012BB58(void *);
#else
extern void fn_8012BB58();
#endif
#ifdef NON_MATCHING
extern void fn_8012BD2C(void *);
#else
extern void fn_8012BD2C();
#endif
#ifdef NON_MATCHING
extern void fn_8012BDA4(void *);
#else
extern void fn_8012BDA4();
#endif
#ifdef NON_MATCHING
extern void fn_801699D8(int, int);
#else
extern void fn_801699D8();
#endif
#ifdef NON_MATCHING
extern void fn_8016B32C(void *);
#else
extern void fn_8016B32C();
#endif
extern unsigned char fn_8016C360(int);
extern void fn_8016C394(int);
#ifdef NON_MATCHING
extern void fn_8016C554(int);
#else
extern void fn_8016C554();
#endif
#ifdef NON_MATCHING
extern void fn_8016DA78(void *);
#else
extern void fn_8016DA78();
#endif
#ifdef NON_MATCHING
extern int fn_8016DC90(void *, struct CoinVec *, float);
#else
extern void fn_8016DC90();
#endif
#ifdef NON_MATCHING
extern int fn_8016DEF4(void *);
#else
extern void fn_8016DEF4();
#endif
#ifdef NON_MATCHING
extern unsigned char fn_8016DF50(void *);
#else
extern void fn_8016DF50();
#endif
#ifdef NON_MATCHING
extern void fn_8016EC80(void *);
#else
extern void fn_8016EC80();
#endif
#ifdef NON_MATCHING
extern void fn_801734B0(void *, struct CoinVec *);
#else
extern void fn_801734B0();
#endif
#ifdef NON_MATCHING
extern void fn_80173500(void *);
#else
extern void fn_80173500();
#endif
#ifdef NON_MATCHING
extern void fn_8017351C(void *);
#else
extern void fn_8017351C();
#endif
extern void fn_80182B50(void *, float, float);
#ifdef NON_MATCHING
extern void fn_80192688(int, int);
#else
extern void fn_80192688();
#endif
#ifdef NON_MATCHING
extern unsigned char fn_80253C40(void *);
#else
extern void fn_80253C40();
#endif
#ifdef NON_MATCHING
extern void fn_80253C74(void *, int, void *, int);
#else
extern void fn_80253C74();
#endif
#ifdef NON_MATCHING
extern void fn_80253FD8(void *, float);
#else
extern void fn_80253FD8();
#endif
extern unsigned char g_lakituStartAnimDone;
extern struct CoinInputView *g_pInputState;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern void *g_weatherSystem;
extern unsigned int lbl_806D7148;
extern unsigned int lbl_806D715C;
extern unsigned int lbl_806D7160;
extern unsigned int lbl_806D7164;
extern unsigned int lbl_806D7168;
extern unsigned int lbl_806D716C;
extern unsigned int lbl_806D7170;
extern unsigned int lbl_806D7184;
extern unsigned int lbl_806D7188;
extern unsigned int lbl_806D718C;
extern unsigned int lbl_806D7190;
extern unsigned int lbl_806D7194;
extern unsigned int lbl_806D7198;
extern unsigned int lbl_806D719C;
extern unsigned int lbl_806D71A0;
extern unsigned int lbl_806D71A4;
extern unsigned int lbl_806D71A8;
extern unsigned int lbl_806D71AC;
extern unsigned int lbl_806D71B0;
extern unsigned int lbl_806D71B4;
extern unsigned int lbl_806D71B8;
extern unsigned int lbl_806D71BC;
extern unsigned int lbl_806D71C0;
extern unsigned int lbl_806D71C4;
extern unsigned int lbl_806D71C8;
extern unsigned int lbl_806D71CC;
extern unsigned int lbl_806D71D0;
extern unsigned int lbl_806D71D4;
extern unsigned int lbl_806D71D8;
extern unsigned int lbl_806D71DC;
extern unsigned int lbl_806D71E0;
extern unsigned int lbl_806D71E4;
extern unsigned int lbl_806D71E8;
extern unsigned int lbl_806D71EC;
extern unsigned int lbl_806D71F0;
extern unsigned int lbl_806D71F4;
extern unsigned int lbl_806D71F8;
extern unsigned int lbl_806D71FC;
extern unsigned int lbl_806D7200;
extern unsigned int lbl_806D7204;
extern unsigned int lbl_806D7208;

extern const char CGameCoin_8012BF5C_rodata_80356730[];
extern void HSD_CObjAnim(void *);
extern void HSD_CObjReqAnim(void *, float);
extern void HSD_JObjClearFlagsAll(struct CoinJObj *, int);
extern void HSD_JObjSetFlagsAll(struct CoinJObj *, int);
extern void Object_SetField8_AndDirty(void *, float);
extern float Saturate_Double(float, float, float);
extern void clNormal3D_Exec(void *);
extern int g_characterId;
extern unsigned int lbl_806D720C;
extern unsigned int lbl_806D7210;
extern unsigned int lbl_806D7214;
extern unsigned int lbl_806D7218;
extern unsigned int lbl_806D721C;
extern unsigned int lbl_806D7220;
extern unsigned int lbl_806D7224;
extern unsigned int lbl_806D7228;
extern unsigned int lbl_806D722C;
extern const char DefeatDemo_Update_rodata_80356C58[];
extern unsigned int lbl_806D7134;
extern unsigned int lbl_806D7234;
extern unsigned int lbl_806D7238;
extern unsigned int lbl_806D723C;
extern unsigned int lbl_806D7240;
extern unsigned int lbl_806D7244;
extern unsigned int lbl_806D7248;
extern unsigned int lbl_806D724C;
extern unsigned int lbl_806D7250;
extern float lbl_80495994[];
extern float lbl_80495A94[];
extern void PSMTXMultVec(float (*)[4], struct CoinVec *, struct CoinVec *);
extern float Vec3_Dot(struct CoinVec *, struct CoinVec *);
extern float KoopaFireball_Update_data_806CF578;
extern float KoopaFireball_Update_data_806CF57C;
extern float KoopaFireball_Update_data_806CF580;
extern float KoopaFireball_Update_data_806CF584;
extern float KoopaFireball_Update_data_806CF588;
extern int KoopaFireball_Update_bss_806D1510;
extern unsigned int lbl_806D7254;
extern unsigned int lbl_806D7258;
extern unsigned int lbl_806D725C;
extern unsigned char fn_80123480(void *, struct CoinVec *);
extern void fn_80172844(void *);
extern unsigned int lbl_806D7260;
extern unsigned int lbl_806D7264;
extern void AudioChannel_DtorWithSeStop(void *, int);
extern void ClRomTable_PurgeAll(void);
extern void CourseEnvironment_Dtor(void *, int);
extern void InputCmd_Dtor(void *, int);
extern void ItemObjectManager_Reset(void);
extern void KartDriver_Dtor(void *, int);
extern void LakituStart_Dtor(void *, int);
extern void MemoryManager_TimedFree(void *);
extern void Object_DtorWithGXSync(void *, int);
extern void RankingTable_Init(void *);
extern void SceneDrawList_Reset(void);
extern void SetActiveCamera(void *, int);
extern void SetPlayerCarObject(void *);
extern void SetResourceLoadingFlag(unsigned char);
extern void VfxSlotMgr_Shutdown(void);
extern void VisualEffectHolder_Dtor(void *, int);
extern void clRom_PurgeAll(void);
extern void dtor_80122FD8(void *, int);
extern void fn_80123B48(void *, int);
extern void fn_80124C84(void *, int);
extern void fn_8012B394(void *, int);
extern void fn_80169C44(void);
extern void fn_8016C634(void *, int);
extern void fn_8016DFAC(void *, int);
extern void fn_8016EFA8(void *, int);
extern void fn_80173550(void *, int);
extern void fn_80254134(void *, int);
extern void *g_raceCamera;
extern CoinVObj *lbl_806D10D0;
extern unsigned int vtable[];
void *Alloc(unsigned long size);
extern void ChallengeGoalCamera_Init();
void *CourseEnvironment_ResolveJointInSlot0(void *env, const char *name);
void CourseObjectManager_Init(void);
void DMAChannelManager_Init(void);
void DrawManager_GetOrCreate(void);
extern void GameMode_BaseInit();
int *GetKartModelNameEntry(int chara, int arg);
void GetStartPosition(int idx, float *x, float *y, float *z);
void HSD_JObjSetFlags(void *jobj, unsigned int flags);
extern void HUD_Init();
void HUD_RegisterOverlay(void *hud, int id, int arg);
void InitRumbleController(int arg);
extern void InputCmd_Init();
extern void InputManager_Init();
void ItemObjectManager_Init(void);
extern void KartAudioChannel_Init();
void KartAudioChannel_ResetSEsAndSetFlag(void *o, int flag);
extern void KartDriver_New_Full();
extern void LakituStart_Init();
float *MiniGame_GetCourseData(void);
int MiniGame_GetTimerValue(void);
void PreloadEffectResources(int id);
void ProcessSystemTick(int arg);
extern void Scene3D_Init();
void SoundChannels_ClearAll(void);
void SoundDriver_GetOrCreate(int arg);
void StrPcb_ForceRun_Neutral(void *pcb);
extern struct CoinStrPcb *StrPcb_GetInstance(void);
extern void StrPcb_ResetCommands_Neutral(struct CoinStrPcb *, int);
void TireEffect_ResetSpin(void *o, float a, float b);
extern void TornadoEffect_Ctor();
void TornadoEffect_SetColorPairC8CC(void *o, int a, int b);
void TransitionEffect_GetOrCreate(void);
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
void clNormal3D_SetFlags(void *o, unsigned int flags, int arg);
extern void fn_80123BB4();
extern void fn_8012B48C();
extern void fn_8016E064();
extern void fn_8016F010();
extern void fn_8017363C();
extern int lbl_806D12BC;
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
extern unsigned int lbl_8048E144[];
extern unsigned int CoinShotBase_vtable_8048E34C[];
extern unsigned int KPCoinShots_vtable_8048E3C0[];
extern void HSD_CObjAddAnim(void *, void *);
extern struct CoinJObj *ResolveJointByName(void *, const char *);
extern void clNormal3D_SetScale(void *, int, float, float, float, float);
extern unsigned int lbl_80419EF8[];
extern unsigned long OSGetTick(void);
extern void Object_SetJObjPositionXYZ(void *, float, float, float);
extern float BossKoopa_Init_data_806CF570;
extern float BossKoopa_Init_data_806CF574;
extern void PSMTXIdentity(float (*)[4]);
extern void *LinkedNode_GetField10_OrFallback(void *, int);
extern void Object_RenderJObjEx(void *, void *, int);
extern void Object_SetJObjPositionVec(void *, void *);
extern void Object_SetJObjRotationY(void *, float);
extern void Object_SetJObjScaleXYZ(void *, float, float, float);
extern unsigned int lbl_806D7130;
extern unsigned int lbl_806D713C;
extern float fn_80186960(float);
extern unsigned int lbl_806D7230;
extern int Clamp_Int(int, int, int);
extern void StrPcb_ResetCommands_Zero(struct CoinStrPcb *, int);
extern int abs(int);
extern const unsigned int lbl_806D7268;
extern const unsigned int lbl_806D726C;
extern unsigned int lbl_806D7270;
struct CGameCoin;
void fn_8012BF5C(CGameCoin *self);
void CGameCoin_Draw(CGameCoin *self);
#ifdef NON_MATCHING
extern "C" int CGameCoin_Update(CGameCoin *self);
#else
void CGameCoin_Update(void);
#endif
struct DefeatDemo;
void DefeatDemo_Update(DefeatDemo *self);
struct BossKoopa;
void BossKoopa_UpdateAnim(BossKoopa *self);
struct KoopaFireball;
void KoopaFireball_Update(KoopaFireball *self);
struct CoinShell;
void Shell_UpdateState(CoinShell *self);
struct CGameCoin;
CGameCoin *CGameCoin_Destroy(CGameCoin *self, short flag);
void CGameCoin_InitDefeatDemo(void);
void BossKoopa_Init(void);
struct CGameCoinFields;
void CGameCoin_InitFields(CGameCoinFields *self);
struct CoinParticleManager;
void CoinParticle_Draw(CoinParticleManager *self);
void CoinParticle_Update(CoinParticleManager *self);
CoinParticleManager *CoinParticleManager_Destroy(CoinParticleManager *self, short flag);
struct CoinInput;
void CGameCoin_ProcessInput(CoinInput *s);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Update[8] = {
    0x38, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Update = {
    (void *)&CGameCoin_Update, 0x00002164, (void *)extab_CGameCoin_Update
};


}

struct CoinVec {
    float x;
    float y;
    float z;
};

struct CoinQuat {
    float x;
    float y;
    float z;
    float w;
};

struct CoinJObj {
    unsigned char pad0[0x14];
    unsigned int flags;
    unsigned char pad18[0x4];
    CoinQuat rotate;
    CoinVec scale;
    CoinVec translate;
    float mtx[3][4];
};

struct CoinNormal3D {
    unsigned char opaque[0x5C];
    CoinNormal3D(const char *path, int flags);
};

struct CoinAnimLeaf {
    void *value;
};

struct CoinAnimNode {
    void *opaque;
    CoinAnimLeaf *next;
};

struct CoinAnimDesc {
    void *opaque;
    CoinAnimNode *next;
};

static inline void *CoinAnimLeaf_Value(CoinAnimLeaf *leaf) {
    if (leaf == 0) return 0;
    return leaf->value;
}

static inline void *CoinAnimNode_Value(CoinAnimNode *node) {
    if (node == 0) return 0;
    return CoinAnimLeaf_Value(node->next);
}

static inline void *CoinAnimDesc_Value(CoinAnimDesc *desc) {
    if (desc == 0) return 0;
    return CoinAnimNode_Value(desc->next);
}

struct CoinScene3D : CoinVObj {
    CoinScene3D(const char *path);
    virtual ~CoinScene3D();
    void *cobj;
    unsigned char pad8[0x24];
    CoinAnimDesc *animDesc;
    unsigned char pad30[0x3054];
    unsigned char animFirst;
    float animSpeed;
    float animFrame;
};

struct CoinAnimScene3D : CoinScene3D {
    CoinAnimScene3D(const char *path) : CoinScene3D(path) {
        animSpeed = -1.0f;
        animFrame = 0.0f;
    }
    virtual void key();
    void Start() {
        if (cobj) {
            animFirst = 1;
            animFrame = 0.0f;
            animSpeed = 1.0f;
            HSD_CObjAddAnim(cobj, CoinAnimDesc_Value(animDesc));
            HSD_CObjReqAnim(cobj, animFrame);
            HSD_CObjAnim(cobj);
        }
    }
};

struct DefeatDemo {
    void *body;
    void *hand;
    void *effect;
    CoinScene3D *scene;
    float frame;
    unsigned char first;
    void *spinA;
    void *spinB;
    void *spinC;
    CoinJObj *wheelA;
    CoinJObj *wheelB;
    float wheelAngleA;
    float wheelAngleB;
    CoinJObj *flash;

    DefeatDemo();
};

struct KoopaFlame {
    float life;
    CoinVec vel;
    CoinVec pos;
    float scale;
    float alpha;
    float grow;
};

struct KoopaFireball {
    void *model;
    CoinJObj *jobj;
    float angle;
    int cooldown;
    unsigned char active;
    int rnd64;
    int rnd48;
    unsigned char first;
    CoinVec dir;
    KoopaFlame flames[64];

    KoopaFireball(const char *modelPath) {
        int i;

        model = 0;
        jobj = 0;
        angle = 0.0f;
        cooldown = 0;
        active = 0;
        first = 1;
        rnd64 = 0;
        rnd48 = 0;
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 0.0f;
        for (i = 0; i < 64; i++) {
            flames[i].life = -1.0f;
        }
        model = new CoinNormal3D(modelPath, 1);
    }
};

struct BossKoopa {
    void *anims[4];
    int state;
    int reqState;
    float frame;
    unsigned char justChanged;
    float timer;
    int attack;
    KoopaFireball *fireball;
    int wait;
    int waitMin;
    int waitMax;
    int waitRndIdx;
    int attackRndIdx;

    BossKoopa(int waitMin, int waitMax);
};

struct CoinHsdObj;

struct CoinShellSet {
    void *model;
    void *jobj;
    int visible;
    float mC;
    unsigned char anim[0x30];
    float alpha;
    void *kartJoint;
    void *shells;
};

#include "game/types/CGameCoin.h"



static inline void CoinShellSet_Draw(CoinShellSet *self) {
    if (self->visible == 0) {
        return;
    }
    if (self->alpha <= 0.0f) {
        return;
    }
    Object_SetAnimBinding(self->jobj, self->anim, 0);
    Object_DriveAnimMatrix(self->jobj);
    Object_SetColorAlphaOnly(self->jobj, 0, self->alpha);
    Object_RenderJObjTree(self->jobj, 7);
    fn_8017218C(self->model);
}

static inline void KoopaFireball_Draw(KoopaFireball *self) {
    float (*proj)[4];
    int i;
    float scale;
    float alpha;
    float m[3][4];
    float rot[3][4];

    if (self->jobj == 0) {
        return;
    }
    proj = CObj_GetProjMatrix_Cached(GetCourseScene3D());
    GXChannel channel(Archive_GetRootJObj(self->model), HSD_JObjGetDObj(Archive_GetRootJObj(self->model)), 0x40000000, 1);
    for (i = 0; i < 64; i++) {
        if (self->flames[i].life < 0.0f) {
            continue;
        }
        scale = self->flames[i].scale * CGameCoin_8012BF5C_data_806CF58C;
        alpha = self->flames[i].alpha * CGameCoin_8012BF5C_data_806CF590;
        PSMTXScale(m, scale, scale, 1.0f);
        PSMTXConcat(m, proj, m);
        PSMTXRotRad(rot, 'X', -0.7853982f);
        PSMTXConcat(m, rot, m);
        m[0][3] = self->flames[i].pos.x;
        m[1][3] = self->flames[i].pos.y;
        m[2][3] = self->flames[i].pos.z;
        Object_SetColorAlphaOnly(self->model, 0, alpha);
        GXChannel_PushTransform(&channel, m);
        scale = self->flames[i].scale * CGameCoin_8012BF5C_data_806CF594;
        alpha = self->flames[i].alpha * CGameCoin_8012BF5C_data_806CF598;
        if (self->flames[i].life < 10.0f) {
            alpha *= 0.1f * self->flames[i].life;
        }
        PSMTXScale(m, scale, scale, 1.0f);
        PSMTXConcat(m, proj, m);
        m[0][3] = self->flames[i].pos.x;
        m[1][3] = self->flames[i].pos.y;
        m[2][3] = self->flames[i].pos.z;
        Object_SetColorAlphaOnly(self->model, 0, alpha);
        GXChannel_PushTransform(&channel, m);
    }
}

static inline void BossKoopa_Draw(BossKoopa *self) {
    if (self->state >= 4) {
        return;
    }
    Object_RenderJObjTree(self->anims[self->state], 7);
    KoopaFireball_Draw(self->fireball);
}

extern "C" void fn_8012BF5C(CGameCoin *self) { /* 0x8012BF5C size:0x370 */
    if (self->scene->Begin() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->scene);
        fn_8016B0C4();
        KartItem_DispatchEffectRenderByState(self->effects);
        fn_8012A61C(self->m48);
        KartItem_FlushPendingRender_v2(self->effects);
        Object_RenderJObjIfWithinRange(self->lakitu);
        CourseEnvironment_RenderObjects_Timed(self->env);
        fn_8016DA30(self->m70);
        Subsystem36c_DispatchPass2_Timed(self->env);
        self->particles->Draw();
        CoinShellSet_Draw(self->shellSet);
        ItemObjectManager_Render();
        BossKoopa_Draw(self->koopa);
        DrawEffect_TickAndCull();
        fn_8016EACC(self->m74);
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        Subsystem36c_DispatchPass4_Timed(self->env);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
        self->scene->Draw();
    }
}

extern "C" void CGameCoin_Draw(CGameCoin *self) { /* 0x8012C2CC size:0x26C */
    DefeatDemo *demo;

    if (self->active == 0) {
        return;
    }
    if (self->demoMode == 0) {
        fn_8012BF5C(self);
    } else if (self->defeated != 0) {
        if (self->defeatDemo->scene->Begin() == 1) {
            clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->defeatDemo->scene);
            fn_8016B0C4();
            demo = self->defeatDemo;
            Object_RenderJObjTree(demo->body, 7);
            Object_RenderJObjTree(demo->hand, 7);
            Object_RenderJObjTree(demo->effect, 7);
            fn_8016EACC(self->m74);
            self->particles->Draw();
            clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
            self->defeatDemo->scene->Draw();
        }
    } else {
        if (self->scene->Begin() == 1) {
            clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->scene);
            fn_8016B0C4();
            fn_8012A61C(self->m48);
            Object_RenderJObjIfWithinRange(self->lakitu);
            CourseEnvironment_RenderObjects_Timed(self->env);
            Subsystem36c_DispatchPass2_Timed(self->env);
            fn_8016EACC(self->m74);
            clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
            self->scene->Draw();
        }
    }
    fn_80253448(self->hud, lbl_806DC1B8);
    fn_802535D4(self->hud);
    TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
    HSD_StateInvalidate(0x7F);
}

/* .rodata pool 0x80356730..0x80357008: defined before the Update asm references it */
extern "C" const char CGameCoin_8012BF5C_rodata_80356730[0x418] = {
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x44, 0x7A, 0x00, 0x00, 0x42, 0x85, 0x55, 0x56, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x3B, 0x80, 0x00, 0x42, 0x85, 0x55, 0x56, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0x85, 0x55, 0x56, 0x45, 0x9C, 0x40, 0x00, 0x42, 0x85, 0x55, 0x56, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x44, 0x7A, 0x00, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x44, 0xFA, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x3B, 0x80, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x7A, 0x00, 0x00,
    0x42, 0xA6, 0xAA, 0xAB, 0x45, 0x9C, 0x40, 0x00, 0x42, 0xA6, 0xAA, 0xAB, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x70, 0x00, 0x00, 0x43, 0x48, 0x00, 0x00,
    0x42, 0x8C, 0x00, 0x00, 0x42, 0x8C, 0x00, 0x00,
};
static const unsigned int s_shellPathData[0x26] = {
    0xC29C0000, 0x00000000, 0xC3460000, 0x42580000, 0x00000000, 0xC3460000,
    0x43988000, 0x00000000, 0x43A28000, 0xC3858000, 0x00000000, 0x439F0000,
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x43B68000,
    0xC28D0000, 0xC25C0000, 0x428D0000, 0xC22E0000, 0xC25C0000, 0xC0800000,
    0x00000000, 0xC25C0000, 0xC0800000, 0x42200000, 0xC25C0000, 0xC0B00000,
    0x42890000, 0xC25C0000, 0x42900000, 0x41400000, 0x40C00000, 0x00000000,
    0xC1000000, 0xC1800000,
};
static const unsigned int s_defaultCourse[5] = {
    0x00000078, 0x40A00000, 0x00000014, 0x00000078, 0x01000000,
};
extern "C" const char lbl_80356BF4[12] = "clCGameKP";
extern "C" const unsigned int CGameCoin_8012BF5C_rodata_80356C00[0x16] = {
    0x636C4A6F, 0x6252756E, 0x6E657200, 0x48697420, 0x4E6F203D, 0x2025640A,
    0x00000000, 0x53746172, 0x7420746F, 0x204B5043, 0x6F696E2E, 0x20436F69,
    0x6E206B69, 0x6E642069, 0x73202564, 0x2E202025, 0x73202D20, 0x25640A00,
    0x4347616D, 0x65436F69, 0x6E2E6870, 0x70000000,
};
extern "C" const char DefeatDemo_Update_rodata_80356C58[40] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static const char s_lakituFile[20] = "jyugemu_start.dat";
static const char s_shellFile[24] = "it_a_03_black_shell.dat";
static const char s_lavaJoint1[28] = "KP_castle_zyougan01_joint";
static const char s_lavaJoint2[28] = "KP_castle_zyougan02_joint";
static const char s_lavaJoint3[28] = "KP_castle_zyougan03_joint";
static const char s_skydomeJoint[32] = "KP_castle_kp01_skydome_joint";
static const char s_skycloudJoint[32] = "KP_castle_kp03_skycloud_joint";
static const char s_coinFile[16] = "mario_coin.dat";
static const char s_kiraFile[16] = "k_kira13.dat";
extern "C" const unsigned int lbl_80356D60[0x9C] = {
    0x6368616C, 0x6C656E67, 0x655F6465, 0x6D6F5F4B, 0x505F656E, 0x642E6461,
    0x74000000, 0x626F7373, 0x5F6D656B, 0x615F6B6F, 0x6F70615F, 0x656E642E,
    0x64617400, 0x626F7373, 0x5F6B6F6F, 0x70615F65, 0x6E642E64, 0x61740000,
    0x6B6F6F70, 0x61646561, 0x642E6461, 0x74000000, 0x4B505F63, 0x616C6C65,
    0x6E67655F, 0x7A796F75, 0x67616E30, 0x315F6A6F, 0x696E7400, 0x4B505F63,
    0x616C6C65, 0x6E67655F, 0x7A796F75, 0x67616E30, 0x325F6A6F, 0x696E7400,
    0x4B505F63, 0x616C6C65, 0x6E67655F, 0x7A796F75, 0x67616E30, 0x335F6A6F,
    0x696E7400, 0x4B505F63, 0x616C6C65, 0x6E67655F, 0x6B703031, 0x5F736B79,
    0x646F6D65, 0x5F6A6F69, 0x6E740000, 0x4B505F63, 0x616C6C65, 0x6E67655F,
    0x6B703033, 0x5F736B79, 0x636C6F75, 0x645F6A6F, 0x696E7400, 0x6B706368,
    0x5F6D6167, 0x756D615F, 0x666C7569, 0x645F7061, 0x7274735F, 0x63686D66,
    0x5F696E5F, 0x6A6F696E, 0x74000000, 0x6B6F6F70, 0x615F6669, 0x72652E64,
    0x61740000, 0x626F7373, 0x5F6D656B, 0x615F6B6F, 0x6F70615F, 0x74616D62,
    0x2E646174, 0x00000000, 0x626F7373, 0x5F6D656B, 0x615F6B6F, 0x6F70615F,
    0x6672616D, 0x652E6461, 0x74000000, 0x626F7373, 0x5F6D656B, 0x615F6B6F,
    0x6F70615F, 0x64616D61, 0x67655F6C, 0x2E646174, 0x00000000, 0x626F7373,
    0x5F6D656B, 0x615F6B6F, 0x6F70615F, 0x64616D61, 0x67655F72, 0x2E646174,
    0x00000000, 0x5F326368, 0x616C6C65, 0x6E67655F, 0x6D656B61, 0x5F6B6F6F,
    0x70615F66, 0x6C616D65, 0x5F6E756C, 0x6C5F6A6F, 0x696E7400, 0x626F7373,
    0x5F6B6F6F, 0x70615F74, 0x616D622E, 0x64617400, 0x626F7373, 0x5F6B6F6F,
    0x70615F66, 0x72616D65, 0x2E646174, 0x00000000, 0x626F7373, 0x5F6B6F6F,
    0x70615F64, 0x616D6167, 0x655F6C2E, 0x64617400, 0x626F7373, 0x5F6B6F6F,
    0x70615F64, 0x616D6167, 0x655F722E, 0x64617400, 0x5F326368, 0x616C6C65,
    0x6E67655F, 0x6B6F6F70, 0x615F666C, 0x616D655F, 0x6E756C6C, 0x5F315F6A,
    0x6F696E74, 0x00000000, 0x636C4D65, 0x6E75496E, 0x70757400, 0x74655369,
    0x6E676C65, 0x746F6E3C, 0x636C4D65, 0x6E75496E, 0x7075743E, 0x00000000,
};
extern "C" const char lbl_80356FD0[16] = "clCGameCoinBase";
extern "C" const unsigned int sdata_806CF1C0_rodata_80356FE0[0xA] = {
    0x636C4347, 0x616D654B, 0x50436F69, 0x6E000000, 0x636C4143, 0x616D6572,
    0x61000000, 0x636C4361, 0x6D657261, 0x00000000,
};

#ifndef NON_MATCHING /* C version: end of this file */
extern "C" asm void CGameCoin_Update(void) { /* 0x8012C538 size:0x2164 */
    nofralloc
    stwu r1, -0x1c0(r1)
    mflr r0
    stw r0, 0x1c4(r1)
    stfd f31, 0x1b0(r1)
    psq_st f31, 0x1b8(r1), 0, 0
    stfd f30, 0x1a0(r1)
    psq_st f30, 0x1a8(r1), 0, 0
    stfd f29, 0x190(r1)
    psq_st f29, 0x198(r1), 0, 0
    stmw r25, 0x174(r1)
    mr r28, r3
    lis r3, CGameCoin_8012BF5C_rodata_80356730@ha
    lbz r0, 0x7c(r28)
    addi r31, r3, CGameCoin_8012BF5C_rodata_80356730@l
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012C580
    li r0, 0x1
    stb r0, 0x7c(r28)
    CGameCoin_Update_L_8012C580:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012C5AC
    lbz r0, 0x7d(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012C5CC
    li r3, 0x33
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, 0x7d(r28)
    b CGameCoin_Update_L_8012C5CC
    CGameCoin_Update_L_8012C5AC:
    lbz r0, 0x7d(r28)
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012C5CC
    li r3, 0x33
    li r4, 0x1
    bl fn_80192688
    li r0, 0x0
    stb r0, 0x7d(r28)
    CGameCoin_Update_L_8012C5CC:
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012C5DC
    li r3, 0x0
    CGameCoin_Update_L_8012C5DC:
    bl CGameCoin_ProcessInput
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lfs f1, lbl_806D7150(r2)
    mr r30, r3
    lfs f0, lbl_806D715C(r2)
    stfs f1, 0x74(r1)
    stfs f1, 0x78(r1)
    stfs f0, 0x7c(r1)
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D880
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r28)
    fmr f31, f1
    lwz r3, 0x304(r3)
    bl ItemEffectBus_SnapshotAndFullReset
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D3BC
    lfs f0, 0x94(r28)
    li r29, 0x0
    lfs f1, lbl_806D7150(r2)
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    beq CGameCoin_Update_L_8012C67C
    lfs f0, 0x98(r28)
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    beq CGameCoin_Update_L_8012C67C
    lwz r3, 0x88(r28)
    lwz r0, 0x8c(r28)
    cmpw r3, r0
    beq CGameCoin_Update_L_8012C680
    CGameCoin_Update_L_8012C67C:
    li r29, 0x1
    CGameCoin_Update_L_8012C680:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    mr r3, r30
    fmr f29, f1
    lwz r12, 0x0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    mr r3, r30
    fmr f30, f1
    lwz r12, 0x0(r30)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lfs f5, lbl_806D7160(r2)
    lis r0, 0x4330
    stw r0, 0x148(r1)
    li r4, 0x0
    fmuls f2, f5, f1
    lfd f4, lbl_806D7148(r2)
    fmuls f1, f5, f30
    stw r0, 0x158(r1)
    fmuls f0, f5, f29
    lwz r3, 0x8(r28)
    fctiwz f2, f2
    stw r0, 0x168(r1)
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f2, 0x140(r1)
    stfd f1, 0x150(r1)
    lwz r0, 0x144(r1)
    stfd f0, 0x160(r1)
    lwz r5, 0x154(r1)
    xoris r6, r0, 0x8000
    lwz r0, 0x164(r1)
    xoris r5, r5, 0x8000
    stw r6, 0x14c(r1)
    xoris r0, r0, 0x8000
    stw r5, 0x15c(r1)
    lfd f0, 0x148(r1)
    stw r0, 0x16c(r1)
    lfd f1, 0x158(r1)
    fsubs f3, f0, f4
    lfd f0, 0x168(r1)
    fsubs f2, f1, f4
    fsubs f0, f0, f4
    fdivs f1, f3, f5
    fdivs f2, f2, f5
    fdivs f3, f0, f5
    bl InputCmd_PushSample
    lwz r3, 0x8(r28)
    bl InputCmd_TickAndDetectAndClear
    lwz r3, 0x4c(r28)
    bl Shell_UpdateState
    lwz r27, 0x4c(r28)
    lwz r4, 0x8(r27)
    cmpwi r4, 0x2
    beq CGameCoin_Update_L_8012C864
    bge CGameCoin_Update_L_8012C788
    cmpwi r4, 0x0
    beq CGameCoin_Update_L_8012C798
    bge CGameCoin_Update_L_8012C82C
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C788:
    cmpwi r4, 0x4
    beq CGameCoin_Update_L_8012CC00
    bge CGameCoin_Update_L_8012D28C
    b CGameCoin_Update_L_8012C9EC
    CGameCoin_Update_L_8012C798:
    lwz r3, 0x9c(r28)
    cmpwi r3, 0x0
    ble CGameCoin_Update_L_8012C7B0
    subi r0, r3, 0x1
    stw r0, 0x9c(r28)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C7B0:
    cmpwi r4, 0x0
    bne CGameCoin_Update_L_8012D28C
    li r0, 0x1
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r27)
    addi r3, r27, 0x10
    lfs f0, lbl_806D7140(r2)
    li r4, 0x59
    stfs f1, 0xc(r27)
    lfs f1, lbl_806D7164(r2)
    stfs f0, 0x40(r27)
    bl PSMTXRotRad
    lfs f1, lbl_806D7168(r2)
    addi r3, r1, 0xe0
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r27, 0x10
    addi r4, r1, 0xe0
    mr r5, r3
    bl PSMTXConcat
    addi r3, r31, 0x454
    lfs f2, 0x454(r31)
    lfs f1, lbl_806D716C(r2)
    lfs f0, 0x4(r3)
    stfs f2, 0x1c(r27)
    fadds f1, f1, f0
    lfs f0, 0x8(r3)
    stfs f1, 0x2c(r27)
    stfs f0, 0x3c(r27)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C82C:
    lfs f1, lbl_806D7170(r2)
    lfs f0, 0x34(r28)
    lfs f2, 0x2c(r27)
    fadds f0, f1, f0
    fcmpo cr0, f2, f0
    bge CGameCoin_Update_L_8012D28C
    cmpwi r4, 0x1
    bne CGameCoin_Update_L_8012D28C
    li r0, 0x2
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r27)
    stfs f0, 0xc(r27)
    stfs f0, 0x40(r27)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C864:
    lwz r3, 0x48(r28)
    bl fn_8012BA38
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    lwz r30, 0x4c(r28)
    addi r5, r31, 0x460
    lwz r3, 0x8c(r28)
    lwz r0, 0x8(r30)
    mulli r3, r3, 0xc
    cmpwi r0, 0x2
    add r5, r5, r3
    bne CGameCoin_Update_L_8012C9C4
    lfs f0, 0x0(r5)
    addi r4, r30, 0x50
    lfs f1, 0x4(r5)
    stfs f0, 0x50(r30)
    lfs f0, 0x8(r5)
    stfs f1, 0x54(r30)
    stfs f0, 0x58(r30)
    lwz r3, 0x0(r30)
    bl fn_801734B0
    lwz r3, 0x0(r30)
    bl fn_8017351C
    li r0, 0x3
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r30)
    stfs f0, 0xc(r30)
    stfs f0, 0x40(r30)
    lwz r27, 0x44(r30)
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012C9C4
    bne CGameCoin_Update_L_8012C8F4
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x47c
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012C8F4:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012C93C
    bne CGameCoin_Update_L_8012C910
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012C910:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012C92C
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012C92C
    li r3, 0x1
    CGameCoin_Update_L_8012C92C:
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012C93C
    mr r3, r27
    bl HSD_JObjSetupMatrixSub
    CGameCoin_Update_L_8012C93C:
    addi r27, r27, 0x44
    addi r4, r30, 0x10
    mr r3, r27
    bl PSMTXCopy
    lfs f1, lbl_806D7164(r2)
    addi r3, r1, 0xb0
    li r4, 0x5a
    bl PSMTXRotRad
    addi r3, r30, 0x10
    addi r4, r1, 0xb0
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0xb0
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r30, 0x10
    addi r4, r1, 0xb0
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    lfs f1, 0x14(r30)
    lfs f0, 0xc(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r30)
    lfs f1, 0x24(r30)
    lfs f0, 0x1c(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r30)
    lfs f1, 0x34(r30)
    lfs f0, 0x2c(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r30)
    CGameCoin_Update_L_8012C9C4:
    lwz r5, 0x84(r28)
    li r3, 0x0
    li r4, 0x1
    lwz r0, 0x0(r5)
    stw r0, 0x9c(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x1
    bl fn_801699D8
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C9EC:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D28C
    cmpwi r4, 0x3
    bne CGameCoin_Update_L_8012CA18
    lfs f1, 0xc(r27)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012CA18
    li r0, 0x1
    b CGameCoin_Update_L_8012CA1C
    CGameCoin_Update_L_8012CA18:
    li r0, 0x0
    CGameCoin_Update_L_8012CA1C:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012D28C
    mr r3, r30
    lis r4, 0x1
    lwz r12, 0x0(r30)
    subi r4, r4, 0x1c01
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    bl Input_IsItemButtonPressed
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    lwz r3, 0x48(r28)
    bl fn_8012B9AC
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x0
    li r4, 0x4
    li r5, 0x1e
    bl SetRumbleMode
    li r3, 0x68
    bl SoundMgr_PlaySE
    lwz r29, 0x4c(r28)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012CAB8
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012CAB8
    li r0, 0x1
    b CGameCoin_Update_L_8012CABC
    CGameCoin_Update_L_8012CAB8:
    li r0, 0x0
    CGameCoin_Update_L_8012CABC:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012CBF8
    lwz r3, 0x0(r29)
    bl fn_80173500
    li r0, 0x4
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r29)
    li r0, 0x0
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r29)
    stfs f0, 0x40(r29)
    stb r0, 0x4c(r29)
    lwz r27, 0x44(r29)
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012CBF8
    bne CGameCoin_Update_L_8012CB0C
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x47c
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012CB0C:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012CB54
    bne CGameCoin_Update_L_8012CB28
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012CB28:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012CB44
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012CB44
    li r3, 0x1
    CGameCoin_Update_L_8012CB44:
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012CB54
    mr r3, r27
    bl HSD_JObjSetupMatrixSub
    CGameCoin_Update_L_8012CB54:
    lfs f1, lbl_806D718C(r2)
    addi r3, r29, 0x10
    li r4, 0x59
    bl PSMTXRotRad
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0x80
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r29, 0x10
    addi r4, r1, 0x80
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    addi r3, r29, 0x5c
    lfs f1, 0x14(r29)
    mr r4, r3
    lfs f0, 0x50(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r29)
    lfs f1, 0x24(r29)
    lfs f0, 0x60(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r29)
    lfs f1, 0x34(r29)
    lfs f0, 0x70(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r29)
    lfs f1, 0x50(r29)
    lfs f0, 0x1c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x5c(r29)
    lfs f1, 0x54(r29)
    lfs f0, 0x2c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x60(r29)
    lfs f1, 0x58(r29)
    lfs f0, 0x3c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x64(r29)
    bl Vec3_Normalize
    CGameCoin_Update_L_8012CBF8:
    li r29, 0x1
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012CC00:
    lfs f0, 0x1c(r27)
    addi r4, r1, 0x38
    lfs f1, lbl_806D7190(r2)
    stfs f0, 0x38(r1)
    lfs f0, 0x2c(r27)
    stfs f0, 0x3c(r1)
    lfs f0, 0x3c(r27)
    stfs f0, 0x40(r1)
    lwz r3, 0x70(r28)
    bl fn_8016DC90
    mr. r25, r3
    blt CGameCoin_Update_L_8012D28C
    lwz r4, 0x4c(r28)
    lwz r0, 0x8(r4)
    cmpwi r0, 0x4
    bne CGameCoin_Update_L_8012CC60
    li r0, 0x5
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r4)
    li r3, 0xc9
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x40(r4)
    bl SoundMgr_PlaySE
    CGameCoin_Update_L_8012CC60:
    cmpwi r25, 0x0
    beq CGameCoin_Update_L_8012CC70
    cmpwi r25, 0x3
    bne CGameCoin_Update_L_8012CC7C
    CGameCoin_Update_L_8012CC70:
    lwz r3, 0x6c(r28)
    li r0, 0x2
    stw r0, 0x14(r3)
    CGameCoin_Update_L_8012CC7C:
    cmpwi r25, 0x1
    beq CGameCoin_Update_L_8012CC8C
    cmpwi r25, 0x2
    bne CGameCoin_Update_L_8012CC98
    CGameCoin_Update_L_8012CC8C:
    lwz r3, 0x6c(r28)
    li r0, 0x3
    stw r0, 0x14(r3)
    CGameCoin_Update_L_8012CC98:
    lwz r3, 0x14(r28)
    li r4, 0xb
    bl SoundObj_PlaySE
    lwz r3, 0x48(r28)
    bl fn_8012BAC4
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    cmpwi r3, 0x4
    bge CGameCoin_Update_L_8012D28C
    mr r4, r25
    addi r3, r31, 0x4dc
    crxor 6, 6, 6
    bl DebugPrintf
    subfic r0, r25, 0x1
    li r4, 0x1
    orc r3, r4, r25
    srwi r0, r0, 1
    subf r0, r0, r3
    srwi. r0, r0, 31
    bne CGameCoin_Update_L_8012CCEC
    li r4, 0x0
    CGameCoin_Update_L_8012CCEC:
    clrlwi r3, r4, 24
    lwz r27, 0xc0(r28)
    neg r0, r3
    or r0, r0, r3
    srwi r30, r0, 31
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012CED8
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012CD40
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012CD40:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD60
    li r3, 0x0
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD60:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD74
    li r3, 0x1
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD74:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD88
    li r3, 0x2
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD88:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD9C
    li r3, 0x3
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD9C:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CDB0
    li r3, 0x4
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CDB0:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CDC0
    li r3, 0x5
    CGameCoin_Update_L_8012CDC0:
    mulli r26, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7198(r2)
    add r3, r27, r26
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r25, r27, r26
    fmuls f0, f2, f1
    lfs f1, lbl_806D7198(r2)
    stfs f0, 0x2c(r25)
    stfs f2, 0x30(r25)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r25
    fmuls f0, f0, f1
    stfs f0, 0x34(r25)
    beq CGameCoin_Update_L_8012CE74
    bge CGameCoin_Update_L_8012CE48
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012CE54
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CE48:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012CED8
    b CGameCoin_Update_L_8012CEA4
    CGameCoin_Update_L_8012CE54:
    lfs f0, 0x2c(r25)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r25)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CE74:
    lfs f1, 0x2c(r25)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r25)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r25)
    fmuls f0, f1, f0
    stfs f0, 0x30(r25)
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CEA4:
    lfs f1, 0x2c(r25)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r25)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r25)
    fmuls f0, f1, f0
    stfs f0, 0x30(r25)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012CED8:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D0B0
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012CF1C
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012CF1C:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF3C
    li r3, 0x0
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF3C:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF50
    li r3, 0x1
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF50:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF64
    li r3, 0x2
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF64:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF78
    li r3, 0x3
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF78:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF8C
    li r3, 0x4
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF8C:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF9C
    li r3, 0x5
    CGameCoin_Update_L_8012CF9C:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f1, lbl_806D7150(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f1, 0x3c(r3)
    stfs f1, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7150(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r26
    fmuls f0, f0, f1
    stfs f0, 0x34(r26)
    beq CGameCoin_Update_L_8012D04C
    bge CGameCoin_Update_L_8012D020
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012D02C
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D020:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012D0B0
    b CGameCoin_Update_L_8012D07C
    CGameCoin_Update_L_8012D02C:
    lfs f0, 0x2c(r26)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r26)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D04C:
    lfs f1, 0x2c(r26)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D07C:
    lfs f1, 0x2c(r26)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012D0B0:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012D0F4
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012D0F4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D114
    li r3, 0x0
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D114:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D128
    li r3, 0x1
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D128:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D13C
    li r3, 0x2
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D13C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D150
    li r3, 0x3
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D150:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D164
    li r3, 0x4
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D164:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D174
    li r3, 0x5
    CGameCoin_Update_L_8012D174:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D71AC(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D71AC(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r26
    fmuls f0, f0, f1
    stfs f0, 0x34(r26)
    beq CGameCoin_Update_L_8012D228
    bge CGameCoin_Update_L_8012D1FC
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012D208
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D1FC:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012D28C
    b CGameCoin_Update_L_8012D258
    CGameCoin_Update_L_8012D208:
    lfs f0, 0x2c(r26)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r26)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D228:
    lfs f1, 0x2c(r26)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D258:
    lfs f1, 0x2c(r26)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012D28C:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D2CC
    lwz r3, 0x8(r28)
    bl InputCmd_GetDetectedFlag
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D2CC
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x94(r28)
    lwz r3, 0x10(r28)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x14(r28)
    li r4, 0x56
    bl SoundObj_PlaySE_Direct
    lwz r3, 0x48(r28)
    bl fn_8012BB58
    li r29, 0x1
    CGameCoin_Update_L_8012D2CC:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D3BC
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012D2E8
    li r0, 0x0
    b CGameCoin_Update_L_8012D2EC
    CGameCoin_Update_L_8012D2E8:
    mr r0, r3
    CGameCoin_Update_L_8012D2EC:
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012D3BC
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012D300
    li r3, 0x0
    CGameCoin_Update_L_8012D300:
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    bne CGameCoin_Update_L_8012D32C
    lwz r3, 0x88(r28)
    cmpwi r3, 0x4
    bge CGameCoin_Update_L_8012D350
    addi r0, r3, 0x1
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8c(r28)
    stfs f0, 0x90(r28)
    b CGameCoin_Update_L_8012D350
    CGameCoin_Update_L_8012D32C:
    cmpwi r0, -0x1
    bne CGameCoin_Update_L_8012D350
    lwz r3, 0x88(r28)
    cmpwi r3, 0x0
    ble CGameCoin_Update_L_8012D350
    subi r0, r3, 0x1
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8c(r28)
    stfs f0, 0x90(r28)
    CGameCoin_Update_L_8012D350:
    lwz r0, 0x88(r28)
    lwz r3, 0x8c(r28)
    cmpw r0, r3
    beq CGameCoin_Update_L_8012D3BC
    lwz r5, 0x4c(r28)
    mulli r3, r3, 0xc
    addi r6, r31, 0x460
    lwz r0, 0x8(r5)
    add r6, r6, r3
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D3A0
    lfs f0, 0x0(r6)
    addi r4, r5, 0x50
    lfs f1, 0x4(r6)
    stfs f0, 0x50(r5)
    lfs f0, 0x8(r6)
    stfs f1, 0x54(r5)
    stfs f0, 0x58(r5)
    lwz r3, 0x0(r5)
    bl fn_801734B0
    CGameCoin_Update_L_8012D3A0:
    lwz r3, 0x10(r28)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x14(r28)
    li r4, 0x56
    bl SoundObj_PlaySE_Direct
    lwz r3, 0x48(r28)
    bl fn_8012BB58
    CGameCoin_Update_L_8012D3BC:
    lfs f2, 0x94(r28)
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D454
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D454
    lfs f1, lbl_806D7140(r2)
    lfs f0, lbl_806D7198(r2)
    fadds f1, f2, f1
    stfs f1, 0x94(r28)
    lfs f1, 0x94(r28)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D414
    lfs f0, lbl_806D71B0(r2)
    fmuls f1, f0, f1
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7138(r2)
    lfs f0, 0x78(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0x78(r1)
    CGameCoin_Update_L_8012D414:
    lfs f0, lbl_806D7198(r2)
    lfs f1, 0x94(r28)
    fcmpu cr0, f0, f1
    bne CGameCoin_Update_L_8012D440
    lwz r3, 0x10(r28)
    lfs f1, lbl_806D71B4(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    lwz r3, 0x14(r28)
    li r4, 0x57
    bl SoundObj_PlaySE_Direct
    b CGameCoin_Update_L_8012D454
    CGameCoin_Update_L_8012D440:
    lfs f0, lbl_806D71B8(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_Update_L_8012D454
    lfs f0, lbl_806D71BC(r2)
    stfs f0, 0x94(r28)
    CGameCoin_Update_L_8012D454:
    lwz r3, 0x88(r28)
    lwz r0, 0x8c(r28)
    cmpw r3, r0
    beq CGameCoin_Update_L_8012D52C
    lfs f1, 0x90(r28)
    lfs f0, lbl_806D7140(r2)
    lfs f2, lbl_806D71C0(r2)
    fadds f0, f1, f0
    stfs f0, 0x90(r28)
    lfs f3, 0x90(r28)
    fcmpo cr0, f3, f2
    bge CGameCoin_Update_L_8012D4D8
    lwz r4, 0x88(r28)
    addi r3, r31, 0x49c
    lwz r0, 0x8c(r28)
    slwi r4, r4, 2
    lfs f1, lbl_806D7170(r2)
    slwi r0, r0, 2
    lfsx f4, r3, r4
    lfsx f0, r3, r0
    fsubs f0, f0, f4
    fmuls f0, f3, f0
    fdivs f0, f0, f2
    fadds f0, f4, f0
    stfs f0, 0xa0(r28)
    lfs f0, 0x90(r28)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7190(r2)
    lfs f0, 0x78(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0x78(r1)
    b CGameCoin_Update_L_8012D4EC
    CGameCoin_Update_L_8012D4D8:
    lwz r0, 0x8c(r28)
    addi r3, r31, 0x49c
    slwi r0, r0, 2
    lfsx f0, r3, r0
    stfs f0, 0xa0(r28)
    CGameCoin_Update_L_8012D4EC:
    lfs f0, lbl_806D71C0(r2)
    lfs f1, 0x90(r28)
    fcmpu cr0, f0, f1
    bne CGameCoin_Update_L_8012D518
    lwz r3, 0x10(r28)
    lfs f1, lbl_806D71C4(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    lwz r3, 0x14(r28)
    li r4, 0x57
    bl SoundObj_PlaySE_Direct
    b CGameCoin_Update_L_8012D52C
    CGameCoin_Update_L_8012D518:
    lfs f0, lbl_806D71C8(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_Update_L_8012D52C
    lwz r0, 0x8c(r28)
    stw r0, 0x88(r28)
    CGameCoin_Update_L_8012D52C:
    lfs f1, lbl_806D7140(r2)
    addi r3, r28, 0x18
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, lbl_806D71D0(r2)
    addi r3, r1, 0x110
    lfs f0, 0xa0(r28)
    li r4, 0x59
    lfs f2, lbl_806D71CC(r2)
    fadds f0, f1, f0
    fmuls f1, f2, f0
    bl PSMTXRotRad
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, 0x74(r1)
    addi r3, r1, 0x110
    lfs f2, 0x78(r1)
    lfs f3, 0x7c(r1)
    bl PSMTXTrans
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lwz r3, 0x6c(r28)
    bl BossKoopa_UpdateAnim
    lwz r3, 0x6c(r28)
    li r27, 0x0
    lfs f30, lbl_806D7150(r2)
    lwz r29, 0x28(r3)
    CGameCoin_Update_L_8012D5AC:
    lfs f0, 0x2c(r29)
    fcmpo cr0, f0, f30
    blt CGameCoin_Update_L_8012D614
    addi r3, r1, 0x74
    addi r4, r29, 0x3c
    addi r5, r1, 0x8
    bl Vec3_Subtract
    lfs f0, lbl_806D7150(r2)
    addi r3, r1, 0x8
    stfs f0, 0xc(r1)
    bl PSVECSquareMag
    lfs f0, lbl_806D71D4(r2)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D614
    lfs f2, 0x78(r1)
    lfs f1, 0xc(r1)
    lfs f0, lbl_806D7150(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D600
    fneg f1, f1
    CGameCoin_Update_L_8012D600:
    lfs f0, lbl_806D7190(r2)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D614
    li r0, 0x1
    b CGameCoin_Update_L_8012D628
    CGameCoin_Update_L_8012D614:
    addi r27, r27, 0x1
    addi r29, r29, 0x28
    cmpwi r27, 0x40
    blt CGameCoin_Update_L_8012D5AC
    li r0, 0x0
    CGameCoin_Update_L_8012D628:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012D718
    lwz r3, 0x4c(r28)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D698
    lwz r3, 0x84(r28)
    lbz r0, 0x10(r3)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012D698
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    lwz r3, 0x4c(r28)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D690
    li r0, 0x6
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r3)
    stfs f0, 0xc(r3)
    lwz r3, 0x0(r3)
    bl fn_80173500
    CGameCoin_Update_L_8012D690:
    lwz r3, 0x48(r28)
    bl fn_8012B924
    CGameCoin_Update_L_8012D698:
    lwz r4, 0x4c(r28)
    lwz r3, 0x8(r4)
    subfic r0, r3, 0x4
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq CGameCoin_Update_L_8012D6D8
    cmpwi r3, 0x4
    bne CGameCoin_Update_L_8012D6D8
    li r0, 0x5
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r4)
    li r3, 0xc9
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x40(r4)
    bl SoundMgr_PlaySE
    CGameCoin_Update_L_8012D6D8:
    lwz r3, 0xc(r28)
    li r4, 0x5f
    li r5, 0x1
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventSet
    lwz r3, 0x10(r28)
    li r4, 0x5f
    li r5, 0x1
    bl TornadoEffect_ApplyItemVisual_Secondary
    lwz r3, 0x14(r28)
    li r4, 0xc
    bl SoundObj_PlaySE
    lwz r3, 0x48(r28)
    bl fn_8012BD2C
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x98(r28)
    CGameCoin_Update_L_8012D718:
    lfs f2, 0x98(r28)
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D768
    lfs f1, lbl_806D7140(r2)
    lfs f0, lbl_806D7188(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x98(r28)
    ble CGameCoin_Update_L_8012D768
    lwz r3, 0xc(r28)
    li r4, 0x5f
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventClear
    lwz r3, 0x10(r28)
    li r4, 0x5f
    bl TornadoEffect_ApplyItemVisual_Primary
    lfs f0, lbl_806D71BC(r2)
    stfs f0, 0x98(r28)
    CGameCoin_Update_L_8012D768:
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0xc(r28)
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x10(r28)
    bl TornadoEffect_Tick
    lwz r3, 0x14(r28)
    bl SoundVolumePan_Update
    fneg f1, f31
    lwz r3, 0x48(r28)
    bl fn_8012A71C
    lwz r3, 0xc(r28)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_TickTornadoCooldown
    lfs f1, lbl_806D7150(r2)
    addi r3, r1, 0x68
    lfs f0, lbl_806D715C(r2)
    mr r4, r3
    stfs f1, 0x50(r1)
    stfs f1, 0x44(r1)
    stfs f1, 0x54(r1)
    stfs f1, 0x48(r1)
    stfs f0, 0x58(r1)
    stfs f0, 0x4c(r1)
    lfs f0, 0x1c(r28)
    stfs f0, 0x68(r1)
    lfs f0, 0x2c(r28)
    stfs f0, 0x6c(r1)
    lfs f0, 0x3c(r28)
    stfs f0, 0x70(r1)
    lfs f0, 0x20(r28)
    stfs f0, 0x5c(r1)
    lfs f0, 0x30(r28)
    stfs f0, 0x60(r1)
    lfs f0, 0x40(r28)
    stfs f0, 0x64(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x5c
    mr r4, r3
    bl Vec3_Normalize
    lfs f7, lbl_806D71D8(r2)
    addi r4, r1, 0x50
    lfs f1, 0x60(r1)
    lfs f0, 0x54(r1)
    lfs f2, 0x5c(r1)
    fnmsubs f5, f7, f1, f0
    lfs f1, 0x50(r1)
    lfs f0, lbl_806D71DC(r2)
    fnmsubs f6, f7, f2, f1
    lfs f4, 0x64(r1)
    lfs f3, 0x58(r1)
    lfs f1, 0x48(r1)
    fadds f2, f5, f0
    lfs f0, lbl_806D71E0(r2)
    fnmsubs f3, f7, f4, f3
    stfs f5, 0x54(r1)
    fadds f0, f1, f0
    stfs f6, 0x50(r1)
    stfs f3, 0x58(r1)
    stfs f2, 0x54(r1)
    stfs f0, 0x48(r1)
    lwz r3, 0x58(r28)
    bl CObj_LoadIntoGX
    lwz r3, 0x58(r28)
    addi r4, r1, 0x44
    bl CObj_ApplyViewport
    b CGameCoin_Update_L_8012D924
    CGameCoin_Update_L_8012D880:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D924
    lfs f1, lbl_806D7140(r2)
    addi r3, r28, 0x18
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, lbl_806D718C(r2)
    addi r3, r1, 0x110
    li r4, 0x59
    bl PSMTXRotRad
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, 0x74(r1)
    addi r3, r1, 0x110
    lfs f2, 0x78(r1)
    lfs f3, 0x7c(r1)
    bl PSMTXTrans
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0xc(r28)
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x10(r28)
    bl TornadoEffect_Tick
    lwz r3, 0x48(r28)
    lfs f1, lbl_806D7150(r2)
    bl fn_8012A71C
    lwz r3, 0x5c(r28)
    addi r5, r28, 0x18
    lwz r4, 0x58(r28)
    bl ChallengeGoalCamera_Update
    CGameCoin_Update_L_8012D924:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0x50(r28)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x54(r28)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0xc0(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x70(r28)
    bl fn_8016DA78
    lwz r3, 0x74(r28)
    bl fn_8016EC80
    lwz r3, 0xa4(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E4(r2)
    bl fn_80182B50
    lwz r3, 0xa8(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lwz r3, 0xac(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lfs f2, 0xb8(r28)
    lfs f1, lbl_806D71EC(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0xb8(r28)
    lfs f1, 0xb8(r28)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D9B8
    fsubs f0, f1, f0
    stfs f0, 0xb8(r28)
    CGameCoin_Update_L_8012D9B8:
    lfs f2, 0xbc(r28)
    lfs f1, lbl_806D71F4(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0xbc(r28)
    lfs f1, 0xbc(r28)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D9E4
    fsubs f0, f1, f0
    stfs f0, 0xbc(r28)
    CGameCoin_Update_L_8012D9E4:
    lwz r27, 0xb0(r28)
    lfs f29, 0xb8(r28)
    cmplwi r27, 0x0
    bne CGameCoin_Update_L_8012DA04
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b8
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA04:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DA20
    addi r5, r31, 0x528
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b9
    bl __assert
    CGameCoin_Update_L_8012DA20:
    stfs f29, 0x20(r27)
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 6, 6
    bne CGameCoin_Update_L_8012DA78
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012DA78
    bne CGameCoin_Update_L_8012DA4C
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA4C:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012DA68
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012DA68
    li r3, 0x1
    CGameCoin_Update_L_8012DA68:
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012DA78
    mr r3, r27
    bl HSD_JObjSetMtxDirtySub
    CGameCoin_Update_L_8012DA78:
    lwz r27, 0xb4(r28)
    lfs f29, 0xbc(r28)
    cmplwi r27, 0x0
    bne CGameCoin_Update_L_8012DA98
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b8
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA98:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DAB4
    addi r5, r31, 0x528
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b9
    bl __assert
    CGameCoin_Update_L_8012DAB4:
    stfs f29, 0x20(r27)
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 6, 6
    bne CGameCoin_Update_L_8012DB0C
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012DB0C
    bne CGameCoin_Update_L_8012DAE0
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DAE0:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012DAFC
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012DAFC
    li r3, 0x1
    CGameCoin_Update_L_8012DAFC:
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012DB0C
    mr r3, r27
    bl HSD_JObjSetMtxDirtySub
    CGameCoin_Update_L_8012DB0C:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DBA8
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012DBA8
    lwz r3, 0x70(r28)
    bl fn_8016DF50
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DB5C
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x7e(r28)
    li r4, 0x0
    stb r0, 0x7f(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    b CGameCoin_Update_L_8012DBA8
    CGameCoin_Update_L_8012DB5C:
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7150(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012DBA8
    lfs f0, lbl_806D71F8(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge CGameCoin_Update_L_8012DBA8
    stfs f1, g_raceTimeRemaining(r13)
    li r0, 0x1
    li r3, 0x0
    li r4, 0x0
    stb r0, 0x7e(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    CGameCoin_Update_L_8012DBA8:
    lwz r3, 0x68(r28)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x68(r28)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012DBCC
    li r3, 0x0
    CGameCoin_Update_L_8012DBCC:
    bl TransitionEffect_Tick
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012E600
    lwz r0, 0x80(r28)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DD44
    lwz r3, 0x70(r28)
    li r29, 0x0
    bl fn_8016DEF4
    mr r30, r3
    bl NokoNokoChallenge_GetCoinDivisor
    cmplwi r3, 0x0
    beq CGameCoin_Update_L_8012DC30
    cmpwi r30, 0x0
    ble CGameCoin_Update_L_8012DC24
    cmpwi r30, 0x4
    bgt CGameCoin_Update_L_8012DC24
    slwi r0, r30, 2
    add r3, r3, r0
    lwz r29, -0x4(r3)
    b CGameCoin_Update_L_8012DC28
    CGameCoin_Update_L_8012DC24:
    li r29, 0x0
    CGameCoin_Update_L_8012DC28:
    mr r3, r29
    bl SetCoinCount
    CGameCoin_Update_L_8012DC30:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012DCB4
    lwz r4, 0x6c(r28)
    li r0, 0x4
    li r3, 0x37
    stw r0, 0x14(r4)
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DC64
    li r3, 0x37
    bl fn_8016C394
    CGameCoin_Update_L_8012DC64:
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    mr r30, r3
    mr r3, r28
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x68(r28)
    mr r6, r30
    li r4, 0x1
    bl fn_80253C74
    lwz r3, 0x78(r28)
    lwz r3, 0xc(r3)
    bl SetCourseScene3D
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b CGameCoin_Update_L_8012DD30
    CGameCoin_Update_L_8012DCB4:
    lwz r4, 0x6c(r28)
    li r0, 0x4
    li r3, 0x37
    stw r0, 0x14(r4)
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DCDC
    li r3, 0x37
    bl fn_8016C394
    CGameCoin_Update_L_8012DCDC:
    lwz r3, 0x48(r28)
    bl fn_8012BDA4
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    mr r30, r3
    mr r3, r28
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x68(r28)
    mr r6, r30
    li r4, 0x0
    bl fn_80253C74
    lwz r3, 0x58(r28)
    li r4, 0x1
    bl Object_SetByte10_Return1
    li r3, 0x0
    bl fn_8016C554
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    CGameCoin_Update_L_8012DD30:
    lbz r5, 0x7f(r28)
    mr r3, r28
    mr r4, r29
    bl NokoNokoChallenge_SaveResult
    b CGameCoin_Update_L_8012DD58
    CGameCoin_Update_L_8012DD44:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012DD58
    lwz r3, 0x78(r28)
    bl DefeatDemo_Update
    CGameCoin_Update_L_8012DD58:
    lwz r3, 0x80(r28)
    addi r0, r3, 0x1
    stw r0, 0x80(r28)
    lwz r0, 0x80(r28)
    cmpwi r0, 0xc8
    bne CGameCoin_Update_L_8012E5E4
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E5E4
    lwz r3, 0x78(r28)
    addi r4, r1, 0x2c
    lwz r3, 0xc(r3)
    bl CObj_ApplyScissor
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DEF0
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DDD0
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012DDD0:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DDF0
    li r3, 0x0
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DDF0:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE04
    li r3, 0x1
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE04:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE18
    li r3, 0x2
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE18:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE2C
    li r3, 0x3
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE2C:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE40
    li r3, 0x4
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE40:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE50
    li r3, 0x5
    CGameCoin_Update_L_8012DE50:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7138(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7138(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012DEF0:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E054
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DF34
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012DF34:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF54
    li r3, 0x0
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF54:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF68
    li r3, 0x1
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF68:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF7C
    li r3, 0x2
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF7C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF90
    li r3, 0x3
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF90:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DFA4
    li r3, 0x4
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DFA4:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DFB4
    li r3, 0x5
    CGameCoin_Update_L_8012DFB4:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D71FC(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D71FC(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E054:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E1B8
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E098
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E098:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0B8
    li r3, 0x0
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0B8:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0CC
    li r3, 0x1
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0CC:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0E0
    li r3, 0x2
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0E0:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0F4
    li r3, 0x3
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0F4:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E108
    li r3, 0x4
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E108:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E118
    li r3, 0x5
    CGameCoin_Update_L_8012E118:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D716C(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D716C(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E1B8:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E31C
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E1FC
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E1FC:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E21C
    li r3, 0x0
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E21C:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E230
    li r3, 0x1
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E230:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E244
    li r3, 0x2
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E244:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E258
    li r3, 0x3
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E258:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E26C
    li r3, 0x4
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E26C:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E27C
    li r3, 0x5
    CGameCoin_Update_L_8012E27C:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7200(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7200(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E31C:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E480
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E360
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E360:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E380
    li r3, 0x0
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E380:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E394
    li r3, 0x1
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E394:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3A8
    li r3, 0x2
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3A8:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3BC
    li r3, 0x3
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3BC:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3D0
    li r3, 0x4
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3D0:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3E0
    li r3, 0x5
    CGameCoin_Update_L_8012E3E0:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7204(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7204(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E480:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E5E4
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E4C4
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E4C4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E4E4
    li r3, 0x0
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E4E4:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E4F8
    li r3, 0x1
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E4F8:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E50C
    li r3, 0x2
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E50C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E520
    li r3, 0x3
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E520:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E534
    li r3, 0x4
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E534:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E544
    li r3, 0x5
    CGameCoin_Update_L_8012E544:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7208(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7208(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E5E4:
    lwz r3, 0x68(r28)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E658
    mr r3, r28
    bl NokoNokoChallenge_TransitionToResult
    b CGameCoin_Update_L_8012E670
    CGameCoin_Update_L_8012E600:
    lwz r3, 0x58(r28)
    addi r4, r1, 0x50
    bl CObj_LoadProjMatrix
    lwz r3, 0x58(r28)
    addi r4, r1, 0x44
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x44(r1)
    addi r3, r1, 0x20
    lwz r8, 0x48(r1)
    addi r4, r1, 0x14
    lwz r7, 0x4c(r1)
    lwz r6, 0x50(r1)
    lwz r5, 0x54(r1)
    lwz r0, 0x58(r1)
    stw r9, 0x14(r1)
    stw r8, 0x18(r1)
    stw r7, 0x1c(r1)
    stw r6, 0x20(r1)
    stw r5, 0x24(r1)
    stw r0, 0x28(r1)
    bl VfxSlotMgr_Update
    CGameCoin_Update_L_8012E658:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Update_L_8012E668
    bl fn_8016B32C
    CGameCoin_Update_L_8012E668:
    bl RumbleUpdate
    li r3, -0x2
    CGameCoin_Update_L_8012E670:
    psq_l f31, 0x1b8(r1), 0, 0
    lfd f31, 0x1b0(r1)
    psq_l f30, 0x1a8(r1), 0, 0
    lfd f30, 0x1a0(r1)
    psq_l f29, 0x198(r1), 0, 0
    lfd f29, 0x190(r1)
    lmw r25, 0x174(r1)
    lwz r0, 0x1c4(r1)
    mtlr r0
    addi r1, r1, 0x1c0
    blr
}
#endif


static inline void CoinJObj_SetMtxDirty(CoinJObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D7174, 0x25D, lbl_806D717C);
        }
        flags = jobj->flags;
        dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (!dirty) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void CoinJObj_SetRotationY(CoinJObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x2B8, lbl_806D717C);
    }
    if (jobj->flags & 0x00020000) {
        __assert(lbl_806D7174, 0x2B9, DefeatDemo_Update_rodata_80356C58);
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleX(CoinJObj *jobj, float x) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x325, lbl_806D717C);
    }
    jobj->scale.x = x;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleY(CoinJObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x333, lbl_806D717C);
    }
    jobj->scale.y = y;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleZ(CoinJObj *jobj, float z) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x341, lbl_806D717C);
    }
    jobj->scale.z = z;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinScene3D_SetAnimFrame(CoinScene3D *scene, float frame) {
    if (scene->animFrame < 0.0f || frame < 0.0f) {
        return;
    }
    scene->animFirst = 1;
    scene->animFrame = frame;
}

static inline void CoinScene3D_UpdateAnim(CoinScene3D *scene) {
    if (scene->animSpeed == -1.0f) {
        return;
    }
    if (scene->animFirst) {
        scene->animFirst = 0;
    } else {
        scene->animFrame += scene->animSpeed;
    }
    HSD_CObjReqAnim(scene->cobj, scene->animFrame);
    HSD_CObjAnim(scene->cobj);
}

extern "C" void DefeatDemo_Update(DefeatDemo *self) { /* 0x8012E69C size:0x5A8 */
    float s;

    if (self->first == 1) {
        self->first = 0;
    } else {
        self->frame += 1.0f;
        if (self->frame >= 270.0f) {
            self->frame = 269.0f;
        }
    }
    if (self->frame == 180.0f && g_characterId != 4) {
        SoundMgr_Play(0x13B);
    }
    CoinScene3D_SetAnimFrame(self->scene, self->frame);
    CoinScene3D_UpdateAnim(self->scene);
    Object_SetField8_AndDirty(self->body, self->frame);
    clNormal3D_Exec(self->body);
    Object_SetField8_AndDirty(self->hand, self->frame);
    clNormal3D_Exec(self->hand);
    Object_SetField8_AndDirty(self->effect, self->frame);
    clNormal3D_Exec(self->effect);
    fn_80182B50(self->spinA, 0.0f, 0.002f);
    fn_80182B50(self->spinB, 0.0f, -0.002f);
    fn_80182B50(self->spinC, 0.0f, -0.002f);
    self->wheelAngleA += 0.00087266444f;
    if (self->wheelAngleA >= 6.283184f) {
        self->wheelAngleA -= 6.283184f;
    }
    self->wheelAngleB += 0.0005817763f;
    if (self->wheelAngleB >= 6.283184f) {
        self->wheelAngleB -= 6.283184f;
    }
    CoinJObj_SetRotationY(self->wheelA, self->wheelAngleA);
    CoinJObj_SetRotationY(self->wheelB, self->wheelAngleB);
    if (self->frame < 192.0f || self->frame > 230.0f) {
        HSD_JObjSetFlagsAll(self->flash, 0x10);
    } else {
        HSD_JObjClearFlagsAll(self->flash, 0x10);
        s = Saturate_Double((self->frame - 192.0f) / 3.0f, 0.0f, 1.0f);
        CoinJObj_SetScaleX(self->flash, 0.5f * s + 0.5f);
        CoinJObj_SetScaleZ(self->flash, 0.5f * s + 0.5f);
        if (self->frame < 198.0f) {
            CoinJObj_SetScaleY(self->flash, 8.0f * Saturate_Double((self->frame - 192.0f) / 6.0f, 0.0f, 1.0f) + 1.0f);
        } else {
            CoinJObj_SetScaleY(self->flash, 9.0f - 8.8f * Saturate_Double((self->frame - 198.0f) / 32.0f, 0.0f, 1.0f));
        }
    }
}


static inline void KoopaFireball_SetActive(KoopaFireball *fb, unsigned char on) {
    if (fb->active != on) {
        fb->active = on;
        if (fb->active) {
            fb->cooldown = 0;
            fb->first = 1;
        }
    }
}

static inline float BossKoopa_Rand64(BossKoopa *self) {
    if (self->waitRndIdx >= 64) {
        self->waitRndIdx = 0;
    }
    return lbl_80495994[self->waitRndIdx++];
}

static inline float BossKoopa_Rand48(BossKoopa *self) {
    if (self->attackRndIdx >= 48) {
        self->attackRndIdx = 0;
    }
    return lbl_80495A94[self->attackRndIdx++];
}

extern "C" void BossKoopa_UpdateAnim(BossKoopa *self) { /* 0x8012EC44 size:0x438 */
    float r;
    float t;

    if (self->state != self->reqState) {
        self->state = self->reqState;
        self->frame = 0.0f;
        self->justChanged = 1;
        self->timer = 0.0f;
        if (self->state == 0) {
            self->wait = (int)((self->waitMax - self->waitMin) * BossKoopa_Rand64(self) + self->waitMin);
        }
    }
    if (self->state == 4) {
        return;
    }
    if (self->justChanged) {
        self->justChanged = 0;
    } else {
        self->timer += 1.0f;
    }
    switch (self->state) {
    case 0:
        if (self->timer >= 60.0f) {
            self->timer = 0.0f;
        }
        self->frame = self->timer;
        if (IsRaceStarted()) {
            if (self->wait > 0) {
                self->wait--;
            } else {
                self->reqState = 1;
                r = BossKoopa_Rand48(self);
                if (r < 0.5f) {
                    self->attack = 0;
                } else if (r < 0.75f) {
                    self->attack = 1;
                } else {
                    self->attack = 2;
                }
            }
        }
        break;
    case 1:
        switch (self->attack) {
        case 0:
            self->frame = self->timer;
            if (self->timer > 198.0f) {
                self->reqState = 0;
            }
            break;
        case 1:
            self->frame = 1.2f * self->timer;
            if (self->timer > 165.0f) {
                self->reqState = 0;
            }
            break;
        case 2:
            t = self->timer;
            if (t < 60.0f) {
                self->frame = t;
            } else {
                self->frame = 0.75f * (t - 60.0f) + 60.0f;
            }
            if (self->timer > 244.0f) {
                self->reqState = 0;
            }
            break;
        case 3:
            t = self->timer;
            if (t <= 150.0f) {
                self->frame = t;
            } else if (t <= 200.0f) {
                self->frame = 150.0f - (t - 150.0f);
            } else {
                self->frame = t - 100.0f;
            }
            if (self->timer > 298.0f) {
                self->reqState = 0;
            }
            break;
        }
        break;
    case 2:
    case 3:
        self->frame = self->timer;
        if (self->timer >= 69.0f) {
            self->reqState = 1;
            self->attack = 3;
        }
        break;
    }
    Object_SetField8_AndDirty(self->anims[self->state], self->frame);
    clNormal3D_Exec(self->anims[self->state]);
    if (self->state == 1 && self->frame >= 60.0f && self->frame <= 150.0f) {
        KoopaFireball_SetActive(self->fireball, 1);
        if (!fn_8016C360(0x37)) {
            SoundMgr_PlaySE(0x37);
        }
    } else {
        KoopaFireball_SetActive(self->fireball, 0);
        if (fn_8016C360(0x37) == 1) {
            fn_8016C394(0x37);
        }
    }
    KoopaFireball_Update(self->fireball);
}

static inline void CoinJObj_SetupMatrix(CoinJObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    if (jobj == 0) {
        __assert(lbl_806D7174, 0x47C, lbl_806D717C);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D7174, 0x25D, lbl_806D717C);
        }
        flags = jobj->flags;
        dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline float (*CoinJObj_GetMtxPtr(CoinJObj *jobj))[4] {
    CoinJObj_SetupMatrix(jobj);
    return jobj->mtx;
}

static inline float KoopaFireball_Rand64(KoopaFireball *self) {
    if (self->rnd64 >= 64) {
        self->rnd64 = 0;
    }
    return lbl_80495994[self->rnd64++];
}

static inline float KoopaFireball_Rand48(KoopaFireball *self) {
    if (self->rnd48 >= 48) {
        self->rnd48 = 0;
    }
    return lbl_80495A94[self->rnd48++];
}

extern "C" void KoopaFireball_Update(KoopaFireball *self) { /* 0x8012F07C size:0x3E0 */
    float (*mtx)[4];
    int i;
    float m[3][4];
    CoinVec d;
    float dot;

    if (self->jobj == 0) {
        return;
    }
    if (self->cooldown != 0) {
        self->cooldown--;
    }
    if (self->active) {
        mtx = CoinJObj_GetMtxPtr(self->jobj);
        for (i = 0; i < 64; i++) {
            if (self->flames[i].life < 0.0f) {
                self->flames[i].pos.x = mtx[0][3];
                self->flames[i].pos.y = mtx[1][3];
                self->flames[i].pos.z = mtx[2][3];
                self->flames[i].vel.x = mtx[0][2];
                self->flames[i].vel.y = mtx[1][2];
                self->flames[i].vel.z = mtx[2][2];
                PSMTXRotRad(m, 'X', 0.017453292f * self->angle);
                PSMTXMultVec(m, &self->flames[i].vel, &self->flames[i].vel);
                self->flames[i].scale = KoopaFireball_Update_data_806CF57C * KoopaFireball_Rand64(self) + KoopaFireball_Update_data_806CF578;
                self->flames[i].grow = KoopaFireball_Update_data_806CF588 * KoopaFireball_Rand48(self) + KoopaFireball_Update_data_806CF584;
                self->flames[i].alpha = 1.0f - 0.2f * KoopaFireball_Rand48(self);
                if (self->cooldown != 0) {
                    self->flames[i].alpha *= 0.5f;
                }
                self->flames[i].life = 0.0f;
                if (self->cooldown == 0) {
                    if (self->first) {
                        self->cooldown = KoopaFireball_Update_bss_806D1510;
                        self->first = 0;
                        self->dir.x = mtx[0][2];
                        self->dir.y = mtx[1][2];
                        self->dir.z = mtx[2][2];
                        Vec3_Normalize(&self->dir, &self->dir);
                    } else {
                        d.x = mtx[0][2];
                        d.y = mtx[1][2];
                        d.z = mtx[2][2];
                        Vec3_Normalize(&d, &d);
                        dot = Vec3_Dot(&d, &self->dir);
                        if (dot < 0.0f) {
                            dot = -dot;
                        }
                        if (dot > 0.999f) {
                            self->cooldown = KoopaFireball_Update_bss_806D1510;
                        } else {
                            self->cooldown = 0;
                        }
                        self->dir.x = d.x;
                        self->dir.y = d.y;
                        self->dir.z = d.z;
                    }
                }
                break;
            }
        }
    }
    for (i = 0; i < 64; i++) {
        if (self->flames[i].life >= 0.0f) {
            self->flames[i].pos.x += self->flames[i].vel.x * KoopaFireball_Update_data_806CF580;
            self->flames[i].pos.y += self->flames[i].vel.y * KoopaFireball_Update_data_806CF580;
            self->flames[i].pos.z += self->flames[i].vel.z * KoopaFireball_Update_data_806CF580;
            if (self->flames[i].vel.y < 0.5f) {
                self->flames[i].vel.y += 0.01f;
                if (self->flames[i].vel.y > 0.5f) {
                    self->flames[i].vel.y = 0.5f;
                }
            }
            self->flames[i].scale += self->flames[i].grow;
            if ((self->flames[i].life += 1.0f) >= 64.0f) {
                self->flames[i].life = -1.0f;
            }
        }
    }
}

struct CoinShell {
    void *effect;
    int m4;
    int state;
    float t;
    float mtx[3][4];
    float alpha;
    CoinJObj *joint;
    void *ground;
    unsigned char landed;
    unsigned char pad4D[0xF];
    CoinVec vel;
    float speed;
};

static inline void Shell_AttachToJoint(CoinShell *self) {
    float (*jm)[4];
    float m[3][4];

    if (self->joint != 0) {
        jm = CoinJObj_GetMtxPtr(self->joint);
        PSMTXCopy(jm, self->mtx);
        PSMTXRotRad(m, 'Z', -1.5707964f);
        PSMTXConcat(self->mtx, m, self->mtx);
        PSMTXScale(m, 1.0f, 1.0f, 1.0f);
        PSMTXConcat(self->mtx, m, self->mtx);
        self->mtx[0][3] = 2.5f * self->mtx[0][1] + jm[0][3];
        self->mtx[1][3] = 2.5f * self->mtx[1][1] + jm[1][3];
        self->mtx[2][3] = 2.5f * self->mtx[2][1] + jm[2][3];
    }
}

static inline void Shell_UpdateRolling(CoinShell *self) {
    CoinVec pos;
    float m[3][4];

    self->t += 1.0f;
    pos.x = self->mtx[0][3];
    pos.y = self->mtx[1][3];
    pos.z = self->mtx[2][3];
    PSMTXScale(m, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(self->mtx, m, self->mtx);
    PSMTXRotRad(m, 'Y', 0.5235988f);
    PSMTXConcat(self->mtx, m, self->mtx);
    pos.x = self->vel.x * self->speed + pos.x;
    pos.y = self->vel.y * self->speed + pos.y;
    pos.z = self->vel.z * self->speed + pos.z;
    self->mtx[0][3] = pos.x;
    self->mtx[1][3] = pos.y;
    self->mtx[2][3] = pos.z;
    if (!self->landed) {
        if (fn_80123480(self->ground, &pos) == 1) {
            self->landed = 1;
        }
    } else if (pos.y < -110.0f || !fn_80123480(self->ground, &pos)) {
        self->state = 5;
        self->t = 0.0f;
    }
}

extern "C" void Shell_UpdateState(CoinShell *self) { /* 0x8012F45C size:0x458 */
    if (self->state == 0) {
        return;
    }
    switch (self->state) {
    case 3:
        Shell_AttachToJoint(self);
        if (self->t < 60.0f) {
            self->t += 1.0f;
            self->alpha = Saturate_Double(self->t / 60.0f, 0.0f, 1.0f);
        }
        break;
    case 1:
        self->mtx[1][3] -= 0.2f;
        break;
    case 4:
        Shell_UpdateRolling(self);
        break;
    case 5:
        if (self->t < 30.0f) {
            self->t += 1.0f;
            self->alpha = -self->alpha * (self->t / 30.0f) + self->alpha;
        } else {
            self->state = 0;
            self->t = 0.0f;
            self->alpha = 0.0f;
        }
        break;
    case 6:
        if (self->t < 30.0f) {
            self->t += 1.0f;
            Shell_AttachToJoint(self);
            self->alpha = -self->alpha * (self->t / 30.0f) + self->alpha;
        } else {
            self->state = 0;
            self->t = 0.0f;
            self->alpha = 0.0f;
        }
        break;
    }
    fn_80172844(self->effect);
}

struct CoinHsdClassInfo {
    unsigned char pad0[0x30];
    void (*release)(struct CoinHsdObj *o);
    void (*destroy)(struct CoinHsdObj *o);
};

struct CoinHsdObj {
    CoinHsdClassInfo *info;
    unsigned short ref;
};

static inline int CoinHsdObj_RefDec(CoinHsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void CoinHsdObj_Unref(CoinHsdObj *o) {
    if (o == 0) {
        return;
    }
    if (CoinHsdObj_RefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}


static inline void CoinShellSet_Delete(CoinShellSet *set) {
    if (set != 0) {
        fn_80173550(set->model, 1);
        Object_DtorWithGXSync(set->jobj, 1);
        fn_80123B48(set->shells, 1);
        MemoryManager_TimedFree(set);
    }
}

static inline void KoopaFireball_Delete(KoopaFireball *fireball) {
    if (fireball != 0) {
        Object_DtorWithGXSync(fireball->model, 1);
        MemoryManager_TimedFree(fireball);
    }
}

static inline void BossKoopa_Delete(BossKoopa *koopa) {
    int i;

    if (koopa != 0) {
        KoopaFireball_Delete(koopa->fireball);
        for (i = 0; i < 4; i++) {
            Object_DtorWithGXSync(koopa->anims[i], 1);
        }
        if (fn_8016C360(0x37) == 1) {
            fn_8016C394(0x37);
        }
        MemoryManager_TimedFree(koopa);
    }
}

static inline void DefeatDemo_Delete(DefeatDemo *demo) {
    if (demo != 0) {
        Object_DtorWithGXSync(demo->body, 1);
        Object_DtorWithGXSync(demo->hand, 1);
        Object_DtorWithGXSync(demo->effect, 1);
        delete demo->scene;
        MemoryManager_TimedFree(demo);
    }
}

extern "C" CGameCoin *CGameCoin_Destroy(CGameCoin *self, short flag) { /* 0x8012F8B4 size:0x3A4 */

    if (self) {
        self->vt = vtable;
        delete self->particles;
        fn_80169C44();
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        SetCourseScene3D(0);
        delete self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCam, 1);
        SetPlayerCarObject(0);
        KartDriver_Dtor(self->driver, 1);
        VisualEffectHolder_Dtor(self->effects, 1);
        AudioChannel_DtorWithSeStop(self->audio, 1);
        fn_8012B394(self->m48, 1);
        InputCmd_Dtor(self->input, 1);
        g_raceCamera = 0;
        if (self->m60 != 0) {
            delete self->m60;
        }
        if (self->lights != 0) {
            CoinHsdObj_Unref(self->lights);
        }
        CourseEnvironment_Dtor(self->env, 1);
        fn_80254134(self->hud, 1);
        CoinShellSet_Delete(self->shellSet);
        BossKoopa_Delete(self->koopa);
        fn_8016DFAC(self->m70, 1);
        fn_8016EFA8(self->m74, 1);
        DefeatDemo_Delete(self->defeatDemo);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        RankingTable_Init(GetRaceContextPtr());
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        dtor_80122FD8(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct CoinInputView {
    void **vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    int fields[8];
};
static inline CoinInputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}
static inline void CreateInputState(void)
{
    CoinInputView *p = (CoinInputView *)Alloc(0x28);
    if (p != 0) {
        p->vt = lbl_803FDF28;
        g_pInputState = p;
        p->vt = lbl_803FDF40;
        p->enabled = 0;
        p->flag5 = 1;
        p->flag6 = 1;
        p->fields[0] = 0;
        p->fields[1] = 0;
        p->fields[2] = 0;
        p->fields[3] = 0;
        p->fields[4] = 0;
        p->fields[5] = 0;
        p->fields[6] = 0;
        p->fields[7] = 0;
    }
}

#include "game/types/InputManager.h"
struct InputCmd { char data[0x30]; InputCmd(int frames); };
struct KartDriver {
    char pad0[0x238];
    int x238;
    char pad23C[0x384 - 0x23C];
    KartDriver(int disp, int chara, void *start, int a, int b, int c);
};
struct PlayerDriver : KartDriver {
    PlayerDriver(int chara, void *start) : KartDriver(GetDisplayBufferIndex(), chara, start, 0, 0, 0) {}
};
struct TornadoEffect {
    char data[0x154];
    TornadoEffect(int a, KartDriver *drv, int chara, int b, float x, float y, float z);
};
struct KartAudioChannel { char data[0x38]; KartAudioChannel(int chara, int a, int b, int c, int d); };
struct KPRival {
    char pad0[0x164];
    int x164;
    KPRival(int chara, void *start);
};
#include "game/types/LakituStart.h"
#include "game/types/Scene3D.h"
#include "game/types/ChallengeGoalCamera.h"
#include "game/types/HUD.h"
#include "game/types/WeatherSystem.h"
struct KPShellPath { char data[0x20]; KPShellPath(); };
struct KPShellTrack { int data; KPShellTrack(const void *path, int arg); };
struct KPUnk70 { char data[0x10]; KPUnk70(); };
struct KPUnk74 { char data[0x898]; KPUnk74(); };

struct ShotVec {
    float x, y, z;
    void Zero() { x = y = z = lbl_806D7150; }
};
struct CoinShotTrail { int age; ShotVec pos; };
struct CoinShot {
    int active;
    int x4;
    int timer;
    ShotVec pos;
    ShotVec vel;
    float rot;
    float alpha;
    CoinShotTrail trail[20];
};

struct CoinShotBase {
    virtual ~CoinShotBase();
    CoinNormal3D *model;
    CoinNormal3D *trailModel;
    int xC;
    int x10;
    CoinShot shots[6];
    int trailCount;
    CoinShotBase(const char *modelFile, const char *trailFile, int trails);
};

inline CoinShotBase::CoinShotBase(const char *modelFile, const char *trailFile, int trails) {
    xC = 0;
    x10 = 0;
    trailCount = trails;
    model = new CoinNormal3D(modelFile, 1);
    clNormal3D_SetFlags(model, 0x40000000, 0);
    trailModel = new CoinNormal3D(trailFile, 1);
    HSD_JObjSetFlags(Archive_GetRootJObj(trailModel), 0x200);
    for (int i = 0; i < 6; i++) {
        shots[i].active = 0;
        shots[i].timer = 0;
        shots[i].rot = lbl_806D7150;
        shots[i].alpha = lbl_806D7150;
        shots[i].x4 = 0;
        shots[i].pos.Zero();
        shots[i].vel.Zero();
        for (int j = 0; j < 20; j++) {
            shots[i].trail[j].age = -1;
        }
    }
    if (trailCount >= 20) {
        trailCount = 19;
    }
}

struct KPCoinShots : CoinShotBase {
    KPCoinShots(const char *modelFile, const char *trailFile) : CoinShotBase(modelFile, trailFile, 7) {}
    virtual ~KPCoinShots();
};


struct KPShell {
    KPShellPath *path;
    CoinNormal3D *model;
    int x8;
    float xC;
    char pad10[0x30];
    float x40;
    int x44;
    KPShellTrack *track;
    unsigned char x4C;
    float x50, x54, x58;
    char pad5C[0xC];
    float speed;
    KPShell(int target, float spd) {
        path = 0;
        model = 0;
        x8 = 0;
        xC = lbl_806D7150;
        x40 = lbl_806D7150;
        x44 = 0;
        track = 0;
        x4C = 0;
        x50 = lbl_806D7150;
        x54 = lbl_806D7150;
        x58 = lbl_806D7150;
        path = new KPShellPath;
        model = new CoinNormal3D(s_shellFile, 1);
        clNormal3D_SetFlags(model, 0x40000000, 0);
        x44 = target;
        speed = spd;
        track = new KPShellTrack(s_shellPathData, 1);
    }
};

#include "game/types/GameModeBase.h"

struct ModeBase : GameModeBase {
    float x4;
    ModeBase() {
        x4 = lbl_806D7150;
    }
    virtual void _key2();
    virtual ~ModeBase();
};


struct KPCourseData {
    int x0;
    float speed;
    int x8;
    int xC;
};

struct KPCoinMode : ModeBase {
    virtual void _key3();
    InputCmd *cmd;
    KartDriver *driver;
    TornadoEffect *tornado;
    KartAudioChannel *audio;
    char start[0x30];
    KPRival *rival;
    KPShell *shell;
    LakituStart *lakitu;
    InputManager *env;
    Scene3D *scene;
    ChallengeGoalCamera *goalCam;
    int x60;
    int x64;
    HUD *hud;
    BossKoopa *koopa;
    KPUnk70 *x70;
    KPUnk74 *x74;
    DefeatDemo *demo;
    char pad7C[8];
    KPCourseData *course;
    char pad88[0x1C];
    void *lavaJoint[3];
    void *skydome;
    void *skycloud;
    char padB8[8];
    KPCoinShots *shots;
    KPCoinMode();
};

KPCoinMode::KPCoinMode() {
    float x, y, z;

    CGameCoin_InitFields((CGameCoinFields *)this);
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    env = new InputManager;
    x60 = 0;
    x64 = 0;
    g_raceCamera = 0;
    ProcessSystemTick(0);
    cmd = new InputCmd(0x3C);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetStartPosition(0, &x, &y, &z);
    driver = new PlayerDriver(g_characterId, start);
    driver->x238 = 1;
    tornado = new TornadoEffect(1, driver, g_characterId, 1, lbl_806D7150, lbl_806D7150, lbl_806D7150);
    TireEffect_ResetSpin(tornado, lbl_806D7150, lbl_806D7140);
    TornadoEffect_SetColorPairC8CC(tornado, 1, 1);
    audio = new KartAudioChannel(g_characterId, 1, 1, 0, 0);
    KartAudioChannel_ResetSEsAndSetFlag(audio, 1);
    rival = new KPRival(g_characterId, start);
    lakitu = new LakituStart(s_lakituFile, 0, lbl_806D7150, lbl_806D7150, lbl_806D7150);
    scene = new Scene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new ChallengeGoalCamera;
    ProcessSystemTick(0);
    hud = new HUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    PreloadEffectResources(5);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    course = (KPCourseData *)MiniGame_GetCourseData();
    if (course == 0) {
        course = (KPCourseData *)s_defaultCourse;
    }
    shell = new KPShell(rival->x164, course->speed);
    koopa = new BossKoopa(course->x8, course->xC);
    x70 = new KPUnk70;
    x74 = new KPUnk74;
    demo = new DefeatDemo;
    lavaJoint[0] = CourseEnvironment_ResolveJointInSlot0(env, s_lavaJoint1);
    lavaJoint[1] = CourseEnvironment_ResolveJointInSlot0(env, s_lavaJoint2);
    lavaJoint[2] = CourseEnvironment_ResolveJointInSlot0(env, s_lavaJoint3);
    skydome = CourseEnvironment_ResolveJointInSlot0(env, s_skydomeJoint);
    skycloud = CourseEnvironment_ResolveJointInSlot0(env, s_skycloudJoint);
    shots = new KPCoinShots(s_coinFile, s_kiraFile);
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    InitRumbleController(0);
    SetResourceLoadingFlag(1);
    if (input_state() == 0) {
        CreateInputState();
    }
    StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
    StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
    {
        CoinInputView *in = input_state();
        in->enabled = 1;
        in->fields[4] = 0;
        in->fields[5] = 0;
    }
}

DefeatDemo::DefeatDemo() { /* 0x801303E4 size:0x2A8 */
    const char *pool = CGameCoin_8012BF5C_rodata_80356730;

    body = 0;
    hand = 0;
    effect = 0;
    scene = 0;
    frame = 0.0f;
    first = 1;
    spinA = 0;
    spinB = 0;
    spinC = 0;
    wheelA = 0;
    wheelB = 0;
    wheelAngleA = 0.0f;
    wheelAngleB = 0.0f;
    flash = 0;
    if (g_characterId == 4) {
        body = new CoinNormal3D(pool + 0x630, 0);
        hand = new CoinNormal3D(pool + 0x64C, 0);
    } else {
        body = new CoinNormal3D(pool + 0x630, 0);
        hand = new CoinNormal3D(pool + 0x664, 0);
    }
    effect = new CoinNormal3D(pool + 0x678, 0);
    clNormal3D_SetScale(body, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    clNormal3D_SetScale(hand, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    clNormal3D_SetScale(effect, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    scene = new CoinAnimScene3D(pool + 0x630);
    ((CoinAnimScene3D *)scene)->Start();
    spinA = ResolveJointByName(body, pool + 0x688);
    spinB = ResolveJointByName(body, pool + 0x6A4);
    spinC = ResolveJointByName(body, pool + 0x6C0);
    wheelA = ResolveJointByName(body, pool + 0x6DC);
    wheelB = ResolveJointByName(body, pool + 0x6FC);
    flash = ResolveJointByName(effect, pool + 0x71C);
}

#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)

BossKoopa::BossKoopa(int waitMin, int waitMax) { /* 0x8013068C size:0x3FC */
    const char *pool = CGameCoin_8012BF5C_rodata_80356730;

    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    anims[3] = 0;
    state = 0;
    reqState = 0;
    frame = 0.0f;
    justChanged = 1;
    timer = 0.0f;
    wait = 60;
    attack = 0;
    fireball = 0;
    waitRndIdx = OSTicksToSeconds(OSGetTick()) % 64;
    attackRndIdx = OSTicksToSeconds(OSGetTick()) % 48;
    this->waitMin = waitMin;
    this->waitMax = waitMax;
    fireball = new KoopaFireball(pool + 0x744);
    if (g_characterId == 4) {
        anims[0] = new CoinNormal3D(pool + 0x754, 0);
        anims[1] = new CoinNormal3D(pool + 0x770, 0);
        anims[2] = new CoinNormal3D(pool + 0x78C, 0);
        anims[3] = new CoinNormal3D(pool + 0x7AC, 0);
        fireball->jobj = ResolveJointByName(anims[1], pool + 0x7CC);
        fireball->angle = BossKoopa_Init_data_806CF574;
    } else {
        anims[0] = new CoinNormal3D(pool + 0x7F4, 0);
        anims[1] = new CoinNormal3D(pool + 0x808, 0);
        anims[2] = new CoinNormal3D(pool + 0x820, 0);
        anims[3] = new CoinNormal3D(pool + 0x838, 0);
        fireball->jobj = ResolveJointByName(anims[1], pool + 0x850);
        fireball->angle = BossKoopa_Init_data_806CF570;
    }
    clNormal3D_SetScale(anims[0], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[0], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[1], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[1], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[2], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[2], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[3], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[3], 0.0f, 15.0f, 40.0f);
}

struct CGameCoinFields {
    unsigned char pad0[0x8];
    int m8;
    int mC;
    int m10;
    int m14;
    float mtx[3][4];
    int m48;
    int m4C;
    int m50[11];
    unsigned char m7C;
    unsigned char m7D;
    unsigned char m7E;
    unsigned char m7F;
    int m80;
    int m84;
    int m88;
    int m8C;
    int m90;
    float m94;
    float m98;
    int m9C;
    float mA0;
    int mA4;
    int mA8;
    int mAC;
    int mB0;
    int mB4;
    float mB8;
    float mBC;
};

extern "C" void CGameCoin_InitFields(CGameCoinFields *self) { /* 0x80130A88 size:0xD4 */
    self->m8 = 0;
    self->mC = 0;
    self->m10 = 0;
    self->m14 = 0;
    PSMTXIdentity(self->mtx);
    self->m48 = 0;
    self->m4C = 0;
    self->m94 = -1.0f;
    self->m98 = -1.0f;
    self->m84 = 0;
    self->m9C = 0;
    self->mA0 = 0.0f;
    self->m88 = 2;
    self->m8C = 2;
    self->m50[0] = 0;
    self->m50[1] = 0;
    self->m50[2] = 0;
    self->m50[3] = 0;
    self->m50[4] = 0;
    self->m50[5] = 0;
    self->m50[6] = 0;
    self->m50[7] = 0;
    self->m50[8] = 0;
    self->m50[9] = 0;
    self->m50[10] = 0;
    self->m7C = 0;
    self->m7D = 0;
    self->m7E = 0;
    self->m7F = 0;
    self->m80 = 0;
    self->mA4 = 0;
    self->mA8 = 0;
    self->mAC = 0;
    self->mB0 = 0;
    self->mB4 = 0;
    self->mB8 = 0.0f;
    self->mBC = 0.0f;
}

struct CoinTrail {
    int t;
    float pos[3];
};

struct CoinParticle {
    int active;
    int m4;
    int timer;
    float pos[3];
    float vel[3];
    float rotY;
    float alpha;
    CoinTrail trail[20];
};

struct CoinParticleManager {
    void *vtbl;
    void *jobj;
    void *trailJobj;
    int sinIdx;
    int heightIdx;
    CoinParticle particles[6];
    int trailCount;
};

extern "C" void CoinParticle_Draw(CoinParticleManager *self) { /* 0x80130B5C size:0x1D0 */
    int i;
    int j;
    void *node;
    float t;
    float scale;

    for (i = 0; i < 6; i++) {
        if (self->particles[i].active != 0) {
            Object_SetJObjPositionVec(self->jobj, self->particles[i].pos);
            Object_SetJObjRotationY(self->jobj, 0.017453289f * self->particles[i].rotY);
            Object_SetJObjScaleXYZ(self->jobj, 1.2f, 1.2f, 1.2f);
            Object_SetColorAlphaOnly(self->jobj, 0, self->particles[i].alpha);
            Object_RenderJObjEx(self->jobj, LinkedNode_GetField10_OrFallback(self->jobj, 0), 7);
            node = LinkedNode_GetField10_OrFallback(self->jobj, 0);
            Object_RenderJObjEx(self->jobj, node == 0 ? 0 : *(void **)((char *)node + 8), 7);
            for (j = 0; j < self->trailCount; j++) {
                t = self->particles[i].trail[j].t / 10.0f;
                scale = 2.0f - t;
                Object_SetJObjPositionVec(self->trailJobj, self->particles[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailJobj, scale, scale, scale);
                Object_SetColorAlphaOnly(self->trailJobj, 0, (1.0f - t) * self->particles[i].alpha);
                Object_RenderJObjTree(self->trailJobj, 7);
            }
        }
    }
}

static inline unsigned char CoinTrail_Spawn(CoinTrail *tr, float angle, float height) {
    if (tr->t >= 0) {
        return 0;
    }
    tr->t = 0;
    angle = 360.0f * angle;
    tr->pos[0] = 5.0f * LUT_Sin12Bit(angle);
    tr->pos[1] = 10.0f * height;
    tr->pos[2] = 5.0f * fn_80186960(angle);
    return 1;
}

extern "C" void CoinParticle_Update(CoinParticleManager *self) { /* 0x80130D2C size:0x2B0 */
    CoinTrail *trail;
    int i;
    int j;

    for (i = 0; i < 6; i++) {
        if (self->particles[i].active != 0) {
            trail = self->particles[i].trail;
            self->particles[i].pos[0] += self->particles[i].vel[0];
            self->particles[i].pos[1] += self->particles[i].vel[1];
            self->particles[i].pos[2] += self->particles[i].vel[2];
            self->particles[i].vel[1] -= 0.1f;
            self->particles[i].rotY += 5.0f;
            if (self->particles[i].rotY > 360.0f) {
                self->particles[i].rotY -= 360.0f;
            }
            self->particles[i].alpha = 1.0f - self->particles[i].timer / 100.0f;
            for (j = 0; j < self->trailCount; j++) {
                if (trail[j].t >= 0) {
                    trail[j].pos[1] -= 2.0f;
                    if (++trail[j].t > 10) {
                        trail[j].t = -1;
                    }
                }
            }
            if ((self->particles[i].timer & 3) == 0) {
                for (j = 0; j < self->trailCount; j++) {
                    if (CoinTrail_Spawn(&trail[j], lbl_80495994[self->sinIdx], lbl_80495A94[self->heightIdx]) == 1) {
                        trail[j].pos[0] += self->particles[i].pos[0];
                        trail[j].pos[1] += self->particles[i].pos[1];
                        trail[j].pos[2] += self->particles[i].pos[2];
                        break;
                    }
                }
                if (++self->sinIdx >= 64) {
                    self->sinIdx = 0;
                }
                if (++self->heightIdx >= 48) {
                    self->heightIdx = 0;
                }
            }
            if (++self->particles[i].timer >= 100) {
                self->particles[i].active = 0;
            }
        }
    }
}

static inline void CoinParticleManagerBase_Dtor(CoinParticleManager *self) {
    if (self != 0) {
        self->vtbl = CoinShotBase_vtable_8048E34C;
        Object_DtorWithGXSync(self->jobj, 1);
        Object_DtorWithGXSync(self->trailJobj, 1);
    }
}

extern "C" CoinParticleManager *CoinParticleManager_Destroy(CoinParticleManager *self, short flag) { /* 0x80130FDC size:0x80 */
    if (self != 0) {
        self->vtbl = KPCoinShots_vtable_8048E3C0;
        CoinParticleManagerBase_Dtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct CoinInputPlayer {
    virtual void v08();
    virtual void v0C();
    virtual float Steer();
    virtual void v14();
    virtual float Accel();
    virtual float Brake();
    virtual unsigned char Pressed(int mask);
    virtual unsigned char Held(int mask);
    virtual void v28();
    virtual unsigned int Down(int mask);
};

/* Steering-wheel coin input: walks the wheel notch position one step at a
 * time towards the clamped stick position and turns notch crossings into
 * coin pulses, then latches the button command for this frame. */
struct CoinInput {
    char pad0[4];
    unsigned char active;      /* 0x04 */
    char pad5;
    unsigned char armed;       /* 0x06 */
    char pad7;
    int notch;                 /* 0x08 */
    int idleTimer;             /* 0x0C */
    int cooldown;              /* 0x10 */
    int dir;                   /* 0x14 */
    int cmd;                   /* 0x18 */
    int lastCmd;               /* 0x1C */
    unsigned int buttons;      /* 0x20 */
    unsigned int prevButtons;  /* 0x24 */
};

static inline float CoinPcbSpeed(void)
{
    return *(float *)((char *)StrPcb_GetInstance() + 0x48);
}

extern "C" void CGameCoin_ProcessInput(CoinInput *s)
{
    CoinInputPlayer *pl;
    int target;
    unsigned char flipped;
    int notch;
    int oldAbs;
    unsigned char moved;
    int cmd;

    if (!(CoinPcbSpeed() < *(float *)&lbl_806D7140)) {
        if (--s->idleTimer <= 0) {
            CoinStrPcb *pcb = StrPcb_GetInstance();
            if (pcb != 0) {
                StrPcb_ResetCommands_Neutral(pcb, 0);
            }
        }
    }
    if (!s->active) {
        return;
    }
    pl = InputMgr_GetPlayer(GetInputManager(), 0);
    s->dir = 0;
    target = Clamp_Int((int)(*(float *)&lbl_806D7194 * pl->Steer()), -3, 3);
    notch = s->notch;
    moved = 0;
    flipped = 0;
    do {
        if (notch > target) {
            notch--;
        } else if (notch < target) {
            notch++;
        }
        oldAbs = abs(s->notch);
        switch (abs(notch)) {
        case 0:
            s->armed = 1;
            s->cooldown = 0;
            break;
        case 1:
        case 2:
            if (oldAbs <= 0) {
                s->armed = 1;
                s->cooldown = 0;
            } else if (oldAbs <= 2 && s->cooldown <= 0) {
                if (s->armed == 1) {
                    s->armed = 0;
                    flipped = 1;
                    s->cooldown = 40;
                } else {
                    s->cooldown = 10;
                }
                moved = 1;
            }
            break;
        case 3:
        case 4:
            if (oldAbs <= 2) {
                s->armed = 1;
                s->cooldown = 8;
            } else if (s->cooldown <= 0) {
                if (s->armed == 1) {
                    s->armed = 0;
                    flipped = 1;
                    s->cooldown = 6;
                } else {
                    s->cooldown = 6;
                }
                moved = 1;
            }
            break;
        }
        s->notch = notch;
    } while (notch != target);
    if (s->cooldown > 0) {
        s->cooldown--;
    }
    if (moved == 1) {
        if (target > 0) {
            s->dir = 1;
        } else if (target < 0) {
            s->dir = -1;
        }
    }
    if (flipped == 1) {
        s->idleTimer = 0;
        if (!(CoinPcbSpeed() < *(float *)&lbl_806D7140)) {
            CoinStrPcb *pcb;
            s->idleTimer = 2;
            pcb = StrPcb_GetInstance();
            if (pcb != 0) {
                StrPcb_ResetCommands_Zero(pcb, 0);
            }
        }
    }
    s->buttons = 0;
    cmd = 0;
    if (pl->Down(0x2000)) {
        s->buttons |= lbl_806D7268;
    }
    if (pl->Accel() > *(float *)&lbl_806D7270) {
        s->buttons |= lbl_806D726C;
    }
    if (s->buttons & ~s->prevButtons) {
        cmd = 1;
    } else if (pl->Brake() > *(float *)&lbl_806D7270) {
        cmd = 2;
    } else if (pl->Down(0x400)) {
        cmd = 3;
    }
    if (cmd == s->lastCmd) {
        s->lastCmd = cmd;
        if (cmd != 1) {
            cmd = 0;
        }
    } else {
        s->lastCmd = cmd;
    }
    s->prevButtons = s->buttons;
    s->cmd = cmd;
}

#ifdef NON_MATCHING
/* Equivalent C++ for CGameCoin_Update (kept as asm in the matching build).
 * Written from the asm; field names past 0x80 are descriptive guesses. */
struct CoinCourseParams {
    int shellWait;             /* 0x00 */
    unsigned char pad4[0xC];
    unsigned char loseShellOnHit; /* 0x10 */
};

struct CGameCoinTail {         /* CGameCoin + 0x80 */
    int demoFrame;             /* 0x80 */
    CoinCourseParams *course;  /* 0x84 */
    int lane;                  /* 0x88 */
    int laneTarget;            /* 0x8C */
    float laneT;               /* 0x90 */
    float jumpT;               /* 0x94 */
    float hitT;                /* 0x98 */
    int shellWait;             /* 0x9C */
    float yaw;                 /* 0xA0 */
    void *spinA;               /* 0xA4 */
    void *spinB;               /* 0xA8 */
    void *spinC;               /* 0xAC */
    CoinJObj *wheelA;          /* 0xB0 */
    CoinJObj *wheelB;          /* 0xB4 */
    float wheelAngleA;         /* 0xB8 */
    float wheelAngleB;         /* 0xBC */
};

/* same vtable as CoinInputPlayer, with the slot at 0x28 typed */
struct CoinUpdatePad {
    virtual void v08();
    virtual void v0C();
    virtual float Steer();
    virtual void v14();
    virtual float Accel();
    virtual float Brake();
    virtual unsigned char Pressed(int mask);
    virtual unsigned char Held(int mask);
    virtual unsigned int Buttons(int mask);
};

#define COIN_STR_HIT_NO     ((const char *)CGameCoin_8012BF5C_rodata_80356C00 + 0x0C) /* "Hit No = %d\n" */
#define COIN_STR_START_COIN ((const char *)CGameCoin_8012BF5C_rodata_80356C00 + 0x1C) /* "Start to KPCoin. Coin kind is %d.  %s - %d\n" */
#define COIN_STR_HPP        ((const char *)CGameCoin_8012BF5C_rodata_80356C00 + 0x48) /* "CGameCoin.hpp" */
#define COIN_SHELL_START    ((const float *)&s_shellPathData[15])
#define COIN_LANE_TARGETS   ((const float *)&s_shellPathData[18]) /* 5 x Vec */
#define COIN_LANE_YAW       ((const float *)&s_shellPathData[33]) /* 5 floats */

static inline void CoinJObj_SetupMatrixNM(CoinJObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) { /* HSD_JObjGetMtxPtr */
        __assert(lbl_806D7174, 0x47C, lbl_806D717C);
    }
    if (jobj == 0) { /* HSD_JObjSetupMatrix */
        __assert(lbl_806D7174, 0x25D, lbl_806D717C);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (clean) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline void CoinParticleManager_Spawn(CoinParticleManager *pm, int kind, const CoinVec &pos, float angle) {
    int idx;
    CoinParticle *p;

    if (!IsCardValid()) {
        return;
    }
    DebugPrintf(COIN_STR_START_COIN, kind, COIN_STR_HPP, 0x1F2);
    if (fn_8016C360(0xAB) == 1) {
        fn_8016C394(0xAB);
    }
    SoundMgr_PlaySE(0xAB);
    idx = 0;
    if (pm->particles[0].active == 0) {
        idx = 0;
    } else if (pm->particles[1].active == 0) {
        idx = 1;
    } else if (pm->particles[2].active == 0) {
        idx = 2;
    } else if (pm->particles[3].active == 0) {
        idx = 3;
    } else if (pm->particles[4].active == 0) {
        idx = 4;
    } else if (pm->particles[5].active == 0) {
        idx = 5;
    }
    p = &pm->particles[idx];
    p->active = 1;
    p->timer = 0;
    p->alpha = 0.0f;
    p->rotY = 0.0f;
    p->pos[0] = pos.x;
    p->pos[1] = pos.y;
    p->pos[2] = pos.z;
    p->vel[0] = 3.0f * Cosf_LUT_Wrap(angle);
    p->vel[1] = 3.0f;
    p->vel[2] = 3.0f * Sinf_LUT_Wrap(angle);
    switch (kind) {
    case 0:
        p->vel[0] *= 0.9f;
        p->vel[2] *= 0.9f;
        break;
    case 1:
        p->vel[0] *= 1.45f;
        p->vel[2] *= 1.45f;
        p->vel[1] *= 0.73f;
        break;
    case 2:
        p->vel[0] *= 0.9f;
        p->vel[2] *= 0.9f;
        p->vel[1] *= 1.4f;
        pm->trailCount = 10;
        break;
    }
}

static inline void CoinShell_Aim(CoinShell *ss, const float *target) {
    CoinVec *aim = (CoinVec *)((char *)ss + 0x50);

    aim->x = target[0];
    aim->y = target[1];
    aim->z = target[2];
    fn_801734B0(ss->effect, aim);
}

static inline float CoinQuantize(float v) {
    return (float)(int)(10000.0f * v) / 10000.0f;
}

extern "C" int CGameCoin_Update(CGameCoin *self) { /* 0x8012C538 size:0x2164 */
    CGameCoinTail *t = (CGameCoinTail *)self->pad80;
    float (*kartMtx)[4] = (float (*)[4])self->pad18;
    void *bus;
    CoinUpdatePad *pad;
    CoinShell *ss;
    CoinJObj *j;
    CoinVec pos;
    CoinVec eye;
    CoinVec at;
    CoinVec eye2;
    CoinVec at2;
    CoinVec side;
    CoinVec fwd;
    CoinVec shellPos;
    CoinVec d;
    CoinVec coinPos;
    float tmp[3][4];
    float steer;
    float accel;
    float brake;
    float steer2;
    float dy;
    unsigned char busy;
    unsigned char hitFlame;
    int hit;
    int kind;
    int i;
    int n;
    int coins;
    int *divisor;
    int dir;
    KoopaFireball *fb;

    if (!self->active) {
        self->active = 1;
    }
    if (!IsRaceStarted()) {
        if (self->m7D == 0) {
            SoundMgr_Play(0x33);
            self->m7D = 1;
        }
    } else if (self->m7D == 1) {
        fn_80192688(0x33, 1);
        self->m7D = 0;
    }
    CGameCoin_ProcessInput((CoinInput *)SINGLETON_INSTANCE(g_pInputState));
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    pad = (CoinUpdatePad *)InputMgr_GetPlayer(GetInputManager(), 0);
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 370.0f;

    if (self->demoMode == 0) {
        steer = pad->Steer();
        bus = *(void **)((char *)self->driver + 0x304);
        ItemEffectBus_SnapshotAndFullReset(bus);
        if (IsRaceStarted()) {
            busy = 0;
            if (t->jumpT >= 0.0f || t->hitT >= 0.0f || t->lane != t->laneTarget) {
                busy = 1;
            }
            brake = pad->Brake();
            accel = pad->Accel();
            steer2 = pad->Steer();
            InputCmd_PushSample(self->input, 0, CoinQuantize(steer2), CoinQuantize(accel), CoinQuantize(brake));
            InputCmd_TickAndDetectAndClear(self->input);
            Shell_UpdateState((CoinShell *)self->shellSet);

            ss = (CoinShell *)self->shellSet;
            switch (ss->state) {
            case 0:
                if (t->shellWait > 0) {
                    t->shellWait--;
                } else if (ss->state == 0) {
                    ss->state = 1;
                    ss->t = 0.0f;
                    ss->alpha = 1.0f;
                    PSMTXRotRad(ss->mtx, 'Y', -1.5707964f);
                    PSMTXScale(tmp, 0.8f, 0.8f, 0.8f);
                    PSMTXConcat(ss->mtx, tmp, ss->mtx);
                    ss->mtx[0][3] = COIN_SHELL_START[0];
                    ss->mtx[1][3] = 50.0f + COIN_SHELL_START[1];
                    ss->mtx[2][3] = COIN_SHELL_START[2];
                }
                break;
            case 1:
                if (ss->mtx[1][3] < 12.0f + kartMtx[1][3]) {
                    if (ss->state == 1) {
                        ss->state = 2;
                        ss->t = 0.0f;
                        ss->alpha = 0.0f;
                    }
                }
                break;
            case 2:
                if (fn_8012BA38(self->m48)) {
                    ss = (CoinShell *)self->shellSet;
                    if (ss->state == 2) {
                        CoinShell_Aim(ss, COIN_LANE_TARGETS + t->laneTarget * 3);
                        fn_8017351C(ss->effect);
                        ss->state = 3;
                        ss->t = 0.0f;
                        ss->alpha = 0.0f;
                        j = ss->joint;
                        if (j != 0) {
                            CoinJObj_SetupMatrixNM(j);
                            PSMTXCopy(j->mtx, ss->mtx);
                            PSMTXRotRad(tmp, 'Z', -1.5707964f);
                            PSMTXConcat(ss->mtx, tmp, ss->mtx);
                            PSMTXScale(tmp, 1.0f, 1.0f, 1.0f);
                            PSMTXConcat(ss->mtx, tmp, ss->mtx);
                            ss->mtx[0][3] = 2.5f * ss->mtx[0][1] + j->mtx[0][3];
                            ss->mtx[1][3] = 2.5f * ss->mtx[1][1] + j->mtx[1][3];
                            ss->mtx[2][3] = 2.5f * ss->mtx[2][1] + j->mtx[2][3];
                        }
                    }
                    t->shellWait = t->course->shellWait;
                    fn_801699D8(0, 1);
                    fn_801699D8(1, 1);
                }
                break;
            case 3:
                if (!busy) {
                    if (ss->state == 3 && ss->t >= 60.0f
                        && Input_IsItemButtonPressed(pad->Buttons(0xE3FF))
                        && fn_8012B9AC(self->m48)) {
                        fn_801699D8(0, 0);
                        fn_801699D8(1, 0);
                        SetRumbleMode(0, 4, 0x1E);
                        SoundMgr_PlaySE(0x68);
                        ss = (CoinShell *)self->shellSet;
                        if (ss->state == 3 && ss->t >= 60.0f) {
                            CoinVec *aim = (CoinVec *)((char *)ss + 0x50);

                            fn_80173500(ss->effect);
                            ss->state = 4;
                            ss->t = 0.0f;
                            ss->alpha = 1.0f;
                            ss->landed = 0;
                            j = ss->joint;
                            if (j != 0) {
                                CoinJObj_SetupMatrixNM(j);
                                PSMTXRotRad(ss->mtx, 'Y', 3.1415927f);
                                PSMTXScale(tmp, 1.0f, 1.0f, 1.0f);
                                PSMTXConcat(ss->mtx, tmp, ss->mtx);
                                ss->mtx[0][3] = 2.5f * ss->mtx[0][1] + j->mtx[0][3];
                                ss->mtx[1][3] = 2.5f * ss->mtx[1][1] + j->mtx[1][3];
                                ss->mtx[2][3] = 2.5f * ss->mtx[2][1] + j->mtx[2][3];
                                ss->vel.x = aim->x - ss->mtx[0][3];
                                ss->vel.y = aim->y - ss->mtx[1][3];
                                ss->vel.z = aim->z - ss->mtx[2][3];
                                Vec3_Normalize(&ss->vel, &ss->vel);
                            }
                        }
                        busy = 1;
                    }
                }
                break;
            case 4:
                shellPos.x = ss->mtx[0][3];
                shellPos.y = ss->mtx[1][3];
                shellPos.z = ss->mtx[2][3];
                hit = fn_8016DC90(self->m70, &shellPos, 5.0f);
                if (hit >= 0) {
                    ss = (CoinShell *)self->shellSet;
                    if (ss->state == 4) {
                        ss->state = 5;
                        ss->t = 0.0f;
                        ss->alpha = 1.0f;
                        SoundMgr_PlaySE(0xC9);
                    }
                    if (hit == 0 || hit == 3) {
                        self->koopa->reqState = 2;
                    }
                    if (hit == 1 || hit == 2) {
                        self->koopa->reqState = 3;
                    }
                    SoundObj_PlaySE(self->audio, 0xB);
                    fn_8012BAC4(self->m48);
                    if (fn_8016DEF4(self->m70) < 4) {
                        DebugPrintf(COIN_STR_HIT_NO, hit);
                        kind = (hit <= 1) ? 1 : 0;
                        CoinParticleManager_Spawn((CoinParticleManager *)self->particles, kind, shellPos, 30.0f);
                        CoinParticleManager_Spawn((CoinParticleManager *)self->particles, kind, shellPos, 0.0f);
                        CoinParticleManager_Spawn((CoinParticleManager *)self->particles, kind, shellPos, -30.0f);
                    }
                }
                break;
            }

            if (!busy && InputCmd_GetDetectedFlag(self->input)) {
                t->jumpT = 0.0f;
                TornadoEffect_SetFlagC0(self->effects);
                SoundObj_PlaySE_Direct(self->audio, 0x56);
                fn_8012BB58(self->m48);
                busy = 1;
            }
            if (!busy && SINGLETON_INSTANCE(g_pInputState) != 0) {
                dir = ((CoinInput *)SINGLETON_INSTANCE(g_pInputState))->dir;
                if (dir == 1) {
                    if (t->lane < 4) {
                        t->laneTarget = t->lane + 1;
                        t->laneT = 0.0f;
                    }
                } else if (dir == -1) {
                    if (t->lane > 0) {
                        t->laneTarget = t->lane - 1;
                        t->laneT = 0.0f;
                    }
                }
                if (t->lane != t->laneTarget) {
                    ss = (CoinShell *)self->shellSet;
                    if (ss->state == 3) {
                        CoinShell_Aim(ss, COIN_LANE_TARGETS + t->laneTarget * 3);
                    }
                    TornadoEffect_SetFlagC0(self->effects);
                    SoundObj_PlaySE_Direct(self->audio, 0x56);
                    fn_8012BB58(self->m48);
                }
            }
        }

        if (t->jumpT >= 0.0f && self->demoMode == 0) {
            t->jumpT += 1.0f;
            if (t->jumpT < 30.0f) {
                pos.y += 10.0f * LUT_Sin12Bit(6.0f * t->jumpT);
            }
            if (30.0f == t->jumpT) {
                TornadoEffect_ClearFlagC0AndSetC4(self->effects, 0.5f);
                SoundObj_PlaySE_Direct(self->audio, 0x57);
            } else if (t->jumpT > 35.0f) {
                t->jumpT = -1.0f;
            }
        }
        if (t->lane != t->laneTarget) {
            t->laneT += 1.0f;
            if (t->laneT < 15.0f) {
                t->yaw = COIN_LANE_YAW[t->lane]
                    + t->laneT * (COIN_LANE_YAW[t->laneTarget] - COIN_LANE_YAW[t->lane]) / 15.0f;
                pos.y += 5.0f * LUT_Sin12Bit(12.0f * t->laneT);
            } else {
                t->yaw = COIN_LANE_YAW[t->laneTarget];
            }
            if (15.0f == t->laneT) {
                TornadoEffect_ClearFlagC0AndSetC4(self->effects, 0.2f);
                SoundObj_PlaySE_Direct(self->audio, 0x57);
            } else if (t->laneT > 20.0f) {
                t->lane = t->laneTarget;
            }
        }

        PSMTXScale(kartMtx, 1.0f, 1.0f, 1.0f);
        PSMTXRotRad(tmp, 'Y', 0.017453292f * (180.0f + t->yaw));
        PSMTXConcat(tmp, kartMtx, kartMtx);
        PSMTXTrans(tmp, pos.x, pos.y, pos.z);
        PSMTXConcat(tmp, kartMtx, kartMtx);

        BossKoopa_UpdateAnim(self->koopa);
        fb = self->koopa->fireball;
        hitFlame = 0;
        for (i = 0; i < 64; i++) {
            if (fb->flames[i].life < 0.0f) {
                continue;
            }
            Vec3_Subtract(&pos, &fb->flames[i].pos, &d);
            d.y = 0.0f;
            if (!(PSVECSquareMag(&d) < 400.0f)) {
                continue;
            }
            dy = pos.y - d.y;
            if (dy < 0.0f) {
                dy = -dy;
            }
            if (dy < 5.0f) {
                hitFlame = 1;
                break;
            }
        }
        if (hitFlame) {
            ss = (CoinShell *)self->shellSet;
            if (ss->state == 3 && t->course->loseShellOnHit) {
                fn_801699D8(0, 0);
                fn_801699D8(1, 0);
                ss = (CoinShell *)self->shellSet;
                if (ss->state == 3) {
                    ss->state = 6;
                    ss->t = 0.0f;
                    fn_80173500(ss->effect);
                }
                fn_8012B924(self->m48);
            }
            ss = (CoinShell *)self->shellSet;
            if (ss->state == 4) {
                ss->state = 5;
                ss->t = 0.0f;
                ss->alpha = 1.0f;
                SoundMgr_PlaySE(0xC9);
            }
            ItemEffectBus_ApplyItemEventSet(*(void **)((char *)self->driver + 0x304), 0x5F, 1);
            TornadoEffect_ApplyItemVisual_Secondary(self->effects, 0x5F, 1);
            SoundObj_PlaySE(self->audio, 0xC);
            fn_8012BD2C(self->m48);
            t->hitT = 0.0f;
        }
        if (t->hitT >= 0.0f) {
            t->hitT += 1.0f;
            if (t->hitT > 60.0f) {
                ItemEffectBus_ApplyItemEventClear(*(void **)((char *)self->driver + 0x304), 0x5F);
                TornadoEffect_ApplyItemVisual_Primary(self->effects, 0x5F);
                t->hitT = -1.0f;
            }
        }
        RenderObj_ItemStateMachine_Timed(self->driver, 0, 0.0f, 0.0f);
        TornadoEffect_Tick(self->effects, GetDisplayBufferIndex());
        SoundVolumePan_Update(self->audio);
        fn_8012A71C(self->m48, -steer);
        ItemEffectBus_TickTornadoCooldown(*(void **)((char *)self->driver + 0x304));

        eye.x = at.x = 0.0f;
        eye.y = at.y = 0.0f;
        eye.z = at.z = 370.0f;
        side.x = kartMtx[0][1];
        side.y = kartMtx[1][1];
        side.z = kartMtx[2][1];
        fwd.x = kartMtx[0][2];
        fwd.y = kartMtx[1][2];
        fwd.z = kartMtx[2][2];
        Vec3_Normalize(&side, &side);
        Vec3_Normalize(&fwd, &fwd);
        eye.x = eye.x - 40.0f * fwd.x;
        eye.y = eye.y - 40.0f * fwd.y;
        eye.z = eye.z - 40.0f * fwd.z;
        eye.y = eye.y + 23.0f;
        at.y = at.y + 17.3f;
        CObj_LoadIntoGX(self->scene, &eye);
        CObj_ApplyViewport(self->scene, &at);
    } else if (self->defeated == 0) {
        PSMTXScale(kartMtx, 1.0f, 1.0f, 1.0f);
        PSMTXRotRad(tmp, 'Y', 3.1415927f);
        PSMTXConcat(tmp, kartMtx, kartMtx);
        PSMTXTrans(tmp, pos.x, pos.y, pos.z);
        PSMTXConcat(tmp, kartMtx, kartMtx);
        RenderObj_ItemStateMachine_Timed(self->driver, 0, 0.0f, 0.0f);
        TornadoEffect_Tick(self->effects, GetDisplayBufferIndex());
        fn_8012A71C(self->m48, 0.0f);
        ChallengeGoalCamera_Update(self->goalCam, self->scene, kartMtx);
    }

    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->env);
    self->particles->Begin(); /* vtable slot 0xC: the particle manager's update */
    fn_8016DA78(self->m70);
    fn_8016EC80(self->m74);
    fn_80182B50(t->spinA, 0.0f, 0.002f);
    fn_80182B50(t->spinB, 0.0f, -0.002f);
    fn_80182B50(t->spinC, 0.0f, -0.002f);
    t->wheelAngleA += 0.00087266444f;
    if (t->wheelAngleA >= 6.283184f) {
        t->wheelAngleA -= 6.283184f;
    }
    t->wheelAngleB += 0.0005817763f;
    if (t->wheelAngleB >= 6.283184f) {
        t->wheelAngleB -= 6.283184f;
    }
    CoinJObj_SetRotationY(t->wheelA, t->wheelAngleA);
    CoinJObj_SetRotationY(t->wheelB, t->wheelAngleB);

    if (IsRaceStarted() && self->demoMode == 0) {
        if (fn_8016DF50(self->m70)) {
            self->demoMode = 1;
            self->defeated = 1;
            fn_801699D8(0, 0);
            fn_801699D8(1, 0);
        } else if (g_raceTimeRemaining >= 0.0f) {
            g_raceTimeRemaining -= 0.016666668f;
            if (g_raceTimeRemaining < 0.0f) {
                g_raceTimeRemaining = 0.0f;
                self->demoMode = 1;
                fn_801699D8(0, 0);
                fn_801699D8(1, 0);
            }
        }
    }
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));

    if (self->demoMode != 0) {
        if (t->demoFrame == 0) {
            coins = 0;
            n = fn_8016DEF4(self->m70);
            divisor = NokoNokoChallenge_GetCoinDivisor();
            if (divisor != 0) {
                if (n > 0 && n <= 4) {
                    coins = divisor[n - 1];
                } else {
                    coins = 0;
                }
                SetCoinCount(coins);
            }
            if (self->defeated) {
                self->koopa->reqState = 4;
                if (fn_8016C360(0x37) == 1) {
                    fn_8016C394(0x37);
                }
                n = fn_8016DEF4(self->m70);
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), n);
                SetCourseScene3D(self->defeatDemo->scene);
                g_raceEnded = 1;
                g_lakituStartAnimDone = 0;
            } else {
                self->koopa->reqState = 4;
                if (fn_8016C360(0x37) == 1) {
                    fn_8016C394(0x37);
                }
                fn_8012BDA4(self->m48);
                n = fn_8016DEF4(self->m70);
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), n);
                Object_SetByte10_Return1(self->scene, 1);
                fn_8016C554(0);
                g_lakituStartAnimDone = 0;
            }
            NokoNokoChallenge_SaveResult(self, coins, self->defeated);
        } else if (self->defeated) {
            DefeatDemo_Update(self->defeatDemo);
        }
        t->demoFrame++;
        if (t->demoFrame == 200 && self->defeated == 1) {
            CObj_ApplyScissor(self->defeatDemo->scene, &coinPos);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, 10.0f);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, 25.0f);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, 50.0f);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, -10.0f);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, -25.0f);
            CoinParticleManager_Spawn((CoinParticleManager *)self->particles, 2, coinPos, -50.0f);
        }
        if (fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
    } else {
        CObj_LoadProjMatrix(self->scene, &eye);
        CObj_ApplyScissor(self->scene, &at);
        ItemObjectManager_Update();
        at2 = at;
        eye2 = eye;
        VfxSlotMgr_Update(&eye2, &at2);
    }
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    RumbleUpdate();
    return -2;
}
#endif

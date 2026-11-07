
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7280[7];
extern unsigned char lbl_806D7288[5];
/*
 * 0x801313D0..0x801341E4: Suika ball minigame.
 */
#pragma cplusplus on

struct Vec3 { float x, y, z; };
struct LNode { char pad[8]; void *f8; };
struct Trail { int age; Vec3 pos; };
struct Shot {
    char pad0[0x14];
    int active;
    char pad18[4];
    int timer;
    Vec3 pos;
    Vec3 vel;
    float rot;
    float alpha;
    Trail trail[18];
    char pad160[0xc];
};
struct ShotSet {
    Shot shots[6];
};
struct ShotOwner {
    char pad0[4];
    void *model;
    void *trailModel;
    int sinIdx;
    int cosIdx;
    char pad14[0x89c - 0x14];
    int trailCount;
};

struct ModelPair {
    void **vt;
    void *a;
    void *b;
};

struct Deletable {
    virtual ~Deletable();
    virtual unsigned char Begin();
    virtual void End();
};

struct Destroyable {
    virtual void v0();
    virtual void Destroy(int flag);
};

struct HsdClass {
    unsigned char pad0[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
};

struct HsdRefObj {
    HsdClass *klass;
    unsigned short ref;
};

struct Quat { float x, y, z, w; };

struct HSD_JObj {
    char pad0[0x14];
    unsigned int flags;     /* 0x14 */
    char pad18[4];
    Quat rotate;            /* 0x1C */
    Vec3 scale;             /* 0x2C */
    Vec3 translate;         /* 0x38 */
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
};

struct SuikaBallObj {
    char pad0[0x38];
    Vec3 pos;               /* 0x38 */
    char pad44[0x60 - 0x44];
    unsigned char hit;      /* 0x60 */
    unsigned char goal;     /* 0x61 */
};

struct Gate {
    Vec3 pos;
    char padC[0x24 - 0xC];
    Vec3 normal;            /* 0x24 */
};

struct GateList {
    Gate *gates[4];
    int next;               /* 0x10 */
};

struct SuikaSlot {
    void *objA;
    void *objB;
    HSD_JObj **bufA;
    HSD_JObj **bufB;
    int count;
};

struct SuikaBall {
    void *vtable;
    char pad4[8];
    Destroyable *car;       /* 0x0C */
    void *lakitu;           /* 0x10 */
    void *environment;      /* 0x14 */
    Deletable *m18;
    void *m1C;
    Deletable *m20;
    HsdRefObj *m24;
    char pad28[4];
    void *hud;              /* 0x2C */
    unsigned char active;   /* 0x30 */
    unsigned char bgmOn;    /* 0x31 */
    unsigned char finished; /* 0x32 */
    unsigned char goalReached; /* 0x33 */
    int state;              /* 0x34 */
    char pad38[4];
    SuikaBallObj *m3C;
    Gate *m40;
    Deletable *m44;
    Deletable *m48;
    float speedScale;       /* 0x4C */
    Vec3 prevPos;           /* 0x50 */
    SuikaSlot *slots;       /* 0x5C */
    Deletable *m60;
    GateList *bufs;         /* 0x64 */
    int coins;              /* 0x68 */
};

/* TOP-END */

extern "C" {
extern void CObj_DebugVizPathFlush(void *cobj);
extern void CourseEnvironment_RenderObjects_Timed(void *env);
extern void DrawEffect_TickAndCull(void);
extern void GXBegin(int type, int fmt, unsigned short n);
extern void GXClearVtxDesc(void);
extern void GXLoadPosMtxImm(void *mtx, unsigned int id);
extern void GXSetBlendMode(int type, int src, int dst, int op);
extern void GXSetChanCtrl(int chan, unsigned char enable, int amb, int mat, unsigned int lights, int diff, int attn);
extern void GXSetCullMode(int mode);
extern void GXSetCurrentMtx(unsigned int id);
extern void GXSetNumChans(unsigned char n);
extern void GXSetNumTevStages(unsigned char n);
extern void GXSetNumTexGens(unsigned char n);
extern void GXSetTevOp(int stage, int mode);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, unsigned char frac);
extern void GXSetVtxDesc(int attr, int type);
extern void GXSetZMode(unsigned char compare, int func, unsigned char update);
extern void *HSD_CObjGetCurrent(void);
extern void *HSD_CObjGetViewingMtxPtr(void *cobj);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void HSD_StateInvalidate(int state);
extern unsigned char IsCardValid(void);
extern void ItemObjectManager_Render(void);
extern void KartItem_RenderPipelinedWithEffects(void *car, int flag);
void Object_RenderJObjEx(void *o, void *node, int mask);
extern void Object_RenderJObjIfWithinRange(void *o);
extern void Subsystem36c_DispatchPass2_Timed(void *env);
extern void Subsystem36c_DispatchPass4_Timed(void *env);
extern void SuikaBallObj_Render(void *o);
extern void TransitionEffect_RenderPass(void *te, int pass);
extern void TransparentDraw_SortAndDispatch(void);
extern void __assert(const char *file, int line, const char *cond);
extern void clDrawMan_Buckets_Dispatch(void *dm);
extern void clDrawMan_Buckets_Reset(void *dm);
extern void clDrawMan_EndFrame_NoOp(void *dm);
extern void fn_8016B0C4(void);
extern void fn_80253448(void *hud, unsigned int flags);
extern void fn_802535D4(void *hud);
extern Deletable *lbl_806D109C;
extern Deletable *lbl_806D10AC;
extern unsigned int lbl_806D7290;
extern unsigned int lbl_806D7294;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC1B8;
extern const Vec3 lbl_803579F4[4][2];
extern void CObj_ApplyScissor(void *cobj, Vec3 *v);
extern void CObj_LoadProjMatrix(void *cobj, Vec3 *v);
extern void CarObject_ApplyInput(void *car, float steer, float accel, float brake, unsigned char started);
extern float CarObject_CalcSpeedRatio(void *car);
extern void CarObject_FrameUpdate(void *car, int flag);
extern void *CarObject_GetRenderObj(void *car);
extern void ChallengeGoalCamera_Update(void *cam, void *cobj, float (*mtx)[4]);
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
extern void DebugPrintf(const char *fmt, ...);
extern void Fog_UpdateFromCourseScene3D(void);
extern void *GetInputManager(void);
void *GetRaceContextPtr(void);
extern void HUD_FrameUpdate(void *hud);
extern InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
extern unsigned char IsRaceStarted(void);
extern void ItemObjectManager_PerFrameUpdate(void);
extern void ItemObjectManager_Update(void);
extern float (*KartDriver_GetKartRootMtx(void *drv))[4];
extern float KartItem_GetCurrentSpeedWithBonus(void *car);
extern void KartItem_UpdateShadowBillboardAndViewport(void *car, void *cobj, int flag);
extern void KartMovement_ResetOnGoal(void *drv);
extern void KartMovement_ResetOnTimeout(void *drv);
extern void KartMovement_SetSpeedScale(void *car, float scale);
extern void KartReaction_Rear(void *drv);
extern float LUT_Cosine(float a);
extern float LUT_Sine(float a);
extern void LakituStart_UpdateCountdown(void *lakitu);
extern int NokoNokoChallenge_CalcResultText(void *self, int goal, int flag);
extern unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, unsigned char brake);
extern void NokoNokoChallenge_SaveResult(void *self, int coins, unsigned char goal);
extern int NokoNokoChallenge_TransitionToResult(void *self);
extern void Object_SetByte10_Return1(void *o, int v);
extern void SetCoinCount(int n);
extern void SoundMgr_Play(int id);
extern void SoundMgr_PlaySE(int id);
extern void SuikaBallObj_UpdatePhysics(SuikaBallObj *ball, float (*mtx)[4], Vec3 *delta, float radius);
extern void TransitionEffect_Tick(void *te);
extern float Vec3_Dot(Vec3 *a, Vec3 *b);
extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern void VfxSlotMgr_Update(Vec3 eye, Vec3 at);
extern double atan2(double y, double x);
extern void clNormal3D_Exec(void *o);
extern void fn_8016B32C(void *ws);
extern unsigned char fn_8016C360(int id);
void fn_8016C394(int n);
extern void fn_80192688(int id, int mode);
extern unsigned char fn_80253C40(void *hud);
extern void fn_80253C74(void *hud, int goal, int text, int flag);
extern void fn_80253EBC(void *hud, float v);
extern void fn_80253EC0(void *hud, float v);
extern void fn_80253FD8(void *hud, float t);
extern unsigned char g_lakituStartAnimDone;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern void *g_weatherSystem;
extern unsigned char lbl_806D1290;
extern const float lbl_806D72A4;
extern const float lbl_806D72B0;
extern const float lbl_806D72B4;
extern const float lbl_806D72B8;
extern unsigned int lbl_806D72BC;
extern unsigned int lbl_806D72C0;
extern unsigned int lbl_806D72C4;
extern unsigned int lbl_806D72C8;
extern unsigned int lbl_806D72CC;
extern unsigned int lbl_806D72D0;
extern unsigned int lbl_806D72D4;
extern unsigned int lbl_806D72D8;
extern unsigned int lbl_806D72DC;
extern unsigned int lbl_806D72E0;
extern unsigned int lbl_806D72E4;
extern unsigned int lbl_806D72E8;
extern const char lbl_80357A6C[];
extern const char lbl_80357A88[];
extern Vec3 lbl_80677C70;
extern Vec3 lbl_80677C7C;
extern void ClRomTable_PurgeAll();
void CourseEnvironment_Dtor(void *p, int flag);
extern void ItemObjectManager_Reset();
void LakituStart_Dtor(void *p, int flag);
void MemoryManager_Free(void *p);
void MemoryManager_TimedFree(void *p);
void Object_DtorWithGXSync(void *o, int flag);
void RankingTable_Init(void *ctx);
extern void SceneDrawList_Reset();
void SetActiveCamera(void *cam, int flag);
void SetPlayerCarObject(void *car);
void SetResourceLoadingFlag(int flag);
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
void dtor_80122FD8(void *p, int flag);
void fn_8012491C(void *p, int flag);
void fn_80124C84(void *p, int flag);
void fn_8016C634(void *p, int flag);
void fn_80254134(void *p, int flag);
extern void *g_raceCamera;
extern Deletable *lbl_806D10D0;
extern char lbl_8048E3F8[];
extern void Alloc();
extern void Archive_GetRootJObj();
extern void Camera_Create();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void FUN_8003b120();
extern void GameMode_BaseInit();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetDisplayBufferIndex();
extern void GetKartModelNameEntry();
extern void GetStartPosition();
extern void HSD_JObjSetFlags();
extern void HSD_LObjLoadDesc();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void LakituStart_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void ResolveJointByName();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SceneRender_CmdB_8aa20();
extern void SetCourseScene3D();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void SuikaBallObj_Init();
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize();
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern void clNormal3D_SetScale();
extern void fn_8018F614();
extern void fn_8018FEAC();
extern unsigned int g_characterId;
extern unsigned int lbl_806D12BC;
extern const float lbl_806D729C;
extern unsigned int lbl_806D72A8;
extern unsigned int lbl_806D72F8;
extern unsigned int lbl_806D72FC;
extern unsigned int lbl_806D7300;
extern unsigned int lbl_806D7304;
extern unsigned int lbl_806D7308;
extern unsigned int lbl_806D730C;
extern unsigned int lbl_806D7310;
extern unsigned int lbl_806D7314;
extern unsigned int lbl_80357008[];
extern unsigned int lbl_8048E144[];
extern void *lbl_8048E34C[];
extern void *lbl_8048E418[];
struct LNode *LinkedNode_GetField10_OrFallback(void *o, int idx);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetColorAlphaOnly(void *o, int idx, float a);
void Object_SetJObjPositionVec(void *o, struct Vec3 *v);
void Object_SetJObjRotationY(void *o, float r);
void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);
extern const float lbl_806D7298;
extern const float lbl_806D72A0;
float LUT_Sin12Bit(float x);
unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *pos, float *height, void *a, void *b, float r);
float fn_80186960(float x);
extern const float lbl_806D72EC;
extern const float lbl_806D72F0;
extern const float lbl_806D72F4;
extern float lbl_80495994[];
extern float lbl_80495A94[];
void SuikaBall_Render(SuikaBall *self);
int SuikaBall_Update(SuikaBall *self);
struct SuikaBall *fn_80133008(struct SuikaBall *self, short flag);
asm void SuikaBall_Init(void);
void fn_80133CA8(ShotOwner *self);
void fn_80133E64(ShotOwner *self);
ModelPair *fn_80134164(ModelPair *self, short flag);

#pragma section R ".extab_user"


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; unsigned int f81; void *f82; unsigned int f83; void *f84; unsigned int f85; unsigned int f86; void *f87; unsigned int f88; void *f89; unsigned int f90; unsigned int f91; void *f92; unsigned int f93; void *f94; unsigned int f95; unsigned int f96; void *f97; unsigned int f98; void *f99; unsigned int f100; unsigned int f101; void *f102; unsigned int f103; void *f104; unsigned int f105; unsigned int f106; void *f107; unsigned int f108; void *f109; unsigned int f110; unsigned int f111; void *f112; unsigned int f113; void *f114; unsigned int f115; unsigned int f116; void *f117; unsigned int f118; void *f119; unsigned int f120; unsigned int f121; void *f122; unsigned int f123; void *f124; unsigned int f125; unsigned int f126; void *f127; unsigned int f128; void *f129; unsigned int f130; unsigned int f131; void *f132; unsigned int f133; void *f134; unsigned int f135; unsigned int f136; void *f137; unsigned int f138; void *f139; unsigned int f140; unsigned int f141; void *f142; unsigned int f143; void *f144; unsigned int f145; void *f146; unsigned int f147; unsigned int f148; void *f149; unsigned int f150; void *f151; unsigned int f152; unsigned int f153; void *f154; unsigned int f155; void *f156; unsigned int f157; unsigned int f158; void *f159; unsigned int f160; void *f161; unsigned int f162; unsigned int f163; void *f164; } extab_SuikaBall_Init = { 0x504A0000, 0x00000054, 0x000B0140, 0x0000008C, 0x00000138, 0x00000094, 0x00040140, 0x000000C4, 0x0000014C, 0x000000D4, 0x00110140, 0x00000128, 0x00100160, 0x00000178, 0x00080140, 0x000001B8, 0x00000174, 0x000001C4, 0x00000140, 0x000001D8, 0x00040188, 0x000001F4, 0x00000140, 0x00000200, 0x0000019C, 0x0000020C, 0x000D0140, 0x00000250, 0x000001B0, 0x00000264, 0x002F0140, 0x00000330, 0x000001C4, 0x00000378, 0x00150140, 0x000003D8, 0x000001D8, 0x000003E4, 0x00000140, 0x000003F0, 0x000001EC, 0x000003FC, 0x00000140, 0x000004A0, 0x00030200, 0x000004D4, 0x00080140, 0x00000508, 0x00000214, 0x00000528, 0x00020140, 0x00000544, 0x00000228, 0x00000564, 0x00290140, 0x00000638, 0x00000244, 0x0000064C, 0x0000023C, 0x00000660, 0x00020244, 0x0000067C, 0x00000258, 0x00000688, 0x00020244, 0x000007DC, 0x00000140, 0x000007FC, 0x0000026C, 0x00000874, 0x00030264, 0x000008D4, 0x00000140, 0x000008E4, 0x00000280, 0x000008F0, 0x00000140, 0x00000000, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x01000244, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };




#pragma section R ".extabindex_user"


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SuikaBall_Init = {
    (void *)&SuikaBall_Init, 0x00000910, (void *)&extab_SuikaBall_Init
};




}





#include "game/singleton.h"

union GXFifoPipe {
    unsigned char u8;
    unsigned short u16;
    unsigned int u32;
    float f32;
};
volatile GXFifoPipe GXWGFifo : 0xCC008000;

static inline void GXPosition3f32(float x, float y, float z)
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXColor1u32(unsigned int c)
{
    GXWGFifo.u32 = c;
}

static inline int HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x25d, (const char *)lbl_806D7288);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj)
{
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3 *t)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x3e4, (const char *)lbl_806D7288);
    }
    t->x = jobj->translate.x;
    t->y = jobj->translate.y;
    t->z = jobj->translate.z;
}

static inline void HSD_JObjSetTranslate(HSD_JObj *jobj, Vec3 *t)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x3a9, (const char *)lbl_806D7288);
    }
    jobj->translate.x = t->x;
    jobj->translate.y = t->y;
    jobj->translate.z = t->z;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetRotation(HSD_JObj *jobj, Quat *q)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x2dd, (const char *)lbl_806D7288);
    }
    q->x = jobj->rotate.x;
    q->y = jobj->rotate.y;
    q->z = jobj->rotate.z;
    q->w = jobj->rotate.w;
}

static inline void HSD_JObjSetRotation(HSD_JObj *jobj, Quat *q)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x290, (const char *)lbl_806D7288);
    }
    jobj->rotate.x = q->x;
    jobj->rotate.y = q->y;
    jobj->rotate.z = q->z;
    jobj->rotate.w = q->w;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetScale(HSD_JObj *jobj, Vec3 *s)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x351, (const char *)lbl_806D7288);
    }
    s->x = jobj->scale.x;
    s->y = jobj->scale.y;
    s->z = jobj->scale.z;
}

static inline void HSD_JObjSetScale(HSD_JObj *jobj, Vec3 *s)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x316, (const char *)lbl_806D7288);
    }
    jobj->scale.x = s->x;
    jobj->scale.y = s->y;
    jobj->scale.z = s->z;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void DrawCardWalls(void)
{
    void *cobj;
    float top;
    float bottom;
    int i;

    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xff, 0xff, 4);
    GXSetTevOp(0, 4);
    GXSetZMode(1, 3, 1);
    GXSetBlendMode(1, 4, 5, 0);
    cobj = HSD_CObjGetCurrent();
    if (cobj != 0) {
        GXSetCurrentMtx(0);
        GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtr(cobj), 0);
        GXSetCullMode(0);
    }
    top = -180.0f;
    bottom = -200.0f;
    for (i = 0; i < 4; i++) {
        GXBegin(0x80, 0, 4);
        GXPosition3f32(lbl_803579F4[i][1].x, top, lbl_803579F4[i][1].z);
        GXColor1u32(0xE0202000);
        GXPosition3f32(lbl_803579F4[i][0].x, top, lbl_803579F4[i][0].z);
        GXColor1u32(0xE0202000);
        GXPosition3f32(lbl_803579F4[i][0].x, bottom, lbl_803579F4[i][0].z);
        GXColor1u32(0xE0202080);
        GXPosition3f32(lbl_803579F4[i][1].x, bottom, lbl_803579F4[i][1].z);
        GXColor1u32(0xE0202080);
    }
    GXSetCullMode(2);
    HSD_StateInvalidate(0x7e);
}

extern "C" void SuikaBall_Render(SuikaBall *self)
{
    if (self->active == 0) {
        return;
    }
    if (self->m18->Begin() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->m18);
        fn_8016B0C4();
        KartItem_RenderPipelinedWithEffects(self->car, 0);
        Object_RenderJObjIfWithinRange(self->lakitu);
        CourseEnvironment_RenderObjects_Timed(self->environment);
        Subsystem36c_DispatchPass2_Timed(self->environment);
        ItemObjectManager_Render();
        SuikaBallObj_Render(self->m3C);
        self->m44->End();
        self->m48->End();
        for (unsigned int i = 0; i < 3; i++) {
            SuikaSlot *slot = &self->slots[i];
            for (int j = 0; j < slot->count; j++) {
                if (slot->bufB[j] != 0 && slot->bufA[j] != 0) {
                    Vec3 v;
                    Quat q;
                    HSD_JObjGetTranslation(slot->bufB[j], &v);
                    HSD_JObjSetTranslate(slot->bufA[j], &v);
                    HSD_JObjGetRotation(slot->bufB[j], &q);
                    HSD_JObjSetRotation(slot->bufA[j], &q);
                    HSD_JObjGetScale(slot->bufB[j], &v);
                    HSD_JObjSetScale(slot->bufA[j], &v);
                    Object_RenderJObjEx(slot->objA, slot->bufA[j], 7);
                }
            }
        }
        fn_80253448(self->hud, lbl_806DC190);
        DrawEffect_TickAndCull();
        if (IsCardValid()) {
            DrawCardWalls();
        }
        self->m60->End();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        Subsystem36c_DispatchPass4_Timed(self->environment);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
        fn_80253448(self->hud, lbl_806DC1B0 | lbl_806DC190);
        self->m18->End();
    }
    fn_80253448(self->hud, lbl_806DC1B8);
    fn_802535D4(self->hud);
    TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
    HSD_StateInvalidate(0x7f);
}

static inline void Fireworks_Launch(ShotSet *fw, Vec3 *pos, float kx, float kz, float spread)
{
    if (IsCardValid()) {
        int i;
        float heading;
        float angle;
        DebugPrintf(lbl_80357A6C, lbl_80357A88, 0x2d8);
        if (fn_8016C360(0xab) == 1) {
            fn_8016C394(0xab);
        }
        SoundMgr_PlaySE(0xab);
        i = 0;
        for (int k = 0; k < 6; k++) {
            if (fw->shots[k].active == 0) {
                i = k;
                break;
            }
        }
        heading = atan2(kx - pos->x, kz - pos->z);
        angle = heading + spread;
        fw->shots[i].active = 1;
        fw->shots[i].timer = 0;
        fw->shots[i].alpha = 0.0f;
        fw->shots[i].rot = 0.0f;
        fw->shots[i].pos.x = pos->x;
        fw->shots[i].pos.y = pos->y;
        fw->shots[i].pos.z = pos->z;
        fw->shots[i].vel.x = 0.7f * LUT_Cosine(angle);
        fw->shots[i].vel.z = 0.7f * LUT_Sine(angle);
        fw->shots[i].vel.y = 1.82f;
    }
}

static inline float Gate_Side(Gate *gate, Vec3 *pos)
{
    Vec3 rel;
    Vec3_Subtract(pos, &gate->pos, &rel);
    return Vec3_Dot(&rel, &gate->normal);
}

static inline bool Gate_IsPassed(Gate *gate, Vec3 *pos)
{
    if (Gate_Side(gate, pos) > 0.0f) {
        return true;
    }
    return false;
}

static inline bool GateList_Update(GateList *list, Vec3 *pos)
{
    if (list->next >= 4) {
        return false;
    }
    if (Gate_IsPassed(list->gates[list->next], pos) == true) {
        list->next++;
        return true;
    }
    return false;
}

extern "C" int SuikaBall_Update(SuikaBall *self)
{
    InputPlayer *pad;
    float (*mtx)[4];
    Vec3 delta;
    Vec3 pos;

    if (self->active == 0) {
        self->active = 1;
    }
    if (!IsRaceStarted()) {
        if (self->bgmOn == 0) {
            SoundMgr_Play(0x24);
            SoundMgr_Play(0xd5);
            self->bgmOn = 1;
        }
    } else if (self->bgmOn == 1) {
        fn_80192688(0x24, 1);
        fn_80192688(0xd5, 1);
        self->bgmOn = 0;
    }
    GetRaceContextPtr();
    ItemObjectManager_PerFrameUpdate();
    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_raceEnded != 1 && self->state >= 0) {
        float accel;
        float brake;
        unsigned char braking;
        if (lbl_806D1290 == 0) {
            accel = pad->StickRight();
        } else {
            accel = 0.8f;
        }
        brake = pad->StickLeft();
        braking = 0;
        if (accel < 0.1f && brake < 0.1f && IsRaceStarted()) {
            braking = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(self, braking) == 1) {
            accel = 1.0f;
        }
        CarObject_ApplyInput(self->car, pad->v2(), accel, brake, IsRaceStarted());
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->m18, 0);
    } else if (self->state < 0) {
        CarObject_ApplyInput(self->car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(self->car, 0.5f);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->m18, 0);
    } else {
        CarObject_ApplyInput(self->car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(self->car, 0.5f);
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->m1C, self->m18, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);

    mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    Vec3_Subtract(&pos, &self->prevPos, &delta);
    self->prevPos.x = pos.x;
    self->prevPos.y = pos.y;
    self->prevPos.z = pos.z;
    SuikaBallObj_UpdatePhysics(self->m3C, mtx, &delta, 12.0f);
    if (self->m3C->hit) {
        KartReaction_Rear(CarObject_GetRenderObj(self->car));
        SoundMgr_PlaySE(0x5d);
        self->speedScale = 0.3f;
    } else {
        self->speedScale += 0.01f;
        if (self->speedScale > 1.0f) {
            self->speedScale = 1.0f;
        }
    }
    KartMovement_SetSpeedScale(self->car, self->speedScale);
    self->m44->Begin();
    self->m48->Begin();

    if (self->finished == 0) {
        float kx;
        float kz;

        mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
        kx = mtx[0][3];
        kz = mtx[2][3];
        pos.x = self->m3C->pos.x;
        pos.y = self->m3C->pos.y;
        pos.z = self->m3C->pos.z;
        if (Gate_Side(self->m40, &pos) > 0.0f) {
            self->m3C->goal = 1;
            self->goalReached = 1;
            self->finished = 1;
            self->state = -50;
            self->coins += 5;
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.0f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 1.570796f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -1.570796f);
        }
        if (GateList_Update(self->bufs, &pos) == true) {
            if (self->bufs->next <= 3) {
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
                self->coins += 2;
            } else {
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 1.570796f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -1.570796f);
                self->coins += 4;
            }
        }
    }

    for (unsigned int i = 0; i < 3; i++) {
        SuikaSlot *slot = &self->slots[i];
        clNormal3D_Exec(slot->objA);
        clNormal3D_Exec(slot->objB);
    }
    self->m60->Begin();
    CObj_LoadProjMatrix(self->m18, &lbl_80677C70);
    CObj_ApplyScissor(self->m18, &lbl_80677C7C);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(lbl_80677C70, lbl_80677C7C);
    if (IsRaceStarted() && self->finished == 0 && g_raceTimeRemaining >= 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            self->finished = 1;
            KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
        }
    }
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));
    if (self->finished != 0) {
        if (self->state == 0) {
            SetCoinCount(self->coins);
            fn_80192688(0xd5, 2);
            if (self->goalReached != 0) {
                KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), 0);
                Object_SetByte10_Return1(self->m18, 1);
                SoundMgr_Play(0xd6);
            } else {
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), 0);
                Object_SetByte10_Return1(self->m18, 1);
            }
            NokoNokoChallenge_SaveResult(self, self->coins, self->goalReached);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
        } else if (self->state > 0 && fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
        self->state++;
    }
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    return -2;
}

static inline int HsdRef_Dec(HsdRefObj *o)
{
    int done = o->ref == (unsigned short)-1;
    if (done) {
        return done;
    }
    return o->ref-- == 0;
}

static inline void HsdObj_Destroy(HsdRefObj *o)
{
    if (o != 0) {
        o->klass->release(o);
        o->klass->destroy(o);
    }
}

static inline void HsdRef_Unref(HsdRefObj *o)
{
    if (o != 0 && HsdRef_Dec(o)) {
        HsdObj_Destroy(o);
    }
}

static inline void FreeBufs(SuikaBall *self)
{
    GateList *bufs = self->bufs;
    if (bufs != 0) {
        for (int i = 0; i < 4; i++) {
            if (bufs->gates[i] != 0) {
                MemoryManager_TimedFree(bufs->gates[i]);
            }
        }
        MemoryManager_TimedFree(bufs);
    }
}

extern "C" SuikaBall *fn_80133008(SuikaBall *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_8048E3F8;
        delete self->m60;
        FreeBufs(self);
        fn_8016C394(0x24);
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete self->m18;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->m1C, 1);
        SetPlayerCarObject(0);
        if (self->car != 0) {
            self->car->Destroy(1);
        }
        g_raceCamera = 0;
        if (self->m20 != 0) {
            delete self->m20;
        }
        if (self->m24 != 0) {
            HsdRef_Unref(self->m24);
        }
        CourseEnvironment_Dtor(self->environment, 1);
        fn_80254134(self->hud, 1);
        fn_8012491C(self->m3C, 1);
        if (self->m40 != 0) {
            MemoryManager_TimedFree(self->m40);
        }
        delete self->m44;
        delete self->m48;
        if (self->slots != 0) {
            for (unsigned int i = 0; i < 3; i++) {
                if (self->slots[i].bufA != 0) {
                    MemoryManager_Free(self->slots[i].bufA);
                }
                if (self->slots[i].bufB != 0) {
                    MemoryManager_Free(self->slots[i].bufB);
                }
                if (self->slots[i].objA != 0) {
                    Object_DtorWithGXSync(self->slots[i].objA, 1);
                }
                if (self->slots[i].objB != 0) {
                    Object_DtorWithGXSync(self->slots[i].objB, 1);
                }
            }
            MemoryManager_Free(self->slots);
        }
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

extern "C" asm void SuikaBall_Init(void) { /* 0x80133398 size:0x910 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stmw r22, 0x78(r1)
    mr r31, r3
    lis r4, lbl_80357008@ha
    mr r0, r31
    mr r22, r0
    addi r30, r4, lbl_80357008@l
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E3F8@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D72B8(r2)
    stw r0, 0x0(r22)
    addi r0, r3, lbl_8048E3F8@l
    stfs f0, 0x4(r22)
    stw r0, 0x0(r31)
    bl MiniGame_GetCourseData
    stw r3, 0x8(r31)
    bl DrawManager_GetOrCreate
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x37c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133424
    bl InputManager_Init
    SuikaBall_Init_L_80133424:
    stw r22, 0x14(r31)
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, 0x24(r31)
    li r3, 0x2c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_8013345C
    lfs f1, lbl_806D72F8(r2)
    li r4, 0x100
    lfs f2, lbl_806D72B4(r2)
    li r5, 0x100
    lwz r6, 0x24(r31)
    bl Camera_Create
    SuikaBall_Init_L_8013345C:
    stw r22, 0x20(r31)
    li r3, 0x0
    lwz r4, 0x20(r31)
    bl SetActiveCamera
    lwz r0, 0x20(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    addi r6, r1, 0x68
    addi r4, r1, 0x60
    addi r5, r1, 0x64
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133500
    lwz r26, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r22
    mr r5, r26
    lfs f1, 0x60(r1)
    li r6, 0x0
    lfs f2, 0x68(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x0
    li r10, 0x0
    bl CarObject_Init
    SuikaBall_Init_L_80133500:
    stw r22, 0xc(r31)
    addi r4, r1, 0x60
    lwz r3, 0xc(r31)
    bl CarObject_SetPosition
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0xc(r31)
    bl SetPlayerCarObject
    li r3, 0x58
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133550
    lfs f1, lbl_806D72B8(r2)
    addi r4, r30, 0xa90
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    SuikaBall_Init_L_80133550:
    stw r22, 0x10(r31)
    li r3, 0x3084
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133580
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r22
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    SuikaBall_Init_L_80133580:
    stw r22, 0x18(r31)
    li r3, 0x8
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133598
    bl ChallengeGoalCamera_Init
    SuikaBall_Init_L_80133598:
    stw r22, 0x1c(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x18(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D729C(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x18(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801335E8
    li r4, 0x0
    bl HUD_Init
    SuikaBall_Init_L_801335E8:
    stw r22, 0x2c(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x2c(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x18(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x74(r1)
    li r3, 0x1
    lfd f1, lbl_806D72A8(r2)
    stw r0, 0x70(r1)
    lfd f0, 0x70(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r0, 0x0
    lfs f1, lbl_806D72A4(r2)
    stb r0, 0x30(r31)
    li r3, 0x7c
    lfs f0, lbl_806D72B8(r2)
    stb r0, 0x32(r31)
    stb r0, 0x33(r31)
    stw r0, 0x34(r31)
    stb r0, 0x31(r31)
    stfs f1, 0x4c(r31)
    stfs f0, 0x50(r31)
    stfs f0, 0x54(r31)
    stfs f0, 0x58(r31)
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801336C8
    addi r4, r30, 0xaa4
    bl SuikaBallObj_Init
    SuikaBall_Init_L_801336C8:
    cmplwi r22, 0x0
    stw r22, 0x3c(r31)
    beq SuikaBall_Init_L_8013375C
    lwz r3, 0x3c(r31)
    lfs f0, lbl_806D72FC(r2)
    lfs f1, lbl_806D7300(r2)
    stfs f0, 0x38(r3)
    lfs f0, lbl_806D7304(r2)
    stfs f1, 0x3c(r3)
    stfs f0, 0x40(r3)
    lwz r23, g_raceCamera(r13)
    cmplwi r23, 0x0
    beq SuikaBall_Init_L_8013371C
    lwz r3, 0x3c(r31)
    lwz r3, 0x0(r3)
    cmplwi r3, 0x0
    beq SuikaBall_Init_L_8013371C
    bl Archive_GetRootJObj
    mr r4, r3
    mr r3, r23
    bl SceneRender_CmdB_8aa20
    SuikaBall_Init_L_8013371C:
    lwz r4, 0x8(r31)
    cmplwi r4, 0x0
    beq SuikaBall_Init_L_8013375C
    lfs f5, 0x14(r4)
    lfs f4, 0x10(r4)
    lfs f3, 0xc(r4)
    lfs f2, 0x8(r4)
    lfs f1, 0x4(r4)
    lwz r3, 0x3c(r31)
    lfs f0, 0x0(r4)
    stfs f0, 0x64(r3)
    stfs f1, 0x68(r3)
    stfs f2, 0x6c(r3)
    stfs f3, 0x70(r3)
    stfs f4, 0x74(r3)
    stfs f5, 0x78(r3)
    SuikaBall_Init_L_8013375C:
    li r3, 0xc
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133770
    bl fn_8018FEAC
    SuikaBall_Init_L_80133770:
    stw r22, 0x44(r31)
    li r3, 0x10
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133788
    bl fn_8018F614
    SuikaBall_Init_L_80133788:
    stw r22, 0x48(r31)
    li r3, 0x30
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133860
    lfs f0, lbl_806D7308(r2)
    mr r4, r22
    lfs f2, lbl_806D7300(r2)
    addi r3, r22, 0xc
    stfs f0, 0x30(r1)
    addi r5, r22, 0x18
    lfs f0, lbl_806D730C(r2)
    stfs f2, 0x34(r1)
    lwz r0, 0x30(r1)
    stfs f0, 0x38(r1)
    lfs f0, lbl_806D7310(r2)
    stw r0, 0x48(r1)
    lwz r6, 0x34(r1)
    stfs f0, 0x3c(r1)
    lwz r0, 0x38(r1)
    stw r6, 0x4c(r1)
    lfs f1, 0x48(r1)
    stfs f2, 0x40(r1)
    lfs f0, lbl_806D7314(r2)
    stw r0, 0x50(r1)
    lwz r0, 0x3c(r1)
    stfs f0, 0x44(r1)
    lwz r6, 0x40(r1)
    stw r0, 0x54(r1)
    lwz r0, 0x44(r1)
    stw r6, 0x58(r1)
    lfs f0, 0x4c(r1)
    stfs f1, 0x0(r22)
    lfs f1, 0x50(r1)
    stfs f0, 0x4(r22)
    lfs f0, 0x54(r1)
    stfs f1, 0x8(r22)
    lfs f1, 0x58(r1)
    stw r0, 0x5c(r1)
    stfs f0, 0xc(r22)
    lfs f0, 0x5c(r1)
    stfs f1, 0x10(r22)
    stfs f0, 0x14(r22)
    bl Vec3_Subtract
    addi r3, r22, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r22)
    fneg f0, f0
    stfs f0, 0x24(r22)
    lfs f0, 0x1c(r22)
    stfs f0, 0x28(r22)
    lfs f0, 0x18(r22)
    stfs f0, 0x2c(r22)
    SuikaBall_Init_L_80133860:
    stw r22, 0x40(r31)
    li r3, 0x3c
    bl FUN_8003b120
    stw r3, 0x5c(r31)
    addi r28, r30, 0x9bc
    li r27, 0x0
    li r29, 0x0
    SuikaBall_Init_L_8013387C:
    lwz r0, 0x5c(r31)
    li r3, 0x5c
    add r26, r0, r29
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801338A0
    lwz r4, 0x0(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    SuikaBall_Init_L_801338A0:
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x0
    stw r22, 0x0(r26)
    fmr f3, f1
    lfs f2, lbl_806D72A4(r2)
    fmr f4, f1
    lwz r3, 0x0(r26)
    bl clNormal3D_SetScale
    li r3, 0x5c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801338DC
    lwz r4, 0x4(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    SuikaBall_Init_L_801338DC:
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x0
    stw r22, 0x4(r26)
    fmr f3, f1
    lfs f2, lbl_806D72A4(r2)
    fmr f4, f1
    lwz r3, 0x4(r26)
    bl clNormal3D_SetScale
    lwz r0, 0xc(r28)
    stw r0, 0x10(r26)
    lwz r0, 0x10(r26)
    slwi r3, r0, 2
    bl FUN_8003b120
    stw r3, 0x8(r26)
    lwz r0, 0x10(r26)
    slwi r3, r0, 2
    bl FUN_8003b120
    li r25, 0x0
    stw r3, 0xc(r26)
    mr r24, r25
    addi r23, r28, 0x8
    li r22, 0x0
    b SuikaBall_Init_L_80133978
    SuikaBall_Init_L_80133938:
    lwz r4, 0x0(r23)
    lwz r3, 0x0(r26)
    lwzx r4, r4, r25
    bl ResolveJointByName
    lwz r5, 0x8(r26)
    addi r0, r25, 0x4
    lwz r4, 0x0(r23)
    stwx r3, r5, r24
    lwz r3, 0x4(r26)
    lwzx r4, r4, r0
    bl ResolveJointByName
    lwz r4, 0xc(r26)
    addi r25, r25, 0x8
    addi r22, r22, 0x1
    stwx r3, r4, r24
    addi r24, r24, 0x4
    SuikaBall_Init_L_80133978:
    lwz r0, 0x10(r26)
    cmpw r22, r0
    blt SuikaBall_Init_L_80133938
    addi r27, r27, 0x1
    addi r28, r28, 0x10
    cmplwi r27, 0x3
    addi r29, r29, 0x14
    blt SuikaBall_Init_L_8013387C
    li r3, 0x8a0
    bl Alloc
    mr. r26, r3
    beq SuikaBall_Init_L_80133B68
    lis r3, lbl_8048E34C@ha
    li r4, 0x0
    addi r3, r3, lbl_8048E34C@l
    li r0, 0x5
    stw r3, 0x0(r26)
    li r3, 0x5c
    stw r4, 0xc(r26)
    stw r4, 0x10(r26)
    stw r0, 0x89c(r26)
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801339E4
    addi r4, r30, 0xab8
    li r5, 0x1
    bl clNormal3D_Construct
    SuikaBall_Init_L_801339E4:
    stw r22, 0x4(r26)
    lis r4, 0x4000
    li r5, 0x0
    lwz r3, 0x4(r26)
    bl clNormal3D_SetFlags
    li r3, 0x5c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133A14
    addi r4, r30, 0xac8
    li r5, 0x1
    bl clNormal3D_Construct
    SuikaBall_Init_L_80133A14:
    stw r22, 0x8(r26)
    lwz r3, 0x8(r26)
    bl Archive_GetRootJObj
    li r4, 0x200
    bl HSD_JObjSetFlags
    li r0, 0x3
    mr r5, r26
    lfs f0, lbl_806D72B8(r2)
    li r4, 0x0
    mtctr r0
    SuikaBall_Init_L_80133A3C:
    li r3, 0x0
    li r0, -0x1
    stw r3, 0x14(r5)
    stw r3, 0x1c(r5)
    stfs f0, 0x38(r5)
    stfs f0, 0x3c(r5)
    stw r3, 0x18(r5)
    stfs f0, 0x28(r5)
    stfs f0, 0x24(r5)
    stfs f0, 0x20(r5)
    stfs f0, 0x34(r5)
    stfs f0, 0x30(r5)
    stfs f0, 0x2c(r5)
    stw r0, 0x40(r5)
    stw r0, 0x50(r5)
    stw r0, 0x60(r5)
    stw r0, 0x70(r5)
    stw r0, 0x80(r5)
    stw r0, 0x90(r5)
    stw r0, 0xa0(r5)
    stw r0, 0xb0(r5)
    stw r0, 0xc0(r5)
    stw r0, 0xd0(r5)
    stw r0, 0xe0(r5)
    stw r0, 0xf0(r5)
    stw r0, 0x100(r5)
    stw r0, 0x110(r5)
    stw r0, 0x120(r5)
    stw r0, 0x130(r5)
    stw r0, 0x140(r5)
    stw r0, 0x150(r5)
    stw r0, 0x160(r5)
    stw r0, 0x170(r5)
    stw r3, 0x180(r5)
    stw r3, 0x188(r5)
    stfs f0, 0x1a4(r5)
    stfs f0, 0x1a8(r5)
    stw r3, 0x184(r5)
    stfs f0, 0x194(r5)
    stfs f0, 0x190(r5)
    stfs f0, 0x18c(r5)
    stfs f0, 0x1a0(r5)
    stfs f0, 0x19c(r5)
    stfs f0, 0x198(r5)
    stw r0, 0x1ac(r5)
    addi r4, r4, 0x1
    stw r0, 0x1bc(r5)
    stw r0, 0x1cc(r5)
    stw r0, 0x1dc(r5)
    stw r0, 0x1ec(r5)
    stw r0, 0x1fc(r5)
    stw r0, 0x20c(r5)
    stw r0, 0x21c(r5)
    stw r0, 0x22c(r5)
    stw r0, 0x23c(r5)
    stw r0, 0x24c(r5)
    stw r0, 0x25c(r5)
    stw r0, 0x26c(r5)
    stw r0, 0x27c(r5)
    stw r0, 0x28c(r5)
    stw r0, 0x29c(r5)
    stw r0, 0x2ac(r5)
    stw r0, 0x2bc(r5)
    stw r0, 0x2cc(r5)
    stw r0, 0x2dc(r5)
    addi r5, r5, 0x2d8
    bdnz SuikaBall_Init_L_80133A3C
    lwz r0, 0x89c(r26)
    cmpwi r0, 0x14
    blt SuikaBall_Init_L_80133B5C
    li r0, 0x13
    stw r0, 0x89c(r26)
    SuikaBall_Init_L_80133B5C:
    lis r3, lbl_8048E418@ha
    addi r0, r3, lbl_8048E418@l
    stw r0, 0x0(r26)
    SuikaBall_Init_L_80133B68:
    stw r26, 0x60(r31)
    li r3, 0x14
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133C4C
    li r26, 0x0
    mr r24, r22
    stw r26, 0x10(r22)
    addi r23, r30, 0x9ec
    SuikaBall_Init_L_80133B8C:
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq SuikaBall_Init_L_80133C34
    lwz r0, 0x0(r23)
    mr r4, r25
    lwz r6, 0x4(r23)
    addi r3, r25, 0xc
    stw r0, 0x18(r1)
    addi r5, r25, 0x18
    lwz r0, 0x8(r23)
    stw r6, 0x1c(r1)
    lfs f1, 0x18(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xc(r23)
    lwz r6, 0x10(r23)
    stw r0, 0x24(r1)
    lwz r0, 0x14(r23)
    stw r6, 0x28(r1)
    lfs f0, 0x1c(r1)
    stfs f1, 0x0(r25)
    lfs f1, 0x20(r1)
    stfs f0, 0x4(r25)
    lfs f0, 0x24(r1)
    stfs f1, 0x8(r25)
    lfs f1, 0x28(r1)
    stw r0, 0x2c(r1)
    stfs f0, 0xc(r25)
    lfs f0, 0x2c(r1)
    stfs f1, 0x10(r25)
    stfs f0, 0x14(r25)
    bl Vec3_Subtract
    addi r3, r25, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r25)
    fneg f0, f0
    stfs f0, 0x24(r25)
    lfs f0, 0x1c(r25)
    stfs f0, 0x28(r25)
    lfs f0, 0x18(r25)
    stfs f0, 0x2c(r25)
    SuikaBall_Init_L_80133C34:
    addi r26, r26, 0x1
    stw r25, 0x0(r24)
    cmpwi r26, 0x4
    addi r23, r23, 0x18
    addi r24, r24, 0x4
    blt SuikaBall_Init_L_80133B8C
    SuikaBall_Init_L_80133C4C:
    stw r22, 0x64(r31)
    li r0, 0x0
    stw r0, 0x68(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne SuikaBall_Init_L_80133C80
    li r3, 0x1b4
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133C7C
    li r4, 0x1
    bl WeatherSystem_Init
    SuikaBall_Init_L_80133C7C:
    stw r22, g_weatherSystem(r13)
    SuikaBall_Init_L_80133C80:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    lmw r22, 0x78(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" void fn_80133CA8(ShotOwner *self)
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)self)->shots[i].active) {
            Object_SetJObjPositionVec(self->model, &((ShotSet *)self)->shots[i].pos);
            Object_SetJObjRotationY(self->model, lbl_806D7298 * ((ShotSet *)self)->shots[i].rot);
            Object_SetColorAlphaOnly(self->model, 0, ((ShotSet *)self)->shots[i].alpha);
            Object_RenderJObjEx(self->model, LinkedNode_GetField10_OrFallback(self->model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(self->model, 0);
            Object_RenderJObjEx(self->model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < self->trailCount; j++) {
                float f = ((ShotSet *)self)->shots[i].trail[j].age / lbl_806D729C;
                float sc = lbl_806D72A0 - f;
                Object_SetJObjPositionVec(self->trailModel, &((ShotSet *)self)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(self->trailModel, 0, (lbl_806D72A4 - f) * ((ShotSet *)self)->shots[i].alpha);
                Object_RenderJObjTree(self->trailModel, 7);
            }
        }
    }
}

static inline bool Trail_Spawn(Trail *t, float c, float s)
{
    if (t->age >= 0) {
        return false;
    }
    t->age = 0;
    t->pos.x = 5.0f * LUT_Sin12Bit(360.0f * c);
    t->pos.y = 10.0f * s;
    t->pos.z = 5.0f * fn_80186960(360.0f * c);
    return true;
}

extern "C" void fn_80133E64(ShotOwner *self)
{
    Trail *tr;
    int i;
    for (i = 0; i < 6; i++) {
        Shot *s = &((ShotSet *)self)->shots[i];
        if (s->active) {
            tr = s->trail;
            s->pos.x += s->vel.x;
            s->pos.y += s->vel.y;
            s->pos.z += s->vel.z;
            s->vel.y -= 0.1f;
            float h = 0.0f;
            if (Terrain_GetGroundHeightWithPenetration(&s->pos, &h, 0, 0, 10.0f) == 1 && s->pos.y < h) {
                s->vel.y = 0.8f * -s->vel.y;
            }
            s->rot += 5.0f;
            if (s->rot > 360.0f) {
                s->rot -= 360.0f;
            }
            s->alpha = 1.0f - s->timer / 70.0f;
            int j;
            for (j = 0; j < self->trailCount; j++) {
                Trail *t = &tr[j];
                if (t->age >= 0) {
                    t->pos.y -= 2.0f;
                    if (++t->age > 10) {
                        t->age = -1;
                    }
                }
            }
            if ((s->timer & 3) == 0) {
                for (j = 0; j < self->trailCount; j++) {
                    if (Trail_Spawn(&tr[j], lbl_80495994[self->sinIdx], lbl_80495A94[self->cosIdx]) == true) {
                        tr[j].pos.x += s->pos.x;
                        tr[j].pos.y += s->pos.y;
                        tr[j].pos.z += s->pos.z;
                        break;
                    }
                }
                if (++self->sinIdx >= 0x40) {
                    self->sinIdx = 0;
                }
                if (++self->cosIdx >= 0x30) {
                    self->cosIdx = 0;
                }
            }
            if (++s->timer >= 0x46) {
                s->active = 0;
            }
        }
    }
}

extern "C" ModelPair *fn_80134164(ModelPair *self, short flag)
{
    if (self) {
        self->vt = lbl_8048E418;
        if (self) {
            self->vt = lbl_8048E34C;
            Object_DtorWithGXSync(self->a, 1);
            Object_DtorWithGXSync(self->b, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}


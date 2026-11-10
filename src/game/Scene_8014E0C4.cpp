#include "game/types/size_t.h"
#include "game/singleton.h"

/* sdata symbols referenced from asm */
extern unsigned char Scene_8014E0C4_data_806CF828[8];
extern unsigned char lbl_806D7F70[8];
extern unsigned char lbl_806D8134[7];
extern unsigned char lbl_806D813C[5];
/*
 * 0x8014E0C4..0x80157940: scene objects (kart/driver demo scene, menu
 * panels and their list helpers).
 */
#pragma cplusplus on

struct TextObjB {
    char pad0[0x20];
    unsigned int color;
    char pad24[0x230 - 0x24];
};

struct TextPairB {
    TextObjB top;
    TextObjB bottom;
};

struct TextPanelB {
    void *vt;
    unsigned char done;
    char pad5[3];
    void *sprite;
    TextPairB *text;
    int state;
    int timer;
    float alpha;
};


struct ResCtrl {
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    char pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    char pad44[0x14];
    ResCtrl();
    ~ResCtrl() {}
    inline void SetSize(float w, float h) {
        width = w;
        height = h;
    }
    inline void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
    inline void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
};

class VObjD {
public:
    virtual void v8();
    virtual ~VObjD();
    char pad4[8];
    void *robj;
    void *effect;
    float mtx[3][4];
    float pos[3];
};

class SceneCam {
public:
    virtual void _keySceneCam();
    virtual unsigned char Begin();
    virtual void End();
};

struct CreditPanel {
    void *vt;
    int f4;
    int state;
    float alpha;
    char pad10[4];
    int timer;
    int duration;
    unsigned char on;
    char pad1D[3];
    int credits;
    void *sprite;
};

struct ObjListSet;

struct CoursePanel {
    void *vt;
    int state;
    float t;
    float alpha;
    int mode;
    void *obj14;
    SceneCam *cam;
    void *lobjs;
    void *obj20;
    unsigned char active;
    char pad25[3];
    int phase;
    float phaseT;
    float blink;
    VObjD *objs[2];
    void *jobjs[2];
    unsigned char hidden[2];
    char pad46[2];
    void *obj48;
    ObjListSet *obj4C;
};


#include "game/types/NamCamObj.h"

struct CamPanel {
    void *vt;
    char pad4[0xC];
    NamCamObj *cam;
    char pad14[0xC];
    void *sprA;
    void *sprB;
};

struct VfxVec;
struct GXColorB {
    unsigned char r, g, b, a;
};

#include "game/types/Vec3f.h"

struct CamVecs {
    Vec3f eye;
    Vec3f up;
    Vec3f target;
};

#include "game/types/WGPipe.h"

#define GXFIFO (*(volatile WGPipe *)0xCC008000)

class VObjE {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
};

struct AttractEntry {
    int f0;
    int f4;
    unsigned char on;
};

struct AttractPanel {
    void *vt;
    unsigned char done;
    char pad5[3];
    VObjE *obj;
    int idx;
    char pad10[0x18];
    float t;
    int blink;
};

struct TexFadePanel {
    void *vt;
    int state;
    float t;
    unsigned char alpha;
    char padD[7];
    char texObj[0x20];
    char tlut[0x10];
};

struct ScrollSprite {
    char pad0[0xC];
    float x;
    float y;
    char pad14[8];
    float z;
    inline void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

struct NamCamPanel {
    void *vt;
    int state;
    float t;
    float scroll;
    NamCamObj *cam;
    float alpha;
    int mode;
    unsigned char logo;
    char pad1D[3];
    struct ScrollSprite *sprA;
    struct ScrollSprite *sprB;
    float width;
};

union ColWord {
    unsigned int w;
    struct {
        unsigned int rgb : 24;
        unsigned int a : 8;
    } f;
};

struct TextObj {
    char pad0[0x20];
    unsigned int color;
    char pad24[0x230 - 0x24];
};

struct TextPair {
    TextObj top;
    TextObj bottom;
};

struct TextPanel {
    void *vt;
    unsigned char done;
    char pad5[3];
    void *sprite;
    struct TextPair *text;
    int state;
    int timer;
    float alpha;
};


class VObjC {
public:
    virtual void v8();
    virtual void vC();
};

struct DemoPanel {
    void *vt;
    int f4;
    VObjC *f8;
};

struct FadeTimer {
    void *vt;
    int state;
    float t;
    unsigned char alpha;
};

struct FadeHolder2 {
    char pad0[0x10];
    void *fade;
    float alpha;
};


struct StatusInfo {
    char pad0[0xC];
    int fC;
    int f10;
    int f14;
};

struct LNode;
#include "game/types/LIter.h"

#include "game/types/ListHead.h"

struct FadeHolder {
    char pad0[0x10];
    void *fade;
};

struct QuadFade {
    char pad0[0xC];
    float alpha;
    unsigned char on;
};


#include "game/types/VObj.h"

struct Base {
    void *vt;
};

struct PalObj {
    void *vt;
    char pad4[0xC];
    void *pal;
};

struct StateObj {
    void *vt;
    int state;
    int state8;
};


extern "C" {
void *Alloc(unsigned long size);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
void MemoryManager_TimedFree(void *p);
extern void CourseObjectManager_Init();
extern void DrawManager_GetOrCreate();
void *FUN_8003b120(int size);
extern void ItemObjectManager_Init();
extern void KartDriver_Init(void *drv, int a, int kart, float (*mtx)[4], int slot, int b, int c);
extern void KartDriver_New_Empty();
void MemoryManager_Free(void *p);
void Object_ReleaseAnimResource(void *o);
extern void PSMTXIdentity(float (*m)[4]);
void PreloadEffectResources(int id);
void PreloadItemResources(int id);
void *ResolveJointByName(void *root, char *name);
void SetResourceLoadingFlag(int on);
extern void SoundChannels_ClearAll();
void TexMgr_SetTexture(void *t, const char *fmt, ...);
void TornadoEffect_Ctor(void *e, int a, void *kart, int id, int b, float x, float y, float z);
void TornadoEffect_SetFlagC0(void *e);
extern void __construct_array();
extern void __construct_new_array();
extern void clNormal3D_Construct();
void clNormal3D_SetScale(void *o, int a, float x, float y, float z, float w);
void fn_80121210(void);
extern void fn_8013D800();
extern void fn_80140874();
void *fn_8014DD5C(void *spr, int phase);
void *fn_8014E004(void *spr, int phase);
void *fn_8014E028(void *spr, int phase);
extern void fn_80157B20();
extern void fn_80157D18();
extern unsigned char fn_80169E10(void);
int fn_80169E20(void);
extern void fn_80171CD0();
char *fn_80293BBC(void);
int isJapanese(void);
extern unsigned int g_kartStartSlot;
extern const float lbl_806D7F68[2];
extern const float lbl_806D8064;
extern const float lbl_806D8068;
extern const float lbl_806D8070;
extern const float lbl_806D8074;
extern const float lbl_806D8078;
extern const float lbl_806D807C;
extern const float lbl_806D8080;
extern unsigned int dtor_800869D0[];
extern unsigned int fn_80149214[];
extern unsigned int DemoScene1C0_vtable_8048FED8[];
extern unsigned int lbl_8048FF80[];
extern void CreditMgr_DrawCoinCreditBanner(int slot, unsigned int color, int count);
extern void HSD_StateInvalidate(int mask);
extern unsigned char IsCardValid(void);
extern float LUT_Sin12Bit(float x);
extern int PcbSync_CountJoinedPcbsAdvancedKarts(void);
float Saturate_Double(float x, float lo, float hi);
extern unsigned char Sci2Card_GetReceiptTestFlag(void);
extern unsigned char ServiceEnable_Get(void);
extern void ServiceMode_UpdateScheduleGate(void);
extern unsigned char ServiceValue_Get(void);
extern void __cvt_fp2unsigned();
void fn_8011F994(int layer);
extern void fn_80169334(int a, int res, int b, float x, float y, float sx, float sy, float alpha);
extern unsigned int lbl_806D8084;
extern unsigned int lbl_806D8088;
extern unsigned int lbl_806D808C;
extern unsigned int lbl_806D8090;
extern unsigned int lbl_806D8094;
int CreditMgr_GetCreditCount(int slot);
void GXDrawDone(void);
unsigned char GetVBlankFlag(void);
void NamCam_End(void);
void NamCam_Init(void);
#ifndef NON_MATCHING
extern void OperationClock_Commit();
extern void RaceFlow_ResetState_FullColdInit();
extern void RumbleUpdate();
extern void SetCourseParams();
#else /* NON_MATCHING */
void OperationClock_Commit(void);
void RaceFlow_ResetState_FullColdInit(void);
void RumbleUpdate(void);
void SetCourseParams(int course, int a, int b, int c);
#endif /* NON_MATCHING */
extern void SetSyncTarget(int target);
extern void Sprite_InitWithAnim();
void *StrPcb_GetInstance(void);
void StrPcb_ResetCommands_NeutralDefault(void *pcb);
void StrPcb_ResetCommands_Zero(void *pcb, int arg);
#ifndef NON_MATCHING
extern void TEXBindPaletteEntry_RGB();
extern void TEXLoadPalette_Retry();
extern void TitleTracker_OnAttract_Stub();
#else /* NON_MATCHING */
void TEXBindPaletteEntry_RGB(void *pal, void *out, int idx);
void TEXLoadPalette_Retry(void **out, char *name);
void TitleTracker_OnAttract_Stub(struct TitleDB *db);
#endif /* NON_MATCHING */
unsigned char VBlankValue_Get(void);
void fn_8002CFB8(int a, int b, int c, int d);
void fn_801699D8(int a, int b);
#ifndef NON_MATCHING
extern void fn_8019FEF4();
#else /* NON_MATCHING */
void fn_8019FEF4(void *spr);
#endif /* NON_MATCHING */
void fn_801B7CD0(int a);
extern void fn_801F6804(void *p);
extern unsigned int g_cupId;
extern unsigned int g_currentSceneState;
extern struct TitleDB *lbl_806D10A0;
#ifndef NON_MATCHING
extern unsigned int lbl_806D12E1;
#else /* NON_MATCHING */
extern unsigned char lbl_806D12E1;
#endif /* NON_MATCHING */
extern unsigned int jumptable_8048FDCC[];
extern unsigned int EntryScene_vtable_8048FE14[];
extern unsigned int CourseDemoScene_vtable_8048FE3C[];
extern unsigned int StatusNoticeScene_vtable_8048FE64[];
extern unsigned int StatusLogoScene_vtable_8048FE8C[];
extern unsigned int AttractScene_vtable_8048FF64[];
#ifndef NON_MATCHING
extern void dtor_80080330();
#endif /* ! NON_MATCHING */
unsigned char Sprite_AdvanceAnim(void *s, float dt);
extern const float lbl_806D8060;
extern unsigned int lbl_806D8098;
extern unsigned int lbl_806D80A0;
void CreditMgr_SetActiveSlot(int slot);
void clRom_PurgeAll(void);
void fn_80120A08(int id);
void fn_80169C44(void);
void fn_801933D0(int a);
extern struct StatusInfo *Scene_8014E0C4_bss_806D1580;
extern unsigned int lbl_803FE0C8[];
void InitRumbleController(int on);
unsigned char PreloadResource(int id);
void SetLocalPcbRole(int role);
extern VObj *g_pInputState;
extern bool lbl_806D117C;
extern unsigned char lbl_806D12B0;
extern unsigned char lbl_806D12E2;
extern int lbl_80598A60[];
extern void dtor_8007D0D4();
void OverlayText(int a, int b, int line, const char *fmt, ...);
extern const char *Scene_8014E0C4_data_8048FD50[];
void Sprite_Destroy(void *s, int flag);
extern unsigned int NamCamPanelC_vtable_8048FFC0[];
void FlashFadeOverlay_Draw(void *h, float a, float b, float c, float d, float e, float f);
extern unsigned int lbl_806D80A8;
extern unsigned int lbl_806D80AC;
extern unsigned int lbl_806D80B0;
extern unsigned int lbl_806D80B4;
extern int NamCam_GetImageHandle(void *out, int arg);
extern void NamCam_LoadImage(void *handle, void *buf, void *out);
extern unsigned char PcbSync_AllKartsInValidSelectState(void);
extern void ResCtrl_Init();
void fn_8011FAFC(struct ResCtrl *c, int layer);
extern void fn_80121E10(struct ResCtrl *c);
extern void fn_801698B4(int layer, int id, int flag, float x, float y);
void fn_801A0004(void *p);
void fn_801A1280(void);
extern unsigned int lbl_806D80B8;
extern unsigned int lbl_806D80C4;
extern unsigned int lbl_806D80C8;
extern unsigned int lbl_806D80D4;
extern unsigned int lbl_806D80D8;
extern unsigned int lbl_806D80DC;
extern unsigned int lbl_806D80E0;
extern unsigned int lbl_806D80E4;
extern unsigned int lbl_806D80E8;
extern unsigned int lbl_806D80EC;
extern void dtor_80082960();
extern unsigned int lbl_806D80F0;
extern unsigned int lbl_806D80F4;
extern unsigned int lbl_806D80F8;
void __destroy_new_array(void *p, void *dtor);
extern unsigned int TextPanelC_vtable_8048FFE8[];
void fn_8011FAB8(void);
void fn_801F8A34(void *a, void *b, int c);
void *fn_801F8E58(void);
void fn_801F93D0(void *t, float sx, float sy);
void fn_801F93EC(void *t, float x, float y);
extern unsigned int lbl_806D80FC;
extern unsigned int lbl_806D8100;
extern unsigned int lbl_806D8104;
extern unsigned int lbl_806D8108;
void HSD_CObjAnim(void *cobj);
void HSD_CObjReqAnim(void *cobj, float frame);
extern void JObj_Hide();
extern void Scene3D_Init();
extern void SceneModel_Init();
void clNormal3D_Exec(void *o);
extern unsigned int lbl_806D806C;
extern unsigned int lbl_80419EF8[];
void CourseEnvironment_Dtor(void *p, int flag);
void KartDriver_Dtor(void *p, int flag);
void SetActiveCamera(void *cam, int a);
void TireEffect_ResetSpin(void *e, float a, float b);
void VisualEffectHolder_Dtor(void *p, int flag);
void fn_8013D4B0(void *p, float a);
void fn_8013D738(void *o, float a, float b);
extern unsigned int g_playerRenderObj;
extern void *g_raceCamera;
void ClRomTable_PurgeAll(void);
void ItemObjectManager_Reset(void);
void LObjList_Destroy(void *p, int flag);
void Object_DtorWithGXSync(void *o, int flag);
void SceneDrawList_Reset(void);
void SetCourseScene3D(void *s);
void VfxSlotMgr_Shutdown(void);
void fn_8013DB9C(void);
unsigned char fn_8019083C(int slot);
void fn_801909A4(int slot);
extern struct VObj *lbl_806D10AC;
extern unsigned int RaceSceneC_vtable_80490010[];
void CObj_DebugVizPathFlush(void *c);
void CourseEnvironment_RenderObjects_Timed(void *env);
void DrawEffect_TickAndCull(void);
void HSD_LObjDeleteCurrentAll(int a);
void ItemObjectManager_Render(void);
void KartDriver_RenderTimed(void *d, int pass, int a);
void KartItem_DispatchEffectRenderByState(void *e);
void KartItem_FlushPendingRender(void *e);
void KartItem_FlushPendingRender_v2(void *e);
void KartItem_FlushRenderIfReady(void *e);
void LObjList_ApplyForCObj(void *l);
void Object_RenderJObjTree(void *j, int mask);
void Subsystem36c_DispatchPass2_Timed(void *env);
void TornadoEffect_SubmitRender(void *e);
void TransparentDraw_SortAndDispatch(void);
void clDrawMan_Buckets_Dispatch(VObj *dm);
void clDrawMan_Buckets_Reset(VObj *dm);
void clDrawMan_EndFrame_NoOp(VObj *dm);
void fn_8013D940(int layer);
void fn_801695E0(int layer, int id, int c, float x, float y, float s);
void fn_802BD6AC(float u, float v);
void fn_802BD6C0(void);
extern const float lbl_806D7F58[2];
extern unsigned int lbl_806D810C;
extern unsigned int lbl_806D8110;
extern unsigned int lbl_806D8114;
extern unsigned int lbl_806D8118;
extern unsigned int lbl_806D811C;
extern unsigned int lbl_806D8120;
extern unsigned int lbl_806D8124;
extern unsigned int lbl_806D8128;
extern unsigned int lbl_806D812C;
extern unsigned int lbl_806D8130;
float BuildOrientationFromYaw(float yaw);
void CObj_ApplyScissor(void *cam, void *out);
void CObj_LoadProjMatrix(void *cam, void *out);
unsigned char ClSound_PlayBgmStream(int id, int a);
unsigned char ClStream_IsActive(int h);
int ClStream_PlayMono(int id, int a, int b);
void ClStream_Stop(int h);
void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
void *DrawEffect_SpawnByType(unsigned char type);
void HSD_JObjSetupMatrixSub(void *jobj);
void ItemEffectBus_SnapshotAndFullReset(void *bus);
void ItemEffectBus_TickTornadoCooldown(void *bus);
void ItemObjectManager_Update(void);
void *KartDriver_GetJointByIdx(void *drv, int idx);
void KartDriver_TickAction_79268_AndSetSlot5aEulerZ(void *drv, float z);
float Mtx44_GetPitchOfPosZ_Padded(void *m);
void Mtx44_GetTranslation_RowMajor(void *out, void *m);
float Mtx44_GetYawOfPosZ_Padded(void *m);
void Object_SetField8_AndDirty(void *o, float v);
void PSMTXCopy(const void *src, void *dst);
unsigned char *PcbSyncTable_Ptr(void);
void RenderObj_ItemStateMachine_Timed(void *o, int a, float b, float c);
void SceneRender_SetViewportRect(void *cam, float a, float b, float c, float d, float e, float f);
void TornadoEffect_SetColorPairC8CC(void *e, int a, int b);
void TornadoEffect_SetFlagB4(void *e, int f);
void TornadoEffect_SetScalePairB0BC(void *e, float a, float b);
void TornadoEffect_Tick(void *e, int a);
void Vec3_Copy(void *dst, void *src);
void VfxSlotMgr_Update(struct VfxVec eye, struct VfxVec target);
void __assert(char *file, int line, char *expr);
void clStream_setVolume(int id, int vol);
float fn_800D3184(void *a, void *b);
void fn_8013D59C(void *p, float x, float y, float z);
void fn_8013D608(void *p, float x, float y, float z);
void fn_8013D634(void *p, float x, float y, float z);
void fn_8013D660(void *p, float x, float y);
void fn_8013D704(void *p);
void fn_8013DAC8(void *p, int layer);
void fn_80194AE0(int h, int vol);
void *fn_801B3A50(int id);
extern unsigned int g_pcbSyncReady;
extern unsigned int lbl_806D80BC;
extern unsigned int lbl_806D80CC;
extern unsigned int lbl_806D8144;
extern unsigned int lbl_806D8148;
extern unsigned int lbl_806D814C;
extern unsigned int lbl_806D8150;
extern unsigned int lbl_806D8154;
extern unsigned int lbl_806D8158;
extern unsigned int lbl_806D815C;
extern unsigned int lbl_806D8160;
extern unsigned int lbl_806D8164;
extern unsigned int lbl_806D8168;
extern unsigned int lbl_806D816C;
extern unsigned int lbl_806D8170;
extern unsigned int lbl_806D8174;
extern unsigned int lbl_806D8178;
extern unsigned int lbl_806D817C;
extern const float lbl_806D8180;
extern unsigned int lbl_80419FB8[];
extern void Camera_Create();
extern void DMAChannelManager_Init();
extern void FileLoader_Open(void *path);
extern void *GetCourseDataPtr();
extern void *HSD_LObjLoadDesc(void *desc);
extern void InputManager_Init();
extern void fn_8013DBF8();
extern unsigned int g_courseVariantIdx;
extern unsigned int g_longRoundFlag;
extern const float lbl_806D80C0;
extern const float lbl_806D8184;
extern unsigned int lbl_8041BC00[];
extern void C_MTXLookAt(float m[3][4], const struct Vec3f *eye, const struct Vec3f *up, const struct Vec3f *target);
extern void C_MTXOrtho(float m[4][4], float t, float b, float l, float r, float n, float f);
extern void GXBegin(int prim, int fmt, unsigned short n);
extern void GXClearVtxDesc(void);
extern void GXLoadPosMtxImm(float m[3][4], unsigned long id);
extern void GXSetBlendMode(int type, int src, int dst, int op);
extern void GXSetChanCtrl(int chan, unsigned char enable, int amb, int mat, unsigned long lights, int diff, int attn);
extern void GXSetChanMatColor(int chan, struct GXColorB color);
extern void GXSetCurrentMtx(unsigned long id);
extern void GXSetNumChans(unsigned char n);
extern void GXSetNumTevStages(unsigned char n);
extern void GXSetNumTexGens(unsigned char n);
extern void GXSetProjection(float m[4][4], int type);
extern void GXSetScissor(unsigned long x, unsigned long y, unsigned long w, unsigned long h);
extern void GXSetTevOp(int stage, int mode);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetViewport(float x, float y, float w, float h, float n, float f);
extern void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, unsigned char frac);
extern void GXSetVtxDesc(int attr, int type);
extern void GXSetZCompLoc(unsigned char before);
extern void GXSetZMode(unsigned char enable, int func, unsigned char update);
extern const GXColorB lbl_806DCF38;
extern unsigned int lbl_806D8188;
struct TaEntry *TaRecord_GetEntry_Indexed(int a, int b, int course, int c, int d);
float TaRecord_GetTime_Indexed(int a, int b, int course, int c, int d);
int fn_8013BFCC(int chr);
int fn_80167744(int n, float t);
void fn_80167DDC(void *dst, const unsigned short *fmt, float x, float y, ...);
void fn_80168910(void *dst, const char *fmt, float x, float y, float sx, float sy, ...);
void fn_80168A4C(void *dst, const char *fmt, float x, float y, ...);
const char *get_title_name(void *db, int title, int variant, int chr, int a);
extern unsigned int lbl_806D818C;
extern unsigned int lbl_806D8190;
extern unsigned int lbl_806D8194;
extern unsigned int lbl_806D8198;
extern unsigned int lbl_806D819C;
extern unsigned int lbl_806D81A0;
extern unsigned int lbl_806D81A4;
extern unsigned int lbl_806D81A8;
extern unsigned int lbl_806D81AC;
extern unsigned int lbl_806D81B0;
extern unsigned int lbl_806D81B4;
extern unsigned int lbl_806D81B8;
extern unsigned int lbl_806D81BC;
extern unsigned int lbl_806D81C0;
extern unsigned int lbl_806D81C4;
extern unsigned int lbl_806D81C8;
extern unsigned int lbl_806D81CC;
extern unsigned int lbl_806D81D0;
extern unsigned int lbl_806D81D4;
extern unsigned int lbl_806D81D8;
extern unsigned int lbl_806D81DC;
extern unsigned int lbl_806D81E0;
extern unsigned int lbl_806D81E4;
extern unsigned int lbl_806D81E8;
extern unsigned int lbl_806D81EC;
extern unsigned int lbl_806D81F0;
extern unsigned int lbl_806D81F4;
extern unsigned int lbl_806D81F8;
extern unsigned int lbl_806D81FC;
extern unsigned int lbl_806D8200;
extern unsigned int lbl_806D8204;
extern unsigned int lbl_806D8208;
extern unsigned int lbl_806D820C;
extern unsigned int lbl_806D8210;
extern unsigned int lbl_806D8214;
extern unsigned int lbl_806D8218;
extern unsigned int lbl_806D821C;
extern unsigned int lbl_806D8220;
void TEXReleasePalette(void **pal);
extern unsigned int lbl_806D8224;
extern void GXLoadTexObj(void *obj, int id);
extern void GXSetTexCoordGen2(int dst, int func, int src, unsigned long mtx, unsigned char normalize, unsigned long postmtx);
extern unsigned int lbl_806D8228;
extern unsigned int lbl_806D822C;
extern unsigned int lbl_806D8230;
extern unsigned int lbl_806D8234;
extern unsigned int lbl_806D8238;
extern unsigned int lbl_806D823C;
extern unsigned int lbl_806D8240;
extern unsigned int lbl_806D8244;
extern void fn_801F6790(void *p);
void fn_80140810(void *p, int flag);
extern void __destroy_arr(void *, void *, unsigned long, unsigned long);
void fn_80157940(struct LIter *ret, void *list, struct LIter *b, struct LIter *e);
void fn_80157B38(struct LIter *ret, void *list, struct LIter *b, struct LIter *e);
void ItemEffectBus_ApplyItemEventClear(void *bus, int item);
void ItemEffectBus_ApplyItemEventSet(void *bus, int item, int a);
void TornadoEffect_ApplyItemVisual_Primary(void *e, int item);
void TornadoEffect_ApplyItemVisual_Secondary(void *e, int item, int a);
void TornadoEffect_ClearFlagC0AndSetC4(void *e, float v);
void fn_80140344(void *o);
void fn_80169468(int layer, int id, int flags, float x, float y, float sx, float sy, float a, float b);
extern unsigned int lbl_806D80D0;
extern unsigned int lbl_806D8248;
extern unsigned int lbl_806D824C;
extern unsigned int lbl_806D8250;
extern unsigned int lbl_806D8254;
extern unsigned int lbl_806D8258;
extern unsigned int lbl_806D825C;
extern unsigned int lbl_806D8260;
extern unsigned int lbl_806D8264;
extern unsigned int lbl_806D8268;
extern unsigned int lbl_806D826C;
extern unsigned int lbl_806D8270;
extern unsigned int lbl_806D8274;
extern unsigned int lbl_806D8278;
extern unsigned int lbl_806D827C;
extern unsigned int lbl_806D8280;
extern unsigned int lbl_806D8284;
extern unsigned int lbl_806D8288;
extern unsigned int lbl_806D828C;
extern unsigned int lbl_806D8290;
float LookupCos(float a);
float LookupSin(float a);
void fn_80157C60(void *ret, void *list, void *pos, const void *val);
void fn_80157DE0(void *ret, void *list, void *pos, const void *val);
void fn_801F6D58(void *d, void *name, int a, int b);
void fn_801F6E84(void *d, int a, int b);
void fn_801F6EAC(void *d, int r, int g, int b, int a);
void fn_801F6ED0(void *d, float sx, float sy);
void fn_801F6EEC(void *d, float rot);
void fn_801F70F0(void *d, float x, float y, float z);
void fn_801F7198(void *res, void *d, int a);
void fn_801F7344(void *res, void *d);
extern void fn_801F7D50();
void fn_801F7E98(void *d);
void HSD_JObjClearFlagsAll(void *j, int flags);
void HSD_JObjDispAll(void *j, int a, int b, int c);
void HSD_JObjSetFlagsAll(void *j, int flags);
void fn_8014017C(void *p);
void dtor_80060024(void *p, int flag);
extern unsigned int DemoKart_vtable_8048FF20[];
void fn_8013A6F8(void);
void fn_80173CC4(void *o, int flag);
extern VObj *lbl_806D10D0;
extern unsigned int DemoScene_vtable_8048FF3C[];
void PSMTXTrans(void *m, float x, float y, float z);
void clItemBoxManager_Update(void *mgr);
void fn_8013A534(void);
void fn_801737F0(void *o);
void fn_80173B68(void *o, void *robj);
void fn_80173BE8(void *o);
void fn_80173C34(void *o);
extern unsigned int lbl_806D8294;
extern unsigned int lbl_806D8298;
extern unsigned int lbl_806D829C;
extern unsigned int lbl_806D82A0;
extern unsigned int lbl_806D82A4;
extern unsigned int lbl_806D82A8;
extern unsigned int lbl_806D82AC;
extern unsigned int lbl_806D82B0;
extern unsigned int lbl_806D82B4;
extern unsigned int lbl_806D82B8;
extern unsigned int lbl_806D82BC;
extern unsigned int lbl_806D82C0;
extern unsigned int lbl_806D82C4;
extern unsigned int lbl_806D82C8;
extern unsigned int lbl_806D82CC;
extern unsigned int lbl_806D82D0;
extern unsigned int lbl_806D82D4;
extern unsigned int lbl_806D82D8;
extern unsigned int lbl_806D82DC;
extern unsigned int lbl_806D82E0;
extern unsigned int lbl_806D82E4;
extern unsigned int lbl_806D82E8;
extern unsigned int lbl_806D82EC;
extern unsigned int lbl_806D82F0;
extern unsigned int lbl_806D82F4;
extern unsigned int lbl_806D82F8;
extern unsigned int lbl_806D82FC;
extern unsigned int lbl_806D8300;
extern unsigned int lbl_806D8304;
extern unsigned int lbl_806D8308;
extern unsigned int lbl_806D830C;
extern unsigned int lbl_806D8310;
extern unsigned int lbl_806D8314;
extern unsigned int lbl_806D8318;
extern unsigned int lbl_806D831C;
extern unsigned int lbl_806D8320;
extern unsigned int lbl_806D8324;
extern unsigned int lbl_806D8328;
extern unsigned int lbl_806D832C;
extern unsigned int lbl_806D8330;
extern unsigned int lbl_806D8334;
extern unsigned int lbl_806D8338;
extern unsigned int lbl_806D833C;
extern unsigned int lbl_806D8340;
extern unsigned int lbl_806D8344;
extern unsigned int lbl_806D8348;
extern unsigned int lbl_806D834C;
void clItemBoxManager_Draw(VObj *m);
void fn_80139810(void);
void fn_801737CC(void *p);
extern void fn_801696E4(int layer, int id, int flag, float x, float y, float rot);
extern void fn_801697C0(int layer, int id, int flag, float x, float y, float sx, float sy);
extern unsigned int lbl_806D8350;
extern unsigned int lbl_806D8354;
extern unsigned int lbl_806D8358;
extern unsigned int lbl_806D835C;
extern unsigned int lbl_806D8360;
extern unsigned int lbl_806D8364;
extern unsigned int lbl_806D8368;
extern unsigned int lbl_806D836C;
extern unsigned int lbl_806D8370;
extern unsigned int lbl_806D8374;
extern unsigned int lbl_806D8378;
extern unsigned int lbl_806D837C;
extern unsigned int lbl_806D8380;
extern unsigned int lbl_806D8384;
extern unsigned int lbl_806D8388;
void fn_80157EA8(void *l);
class PairObj : public VObj {
public:
    PairObj(const char *name, int flag);
    virtual ~PairObj();
    virtual void Update();
    char data[0x1C];
};

struct PairPos {
    float x;
    float y;
};

struct VObjPair {
    PairObj *a;
    PairObj *b;
    unsigned char started;
    char pad9[3];
    int mode;
    float t;
    unsigned char on[5];
    char pad19[3];
    PairPos pos[5];
    PairPos scale[5];
    float vel[5];
    unsigned char aOn;
    char pad81[3];
    PairPos aPos;
    PairPos aScale;
    float aVel;
    VObjPair();
    void Update();
    void Draw() {
        if (mode == 1) {
            int k;
            for (k = 0; k < 5; k++) {
                if (on[k] && pos[k].x > 0.0f) {
                    fn_8013D660(b, pos[k].x, pos[k].y);
                    fn_8013D608(b, scale[k].x, scale[k].y, scale[k].x);
                    b->Update();
                }
            }
            if (aOn) {
                fn_8013D660(a, aPos.x, aPos.y);
                fn_8013D608(a, aScale.x, aScale.y, aScale.x);
                a->Update();
            }
        }
    }
    ~VObjPair() {
        delete a;
        delete b;
    }
};

class CourseFx : public VObj {
public:
    virtual ~CourseFx();
    virtual void vC();
    virtual void Draw();
};

struct CourseSprKey {
    float time;
    float x, y, sx, sy, rot, r, g, b, a;
};

struct CourseSprTrack {
    CourseSprKey *keys;
    int id;
    int flags;
};

struct CourseItemEvent {
    float time;
    int kart;
    int item;
    unsigned char set;
};

struct CourseCamKey {
    float time;
    int phase;
};

struct CourseScene {
    void *vt;
    int variant;
    int state;
    float t;
    float alpha;
    void *obj14;
    SceneCam *cam;
    void *lobjs;
    void *obj20;
    CourseSprTrack *tracks;
    unsigned char bgmOn;
    unsigned char active;
    char pad2A[2];
    unsigned int keyIdx;
    float keyT;
    void *drivers[6];
    void *effects[6];
    float mtx[6][3][4];
    void *jobjs[6];
    unsigned char hidden[6];
    char pad1A2[2];
    int color;
    CourseFx *obj1A8;
    void *obj1AC;
    unsigned char on1B0;
    char pad1B1[3];
    VObjPair *pair;
    ObjListSet *list;
    void *arr;
};

struct SetLLink {
    struct SetLNode *prev;
    struct SetLNode *next;
};

struct SetLNode : SetLLink {
    void *obj;
    char data[4];
};

class SetLIter {
public:
    SetLNode *n;
    SetLIter(SetLNode *p) : n(p) {}
    SetLIter(const SetLIter &o) : n(o.n) {}
};

struct SetSubList;
extern "C" SetLIter fn_80157D30(SetSubList *l, SetLIter b, SetLIter e);

struct SetSubList {
    unsigned int size;
    SetLLink anchor;
    SetLNode *begin() { return anchor.next; }
    SetLNode *end() { return (SetLNode *)&anchor; }
    void clear() { fn_80157D30(this, begin(), end()); }
};

extern "C" void GX_EndDraw(int a);
extern "C" void GX_BeginDraw(void);
extern "C" void fn_801F7B74(void *obj, void *data, float a);

struct ObjListSet {
    char pad0[0x18];
    SetSubList sub[2];
    void FlushLayer(unsigned int layer) {
        if (layer < 2 && sub[layer].size != 0) {
            SetLNode *e;
            SetLNode *n;
            GX_EndDraw(0);
            e = sub[layer].end();
            for (n = sub[layer].begin(); n != e; n = n->next) {
                fn_801F7B74(n->obj, n->data, -1.0f);
            }
            GX_BeginDraw();
            sub[layer].clear();
        }
    }
    void FlushAll() {
        unsigned int i;
        for (i = 0; i < 2; i++) {
            FlushLayer(i);
        }
    }
};

struct HsdClassInfo {
    char pad[0x30];
    void (*release)(struct HsdObj *o);
    void (*destroy)(struct HsdObj *o);
};

struct HsdObj {
    HsdClassInfo *info;
    unsigned short ref;
};

class RaceCam : public VObj {
public:
    virtual ~RaceCam();
    virtual unsigned char Begin();
    virtual void End();
};

struct RaceUV {
    float u;
    float v;
};

struct CourseModeInfo {
    int time;
    int id;
    unsigned char env;
    unsigned char transparent;
    char padA[2];
    int fC;
    int f10;
    const char *name;
};

struct SprEntry {
    unsigned int key;
    char name[8];
    float w;
    float h;
};



struct RaceScriptEntry {
    int start;
    int f4;
    int type;
    int arg;
    const char *joint;
};

struct RaceScene {
    void *vt;
    int started;
    int mode;
    int timer;
    unsigned char done;
    unsigned char cardOn;
    char pad12[2];
    int cardSlot;
    int scriptIdx;
    void *env;
    VObj *camera;
    HsdObj *lights;
    RaceCam *objs[21];
    void *lists[21];
    void *models[21];
    void *drivers[11];
    void *effects[11];
    float mtx[11][3][4];
    unsigned char active[11];
    char pad397;
    RaceUV uv[11];
    void *sprites[48];
    int spriteOn[48];
    unsigned int stream;
    VObj *obj574;
    RaceScriptEntry *script;
    int scriptCount;
};

void *fn_8014E0C4(int a);
void fn_8014E618(AttractPanel *self);
#ifndef NON_MATCHING
asm void fn_8014E804(void);
#else /* NON_MATCHING */
void fn_8014E804(struct StatusView *self);
#endif /* NON_MATCHING */
void fn_8014F164(CreditPanel *self);
DemoPanel *fn_8014F2DC(DemoPanel *self, short flag);
void fn_8014F3D8(void *self);
void fn_8014F5A8(VObj *p);
void fn_8014F5E0(void);
void *fn_8014F6A4(void);
unsigned char fn_8014F6E0(StateObj *o);
CamPanel *fn_8014F6F4(CamPanel *self, short flag);
void fn_8014F81C(VObj *p);
void fn_8014F854(FadeHolder *self);
void fn_8014F8FC(NamCamPanel *self);
void fn_8014FC40(void);
unsigned char fn_8014FE08(unsigned char *o);
Base *fn_8014FE10(Base *self, short flag);
void fn_8014FEC4(VObj *p);
void fn_8014FEFC(TextPanelB *self);
void fn_80150004(TextPanel *self);
extern "C" void fn_801502AC(RaceScene *self, int mode);
unsigned char fn_80150924(unsigned char *o);
RaceScene *fn_8015092C(RaceScene *self, short flag);
void fn_80150BE4(VObj *p);
void fn_80150C1C(RaceScene *self);
void fn_80151234(RaceScene *self);
extern "C" void fn_80151F08();
void DrawColoredQuad(int r, int g, int b, int a, float x, float y, float w, float h);
void fn_80152930(VObj *p);
Base *fn_80152968(Base *self, short flag);
unsigned char fn_801529EC(StateObj *o);
void fn_80152A00(CreditPanel *self);
void fn_80152B2C(VObj *p);
Base *fn_80152B64(Base *self, short flag);
void fn_80152C00(struct TaPanel *self);
unsigned char fn_80153504(StateObj *o);
void fn_80153518(QuadFade *self);
void fn_80153594(VObj *p);
PalObj *fn_801535CC(PalObj *self, short flag);
void fn_80153668(FadeTimer *o);
unsigned char fn_80153758(StateObj *o);
void fn_8015376C(TexFadePanel *self);
void fn_80153A3C(VObj *p);
PalObj *fn_80153A74(PalObj *self, short flag);
void fn_80153AFC(FadeTimer *o);
unsigned char fn_80153BEC(StateObj *o);
void fn_80153C00(TexFadePanel *self);
void fn_80153ED0(VObj *p);
CourseScene *fn_80153F08(CourseScene *self, short flag);
struct ObjListSetFull;
ObjListSetFull *fn_801540E0(ObjListSetFull *o, short flag);
void fn_80154304(CourseScene *self);
void fn_80154FB0(struct SprScene *self, unsigned int layer, unsigned int id, unsigned int flags, float x, float y, float sx, float sy, float rot, float r, float g, float b, float a);
unsigned char fn_80155398(StateObj *o);
void fn_801553AC(CourseScene *self);
Base *fn_801556A0(Base *self, short flag);
int fn_8015571C(char *o, float *a, float *b, float *c);
void fn_8015573C(VObj *p);
CoursePanel *fn_80155774(CoursePanel *self, short flag);
void fn_801558CC(CoursePanel *self);
unsigned char fn_80156FC0(StateObj *o);
void fn_80156FD4(CoursePanel *self);
void fn_80157240(VObj *p);
CamPanel *fn_80157278(CamPanel *self, short flag);
void fn_80157378(NamCamPanel *self);
unsigned char fn_801576D8(StateObj *o);
void fn_801576EC(FadeHolder2 *self);
void fn_801577C4(void);
int fn_801577C8(void);
void fn_801577D0(void);
Base *dtor_801577D4(Base *self, short flag);
void fn_8015781C(void);
void *fn_80157820(void *l);
ListHead *dtor_80157850(ListHead *self, short flag);
ListHead *dtor_801578C8(ListHead *self, short flag);

#pragma section R ".extab_user"



#ifndef NON_MATCHING
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; void *f56; unsigned int f57; unsigned int f58; void *f59; unsigned int f60; void *f61; unsigned int f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; unsigned int f71; void *f72; unsigned int f73; void *f74; unsigned int f75; void *f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; void *f83; unsigned int f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; unsigned int f100; void *f101; unsigned int f102; void *f103; unsigned int f104; void *f105; unsigned int f106; void *f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; void *f115; unsigned int f116; void *f117; } extab_fn_8014E804 = { 0x180A0000, 0x00000248, 0x000000E4, 0x00000260, 0x001700D8, 0x000002FC, 0x00000104, 0x00000314, 0x000D00F8, 0x00000430, 0x00000118, 0x00000498, 0x00120134, 0x000004F8, 0x0000012C, 0x00000508, 0x00000134, 0x00000520, 0x00000148, 0x00000540, 0x00050134, 0x000005B4, 0x0011015C, 0x00000610, 0x00000154, 0x00000620, 0x0000015C, 0x00000638, 0x00000170, 0x00000658, 0x0005015C, 0x000006C0, 0x000E0184, 0x0000071C, 0x0000017C, 0x0000072C, 0x00130184, 0x000007DC, 0x00000198, 0x00000808, 0x000001A0, 0x00000850, 0x000001A8, 0x00000874, 0x000001B0, 0x000008A0, 0x000001B8, 0x000008C4, 0x000001C0, 0x000008E8, 0x000001C8, 0x0000090C, 0x000001D0, 0x00000000, 0x0780001D, 0x00000034, (void *)&dtor_80080330, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0780001D, 0x00000034, (void *)&dtor_80080330, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x01000134, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0100015C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };
#endif /* ! NON_MATCHING */




























































#pragma section R ".extabindex_user"



#ifndef NON_MATCHING
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014E804 = {
    (void *)&fn_8014E804, 0x00000960, (void *)&extab_fn_8014E804
};
#endif /* ! NON_MATCHING */




























































}


struct Panel44 {
    inline Panel44() { fn_8014F3D8(this); }
    char pad[0x44];
};


struct TextPanelIds {
    int id[4];
};

#include "src/game/Scene_8014E0C4_rodata.inc"

/* .data 0x8048F178..0x8048FDB0 */
extern const char lbl_806D8020[];
extern const char lbl_806D8028[];
extern const char lbl_806D8030[];
extern const char lbl_806D8038[];
extern const char lbl_806D8040[];
extern const char lbl_806D8048[];
extern const char lbl_806D8050[];
extern const char lbl_806D8058[];
extern char Scene_8014E0C4_data_806CF830[];
extern char Scene_8014E0C4_data_806CF838[];

#pragma push
#pragma force_active on
static const char *Scene_8014E0C4_data_8048F178[12] = {
    lbl_803643DC, lbl_803643F0, lbl_80364404, lbl_80364418, lbl_8036442C, lbl_80364440, lbl_80364454, lbl_80364468, lbl_8036447C, lbl_80364490, lbl_803644A8, lbl_803644BC,
};

static const char *Scene_8014E0C4_data_8048F1A8[6] = {
    lbl_80364B28, lbl_80364B3C, lbl_80364B50, lbl_80364B64, lbl_80364B78, lbl_80364B90,
};

static RaceScriptEntry lbl_8048F1C0[51] = {
    {1, 0, 2, 0, 0},
    {4, 0, 8, 0, 0},
    {4, 0x78, 0, 0, 0},
    {6, 0, 0, 1, 0},
    {7, 0, 0, 2, 0},
    {7, 0x3C, 0, 3, 0},
    {7, 0x78, 0, 4, 0},
    {7, 0xB4, 0, 5, 0},
    {8, 0, 0, 6, 0},
    {8, 0x1E, 0, 7, 0},
    {8, 0x3C, 0, 8, 0},
    {8, 0x5A, 0, 9, 0},
    {8, 0x78, 0, 0xA, 0},
    {8, 0x96, 0, 0xB, 0},
    {8, 0xB4, 0, 0xC, 0},
    {9, 0, 0, 0xD, 0},
    {0xA, 0, 1, 0xC, 0},
    {0xB, 0, 0, 0xE, 0},
    {0xC, 0x5A, 0, 0xF, 0},
    {0xD, 0, 0, 0x10, 0},
    {0xF, 0, 0, 0x11, 0},
    {0x10, 0, 0, 0x12, 0},
    {0x10, 0, 7, 0, 0},
    {0x10, 0, 4, 0, 0},
    {0x10, 0, 5, 0, 0},
    {0x10, 0x1E, 5, 3, 0},
    {0x10, 0x3C, 5, 6, 0},
    {0x11, 0, 0, 0x13, 0},
    {0x11, 0, 7, 0, 0},
    {0x11, 0, 5, 8, 0},
    {0x11, 0x1E, 5, 0xA, 0},
    {0x11, 0x3C, 5, 2, 0},
    {0x11, 0x5A, 5, 1, 0},
    {0x11, 0x78, 5, 5, 0},
    {0x12, 0, 3, 0x279, 0},
    {0x12, 0, 0, 0x14, 0},
    {0x12, 0, 5, 0xC, 0},
    {0x12, 0x1E, 5, 0xB, 0},
    {0x12, 0x3C, 3, 0x27A, 0},
    {0x12, 0x3C, 0, 0x15, 0},
    {0x12, 0x78, 3, 0x27B, 0},
    {0x12, 0x78, 0, 0x16, 0},
    {0x13, 0, 3, 0x27C, 0},
    {0x13, 0x64, 3, 0x27D, 0},
    {0x13, 0xDC, 1, 0xF, 0},
    {0x14, 0, 6, 0, 0},
    {0x14, 0, 4, 0, 0},
    {0x14, 0, 8, 0x17, 0},
    {0x14, 0, 1, 0xE, 0},
    {0x14, 0x1E, 3, 0x27E, 0},
    {0x14, 0x78, 0, 0x17, 0},
};

static RaceScriptEntry lbl_8048F5BC[51] = {
    {1, 0, 2, 0, 0},
    {4, 0, 8, 0x18, 0},
    {4, 0x78, 0, 0x18, 0},
    {6, 0, 0, 0x19, 0},
    {7, 0, 0, 0x1A, 0},
    {7, 0x3C, 0, 0x1B, 0},
    {7, 0x78, 0, 0x1C, 0},
    {7, 0xB4, 0, 0x1D, 0},
    {8, 0, 0, 0x1E, 0},
    {8, 0x1E, 0, 0x1F, 0},
    {8, 0x3C, 0, 0x20, 0},
    {8, 0x5A, 0, 0x21, 0},
    {8, 0x78, 0, 0x22, 0},
    {8, 0x96, 0, 0x23, 0},
    {8, 0xB4, 0, 0x24, 0},
    {9, 0, 0, 0x25, 0},
    {0xA, 0, 1, 0xC, 0},
    {0xB, 0, 0, 0x26, 0},
    {0xC, 0x5A, 0, 0x27, 0},
    {0xD, 0, 0, 0x28, 0},
    {0xF, 0, 0, 0x29, 0},
    {0x10, 0, 0, 0x2A, 0},
    {0x10, 0, 7, 0, 0},
    {0x10, 0, 4, 0, 0},
    {0x10, 0, 5, 0, 0},
    {0x10, 0x1E, 5, 3, 0},
    {0x10, 0x3C, 5, 6, 0},
    {0x11, 0, 0, 0x2B, 0},
    {0x11, 0, 7, 0, 0},
    {0x11, 0, 5, 8, 0},
    {0x11, 0x1E, 5, 0xA, 0},
    {0x11, 0x3C, 5, 2, 0},
    {0x11, 0x5A, 5, 1, 0},
    {0x11, 0x78, 5, 5, 0},
    {0x12, 0, 3, 0x279, 0},
    {0x12, 0, 0, 0x2C, 0},
    {0x12, 0, 5, 0xC, 0},
    {0x12, 0x1E, 5, 0xB, 0},
    {0x12, 0x3C, 3, 0x27A, 0},
    {0x12, 0x3C, 0, 0x2D, 0},
    {0x12, 0x78, 3, 0x27B, 0},
    {0x12, 0x78, 0, 0x2E, 0},
    {0x13, 0, 3, 0x27C, 0},
    {0x13, 0x64, 3, 0x27D, 0},
    {0x13, 0xDC, 1, 0xF, 0},
    {0x14, 0, 6, 0, 0},
    {0x14, 0, 4, 0, 0},
    {0x14, 0, 8, 0x2F, 0},
    {0x14, 0, 1, 0xE, 0},
    {0x14, 0x1E, 3, 0x27E, 0},
    {0x14, 0x78, 0, 0x2F, 0},
};

static RaceScriptEntry lbl_8048F9B8[46] = {
    {1, 0, 2, 0, 0},
    {4, 0, 8, 0x18, 0},
    {4, 0x78, 0, 0x18, 0},
    {6, 0, 0, 0x19, 0},
    {7, 0, 0, 0x1A, 0},
    {7, 0x3C, 0, 0x1B, 0},
    {7, 0x78, 0, 0x1C, 0},
    {7, 0xB4, 0, 0x1D, 0},
    {8, 0, 0, 0x1E, 0},
    {8, 0x1E, 0, 0x1F, 0},
    {8, 0x3C, 0, 0x20, 0},
    {8, 0x5A, 0, 0x21, 0},
    {8, 0x78, 0, 0x22, 0},
    {8, 0x96, 0, 0x23, 0},
    {8, 0xB4, 0, 0x24, 0},
    {9, 0, 0, 0x25, 0},
    {0xA, 0, 1, 0xC, 0},
    {0xB, 0, 0, 0x26, 0},
    {0xC, 0x5A, 0, 0x27, 0},
    {0xD, 0, 0, 0x28, 0},
    {0x10, 0, 4, 0, 0},
    {0x10, 0, 5, 0, 0},
    {0x10, 0x1E, 5, 3, 0},
    {0x10, 0x3C, 5, 6, 0},
    {0x11, 0, 5, 8, 0},
    {0x11, 0x1E, 5, 0xA, 0},
    {0x11, 0x3C, 5, 2, 0},
    {0x11, 0x5A, 5, 1, 0},
    {0x11, 0x78, 5, 5, 0},
    {0x12, 0, 3, 0x279, 0},
    {0x12, 0, 0, 0x2C, 0},
    {0x12, 0, 5, 0xC, 0},
    {0x12, 0x1E, 5, 0xB, 0},
    {0x12, 0x3C, 3, 0x27A, 0},
    {0x12, 0x3C, 0, 0x2D, 0},
    {0x12, 0x78, 3, 0x27B, 0},
    {0x12, 0x78, 0, 0x2E, 0},
    {0x13, 0, 3, 0x27C, 0},
    {0x13, 0x64, 3, 0x27D, 0},
    {0x13, 0xDC, 1, 0xF, 0},
    {0x14, 0, 6, 0, 0},
    {0x14, 0, 4, 0, 0},
    {0x14, 0, 8, 0x2F, 0},
    {0x14, 0, 1, 0xE, 0},
    {0x14, 0x1E, 3, 0x27E, 0},
    {0x14, 0x78, 0, 0x2F, 0},
};

const char *Scene_8014E0C4_data_8048FD50[15] = {
    lbl_80367438, lbl_806D8020, lbl_806D8028, lbl_806D8030, lbl_806D8038, lbl_806D8040, lbl_806D8048, lbl_806D8050, lbl_80367444, lbl_80367454, lbl_80367464, lbl_80367470, lbl_8036747C, lbl_806D8058, 0,
};

unsigned int sdata_806CF750_data_8048FD8C[3] = { (unsigned int)Scene_8014E0C4_data_806CF830, 0, 0 };

void *Scene_8014E0C4_data_8048FD98[6] = { (void *)Scene_8014E0C4_data_806CF838, 0, (void *)&fn_8014F2DC, (void *)&fn_8014F5A8, (void *)&fn_8014E804, (void *)&fn_8014E618 };
#pragma pop

/* ---- formerly SceneFactory_8014D540.cpp ---- */
#pragma use_lmw_stmw on

/* sdata symbols referenced from asm */
extern const int lbl_806D7F50[2];
/*
 * 0x8014D540..0x8014DD5C: scene factory and its object.
 */


#include "game/types/ListNode.h"
#include "game/types/ListIter.h"
#include "game/types/List.h"
extern "C" List *fn_8014E04C(List *self, short flag);

/* TOP-END */

extern "C" {
void *Alloc(unsigned long size);
int CreditMgr_GetCreditCount(int);
void CreditMgr_SetActiveSlot(int);
void *FUN_8003b120(int);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
unsigned char GetVBlankFlag(void);
void NamCam_End(void);
void NamCam_Init(void);
void SetLocalPcbRole(int);
void SetResourceLoadingFlag(int);
void SetSyncTarget(int);
unsigned char VBlankValue_Get(void);
void clRom_PurgeAll(void);
void fn_80121210(void);
void *fn_8014E0C4(int);
extern void fn_8014FC40();
extern void fn_801500F4();
extern void fn_80151F08();
void *fn_80163614(void *);
void fn_801933D0(int);
int isJapanese(void);
extern bool lbl_806D117C;
extern unsigned char lbl_806D12B0;
extern const float lbl_806D8064;
extern unsigned int lbl_8048FF80[];
void MemoryManager_TimedFree(void *p);
extern void dtor_8007D0D4();
void CoinSystem_Init(const void *tbl, int n);
extern void CourseObjectManager_Init();
extern void DrawManager_GetOrCreate();
extern void ItemObjectManager_Init();
void KartDriver_InitFull(void *k, int a, int id, void *mtx, int slot, int b, int c);
extern void KartDriver_New_Empty();
void PreloadEffectResources(int id);
extern void SoundChannels_ClearAll();
void SoundDriver_GetOrCreate(const void *tbl);
extern void __construct_array();
extern void clItemBoxResponder_Ctor();
extern void clNormal3D_Construct();
void clNormal3D_SetScale(void *o, int a, float x, float y, float z, float w);
extern void fn_80157B20();
extern void fn_80157D18();
extern void fn_80173DB4();
extern void fn_801F7D50();
extern unsigned int g_kartStartSlot;
extern const float lbl_806D8068;
extern unsigned int DemoKart_vtable_8048FF20[];
extern unsigned int DemoScene_vtable_8048FF3C[];
void *fn_8014D848(void);

#pragma section R ".extab_user"



#pragma section R ".extabindex_user"



}






struct clSceneInterface {
    clSceneInterface() : done(0) {}
    virtual ~clSceneInterface();
    virtual void _keyS();
    unsigned char done;
};

#include "game/types/LoaderBase.h"

struct NamCam {
    unsigned char active;
    unsigned char paused;
    void *buf;

    NamCam() : active(0), paused(0), buf(0) { buf = FUN_8003b120(0x4B000); }
    void Stop() {
        if (GetVBlankFlag() && active) {
            active = 0;
            NamCam_End();
        }
    }
    void Start() {
        if (GetVBlankFlag()) {
            if (active == 1) {
                Stop();
            }
            active = 1;
            paused = 0;
            NamCam_Init();
        }
    }
};

struct AttractScene : LoaderBase {
    virtual void _key();
    int state;
    float f08;
    float f0C;
    NamCam *cam;
    float f14;
    int japanese;
    unsigned char noCam;

    AttractScene() {
        state = 0;
        f08 = 0.0f;
        f0C = 0.0f;
        f14 = 0.0f;
        japanese = isJapanese();
        noCam = 0;
        cam = 0;
        if (VBlankValue_Get()) {
            noCam = 1;
        }
        if (noCam == 0) {
            cam = new NamCam;
            cam->Start();
        }
    }
};

struct TitleScene {
    TitleScene(int a, void *arg);
    char pad[0x580];
};

struct SelectScene {
    SelectScene(void *arg, int b);
    char pad[0x1C];
};

struct RankingScene {
    RankingScene();
    char pad[0x2C];
};

struct SceneFactory : clSceneInterface {
    virtual void _key();
    void *scene;
    int f0C;
    int f10;
    int f14;
    unsigned char f18;
    int f1C;
    int f20;
    int f24;
    float f28;
    int f2C;
    int credits;
    unsigned char f34;
    int f38;

    SceneFactory(int mode, void *arg);
};

SceneFactory::SceneFactory(int mode, void *arg)
{
    Scene_8014E0C4_bss_806D1580 = (StatusInfo *)this;
    f14 = 0;
    scene = 0;
    f0C = 0;
    f10 = 0;
    f18 = 1;
    f28 = 0.0f;
    f2C = 0;
    credits = CreditMgr_GetCreditCount(0);
    f34 = 0;
    f38 = 0;
    f1C = 0;
    f20 = 0;
    fn_80121210();
    clRom_PurgeAll();
    if (SINGLETON_INSTANCE(g_pInputState) != 0) {
        delete g_pInputState;
        g_pInputState = 0;
    }
    SetSyncTarget(4);
    SetLocalPcbRole(0);
    lbl_806D12B0 = 0;
    SetResourceLoadingFlag(0);
    lbl_806D117C = CreditMgr_GetCreditCount(0) <= 0;
    CreditMgr_SetActiveSlot(0);
    fn_801933D0(1);
    switch (mode) {
    case 0:
        scene = fn_8014E0C4(1);
        break;
    case 1:
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        scene = new TitleScene(1, arg);
        break;
    case 2:
        scene = new SelectScene(arg, 2);
        break;
    case 3:
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        scene = new AttractScene;
        break;
    case 4:
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        scene = new RankingScene;
        break;
    case 5:
        scene = fn_80163614(arg);
        break;
    case 6:
        scene = fn_8014D848();
        break;
    }
}

class SceneBase {
public:
    virtual void _keySceneBase();

    virtual ~SceneBase();
};

class KartDrv {
public:
    char data[0x384];
    KartDrv();
};

class TornadoFx {
public:
    char data[0x154];
    TornadoFx(int a, void *kart, int id, int b, float x, float y, float z);
};

struct SprNodeBase {
    SprNodeBase *prev;
    SprNodeBase *next;
};

struct SprNode : SprNodeBase {
    unsigned int key;
    int ref;
    void *res;
};

struct SprList {
    unsigned int count;
    SprNodeBase end;
};

struct SprIter {
    SprNodeBase *n;
};
struct SprScene {
    char pad0[0xC];
    SprList cache;
    SprList layers[2];
    void Draw(unsigned int layer, unsigned int id, unsigned int flags, float x, float y, float sx, float sy, float rot, float r, float g, float b, float a);
};



struct SprCacheVal {
    unsigned int key;
    int ref;
    void *res;
};

class SprRes {
public:
    void *p;
    SprRes(char *name);
};

static inline void SprCache_Insert(SprList *l, SprCacheVal *v) {
    SprIter ret;
    SprIter pos;
    pos.n = &l->end;
    fn_80157C60(&ret, l, &pos, v);
}

static inline void *SprCache_Get(SprList *cache, unsigned int key) {
    SprNodeBase *n;
    if (key >= 12) {
        return 0;
    }
    if (cache->count != 0) {
        for (n = cache->end.next; n != &cache->end; n = n->next) {
            if (((SprNode *)n)->key == key) {
                ((SprNode *)n)->ref++;
                return ((SprNode *)n)->res;
            }
        }
    }
    {
        SprCacheVal v;
        v.key = key;
        v.ref = 1;
        v.res = new SprRes((char *)Scene_8014E0C4_data_8048F178[key]);
        SprCache_Insert(cache, &v);
        return v.res;
    }
}


struct SceneCacheNormal {
    unsigned char opaque[0x5c];
    SceneCacheNormal(const char *path, int flags);
};

class ItemBoxResponder {
public:
    ItemBoxResponder(float *pos);
    virtual ~ItemBoxResponder();
    char pad4[8];
};

class DemoKart : public ItemBoxResponder {
public:
    virtual void _keyDemoKart();
    KartDrv *kart;
    TornadoFx *fx;
    float mtx[3][4];
    float pos[3];

    DemoKart(int id, int slot) : ItemBoxResponder(pos) {
        PSMTXIdentity(mtx);
        pos[0] = lbl_806D8064;
        pos[1] = lbl_806D8064;
        pos[2] = lbl_806D8064;
        kart = new KartDrv;
        KartDriver_InitFull(kart, 0, id, mtx, slot, 0, 0);
        fx = new TornadoFx(0, kart, id, 1, lbl_806D8064, lbl_806D8064, lbl_806D8064);
    }
};

class DemoCam {
public:
    char data[0x30];
    DemoCam(void *kart);
};

class SceneListA {
public:
    char data[0xC];
    SceneListA();
    ~SceneListA();
};

class SprListC : public SprList {
public:
    SprListC();
    ~SprListC();
};

class LayerList {
public:
    char data[0xC];
    LayerList();
    ~LayerList();
};

class SprSceneC {
public:
    SceneListA scenes;
    SprListC cache;
    LayerList layers[2];

    void Preload(unsigned int i) {
        if (i < 80) {
            SprCache_Get(&cache, Scene_8014E0C4_rodata_803644D0[i].key);
        }
    }
};

class DemoScene : public SceneBase {
public:
    virtual void _keyDemoScene();
    int state;
    float f08;
    float f0C;
    int japanese;
    SceneCacheNormal *map;
    int f18;
    int f1C;
    int f20;
    unsigned char f24;
    int f28;
    float f2C;
    float f30;
    DemoKart *karts[2];
    int f3C[2];
    unsigned char f44[2];
    DemoCam *cam;
    SprSceneC *spr;

    DemoScene();
};

#ifdef NON_MATCHING
#pragma push
#pragma auto_inline off
#endif /* NON_MATCHING */
extern "C" void *fn_8014D848(void)
{
    Frame_PostDrawOverlay();
    Frame_UpdatePerFrameState();
    return new DemoScene;
}
#ifdef NON_MATCHING
#pragma pop
#endif /* NON_MATCHING */

DemoScene::DemoScene()
{
    int i;

    DrawManager_GetOrCreate();
    f24 = 1;
    state = 0;
    f08 = lbl_806D8064;
    f0C = lbl_806D8064;
    japanese = isJapanese();
    f28 = 0;
    f2C = lbl_806D8064;
    f30 = lbl_806D8064;
    map = new SceneCacheNormal(lbl_80367540, 0);
    f18 = 0;
    f1C = 0;
    f20 = 0;
    SoundDriver_GetOrCreate(lbl_80366D40);
    CoinSystem_Init(lbl_80366D40, 2);
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    g_kartStartSlot = -1;
    for (i = 0; i < 2; i++) {
        karts[i] = new DemoKart(lbl_806D7F50[i], i);
        TornadoEffect_SetColorPairC8CC(karts[i]->fx, 0x20, 0x20);
        TireEffect_ResetSpin(karts[i]->fx, lbl_806D8064, lbl_806D8068);
        f44[i] = 0;
        f3C[i] = 0;
    }
    cam = new DemoCam(karts[0]->kart);
    spr = new SprSceneC;
    SetResourceLoadingFlag(1);
    fn_8014E028(spr, 10);
    fn_8014E028(spr, 11);
    fn_8014E028(spr, 12);
    fn_8014E004(spr, 10);
    fn_8014E004(spr, 11);
    fn_8014E004(spr, 12);
    {
        void *o;
        if ((o = fn_8014DD5C(spr, 10)) != 0) {
            clNormal3D_SetScale(o, 0, lbl_806D8064, lbl_806D8068, lbl_806D8064, lbl_806D8064);
        }
        if ((o = fn_8014DD5C(spr, 11)) != 0) {
            clNormal3D_SetScale(o, 0, lbl_806D8064, lbl_806D8068, lbl_806D8064, lbl_806D8064);
        }
        if ((o = fn_8014DD5C(spr, 12)) != 0) {
            clNormal3D_SetScale(o, 0, lbl_806D8064, lbl_806D8068, lbl_806D8064, lbl_806D8064);
        }
    }
    PreloadEffectResources(2);
    PreloadEffectResources(9);
    if (japanese == 1) {
        for (i = 0x3E; i <= 0x4C; i++) {
            spr->Preload(i);
        }
    } else {
        for (i = 0x14; i <= 0x22; i++) {
            spr->Preload(i);
        }
    }
}


struct SceneCacheList;
extern "C" void *fn_8014DD80(SceneCacheList *list, unsigned int id, unsigned int type);

/* ---- formerly fn_8014DD5C.c ---- */
#pragma push
#pragma auto_inline off
extern "C" void *fn_8014DD5C(void *p0, int p1) {
    return fn_8014DD80((SceneCacheList *)p0, p1, 0);
}

/* ---- formerly fn_8014DD80.cpp ---- */
/*
 * 0x8014DD80..0x8014E004: scene cache lookup / create.
 *
 * Returns the cached scene object for (id, type), bumping its reference
 * count, or creates it (normal model, 3D scene, animated-camera 3D scene or
 * scene model, named by the id's archive path) and appends it to the cache.
 */

void *operator new(size_t);
void operator delete(void *);



struct SceneCacheAnimLeaf { void *value; };
struct SceneCacheAnimNode { void *opaque; SceneCacheAnimLeaf *next; };
struct SceneCacheDescriptor { void *opaque; SceneCacheAnimNode *next; };

static inline void *leaf_value(SceneCacheAnimLeaf *leaf)
{
    if (leaf == 0) return 0;
    return leaf->value;
}

static inline void *node_value(SceneCacheAnimNode *node)
{
    if (node == 0) return 0;
    return leaf_value(node->next);
}

static inline void *descriptor_value(SceneCacheDescriptor *descriptor)
{
    if (descriptor == 0) return 0;
    return node_value(descriptor->next);
}

extern "C" {
void HSD_CObjAddAnim(void *cobj, void *anim);
void HSD_CObjReqAnim(void *cobj, float frame);
void HSD_CObjAnim(void *cobj);
}

struct SceneCacheSceneRoot { virtual void identity(); };

struct SceneCacheScene : SceneCacheSceneRoot {
    void *camera;                       /* 0x0004 */
    unsigned char opaque8[0x24];
    SceneCacheDescriptor *descriptor;   /* 0x002C */
    unsigned char opaque30[0x3054];
    SceneCacheScene(const char *path);
    virtual void identity();
};

struct SceneCacheAnimScene : SceneCacheScene {
    unsigned char active, opaque3085[3]; /* 0x3084 */
    float speed;                         /* 0x3088 */
    float frame;                         /* 0x308C */
    SceneCacheAnimScene(const char *path) : SceneCacheScene(path) {
        speed = -1.0f;
        frame = 0.0f;
    }
    virtual void identity();
    void start() {
        if (camera) {
            active = 1;
            frame = 0.0f;
            speed = 1.0f;
            HSD_CObjAddAnim(camera, descriptor_value(descriptor));
            HSD_CObjReqAnim(camera, frame);
            HSD_CObjAnim(camera);
        }
    }
};

struct SceneCacheModel {
    unsigned char opaque[0x28];
    SceneCacheModel(const char *path, int flags);
};

struct SceneCacheEntry {
    unsigned int key;  /* id | type << 29 */
    int refCount;
    void *obj;
};

struct SceneCacheLink {
    SceneCacheLink *prev;
    SceneCacheLink *next;
};

struct SceneCacheNode : SceneCacheLink {
    SceneCacheEntry entry;
};

struct SceneCacheIter {
    SceneCacheIter(SceneCacheLink *n) : node(n) {}
    SceneCacheLink *node;
};

struct SceneCacheList {
    unsigned int count;
    SceneCacheLink anchor;
    SceneCacheIter end() { return SceneCacheIter(&anchor); }
    SceneCacheIter insert(const SceneCacheIter &pos, const SceneCacheEntry &entry);
};

extern "C" void *fn_8014DD80(SceneCacheList *list, unsigned int id, unsigned int type)
{
    SceneCacheEntry entry;
    SceneCacheLink *node;
    unsigned int key;

    if (id >= 29 || type >= 4) {
        return 0;
    }

    key = id | (type << 29);
    if (list->count != 0) {
        for (node = list->anchor.next; node != &list->anchor; node = node->next) {
            if (((SceneCacheNode *)node)->entry.key == key) {
                ((SceneCacheNode *)node)->entry.refCount++;
                return ((SceneCacheNode *)node)->entry.obj;
            }
        }
    }

    entry.key = key;
    entry.refCount = 1;
    switch (type) {
    case 0:
        entry.obj = new SceneCacheNormal(((const char *const *)&Scene_8014E0C4_rodata_80364368)[id], 0);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    case 1:
        entry.obj = new SceneCacheScene(((const char *const *)&Scene_8014E0C4_rodata_80364368)[id]);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    case 2: {
        SceneCacheAnimScene *scene = new SceneCacheAnimScene(((const char *const *)&Scene_8014E0C4_rodata_80364368)[id]);
        entry.obj = scene;
        if (scene == 0) {
            return 0;
        }
        scene->start();
        break;
    }
    case 3:
        entry.obj = new SceneCacheModel(((const char *const *)&Scene_8014E0C4_rodata_80364368)[id], 1);
        if (entry.obj == 0) {
            return 0;
        }
        break;
    default:
        return 0;
    }

    /* list->end() inline here would defer this function past fn_8014E028 */
    SceneCacheIter pos(&list->anchor);
    list->insert(pos, entry);
    return entry.obj;
}

/* ---- formerly fn_8014E004.c / fn_8014E028.c ---- */
extern "C" void *fn_8014E004(void *p0, int p1) {
    return fn_8014DD80((SceneCacheList *)p0, p1, 3);
}

extern "C" void *fn_8014E028(void *p0, int p1) {
    return fn_8014DD80((SceneCacheList *)p0, p1, 2);
}
#pragma pop

/* ---- formerly fn_8014E04C.cpp ---- */
/*
 * 0x8014E04C..0x8014E0C4: list holder dtor.
 */


/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
List *fn_8014E04C(List *self, short flag);

#pragma section R ".extab_user"

#pragma section R ".extabindex_user"

}





extern "C" List *fn_8014E04C(List *self, short flag)
{
    if (self) {
        if (self) {
            if (self) {
                ListIter e, f, r;
                e.n = &self->head;
                f.n = self->head.next;
                ((void (*)(ListIter *, List *, ListIter *, ListIter *))fn_80157D30)(&r, self, &f, &e);
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}


#pragma use_lmw_stmw reset
/* ---- Scene_8014E0C4 ---- */

class Halation {
public:
    char data[0x7C];
    Halation(const char *name, void *joint, float a, float b);
};

class DemoLight {
public:
    char pad0[8];
    float f08;
    int f0C;
    float f10;
    float f14;
    float f18;
    char pad1C[8];
    DemoLight();
};

class CreamModel {
public:
    char data[0x20];
    CreamModel(const char *name, int a);
};

struct CreamPos {
    float x;
    float y;
};

class DemoCream {
public:
    CreamModel *model;
    CreamModel *plate;
    unsigned char f08;
    int f0C;
    float f10;
    unsigned char on[5];
    CreamPos pos[5];
    CreamPos vel[5];
    float t[5];
    unsigned char f80;
    float f84;
    float f88;
    char pad8C[8];
    float f94;

    DemoCream() {
        int i;
        model = new CreamModel(lbl_80367590, 0);
        plate = new CreamModel(lbl_8036759C, 0);
        f08 = 0;
        f0C = 0;
        f10 = lbl_806D8064;
        for (i = 0; i < 5; i++) {
            on[i] = 1;
            pos[i].x = ((const CreamPos *)lbl_80366E4C)[i].x;
            pos[i].y = ((const CreamPos *)lbl_80366E4C)[i].y;
            t[i] = lbl_806D8064;
        }
        f80 = 1;
        f84 = lbl_806D7F68[0];
        f88 = lbl_806D7F68[1];
        f94 = lbl_806D8064;
    }
};

class BdText {
public:
    char pad0[0x18];
    int f18;
    char pad1C[0x230 - 0x1C];
    BdText();
    ~BdText();
};

class DemoScene1C0 : public SceneBase {
public:
    virtual void _keyDemoScene1C0();
    int mode;
    int f08;
    float f0C;
    float f10;
    SceneCacheNormal *model;
    int f18;
    int f1C;
    int f20;
    const DemoScriptEntry *script;
    unsigned char f28;
    unsigned char f29;
    int f2C;
    float f30;
    KartDrv *karts[6];
    TornadoFx *fx[6];
    float mtx[6][3][4];
    int f184[6];
    unsigned char f19C[6];
    int f1A4;
    Halation *halation;
    DemoLight *light;
    unsigned char f1B0;
    DemoCream *cream;
    SprSceneC *spr;
    BdText *text;

    DemoScene1C0(int a);
};

#ifdef NON_MATCHING
#pragma push
#pragma auto_inline off
#endif /* NON_MATCHING */
extern "C" void *fn_8014E0C4(int a) {
    Frame_PostDrawOverlay();
    Frame_UpdatePerFrameState();
    return new DemoScene1C0(a);
}
#ifdef NON_MATCHING
#pragma pop
#endif /* NON_MATCHING */

#pragma push
#pragma use_lmw_stmw on
DemoScene1C0::DemoScene1C0(int a)
{
    unsigned int j;
    int i;
    char *font;

    fn_80121210();
    DrawManager_GetOrCreate();
    mode = fn_80169E20();
    f08 = 0;
    f0C = lbl_806D8070;
    f10 = lbl_806D8064;
    f28 = 0;
    f29 = 0;
    f2C = 0;
    f30 = lbl_806D8064;
    f18 = 0;
    f1C = 0;
    f20 = 0;
    script = 0;
    model = 0;
    halation = 0;
    light = 0;
    cream = 0;
    if ((unsigned char)a == 0) {
        f28 = 1;
    }
    if (isJapanese() == 1) {
        if (fn_80169E10() == 1) {
            script = lbl_80366A64;
        } else {
            script = lbl_80366BD8;
        }
    } else {
        if (fn_80169E10() == 1) {
            script = lbl_80366848;
        } else {
            script = lbl_8036698C;
        }
    }
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    g_kartStartSlot = -1;
    for (i = 0; i < 6; i++) {
        PSMTXIdentity(mtx[i]);
        karts[i] = new KartDrv;
        KartDriver_Init(karts[i], 0, lbl_80364B10[i], mtx[i], i, 0, 0);
        fx[i] = new TornadoFx(0, karts[i], lbl_80364B10[i], 1, lbl_806D8064, lbl_806D8064, lbl_806D8064);
        f184[i] = 0;
        TornadoEffect_SetFlagC0(fx[i]);
        f19C[i] = 1;
    }
    f1A4 = 1;
    model = new SceneCacheNormal(lbl_80367550, 0);
    halation = new Halation(lbl_80367568, ResolveJointByName(model, (char *)lbl_80367578), 1.0f, 1.0f);
    Object_ReleaseAnimResource(model);
    f1B0 = 0;
    light = new DemoLight;
    light->f0C = 3;
    light->f08 = lbl_806D8074;
    light->f10 = lbl_806D8078;
    light->f14 = lbl_806D807C;
    light->f18 = lbl_806D8080;
    cream = new DemoCream;
    text = new BdText[2];
    text[0].f18 = 0;
    text[1].f18 = 0;
    font = fn_80293BBC();
    TexMgr_SetTexture(&text[0], lbl_803675B4, font + 0x18);
    TexMgr_SetTexture(&text[1], lbl_803675C4, font + 0x2C);
    spr = new SprSceneC;
    SetResourceLoadingFlag(1);
    for (j = 0; j < 10; j++) {
        void *o;
        fn_8014E028(spr, lbl_80366E88[j].id);
        fn_8014E004(spr, lbl_80366E88[j].id);
        if ((o = fn_8014DD5C(spr, lbl_80366E88[j].id)) != 0) {
            clNormal3D_SetScale(o, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        }
    }
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadItemResources(0x32);
    PreloadItemResources(0x39);
    PreloadItemResources(8);
}
#pragma pop

extern "C" void fn_8014E618(AttractPanel *self) {
    if (!self->done) {
        if (self->obj != 0) {
            self->obj->v14();
        }
        ServiceMode_UpdateScheduleGate();
        if (fn_80169E10() && IsCardValid() == 1) {
            if (!ServiceEnable_Get() || ServiceValue_Get()) {
                fn_80169334(0, 0x1553, 0, 8.0f, 8.0f, 1.0f, 1.0f, 1.0f);
            } else if (Sci2Card_GetReceiptTestFlag()) {
                fn_80169334(0, 0x1554, 0, 8.0f, 8.0f, 1.0f, 1.0f, 1.0f);
            } else {
                fn_80169334(0, 0x1554, 0, 8.0f, 8.0f, 1.0f, 1.0f, 0.0f);
            }
        }
        fn_8011F994(0);
        if (Scene_8014E0C4_rodata_80367488[self->idx].on) {
            float s = LUT_Sin12Bit(Saturate_Double(1.5f * self->t, 0.0f, 180.0f));
            int n = PcbSync_CountJoinedPcbsAdvancedKarts();
            CreditMgr_DrawCoinCreditBanner(0, 0xFFFFFF00 | ((unsigned int)(255.0f * s) & 0xFF), n);
            if ((self->t += 1.0f) >= 120.0f) {
                self->t = 0.0f;
                self->blink = (self->blink + 1) & 1;
            }
        } else {
            self->t = 0.0f;
            self->blink = 0;
        }
        fn_8011F994(6);
        HSD_StateInvalidate(-1);
    }
}

#ifndef NON_MATCHING
extern "C" asm void fn_8014E804(void) { /* 0x8014E804 size:0x960 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lis r3, Scene_8014E0C4_rodata_80363D30@ha
    stw r30, 0x18(r1)
    addi r30, r3, Scene_8014E0C4_rodata_80363D30@l
    li r3, 0x0
    stw r29, 0x14(r1)
    lwz r29, 0x30(r31)
    bl CreditMgr_GetCreditCount
    stw r3, 0x30(r31)
    lwz r0, 0x30(r31)
    cmpw r0, r29
    beq fn_8014E804_L_8014E8BC
    li r0, 0x1
    addi r3, r30, 0x3758
    stb r0, 0x34(r31)
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    lwzx r0, r3, r0
    cmplwi r0, 0x6
    beq fn_8014E804_L_8014E8BC
    li r29, 0x0
    fn_8014E804_L_8014E868:
    lwz r0, 0x0(r3)
    cmplwi r0, 0xf
    bge fn_8014E804_L_8014E8BC
    cmplwi r0, 0x6
    bne fn_8014E804_L_8014E8B0
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    beq fn_8014E804_L_8014E8A8
    bl GXDrawDone
    lwz r3, 0x8(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x0
    stw r0, 0x8(r31)
    fn_8014E804_L_8014E8A8:
    stw r29, 0xc(r31)
    b fn_8014E804_L_8014E8BC
    fn_8014E804_L_8014E8B0:
    addi r3, r3, 0xc
    addi r29, r29, 0x1
    b fn_8014E804_L_8014E868
    fn_8014E804_L_8014E8BC:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014E9B8
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_8014E804_L_8014E9B8
    bl GXDrawDone
    lwz r3, 0x8(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x0
    stw r0, 0x8(r31)
    bl StrPcb_GetInstance
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014E920
    bl StrPcb_GetInstance
    li r4, 0x1
    bl StrPcb_ResetCommands_Zero
    bl StrPcb_GetInstance
    bl StrPcb_ResetCommands_NeutralDefault
    fn_8014E804_L_8014E920:
    addi r29, r30, 0x3758
    fn_8014E804_L_8014E924:
    lwz r3, 0xc(r31)
    addi r0, r3, 0x1
    stw r0, 0xc(r31)
    lwz r3, 0xc(r31)
    mulli r0, r3, 0xc
    lwzx r0, r29, r0
    cmplwi r0, 0xd
    bne fn_8014E804_L_8014E960
    lbz r0, lbl_806D12E1(r13)
    cmplwi r0, 0x1
    bne fn_8014E804_L_8014E958
    addi r0, r3, 0x1
    stw r0, 0xc(r31)
    fn_8014E804_L_8014E958:
    li r0, 0x1
    stb r0, lbl_806D12E1(r13)
    fn_8014E804_L_8014E960:
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    lwzx r0, r29, r0
    cmplwi r0, 0xf
    blt fn_8014E804_L_8014E9A4
    li r0, 0x1
    li r3, 0x0
    stw r0, 0xc(r31)
    stb r3, 0x18(r31)
    lwz r0, lbl_806D10A0(r13)
    cmplwi r0, 0x0
    bne fn_8014E804_L_8014E994
    b fn_8014E804_L_8014E998
    fn_8014E804_L_8014E994:
    mr r3, r0
    fn_8014E804_L_8014E998:
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014E9A4
    bl TitleTracker_OnAttract_Stub
    fn_8014E804_L_8014E9A4:
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    lwzx r0, r29, r0
    cmplwi r0, 0x6
    beq fn_8014E804_L_8014E924
    fn_8014E804_L_8014E9B8:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_8014E804_L_8014F114
    lwz r0, 0xc(r31)
    addi r4, r30, 0x3758
    mulli r0, r0, 0xc
    lwzx r0, r4, r0
    stw r0, 0x10(r31)
    lwz r0, 0x10(r31)
    cmplwi r0, 0xe
    bgt fn_8014E804_L_8014F114
    lis r3, jumptable_8048FDCC@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8048FDCC@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r3, 0x14(r31)
    addi r0, r3, 0x1
    stw r0, 0x14(r31)
    bl ServiceMode_UpdateScheduleGate
    bl OperationClock_Commit
    bl RaceFlow_ResetState_FullColdInit
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x80
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EAC0
    lis r4, lbl_8048FF80@ha
    lis r3, StatusLogoScene_vtable_8048FE8C@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r29)
    addi r0, r3, StatusLogoScene_vtable_8048FE8C@l
    addi r3, r29, 0x34
    stw r0, 0x0(r29)
    bl fn_801F6804
    li r0, 0x0
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r29)
    stfs f0, 0x8(r29)
    stw r0, 0x10(r29)
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8014E804_L_8014EA7C
    addi r3, r29, 0x10
    addi r4, r30, 0x38a4
    bl TEXLoadPalette_Retry
    b fn_8014E804_L_8014EA88
    fn_8014E804_L_8014EA7C:
    addi r3, r29, 0x10
    addi r4, r30, 0x38bc
    bl TEXLoadPalette_Retry
    fn_8014E804_L_8014EA88:
    lwz r3, 0x10(r29)
    addi r4, r29, 0x14
    li r5, 0x0
    bl TEXBindPaletteEntry_RGB
    lwz r0, g_currentSceneState(r13)
    cmpwi r0, 0x5
    beq fn_8014E804_L_8014EAAC
    li r3, 0x4
    bl SetSyncTarget
    fn_8014E804_L_8014EAAC:
    li r3, 0xff
    li r4, 0xff
    li r5, 0xff
    li r6, 0xff
    bl fn_8002CFB8
    fn_8014E804_L_8014EAC0:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x80
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EB4C
    lis r4, lbl_8048FF80@ha
    lis r3, StatusNoticeScene_vtable_8048FE64@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r29)
    addi r0, r3, StatusNoticeScene_vtable_8048FE64@l
    addi r3, r29, 0x34
    stw r0, 0x0(r29)
    bl fn_801F6804
    li r0, 0x0
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r29)
    stfs f0, 0x8(r29)
    stw r0, 0x10(r29)
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8014E804_L_8014EB30
    addi r3, r29, 0x10
    addi r4, r30, 0x38d4
    bl TEXLoadPalette_Retry
    b fn_8014E804_L_8014EB3C
    fn_8014E804_L_8014EB30:
    addi r3, r29, 0x10
    addi r4, r30, 0x38e8
    bl TEXLoadPalette_Retry
    fn_8014E804_L_8014EB3C:
    lwz r3, 0x10(r29)
    addi r4, r29, 0x14
    li r5, 0x0
    bl TEXBindPaletteEntry_RGB
    fn_8014E804_L_8014EB4C:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    lbz r0, 0x18(r31)
    cmplwi r0, 0x0
    beq fn_8014E804_L_8014EB70
    li r3, 0x0
    bl fn_8014E0C4
    stw r3, 0x8(r31)
    b fn_8014E804_L_8014F114
    fn_8014E804_L_8014EB70:
    li r3, 0x1
    bl fn_8014E0C4
    stw r3, 0x8(r31)
    b fn_8014E804_L_8014F114
    bl fn_8014D848
    stw r3, 0x8(r31)
    b fn_8014E804_L_8014F114
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    add r3, r4, r0
    lwz r0, 0x4(r3)
    cmplwi r0, 0x1
    bne fn_8014E804_L_8014EBD0
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x0
    beq fn_8014E804_L_8014EBD0
    cmpwi r0, 0x3
    beq fn_8014E804_L_8014EBD0
    ble fn_8014E804_L_8014EBC8
    li r0, 0x0
    stw r0, 0x1c(r31)
    b fn_8014E804_L_8014EBD0
    fn_8014E804_L_8014EBC8:
    li r0, 0x3
    stw r0, 0x1c(r31)
    fn_8014E804_L_8014EBD0:
    lwz r3, 0x1c(r31)
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    addi r3, r3, 0x1
    bl SetCourseParams
    li r3, 0x18
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EC34
    lis r4, lbl_8048FF80@ha
    lis r3, CourseDemoScene_vtable_8048FE3C@ha
    addi r0, r4, lbl_8048FF80@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r29)
    addi r3, r3, CourseDemoScene_vtable_8048FE3C@l
    li r0, 0x0
    stw r3, 0x0(r29)
    stw r0, 0x4(r29)
    stfs f0, 0x8(r29)
    stb r0, 0x10(r29)
    stfs f0, 0xc(r29)
    lwz r0, g_cupId(r13)
    stw r0, 0x14(r29)
    bl DrawManager_GetOrCreate
    fn_8014E804_L_8014EC34:
    stw r29, 0x8(r31)
    lwz r3, 0x1c(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0x6
    stw r0, 0x1c(r31)
    blt fn_8014E804_L_8014F114
    li r0, 0x0
    stw r0, 0x1c(r31)
    b fn_8014E804_L_8014F114
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    add r3, r4, r0
    lwz r29, 0x4(r3)
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x28
    bl Alloc
    mr. r30, r3
    beq fn_8014E804_L_8014ED58
    lis r4, lbl_8048FF80@ha
    lis r3, EntryScene_vtable_8048FE14@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r30)
    addi r0, r3, EntryScene_vtable_8048FE14@l
    stw r0, 0x0(r30)
    bl fn_80169E20
    stw r3, 0x4(r30)
    li r4, 0x0
    lfs f0, lbl_806D8064(r2)
    li r0, 0x1
    stw r4, 0x8(r30)
    li r3, 0x0
    stfs f0, 0xc(r30)
    stb r0, 0x10(r30)
    stw r4, 0x14(r30)
    stw r29, 0x18(r30)
    stb r4, 0x1c(r30)
    bl CreditMgr_GetCreditCount
    stw r3, 0x20(r30)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bne fn_8014E804_L_8014ED04
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014ECFC
    li r4, 0x138
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014E804_L_8014ECFC:
    stw r29, 0x24(r30)
    b fn_8014E804_L_8014ED28
    fn_8014E804_L_8014ED04:
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014ED24
    li r4, 0x107
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014E804_L_8014ED24:
    stw r29, 0x24(r30)
    fn_8014E804_L_8014ED28:
    lwz r3, 0x24(r30)
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014ED44
    li r0, 0x1
    stw r0, 0x4(r3)
    lwz r3, 0x24(r30)
    bl fn_8019FEF4
    fn_8014E804_L_8014ED44:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_8014E804_L_8014ED58:
    stw r30, 0x8(r31)
    mr r3, r31
    lwz r12, 0x0(r31)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    b fn_8014E804_L_8014F114
    lwz r0, 0xc(r31)
    mulli r0, r0, 0xc
    add r3, r4, r0
    lwz r29, 0x4(r3)
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x28
    bl Alloc
    mr. r30, r3
    beq fn_8014E804_L_8014EE70
    lis r4, lbl_8048FF80@ha
    lis r3, EntryScene_vtable_8048FE14@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r30)
    addi r0, r3, EntryScene_vtable_8048FE14@l
    stw r0, 0x0(r30)
    bl fn_80169E20
    stw r3, 0x4(r30)
    li r0, 0x0
    lfs f0, lbl_806D8064(r2)
    li r3, 0x0
    stw r0, 0x8(r30)
    stfs f0, 0xc(r30)
    stb r0, 0x10(r30)
    stw r0, 0x14(r30)
    stw r29, 0x18(r30)
    stb r0, 0x1c(r30)
    bl CreditMgr_GetCreditCount
    stw r3, 0x20(r30)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bne fn_8014E804_L_8014EE1C
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EE14
    li r4, 0x138
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014E804_L_8014EE14:
    stw r29, 0x24(r30)
    b fn_8014E804_L_8014EE40
    fn_8014E804_L_8014EE1C:
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EE3C
    li r4, 0x107
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014E804_L_8014EE3C:
    stw r29, 0x24(r30)
    fn_8014E804_L_8014EE40:
    lwz r3, 0x24(r30)
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014EE5C
    li r0, 0x1
    stw r0, 0x4(r3)
    lwz r3, 0x24(r30)
    bl fn_8019FEF4
    fn_8014E804_L_8014EE5C:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_8014E804_L_8014EE70:
    stw r30, 0x8(r31)
    b fn_8014E804_L_8014F114
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x20
    bl Alloc
    mr. r30, r3
    beq fn_8014E804_L_8014EF7C
    lis r4, lbl_8048FF80@ha
    lis r3, AttractScene_vtable_8048FF64@ha
    addi r0, r4, lbl_8048FF80@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r30)
    addi r3, r3, AttractScene_vtable_8048FF64@l
    li r0, 0x0
    stw r3, 0x0(r30)
    stw r0, 0x4(r30)
    stfs f0, 0x8(r30)
    stfs f0, 0xc(r30)
    stfs f0, 0x14(r30)
    bl isJapanese
    stw r3, 0x18(r30)
    li r0, 0x0
    stb r0, 0x1c(r30)
    stw r0, 0x10(r30)
    bl VBlankValue_Get
    clrlwi. r0, r3, 24
    beq fn_8014E804_L_8014EEE8
    li r0, 0x1
    stb r0, 0x1c(r30)
    fn_8014E804_L_8014EEE8:
    lbz r0, 0x1c(r30)
    cmplwi r0, 0x0
    bne fn_8014E804_L_8014EF7C
    li r3, 0x8
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EF24
    li r0, 0x0
    lis r3, 0x5
    stb r0, 0x0(r29)
    subi r3, r3, 0x5000
    stb r0, 0x1(r29)
    stw r0, 0x4(r29)
    bl FUN_8003b120
    stw r3, 0x4(r29)
    fn_8014E804_L_8014EF24:
    stw r29, 0x10(r30)
    lwz r29, 0x10(r30)
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014E804_L_8014EF7C
    lbz r0, 0x0(r29)
    cmplwi r0, 0x1
    bne fn_8014E804_L_8014EF68
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014E804_L_8014EF68
    lbz r0, 0x0(r29)
    cmplwi r0, 0x0
    beq fn_8014E804_L_8014EF68
    li r0, 0x0
    stb r0, 0x0(r29)
    bl NamCam_End
    fn_8014E804_L_8014EF68:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x0(r29)
    stb r0, 0x1(r29)
    bl NamCam_Init
    fn_8014E804_L_8014EF7C:
    stw r30, 0x8(r31)
    b fn_8014E804_L_8014F114
    lwz r3, 0x20(r31)
    bl fn_80163614
    stw r3, 0x8(r31)
    lwz r3, 0x20(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0x4
    stw r0, 0x20(r31)
    blt fn_8014E804_L_8014F114
    li r0, 0x0
    stw r0, 0x20(r31)
    b fn_8014E804_L_8014F114
    lbz r0, 0x18(r31)
    cmplwi r0, 0x0
    beq fn_8014E804_L_8014EFE8
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x580
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014EFE0
    li r4, 0x0
    li r5, -0x1
    bl fn_80151F08
    fn_8014E804_L_8014EFE0:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    fn_8014E804_L_8014EFE8:
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x580
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F00C
    li r4, 0x1
    li r5, -0x1
    bl fn_80151F08
    fn_8014E804_L_8014F00C:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    lwz r3, 0x14(r31)
    addi r0, r3, 0x1
    stw r0, 0x14(r31)
    bl ServiceMode_UpdateScheduleGate
    bl OperationClock_Commit
    bl RaceFlow_ResetState_FullColdInit
    lwz r0, 0x40(r31)
    cmpwi r0, 0x0
    beq fn_8014E804_L_8014F05C
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F054
    li r4, 0x0
    li r5, 0x0
    bl fn_801500F4
    fn_8014E804_L_8014F054:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F07C
    fn_8014E804_L_8014F05C:
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F078
    li r4, 0x0
    li r5, 0x1
    bl fn_801500F4
    fn_8014E804_L_8014F078:
    stw r29, 0x8(r31)
    fn_8014E804_L_8014F07C:
    li r0, 0x1
    stw r0, 0x40(r31)
    b fn_8014E804_L_8014F114
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F0A4
    li r4, 0x1
    li r5, 0x0
    bl fn_801500F4
    fn_8014E804_L_8014F0A4:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F0C8
    li r4, 0x2
    li r5, 0x2
    bl fn_801500F4
    fn_8014E804_L_8014F0C8:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F0EC
    li r4, 0x3
    li r5, 0x1
    bl fn_801500F4
    fn_8014E804_L_8014F0EC:
    stw r29, 0x8(r31)
    b fn_8014E804_L_8014F114
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x2c
    bl Alloc
    mr. r29, r3
    beq fn_8014E804_L_8014F110
    bl fn_8014FC40
    fn_8014E804_L_8014F110:
    stw r29, 0x8(r31)
    fn_8014E804_L_8014F114:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq fn_8014E804_L_8014F138
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    li r3, 0x0
    bl fn_801B7CD0
    fn_8014E804_L_8014F138:
    lbz r4, 0x3c(r31)
    li r3, 0x0
    bl fn_801699D8
    bl RumbleUpdate
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
#else /* NON_MATCHING */
class SceneSprite {
public:
    char pad0[4];
    int mode;
    char pad8[4];
    float x;
    float y;
    char pad14[0x1C];
    SceneSprite(int id, int a, int b);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

struct SceneIf {
    virtual void _keySceneIf();
    virtual void Release();
    virtual void Start();
    virtual void Next();
    virtual bool IsDone();
};

struct StatusEntry {
    unsigned int kind;
    unsigned int arg;
    int pad;
};

#define STATUS_TABLE ((StatusEntry *)(base + 0x3758))

struct StatusView : SceneIf {
    unsigned char done;
    SceneIf *scene;
    int index;
    unsigned int kind;
    int f14;
    unsigned char f18;
    int course;
    int f20;
    char pad24[4];
    float f28;
    int f2C;
    int credits;
    unsigned char f34;
    int f38;
    unsigned char rumble;
    int f40;
};


struct NamCamTexture {
    NamCamTexture() { fn_801F6804(this); }
    ~NamCamTexture();
    char pad[0x4C];
};

class StatusLogoScene : public LoaderBase {
public:
    virtual void _keyStatusLogoScene();
    StatusLogoScene(char *base) {
        f4 = 0;
        f8 = 0.0f;
        palette = 0;
        if (isJapanese() == 1) {
            TEXLoadPalette_Retry(&palette, base + 0x38A4);
        } else {
            TEXLoadPalette_Retry(&palette, base + 0x38BC);
        }
        TEXBindPaletteEntry_RGB(palette, rgb, 0);
        if ((int)g_currentSceneState != 5) {
            SetSyncTarget(4);
        }
        fn_8002CFB8(0xFF, 0xFF, 0xFF, 0xFF);
    }
    int f4;
    float f8;
    int fC;
    void *palette;
    char rgb[0x20];
    NamCamTexture tex;
};

class StatusNoticeScene : public LoaderBase {
public:
    virtual void _keyStatusNoticeScene();
    StatusNoticeScene(char *base) {
        f4 = 0;
        f8 = 0.0f;
        palette = 0;
        if (isJapanese() == 1) {
            TEXLoadPalette_Retry(&palette, base + 0x38D4);
        } else {
            TEXLoadPalette_Retry(&palette, base + 0x38E8);
        }
        TEXBindPaletteEntry_RGB(palette, rgb, 0);
    }
    int f4;
    float f8;
    int fC;
    void *palette;
    char rgb[0x20];
    NamCamTexture tex;
};

class CourseDemoScene : public LoaderBase {
public:
    virtual void _keyCourseDemoScene();
    CourseDemoScene() {
        f4 = 0;
        f8 = 0.0f;
        f10 = 0;
        fC = 0.0f;
        cup = g_cupId;
        DrawManager_GetOrCreate();
    }
    int f4;
    float f8;
    float fC;
    unsigned char f10;
    int cup;
};

class EntryScene : public LoaderBase {
public:
    virtual void _keyEntryScene();
    virtual void Init();
    EntryScene(int arg, unsigned char flag) {
        lang = fn_80169E20();
        f8 = 0;
        fC = 0.0f;
        f10 = flag;
        f14 = 0;
        f18 = arg;
        f1C = 0;
        credits = CreditMgr_GetCreditCount(0);
        if (lang == 0) {
            sprite = new SceneSprite(0x138, 1, 0);
        } else {
            sprite = new SceneSprite(0x107, 1, 0);
        }
        if (sprite != 0) {
            sprite->mode = 1;
            fn_8019FEF4(sprite);
        }
        Init();
    }
    int lang;
    int f8;
    float fC;
    unsigned char f10;
    int f14;
    int f18;
    unsigned char f1C;
    int credits;
    SceneSprite *sprite;
};




extern "C" void fn_8014E804(StatusView *self) {
    char *base = (char *)Scene_8014E0C4_rodata_80363D30;
    int prev = self->credits;
    self->credits = CreditMgr_GetCreditCount(0);
    if (self->credits != prev) {
        StatusEntry *e;
        self->f34 = 1;
        e = STATUS_TABLE;
        if (e[self->index].kind != 6) {
            int i = 0;
            while (1) {
                if (e->kind >= 15) {
                    break;
                }
                if (e->kind == 6) {
                    if (self->scene != 0) {
                        GXDrawDone();
                        self->scene->Release();
                        self->scene = 0;
                    }
                    self->index = i;
                    break;
                }
                e++;
                i++;
            }
        }
    }
    if (self->scene != 0 && self->scene->IsDone()) {
        GXDrawDone();
        self->scene->Release();
        self->scene = 0;
        if (StrPcb_GetInstance() != 0) {
            StrPcb_ResetCommands_Zero(StrPcb_GetInstance(), 1);
            StrPcb_ResetCommands_NeutralDefault(StrPcb_GetInstance());
        }
        StatusEntry *table = STATUS_TABLE;
        do {
            self->index++;
            if (table[self->index].kind == 13) {
                if (lbl_806D12E1 == 1) {
                    self->index = self->index + 1;
                }
                lbl_806D12E1 = 1;
            }
            if (table[self->index].kind >= 15) {
                self->index = 1;
                self->f18 = 0;
                TitleDB *db = SINGLETON_INSTANCE(lbl_806D10A0);
                if (db != 0) {
                    TitleTracker_OnAttract_Stub(db);
                }
            }
        } while (table[self->index].kind == 6);
    }
    if (self->scene == 0) {
        StatusEntry *table = STATUS_TABLE;
        self->kind = table[self->index].kind;
        switch (self->kind) {
        case 0:
            self->f14++;
            ServiceMode_UpdateScheduleGate();
            OperationClock_Commit();
            RaceFlow_ResetState_FullColdInit();
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new StatusLogoScene(base);
            break;
        case 1:
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new StatusNoticeScene(base);
            break;
        case 2:
            if (self->f18) {
                self->scene = (SceneIf *)fn_8014E0C4(0);
            } else {
                self->scene = (SceneIf *)fn_8014E0C4(1);
            }
            break;
        case 3:
            self->scene = (SceneIf *)fn_8014D848();
            break;
        case 4:
            if (table[self->index].arg == 1 && self->course != 0 && self->course != 3) {
                if (self->course > 3) {
                    self->course = 0;
                } else {
                    self->course = 3;
                }
            }
            SetCourseParams(self->course + 1, 0, 0, 0);
            self->scene = (SceneIf *)new CourseDemoScene;
            if (++self->course >= 6) {
                self->course = 0;
            }
            break;
        case 5: {
            int arg = table[self->index].arg;
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new EntryScene(arg, 1);
            self->Next();
            break;
        }
        case 6: {
            int arg = table[self->index].arg;
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new EntryScene(arg, 0);
            break;
        }
        case 7:
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new AttractScene;
            break;
        case 8:
            self->scene = (SceneIf *)fn_80163614((void *)self->f20);
            if (++self->f20 >= 4) {
                self->f20 = 0;
            }
            break;
        case 9:
            if (self->f18) {
                Frame_PostDrawOverlay();
                Frame_UpdatePerFrameState();
                self->scene = (SceneIf *)new TitleScene(0, (void *)-1);
            } else {
                Frame_PostDrawOverlay();
                Frame_UpdatePerFrameState();
                self->scene = (SceneIf *)new TitleScene(1, (void *)-1);
            }
            break;
        case 10:
            self->f14++;
            ServiceMode_UpdateScheduleGate();
            OperationClock_Commit();
            RaceFlow_ResetState_FullColdInit();
            if (self->f40) {
                self->scene = (SceneIf *)new SelectScene((void *)0, 0);
            } else {
                self->scene = (SceneIf *)new SelectScene((void *)0, 1);
            }
            self->f40 = 1;
            break;
        case 11:
            self->scene = (SceneIf *)new SelectScene((void *)1, 0);
            break;
        case 12:
            self->scene = (SceneIf *)new SelectScene((void *)2, 2);
            break;
        case 13:
            self->scene = (SceneIf *)new SelectScene((void *)3, 1);
            break;
        case 14:
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            self->scene = (SceneIf *)new RankingScene;
            break;
        }
    }
    if (self->scene != 0) {
        self->scene->Start();
        fn_801B7CD0(0);
    }
    fn_801699D8(0, self->rumble);
    RumbleUpdate();
#endif /* NON_MATCHING */
}

extern "C" void fn_8014F164(CreditPanel *self) {
    float fade;
    int prev;
    int start;

    if (self->state == 9) {
        return;
    }
    if (!self->on) {
        self->on = 1;
    }
    if (self->sprite != 0) {
        Sprite_AdvanceAnim(self->sprite, 0.0165f);
    }
    prev = self->credits;
    self->credits = CreditMgr_GetCreditCount(0);
    if (self->credits != prev) {
        self->timer = 0;
    }
    self->timer++;
    fade = lbl_806D8060;
    if (self->alpha && self->timer < (int)fade) {
        self->alpha = Saturate_Double(1.0f - self->timer / fade, 0.0f, 1.0f);
    }
    start = self->duration - (int)fade;
    if (self->timer > start) {
        self->alpha = Saturate_Double((self->timer - start) / fade, 0.0f, 1.0f);
    } else {
        self->alpha = 0.0f;
    }
    if (self->timer >= self->duration) {
        self->state = 9;
    }
}

extern "C" DemoPanel *fn_8014F2DC(DemoPanel *self, short flag) {
    if (self != 0) {
        self->vt = Scene_8014E0C4_data_8048FD98;
        fn_80120A08(0x1553);
        fn_80120A08(0x1554);
        if (self->f8 != 0) {
            GXDrawDone();
            self->f8->vC();
            self->f8 = 0;
        }
        fn_801B7CD0(0);
        CreditMgr_SetActiveSlot(0);
        Scene_8014E0C4_bss_806D1580 = 0;
        fn_801933D0(0);
        fn_8002CFB8(0, 0, 0, 0xFF);
        fn_801699D8(0, 0);
        fn_80169C44();
        fn_80121210();
        clRom_PurgeAll();
        SetResourceLoadingFlag(0);
        if (self != 0) {
            self->vt = lbl_803FE0C8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

class ModeScene {
public:
    virtual void _keyModeScene();
    ModeScene() { done = 0; }
    virtual ~ModeScene();
    unsigned char done;
};

class StatusScene : public ModeScene {
public:
    virtual void _keyStatusScene();
    StatusScene();
    int f8;
    int fC;
    int f10;
    int f14;
    unsigned char f18;
    int f1C;
    int f20;
    char pad24[4];
    float f28;
    int f2C;
    int credits;
    unsigned char f34;
    int f38;
    unsigned char rumble;
    int f40;
};

StatusScene::StatusScene() {
    f14 = 0;
    f8 = 0;
    fC = 0;
    f10 = 0;
    f18 = 1;
    f28 = 0.0f;
    f2C = 0;
    credits = CreditMgr_GetCreditCount(0);
    f34 = 0;
    f38 = 0;
    if ((int)((unsigned char *)lbl_80598A60)[0x20] == 2) {
        rumble = 0;
    } else {
        rumble = 1;
    }
    rumble = 0;
    f1C = 0;
    f20 = 0;
    f40 = 0;
    if (lbl_806D12E2 == 0) {
        f40 = 1;
        fC = 1;
    }
    lbl_806D12E2 = 0;
    fn_80121210();
    clRom_PurgeAll();
    if (StrPcb_GetInstance() != 0) {
        StrPcb_ResetCommands_Zero(StrPcb_GetInstance(), 1);
        StrPcb_ResetCommands_NeutralDefault(StrPcb_GetInstance());
    }
    if (SINGLETON_INSTANCE(g_pInputState) != 0) {
        delete g_pInputState;
        g_pInputState = 0;
    }
    InitRumbleController(1);
    fn_801699D8(0, rumble);
    if ((int)g_currentSceneState != 5) {
        SetSyncTarget(4);
    }
    SetLocalPcbRole(0);
    lbl_806D12B0 = 0;
    SetResourceLoadingFlag(0);
    lbl_806D117C = CreditMgr_GetCreditCount(0) <= 0;
    CreditMgr_SetActiveSlot(0);
    Scene_8014E0C4_bss_806D1580 = (StatusInfo *)this;
    fn_801933D0(1);
    fn_801B7CD0(0);
    PreloadResource(0x1553);
    PreloadResource(0x1554);
}

extern "C" void fn_8014F5A8(VObj *p) {
    delete p;
}

extern "C" void fn_8014F5E0(void) {
    char *s = (char *)Scene_8014E0C4_rodata_80363D30;
    if (Scene_8014E0C4_bss_806D1580 != 0) {
        OverlayText(1, 1, 2, s + 0x38F8, Scene_8014E0C4_bss_806D1580->f14);
        OverlayText(1, 1, 3, s + 0x3908, Scene_8014E0C4_bss_806D1580->fC);
        OverlayText(1, 1, 4, s + 0x3918, Scene_8014E0C4_bss_806D1580->f10);
        OverlayText(1, 1, 5, s + 0x3928, Scene_8014E0C4_data_8048FD50[Scene_8014E0C4_bss_806D1580->f10]);
    }
}

extern "C" void *fn_8014F6A4(void) {
    return new Panel44;
}

extern "C" unsigned char fn_8014F6E0(StateObj *o) {
    return o->state == 9;
}

extern "C" CamPanel *fn_8014F6F4(CamPanel *self, short flag) {
    if (self != 0) {
        NamCamObj *cam;
        self->vt = NamCamPanelC_vtable_8048FFC0;
        if (self->cam != 0) {
            cam = self->cam;
            if (GetVBlankFlag() && cam->active) {
                cam->active = 0;
                NamCam_End();
            }
            cam = self->cam;
            if (cam != 0) {
                MemoryManager_Free(cam->buf);
                if (GetVBlankFlag()) {
                    if (GetVBlankFlag() && cam->active) {
                        cam->active = 0;
                        NamCam_End();
                    }
                    cam->buf = 0;
                }
                MemoryManager_TimedFree(cam);
            }
        }
        if (self->sprA != 0) {
            Sprite_Destroy(self->sprA, 1);
        }
        if (self->sprB != 0) {
            Sprite_Destroy(self->sprB, 1);
        }
        fn_80121210();
        clRom_PurgeAll();
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_8014F81C(VObj *p) {
    delete p;
}

extern "C" void fn_8014F854(FadeHolder *self) {
    fn_8011F994(0);
    if (self->fade != 0) {
        FlashFadeOverlay_Draw(self->fade, 99.0f, 3.0f, 539.0f, 285.0f, (float)lbl_80598A60[0x13], (float)lbl_80598A60[0x12]);
    }
    fn_8011F994(4);
    fn_8011F994(5);
    fn_8011F994(6);
}

extern "C" void fn_8014F8FC(NamCamPanel *self) {
    float fade;
    NamCamObj *cam;
    char info[0xC];
    void *handle;

    if (self->state == 9) {
        return;
    }
    fn_801698B4(0, 0x1499, 0, 320.0f, 240.0f);
    fn_801698B4(5, 0x149B, 0, 97.0f, 284.0f);
    fn_801698B4(5, 0x149C, 0, 544.0f, 284.0f);
    if (self->logo) {
        fn_801698B4(6, 0x50D, 0, 320.0f, 160.0f);
    }
    fn_801A1280();
    if (self->sprA != 0) {
        Sprite_AdvanceAnim(self->sprA, 0.0165f);
    }
    if (self->sprA != 0) {
        fn_801A0004(self->sprA);
    }
    if (self->sprB != 0) {
        self->scroll += 4.0f;
        if (640.0f + self->width < self->scroll) {
            self->scroll = 0.0f;
        }
        {
            float ofs = 0.0f;
            float left = 640.0f + self->width - self->scroll - self->width;
            self->sprB->SetPos(left + ofs, 409.0f);
            self->sprB->z = ofs;
        }
        Sprite_AdvanceAnim(self->sprB, 0.0165f);
        fn_801A0004(self->sprB);
    }
    cam = self->cam;
    if (cam != 0 && GetVBlankFlag() && cam->active) {
        if (NamCam_GetImageHandle(&handle, 0) == 1) {
            NamCam_LoadImage(handle, cam->buf, info);
            cam->loaded = 1;
        }
    }
    fade = lbl_806D8060;
    switch (self->state) {
    case 0:
        self->t += 1.0f;
        if (self->t < fade) {
            self->alpha = Saturate_Double(1.0f - self->t / fade, 0.0f, 1.0f);
        } else {
            self->alpha = 0.0f;
        }
        if (self->t >= 600.0f) {
            SetSyncTarget(5);
            self->state = 1;
            self->t = 0.0f;
        }
        break;
    case 1:
        self->alpha = 0.0f;
        if (PcbSync_AllKartsInValidSelectState()) {
            self->state = 2;
            self->t = 0.0f;
        }
        break;
    case 2:
        self->t += 1.0f;
        self->alpha = Saturate_Double(self->t / fade, 0.0f, 1.0f);
        if (self->t >= fade) {
            self->state = 9;
        }
        break;
    }
    if (0.0f < self->alpha) {
        ResCtrl c;
        fn_80121E10(&c);
        c.mode = 2;
        c.Show(320.0f, 240.0f, 1.0f);
        c.SetSize(640.0f, 480.0f);
        c.SetColor((unsigned char)(255.0f * self->alpha));
        fn_8011FAFC(&c, 7);
    }
}


#ifndef NON_MATCHING
class SceneSprite {
public:
    char pad0[4];
    int mode;
    char pad8[4];
    float x;
    float y;
    char pad14[0x1C];
    SceneSprite(int id, int a, int b);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};
#endif /* ! NON_MATCHING */

class NamCamC {
public:
    unsigned char active;
    unsigned char loaded;
    void *buf;
    NamCamC() {
        active = 0;
        loaded = 0;
        buf = 0;
        buf = FUN_8003b120(0x4B000);
    }
    void Stop() {
        if (GetVBlankFlag() && active) {
            active = 0;
            NamCam_End();
        }
    }
    void Start() {
        if (GetVBlankFlag()) {
            if (active == 1) {
                Stop();
            }
            active = 1;
            loaded = 0;
            NamCam_Init();
        }
    }
};

class NamCamPanelC : public SceneBase {
public:
    virtual void _keyNamCamPanelC();
    NamCamPanelC();
    int state;
    float t;
    float scroll;
    NamCamC *cam;
    float alpha;
    int mode;
    unsigned char logo;
    SceneSprite *sprA;
    SceneSprite *sprB;
    float width;
};

NamCamPanelC::NamCamPanelC() {
    state = 0;
    t = 0.0f;
    scroll = 0.0f;
    alpha = 1.0f;
    mode = isJapanese();
    if (!VBlankValue_Get()) {
        NamCamC *c;
        logo = 0;
        cam = new NamCamC;
        c = cam;
        c->Start();
    } else {
        logo = 1;
        cam = 0;
    }
    sprA = new SceneSprite(0x1AE, 1, 0);
    if (sprA != 0) {
        sprA->SetPos(320.0f, 137.0f);
    }
    if (fn_80169E20() == 0) {
        sprB = new SceneSprite(0x13D, 1, 0);
        width = 450.0f;
    } else {
        sprB = new SceneSprite(0x10B, 1, 0);
        width = 790.0f;
    }
}

extern "C" unsigned char fn_8014FE08(unsigned char *o) {
    return o[4];
}

extern "C" Base *fn_8014FE10(Base *self, short flag) {
    if (self != 0) {
        self->vt = TextPanelC_vtable_8048FFE8;
        if (((void **)self)[2] != 0) {
            Sprite_Destroy(((void **)self)[2], 1);
        }
        __destroy_new_array(((void **)self)[3], (void *)dtor_800869D0);
        ((void **)self)[3] = 0;
        fn_80121210();
        clRom_PurgeAll();
        fn_8002CFB8(0, 0, 0, 0);
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_8014FEC4(VObj *p) {
    delete p;
}

extern "C" void fn_8014FEFC(TextPanelB *self) {
    float a;
    if (self->sprite != 0) {
        fn_801A0004(self->sprite);
    }
    fn_8011FAB8();
    fn_801A1280();
    if (0.0f < (a = self->alpha)) {
        unsigned int col;
        void *r;
        fn_801F93EC(&self->text->top, 153.0f, 416.0f);
        fn_801F93D0(&self->text->top, 1.0f, 1.0f);
        col = 0xFFFFFF00 | ((int)(255.0f * a) & 0xFF);
        self->text->top.color = col;
        r = fn_801F8E58();
        fn_801F8A34(r, &self->text->top, 0);
        fn_801F93EC(&self->text->bottom, 153.0f, 442.0f);
        fn_801F93D0(&self->text->bottom, 1.0f, 1.0f);
        self->text->bottom.color = col;
        r = fn_801F8E58();
        fn_801F8A34(r, &self->text->bottom, 0);
    }
    fn_8011F994(0);
}

extern "C" void fn_80150004(TextPanel *self) {
    fn_801A1280();
    if (self->sprite != 0) {
        if (!Sprite_AdvanceAnim(self->sprite, 0.0165f)) {
            Sprite_Destroy(self->sprite, 1);
            self->sprite = 0;
            self->done = 1;
        }
    }
    self->timer++;
    switch (self->state) {
    case 0:
        self->alpha += 0.016666668f;
        if (1.0f < self->alpha) {
            self->alpha = 1.0f;
        }
        break;
    case 1:
        break;
    case 2:
        if (self->timer > 180) {
            self->alpha = self->alpha - 0.016666668f;
            if (self->alpha < 0.0f) {
                self->alpha = 0.0f;
            }
        }
        break;
    }
}

struct TextManager {
    char pad0[0x18];
    int visible;
    char pad1C[0x230 - 0x1C];
    TextManager();
    ~TextManager();
};



class TextPanelC : public SceneBase {
public:
    virtual void _keyTextPanelC();
    TextPanelC(int which, int state);
    unsigned char done;
    SceneSprite *sprite;
    TextManager *text;
    int state;
    int timer;
    float alpha;
};

#pragma use_lmw_stmw on
TextPanelC::TextPanelC(int which, int st) {
    TextPanelIds ids = TextPanelSpriteIds();
    char *info;

    fn_80121210();
    done = 0;
    sprite = 0;
    sprite = new SceneSprite(ids.id[which], 1, 0);
    if (sprite != 0) {
        sprite->mode = 7;
    }
    if (sprite == 0) {
        done = 1;
    }
    fn_8002CFB8(0xFF, 0xFF, 0xFF, 0);
    text = new TextManager[2];
    text[0].visible = 0;
    text[1].visible = 0;
    info = fn_80293BBC();
    TexMgr_SetTexture(&text[0], (const char *)lbl_803675B4, info + 0x18);
    TexMgr_SetTexture(&text[1], (const char *)lbl_803675C4, info + 0x2C);
    state = st;
    timer = 0;
    switch (st) {
    case 0:
        alpha = 0.0f;
        break;
    case 1:
        alpha = 1.0f;
        break;
    case 2:
        alpha = 1.0f;
        break;
    }
}
#pragma use_lmw_stmw reset

struct RaceSceneAnimCam : SceneCacheAnimScene {
    RaceSceneAnimCam(const char *path) : SceneCacheAnimScene(path) {}
    void step() {
        if (-1.0f != speed) {
            if (active) {
                active = 0;
            } else {
                frame += speed;
            }
            HSD_CObjReqAnim(camera, frame);
            HSD_CObjAnim(camera);
        }
    }
};
typedef void (*JObjHideFn)(void *, void *, int);

#pragma use_lmw_stmw on
static inline void LoadCam_(RaceScene *self, int mode, const char *path) {
    RaceScene *slot = (RaceScene *)((char *)self + mode * 4);
    if (slot->objs[0] == 0) {
        slot->objs[0] = (RaceCam *)new SceneCacheAnimScene(path);
        if (slot->objs[0] != 0) {
            ((SceneCacheAnimScene *)slot->objs[0])->start();
        }
        if (slot->objs[0] != 0) {
            ((RaceSceneAnimCam *)slot->objs[0])->step();
        }
    }
}
extern "C" void fn_801502AC(RaceScene *self, int mode) {
    const char *path;

    if (Scene_8014E0C4_rodata_80366EF0[mode].id == -1) {
        return;
    }
    path = ((const char *const *)&Scene_8014E0C4_rodata_80364368)[Scene_8014E0C4_rodata_80366EF0[mode].id];
    LoadCam_(self, mode, path);
    if (self->lists[mode] == 0) {
        self->lists[mode] = new SceneCacheModel(path, 1);
    }
    if (self->models[mode] == 0) {
        self->models[mode] = new SceneCacheNormal(path, 0);
        if (self->models[mode] != 0) {
            clNormal3D_SetScale(self->models[mode], 0, 0.0f, 1.0f, 0.0f, 0.0f);
        }
        if (self->models[mode] != 0) {
            clNormal3D_Exec(self->models[mode]);
        }
        if (Scene_8014E0C4_rodata_80366EF0[mode].id == 0x15) {
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_80367668), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_8036767C), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_80367690), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_803676A4), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_803676B8), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_803676CC), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_803676E0), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_803676F4), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_80367708), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_8036771C), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_80367730), 0x10);
            ((JObjHideFn)JObj_Hide)(self->models[mode], ResolveJointByName(self->models[mode], (char *)lbl_80367744), 0x10);
        }
    }
}
#pragma use_lmw_stmw reset


class VObjModel : public VObj {
public:
    char pad4[0x1C];
    VObjModel(const char *name, int a);
};

struct RacePartKart {
    int id;
    int pad[2];
};

static inline int RaceRefDec(HsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void RaceObjUnref(HsdObj *o) {
    if (o == 0) {
        return;
    }
    if (RaceRefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_8015061C(RaceScene *self, int part, int arg) {
    int i;

    switch (part) {
    case 4:
        for (i = 0; i < 11; i++) {
            if (self->drivers[i] != 0) {
                KartDriver_Dtor(self->drivers[i], 1);
            }
            if (self->effects[i] != 0) {
                VisualEffectHolder_Dtor(self->effects[i], 1);
            }
            self->drivers[i] = 0;
            self->effects[i] = 0;
            self->active[i] = 0;
            PSMTXIdentity(self->mtx[i]);
            g_playerRenderObj = 0;
        }
        break;
    case 5: {
        const RaceKartDescR *k = Scene_8014E0C4_rodata_80367200;
        for (i = 0; i < 11; i++) {
            if (arg == (int)k[i].character) {
                self->drivers[i] = new KartDrv;
                if (self->drivers[i] != 0) {
                    KartDriver_Init(self->drivers[i], 0, k[i].character, self->mtx[i], i, 0, 2);
                }
                self->effects[i] = new TornadoFx(0, self->drivers[i], k[i].character, 1, 0.0f, 0.0f, 0.0f);
                TireEffect_ResetSpin(self->effects[i], 0.0f, 1.0f);
                if (i == 0) {
                    g_playerRenderObj = (unsigned int)self->drivers[i];
                }
            }
        }
        break;
    }
    case 6:
        if (self->env != 0) {
            CourseEnvironment_Dtor(self->env, 1);
        }
        self->env = 0;
        g_raceCamera = 0;
        SetActiveCamera(0, 0);
        if (self->camera != 0) {
            delete self->camera;
        }
        if (self->lights != 0) {
            RaceObjUnref(self->lights);
        }
        self->camera = 0;
        self->lights = 0;
        break;
    case 7:
        self->obj574 = new VObjModel((const char *)lbl_80367758, 0);
        fn_8013D738(self->obj574, 0.0f, 1.0f);
        fn_8013D4B0(self->obj574, 0.0f);
        break;
    case 8:
        if (self->sprites[arg] == 0) {
            if (lbl_80367284[arg] != -1) {
                self->sprites[arg] = new SceneSprite(lbl_80367284[arg], 1, 0);
                self->spriteOn[arg] = 1;
            }
        }
        break;
    }
}
#pragma use_lmw_stmw reset

extern "C" unsigned char fn_80150924(unsigned char *o) {
    return o[0x10];
}

static inline int RefDec(HsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void ObjUnref(HsdObj *o) {
    if (o == 0) {
        return;
    }
    if (RefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}

extern "C" RaceScene *fn_8015092C(RaceScene *self, short flag) {
    if (self != 0) {
        int i;
        self->vt = RaceSceneC_vtable_80490010;
        if (self->obj574 != 0) {
            delete self->obj574;
        }
        fn_8013DB9C();
        if (self->cardOn && self->cardSlot != -1 && fn_8019083C(self->cardSlot)) {
            fn_801909A4(self->cardSlot);
        }
        if (self->env != 0) {
            CourseEnvironment_Dtor(self->env, 1);
        }
        g_raceCamera = 0;
        SetActiveCamera(0, 0);
        if (self->camera != 0) {
            delete self->camera;
        }
        if (self->lights != 0) {
            ObjUnref(self->lights);
        }
        for (i = 0; i < 21; i++) {
            if (self->objs[i] != 0) {
                delete self->objs[i];
            }
            if (self->lists[i] != 0) {
                LObjList_Destroy(self->lists[i], 1);
            }
            if (self->models[i] != 0) {
                Object_DtorWithGXSync(self->models[i], 1);
            }
        }
        for (i = 0; i < 11; i++) {
            if (self->drivers[i] != 0) {
                KartDriver_Dtor(self->drivers[i], 1);
            }
            if (self->effects[i] != 0) {
                VisualEffectHolder_Dtor(self->effects[i], 1);
            }
        }
        for (i = 0; i < 48; i++) {
            if (self->sprites[i] != 0) {
                Sprite_Destroy(self->sprites[i], 1);
            }
        }
        SetCourseScene3D(0);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        SceneDrawList_Reset();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        SetResourceLoadingFlag(0);
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80150BE4(VObj *p) {
    delete p;
}

static inline void RaceDrawLogo(float alpha) {
    if (alpha <= 0.0f) {
        return;
    }
    {
        ResCtrl c;
        float h, w;
        w = lbl_806D7F58[0];
        h = lbl_806D7F58[1];
        c.mode = 2;
        c.SetSize(w, h);
        c.SetColor(0xFFFFFF00 | (unsigned char)(int)(255.0f * alpha));
        c.Show(0.5f * w + 99.0f, 0.5f * h + 309.0f, 1.0f);
        fn_8011FAFC(&c, 6);
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80150C1C(RaceScene *self) {
    int i;
    if (self->objs[self->mode] != 0) {
        SetCourseScene3D(self->objs[self->mode]);
        if (self->objs[self->mode]->Begin()) {
            unsigned char wave;
            clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
            LObjList_ApplyForCObj(self->lists[self->mode]);
            if (Scene_8014E0C4_rodata_80366EF0[self->mode].transparent) {
                TransparentDraw_SortAndDispatch();
            }
            CObj_DebugVizPathFlush(self->objs[self->mode]);
            if (self->env != 0 && Scene_8014E0C4_rodata_80366EF0[self->mode].env) {
                CourseEnvironment_RenderObjects_Timed(self->env);
                Subsystem36c_DispatchPass2_Timed(self->env);
            }
            wave = 0;
            if (self->mode == 0x11) {
                wave = 1;
            }
            if (self->mode == 0x13) {
                wave = 1;
            }
            for (i = 0; i < 11; i++) {
                if (wave == 1) {
                    self->uv[i].u += 0.05f;
                    self->uv[i].v += 0.05f;
                    while (1.0f < self->uv[i].u) {
                        self->uv[i].u -= 1.0f;
                    }
                    while (1.0f < self->uv[i].v) {
                        self->uv[i].v -= 1.0f;
                    }
                }
                if (self->drivers[i] != 0 && self->active[i]) {
                    KartItem_FlushRenderIfReady(self->effects[i]);
                    KartDriver_RenderTimed(self->drivers[i], 2, 1);
                    KartItem_FlushPendingRender(self->effects[i]);
                    KartItem_DispatchEffectRenderByState(self->effects[i]);
                    KartDriver_RenderTimed(self->drivers[i], 3, 1);
                    KartItem_FlushPendingRender_v2(self->effects[i]);
                    if (wave == 1) {
                        fn_802BD6AC(self->uv[i].u, self->uv[i].v);
                    }
                    KartItem_DispatchEffectRenderByState(self->effects[i]);
                    KartDriver_RenderTimed(self->drivers[i], 4, 1);
                    KartItem_FlushPendingRender_v2(self->effects[i]);
                    if (wave == 1) {
                        fn_802BD6C0();
                    }
                    TornadoEffect_SubmitRender(self->effects[i]);
                }
            }
            if (self->mode < 0x14 || self->timer < 0xB4) {
                Object_RenderJObjTree(self->models[self->mode], 7);
            }
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
            self->objs[self->mode]->End();
            HSD_LObjDeleteCurrentAll(0);
        }
    }
    for (i = 0; i < 48; i++) {
        if (self->sprites[i] != 0 && self->spriteOn[i] == 2) {
            fn_801A0004(self->sprites[i]);
        }
    }
    if (isJapanese() == 1) {
        if (self->mode == 4) {
            if (self->timer >= 0xD2) {
                float a;
                float t = (float)self->timer - 210.0f;
                if (t <= 7.0f) {
                    a = 0.7f * (t / 7.0f);
                } else {
                    a = 0.3f * ((t - 7.0f) / 7.0f) + 0.7f;
                }
                if (a > 1.0f) {
                    a = 1.0f;
                }
                RaceDrawLogo(a);
            }
        } else if (self->mode == 0x14) {
            if (self->timer >= 0x78) {
                float a;
                float t = (float)self->timer - 120.0f;
                if (t <= 5.0f) {
                    a = 0.7f * (t / 5.0f);
                } else {
                    a = 0.3f * ((t - 5.0f) / 5.0f) + 0.7f;
                }
                if (a > 1.0f) {
                    a = 1.0f;
                }
                RaceDrawLogo(a);
            }
        }
    }
    if (self->mode == 0x14 && self->timer >= 0xAA) {
        float a;
        float t = (float)self->timer - 170.0f;
        if (t <= 3.0f) {
            a = 0.7f * (t / 3.0f);
        } else {
            a = 0.3f * ((t - 3.0f) / 3.0f) + 0.7f;
        }
        if (a >= 1.0f) {
            a = 1.0f;
        }
        fn_801695E0(6, 0x2AFD, 0, 49.0f, 445.5f, a);
    }
    fn_8011F994(0);
    fn_8011F994(4);
    fn_8013D940(7);
    fn_8011F994(6);
}
#pragma use_lmw_stmw reset

struct CourseCamAnim {
    void *vt;
    void *cobj;
    char pad8[0x3084 - 0x8];
    unsigned char reset;
    float speed;
    float frame;
};

struct VfxVec {
    float x, y, z;
};

static inline unsigned char JObjMtxIsDirty(void *j) {
    if (j == 0) {
        __assert((char *)lbl_806D8134, 0x25D, (char *)lbl_806D813C);
    }
    unsigned int flags = *(unsigned int *)((char *)j + 0x14);
    unsigned char dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        dirty = 1;
    }
    return dirty;
}

static inline void JObjSetupMatrix(void *j) {
    if (j == 0) {
        __assert((char *)lbl_806D8134, 0x47C, (char *)lbl_806D813C);
    }
    if (j != 0) {
        if (JObjMtxIsDirty(j)) {
            HSD_JObjSetupMatrixSub(j);
        }
    }
}

static inline void CamAnim_SetFrame(CourseCamAnim *c, float f) {
    if (c->frame < 0.0f || f < 0.0f) {
        return;
    }
    c->reset = 1;
    c->frame = f;
}

static inline void CamAnim_Tick(CourseCamAnim *c) {
    if (-1.0f != c->speed) {
        if (c->reset) {
            c->reset = 0;
        } else {
            c->frame += c->speed;
        }
        HSD_CObjReqAnim(c->cobj, c->frame);
        HSD_CObjAnim(c->cobj);
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80151234(RaceScene *self) {
    int i;
    VfxVec scissor;

    if (!self->done) {
        self->timer++;
    }
    if (Scene_8014E0C4_rodata_80366EF0[self->mode].time <= self->timer) {
        if (self->started == 0) {
            int next = self->mode + 1;
            if (next < 21) {
                self->mode = next;
                if (self->mode == 1) {
                    SetSyncTarget(3);
                }
                self->timer = 0;
                if (self->obj574 != 0) {
                    delete self->obj574;
                }
                self->obj574 = 0;
                {
                    int k = self->mode - 1;
                    if (self->objs[k] != 0) {
                        delete self->objs[k];
                    }
                    if (self->lists[k] != 0) {
                        LObjList_Destroy(self->lists[k], 1);
                    }
                    if (self->models[k] != 0) {
                        Object_DtorWithGXSync(self->models[k], 1);
                    }
                    self->objs[k] = 0;
                    self->lists[k] = 0;
                    self->models[k] = 0;
                }
            } else {
                self->done = 1;
            }
        } else {
            self->done = 1;
        }
    }
    {
        int st = PcbSyncTable_Ptr()[0x18];
        if (self->mode == 1 && (int)g_currentSceneState == 3) {
            if (*(unsigned char *)&g_pcbSyncReady && st == 2) {
                SetSyncTarget(4);
            } else if (st == 1) {
                SetSyncTarget(4);
            } else {
                return;
            }
        }
    }
    {
        int k = Scene_8014E0C4_rodata_80366EF0[self->mode].f10 * 3;
        fn_8002CFB8(lbl_806D7F70[k], lbl_806D7F70[k + 1], lbl_806D7F70[k + 2], 0);
    }
    {
        int next = self->mode + 1;
        if (next < 21 && Scene_8014E0C4_rodata_80366EF0[self->mode].time - 15 <= self->timer) {
            ((void (*)(RaceScene *, int))fn_801502AC)(self, next);
        }
    }
    if (Scene_8014E0C4_rodata_80366EF0[self->mode].id != -1) {
        if (self->objs[self->mode] != 0) {
            CamAnim_SetFrame((CourseCamAnim *)self->objs[self->mode], (float)self->timer);
            CamAnim_Tick((CourseCamAnim *)self->objs[self->mode]);
        }
        if (self->models[self->mode] != 0) {
            Object_SetField8_AndDirty(self->models[self->mode], (float)self->timer);
            clNormal3D_Exec(self->models[self->mode]);
        }
        SetCourseScene3D(self->objs[self->mode]);
        if (self->objs[self->mode] != 0 && self->camera != 0) {
            CObj_ApplyScissor(self->objs[self->mode], &scissor);
            SceneRender_SetViewportRect(self->camera, scissor.x, scissor.y, scissor.z, 0.0f, 1.0f, 0.0f);
        }
    }
    while (self->scriptIdx < self->scriptCount) {
        if (self->script[self->scriptIdx].start < self->mode) {
            self->scriptIdx++;
            continue;
        }
        if (self->mode < self->script[self->scriptIdx].start) {
            break;
        }
        if (self->script[self->scriptIdx].f4 < self->timer) {
            self->scriptIdx++;
            continue;
        }
        if (self->timer < self->script[self->scriptIdx].f4) {
            break;
        }
        switch (self->script[self->scriptIdx].type) {
        case 0: {
            int j;
            int idx = self->script[self->scriptIdx].arg;
            for (j = 0; j < 48; j++) {
                if (self->sprites[j] != 0 && j != idx) {
                    Sprite_Destroy(self->sprites[j], 1);
                    self->sprites[j] = 0;
                    self->spriteOn[j] = 3;
                }
            }
            if (self->sprites[idx] == 0) {
                if (lbl_80367284[idx] != -1) {
                    self->sprites[idx] = new SceneSprite(lbl_80367284[idx], 1, 0);
                    self->spriteOn[idx] = 1;
                }
            }
            if (self->spriteOn[idx] == 1) {
                self->spriteOn[idx] = 2;
            }
            break;
        }
        case 1: {
            void *eff = DrawEffect_SpawnByType((unsigned char)self->script[self->scriptIdx].arg);
            if (eff != 0) {
                VfxVec pos = *(const VfxVec *)&lbl_80367344;
                if (self->script[self->scriptIdx].joint != 0 && self->models[self->mode] != 0) {
                    void *jobj = ResolveJointByName(self->models[self->mode], (char *)self->script[self->scriptIdx].joint);
                    if (jobj != 0) {
                        JObjSetupMatrix(jobj);
                        Mtx44_GetTranslation_RowMajor(&pos, (char *)jobj + 0x44);
                        Vec3_Copy((char *)eff + 0x8C, &pos);
                    }
                }
                ((void (**)(void *))lbl_80419FB8)[self->script[self->scriptIdx].arg](eff);
            }
            break;
        }
        case 2:
            if (self->cardOn) {
                if (self->cardSlot != -1) {
                    if (fn_8019083C(self->cardSlot)) {
                        fn_801909A4(self->cardSlot);
                    }
                    self->cardSlot = -1;
                }
                if (ClSound_PlayBgmStream(self->script[self->scriptIdx].arg, 0)) {
                    clStream_setVolume(self->script[self->scriptIdx].arg, 100);
                    self->cardSlot = self->script[self->scriptIdx].arg;
                }
            }
            break;
        case 3:
            if (self->cardOn) {
                if (self->stream != -1) {
                    ClStream_Stop(self->stream);
                    self->stream = -1;
                }
                self->stream = ClStream_PlayMono(*(int *)((char *)fn_801B3A50(self->script[self->scriptIdx].arg) + 8), 0, 0);
                if (self->stream != -1) {
                    fn_80194AE0(self->stream, (((unsigned char *)lbl_80598A60)[0x31] & 0x7F) * 2);
                }
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            ((void (*)(RaceScene *, int, int))fn_8015061C)(self, self->script[self->scriptIdx].type, self->script[self->scriptIdx].arg);
            break;
        }
        self->scriptIdx++;
    }
    if (self->stream != -1 && !ClStream_IsActive(self->stream)) {
        ClStream_Stop(self->stream);
        self->stream = -1;
    }
    for (i = 0; i < 11; i++) {
        if (self->drivers[i] != 0) {
            ItemEffectBus_SnapshotAndFullReset(*(void **)((char *)self->drivers[i] + 0x304));
        }
    }
    {
        VfxVec from;
        VfxVec to;
        for (i = 0; i < 11; i++) {
            if (self->drivers[i] != 0) {
                void *jobj = 0;
                if (self->models[self->mode] != 0) {
                    jobj = ResolveJointByName(self->models[self->mode], (char *)Scene_8014E0C4_rodata_80367200[i].joint);
                }
                if (jobj != 0) {
                    float yaw0;
                    float yaw1;
                    float dist;
                    int col;
                    Mtx44_GetTranslation_RowMajor(&from, self->mtx[i]);
                    yaw0 = Mtx44_GetYawOfPosZ_Padded(self->mtx[i]);
                    JObjSetupMatrix(jobj);
                    PSMTXCopy((char *)jobj + 0x44, self->mtx[i]);
                    Mtx44_GetTranslation_RowMajor(&to, self->mtx[i]);
                    yaw1 = Mtx44_GetYawOfPosZ_Padded(self->mtx[i]);
                    dist = fn_800D3184(&from, &to);
                    RenderObj_ItemStateMachine_Timed(self->drivers[i], 0, BuildOrientationFromYaw(yaw1 - yaw0) / 0.017453289f / 90.0f, dist);
                    col = 0;
                    if (self->timer < Scene_8014E0C4_rodata_80366EF0[self->mode].fC) {
                        col = 0x20;
                    }
                    TornadoEffect_SetScalePairB0BC(self->effects[i], 0.0f, 1.0f);
                    TornadoEffect_SetFlagB4(self->effects[i], 0);
                    TornadoEffect_SetColorPairC8CC(self->effects[i], col, col);
                    TornadoEffect_Tick(self->effects[i], 0);
                    if (*(int *)((char *)self->drivers[i] + 0x1F8) == 10) {
                        KartDriver_TickAction_79268_AndSetSlot5aEulerZ(self->drivers[i], -Mtx44_GetPitchOfPosZ_Padded(KartDriver_GetJointByIdx(self->drivers[i], 0)));
                    }
                    self->active[i] = 1;
                } else {
                    self->active[i] = 0;
                    TornadoEffect_SetColorPairC8CC(self->effects[i], 0, 0);
                }
            }
        }
    }
    for (i = 0; i < 11; i++) {
        if (self->drivers[i] != 0) {
            ItemEffectBus_TickTornadoCooldown(*(void **)((char *)self->drivers[i] + 0x304));
        }
    }
    if (self->objs[self->mode] != 0 && self->env != 0) {
        CourseEnvironment_UpdateAndCullZones_Timed(self->env);
    }
    {
        VfxVec eye = *(const VfxVec *)&lbl_80367350;
        VfxVec target = *(const VfxVec *)&lbl_8036735C;
        if (self->objs[self->mode] != 0) {
            CObj_LoadProjMatrix(self->objs[self->mode], &eye);
            CObj_ApplyScissor(self->objs[self->mode], &target);
        }
        ItemObjectManager_Update();
        VfxSlotMgr_Update(eye, target);
        fn_801A1280();
    }
    for (i = 0; i < 48; i++) {
        if (self->sprites[i] != 0 && self->spriteOn[i] == 2 && !Sprite_AdvanceAnim(self->sprites[i], 0.0165f) && self->mode != 20) {
            Sprite_Destroy(self->sprites[i], 1);
            self->sprites[i] = 0;
            self->spriteOn[i] = 3;
        }
    }
    if (self->obj574 != 0) {
        float x = 320.0f;
        float y = 240.0f;
        float s = 100.0f;
        float rot = 0.0f;
        if (self->mode == 16) {
            int t = self->timer;
            if (t >= 0 && t <= 40) {
                rot = 0.6283184f * (float)t;
            } else if (t >= 40 && t <= 58) {
                rot = 0.34906578f * ((float)t - 40.0f);
            }
            x = 320.0f;
            if (t >= 0 && t <= 20) {
                y = -19.9f * (float)t + 586.0f;
            } else if (t >= 20) {
                y = 188.0f;
            }
        } else if (self->mode == 17) {
            int t = self->timer;
            if (t >= 0 && t <= 20) {
                x = -13.3f * (float)t + x;
                y = 6.4f * (float)t + 188.0f;
                s = -3.25f * (float)t + s;
            } else if (t >= 20) {
                x = 54.0f;
                y = 316.0f;
                s = 35.0f;
            }
        }
        s *= 0.01f;
        fn_8013D660(self->obj574, x, y);
        fn_8013D634(self->obj574, 0.0f, -0.16f, 0.0f);
        fn_8013D59C(self->obj574, 0.0f, rot, 0.0f);
        fn_8013D608(self->obj574, s * lbl_806D8180, s * lbl_806D8180, s * lbl_806D8180);
        fn_8013D4B0(self->obj574, 1.0f);
        fn_8013D704(self->obj574);
        fn_8013DAC8(self->obj574, 7);
    }
}
#pragma use_lmw_stmw reset

struct RaceKartDesc {
    int character;
    const void *joint;
    unsigned char enabled;
    char pad9[3];
};

class RaceInputManager {
public:
    char data[0x37C];
    RaceInputManager();
};

class RaceCamera {
public:
    char data[0x2C];
    RaceCamera(float a, int w, float b, int h, void *lights);
};

class RaceDriver {
public:
    char data[0x384];
    RaceDriver();
};

class RaceTornado {
public:
    char data[0x154];
    RaceTornado(int a, RaceDriver *drv, int character, int b, float x, float y, float z);
};

class RaceSceneC : public SceneBase {
public:
    virtual void _keyRaceSceneC();
    RaceSceneC(unsigned char card, int mode);
    int started;
    int mode;
    int cardSlot;
    unsigned char flag10;
    unsigned char card;
    char pad12[2];
    int sel;
    int f18;
    RaceInputManager *input;
    RaceCamera *camera;
    void *lights;
    void *objs[21];
    void *lists[21];
    void *models[21];
    RaceDriver *drivers[11];
    RaceTornado *effects[11];
    float mtx[11][3][4];
    unsigned char active[11];
    char pad397;
    RaceUV uv[11];
    void *sprites[48];
    int spriteOn[48];
    int f570;
    void *f574;
    RaceScriptEntry *script;
    int scriptCount;
};

#pragma use_lmw_stmw on
RaceSceneC::RaceSceneC(unsigned char card, int mode) {
    char *scripts;
    int i;

    DrawManager_GetOrCreate();
    fn_80121210();
    DMAChannelManager_Init();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    switch (fn_80169E20()) {
    case 1:
        if (IsCardValid() == 1) {
            script = lbl_8048F5BC;
            scriptCount = 0x33;
        } else {
            script = lbl_8048F9B8;
            scriptCount = 0x2E;
        }
        break;
    case 2:
        script = lbl_8048F9B8;
        scriptCount = 0x2E;
        break;
    default:
        script = lbl_8048F1C0;
        scriptCount = 0x33;
        break;
    }
    if (mode < -1) {
        mode = -1;
    }
    if (mode > 20) {
        mode = 20;
    }
    cardSlot = -1;
    flag10 = 0;
    if (mode < 0) {
        started = 0;
        this->mode = 0;
    } else {
        started = 1;
        this->mode = mode;
    }
    f18 = 0;
    this->card = card;
    sel = -1;
    input = 0;
    camera = 0;
    lights = 0;
    for (i = 0; i < 21; i++) {
        objs[i] = 0;
    }
    for (i = 0; i < 21; i++) {
        lists[i] = 0;
    }
    for (i = 0; i < 21; i++) {
        models[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        drivers[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        effects[i] = 0;
    }
    for (i = 0; i < 48; i++) {
        sprites[i] = 0;
    }
    for (i = 0; i < 48; i++) {
        spriteOn[i] = 0;
    }
    g_cupId = 8;
    g_longRoundFlag = 1;
    g_courseVariantIdx = 0;
    input = new RaceInputManager;
    lights = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new RaceCamera(lbl_806D80C0, 0x200, lbl_806D8184, 0x200, lights);
    SetActiveCamera(0, (int)camera);
    g_raceCamera = camera;
    for (i = 0; i < 11; i++) {
        drivers[i] = 0;
        effects[i] = 0;
        active[i] = 0;
        PSMTXIdentity(mtx[i]);
        uv[i].u = lbl_806D8064;
        uv[i].v = lbl_806D8064;
        if (Scene_8014E0C4_rodata_80367200[i].enabled) {
            drivers[i] = new RaceDriver;
            if (drivers[i] != 0) {
                KartDriver_Init(drivers[i], 0, Scene_8014E0C4_rodata_80367200[i].character, mtx[i], i, 0, 0);
            }
            effects[i] = new RaceTornado(0, drivers[i], Scene_8014E0C4_rodata_80367200[i].character, 1, lbl_806D8064, lbl_806D8064, lbl_806D8064);
            TireEffect_ResetSpin(effects[i], lbl_806D8064, lbl_806D8068);
            if (i == 0) {
                g_playerRenderObj = (unsigned int)drivers[i];
            }
        }
    }
    for (i = 0; i < 48; i++) {
        sprites[i] = 0;
        spriteOn[i] = 0;
    }
    for (i = 0; i < 21; i++) {
        objs[i] = 0;
        lists[i] = 0;
        models[i] = 0;
    }
    ((void (*)(RaceSceneC *, int))fn_801502AC)(this, this->mode);
    FileLoader_Open(((void **)lbl_8041BC00)[0xBA4 / 4]);
    FileLoader_Open(((void **)lbl_8041BC00)[0xBB8 / 4]);
    for (i = 0; i < scriptCount; i++) {
        RaceScriptEntry *e = &script[i];
        int type = e->type;
        if (type == 4 || (unsigned int)(type - 5) <= 2 || type == 8) {
            if (e->start < this->mode) {
                ((void (*)(RaceSceneC *, int, int))fn_8015061C)(this, type, e->arg);
            }
        }
    }
    f570 = -1;
    f574 = 0;
    fn_8013DBF8();
}

#pragma use_lmw_stmw on
static inline void GXPosition2f32(float x, float y) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
}

static inline void GXTexCoord2f32(float s, float t) {
    GXFIFO.f32 = s;
    GXFIFO.f32 = t;
}

#pragma use_lmw_stmw on
extern "C" void DrawColoredQuad(int r, int g, int b, int a, float x, float y, float w, float h) {
    float proj[4][4];
    float view[3][4];

    GXSetZMode(0, 7, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 100.0f);
    GXSetProjection(proj, 1);
    Vec3f eye = *(const Vec3f *)lbl_80366DE0;
    Vec3f up = *(const Vec3f *)lbl_80366DEC;
    Vec3f target = *(const Vec3f *)lbl_80366DF8;
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTevOp(0, 4);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXColorB color = lbl_806DCF38;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    GXSetChanMatColor(4, color);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 0, 4, 0);
    GXBegin(0x80, 0, 4);
    GXPosition2f32(x, y);
    GXPosition2f32(x + w, y);
    GXPosition2f32(x + w, y + h);
    GXPosition2f32(x, y + h);
}
#pragma use_lmw_stmw reset
#pragma use_lmw_stmw reset

extern "C" void fn_80152930(VObj *p) {
    delete p;
}

extern "C" Base *fn_80152968(Base *self, short flag) {
    if (self != 0) {
        self->vt = EntryScene_vtable_8048FE14;
        if (((void **)self)[9] != 0) {
            Sprite_Destroy(((void **)self)[9], 1);
        }
        fn_80121210();
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" unsigned char fn_801529EC(StateObj *o) {
    return o->state8 == 9;
}

extern "C" void fn_80152A00(CreditPanel *self) {
    if (self->on) {
        if (self->sprite != 0) {
            fn_801A0004(self->sprite);
        }
        if (self->f4 != 0) {
            ResCtrl c;
            float w, h;
            w = lbl_806D7F58[0];
            h = lbl_806D7F58[1];
            c.mode = 2;
            c.SetSize(w, h);
            c.SetColor(0xFFFFFFFF);
            c.Show(0.5f * w + 98.0f, 0.5f * h + 309.0f, 1.0f);
            fn_8011FAFC(&c, 6);
        }
        fn_801695E0(6, 0x2AFD, 0, 49.0f, 445.5f, 1.0f);
        fn_8011FAB8();
        fn_801A1280();
        fn_8011F994(0);
        if (self->alpha > 0.0f) {
            DrawColoredQuad(0, 0, 0, (int)(255.0f * self->alpha), 0.0f, 0.0f, 640.0f, 480.0f);
        }
    }
}

extern "C" void fn_80152B2C(VObj *p) {
    delete p;
}

extern "C" Base *fn_80152B64(Base *self, short flag) {
    if (self != 0) {
        self->vt = CourseDemoScene_vtable_8048FE3C;
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct TaPanel {
    void *vt;
    int state;
    float t;
    float alpha;
    unsigned char started;
    char pad11[3];
    int course;
};

struct TaEntry {
    unsigned short name[6];
    signed char chr;
    unsigned char title;
    unsigned char variant;
};

static inline void TaDrawTitle(void *db, TaEntry *e, float x, float y) {
    if (db != 0) {
        const char *name = get_title_name(db, e->title, e->variant, e->chr, 0);
        if (name != 0) {
            if (isJapanese() == 1) {
                fn_80168910(0, name, x, y, 0.9f, 1.0f);
            } else {
                fn_80168910(0, name, x, y, 0.8f, 1.0f);
            }
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80152C00(TaPanel *self) {
    float fade;
    float t;
    int i;
    const char *name;
    void *db;
    int course;
    float x0;
    float x1;
    float sx;
    int idL;
    int idR;
    float time;
    TaEntry *e;
    if (self->state == 9) {
        return;
    }
    course = self->course - 1;
    db = SINGLETON_INSTANCE(lbl_806D10A0);
    x0 = 0.0f;
    x1 = x0;
    if (self->t < 30.0f) {
        x0 = -640.0f + 640.0f * (self->t / 30.0f);
        x1 = 640.0f - 640.0f * (self->t / 30.0f);
    }
    idL = -1;
    idR = -1;
    switch (self->course) {
    case 1:
        sx = 244.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    case 2:
        sx = 244.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    case 3:
        sx = 276.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    case 4:
        sx = 256.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    case 5:
        sx = 260.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    case 6:
        sx = 296.0f;
        idL = 0x1D62;
        idR = 0x1D62;
        break;
    }
    fn_801698B4(0, idL, 0, 256.0f, 240.0f);
    fn_801698B4(0, idR, 0, 576.0f, 240.0f);
    fn_801698B4(0, 0x865, 0, 320.0f, 45.0f);
    fn_801698B4(0, course + 0x76C, 0, 110.0f + x0, 60.0f);
    if (isJapanese() == 1) {
        fn_80168A4C(0, (const char *)Scene_8014E0C4_rodata_803677B0, 318.0f + x1, 43.0f);
    } else {
        fn_80168A4C(0, (const char *)Scene_8014E0C4_rodata_803677C8, 318.0f + x1, 43.0f);
    }
    fn_801698B4(0, 0x76A, 0, 320.0f + x0, 137.0f);
    fn_801698B4(0, course * 2 + 0x750, 0, 144.0f + x0, 127.0f);
    fn_801698B4(0, 0x769, 0, x0 + sx, 127.0f);
    fn_801698B4(0, 0x75C, 0, 101.0f + x1, 157.0f);
    fn_801698B4(0, 0x75D, 0, 101.0f + x1, 214.0f);
    fn_801698B4(0, 0x76A, 0, 320.0f + x0, 317.0f);
    fn_801698B4(0, course * 2 + 0x751, 0, 144.0f + x0, 307.0f);
    fn_801698B4(0, 0x769, 0, x0 + sx, 307.0f);
    fn_801698B4(0, 0x75C, 0, 101.0f + x1, 337.0f);
    fn_801698B4(0, 0x75D, 0, 101.0f + x1, 394.0f);

    time = TaRecord_GetTime_Indexed(0, 1, self->course, 0, 0);
    e = TaRecord_GetEntry_Indexed(0, 1, self->course, 0, 0);
    fn_80167DDC(0, e->name, 68.0f + x1, 180.0f);
    fn_801698B4(0, fn_8013BFCC(e->chr), 0, 209.0f + x1, 177.0f);
    for (i = 0; i < 8; i++) {
        fn_801698B4(0, fn_80167744(i, time) + 0x778, 0, 18.0f * (7 - i) + (255.0f + x1), 180.0f);
    }
    if (db != 0) {
        name = get_title_name(db, e->title, e->variant, e->chr, 0);
        if (name != 0) {
            if (isJapanese() == 1) {
                fn_80168910(0, name, 422.0f + x1, 184.0f, 0.9f, 1.0f);
            } else {
                fn_80168910(0, name, 422.0f + x1, 184.0f, 0.8f, 1.0f);
            }
        }
    }

    fn_80167DDC(0, e->name, 68.0f + x1, 236.0f);
    fn_801698B4(0, fn_8013BFCC(e->chr), 0, 209.0f + x1, 233.0f);
    for (i = 0; i < 8; i++) {
        fn_801698B4(0, fn_80167744(i, time) + 0x778, 0, 18.0f * (7 - i) + (255.0f + x1), 236.0f);
    }
    TaDrawTitle(db, e, 422.0f + x1, 240.0f);

    time = TaRecord_GetTime_Indexed(0, 1, self->course, 1, 0);
    e = TaRecord_GetEntry_Indexed(0, 1, self->course, 1, 0);
    fn_80167DDC(0, e->name, 68.0f + x1, 360.0f);
    fn_801698B4(0, fn_8013BFCC(e->chr), 0, 209.0f + x1, 357.0f);
    for (i = 0; i < 8; i++) {
        fn_801698B4(0, fn_80167744(i, time) + 0x778, 0, 18.0f * (7 - i) + (255.0f + x1), 360.0f);
    }
    TaDrawTitle(db, e, 422.0f + x1, 364.0f);

    time = TaRecord_GetTime_Indexed(0, 1, self->course, 1, 1);
    e = TaRecord_GetEntry_Indexed(0, 1, self->course, 1, 1);
    fn_80167DDC(0, e->name, 68.0f + x1, 416.0f);
    fn_801698B4(0, fn_8013BFCC(e->chr), 0, 209.0f + x1, 412.0f);
    for (i = 0; i < 8; i++) {
        fn_801698B4(0, fn_80167744(i, time) + 0x778, 0, 18.0f * (7 - i) + (255.0f + x1), 416.0f);
    }
    TaDrawTitle(db, e, 422.0f + x1, 420.0f);

    if (!self->started) {
        self->started = 1;
    }
    fade = lbl_806D8060;
    t = self->t;
    if (t < fade) {
        self->alpha = Saturate_Double(1.0f - t / fade, 0.0f, 1.0f);
    } else if (t > 300.0f - fade) {
        self->alpha = Saturate_Double((t - (300.0f - fade)) / fade, 0.0f, 1.0f);
    } else {
        self->alpha = 0.0f;
    }
    if ((self->t += 1.0f) >= 300.0f) {
        self->state = 9;
    }
}
#pragma use_lmw_stmw reset

extern "C" unsigned char fn_80153504(StateObj *o) {
    return o->state == 9;
}

extern "C" void fn_80153518(QuadFade *self) {
    if (self->on) {
        fn_8011F994(0);
        if (self->alpha > 0.0f) {
            DrawColoredQuad(0, 0, 0, (int)(255.0f * self->alpha), 0.0f, 0.0f, 640.0f, 480.0f);
        }
    }
}

extern "C" void fn_80153594(VObj *p) {
    delete p;
}

extern "C" PalObj *fn_801535CC(PalObj *self, short flag) {
    if (self != 0) {
        self->vt = StatusNoticeScene_vtable_8048FE64;
        if (self->pal != 0) {
            TEXReleasePalette(&self->pal);
        }
        fn_80121210();
        clRom_PurgeAll();
        fn_8002CFB8(0, 0, 0, 0xFF);
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80153668(FadeTimer *o) {
    if (o->state != 9) {
        if (o->t < 30.0f) {
            o->alpha = 255.0f * Saturate_Double(o->t / 30.0f, 0.0f, 1.0f);
        } else if (o->t >= 90.0f) {
            o->alpha = 255.0f * (1.0f - Saturate_Double((o->t - 90.0f) / 28.0f, 0.0f, 1.0f));
        } else {
            o->alpha = 0xFF;
        }
        o->t += 1.0f;
        if (o->t >= 120.0f) {
            o->state = 9;
        }
    }
}

extern "C" unsigned char fn_80153758(StateObj *o) {
    return o->state == 9;
}

extern "C" void fn_8015376C(TexFadePanel *self) {
    float proj[4][4];
    float view[3][4];

    fn_801F6804(self->tlut);
    DrawColoredQuad(0xFF, 0xFF, 0xFF, 0xFF, 0.0f, 0.0f, 640.0f, 480.0f);
    GXSetZMode(0, 7, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    C_MTXOrtho(proj, -23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
    GXSetProjection(proj, 1);
    Vec3f eye = *(const Vec3f *)lbl_80366E28;
    Vec3f up = *(const Vec3f *)lbl_80366E34;
    Vec3f target = *(const Vec3f *)lbl_80366E40;
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTevOp(0, 1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXColorB color = {0xFF, 0xFF, 0xFF, self->alpha};
    GXSetChanMatColor(4, color);
    GXLoadTexObj(self->texObj, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 0, 4, 0);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    {
        float left = 117.0f;
        float top = 154.0f;
        float right = 493.0f;
        float bottom = 258.0f;
        float u0 = 0.0f;
        float u1 = 1.0f;
        GXPosition2f32(left, top);
        GXTexCoord2f32(u0, u0);
        GXPosition2f32(right, top);
        GXTexCoord2f32(u1, u0);
        GXPosition2f32(right, bottom);
        GXTexCoord2f32(u1, u1);
        GXPosition2f32(left, bottom);
        GXTexCoord2f32(u0, u1);
    }
    fn_801F6804(self->tlut);
}

extern "C" void fn_80153A3C(VObj *p) {
    delete p;
}

extern "C" PalObj *fn_80153A74(PalObj *self, short flag) {
    if (self != 0) {
        self->vt = StatusLogoScene_vtable_8048FE8C;
        if (self->pal != 0) {
            TEXReleasePalette(&self->pal);
        }
        fn_80121210();
        clRom_PurgeAll();
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80153AFC(FadeTimer *o) {
    if (o->state != 9) {
        if (o->t < 30.0f) {
            o->alpha = 255.0f * Saturate_Double(o->t / 30.0f, 0.0f, 1.0f);
        } else if (o->t >= 90.0f) {
            o->alpha = 255.0f * (1.0f - Saturate_Double((o->t - 90.0f) / 28.0f, 0.0f, 1.0f));
        } else {
            o->alpha = 0xFF;
        }
        o->t += 1.0f;
        if (o->t >= 120.0f) {
            o->state = 9;
        }
    }
}

extern "C" unsigned char fn_80153BEC(StateObj *o) {
    return o->state == 9;
}

extern "C" void fn_80153C00(TexFadePanel *self) {
    float proj[4][4];
    float view[3][4];

    fn_801F6804(self->tlut);
    DrawColoredQuad(0xFF, 0xFF, 0xFF, 0xFF, 0.0f, 0.0f, 640.0f, 480.0f);
    GXSetZMode(0, 7, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    C_MTXOrtho(proj, -23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
    GXSetProjection(proj, 1);
    Vec3f eye = *(const Vec3f *)lbl_80366E04;
    Vec3f up = *(const Vec3f *)lbl_80366E10;
    Vec3f target = *(const Vec3f *)lbl_80366E1C;
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTevOp(0, 1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXColorB color = {0xFF, 0xFF, 0xFF, self->alpha};
    GXSetChanMatColor(4, color);
    GXLoadTexObj(self->texObj, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 0, 4, 0);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    {
        float left = 117.0f;
        float top = 154.0f;
        float right = 493.0f;
        float bottom = 258.0f;
        float u0 = 0.0f;
        float u1 = 1.0f;
        GXPosition2f32(left, top);
        GXTexCoord2f32(u0, u0);
        GXPosition2f32(right, top);
        GXTexCoord2f32(u1, u0);
        GXPosition2f32(right, bottom);
        GXTexCoord2f32(u1, u1);
        GXPosition2f32(left, bottom);
        GXTexCoord2f32(u0, u1);
    }
    fn_801F6790(self->tlut);
}

extern "C" void fn_80153ED0(VObj *p) {
    delete p;
}

extern "C" CourseScene *fn_80153F08(CourseScene *self, short flag) {
    if (self != 0) {
        int i;
        self->vt = DemoScene1C0_vtable_8048FED8;
        SetCourseScene3D(0);
        if (fn_8019083C(0)) {
            fn_801909A4(0);
        }
        for (i = 0; i < 6; i++) {
            VisualEffectHolder_Dtor(self->effects[i], 1);
            KartDriver_Dtor(self->drivers[i], 1);
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        if (self->obj14 != 0) {
            Object_DtorWithGXSync(self->obj14, 1);
        }
        if (self->obj1A8 != 0) {
            delete self->obj1A8;
        }
        if (self->obj1AC != 0) {
            fn_80140810(self->obj1AC, 1);
        }
        if (self->pair != 0) {
            delete self->pair;
        }
        fn_801540E0((ObjListSetFull *)self->list, 1);
        __destroy_new_array(self->arr, dtor_800869D0);
        self->arr = 0;
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        SetResourceLoadingFlag(0);
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct ObjNode {
    ObjNode *prev;
    ObjNode *next;
    unsigned int flags;
    int pad;
    void *obj;
};

struct ObjListSetFull {
    ListHead objs;
    ListHead models;
    SetSubList sub[2];
};

extern "C" void fn_801579F0(LIter *ret, void *list, LIter *pos);
extern "C" void fn_80157BE8(void *ret, void *list, void *pos);
extern "C" void fn_801F7CD8(void *obj, int flag);

static inline void ModelsDtor1(ListHead *l) {
    if (l != 0) {
        LIter r;
        LIter b;
        LIter e;
        LNode **a = &l->f4;
        e.n = (LNode *)a;
        b.n = a[1];
        fn_80157B38(&r, l, &b, &e);
    }
}
static inline void ModelsDtor2(ListHead *l) { if (l != 0) ModelsDtor1(l); }
static inline void ModelsDtor3(ListHead *l) { if (l != 0) ModelsDtor2(l); }
static inline void ObjsDtor1(ListHead *l) {
    if (l != 0) {
        LIter r;
        LIter b;
        LIter e;
        e.n = (LNode *)&l->f4;
        b.n = l->head;
        fn_80157940(&r, l, &b, &e);
    }
}
static inline void ObjsDtor2(ListHead *l) { if (l != 0) ObjsDtor1(l); }
static inline void ObjsDtor3(ListHead *l) { if (l != 0) ObjsDtor2(l); }
extern "C" ObjListSetFull *fn_801540E0(ObjListSetFull *o, short flag) {
    if (o != 0) {
        int i;
        ObjListSetFull *c;
        for (i = 0, c = o; i < 2; i++) {
            SetSubList *l = &c->sub[0];
            l->clear();
            c = (ObjListSetFull *)((char *)c + sizeof(SetSubList));
        }
        while ((unsigned int)o->models.count != 0) {
            ObjNode *n = (ObjNode *)o->models.head;
            if (n->obj != 0) {
                fn_801F7CD8(n->obj, 1);
            }
            {
                LIter p;
                LIter r;
                p.n = o->models.head;
                fn_80157BE8(&r, &o->models, &p);
            }
        }
        while ((unsigned int)o->objs.count != 0) {
            ObjNode *n = (ObjNode *)o->objs.head;
            void *obj = n->obj;
            if (obj != 0) {
                switch (n->flags >> 29) {
                case 0:
                    Object_DtorWithGXSync(obj, 1);
                    break;
                case 1:
                    delete (VObj *)obj;
                    break;
                case 2:
                    delete (VObj *)obj;
                    break;
                case 3:
                    LObjList_Destroy(obj, 1);
                    break;
                default:
                    MemoryManager_TimedFree(obj);
                    break;
                }
            }
            {
                LIter p;
                LIter r;
                p.n = o->objs.head;
                fn_801579F0(&r, &o->objs, &p);
            }
        }
        __destroy_arr(o->sub, (void *)fn_8014E04C, 0xc, 2);
        ModelsDtor3(&o->models);
        ObjsDtor3(&o->objs);
        if (flag > 0) {
            MemoryManager_TimedFree(o);
        }
    }
    return o;
}


inline VObjPair::VObjPair() {
    int k;
    a = new PairObj(lbl_80367590, 0);
    b = new PairObj(lbl_8036759C, 0);
    started = 0;
    mode = 0;
    t = 0.0f;
    for (k = 0; k < 5; k++) {
        on[k] = 1;
        pos[k].x = ((const PairPos *)lbl_80366E4C)[k].x;
        pos[k].y = ((const PairPos *)lbl_80366E4C)[k].y;
        vel[k] = 0.0f;
    }
    aOn = 1;
    aPos = *(const PairPos *)&lbl_806D7F68;
    aVel = 0.0f;
}

inline void VObjPair::Update() {
    if (!started) {
        started = 1;
    } else {
        t += 1.0f;
    }
    if (mode == 1) {
        int i;
        for (i = 0; i < 5; i++) {
            if (on[i]) {
                if (t < lbl_80366E74[i]) {
                    scale[i].x = 0.0f;
                    scale[i].y = 0.0f;
                } else if (t < lbl_80366E74[i] + 10.0f) {
                    float s = 0.03f * Saturate_Double((t - lbl_80366E74[i]) / 3.0f, 0.0f, 1.0f);
                    scale[i].x = s;
                    scale[i].y = s;
                } else {
                    vel[i] += 0.8f;
                    pos[i].y += vel[i];
                }
                if (pos[i].y > 500.0f) {
                    on[i] = 0;
                }
            }
        }
        if (aOn) {
            if (t < 10.0f) {
                float s = 0.055f * Saturate_Double(t / 3.0f, 0.0f, 1.0f);
                aScale.x = s;
                aScale.y = s;
            } else {
                aVel += 0.5f;
                aPos.y += aVel;
                aScale.y += 0.001f;
            }
            if (aPos.y > 500.0f) {
                aOn = 0;
            }
        }
    }
}

static inline void *JObjGetMtxPtr(void *j) {
    JObjSetupMatrix(j);
    return (char *)j + 0x44;
}

static inline void SprScene_Sweep(CourseScene *self, SprNodeBase *&e) {
    SprNodeBase *n2;
    SprScene *spr = (SprScene *)self->list;
    if (spr->cache.count != 0) {
        n2 = spr->cache.end.next;
        e = &spr->cache.end;
        while (n2 != e) {
            if (((SprNode *)n2)->ref > 0) {
                ((SprNode *)n2)->ref = 0;
            } else {
                SprIter ret;
                SprIter pos;
                if (((SprNode *)n2)->res != 0) {
                    fn_801F7CD8(((SprNode *)n2)->res, 1);
                }
                pos.n = n2;
                fn_80157BE8(&ret, &spr->cache, &pos);
                n2 = ret.n;
                continue;
            }
            n2 = n2->next;
        }
    }
}

static inline void CourseScene_UpdateJoints(CourseScene *self) {
    int i;
    for (i = 0; i < 6; i++) {
        self->jobjs[i] = ResolveJointByName(self->obj20, ((char **)Scene_8014E0C4_data_8048F1A8)[i]);
        if (self->jobjs[i] != 0) {
            PSMTXCopy(JObjGetMtxPtr(self->jobjs[i]), self->mtx[i]);
            if (self->hidden[i]) {
                TornadoEffect_ClearFlagC0AndSetC4(self->effects[i], 0.0f);
                self->hidden[i] = 0;
            }
        } else if (!self->hidden[i]) {
            self->mtx[i][1][3] = -800.0f;
            TornadoEffect_SetFlagC0(self->effects[i]);
            self->hidden[i] = 1;
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80154304(CourseScene *self) {
    int i;
    SprNodeBase *e;
    unsigned int n;

    if (self->state == 9) {
        return;
    }
    if (!self->bgmOn) {
        if (ClSound_PlayBgmStream(0, 0)) {
            self->bgmOn = 1;
        }
    }
    if (!self->active) {
        self->active = 1;
        self->keyIdx = 0;
        self->keyT = 0.0f;
    } else {
        self->keyT += 1.0f;
    }
    if (self->keyT >= lbl_80366E88[self->keyIdx].time) {
        if (self->keyIdx == 9) {
            self->keyT = lbl_80366E88[self->keyIdx].time - 1.0f;
        } else {
            self->keyIdx++;
            self->keyT = 0.0f;
        }
    }
    self->cam = (SceneCam *)fn_8014E028(self->list, lbl_80366E88[self->keyIdx].id);
    self->lobjs = fn_8014E004(self->list, lbl_80366E88[self->keyIdx].id);
    self->obj20 = fn_8014DD5C(self->list, lbl_80366E88[self->keyIdx].id);
    if (self->cam != 0) {
        CamAnim_SetFrame((CourseCamAnim *)self->cam, self->keyT);
        CamAnim_Tick((CourseCamAnim *)self->cam);
    }
    if (self->obj20 != 0) {
        Object_SetField8_AndDirty(self->obj20, self->keyT);
        clNormal3D_Exec(self->obj20);
    }
    SetCourseScene3D(self->cam);
    CourseScene_UpdateJoints(self);
    for (n = 0; n < 6; n++) {
        ItemEffectBus_SnapshotAndFullReset(*(void **)((char *)self->drivers[n] + 0x304));
    }
    for (i = 0;; i++) {
        if (lbl_80364BE0[i].time < 0.0f) {
            break;
        }
            if (self->t == lbl_80364BE0[i].time) {
                if (lbl_80364BE0[i].set) {
                    ItemEffectBus_ApplyItemEventSet(*(void **)((char *)self->drivers[lbl_80364BE0[i].kart] + 0x304), lbl_80364BE0[i].item, 1);
                    TornadoEffect_ApplyItemVisual_Secondary(self->effects[lbl_80364BE0[i].kart], lbl_80364BE0[i].item, 1);
                    if (lbl_80364BE0[i].item == 50) {
                        *(float *)((char *)*(void **)((char *)self->drivers[lbl_80364BE0[i].kart] + 0x304) + 0x28) = 0.20943947f;
                    }
                } else {
                    ItemEffectBus_ApplyItemEventClear(*(void **)((char *)self->drivers[lbl_80364BE0[i].kart] + 0x304), lbl_80364BE0[i].item);
                    TornadoEffect_ApplyItemVisual_Primary(self->effects[lbl_80364BE0[i].kart], lbl_80364BE0[i].item);
                    if (lbl_80364BE0[i].item == 50) {
                        *(float *)((char *)*(void **)((char *)self->drivers[lbl_80364BE0[i].kart] + 0x304) + 0x28) = 0.0f;
                    }
                }
            }
    }
    if (1080.0f == self->t) {
        TornadoEffect_SetFlagC0(self->effects[2]);
        TornadoEffect_SetFlagC0(self->effects[4]);
        TornadoEffect_SetFlagC0(self->effects[5]);
    }
    if (1234.0f == self->t) {
        TornadoEffect_ClearFlagC0AndSetC4(self->effects[2], 1.0f);
    }
    if (1243.0f == self->t) {
        TornadoEffect_ClearFlagC0AndSetC4(self->effects[5], 1.0f);
    }
    if (1270.0f == self->t) {
        TornadoEffect_ClearFlagC0AndSetC4(self->effects[4], 1.0f);
    }
    if (1560.0f == self->t) {
        self->color = 16;
        TireEffect_ResetSpin(self->effects[3], 1.0f, 1.0f);
        TireEffect_ResetSpin(self->effects[0], 1.0f, 1.0f);
    }
    for (i = 0; i < 6; i++) {
        RenderObj_ItemStateMachine_Timed(self->drivers[i], 0, 0.0f, 0.0f);
        TornadoEffect_Tick(self->effects[i], 0);
        if (self->jobjs[i] != 0) {
            TornadoEffect_SetColorPairC8CC(self->effects[i], self->color, self->color);
        } else {
            TornadoEffect_SetColorPairC8CC(self->effects[i], 0, 0);
        }
    }
    for (n = 0; n < 6; n++) {
        ItemEffectBus_TickTornadoCooldown(*(void **)((char *)self->drivers[n] + 0x304));
    }
    for (i = 0; self->tracks[i].keys != 0; i++) {
        CourseSprKey *k = self->tracks[i].keys;
        if (!(self->t < k[0].time)) {
            int id = self->tracks[i].id;
            int flags = self->tracks[i].flags;
            int j;
            for (j = 1;; j++) {
                if (k[j].time < 0.0f) {
                    break;
                }
                if (!(self->t > k[j].time)) {
                    CourseSprKey *b = &k[j];
                    CourseSprKey *a = b - 1;
                    float f = (self->t - a->time) / (b->time - a->time);
                    fn_80154FB0((SprScene *)self->list, 0, id, flags,
                                f * (b->x - a->x) + a->x, f * (b->y - a->y) + a->y,
                                f * (b->sx - a->sx) + a->sx, f * (b->sy - a->sy) + a->sy,
                                f * (b->rot - a->rot) + a->rot, f * (b->r - a->r) + a->r,
                                f * (b->g - a->g) + a->g, f * (b->b - a->b) + a->b,
                                f * (b->a - a->a) + a->a);
                    break;
                }
            }
        }
    }
    if (self->obj1A8 != 0) {
        self->obj1A8->vC();
    }
    if (self->t >= 440.0f && self->t <= 539.0f) {
        self->on1B0 = 1;
    } else {
        self->on1B0 = 0;
    }
    if (self->on1B0) {
        fn_80140344(self->obj1AC);
    }
    if (self->t >= 1710.0f) {
        if (self->pair == 0) {
            self->pair = new VObjPair;
        }
        if (self->pair != 0) {
            if (self->pair->mode == 0) {
                self->pair->mode = 1;
            }
            self->pair->Update();
        }
    }
    if (self->t >= 1715.0f) {
        float a = Saturate_Double((self->t - 1715.0f) / 5.0f, 0.0f, 1.0f);
        switch (self->variant) {
        case 1:
            fn_80169468(0, 0x55, 0, 256.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            fn_80169468(0, 0x56, 0, 576.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            break;
        case 2:
            fn_80169468(0, 0x3A9, 0, 256.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            fn_80169468(0, 0x3AA, 0, 576.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            break;
        default:
            fn_80169468(0, 0x9C6, 0, 256.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            fn_80169468(0, 0x9C8, 0, 576.0f, 240.0f, 1.0f, 1.0f, 1.0f, a);
            fn_80169468(0, 0x582, 0, 576.0f, 130.0f, 1.0f, 1.0f, 1.0f, a);
            break;
        }
        fn_801F93EC(self->arr, 280.0f, 16.0f);
        fn_801F93D0(self->arr, 1.0f, 1.0f);
        fn_801F8A34(fn_801F8E58(), self->arr, 0);
        fn_801F93EC((char *)self->arr + 0x230, 280.0f, 32.0f);
        fn_801F93D0((char *)self->arr + 0x230, 1.0f, 1.0f);
        fn_801F8A34(fn_801F8E58(), (char *)self->arr + 0x230, 0);
    }
    {
        VfxVec eye;
        VfxVec target;
        CObj_LoadProjMatrix(self->cam, &eye);
        CObj_ApplyScissor(self->cam, &target);
        ItemObjectManager_Update();
        VfxSlotMgr_Update(eye, target);
    }
    GXDrawDone();
    SprScene_Sweep(self, e);
    self->t += 1.0f;
    {
        const float fadeLen = lbl_806D8060;
        if (self->t > 2100.0f - fadeLen) {
            self->alpha = Saturate_Double((self->t - (2100.0f - fadeLen)) / fadeLen, 0.0f, 1.0f);
        } else {
            self->alpha = 0.0f;
        }
    }
    if (self->t >= 2100.0f) {
        self->state = 9;
    }
}
#pragma use_lmw_stmw reset


struct SprDraw {
    char pad0[0x2C];
    int f2C;
    char pad30[0x98 - 0x30];
};

struct SprInst {
    void *res;
    SprDraw d;
    SprInst(void *r) {
        fn_801F7E98(&d);
        res = r;
    }
    ~SprInst();
};


static inline void SprList_PushBack(SprList *l, SprInst *h) {
    SprIter ret;
    SprIter pos;
    pos.n = &l->end;
    fn_80157DE0(&ret, l, &pos, h);
}

#pragma defer_codegen on
SprInst::~SprInst() {}

#pragma use_lmw_stmw on
void SprScene::Draw(unsigned int layer, unsigned int id, unsigned int flags, float x, float y, float sx, float sy, float rot, float r, float g, float b, float a) {
    float hw;
    float hh;
    void *res;
    SprEntry *e;

    if (layer >= 2) {
        return;
    }
    if (id >= 80) {
        return;
    }
    hw = sx * (0.5f * Scene_8014E0C4_rodata_803644D0[id].w);
    hh = sy * (0.5f * Scene_8014E0C4_rodata_803644D0[id].h);
    if (rot != 0.0f) {
        float s = LookupSin(rot);
        float c = LookupCos(rot);
        float t = hw;
        if (s < 0.0f) {
            s = -s;
        }
        if (c < 0.0f) {
            c = -c;
        }
        hw = hw * c + hh * s;
        hh = t * s + hh * c;
    }
    /* original code tests x + hw twice (probable typo for y + hh); the target compares it twice */
    if (x - hw > 640.0f || x + hw < 0.0f || y - hh > 480.0f || x + hw < 0.0f) {
        return;
    }
    e = (SprEntry *)&Scene_8014E0C4_rodata_803644D0[id];
    res = SprCache_Get(&cache, e->key);
    if (res == 0) {
        return;
    }
    SprInst inst(res);
    fn_801F7344(res, &inst.d);
    fn_801F7198(inst.res, &inst.d, 0);
    fn_801F6D58(&inst.d, e->name, 0, 0);
    fn_801F70F0(&inst.d, x, y, 1.0f);
    fn_801F6ED0(&inst.d, sx, sy);
    fn_801F6EEC(&inst.d, rot);
    fn_801F6EAC(&inst.d, (int)(255.0f * r), (int)(255.0f * g), (int)(255.0f * b), (int)(255.0f * a));
    if (flags & 1) {
        fn_801F6E84(&inst.d, 4, 1);
    }
    if (flags & 2) {
        inst.d.f2C = 1;
    }
    SprList_PushBack(&layers[layer], &inst);
}
#pragma use_lmw_stmw reset
#pragma defer_codegen off

extern "C" unsigned char fn_80155398(StateObj *o) {
    return o->state8 == 9;
}

#pragma use_lmw_stmw on
extern "C" void fn_801553AC(CourseScene *self) {
    if (self->active && self->cam->Begin()) {
        int j;
        LObjList_ApplyForCObj(self->lobjs);
        CObj_DebugVizPathFlush(self->cam);
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        Object_RenderJObjTree(self->obj14, 7);
        for (j = 0; j < 6; j++) {
            if (self->jobjs[j] != 0) {
                HSD_JObjClearFlagsAll(self->jobjs[j], 0x10);
                KartItem_DispatchEffectRenderByState(self->effects[j]);
                HSD_JObjDispAll(self->jobjs[j], 0, 7, 0);
                KartItem_FlushPendingRender_v2(self->effects[j]);
                TornadoEffect_SubmitRender(self->effects[j]);
                HSD_JObjSetFlagsAll(self->jobjs[j], 0x10);
            }
        }
        Object_RenderJObjTree(self->obj20, 7);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        if (self->obj1A8 != 0) {
            self->obj1A8->Draw();
        }
        self->cam->End();
    }
    if (self->on1B0) {
        fn_8014017C(self->obj1AC);
    }
    fn_8011F994(0);
    self->list->FlushAll();
    if (self->pair != 0) {
        self->pair->Draw();
    }
    if (self->alpha > 0.0f) {
        DrawColoredQuad(0, 0, 0, (int)(255.0f * self->alpha), 0.0f, 0.0f, 640.0f, 480.0f);
    }
}
#pragma use_lmw_stmw reset

extern "C" Base *fn_801556A0(Base *self, short flag) {
    if (self != 0) {
        self->vt = DemoKart_vtable_8048FF20;
        VisualEffectHolder_Dtor(((void **)self)[4], 1);
        KartDriver_Dtor(((void **)self)[3], 1);
        dtor_80060024(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" int fn_8015571C(char *o, float *a, float *b, float *c) {
    *a = *(float *)(o + 0x1C);
    *b = *(float *)(o + 0x2C);
    *c = *(float *)(o + 0x3C);
    return 1;
}

extern "C" void fn_8015573C(VObj *p) {
    delete p;
}

extern "C" CoursePanel *fn_80155774(CoursePanel *self, short flag) {
    if (self != 0) {
        int i;
        self->vt = DemoScene_vtable_8048FF3C;
        SetCourseScene3D(0);
        fn_80173CC4(self->obj48, 1);
        for (i = 0; i < 2; i++) {
            delete self->objs[i];
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        if (self->obj14 != 0) {
            Object_DtorWithGXSync(self->obj14, 1);
        }
        fn_801540E0((ObjListSetFull *)self->obj4C, 1);
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        fn_8013A6F8();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        SetResourceLoadingFlag(0);
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline void VObjD_SetMtx(VObjD *o, void *m) {
    PSMTXCopy(m, o->mtx);
    o->pos[0] = o->mtx[0][3];
    o->pos[1] = o->mtx[1][3];
    o->pos[2] = o->mtx[2][3];
}

#define SPR ((SprScene *)self->obj4C)

static inline void CourseDraw(CoursePanel *self, unsigned int id, unsigned int flags, float x, float y, float a) {
    SPR->Draw(0, id, flags, x, y, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, a);
}

#pragma use_lmw_stmw on
extern "C" void fn_801558CC(CoursePanel *self) {
    int i;
    unsigned int n;
    void *jobj;
    SprNodeBase *e;
    SprScene *spr;
    SprNodeBase *n2;
    float t;
    float fade;
    float s;

    if (self->state == 9) {
        return;
    }
    if (!self->active) {
        self->active = 1;
    }
    if (self->t < 300.0f) {
        self->phase = 10;
        self->phaseT = self->t;
    } else if (self->t < 600.0f) {
        self->phase = 11;
        self->phaseT = self->t - 300.0f;
    } else {
        self->phase = 12;
        self->phaseT = self->t - 600.0f;
        if (self->phaseT >= 300.0f) {
            self->phaseT = 299.0f;
        }
    }
    self->cam = (SceneCam *)fn_8014E028(self->obj4C, self->phase);
    self->lobjs = fn_8014E004(self->obj4C, self->phase);
    self->obj20 = fn_8014DD5C(self->obj4C, self->phase);

    if (self->cam != 0) {
        CamAnim_SetFrame((CourseCamAnim *)self->cam, self->phaseT);
        CamAnim_Tick((CourseCamAnim *)self->cam);
    }
    if (self->obj20 != 0) {
        Object_SetField8_AndDirty(self->obj20, self->phaseT);
        clNormal3D_Exec(self->obj20);
    }
    SetCourseScene3D(self->cam);

    for (i = 0; i < 2; i++) {
        ItemEffectBus_SnapshotAndFullReset(*(void **)((char *)self->objs[i]->robj + 0x304));
        self->jobjs[i] = ResolveJointByName(self->obj20, ((char **)Scene_8014E0C4_data_806CF828)[i]);
        jobj = self->jobjs[i];
        if (jobj != 0) {
            JObjSetupMatrix(jobj);
            VObjD_SetMtx(self->objs[i], (char *)jobj + 0x44);
            if (self->hidden[i]) {
                TornadoEffect_ClearFlagC0AndSetC4(self->objs[i]->effect, 0.0f);
                TireEffect_ResetSpin(self->objs[i]->effect, 0.0f, 1.0f);
                self->hidden[i] = 0;
            }
        } else if (!self->hidden[i]) {
            float m[3][4];
            PSMTXTrans(m, 0.0f, -800.0f, 0.0f);
            VObjD_SetMtx(self->objs[i], m);
            TornadoEffect_SetFlagC0(self->objs[i]->effect);
            self->hidden[i] = 1;
        }
        RenderObj_ItemStateMachine_Timed(self->objs[i]->robj, 0, 0.0f, 0.0f);
        TornadoEffect_Tick(self->objs[i]->effect, 0);
        ItemEffectBus_TickTornadoCooldown(*(void **)((char *)self->objs[i]->robj + 0x304));
    }

    t = self->t;
    if (t >= 300.0f && t < 600.0f) {
        if (300.0f == t) {
            fn_80173B68(self->obj48, self->objs[1]->robj);
            fn_80173C34(self->obj48);
        }
        if (550.0f == self->t) {
            fn_80173BE8(self->obj48);
        }
        fn_801737F0(self->obj48);
    }

    t = self->t;
    if (t >= 70.0f && t < 230.0f) {
        if (t < 100.0f) {
            fade = (t - 70.0f) / 30.0f;
        } else if (t >= 200.0f) {
            fade = 1.0f - (t - 200.0f) / 30.0f;
        } else {
            fade = 1.0f;
        }
        s = LUT_Sin12Bit(4.5f * (t - 70.0f));
        if (s < 0.0f) {
            s = -s;
        }
        if (self->mode == 1) {
            CourseDraw(self, 0x46, 0, 169.5f, 121.5f, fade);
            CourseDraw(self, 0x47, 0, 208.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 240.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 272.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 304.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 336.0f, 129.5f, fade);
            CourseDraw(self, 0x48, 0, 372.0f, 129.5f, fade);
            CourseDraw(self, 0x44, 0, 272.0f, 132.0f, fade);
            CourseDraw(self, 0x49, 0, 281.5f, 207.5f, fade);
            CourseDraw(self, 0x4A, 1, 313.0f, 239.0f, fade * s);
        } else {
            CourseDraw(self, 0x1C, 0, 169.5f, 121.5f, fade);
            CourseDraw(self, 0x1D, 0, 208.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 240.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 272.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 304.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 336.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 368.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 400.0f, 129.5f, fade);
            CourseDraw(self, 0x1E, 0, 436.0f, 129.5f, fade);
            CourseDraw(self, 0x1A, 0, 310.0f, 132.0f, fade);
            CourseDraw(self, 0x1F, 0, 281.5f, 207.5f, fade);
            CourseDraw(self, 0x20, 1, 313.0f, 239.0f, fade * s);
        }
    }

    t = self->t;
    if (t >= 370.0f && t < 530.0f) {
        if (t < 400.0f) {
            fade = (t - 370.0f) / 30.0f;
        } else if (t >= 500.0f) {
            fade = 1.0f - (t - 500.0f) / 30.0f;
        } else {
            fade = 1.0f;
        }
        n = (unsigned int)(t - 370.0f) % 9;
        if (n >= 5) {
            n = 9 - n;
        }
        if (self->mode == 1) {
            CourseDraw(self, 0x46, 0, 169.5f, 111.5f, fade);
            CourseDraw(self, 0x47, 0, 208.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 240.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 272.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 304.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 336.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 368.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 400.0f, 119.5f, fade);
            CourseDraw(self, 0x47, 0, 432.0f, 119.5f, fade);
            CourseDraw(self, 0x48, 0, 468.0f, 119.5f, fade);
            CourseDraw(self, 0x45, 0, 364.0f, 122.0f, fade);
            CourseDraw(self, n + 0x3E, 0, 213.0f, 121.0f, fade);
        } else {
            CourseDraw(self, 0x1C, 0, 169.5f, 111.5f, fade);
            CourseDraw(self, 0x1D, 0, 208.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 240.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 272.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 304.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 336.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 368.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 400.0f, 119.5f, fade);
            CourseDraw(self, 0x1D, 0, 432.0f, 119.5f, fade);
            CourseDraw(self, 0x1E, 0, 468.0f, 119.5f, fade);
            CourseDraw(self, 0x1B, 0, 364.0f, 122.0f, fade);
            CourseDraw(self, n + 0x14, 0, 213.0f, 121.0f, fade);
        }
    }

    t = self->t;
    if (t >= 670.0f && t < 830.0f) {
        if (t < 700.0f) {
            fade = (t - 670.0f) / 30.0f;
        } else if (t >= 800.0f) {
            fade = 1.0f - (t - 800.0f) / 30.0f;
        } else {
            fade = 1.0f;
        }
        s = LUT_Sin12Bit(4.5f * (t - 670.0f));
        if (s < 0.0f) {
            s = -s;
        }
        if (self->mode == 1) {
            CourseDraw(self, 0x46, 0, 209.5f, 121.5f, fade);
            CourseDraw(self, 0x47, 0, 248.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 280.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 312.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 344.0f, 129.5f, fade);
            CourseDraw(self, 0x47, 0, 376.0f, 129.5f, fade);
            CourseDraw(self, 0x48, 0, 412.0f, 129.5f, fade);
            CourseDraw(self, 0x43, 0, 312.5f, 132.0f, fade);
            CourseDraw(self, 0x49, 0, 281.5f, 207.5f, fade);
            CourseDraw(self, 0x4A, 1, 313.0f, 239.0f, fade * s);
        } else {
            CourseDraw(self, 0x1C, 0, 209.5f, 121.5f, fade);
            CourseDraw(self, 0x1D, 0, 248.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 280.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 312.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 344.0f, 129.5f, fade);
            CourseDraw(self, 0x1D, 0, 376.0f, 129.5f, fade);
            CourseDraw(self, 0x1E, 0, 412.0f, 129.5f, fade);
            CourseDraw(self, 0x19, 0, 313.0f, 132.0f, fade);
            CourseDraw(self, 0x1F, 0, 281.5f, 207.5f, fade);
            CourseDraw(self, 0x20, 1, 313.0f, 239.0f, fade * s);
        }
    }

    if (self->mode == 1) {
        CourseDraw(self, 0x4B, 0, 506.0f, 400.0f, 1.0f);
        if (self->blink >= 30.0f) {
            CourseDraw(self, 0x4C, 0, 532.0f, 401.0f, 1.0f);
        }
    } else if (self->blink < 30.0f) {
        CourseDraw(self, 0x21, 0, 533.5f, 400.0f, 1.0f);
    } else {
        CourseDraw(self, 0x22, 0, 533.5f, 400.0f, 1.0f);
    }
    if ((self->blink += 1.0f) >= 60.0f) {
        self->blink = 0.0f;
    }

    if (self->t < 300.0f) {
        clItemBoxManager_Update(SINGLETON_INSTANCE(lbl_806D10D0));
    }
    if (self->t >= 600.0f) {
        fn_8013A534();
    }
    {
        VfxVec eye;
        VfxVec target;
        CObj_LoadProjMatrix(self->cam, &eye);
        CObj_ApplyScissor(self->cam, &target);
        ItemObjectManager_Update();
        VfxSlotMgr_Update(eye, target);
    }
    GXDrawDone();
    {
        spr = SPR;
        if (spr->cache.count != 0) {
            e = &spr->cache.end;
            n2 = spr->cache.end.next;
            while (n2 != e) {
                if (((SprNode *)n2)->ref > 0) {
                    ((SprNode *)n2)->ref = 0;
                } else {
                    SprIter pos;
                    SprIter ret;
                    if (((SprNode *)n2)->res != 0) {
                        fn_801F7CD8(((SprNode *)n2)->res, 1);
                    }
                    pos.n = n2;
                    fn_80157BE8(&ret, &spr->cache, &pos);
                    n2 = ret.n;
                    continue;
                }
                n2 = n2->next;
            }
        }
    }
    {
        const float fadeLen = lbl_806D8060;
        if (self->t < fadeLen) {
            self->alpha = Saturate_Double(1.0f - self->t / fadeLen, 0.0f, 1.0f);
        } else if (self->t > 900.0f - fadeLen) {
            self->alpha = Saturate_Double((self->t - (900.0f - fadeLen)) / fadeLen, 0.0f, 1.0f);
        } else {
            self->alpha = 0.0f;
        }
    }
    self->t += 1.0f;
    if (self->t >= 900.0f) {
        self->state = 9;
    }
}
#pragma use_lmw_stmw reset

extern "C" unsigned char fn_80156FC0(StateObj *o) {
    return o->state == 9;
}

#pragma use_lmw_stmw on
extern "C" void fn_80156FD4(CoursePanel *self) {
    if (self->active && self->cam != 0) {
    if (self->cam->Begin()) {
        int j;
        LObjList_ApplyForCObj(self->lobjs);
        CObj_DebugVizPathFlush(self->cam);
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        Object_RenderJObjTree(self->obj14, 7);
        for (j = 0; j < 2; j++) {
            if (self->jobjs[j] != 0) {
                HSD_JObjClearFlagsAll(self->jobjs[j], 0x10);
                KartItem_DispatchEffectRenderByState(self->objs[j]->effect);
                HSD_JObjDispAll(self->jobjs[j], 0, 7, 0);
                KartItem_FlushPendingRender_v2(self->objs[j]->effect);
                TornadoEffect_SubmitRender(self->objs[j]->effect);
                HSD_JObjSetFlagsAll(self->jobjs[j], 0x10);
            }
        }
        Object_RenderJObjTree(self->obj20, 7);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        if (self->t < 300.0f) {
            clItemBoxManager_Draw(SINGLETON_INSTANCE(lbl_806D10D0));
        }
        if (self->t >= 600.0f) {
            fn_80139810();
        }
        if (self->t >= 300.0f && self->t < 600.0f) {
            fn_801737CC(self->obj48);
        }
        self->cam->End();
    }
    self->obj4C->FlushAll();
    if (self->alpha > 0.0f) {
        DrawColoredQuad(0, 0, 0, (int)(255.0f * self->alpha), 0.0f, 0.0f, 640.0f, 480.0f);
    }
    }
}
#pragma use_lmw_stmw reset

extern "C" void fn_80157240(VObj *p) {
    delete p;
}

extern "C" CamPanel *fn_80157278(CamPanel *self, short flag) {
    if (self != 0) {
        NamCamObj *cam;
        self->vt = AttractScene_vtable_8048FF64;
        if (self->cam != 0) {
            cam = self->cam;
            if (GetVBlankFlag() && cam->active) {
                cam->active = 0;
                NamCam_End();
            }
            cam = self->cam;
            if (cam != 0) {
                MemoryManager_Free(cam->buf);
                if (GetVBlankFlag()) {
                    if (GetVBlankFlag() && cam->active) {
                        cam->active = 0;
                        NamCam_End();
                    }
                    cam->buf = 0;
                }
                MemoryManager_TimedFree(cam);
            }
        }
        fn_80121210();
        clRom_PurgeAll();
        if (self != 0) {
            self->vt = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80157378(NamCamPanel *self) {
    float x;
    float y1;
    float y2;
    float u;
    float fade;
    NamCamObj *cam;
    char info[4];
    void *handle;

    if (self->state == 9) {
        return;
    }
    if (self->scroll <= 149.0f) {
        x = 317.0f - 438.0f * (self->scroll / 149.0f);
    } else {
        x = 758.0f - 438.0f * ((self->scroll - 150.0f) / 149.0f);
    }
    u = self->scroll / 299.0f;
    y1 = 758.0f - 879.0f * u;
    y2 = 876.0f - 1120.0f * u;
    if (self->mode == 1) {
        fn_801698B4(0, 0x72, 0, 320.0f, 240.0f);
        fn_801698B4(0, 0x71, 1, x, 95.0f);
        fn_801698B4(0, 0x71, 1, y1, 288.0f);
        fn_801696E4(0, 0x70, 0, y2, 411.0f, -1.570796f);
    } else {
        fn_801698B4(0, 0x9, 0, 320.0f, 240.0f);
        fn_801698B4(0, 0x8, 1, x, 95.0f);
        fn_801698B4(0, 0x8, 1, y1, 288.0f);
        fn_801696E4(0, 0x7, 0, y2, 411.0f, -1.570796f);
    }
    fn_801697C0(1, 0x55C, 0, 320.0f, 144.0f, 0.75f, 0.75f);
    if (self->logo) {
        fn_801698B4(1, 0x50D, 0, 320.0f, 160.0f);
    }
    cam = self->cam;
    if (cam != 0 && GetVBlankFlag() && cam->active) {
        if (NamCam_GetImageHandle(&handle, 0) == 1) {
            NamCam_LoadImage(handle, cam->buf, info);
            cam->loaded = 1;
        }
    }
    self->scroll += 1.0f;
    if (self->scroll >= 300.0f) {
        self->scroll = 0.0f;
    }
    fade = lbl_806D8060;
    switch (self->state) {
    case 0:
        self->t += 1.0f;
        if (self->t < fade) {
            self->alpha = Saturate_Double(1.0f - self->t / fade, 0.0f, 1.0f);
        } else {
            self->alpha = 0.0f;
        }
        if (self->t >= 600.0f) {
            SetSyncTarget(5);
            self->state = 1;
            self->t = 0.0f;
        }
        break;
    case 1:
        self->alpha = 0.0f;
        if (PcbSync_AllKartsInValidSelectState()) {
            self->state = 2;
            self->t = 0.0f;
        }
        break;
    case 2:
        self->t += 1.0f;
        self->alpha = Saturate_Double(self->t / fade, 0.0f, 1.0f);
        if (self->t >= fade) {
            self->state = 9;
        }
        break;
    }
}

extern "C" unsigned char fn_801576D8(StateObj *o) {
    return o->state == 9;
}

extern "C" void fn_801576EC(FadeHolder2 *self) {
    fn_8011F994(0);
    if (self->fade != 0) {
        FlashFadeOverlay_Draw(self->fade, 145.0f, 20.0f, 465.0f, 260.0f, (float)lbl_80598A60[0x13], (float)lbl_80598A60[0x12]);
    }
    fn_8011F994(1);
    if (self->alpha > 0.0f) {
        DrawColoredQuad(0, 0, 0, (int)(255.0f * self->alpha), 0.0f, 0.0f, 640.0f, 480.0f);
    }
}

extern "C" void fn_801577C4(void) {
}

extern "C" int fn_801577C8(void) {
    return 1;
}

extern "C" void fn_801577D0(void) {
}

extern "C" Base *dtor_801577D4(Base *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FF80;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_8015781C(void) {
}

extern "C" void *fn_80157820(void *l) {
    fn_80157EA8(l);
    return l;
}

extern "C" ListHead *dtor_80157850(ListHead *self, short flag) {
    if (self != 0) {
        if (self != 0) {
            if (self != 0) {
                LIter e;
                LIter b;
                LIter r;
                e.n = (LNode *)&self->f4;
                b.n = self->head;
                fn_80157B38(&r, self, &b, &e);
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" ListHead *dtor_801578C8(ListHead *self, short flag) {
    if (self != 0) {
        if (self != 0) {
            if (self != 0) {
                LIter e;
                LIter b;
                LIter r;
                e.n = (LNode *)&self->f4;
                b.n = self->head;
                fn_80157940(&r, self, &b, &e);
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}


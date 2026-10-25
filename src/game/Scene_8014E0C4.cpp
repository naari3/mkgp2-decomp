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

struct CoursePanel {
    void *vt;
    char pad4[0x10];
    void *obj14;
    char pad18[0x1C];
    VObjD *objs[2];
    char pad3C[0xC];
    void *obj48;
    void *obj4C;
};


struct NamCamObj {
    unsigned char active;
    char pad1[3];
    void *buf;
};

struct CamPanel {
    void *vt;
    char pad4[0xC];
    NamCamObj *cam;
    char pad14[0xC];
    void *sprA;
    void *sprB;
};

struct GXColorB {
    unsigned char r, g, b, a;
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
struct LIter {
    LNode *n;
};

struct ListHead {
    int count;
    LNode *f4;
    LNode *head;
};

struct FadeHolder {
    char pad0[0x10];
    void *fade;
};

struct QuadFade {
    char pad0[0xC];
    float alpha;
    unsigned char on;
};


class VObj {
public:
    virtual ~VObj();
};

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
extern void FUN_8003b120();
extern void ItemObjectManager_Init();
extern void KartDriver_Init();
extern void KartDriver_New_Empty();
void MemoryManager_Free(void *p);
extern void Object_ReleaseAnimResource();
extern void PSMTXIdentity();
extern void PreloadEffectResources();
extern void PreloadItemResources();
extern void ResolveJointByName();
void SetResourceLoadingFlag(int on);
extern void SoundChannels_ClearAll();
extern void TexMgr_SetTexture();
extern void TornadoEffect_Ctor();
extern void TornadoEffect_SetFlagC0();
extern void __construct_array();
extern void __construct_new_array();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
void fn_80121210(void);
extern void fn_8013D800();
extern void fn_80140874();
extern void fn_8014DD5C();
extern void fn_8014E004();
extern void fn_8014E028();
extern void fn_80157B20();
extern void fn_80157D18();
extern void fn_80169E10();
extern void fn_80169E20();
extern void fn_80171CD0();
extern void fn_80293BBC();
extern void isJapanese();
extern unsigned int g_kartStartSlot;
extern unsigned int lbl_806D7F68;
extern unsigned int lbl_806D8064;
extern unsigned int lbl_806D8068;
extern unsigned int lbl_806D8070;
extern unsigned int lbl_806D8074;
extern unsigned int lbl_806D8078;
extern unsigned int lbl_806D807C;
extern unsigned int lbl_806D8080;
extern unsigned int dtor_800869D0[];
extern unsigned int fn_80149214[];
extern unsigned int fn_8014E04C[];
extern char lbl_80363D30[];
extern unsigned int lbl_8048FED8[];
extern unsigned int lbl_8048FF80[];
extern void CreditMgr_DrawCoinCreditBanner();
extern void HSD_StateInvalidate();
extern void IsCardValid();
extern void LUT_Sin12Bit();
extern void PcbSync_CountJoinedPcbsAdvancedKarts();
float Saturate_Double(float x, float lo, float hi);
extern void Sci2Card_GetReceiptTestFlag();
extern void ServiceEnable_Get();
extern void ServiceMode_UpdateScheduleGate();
extern void ServiceValue_Get();
extern void __cvt_fp2unsigned();
void fn_8011F994(int layer);
extern void fn_80169334();
extern unsigned int lbl_806D8084;
extern unsigned int lbl_806D8088;
extern unsigned int lbl_806D808C;
extern unsigned int lbl_806D8090;
extern unsigned int lbl_806D8094;
extern unsigned int lbl_80367488[];
int CreditMgr_GetCreditCount(int slot);
void GXDrawDone(void);
unsigned char GetVBlankFlag(void);
void NamCam_End(void);
extern void NamCam_Init();
extern void OperationClock_Commit();
extern void RaceFlow_ResetState_FullColdInit();
extern void RumbleUpdate();
extern void SetCourseParams();
extern void SetSyncTarget();
extern void Sprite_InitWithAnim();
extern void StrPcb_GetInstance();
extern void StrPcb_ResetCommands_NeutralDefault();
extern void StrPcb_ResetCommands_Zero();
extern void TEXBindPaletteEntry_RGB();
extern void TEXLoadPalette_Retry();
extern void TitleTracker_OnAttract_Stub();
extern void VBlankValue_Get();
void fn_8002CFB8(int a, int b, int c, int d);
extern void fn_8014D848();
extern void fn_80163614();
void fn_801699D8(int a, int b);
extern void fn_8019FEF4();
void fn_801B7CD0(int a);
extern void fn_801F6804();
extern unsigned int g_cupId;
extern unsigned int g_currentSceneState;
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D12E1;
extern unsigned int jumptable_8048FDCC[];
extern unsigned int lbl_8048FE14[];
extern unsigned int lbl_8048FE3C[];
extern unsigned int lbl_8048FE64[];
extern unsigned int lbl_8048FE8C[];
extern unsigned int lbl_8048FF64[];
extern void dtor_80080330();
unsigned char Sprite_AdvanceAnim(void *s, float dt);
extern unsigned int lbl_806D8060;
extern unsigned int lbl_806D8098;
extern unsigned int lbl_806D80A0;
void CreditMgr_SetActiveSlot(int slot);
void clRom_PurgeAll(void);
void fn_80120A08(int id);
void fn_80169C44(void);
void fn_801933D0(int a);
extern struct StatusInfo *lbl_806D1580;
extern unsigned int lbl_803FE0C8[];
extern unsigned int lbl_8048FD98[];
extern void InitRumbleController();
extern void PreloadResource();
extern void SetLocalPcbRole();
extern unsigned int g_pInputState;
extern unsigned int lbl_806D117C;
extern unsigned int lbl_806D12B0;
extern unsigned int lbl_806D12E2;
extern int lbl_80598A60[];
extern void dtor_8007D0D4();
void OverlayText(int a, int b, int line, const char *fmt, ...);
extern const char *lbl_8048FD50[];
void Sprite_Destroy(void *s, int flag);
extern unsigned int lbl_8048FFC0[];
void FlashFadeOverlay_Draw(void *h, float a, float b, float c, float d, float e, float f);
extern unsigned int lbl_806D80A8;
extern unsigned int lbl_806D80AC;
extern unsigned int lbl_806D80B0;
extern unsigned int lbl_806D80B4;
extern void NamCam_GetImageHandle();
extern void NamCam_LoadImage();
extern void PcbSync_AllKartsInValidSelectState();
extern void ResCtrl_Init();
void fn_8011FAFC(struct ResCtrl *c, int layer);
extern void fn_80121E10();
extern void fn_801698B4();
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
extern unsigned int lbl_8048FFE8[];
void fn_8011FAB8(void);
void fn_801F8A34(void *a, void *b, int c);
void *fn_801F8E58(void);
void fn_801F93D0(void *t, float sx, float sy);
void fn_801F93EC(void *t, float x, float y);
extern unsigned int lbl_806D80FC;
extern unsigned int lbl_806D8100;
extern unsigned int lbl_806D8104;
extern unsigned int lbl_806D8108;
extern void HSD_CObjAddAnim();
extern void HSD_CObjAnim();
extern void HSD_CObjReqAnim();
extern void JObj_Hide();
extern void Scene3D_Init();
extern void SceneModel_Init();
extern void clNormal3D_Exec();
extern unsigned int lbl_806D806C;
extern unsigned int lbl_80419EF8[];
extern void CourseEnvironment_Dtor();
void KartDriver_Dtor(void *p, int flag);
extern void SetActiveCamera();
extern void TireEffect_ResetSpin();
void VisualEffectHolder_Dtor(void *p, int flag);
extern void fn_8013D4B0();
extern void fn_8013D738();
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceCamera;
void ClRomTable_PurgeAll(void);
void ItemObjectManager_Reset(void);
extern void LObjList_Destroy();
void Object_DtorWithGXSync(void *o, int flag);
extern void SceneDrawList_Reset();
void SetCourseScene3D(void *s);
void VfxSlotMgr_Shutdown(void);
extern void fn_8013DB9C();
extern void fn_8019083C();
extern void fn_801909A4();
extern struct VObj *lbl_806D10AC;
extern unsigned int lbl_80490010[];
extern void CObj_DebugVizPathFlush();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void HSD_LObjDeleteCurrentAll();
extern void ItemObjectManager_Render();
extern void KartDriver_RenderTimed();
extern void KartItem_DispatchEffectRenderByState();
extern void KartItem_FlushPendingRender();
extern void KartItem_FlushPendingRender_v2();
extern void KartItem_FlushRenderIfReady();
extern void LObjList_ApplyForCObj();
extern void Object_RenderJObjTree();
extern void Subsystem36c_DispatchPass2_Timed();
extern void TornadoEffect_SubmitRender();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8013D940();
void fn_801695E0(int layer, int id, int c, float x, float y, float s);
extern void fn_802BD6AC();
extern void fn_802BD6C0();
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
extern unsigned int lbl_80366EF0[];
extern void BuildOrientationFromYaw();
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void ClSound_PlayBgmStream();
extern void ClStream_IsActive();
extern void ClStream_PlayMono();
extern void ClStream_Stop();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DrawEffect_SpawnByType();
extern void HSD_JObjSetupMatrixSub();
extern void ItemEffectBus_SnapshotAndFullReset();
extern void ItemEffectBus_TickTornadoCooldown();
extern void ItemObjectManager_Update();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_TickAction_79268_AndSetSlot5aEulerZ();
extern void Mtx44_GetPitchOfPosZ_Padded();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_GetYawOfPosZ_Padded();
extern void Object_SetField8_AndDirty();
extern void PSMTXCopy();
extern void PcbSyncTable_Ptr();
extern void RenderObj_ItemStateMachine_Timed();
extern void SceneRender_SetViewportRect();
extern void TornadoEffect_SetColorPairC8CC();
extern void TornadoEffect_SetFlagB4();
extern void TornadoEffect_SetScalePairB0BC();
extern void TornadoEffect_Tick();
extern void Vec3_Copy();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void clStream_setVolume();
extern void fn_800D3184();
extern void fn_8013D59C();
extern void fn_8013D608();
extern void fn_8013D634();
extern void fn_8013D660();
extern void fn_8013D704();
extern void fn_8013DAC8();
extern void fn_80194AE0();
extern void fn_801B3A50();
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
extern unsigned int lbl_806D8180;
extern unsigned int lbl_80419FB8[];
extern void Camera_Create();
extern void DMAChannelManager_Init();
extern void FileLoader_Open();
extern void GetCourseDataPtr();
extern void HSD_LObjLoadDesc();
extern void InputManager_Init();
extern void fn_8013DBF8();
extern unsigned int g_courseVariantIdx;
extern unsigned int g_longRoundFlag;
extern unsigned int lbl_806D80C0;
extern unsigned int lbl_806D8184;
extern unsigned int lbl_80367200[];
extern unsigned int lbl_8041BC00[];
extern unsigned int lbl_8048F178[];
extern void C_MTXLookAt();
extern void C_MTXOrtho();
extern void GXBegin();
extern void GXClearVtxDesc();
extern void GXLoadPosMtxImm();
extern void GXSetBlendMode();
extern void GXSetChanCtrl();
extern void GXSetChanMatColor();
extern void GXSetCurrentMtx();
extern void GXSetNumChans();
extern void GXSetNumTevStages();
extern void GXSetNumTexGens();
extern void GXSetProjection();
extern void GXSetScissor();
extern void GXSetTevOp();
extern void GXSetTevOrder();
extern void GXSetViewport();
extern void GXSetVtxAttrFmt();
extern void GXSetVtxDesc();
extern void GXSetZCompLoc();
extern void GXSetZMode();
extern unsigned int lbl_806DCF38;
extern unsigned int lbl_806D8188;
extern void TaRecord_GetEntry_Indexed();
extern void TaRecord_GetTime_Indexed();
extern void fn_8013BFCC();
extern void fn_80167744();
extern void fn_80167DDC();
extern void fn_80168910();
extern void fn_80168A4C();
extern void get_title_name();
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
extern unsigned int lbl_803677B0[];
extern unsigned int lbl_803677C8[];
void TEXReleasePalette(void **pal);
extern unsigned int lbl_806D8224;
extern void GXLoadTexObj();
extern void GXSetTexCoordGen2();
extern unsigned int lbl_806D7F64;
extern unsigned int lbl_806D8228;
extern unsigned int lbl_806D822C;
extern unsigned int lbl_806D8230;
extern unsigned int lbl_806D8234;
extern unsigned int lbl_806D8238;
extern unsigned int lbl_806D823C;
extern unsigned int lbl_806D8240;
extern unsigned int lbl_806D8244;
extern void fn_801F6790();
extern unsigned int lbl_806D7F60;
extern void fn_80140810();
extern void __destroy_arr();
void fn_80157940(struct LIter *ret, void *list, struct LIter *b, struct LIter *e);
extern void fn_801579F0();
void fn_80157B38(struct LIter *ret, void *list, struct LIter *b, struct LIter *e);
extern void fn_80157BE8();
extern void fn_80157D30();
extern void fn_801F7CD8();
extern void ItemEffectBus_ApplyItemEventClear();
extern void ItemEffectBus_ApplyItemEventSet();
extern void TornadoEffect_ApplyItemVisual_Primary();
extern void TornadoEffect_ApplyItemVisual_Secondary();
extern void TornadoEffect_ClearFlagC0AndSetC4();
extern void fn_80140344();
extern void fn_80169468();
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
extern unsigned int lbl_8048F1A8[];
extern void LookupCos();
extern void LookupSin();
extern void fn_80157C60();
extern void fn_80157DE0();
extern void fn_801F6D58();
extern void fn_801F6E84();
extern void fn_801F6EAC();
extern void fn_801F6ED0();
extern void fn_801F6EEC();
extern void fn_801F70F0();
extern void fn_801F7198();
extern void fn_801F7344();
extern void fn_801F7D50();
extern void fn_801F7E98();
extern unsigned int lbl_803644D0[];
extern void GX_BeginDraw();
extern void GX_EndDraw();
extern void HSD_JObjClearFlagsAll();
extern void HSD_JObjDispAll();
extern void HSD_JObjSetFlagsAll();
extern void fn_8014017C();
extern void fn_801F7B74();
void dtor_80060024(void *p, int flag);
extern unsigned int lbl_8048FF20[];
void fn_8013A6F8(void);
void fn_80173CC4(void *o, int flag);
extern VObj *lbl_806D10D0;
extern unsigned int lbl_8048FF3C[];
extern void PSMTXTrans();
extern void clItemBoxManager_Update();
extern void fn_8013A534();
extern void fn_801737F0();
extern void fn_80173B68();
extern void fn_80173BE8();
extern void fn_80173C34();
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
extern void clItemBoxManager_Draw();
extern void fn_80139810();
extern void fn_801737CC();
extern void fn_801696E4();
extern void fn_801697C0();
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
void *fn_8014E0C4(int a);
asm void fn_8014E118(void *self, int a);
asm void fn_8014E618(void);
asm void fn_8014E804(void);
asm void fn_8014F164(void);
DemoPanel *fn_8014F2DC(DemoPanel *self, short flag);
asm void fn_8014F3D8(void *self);
void fn_8014F5A8(VObj *p);
void fn_8014F5E0(void);
void *fn_8014F6A4(void);
unsigned char fn_8014F6E0(StateObj *o);
CamPanel *fn_8014F6F4(CamPanel *self, short flag);
void fn_8014F81C(VObj *p);
void fn_8014F854(FadeHolder *self);
asm void fn_8014F8FC(void);
asm void fn_8014FC40(void);
unsigned char fn_8014FE08(unsigned char *o);
Base *fn_8014FE10(Base *self, short flag);
void fn_8014FEC4(VObj *p);
void fn_8014FEFC(TextPanelB *self);
void fn_80150004(TextPanel *self);
asm void fn_801500F4(void);
asm void fn_801502AC(void);
asm void fn_8015061C(void);
unsigned char fn_80150924(unsigned char *o);
asm void fn_8015092C(void);
void fn_80150BE4(VObj *p);
asm void fn_80150C1C(void);
asm void fn_80151234(void);
asm void fn_80151F08(void);
asm void DrawColoredQuad(int r, int g, int b, int a, float x, float y, float w, float h);
void fn_80152930(VObj *p);
Base *fn_80152968(Base *self, short flag);
unsigned char fn_801529EC(StateObj *o);
void fn_80152A00(CreditPanel *self);
void fn_80152B2C(VObj *p);
Base *fn_80152B64(Base *self, short flag);
asm void fn_80152C00(void);
unsigned char fn_80153504(StateObj *o);
void fn_80153518(QuadFade *self);
void fn_80153594(VObj *p);
PalObj *fn_801535CC(PalObj *self, short flag);
void fn_80153668(FadeTimer *o);
unsigned char fn_80153758(StateObj *o);
asm void fn_8015376C(void);
void fn_80153A3C(VObj *p);
PalObj *fn_80153A74(PalObj *self, short flag);
void fn_80153AFC(FadeTimer *o);
unsigned char fn_80153BEC(StateObj *o);
asm void fn_80153C00(void);
void fn_80153ED0(VObj *p);
asm void fn_80153F08(void);
asm void fn_801540E0(void *o, int flag);
asm void fn_80154304(void);
asm void fn_80154FB0(void);
void *dtor_8015535C(void *self, short flag);
unsigned char fn_80155398(StateObj *o);
asm void fn_801553AC(void);
Base *fn_801556A0(Base *self, short flag);
int fn_8015571C(char *o, float *a, float *b, float *c);
void fn_8015573C(VObj *p);
CoursePanel *fn_80155774(CoursePanel *self, short flag);
asm void fn_801558CC(void);
unsigned char fn_80156FC0(StateObj *o);
asm void fn_80156FD4(void);
void fn_80157240(VObj *p);
CamPanel *fn_80157278(CamPanel *self, short flag);
asm void fn_80157378(void);
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

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; unsigned int f49; void *f50; unsigned int f51; unsigned int f52; void *f53; unsigned int f54; void *f55; unsigned int f56; unsigned int f57; void *f58; unsigned int f59; void *f60; unsigned int f61; unsigned int f62; void *f63; unsigned int f64; void *f65; unsigned int f66; unsigned int f67; void *f68; unsigned int f69; void *f70; unsigned int f71; void *f72; unsigned int f73; unsigned int f74; void *f75; unsigned int f76; void *f77; unsigned int f78; unsigned int f79; void *f80; unsigned int f81; unsigned int f82; void *f83; unsigned int f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; } extab_fn_8014E118 = { 0x400A0000, 0x0000003C, 0x003D00B8, 0x0000013C, 0x000000B0, 0x00000168, 0x000200B8, 0x0000019C, 0x000000C4, 0x000001B8, 0x000C00B8, 0x000001FC, 0x000000D8, 0x00000208, 0x000000B8, 0x0000021C, 0x000600EC, 0x00000240, 0x000400B8, 0x0000025C, 0x00000100, 0x000002A4, 0x000000B8, 0x000002B4, 0x0000011C, 0x000002C8, 0x00000114, 0x000002D4, 0x0000011C, 0x000002E8, 0x00000130, 0x000003A8, 0x0009013C, 0x000003EC, 0x000E00B8, 0x00000430, 0x00000168, 0x00000438, 0x0000015C, 0x00000458, 0x00000150, 0x00000464, 0x002100B8, 0x00000000, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0100011C, 0x0A80001D, (void *)&MemoryManager_Free, 0x8680001E, 0x00000000, (void *)&dtor_801577D4, 0x07800018, 0x0000000C, (void *)&dtor_80157850, 0x07800018, 0x00000000, (void *)&dtor_801578C8, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801577D4 };

__declspec(section ".extab_user") static const unsigned char extab_fn_8014E618[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; void *f56; unsigned int f57; unsigned int f58; void *f59; unsigned int f60; void *f61; unsigned int f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; unsigned int f71; void *f72; unsigned int f73; void *f74; unsigned int f75; void *f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; void *f83; unsigned int f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; unsigned int f100; void *f101; unsigned int f102; void *f103; unsigned int f104; void *f105; unsigned int f106; void *f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; void *f115; unsigned int f116; void *f117; } extab_fn_8014E804 = { 0x180A0000, 0x00000248, 0x000000E4, 0x00000260, 0x001700D8, 0x000002FC, 0x00000104, 0x00000314, 0x000D00F8, 0x00000430, 0x00000118, 0x00000498, 0x00120134, 0x000004F8, 0x0000012C, 0x00000508, 0x00000134, 0x00000520, 0x00000148, 0x00000540, 0x00050134, 0x000005B4, 0x0011015C, 0x00000610, 0x00000154, 0x00000620, 0x0000015C, 0x00000638, 0x00000170, 0x00000658, 0x0005015C, 0x000006C0, 0x000E0184, 0x0000071C, 0x0000017C, 0x0000072C, 0x00130184, 0x000007DC, 0x00000198, 0x00000808, 0x000001A0, 0x00000850, 0x000001A8, 0x00000874, 0x000001B0, 0x000008A0, 0x000001B8, 0x000008C4, 0x000001C0, 0x000008E8, 0x000001C8, 0x0000090C, 0x000001D0, 0x00000000, 0x0780001D, 0x00000034, (void *)&dtor_80080330, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0780001D, 0x00000034, (void *)&dtor_80080330, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0680001D, 0x00000000, (void *)&dtor_801577D4, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x01000134, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0100015C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001E, 0x00000000, (void *)&dtor_801577D4, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const unsigned char extab_fn_8014F164[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_fn_8014F3D8 = { 0x080A0000, 0x00000060, 0x00560010, 0x00000000, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4 };







__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8014F8FC = { 0x104A0000, 0x000002B4, 0x001C0010, 0x00000000, 0x82000018, (void *)&dtor_80082960 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; void *f19; unsigned int f20; unsigned int f21; void *f22; unsigned int f23; void *f24; unsigned int f25; unsigned int f26; void *f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; void *f34; unsigned int f35; unsigned int f36; void *f37; } extab_fn_8014FC40 = { 0x100A0000, 0x00000050, 0x00080050, 0x00000094, 0x00000048, 0x000000A4, 0x001A0050, 0x00000124, 0x0000005C, 0x00000148, 0x00040050, 0x00000170, 0x00000070, 0x00000188, 0x00000050, 0x000001A0, 0x00000084, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801577D4, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801577D4, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801577D4, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801577D4 };





__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; void *f13; unsigned int f14; unsigned int f15; void *f16; unsigned int f17; void *f18; unsigned int f19; unsigned int f20; void *f21; } extab_fn_801500F4 = { 0x300A0000, 0x00000060, 0x00050038, 0x00000094, 0x00000030, 0x000000D4, 0x00000038, 0x000000DC, 0x00090044, 0x00000120, 0x000C0038, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001D, 0x00000000, (void *)&dtor_801577D4, 0x0A80001C, (void *)&MemoryManager_Free, 0x8680001D, 0x00000000, (void *)&dtor_801577D4 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_fn_801502AC = { 0x380A0000, 0x0000006C, 0x00000020, 0x00000198, 0x00000028, 0x000001C8, 0x00000030, 0x00000000, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_fn_8015061C = { 0x300A0000, 0x000000E8, 0x00000028, 0x00000144, 0x00000030, 0x0000027C, 0x00000038, 0x000002E4, 0x00000040, 0x00000000, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const unsigned char extab_fn_8015092C[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_fn_80150C1C = { 0x304A0000, 0x00000428, 0x00000018, 0x00000540, 0x00000020, 0x00000000, 0x82000060, (void *)&dtor_80082960, 0x82000008, (void *)&dtor_80082960 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80151234 = { 0x408A0000, 0x000004B4, 0x00000010, 0x00000000, 0x8A800018, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; void *f21; unsigned int f22; unsigned int f23; void *f24; unsigned int f25; void *f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; unsigned int f33; void *f34; unsigned int f35; void *f36; unsigned int f37; unsigned int f38; void *f39; } extab_fn_80151F08 = { 0x384A0000, 0x00000048, 0x00F70058, 0x00000430, 0x00000050, 0x00000438, 0x00040058, 0x00000468, 0x00000064, 0x00000478, 0x001C0058, 0x000004F4, 0x00000078, 0x00000528, 0x00020058, 0x0000055C, 0x0000008C, 0x00000574, 0x008A0058, 0x00000000, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001A, 0x00000000, (void *)&dtor_801577D4, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001A, 0x00000000, (void *)&dtor_801577D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001A, 0x00000000, (void *)&dtor_801577D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001A, 0x00000000, (void *)&dtor_801577D4 };

__declspec(section ".extab_user") static const unsigned char extab_DrawColoredQuad[8] = {
    0x39, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};






__declspec(section ".extab_user") static const unsigned char extab_fn_80152C00[8] = {
    0x29, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};





__declspec(section ".extab_user") static const unsigned char extab_fn_8015376C[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




__declspec(section ".extab_user") static const unsigned char extab_fn_80153C00[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_80153F08[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_801540E0[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_fn_80154304 = { 0x384A0000, 0x000006EC, 0x00000030, 0x00000700, 0x00000028, 0x0000070C, 0x00000030, 0x00000720, 0x00000038, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_fn_80154FB0 = { 0x330A0000, 0x00000204, 0x00000018, 0x0000024C, 0x003B0020, 0x00000000, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x82000024, (void *)&dtor_8015535C };


__declspec(section ".extab_user") static const unsigned char extab_fn_801553AC[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




__declspec(section ".extab_user") static const unsigned char extab_fn_801558CC[8] = {
    0x30, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80156FD4[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



__declspec(section ".extab_user") static const unsigned char extab_fn_80157378[8] = {
    0x10, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};






#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014E118 = {
    (void *)&fn_8014E118, 0x00000500, (void *)&extab_fn_8014E118
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014E618 = {
    (void *)&fn_8014E618, 0x000001EC, (void *)extab_fn_8014E618
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014E804 = {
    (void *)&fn_8014E804, 0x00000960, (void *)&extab_fn_8014E804
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014F164 = {
    (void *)&fn_8014F164, 0x00000178, (void *)extab_fn_8014F164
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014F3D8 = {
    (void *)&fn_8014F3D8, 0x000001D0, (void *)&extab_fn_8014F3D8
};







__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014F8FC = {
    (void *)&fn_8014F8FC, 0x00000344, (void *)&extab_fn_8014F8FC
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014FC40 = {
    (void *)&fn_8014FC40, 0x000001C8, (void *)&extab_fn_8014FC40
};





__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801500F4 = {
    (void *)&fn_801500F4, 0x000001B8, (void *)&extab_fn_801500F4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801502AC = {
    (void *)&fn_801502AC, 0x00000370, (void *)&extab_fn_801502AC
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8015061C = {
    (void *)&fn_8015061C, 0x00000308, (void *)&extab_fn_8015061C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8015092C = {
    (void *)&fn_8015092C, 0x000002B8, (void *)extab_fn_8015092C
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80150C1C = {
    (void *)&fn_80150C1C, 0x00000618, (void *)&extab_fn_80150C1C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80151234 = {
    (void *)&fn_80151234, 0x00000CD4, (void *)&extab_fn_80151234
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80151F08 = {
    (void *)&fn_80151F08, 0x000007BC, (void *)&extab_fn_80151F08
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DrawColoredQuad = {
    (void *)&DrawColoredQuad, 0x0000026C, (void *)extab_DrawColoredQuad
};






__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80152C00 = {
    (void *)&fn_80152C00, 0x00000904, (void *)extab_fn_80152C00
};





__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8015376C = {
    (void *)&fn_8015376C, 0x000002D0, (void *)extab_fn_8015376C
};




__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80153C00 = {
    (void *)&fn_80153C00, 0x000002D0, (void *)extab_fn_80153C00
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80153F08 = {
    (void *)&fn_80153F08, 0x000001D8, (void *)extab_fn_80153F08
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801540E0 = {
    (void *)&fn_801540E0, 0x00000224, (void *)extab_fn_801540E0
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80154304 = {
    (void *)&fn_80154304, 0x00000CAC, (void *)&extab_fn_80154304
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80154FB0 = {
    (void *)&fn_80154FB0, 0x000003AC, (void *)&extab_fn_80154FB0
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801553AC = {
    (void *)&fn_801553AC, 0x000002F4, (void *)extab_fn_801553AC
};




__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801558CC = {
    (void *)&fn_801558CC, 0x000016F4, (void *)extab_fn_801558CC
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80156FD4 = {
    (void *)&fn_80156FD4, 0x0000026C, (void *)extab_fn_80156FD4
};



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157378 = {
    (void *)&fn_80157378, 0x00000360, (void *)extab_fn_80157378
};






}

struct DemoScene1C0 {
    inline DemoScene1C0(int a) { fn_8014E118(this, a); }
    char pad[0x1C0];
};

struct Panel44 {
    inline Panel44() { fn_8014F3D8(this); }
    char pad[0x44];
};


extern "C" void *fn_8014E0C4(int a) {
    Frame_PostDrawOverlay();
    Frame_UpdatePerFrameState();
    return new DemoScene1C0(a);
}

extern "C" asm void fn_8014E118(void *self, int a) { /* 0x8014E118 size:0x500 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r6, lbl_8048FF80@ha
    lis r5, lbl_8048FED8@ha
    stw r0, 0x34(r1)
    addi r0, r5, lbl_8048FED8@l
    lis r7, lbl_80363D30@ha
    stmw r24, 0x10(r1)
    mr r30, r3
    addi r3, r6, lbl_8048FF80@l
    mr r25, r4
    addi r31, r7, lbl_80363D30@l
    stw r3, 0x0(r30)
    stw r0, 0x0(r30)
    bl fn_80121210
    bl DrawManager_GetOrCreate
    bl fn_80169E20
    stw r3, 0x4(r30)
    li r3, 0x0
    lfs f1, lbl_806D8070(r2)
    clrlwi. r0, r25, 24
    stw r3, 0x8(r30)
    lfs f0, lbl_806D8064(r2)
    stfs f1, 0xc(r30)
    stfs f0, 0x10(r30)
    stb r3, 0x28(r30)
    stb r3, 0x29(r30)
    stw r3, 0x2c(r30)
    stfs f0, 0x30(r30)
    stw r3, 0x18(r30)
    stw r3, 0x1c(r30)
    stw r3, 0x20(r30)
    stw r3, 0x24(r30)
    stw r3, 0x14(r30)
    stw r3, 0x1a8(r30)
    stw r3, 0x1ac(r30)
    stw r3, 0x1b4(r30)
    bne fn_8014E118_L_8014E1B8
    li r0, 0x1
    stb r0, 0x28(r30)
    fn_8014E118_L_8014E1B8:
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8014E118_L_8014E1EC
    bl fn_80169E10
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014E118_L_8014E1E0
    addi r0, r31, 0x2d34
    stw r0, 0x24(r30)
    b fn_8014E118_L_8014E210
    fn_8014E118_L_8014E1E0:
    addi r0, r31, 0x2ea8
    stw r0, 0x24(r30)
    b fn_8014E118_L_8014E210
    fn_8014E118_L_8014E1EC:
    bl fn_80169E10
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014E118_L_8014E208
    addi r0, r31, 0x2b18
    stw r0, 0x24(r30)
    b fn_8014E118_L_8014E210
    fn_8014E118_L_8014E208:
    addi r0, r31, 0x2c5c
    stw r0, 0x24(r30)
    fn_8014E118_L_8014E210:
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r0, -0x1
    li r28, 0x0
    stw r0, g_kartStartSlot(r13)
    mr r27, r28
    addi r26, r31, 0xde0
    li r25, 0x0
    fn_8014E118_L_8014E234:
    addi r3, r28, 0x64
    add r3, r30, r3
    bl PSMTXIdentity
    li r3, 0x384
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E254
    bl KartDriver_New_Empty
    fn_8014E118_L_8014E254:
    addi r0, r27, 0x34
    addi r6, r28, 0x64
    stwx r24, r30, r0
    mr r7, r25
    lwz r5, 0x0(r26)
    add r6, r30, r6
    lwzx r3, r30, r0
    li r4, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_Init
    li r3, 0x154
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E2B4
    lfs f1, lbl_806D8064(r2)
    addi r0, r27, 0x34
    lwzx r5, r30, r0
    li r4, 0x0
    fmr f2, f1
    lwz r6, 0x0(r26)
    fmr f3, f1
    li r7, 0x1
    bl TornadoEffect_Ctor
    fn_8014E118_L_8014E2B4:
    addi r4, r27, 0x4c
    addi r0, r27, 0x184
    stwx r24, r30, r4
    li r3, 0x0
    stwx r3, r30, r0
    lwzx r3, r30, r4
    bl TornadoEffect_SetFlagC0
    addi r0, r25, 0x19c
    addi r25, r25, 0x1
    li r3, 0x1
    addi r27, r27, 0x4
    cmpwi r25, 0x6
    stbx r3, r30, r0
    addi r26, r26, 0x4
    addi r28, r28, 0x30
    blt fn_8014E118_L_8014E234
    stw r3, 0x1a4(r30)
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E314
    addi r4, r31, 0x3820
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8014E118_L_8014E314:
    stw r24, 0x14(r30)
    li r3, 0x7c
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E34C
    lwz r3, 0x14(r30)
    addi r4, r31, 0x3848
    bl ResolveJointByName
    lfs f1, lbl_806D8068(r2)
    mr r5, r3
    mr r3, r24
    addi r4, r31, 0x3838
    fmr f2, f1
    bl fn_80171CD0
    fn_8014E118_L_8014E34C:
    stw r24, 0x1a8(r30)
    lwz r3, 0x14(r30)
    bl Object_ReleaseAnimResource
    li r0, 0x0
    li r3, 0x24
    stb r0, 0x1b0(r30)
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E374
    bl fn_80140874
    fn_8014E118_L_8014E374:
    stw r24, 0x1ac(r30)
    li r0, 0x3
    lfs f3, lbl_806D8074(r2)
    li r3, 0x98
    lwz r4, 0x1ac(r30)
    lfs f2, lbl_806D8078(r2)
    stw r0, 0xc(r4)
    lfs f1, lbl_806D807C(r2)
    lwz r4, 0x1ac(r30)
    lfs f0, lbl_806D8080(r2)
    stfs f3, 0x8(r4)
    lwz r4, 0x1ac(r30)
    stfs f2, 0x10(r4)
    lwz r4, 0x1ac(r30)
    stfs f1, 0x14(r4)
    lwz r4, 0x1ac(r30)
    stfs f0, 0x18(r4)
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E4B4
    li r3, 0x20
    bl Alloc
    mr. r25, r3
    beq fn_8014E118_L_8014E3E0
    addi r4, r31, 0x3860
    li r5, 0x0
    bl fn_8013D800
    fn_8014E118_L_8014E3E0:
    stw r25, 0x0(r24)
    li r3, 0x20
    bl Alloc
    mr. r25, r3
    beq fn_8014E118_L_8014E400
    addi r4, r31, 0x386c
    li r5, 0x0
    bl fn_8013D800
    fn_8014E118_L_8014E400:
    stw r25, 0x4(r24)
    addi r4, r31, 0x311c
    li r5, 0x0
    addi r3, r2, -0x22F8  /* lbl_806D7F68 */
    stb r5, 0x8(r24)
    li r0, 0x1
    lfs f7, lbl_806D8064(r2)
    stw r5, 0xc(r24)
    lfs f1, 0x311c(r31)
    stfs f7, 0x10(r24)
    lfs f0, 0x4(r4)
    stb r0, 0x14(r24)
    lfs f2, 0x8(r4)
    stfs f1, 0x1c(r24)
    lfs f1, 0xc(r4)
    stfs f0, 0x20(r24)
    lfs f0, 0x10(r4)
    stfs f7, 0x6c(r24)
    lfs f6, 0x14(r4)
    stb r0, 0x15(r24)
    lfs f5, 0x18(r4)
    stfs f2, 0x24(r24)
    lfs f4, 0x1c(r4)
    stfs f1, 0x28(r24)
    lfs f3, 0x20(r4)
    stfs f7, 0x70(r24)
    lfs f2, 0x24(r4)
    stb r0, 0x16(r24)
    lfs f1, lbl_806D7F68(r2)
    stfs f0, 0x2c(r24)
    lfs f0, 0x4(r3)
    stfs f6, 0x30(r24)
    stfs f7, 0x74(r24)
    stb r0, 0x17(r24)
    stfs f5, 0x34(r24)
    stfs f4, 0x38(r24)
    stfs f7, 0x78(r24)
    stb r0, 0x18(r24)
    stfs f3, 0x3c(r24)
    stfs f2, 0x40(r24)
    stfs f7, 0x7c(r24)
    stb r0, 0x80(r24)
    stfs f1, 0x84(r24)
    stfs f0, 0x88(r24)
    stfs f7, 0x94(r24)
    fn_8014E118_L_8014E4B4:
    stw r24, 0x1b4(r30)
    li r3, 0x470
    bl FUN_8003b120
    mr. r29, r3
    beq fn_8014E118_L_8014E4E8
    lis r4, fn_80149214@ha
    lis r5, dtor_800869D0@ha
    addi r4, r4, fn_80149214@l
    li r6, 0x230
    addi r5, r5, dtor_800869D0@l
    li r7, 0x2
    bl __construct_new_array
    mr r29, r3
    fn_8014E118_L_8014E4E8:
    stw r29, 0x1bc(r30)
    li r0, 0x0
    lwz r3, 0x1bc(r30)
    stw r0, 0x18(r3)
    lwz r3, 0x1bc(r30)
    stw r0, 0x248(r3)
    bl fn_80293BBC
    mr r29, r3
    lwz r3, 0x1bc(r30)
    addi r4, r31, 0x3884
    addi r5, r29, 0x18
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lwz r3, 0x1bc(r30)
    addi r4, r31, 0x3894
    addi r5, r29, 0x2c
    addi r3, r3, 0x230
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_8014E118_L_8014E570
    bl fn_80157B20
    addi r3, r24, 0xc
    bl fn_80157D18
    lis r3, fn_80157820@ha
    lis r5, fn_8014E04C@ha
    addi r4, r3, fn_80157820@l
    li r6, 0xc
    addi r3, r24, 0x18
    addi r5, r5, fn_8014E04C@l
    li r7, 0x2
    bl __construct_array
    fn_8014E118_L_8014E570:
    stw r24, 0x1b8(r30)
    li r3, 0x1
    bl SetResourceLoadingFlag
    li r27, 0x0
    addi r26, r31, 0x3158
    fn_8014E118_L_8014E584:
    lwz r3, 0x1b8(r30)
    lwz r4, 0x4(r26)
    bl fn_8014E028
    lwz r3, 0x1b8(r30)
    lwz r4, 0x4(r26)
    bl fn_8014E004
    lwz r3, 0x1b8(r30)
    lwz r4, 0x4(r26)
    bl fn_8014DD5C
    cmplwi r3, 0x0
    beq fn_8014E118_L_8014E5C8
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lfs f2, lbl_806D8068(r2)
    fmr f3, f1
    fmr f4, f1
    bl clNormal3D_SetScale
    fn_8014E118_L_8014E5C8:
    addi r27, r27, 0x1
    addi r26, r26, 0x8
    cmplwi r27, 0xa
    blt fn_8014E118_L_8014E584
    li r3, 0x1
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0x32
    bl PreloadItemResources
    li r3, 0x39
    bl PreloadItemResources
    li r3, 0x8
    bl PreloadItemResources
    mr r3, r30
    lmw r24, 0x10(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_8014E618(void) { /* 0x8014E618 size:0x1EC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r31, r3
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    bne fn_8014E618_L_8014E7E4
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq fn_8014E618_L_8014E660
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    fn_8014E618_L_8014E660:
    bl ServiceMode_UpdateScheduleGate
    bl fn_80169E10
    clrlwi. r0, r3, 24
    beq fn_8014E618_L_8014E718
    bl IsCardValid
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014E618_L_8014E718
    bl ServiceEnable_Get
    clrlwi. r0, r3, 24
    beq fn_8014E618_L_8014E698
    bl ServiceValue_Get
    clrlwi. r0, r3, 24
    beq fn_8014E618_L_8014E6C0
    fn_8014E618_L_8014E698:
    lfs f3, lbl_806D8068(r2)
    li r3, 0x0
    lfs f1, lbl_806D8084(r2)
    li r4, 0x1553
    fmr f4, f3
    li r5, 0x0
    fmr f2, f1
    fmr f5, f3
    bl fn_80169334
    b fn_8014E618_L_8014E718
    fn_8014E618_L_8014E6C0:
    bl Sci2Card_GetReceiptTestFlag
    clrlwi. r0, r3, 24
    beq fn_8014E618_L_8014E6F4
    lfs f3, lbl_806D8068(r2)
    li r3, 0x0
    lfs f1, lbl_806D8084(r2)
    li r4, 0x1554
    fmr f4, f3
    li r5, 0x0
    fmr f2, f1
    fmr f5, f3
    bl fn_80169334
    b fn_8014E618_L_8014E718
    fn_8014E618_L_8014E6F4:
    lfs f1, lbl_806D8084(r2)
    li r3, 0x0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x1554
    fmr f2, f1
    lfs f5, lbl_806D8064(r2)
    fmr f4, f3
    li r5, 0x0
    bl fn_80169334
    fn_8014E618_L_8014E718:
    li r3, 0x0
    bl fn_8011F994
    lwz r0, 0xc(r31)
    lis r3, lbl_80367488@ha
    addi r3, r3, lbl_80367488@l
    mulli r0, r0, 0xc
    add r3, r3, r0
    lbz r0, 0x8(r3)
    cmplwi r0, 0x0
    beq fn_8014E618_L_8014E7C4
    lfs f1, lbl_806D8088(r2)
    lfs f0, 0x28(r31)
    lfs f2, lbl_806D8064(r2)
    fmuls f1, f1, f0
    lfs f3, lbl_806D808C(r2)
    bl Saturate_Double
    bl LUT_Sin12Bit
    fmr f31, f1
    bl PcbSync_CountJoinedPcbsAdvancedKarts
    lfs f0, lbl_806D8090(r2)
    mr r30, r3
    fmuls f1, f0, f31
    bl __cvt_fp2unsigned
    li r4, -0x100
    mr r5, r30
    rlwimi r4, r3, 0, 24, 31
    li r3, 0x0
    bl CreditMgr_DrawCoinCreditBanner
    lfs f2, 0x28(r31)
    lfs f1, lbl_806D8068(r2)
    lfs f0, lbl_806D8094(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x28(r31)
    cror eq, gt, eq
    bne fn_8014E618_L_8014E7D4
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x28(r31)
    lwz r3, 0x2c(r31)
    addi r0, r3, 0x1
    clrlwi r0, r0, 31
    stw r0, 0x2c(r31)
    b fn_8014E618_L_8014E7D4
    fn_8014E618_L_8014E7C4:
    lfs f0, lbl_806D8064(r2)
    li r0, 0x0
    stfs f0, 0x28(r31)
    stw r0, 0x2c(r31)
    fn_8014E618_L_8014E7D4:
    li r3, 0x6
    bl fn_8011F994
    li r3, -0x1
    bl HSD_StateInvalidate
    fn_8014E618_L_8014E7E4:
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_8014E804(void) { /* 0x8014E804 size:0x960 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lis r3, lbl_80363D30@ha
    stw r30, 0x18(r1)
    addi r30, r3, lbl_80363D30@l
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
    lis r3, lbl_8048FE8C@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r29)
    addi r0, r3, lbl_8048FE8C@l
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
    lis r3, lbl_8048FE64@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r29)
    addi r0, r3, lbl_8048FE64@l
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
    lis r3, lbl_8048FE3C@ha
    addi r0, r4, lbl_8048FF80@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r29)
    addi r3, r3, lbl_8048FE3C@l
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
    lis r3, lbl_8048FE14@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r30)
    addi r0, r3, lbl_8048FE14@l
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
    lis r3, lbl_8048FE14@ha
    addi r0, r4, lbl_8048FF80@l
    stw r0, 0x0(r30)
    addi r0, r3, lbl_8048FE14@l
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
    lis r3, lbl_8048FF64@ha
    addi r0, r4, lbl_8048FF80@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r30)
    addi r3, r3, lbl_8048FF64@l
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
}

extern "C" asm void fn_8014F164(void) { /* 0x8014F164 size:0x178 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r31, r3
    lwz r0, 0x8(r3)
    cmpwi r0, 0x9
    beq fn_8014F164_L_8014F2BC
    lbz r0, 0x1c(r31)
    cmplwi r0, 0x0
    bne fn_8014F164_L_8014F1A4
    li r0, 0x1
    stb r0, 0x1c(r31)
    fn_8014F164_L_8014F1A4:
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq fn_8014F164_L_8014F1B8
    lfs f1, lbl_806D8098(r2)
    bl Sprite_AdvanceAnim
    fn_8014F164_L_8014F1B8:
    lwz r30, 0x20(r31)
    li r3, 0x0
    bl CreditMgr_GetCreditCount
    stw r3, 0x20(r31)
    lwz r0, 0x20(r31)
    cmpw r0, r30
    beq fn_8014F164_L_8014F1DC
    li r0, 0x0
    stw r0, 0x14(r31)
    fn_8014F164_L_8014F1DC:
    lwz r3, 0x14(r31)
    lfs f2, lbl_806D8064(r2)
    addi r0, r3, 0x1
    lfs f31, lbl_806D8060(r2)
    stw r0, 0x14(r31)
    lfs f0, 0xc(r31)
    fcmpu cr0, f0, f2
    beq fn_8014F164_L_8014F244
    fctiwz f0, f31
    lwz r3, 0x14(r31)
    stfd f0, 0x8(r1)
    lwz r0, 0xc(r1)
    cmpw r3, r0
    bge fn_8014F164_L_8014F244
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f1, lbl_806D80A0(r2)
    stw r0, 0x8(r1)
    lfs f3, lbl_806D8068(r2)
    lfd f0, 0x8(r1)
    fsubs f0, f0, f1
    fdivs f0, f0, f31
    fsubs f1, f3, f0
    bl Saturate_Double
    stfs f1, 0xc(r31)
    fn_8014F164_L_8014F244:
    fctiwz f0, f31
    lwz r0, 0x18(r31)
    lwz r4, 0x14(r31)
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    subf r0, r3, r0
    cmpw r4, r0
    ble fn_8014F164_L_8014F29C
    subf r3, r0, r4
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x8(r1)
    lfd f1, lbl_806D80A0(r2)
    stw r3, 0xc(r1)
    lfs f2, lbl_806D8064(r2)
    lfd f0, 0x8(r1)
    lfs f3, lbl_806D8068(r2)
    fsubs f0, f0, f1
    fdivs f1, f0, f31
    bl Saturate_Double
    stfs f1, 0xc(r31)
    b fn_8014F164_L_8014F2A4
    fn_8014F164_L_8014F29C:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0xc(r31)
    fn_8014F164_L_8014F2A4:
    lwz r3, 0x14(r31)
    lwz r0, 0x18(r31)
    cmpw r3, r0
    blt fn_8014F164_L_8014F2BC
    li r0, 0x9
    stw r0, 0x8(r31)
    fn_8014F164_L_8014F2BC:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" DemoPanel *fn_8014F2DC(DemoPanel *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FD98;
        fn_80120A08(0x1553);
        fn_80120A08(0x1554);
        if (self->f8 != 0) {
            GXDrawDone();
            self->f8->vC();
            self->f8 = 0;
        }
        fn_801B7CD0(0);
        CreditMgr_SetActiveSlot(0);
        lbl_806D1580 = 0;
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

extern "C" asm void fn_8014F3D8(void *self) { /* 0x8014F3D8 size:0x1D0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, lbl_803FE0C8@ha
    li r5, 0x0
    stw r0, 0x14(r1)
    addi r0, r4, lbl_803FE0C8@l
    lfs f0, lbl_806D8064(r2)
    stw r31, 0xc(r1)
    mr r31, r3
    lis r3, lbl_8048FD98@ha
    stw r0, 0x0(r31)
    addi r4, r3, lbl_8048FD98@l
    li r0, 0x1
    li r3, 0x0
    stb r5, 0x4(r31)
    stw r4, 0x0(r31)
    stw r5, 0x14(r31)
    stw r5, 0x8(r31)
    stw r5, 0xc(r31)
    stw r5, 0x10(r31)
    stb r0, 0x18(r31)
    stfs f0, 0x28(r31)
    stw r5, 0x2c(r31)
    bl CreditMgr_GetCreditCount
    stw r3, 0x30(r31)
    li r4, 0x0
    lis r3, lbl_80598A60@ha
    stb r4, 0x34(r31)
    addi r3, r3, lbl_80598A60@l
    stw r4, 0x38(r31)
    lbz r0, 0x20(r3)
    cmpwi r0, 0x2
    bne fn_8014F3D8_L_8014F464
    stb r4, 0x3c(r31)
    b fn_8014F3D8_L_8014F46C
    fn_8014F3D8_L_8014F464:
    li r0, 0x1
    stb r0, 0x3c(r31)
    fn_8014F3D8_L_8014F46C:
    li r0, 0x0
    stb r0, 0x3c(r31)
    stw r0, 0x1c(r31)
    stw r0, 0x20(r31)
    stw r0, 0x40(r31)
    lbz r0, lbl_806D12E2(r13)
    cmplwi r0, 0x0
    bne fn_8014F3D8_L_8014F498
    li r0, 0x1
    stw r0, 0x40(r31)
    stw r0, 0xc(r31)
    fn_8014F3D8_L_8014F498:
    li r0, 0x0
    stb r0, lbl_806D12E2(r13)
    bl fn_80121210
    bl clRom_PurgeAll
    bl StrPcb_GetInstance
    cmplwi r3, 0x0
    beq fn_8014F3D8_L_8014F4C8
    bl StrPcb_GetInstance
    li r4, 0x1
    bl StrPcb_ResetCommands_Zero
    bl StrPcb_GetInstance
    bl StrPcb_ResetCommands_NeutralDefault
    fn_8014F3D8_L_8014F4C8:
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne fn_8014F3D8_L_8014F4DC
    li r0, 0x0
    b fn_8014F3D8_L_8014F4E0
    fn_8014F3D8_L_8014F4DC:
    mr r0, r3
    fn_8014F3D8_L_8014F4E0:
    cmplwi r0, 0x0
    beq fn_8014F3D8_L_8014F50C
    cmplwi r3, 0x0
    beq fn_8014F3D8_L_8014F504
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014F3D8_L_8014F504:
    li r0, 0x0
    stw r0, g_pInputState(r13)
    fn_8014F3D8_L_8014F50C:
    li r3, 0x1
    bl InitRumbleController
    lbz r4, 0x3c(r31)
    li r3, 0x0
    bl fn_801699D8
    lwz r0, g_currentSceneState(r13)
    cmpwi r0, 0x5
    beq fn_8014F3D8_L_8014F534
    li r3, 0x4
    bl SetSyncTarget
    fn_8014F3D8_L_8014F534:
    li r3, 0x0
    bl SetLocalPcbRole
    li r0, 0x0
    li r3, 0x0
    stb r0, lbl_806D12B0(r13)
    bl SetResourceLoadingFlag
    li r3, 0x0
    bl CreditMgr_GetCreditCount
    cntlzw r0, r3
    li r3, 0x1
    rlwnm r0, r3, r0, 31, 31
    li r3, 0x0
    stb r0, lbl_806D117C(r13)
    bl CreditMgr_SetActiveSlot
    stw r31, lbl_806D1580(r13)
    li r3, 0x1
    bl fn_801933D0
    li r3, 0x0
    bl fn_801B7CD0
    li r3, 0x1553
    bl PreloadResource
    li r3, 0x1554
    bl PreloadResource
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void fn_8014F5A8(VObj *p) {
    delete p;
}

extern "C" void fn_8014F5E0(void) {
    char *s = lbl_80363D30;
    if (lbl_806D1580 != 0) {
        OverlayText(1, 1, 2, s + 0x38F8, lbl_806D1580->f14);
        OverlayText(1, 1, 3, s + 0x3908, lbl_806D1580->fC);
        OverlayText(1, 1, 4, s + 0x3918, lbl_806D1580->f10);
        OverlayText(1, 1, 5, s + 0x3928, lbl_8048FD50[lbl_806D1580->f10]);
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
        self->vt = lbl_8048FFC0;
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

extern "C" asm void fn_8014F8FC(void) { /* 0x8014F8FC size:0x344 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    mr r31, r3
    lwz r0, 0x4(r3)
    cmpwi r0, 0x9
    beq fn_8014F8FC_L_8014FC20
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x0
    lfs f2, lbl_806D8070(r2)
    li r4, 0x1499
    li r5, 0x0
    bl fn_801698B4
    lfs f1, lbl_806D80D4(r2)
    li r3, 0x5
    lfs f2, lbl_806D80D8(r2)
    li r4, 0x149b
    li r5, 0x0
    bl fn_801698B4
    lfs f1, lbl_806D80DC(r2)
    li r3, 0x5
    lfs f2, lbl_806D80D8(r2)
    li r4, 0x149c
    li r5, 0x0
    bl fn_801698B4
    lbz r0, 0x1c(r31)
    cmplwi r0, 0x0
    beq fn_8014F8FC_L_8014F994
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x6
    lfs f2, lbl_806D80E0(r2)
    li r4, 0x50d
    li r5, 0x0
    bl fn_801698B4
    fn_8014F8FC_L_8014F994:
    bl fn_801A1280
    lwz r3, 0x20(r31)
    cmplwi r3, 0x0
    beq fn_8014F8FC_L_8014F9AC
    lfs f1, lbl_806D8098(r2)
    bl Sprite_AdvanceAnim
    fn_8014F8FC_L_8014F9AC:
    lwz r3, 0x20(r31)
    cmplwi r3, 0x0
    beq fn_8014F8FC_L_8014F9BC
    bl fn_801A0004
    fn_8014F8FC_L_8014F9BC:
    lwz r0, 0x24(r31)
    cmplwi r0, 0x0
    beq fn_8014F8FC_L_8014FA44
    lfs f1, 0xc(r31)
    lfs f0, lbl_806D80E4(r2)
    lfs f2, lbl_806D80C4(r2)
    fadds f0, f1, f0
    stfs f0, 0xc(r31)
    lfs f1, 0x28(r31)
    lfs f0, 0xc(r31)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    bge fn_8014F8FC_L_8014F9F8
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0xc(r31)
    fn_8014F8FC_L_8014F9F8:
    lfs f4, 0x28(r31)
    lfs f0, lbl_806D80C4(r2)
    lfs f1, 0xc(r31)
    fadds f2, f0, f4
    lfs f3, lbl_806D8064(r2)
    lwz r3, 0x24(r31)
    lfs f0, lbl_806D80E8(r2)
    fsubs f2, f2, f1
    lfs f1, lbl_806D8098(r2)
    fsubs f2, f2, f4
    fadds f2, f2, f3
    stfs f2, 0xc(r3)
    stfs f0, 0x10(r3)
    lwz r3, 0x24(r31)
    stfs f3, 0x1c(r3)
    lwz r3, 0x24(r31)
    bl Sprite_AdvanceAnim
    lwz r3, 0x24(r31)
    bl fn_801A0004
    fn_8014F8FC_L_8014FA44:
    lwz r30, 0x10(r31)
    cmplwi r30, 0x0
    beq fn_8014F8FC_L_8014FA94
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014F8FC_L_8014FA94
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8014F8FC_L_8014FA94
    addi r3, r1, 0x8
    li r4, 0x0
    bl NamCam_GetImageHandle
    cmpwi r3, 0x1
    bne fn_8014F8FC_L_8014FA94
    lwz r3, 0x8(r1)
    addi r5, r1, 0xc
    lwz r4, 0x4(r30)
    bl NamCam_LoadImage
    li r0, 0x1
    stb r0, 0x1(r30)
    fn_8014F8FC_L_8014FA94:
    lwz r0, 0x4(r31)
    lfs f31, lbl_806D8060(r2)
    cmpwi r0, 0x1
    beq fn_8014F8FC_L_8014FB2C
    bge fn_8014F8FC_L_8014FAB4
    cmpwi r0, 0x0
    bge fn_8014F8FC_L_8014FAC0
    b fn_8014F8FC_L_8014FB90
    fn_8014F8FC_L_8014FAB4:
    cmpwi r0, 0x3
    bge fn_8014F8FC_L_8014FB90
    b fn_8014F8FC_L_8014FB54
    fn_8014F8FC_L_8014FAC0:
    lfs f0, 0x8(r31)
    lfs f3, lbl_806D8068(r2)
    fadds f0, f0, f3
    stfs f0, 0x8(r31)
    lfs f0, 0x8(r31)
    fcmpo cr0, f0, f31
    bge fn_8014F8FC_L_8014FAF4
    fdivs f0, f0, f31
    lfs f2, lbl_806D8064(r2)
    fsubs f1, f3, f0
    bl Saturate_Double
    stfs f1, 0x14(r31)
    b fn_8014F8FC_L_8014FAFC
    fn_8014F8FC_L_8014FAF4:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x14(r31)
    fn_8014F8FC_L_8014FAFC:
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014F8FC_L_8014FB90
    li r3, 0x5
    bl SetSyncTarget
    li r0, 0x1
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r31)
    stfs f0, 0x8(r31)
    b fn_8014F8FC_L_8014FB90
    fn_8014F8FC_L_8014FB2C:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x14(r31)
    bl PcbSync_AllKartsInValidSelectState
    clrlwi. r0, r3, 24
    beq fn_8014F8FC_L_8014FB90
    li r0, 0x2
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r31)
    stfs f0, 0x8(r31)
    b fn_8014F8FC_L_8014FB90
    fn_8014F8FC_L_8014FB54:
    lfs f3, lbl_806D8068(r2)
    lfs f0, 0x8(r31)
    lfs f2, lbl_806D8064(r2)
    fadds f0, f0, f3
    stfs f0, 0x8(r31)
    lfs f0, 0x8(r31)
    fdivs f1, f0, f31
    bl Saturate_Double
    stfs f1, 0x14(r31)
    lfs f0, 0x8(r31)
    fcmpo cr0, f0, f31
    cror eq, gt, eq
    bne fn_8014F8FC_L_8014FB90
    li r0, 0x9
    stw r0, 0x4(r31)
    fn_8014F8FC_L_8014FB90:
    lfs f1, lbl_806D8064(r2)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    bge fn_8014F8FC_L_8014FC20
    addi r3, r1, 0x18
    bl ResCtrl_Init
    addi r3, r1, 0x18
    bl fn_80121E10
    lfs f5, lbl_806D80B8(r2)
    li r5, 0x2
    lfs f4, lbl_806D8070(r2)
    li r0, 0x1
    lfs f3, lbl_806D8068(r2)
    addi r3, r1, 0x18
    lfs f2, lbl_806D80C4(r2)
    li r4, 0x7
    lfs f0, lbl_806D80C8(r2)
    stw r5, 0x20(r1)
    lfs f1, lbl_806D8090(r2)
    stb r0, 0x28(r1)
    stfs f5, 0x2c(r1)
    stfs f4, 0x30(r1)
    stfs f3, 0x34(r1)
    stfs f2, 0x38(r1)
    stfs f0, 0x3c(r1)
    lfs f0, 0x14(r31)
    fmuls f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x70(r1)
    lwz r0, 0x74(r1)
    clrlwi r0, r0, 24
    stw r0, 0x4c(r1)
    stw r0, 0x50(r1)
    stw r0, 0x54(r1)
    stw r0, 0x58(r1)
    bl fn_8011FAFC
    fn_8014F8FC_L_8014FC20:
    psq_l f31, 0x88(r1), 0, 0
    lwz r0, 0x94(r1)
    lfd f31, 0x80(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

extern "C" asm void fn_8014FC40(void) { /* 0x8014FC40 size:0x1C8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, lbl_8048FF80@ha
    lis r4, lbl_8048FFC0@ha
    stw r0, 0x14(r1)
    addi r5, r5, lbl_8048FF80@l
    li r0, 0x0
    lfs f1, lbl_806D8064(r2)
    stw r31, 0xc(r1)
    mr r31, r3
    addi r3, r4, lbl_8048FFC0@l
    lfs f0, lbl_806D8068(r2)
    stw r30, 0x8(r1)
    stw r5, 0x0(r31)
    stw r3, 0x0(r31)
    stw r0, 0x4(r31)
    stfs f1, 0x8(r31)
    stfs f1, 0xc(r31)
    stfs f0, 0x14(r31)
    bl isJapanese
    stw r3, 0x18(r31)
    bl VBlankValue_Get
    clrlwi. r0, r3, 24
    bne fn_8014FC40_L_8014FD34
    li r0, 0x0
    li r3, 0x8
    stb r0, 0x1c(r31)
    bl Alloc
    mr. r30, r3
    beq fn_8014FC40_L_8014FCD8
    li r0, 0x0
    lis r3, 0x5
    stb r0, 0x0(r30)
    subi r3, r3, 0x5000
    stb r0, 0x1(r30)
    stw r0, 0x4(r30)
    bl FUN_8003b120
    stw r3, 0x4(r30)
    fn_8014FC40_L_8014FCD8:
    stw r30, 0x10(r31)
    lwz r30, 0x10(r31)
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014FC40_L_8014FD44
    lbz r0, 0x0(r30)
    cmplwi r0, 0x1
    bne fn_8014FC40_L_8014FD1C
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014FC40_L_8014FD1C
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8014FC40_L_8014FD1C
    li r0, 0x0
    stb r0, 0x0(r30)
    bl NamCam_End
    fn_8014FC40_L_8014FD1C:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x0(r30)
    stb r0, 0x1(r30)
    bl NamCam_Init
    b fn_8014FC40_L_8014FD44
    fn_8014FC40_L_8014FD34:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x1c(r31)
    stw r0, 0x10(r31)
    fn_8014FC40_L_8014FD44:
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq fn_8014FC40_L_8014FD64
    li r4, 0x1ae
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014FC40_L_8014FD64:
    stw r30, 0x20(r31)
    lwz r3, 0x20(r31)
    cmplwi r3, 0x0
    beq fn_8014FC40_L_8014FD84
    lfs f1, lbl_806D80B8(r2)
    lfs f0, lbl_806D80F0(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    fn_8014FC40_L_8014FD84:
    bl fn_80169E20
    cmpwi r3, 0x0
    bne fn_8014FC40_L_8014FDC0
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq fn_8014FC40_L_8014FDB0
    li r4, 0x13d
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014FC40_L_8014FDB0:
    stw r30, 0x24(r31)
    lfs f0, lbl_806D80F4(r2)
    stfs f0, 0x28(r31)
    b fn_8014FC40_L_8014FDEC
    fn_8014FC40_L_8014FDC0:
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq fn_8014FC40_L_8014FDE0
    li r4, 0x10b
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014FC40_L_8014FDE0:
    stw r30, 0x24(r31)
    lfs f0, lbl_806D80F8(r2)
    stfs f0, 0x28(r31)
    fn_8014FC40_L_8014FDEC:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" unsigned char fn_8014FE08(unsigned char *o) {
    return o[4];
}

extern "C" Base *fn_8014FE10(Base *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FFE8;
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

extern "C" asm void fn_801500F4(void) { /* 0x801500F4 size:0x1B8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r7, lbl_8048FF80@ha
    lis r6, lbl_8048FFE8@ha
    stw r0, 0x34(r1)
    addi r0, r6, lbl_8048FFE8@l
    lis r8, lbl_80363D30@ha
    stmw r26, 0x18(r1)
    mr r29, r3
    addi r3, r7, lbl_8048FF80@l
    addi r31, r8, lbl_80363D30@l
    mr r27, r4
    mr r30, r5
    stw r3, 0x0(r29)
    stw r0, 0x0(r29)
    lwz r5, 0x3638(r31)
    lwz r4, 0x363c(r31)
    lwz r3, 0x3640(r31)
    lwz r0, 0x3644(r31)
    stw r5, 0x8(r1)
    stw r4, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    bl fn_80121210
    li r0, 0x0
    li r3, 0x30
    stb r0, 0x4(r29)
    stw r0, 0x8(r29)
    bl Alloc
    mr. r26, r3
    beq fn_801500F4_L_80150188
    slwi r0, r27, 2
    addi r4, r1, 0x8
    lwzx r4, r4, r0
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_801500F4_L_80150188:
    stw r26, 0x8(r29)
    lwz r3, 0x8(r29)
    cmplwi r3, 0x0
    beq fn_801500F4_L_801501A0
    li r0, 0x7
    stw r0, 0x4(r3)
    fn_801500F4_L_801501A0:
    lwz r0, 0x8(r29)
    cmplwi r0, 0x0
    bne fn_801500F4_L_801501B4
    li r0, 0x1
    stb r0, 0x4(r29)
    fn_801500F4_L_801501B4:
    li r3, 0xff
    li r4, 0xff
    li r5, 0xff
    li r6, 0x0
    bl fn_8002CFB8
    li r3, 0x470
    bl FUN_8003b120
    mr. r28, r3
    beq fn_801500F4_L_801501F8
    lis r4, fn_80149214@ha
    lis r5, dtor_800869D0@ha
    addi r4, r4, fn_80149214@l
    li r6, 0x230
    addi r5, r5, dtor_800869D0@l
    li r7, 0x2
    bl __construct_new_array
    mr r28, r3
    fn_801500F4_L_801501F8:
    stw r28, 0xc(r29)
    li r0, 0x0
    lwz r3, 0xc(r29)
    stw r0, 0x18(r3)
    lwz r3, 0xc(r29)
    stw r0, 0x248(r3)
    bl fn_80293BBC
    mr r28, r3
    lwz r3, 0xc(r29)
    addi r4, r31, 0x3884
    addi r5, r28, 0x18
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lwz r3, 0xc(r29)
    addi r4, r31, 0x3894
    addi r5, r28, 0x2c
    addi r3, r3, 0x230
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    stw r30, 0x10(r29)
    li r0, 0x0
    cmpwi r30, 0x1
    stw r0, 0x14(r29)
    beq fn_801500F4_L_80150280
    bge fn_801500F4_L_80150268
    cmpwi r30, 0x0
    bge fn_801500F4_L_80150274
    b fn_801500F4_L_80150294
    fn_801500F4_L_80150268:
    cmpwi r30, 0x3
    bge fn_801500F4_L_80150294
    b fn_801500F4_L_8015028C
    fn_801500F4_L_80150274:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x18(r29)
    b fn_801500F4_L_80150294
    fn_801500F4_L_80150280:
    lfs f0, lbl_806D8068(r2)
    stfs f0, 0x18(r29)
    b fn_801500F4_L_80150294
    fn_801500F4_L_8015028C:
    lfs f0, lbl_806D8068(r2)
    stfs f0, 0x18(r29)
    fn_801500F4_L_80150294:
    mr r3, r29
    lmw r26, 0x18(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_801502AC(void) { /* 0x801502AC size:0x370 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r5, lbl_80363D30@ha
    stw r0, 0x34(r1)
    mulli r0, r4, 0x18
    stmw r25, 0x14(r1)
    addi r31, r5, lbl_80363D30@l
    mr r27, r3
    addi r3, r31, 0x31c0
    add r29, r3, r0
    lwzu r0, 0x4(r29)
    cmpwi r0, -0x1
    beq fn_801502AC_L_80150608
    slwi r30, r4, 2
    slwi r4, r0, 2
    add r26, r27, r30
    addi r3, r31, 0x638
    lwz r0, 0x28(r26)
    lwzx r28, r3, r4
    cmplwi r0, 0x0
    bne fn_801502AC_L_80150418
    li r3, 0x3090
    bl Alloc
    mr. r25, r3
    beq fn_801502AC_L_80150334
    mr r4, r28
    bl Scene3D_Init
    lis r3, lbl_80419EF8@ha
    lfs f1, lbl_806D806C(r2)
    addi r0, r3, lbl_80419EF8@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r25)
    stfs f1, 0x3088(r25)
    stfs f0, 0x308c(r25)
    fn_801502AC_L_80150334:
    stw r25, 0x28(r26)
    lwz r25, 0x28(r26)
    cmplwi r25, 0x0
    beq fn_801502AC_L_801503C4
    lwz r0, 0x4(r25)
    cmplwi r0, 0x0
    beq fn_801502AC_L_801503C4
    li r0, 0x1
    lfs f1, lbl_806D8064(r2)
    stb r0, 0x3084(r25)
    lfs f0, lbl_806D8068(r2)
    stfs f1, 0x308c(r25)
    stfs f0, 0x3088(r25)
    lwz r3, 0x2c(r25)
    cmplwi r3, 0x0
    bne fn_801502AC_L_8015037C
    li r4, 0x0
    b fn_801502AC_L_801503A8
    fn_801502AC_L_8015037C:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_801502AC_L_80150390
    li r4, 0x0
    b fn_801502AC_L_801503A8
    fn_801502AC_L_80150390:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_801502AC_L_801503A4
    li r4, 0x0
    b fn_801502AC_L_801503A8
    fn_801502AC_L_801503A4:
    lwz r4, 0x0(r3)
    fn_801502AC_L_801503A8:
    lwz r3, 0x4(r25)
    bl HSD_CObjAddAnim
    lwz r3, 0x4(r25)
    lfs f1, 0x308c(r25)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r25)
    bl HSD_CObjAnim
    fn_801502AC_L_801503C4:
    lwz r25, 0x28(r26)
    cmplwi r25, 0x0
    beq fn_801502AC_L_80150418
    lfs f0, lbl_806D806C(r2)
    lfs f1, 0x3088(r25)
    fcmpu cr0, f0, f1
    beq fn_801502AC_L_80150418
    lbz r0, 0x3084(r25)
    cmplwi r0, 0x0
    beq fn_801502AC_L_801503F8
    li r0, 0x0
    stb r0, 0x3084(r25)
    b fn_801502AC_L_80150404
    fn_801502AC_L_801503F8:
    lfs f0, 0x308c(r25)
    fadds f0, f0, f1
    stfs f0, 0x308c(r25)
    fn_801502AC_L_80150404:
    lwz r3, 0x4(r25)
    lfs f1, 0x308c(r25)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r25)
    bl HSD_CObjAnim
    fn_801502AC_L_80150418:
    add r25, r27, r30
    lwz r0, 0x7c(r25)
    cmplwi r0, 0x0
    bne fn_801502AC_L_80150448
    li r3, 0x28
    bl Alloc
    mr. r26, r3
    beq fn_801502AC_L_80150444
    mr r4, r28
    li r5, 0x1
    bl SceneModel_Init
    fn_801502AC_L_80150444:
    stw r26, 0x7c(r25)
    fn_801502AC_L_80150448:
    add r30, r27, r30
    lwz r0, 0xd0(r30)
    cmplwi r0, 0x0
    bne fn_801502AC_L_80150608
    li r3, 0x5c
    bl Alloc
    mr. r25, r3
    beq fn_801502AC_L_80150474
    mr r4, r28
    li r5, 0x0
    bl clNormal3D_Construct
    fn_801502AC_L_80150474:
    stw r25, 0xd0(r30)
    lwz r3, 0xd0(r30)
    cmplwi r3, 0x0
    beq fn_801502AC_L_8015049C
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lfs f2, lbl_806D8068(r2)
    fmr f3, f1
    fmr f4, f1
    bl clNormal3D_SetScale
    fn_801502AC_L_8015049C:
    lwz r3, 0xd0(r30)
    cmplwi r3, 0x0
    beq fn_801502AC_L_801504AC
    bl clNormal3D_Exec
    fn_801502AC_L_801504AC:
    lwz r0, 0x0(r29)
    cmpwi r0, 0x15
    bne fn_801502AC_L_80150608
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3938
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x394c
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3960
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3974
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3988
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x399c
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x39b0
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x39c4
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x39d8
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x39ec
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3a00
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    lwz r3, 0xd0(r30)
    addi r4, r31, 0x3a14
    bl ResolveJointByName
    mr r4, r3
    lwz r3, 0xd0(r30)
    li r5, 0x10
    bl JObj_Hide
    fn_801502AC_L_80150608:
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_8015061C(void) { /* 0x8015061C size:0x308 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r4, 0x6
    lis r6, lbl_80363D30@ha
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr r31, r3
    mr r26, r5
    addi r30, r6, lbl_80363D30@l
    beq fn_8015061C_L_801507A0
    bge fn_8015061C_L_80150658
    cmpwi r4, 0x4
    beq fn_8015061C_L_80150668
    bge fn_8015061C_L_801506D8
    b fn_8015061C_L_80150910
    fn_8015061C_L_80150658:
    cmpwi r4, 0x8
    beq fn_8015061C_L_801508BC
    bge fn_8015061C_L_80150910
    b fn_8015061C_L_8015087C
    fn_8015061C_L_80150668:
    mr r30, r31
    mr r29, r31
    li r27, 0x0
    fn_8015061C_L_80150674:
    lwz r3, 0x124(r30)
    cmplwi r3, 0x0
    beq fn_8015061C_L_80150688
    li r4, 0x1
    bl KartDriver_Dtor
    fn_8015061C_L_80150688:
    lwz r3, 0x150(r30)
    cmplwi r3, 0x0
    beq fn_8015061C_L_8015069C
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    fn_8015061C_L_8015069C:
    li r4, 0x0
    addi r0, r27, 0x38c
    stw r4, 0x124(r30)
    addi r3, r29, 0x17c
    stw r4, 0x150(r30)
    stbx r4, r31, r0
    bl PSMTXIdentity
    addi r27, r27, 0x1
    li r0, 0x0
    cmpwi r27, 0xb
    stw r0, g_playerRenderObj(r13)
    addi r30, r30, 0x4
    addi r29, r29, 0x30
    blt fn_8015061C_L_80150674
    b fn_8015061C_L_80150910
    fn_8015061C_L_801506D8:
    mr r28, r31
    addi r29, r30, 0x34d0
    li r27, 0x0
    fn_8015061C_L_801506E4:
    lwz r0, 0x0(r29)
    cmpw r26, r0
    bne fn_8015061C_L_80150784
    li r3, 0x384
    bl Alloc
    mr. r30, r3
    beq fn_8015061C_L_80150704
    bl KartDriver_New_Empty
    fn_8015061C_L_80150704:
    stw r30, 0x124(r31)
    lwz r3, 0x124(r31)
    cmplwi r3, 0x0
    beq fn_8015061C_L_80150730
    lwz r5, 0x0(r29)
    mr r7, r27
    addi r6, r28, 0x17c
    li r4, 0x0
    li r8, 0x0
    li r9, 0x2
    bl KartDriver_Init
    fn_8015061C_L_80150730:
    li r3, 0x154
    bl Alloc
    mr. r30, r3
    beq fn_8015061C_L_80150760
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lwz r5, 0x124(r31)
    li r7, 0x1
    fmr f2, f1
    lwz r6, 0x0(r29)
    fmr f3, f1
    bl TornadoEffect_Ctor
    fn_8015061C_L_80150760:
    stw r30, 0x150(r31)
    lfs f1, lbl_806D8064(r2)
    lwz r3, 0x150(r31)
    lfs f2, lbl_806D8068(r2)
    bl TireEffect_ResetSpin
    cmpwi r27, 0x0
    bne fn_8015061C_L_80150784
    lwz r0, 0x124(r31)
    stw r0, g_playerRenderObj(r13)
    fn_8015061C_L_80150784:
    addi r27, r27, 0x1
    addi r31, r31, 0x4
    cmpwi r27, 0xb
    addi r28, r28, 0x30
    addi r29, r29, 0xc
    blt fn_8015061C_L_801506E4
    b fn_8015061C_L_80150910
    fn_8015061C_L_801507A0:
    lwz r3, 0x1c(r31)
    cmplwi r3, 0x0
    beq fn_8015061C_L_801507B4
    li r4, 0x1
    bl CourseEnvironment_Dtor
    fn_8015061C_L_801507B4:
    li r0, 0x0
    li r3, 0x0
    stw r0, 0x1c(r31)
    li r4, 0x0
    stw r0, g_raceCamera(r13)
    bl SetActiveCamera
    lwz r3, 0x20(r31)
    cmplwi r3, 0x0
    beq fn_8015061C_L_801507F0
    beq fn_8015061C_L_801507F0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8015061C_L_801507F0:
    lwz r28, 0x24(r31)
    cmplwi r28, 0x0
    beq fn_8015061C_L_8015086C
    beq fn_8015061C_L_8015086C
    lis r3, 0x1
    lhz r4, 0x4(r28)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq fn_8015061C_L_80150824
    b fn_8015061C_L_80150834
    fn_8015061C_L_80150824:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r28)
    extrwi r0, r0, 8, 19
    fn_8015061C_L_80150834:
    cmpwi r0, 0x0
    beq fn_8015061C_L_8015086C
    cmplwi r28, 0x0
    beq fn_8015061C_L_8015086C
    lwz r4, 0x0(r28)
    mr r3, r28
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r28)
    mr r3, r28
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    fn_8015061C_L_8015086C:
    li r0, 0x0
    stw r0, 0x20(r31)
    stw r0, 0x24(r31)
    b fn_8015061C_L_80150910
    fn_8015061C_L_8015087C:
    li r3, 0x20
    bl Alloc
    mr. r26, r3
    beq fn_8015061C_L_80150898
    addi r4, r30, 0x3a28
    li r5, 0x0
    bl fn_8013D800
    fn_8015061C_L_80150898:
    stw r26, 0x574(r31)
    lfs f1, lbl_806D8064(r2)
    lwz r3, 0x574(r31)
    lfs f2, lbl_806D8068(r2)
    bl fn_8013D738
    lwz r3, 0x574(r31)
    lfs f1, lbl_806D8064(r2)
    bl fn_8013D4B0
    b fn_8015061C_L_80150910
    fn_8015061C_L_801508BC:
    slwi r28, r26, 2
    add r27, r31, r28
    lwz r0, 0x3f0(r27)
    cmplwi r0, 0x0
    bne fn_8015061C_L_80150910
    addi r29, r30, 0x3554
    lwzx r0, r29, r28
    cmpwi r0, -0x1
    beq fn_8015061C_L_80150910
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq fn_8015061C_L_80150900
    lwzx r4, r29, r28
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8015061C_L_80150900:
    stw r26, 0x3f0(r27)
    add r3, r31, r28
    li r0, 0x1
    stw r0, 0x4b0(r3)
    fn_8015061C_L_80150910:
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" unsigned char fn_80150924(unsigned char *o) {
    return o[0x10];
}

extern "C" asm void fn_8015092C(void) { /* 0x8015092C size:0x2B8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    beq fn_8015092C_L_80150BC0
    lis r3, lbl_80490010@ha
    addi r0, r3, lbl_80490010@l
    stw r0, 0x0(r30)
    lwz r3, 0x574(r30)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150984
    beq fn_8015092C_L_80150984
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8015092C_L_80150984:
    bl fn_8013DB9C
    lbz r0, 0x11(r30)
    cmplwi r0, 0x0
    beq fn_8015092C_L_801509B4
    lwz r3, 0x14(r30)
    cmpwi r3, -0x1
    beq fn_8015092C_L_801509B4
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_8015092C_L_801509B4
    lwz r3, 0x14(r30)
    bl fn_801909A4
    fn_8015092C_L_801509B4:
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq fn_8015092C_L_801509C8
    li r4, 0x1
    bl CourseEnvironment_Dtor
    fn_8015092C_L_801509C8:
    li r0, 0x0
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x20(r30)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150A00
    beq fn_8015092C_L_80150A00
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8015092C_L_80150A00:
    lwz r29, 0x24(r30)
    cmplwi r29, 0x0
    beq fn_8015092C_L_80150A7C
    beq fn_8015092C_L_80150A7C
    lis r3, 0x1
    lhz r4, 0x4(r29)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq fn_8015092C_L_80150A34
    b fn_8015092C_L_80150A44
    fn_8015092C_L_80150A34:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r29)
    extrwi r0, r0, 8, 19
    fn_8015092C_L_80150A44:
    cmpwi r0, 0x0
    beq fn_8015092C_L_80150A7C
    cmplwi r29, 0x0
    beq fn_8015092C_L_80150A7C
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    fn_8015092C_L_80150A7C:
    li r28, 0x0
    mr r29, r30
    fn_8015092C_L_80150A84:
    lwz r3, 0x28(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150AA8
    beq fn_8015092C_L_80150AA8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8015092C_L_80150AA8:
    lwz r3, 0x7c(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150ABC
    li r4, 0x1
    bl LObjList_Destroy
    fn_8015092C_L_80150ABC:
    lwz r3, 0xd0(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150AD0
    li r4, 0x1
    bl Object_DtorWithGXSync
    fn_8015092C_L_80150AD0:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x15
    blt fn_8015092C_L_80150A84
    li r28, 0x0
    mr r29, r30
    fn_8015092C_L_80150AE8:
    lwz r3, 0x124(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150AFC
    li r4, 0x1
    bl KartDriver_Dtor
    fn_8015092C_L_80150AFC:
    lwz r3, 0x150(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150B10
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    fn_8015092C_L_80150B10:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0xb
    blt fn_8015092C_L_80150AE8
    li r28, 0x0
    mr r29, r30
    fn_8015092C_L_80150B28:
    lwz r3, 0x3f0(r29)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150B3C
    li r4, 0x1
    bl Sprite_Destroy
    fn_8015092C_L_80150B3C:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x30
    blt fn_8015092C_L_80150B28
    li r3, 0x0
    bl SetCourseScene3D
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl SceneDrawList_Reset
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq fn_8015092C_L_80150B84
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8015092C_L_80150B84:
    li r0, 0x0
    stw r0, lbl_806D10AC(r13)
    bl fn_80121210
    bl clRom_PurgeAll
    li r3, 0x0
    bl SetResourceLoadingFlag
    cmplwi r30, 0x0
    beq fn_8015092C_L_80150BB0
    lis r3, lbl_8048FF80@ha
    addi r0, r3, lbl_8048FF80@l
    stw r0, 0x0(r30)
    fn_8015092C_L_80150BB0:
    extsh. r0, r31
    ble fn_8015092C_L_80150BC0
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_8015092C_L_80150BC0:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_80150BE4(VObj *p) {
    delete p;
}

extern "C" asm void fn_80150C1C(void) { /* 0x80150C1C size:0x618 */
    nofralloc
    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stfd f31, 0xe0(r1)
    psq_st f31, 0xe8(r1), 0, 0
    stmw r26, 0xc8(r1)
    mr r31, r3
    lwz r0, 0x8(r3)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    cmplwi r3, 0x0
    beq fn_80150C1C_L_80150EEC
    bl SetCourseScene3D
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80150C1C_L_80150EEC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80150C1C_L_80150C8C
    li r3, 0x0
    fn_80150C1C_L_80150C8C:
    bl clDrawMan_Buckets_Reset
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x7c(r3)
    bl LObjList_ApplyForCObj
    lwz r0, 0x8(r31)
    lis r3, lbl_80366EF0@ha
    addi r3, r3, lbl_80366EF0@l
    mulli r0, r0, 0x18
    add r3, r3, r0
    lbz r0, 0x9(r3)
    cmplwi r0, 0x0
    beq fn_80150C1C_L_80150CC8
    bl TransparentDraw_SortAndDispatch
    fn_80150C1C_L_80150CC8:
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    bl CObj_DebugVizPathFlush
    lwz r3, 0x1c(r31)
    cmplwi r3, 0x0
    beq fn_80150C1C_L_80150D14
    lwz r0, 0x8(r31)
    lis r4, lbl_80366EF0@ha
    addi r4, r4, lbl_80366EF0@l
    mulli r0, r0, 0x18
    add r4, r4, r0
    lbz r0, 0x8(r4)
    cmplwi r0, 0x0
    beq fn_80150C1C_L_80150D14
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x1c(r31)
    bl Subsystem36c_DispatchPass2_Timed
    fn_80150C1C_L_80150D14:
    lwz r0, 0x8(r31)
    li r26, 0x0
    cmpwi r0, 0x11
    bne fn_80150C1C_L_80150D28
    li r26, 0x1
    fn_80150C1C_L_80150D28:
    cmpwi r0, 0x13
    bne fn_80150C1C_L_80150D34
    li r26, 0x1
    fn_80150C1C_L_80150D34:
    mr r29, r31
    mr r28, r31
    clrlwi r30, r26, 24
    li r27, 0x0
    fn_80150C1C_L_80150D44:
    cmplwi r30, 0x1
    bne fn_80150C1C_L_80150DA8
    lfs f0, 0x398(r29)
    lfs f2, lbl_806D807C(r2)
    lfs f1, lbl_806D8068(r2)
    fadds f0, f0, f2
    stfs f0, 0x398(r29)
    lfs f0, 0x39c(r29)
    fadds f0, f0, f2
    stfs f0, 0x39c(r29)
    b fn_80150C1C_L_80150D7C
    fn_80150C1C_L_80150D70:
    lfs f0, 0x398(r29)
    fsubs f0, f0, f1
    stfs f0, 0x398(r29)
    fn_80150C1C_L_80150D7C:
    lfs f0, 0x398(r29)
    fcmpo cr0, f1, f0
    blt fn_80150C1C_L_80150D70
    lfs f1, lbl_806D8068(r2)
    b fn_80150C1C_L_80150D9C
    fn_80150C1C_L_80150D90:
    lfs f0, 0x39c(r29)
    fsubs f0, f0, f1
    stfs f0, 0x39c(r29)
    fn_80150C1C_L_80150D9C:
    lfs f0, 0x39c(r29)
    fcmpo cr0, f1, f0
    blt fn_80150C1C_L_80150D90
    fn_80150C1C_L_80150DA8:
    lwz r0, 0x124(r28)
    cmplwi r0, 0x0
    beq fn_80150C1C_L_80150E54
    addi r0, r27, 0x38c
    lbzx r0, r31, r0
    cmplwi r0, 0x0
    beq fn_80150C1C_L_80150E54
    lwz r3, 0x150(r28)
    bl KartItem_FlushRenderIfReady
    lwz r3, 0x124(r28)
    li r4, 0x2
    li r5, 0x1
    bl KartDriver_RenderTimed
    lwz r3, 0x150(r28)
    bl KartItem_FlushPendingRender
    lwz r3, 0x150(r28)
    bl KartItem_DispatchEffectRenderByState
    lwz r3, 0x124(r28)
    li r4, 0x3
    li r5, 0x1
    bl KartDriver_RenderTimed
    lwz r3, 0x150(r28)
    bl KartItem_FlushPendingRender_v2
    clrlwi r0, r26, 24
    cmplwi r0, 0x1
    bne fn_80150C1C_L_80150E1C
    lfs f1, 0x398(r29)
    lfs f2, 0x39c(r29)
    bl fn_802BD6AC
    fn_80150C1C_L_80150E1C:
    lwz r3, 0x150(r28)
    bl KartItem_DispatchEffectRenderByState
    lwz r3, 0x124(r28)
    li r4, 0x4
    li r5, 0x1
    bl KartDriver_RenderTimed
    lwz r3, 0x150(r28)
    bl KartItem_FlushPendingRender_v2
    clrlwi r0, r26, 24
    cmplwi r0, 0x1
    bne fn_80150C1C_L_80150E4C
    bl fn_802BD6C0
    fn_80150C1C_L_80150E4C:
    lwz r3, 0x150(r28)
    bl TornadoEffect_SubmitRender
    fn_80150C1C_L_80150E54:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xb
    addi r29, r29, 0x8
    blt fn_80150C1C_L_80150D44
    lwz r3, 0x8(r31)
    cmpwi r3, 0x14
    blt fn_80150C1C_L_80150E80
    lwz r0, 0xc(r31)
    cmpwi r0, 0xb4
    bge fn_80150C1C_L_80150E94
    fn_80150C1C_L_80150E80:
    slwi r0, r3, 2
    li r4, 0x7
    add r3, r31, r0
    lwz r3, 0xd0(r3)
    bl Object_RenderJObjTree
    fn_80150C1C_L_80150E94:
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80150C1C_L_80150EAC
    li r3, 0x0
    fn_80150C1C_L_80150EAC:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80150C1C_L_80150EC0
    li r3, 0x0
    fn_80150C1C_L_80150EC0:
    bl clDrawMan_Buckets_Dispatch
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    li r3, 0x0
    bl HSD_LObjDeleteCurrentAll
    fn_80150C1C_L_80150EEC:
    li r29, 0x0
    mr r28, r31
    fn_80150C1C_L_80150EF4:
    lwz r3, 0x3f0(r28)
    cmplwi r3, 0x0
    beq fn_80150C1C_L_80150F10
    lwz r0, 0x4b0(r28)
    cmpwi r0, 0x2
    bne fn_80150C1C_L_80150F10
    bl fn_801A0004
    fn_80150C1C_L_80150F10:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x30
    blt fn_80150C1C_L_80150EF4
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80150C1C_L_8015115C
    lwz r0, 0x8(r31)
    cmpwi r0, 0x4
    bne fn_80150C1C_L_80151048
    lwz r0, 0xc(r31)
    cmpwi r0, 0xd2
    blt fn_80150C1C_L_8015115C
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xbc(r1)
    lfd f2, lbl_806D80A0(r2)
    stw r0, 0xb8(r1)
    lfs f0, lbl_806D810C(r2)
    lfd f1, 0xb8(r1)
    lfs f3, lbl_806D8114(r2)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    fcmpo cr0, f0, f3
    cror eq, lt, eq
    bne fn_80150C1C_L_80150F88
    fdivs f0, f0, f3
    lfs f1, lbl_806D8110(r2)
    fmuls f31, f1, f0
    b fn_80150C1C_L_80150F9C
    fn_80150C1C_L_80150F88:
    fsubs f1, f0, f3
    lfs f2, lbl_806D8118(r2)
    lfs f0, lbl_806D8110(r2)
    fdivs f1, f1, f3
    fmadds f31, f2, f1, f0
    fn_80150C1C_L_80150F9C:
    lfs f0, lbl_806D8068(r2)
    fcmpo cr0, f31, f0
    ble fn_80150C1C_L_80150FAC
    fmr f31, f0
    fn_80150C1C_L_80150FAC:
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f31, f0
    cror eq, lt, eq
    beq fn_80150C1C_L_8015115C
    addi r3, r1, 0x60
    bl ResCtrl_Init
    lfs f0, lbl_806D8090(r2)
    addi r3, r2, -0x2308  /* lbl_806D7F58 */
    lfs f6, 0x4(r3)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f5, lbl_806D7F58(r2)
    lfs f0, lbl_806D8068(r2)
    li r0, 0x1
    stw r4, 0x68(r1)
    li r6, -0x100
    fctiwz f4, f1
    lfs f3, lbl_806D811C(r2)
    lfs f2, lbl_806D80A8(r2)
    addi r3, r1, 0x60
    lfs f1, lbl_806D8120(r2)
    li r4, 0x6
    stfd f4, 0xb8(r1)
    fmadds f2, f3, f5, f2
    fmadds f1, f3, f6, f1
    lwz r5, 0xbc(r1)
    stfs f5, 0x80(r1)
    rlwimi r6, r5, 0, 24, 31
    stfs f6, 0x84(r1)
    stw r6, 0x94(r1)
    stw r6, 0x98(r1)
    stw r6, 0x9c(r1)
    stw r6, 0xa0(r1)
    stb r0, 0x70(r1)
    stfs f2, 0x74(r1)
    stfs f1, 0x78(r1)
    stfs f0, 0x7c(r1)
    bl fn_8011FAFC
    b fn_80150C1C_L_8015115C
    fn_80150C1C_L_80151048:
    cmpwi r0, 0x14
    bne fn_80150C1C_L_8015115C
    lwz r0, 0xc(r31)
    cmpwi r0, 0x78
    blt fn_80150C1C_L_8015115C
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xbc(r1)
    lfd f2, lbl_806D80A0(r2)
    stw r0, 0xb8(r1)
    lfs f0, lbl_806D8094(r2)
    lfd f1, 0xb8(r1)
    lfs f3, lbl_806D8124(r2)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    fcmpo cr0, f0, f3
    cror eq, lt, eq
    bne fn_80150C1C_L_801510A0
    fdivs f0, f0, f3
    lfs f1, lbl_806D8110(r2)
    fmuls f31, f1, f0
    b fn_80150C1C_L_801510B4
    fn_80150C1C_L_801510A0:
    fsubs f1, f0, f3
    lfs f2, lbl_806D8118(r2)
    lfs f0, lbl_806D8110(r2)
    fdivs f1, f1, f3
    fmadds f31, f2, f1, f0
    fn_80150C1C_L_801510B4:
    lfs f0, lbl_806D8068(r2)
    fcmpo cr0, f31, f0
    ble fn_80150C1C_L_801510C4
    fmr f31, f0
    fn_80150C1C_L_801510C4:
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f31, f0
    cror eq, lt, eq
    beq fn_80150C1C_L_8015115C
    addi r3, r1, 0x8
    bl ResCtrl_Init
    lfs f0, lbl_806D8090(r2)
    addi r3, r2, -0x2308  /* lbl_806D7F58 */
    lfs f6, 0x4(r3)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f5, lbl_806D7F58(r2)
    lfs f0, lbl_806D8068(r2)
    li r0, 0x1
    stw r4, 0x10(r1)
    li r6, -0x100
    fctiwz f4, f1
    lfs f3, lbl_806D811C(r2)
    lfs f2, lbl_806D80A8(r2)
    addi r3, r1, 0x8
    lfs f1, lbl_806D8120(r2)
    li r4, 0x6
    stfd f4, 0xb8(r1)
    fmadds f2, f3, f5, f2
    fmadds f1, f3, f6, f1
    lwz r5, 0xbc(r1)
    stfs f5, 0x28(r1)
    rlwimi r6, r5, 0, 24, 31
    stfs f6, 0x2c(r1)
    stw r6, 0x3c(r1)
    stw r6, 0x40(r1)
    stw r6, 0x44(r1)
    stw r6, 0x48(r1)
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl fn_8011FAFC
    fn_80150C1C_L_8015115C:
    lwz r0, 0x8(r31)
    cmpwi r0, 0x14
    bne fn_80150C1C_L_801511F8
    lwz r0, 0xc(r31)
    cmpwi r0, 0xaa
    blt fn_80150C1C_L_801511F8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xbc(r1)
    lfd f2, lbl_806D80A0(r2)
    stw r0, 0xb8(r1)
    lfs f0, lbl_806D8128(r2)
    lfd f1, 0xb8(r1)
    lfs f3, lbl_806D80AC(r2)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    fcmpo cr0, f0, f3
    cror eq, lt, eq
    bne fn_80150C1C_L_801511B8
    fdivs f0, f0, f3
    lfs f1, lbl_806D8110(r2)
    fmuls f3, f1, f0
    b fn_80150C1C_L_801511CC
    fn_80150C1C_L_801511B8:
    fsubs f1, f0, f3
    lfs f2, lbl_806D8118(r2)
    lfs f0, lbl_806D8110(r2)
    fdivs f1, f1, f3
    fmadds f3, f2, f1, f0
    fn_80150C1C_L_801511CC:
    lfs f0, lbl_806D8068(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne fn_80150C1C_L_801511E0
    fmr f3, f0
    fn_80150C1C_L_801511E0:
    lfs f1, lbl_806D812C(r2)
    li r3, 0x6
    lfs f2, lbl_806D8130(r2)
    li r4, 0x2afd
    li r5, 0x0
    bl fn_801695E0
    fn_80150C1C_L_801511F8:
    li r3, 0x0
    bl fn_8011F994
    li r3, 0x4
    bl fn_8011F994
    li r3, 0x7
    bl fn_8013D940
    li r3, 0x6
    bl fn_8011F994
    psq_l f31, 0xe8(r1), 0, 0
    lfd f31, 0xe0(r1)
    lmw r26, 0xc8(r1)
    lwz r0, 0xf4(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr
}

extern "C" asm void fn_80151234(void) { /* 0x80151234 size:0xCD4 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stmw r24, 0x80(r1)
    mr r31, r3
    lis r3, lbl_80363D30@ha
    lbz r0, 0x10(r31)
    addi r30, r3, lbl_80363D30@l
    cmplwi r0, 0x0
    bne fn_80151234_L_80151278
    lwz r3, 0xc(r31)
    addi r0, r3, 0x1
    stw r0, 0xc(r31)
    fn_80151234_L_80151278:
    lwz r5, 0x8(r31)
    addi r3, r30, 0x31c0
    lwz r0, 0xc(r31)
    mulli r4, r5, 0x18
    lwzx r3, r3, r4
    cmpw r3, r0
    bgt fn_80151234_L_80151384
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bne fn_80151234_L_8015137C
    addi r0, r5, 0x1
    cmpwi r0, 0x15
    bge fn_80151234_L_80151370
    stw r0, 0x8(r31)
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1
    bne fn_80151234_L_801512C4
    li r3, 0x3
    bl SetSyncTarget
    fn_80151234_L_801512C4:
    li r0, 0x0
    stw r0, 0xc(r31)
    lwz r3, 0x574(r31)
    cmplwi r3, 0x0
    beq fn_80151234_L_801512F0
    beq fn_80151234_L_801512F0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80151234_L_801512F0:
    li r0, 0x0
    stw r0, 0x574(r31)
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    slwi r26, r0, 2
    add r27, r31, r26
    lwz r3, 0x28(r27)
    cmplwi r3, 0x0
    beq fn_80151234_L_8015132C
    beq fn_80151234_L_8015132C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80151234_L_8015132C:
    add r28, r31, r26
    lwz r3, 0x7c(r28)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151344
    li r4, 0x1
    bl LObjList_Destroy
    fn_80151234_L_80151344:
    add r26, r31, r26
    lwz r3, 0xd0(r26)
    cmplwi r3, 0x0
    beq fn_80151234_L_8015135C
    li r4, 0x1
    bl Object_DtorWithGXSync
    fn_80151234_L_8015135C:
    li r0, 0x0
    stw r0, 0x28(r27)
    stw r0, 0x7c(r28)
    stw r0, 0xd0(r26)
    b fn_80151234_L_80151384
    fn_80151234_L_80151370:
    li r0, 0x1
    stb r0, 0x10(r31)
    b fn_80151234_L_80151384
    fn_80151234_L_8015137C:
    li r0, 0x1
    stb r0, 0x10(r31)
    fn_80151234_L_80151384:
    bl PcbSyncTable_Ptr
    lwz r0, 0x8(r31)
    lbz r3, 0x18(r3)
    cmpwi r0, 0x1
    bne fn_80151234_L_801513DC
    lwz r0, g_currentSceneState(r13)
    cmpwi r0, 0x3
    bne fn_80151234_L_801513DC
    lbz r0, g_pcbSyncReady(r13)
    cmplwi r0, 0x0
    beq fn_80151234_L_801513C4
    cmpwi r3, 0x2
    bne fn_80151234_L_801513C4
    li r3, 0x4
    bl SetSyncTarget
    b fn_80151234_L_801513DC
    fn_80151234_L_801513C4:
    cmpwi r3, 0x1
    bne fn_80151234_L_80151EE4
    li r3, 0x4
    bl SetSyncTarget
    b fn_80151234_L_801513DC
    b fn_80151234_L_80151EE4
    fn_80151234_L_801513DC:
    lwz r0, 0x8(r31)
    addi r4, r30, 0x31c0
    addi r3, r2, -0x22F0  /* lbl_806D7F70 */
    li r6, 0x0
    mulli r0, r0, 0x18
    add r4, r4, r0
    lwz r0, 0x10(r4)
    mulli r0, r0, 0x3
    add r5, r3, r0
    lbzx r3, r3, r0
    lbz r4, 0x1(r5)
    lbz r5, 0x2(r5)
    bl fn_8002CFB8
    lwz r3, 0x8(r31)
    addi r4, r3, 0x1
    cmpwi r4, 0x15
    bge fn_80151234_L_80151444
    mulli r5, r3, 0x18
    addi r3, r30, 0x31c0
    lwz r0, 0xc(r31)
    lwzx r3, r3, r5
    subi r3, r3, 0xf
    cmpw r3, r0
    bgt fn_80151234_L_80151444
    mr r3, r31
    bl fn_801502AC
    fn_80151234_L_80151444:
    lwz r4, 0x8(r31)
    addi r3, r30, 0x31c0
    mulli r0, r4, 0x18
    add r3, r3, r0
    lwz r0, 0x4(r3)
    cmpwi r0, -0x1
    beq fn_80151234_L_801515C0
    slwi r0, r4, 2
    add r3, r31, r0
    lwz r4, 0x28(r3)
    cmplwi r4, 0x0
    beq fn_80151234_L_80151510
    lwz r3, 0xc(r31)
    lis r0, 0x4330
    stw r0, 0x68(r1)
    xoris r0, r3, 0x8000
    lfd f3, lbl_806D80A0(r2)
    stw r0, 0x6c(r1)
    lfs f1, 0x308c(r4)
    lfd f2, 0x68(r1)
    lfs f0, lbl_806D8064(r2)
    fsubs f2, f2, f3
    fcmpo cr0, f1, f0
    blt fn_80151234_L_801514B8
    fcmpo cr0, f2, f0
    blt fn_80151234_L_801514B8
    li r0, 0x1
    stb r0, 0x3084(r4)
    stfs f2, 0x308c(r4)
    fn_80151234_L_801514B8:
    lwz r0, 0x8(r31)
    lfs f0, lbl_806D806C(r2)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r26, 0x28(r3)
    lfs f1, 0x3088(r26)
    fcmpu cr0, f0, f1
    beq fn_80151234_L_80151510
    lbz r0, 0x3084(r26)
    cmplwi r0, 0x0
    beq fn_80151234_L_801514F0
    li r0, 0x0
    stb r0, 0x3084(r26)
    b fn_80151234_L_801514FC
    fn_80151234_L_801514F0:
    lfs f0, 0x308c(r26)
    fadds f0, f0, f1
    stfs f0, 0x308c(r26)
    fn_80151234_L_801514FC:
    lwz r3, 0x4(r26)
    lfs f1, 0x308c(r26)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r26)
    bl HSD_CObjAnim
    fn_80151234_L_80151510:
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xd0(r3)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151560
    lwz r4, 0xc(r31)
    lis r0, 0x4330
    stw r0, 0x68(r1)
    xoris r0, r4, 0x8000
    lfd f1, lbl_806D80A0(r2)
    stw r0, 0x6c(r1)
    lfd f0, 0x68(r1)
    fsubs f1, f0, f1
    bl Object_SetField8_AndDirty
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xd0(r3)
    bl clNormal3D_Exec
    fn_80151234_L_80151560:
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    bl SetCourseScene3D
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    cmplwi r3, 0x0
    beq fn_80151234_L_801515C0
    lwz r0, 0x20(r31)
    cmplwi r0, 0x0
    beq fn_80151234_L_801515C0
    addi r4, r1, 0x5c
    bl CObj_ApplyScissor
    lfs f4, lbl_806D8064(r2)
    lwz r3, 0x20(r31)
    fmr f6, f4
    lfs f1, 0x5c(r1)
    lfs f2, 0x60(r1)
    lfs f3, 0x64(r1)
    lfs f5, lbl_806D8068(r2)
    bl SceneRender_SetViewportRect
    fn_80151234_L_801515C0:
    lis r3, lbl_80598A60@ha
    addi r29, r3, lbl_80598A60@l
    b fn_80151234_L_8015193C
    fn_80151234_L_801515CC:
    mulli r0, r3, 0x14
    lwz r3, 0x578(r31)
    lwz r4, 0x8(r31)
    add r3, r3, r0
    lwz r0, 0x0(r3)
    cmpw r0, r4
    bge fn_80151234_L_801515F8
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    stw r0, 0x18(r31)
    b fn_80151234_L_8015193C
    fn_80151234_L_801515F8:
    cmpw r4, r0
    blt fn_80151234_L_8015194C
    lwz r0, 0x4(r3)
    lwz r4, 0xc(r31)
    cmpw r0, r4
    bge fn_80151234_L_80151620
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    stw r0, 0x18(r31)
    b fn_80151234_L_8015193C
    fn_80151234_L_80151620:
    cmpw r4, r0
    blt fn_80151234_L_8015194C
    lwz r4, 0x8(r3)
    cmpwi r4, 0x2
    beq fn_80151234_L_80151820
    bge fn_80151234_L_80151648
    cmpwi r4, 0x0
    beq fn_80151234_L_8015165C
    bge fn_80151234_L_8015170C
    b fn_80151234_L_80151930
    fn_80151234_L_80151648:
    cmpwi r4, 0x9
    bge fn_80151234_L_80151930
    cmpwi r4, 0x4
    bge fn_80151234_L_80151924
    b fn_80151234_L_801518B0
    fn_80151234_L_8015165C:
    lwz r24, 0xc(r3)
    mr r28, r31
    li r25, 0x0
    li r27, 0x0
    li r26, 0x3
    fn_80151234_L_80151670:
    lwz r3, 0x3f0(r28)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151694
    cmpw r25, r24
    beq fn_80151234_L_80151694
    li r4, 0x1
    bl Sprite_Destroy
    stw r27, 0x3f0(r28)
    stw r26, 0x4b0(r28)
    fn_80151234_L_80151694:
    addi r25, r25, 0x1
    addi r28, r28, 0x4
    cmpwi r25, 0x30
    blt fn_80151234_L_80151670
    slwi r26, r24, 2
    add r28, r31, r26
    lwz r0, 0x3f0(r28)
    cmplwi r0, 0x0
    bne fn_80151234_L_801516F4
    addi r27, r30, 0x3554
    lwzx r0, r27, r26
    cmpwi r0, -0x1
    beq fn_80151234_L_801516F4
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_80151234_L_801516E8
    lwzx r4, r27, r26
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_80151234_L_801516E8:
    stw r24, 0x3f0(r28)
    li r0, 0x1
    stw r0, 0x4b0(r28)
    fn_80151234_L_801516F4:
    lwz r0, 0x4b0(r28)
    cmpwi r0, 0x1
    bne fn_80151234_L_80151930
    li r0, 0x2
    stw r0, 0x4b0(r28)
    b fn_80151234_L_80151930
    fn_80151234_L_8015170C:
    lwz r0, 0xc(r3)
    clrlwi r3, r0, 24
    bl DrawEffect_SpawnByType
    mr. r26, r3
    beq fn_80151234_L_80151930
    lwz r4, 0x3614(r30)
    lwz r3, 0x3618(r30)
    lwz r0, 0x361c(r30)
    stw r4, 0x50(r1)
    stw r3, 0x54(r1)
    stw r0, 0x58(r1)
    lwz r0, 0x18(r31)
    lwz r4, 0x578(r31)
    mulli r3, r0, 0x14
    addi r0, r3, 0x10
    lwzx r4, r4, r0
    cmplwi r4, 0x0
    beq fn_80151234_L_801517EC
    lwz r0, 0x8(r31)
    slwi r3, r0, 2
    addi r0, r3, 0xd0
    lwzx r3, r31, r0
    cmplwi r3, 0x0
    beq fn_80151234_L_801517EC
    bl ResolveJointByName
    mr. r24, r3
    beq fn_80151234_L_801517EC
    bne fn_80151234_L_8015178C
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x47c
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80151234_L_8015178C:
    cmplwi r24, 0x0
    beq fn_80151234_L_801517D4
    bne fn_80151234_L_801517A8
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x25d
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80151234_L_801517A8:
    lwz r4, 0x14(r24)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80151234_L_801517C4
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80151234_L_801517C4
    li r3, 0x1
    fn_80151234_L_801517C4:
    clrlwi. r0, r3, 24
    beq fn_80151234_L_801517D4
    mr r3, r24
    bl HSD_JObjSetupMatrixSub
    fn_80151234_L_801517D4:
    addi r3, r1, 0x50
    addi r4, r24, 0x44
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r26, 0x8c
    addi r4, r1, 0x50
    bl Vec3_Copy
    fn_80151234_L_801517EC:
    lwz r0, 0x18(r31)
    lis r3, lbl_80419FB8@ha
    lwz r6, 0x578(r31)
    addi r4, r3, lbl_80419FB8@l
    mulli r5, r0, 0x14
    mr r3, r26
    addi r0, r5, 0xc
    lwzx r0, r6, r0
    slwi r0, r0, 2
    lwzx r12, r4, r0
    mtctr r12
    bctrl
    b fn_80151234_L_80151930
    fn_80151234_L_80151820:
    lbz r0, 0x11(r31)
    cmplwi r0, 0x0
    beq fn_80151234_L_80151930
    lwz r3, 0x14(r31)
    cmpwi r3, -0x1
    beq fn_80151234_L_80151854
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_80151234_L_8015184C
    lwz r3, 0x14(r31)
    bl fn_801909A4
    fn_80151234_L_8015184C:
    li r0, -0x1
    stw r0, 0x14(r31)
    fn_80151234_L_80151854:
    lwz r0, 0x18(r31)
    li r4, 0x0
    lwz r5, 0x578(r31)
    mulli r3, r0, 0x14
    addi r0, r3, 0xc
    lwzx r3, r5, r0
    bl ClSound_PlayBgmStream
    clrlwi. r0, r3, 24
    beq fn_80151234_L_80151930
    lwz r0, 0x18(r31)
    li r4, 0x64
    lwz r5, 0x578(r31)
    mulli r3, r0, 0x14
    addi r0, r3, 0xc
    lwzx r3, r5, r0
    bl clStream_setVolume
    lwz r0, 0x18(r31)
    lwz r4, 0x578(r31)
    mulli r3, r0, 0x14
    addi r0, r3, 0xc
    lwzx r0, r4, r0
    stw r0, 0x14(r31)
    b fn_80151234_L_80151930
    fn_80151234_L_801518B0:
    lbz r0, 0x11(r31)
    cmplwi r0, 0x0
    beq fn_80151234_L_80151930
    lwz r3, 0x570(r31)
    addis r0, r3, 0x1
    cmplwi r0, 0xffff
    beq fn_80151234_L_801518D8
    bl ClStream_Stop
    li r0, -0x1
    stw r0, 0x570(r31)
    fn_80151234_L_801518D8:
    lwz r0, 0x18(r31)
    lwz r4, 0x578(r31)
    mulli r3, r0, 0x14
    addi r0, r3, 0xc
    lwzx r3, r4, r0
    bl fn_801B3A50
    lwz r3, 0x8(r3)
    li r4, 0x0
    li r5, 0x0
    bl ClStream_PlayMono
    stw r3, 0x570(r31)
    lwz r3, 0x570(r31)
    addis r0, r3, 0x1
    cmplwi r0, 0xffff
    beq fn_80151234_L_80151930
    lbz r0, 0x31(r29)
    clrlslwi r4, r0, 25, 1
    bl fn_80194AE0
    b fn_80151234_L_80151930
    fn_80151234_L_80151924:
    lwz r5, 0xc(r3)
    mr r3, r31
    bl fn_8015061C
    fn_80151234_L_80151930:
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    stw r0, 0x18(r31)
    fn_80151234_L_8015193C:
    lwz r3, 0x18(r31)
    lwz r0, 0x57c(r31)
    cmpw r3, r0
    blt fn_80151234_L_801515CC
    fn_80151234_L_8015194C:
    lwz r3, 0x570(r31)
    addis r0, r3, 0x1
    cmplwi r0, 0xffff
    beq fn_80151234_L_80151978
    bl ClStream_IsActive
    clrlwi. r0, r3, 24
    bne fn_80151234_L_80151978
    lwz r3, 0x570(r31)
    bl ClStream_Stop
    li r0, -0x1
    stw r0, 0x570(r31)
    fn_80151234_L_80151978:
    li r27, 0x0
    mr r26, r31
    fn_80151234_L_80151980:
    lwz r3, 0x124(r26)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151994
    lwz r3, 0x304(r3)
    bl ItemEffectBus_SnapshotAndFullReset
    fn_80151234_L_80151994:
    addi r27, r27, 0x1
    addi r26, r26, 0x4
    cmpwi r27, 0xb
    blt fn_80151234_L_80151980
    mr r29, r31
    mr r27, r31
    addi r28, r30, 0x34d0
    li r26, 0x0
    fn_80151234_L_801519B4:
    lwz r0, 0x124(r29)
    cmplwi r0, 0x0
    beq fn_80151234_L_80151B7C
    lwz r0, 0x8(r31)
    li r24, 0x0
    slwi r3, r0, 2
    addi r0, r3, 0xd0
    lwzx r3, r31, r0
    cmplwi r3, 0x0
    beq fn_80151234_L_801519E8
    lwz r4, 0x4(r28)
    bl ResolveJointByName
    mr r24, r3
    fn_80151234_L_801519E8:
    cmplwi r24, 0x0
    beq fn_80151234_L_80151B60
    addi r3, r1, 0x44
    addi r4, r27, 0x17c
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r27, 0x17c
    bl Mtx44_GetYawOfPosZ_Padded
    fmr f31, f1
    cmplwi r24, 0x0
    bne fn_80151234_L_80151A20
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x47c
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80151234_L_80151A20:
    cmplwi r24, 0x0
    beq fn_80151234_L_80151A68
    bne fn_80151234_L_80151A3C
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x25d
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80151234_L_80151A3C:
    lwz r4, 0x14(r24)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80151234_L_80151A58
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80151234_L_80151A58
    li r3, 0x1
    fn_80151234_L_80151A58:
    clrlwi. r0, r3, 24
    beq fn_80151234_L_80151A68
    mr r3, r24
    bl HSD_JObjSetupMatrixSub
    fn_80151234_L_80151A68:
    addi r3, r24, 0x44
    addi r4, r27, 0x17c
    bl PSMTXCopy
    addi r3, r1, 0x38
    addi r4, r27, 0x17c
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r27, 0x17c
    bl Mtx44_GetYawOfPosZ_Padded
    fmr f30, f1
    addi r3, r1, 0x44
    addi r4, r1, 0x38
    bl fn_800D3184
    fmr f0, f1
    fsubs f1, f30, f31
    fmr f30, f0
    bl BuildOrientationFromYaw
    lfs f3, lbl_806D8144(r2)
    fmr f2, f30
    lfs f0, lbl_806D80CC(r2)
    li r4, 0x0
    fdivs f1, f1, f3
    lwz r3, 0x124(r29)
    fdivs f1, f1, f0
    bl RenderObj_ItemStateMachine_Timed
    lwz r0, 0x8(r31)
    addi r3, r30, 0x31c0
    lwz r5, 0xc(r31)
    li r24, 0x0
    mulli r4, r0, 0x18
    addi r0, r4, 0xc
    lwzx r0, r3, r0
    cmpw r5, r0
    bge fn_80151234_L_80151AF0
    li r24, 0x20
    fn_80151234_L_80151AF0:
    lwz r3, 0x150(r29)
    lfs f1, lbl_806D8064(r2)
    lfs f2, lbl_806D8068(r2)
    bl TornadoEffect_SetScalePairB0BC
    lwz r3, 0x150(r29)
    li r4, 0x0
    bl TornadoEffect_SetFlagB4
    lwz r3, 0x150(r29)
    mr r4, r24
    mr r5, r24
    bl TornadoEffect_SetColorPairC8CC
    lwz r3, 0x150(r29)
    li r4, 0x0
    bl TornadoEffect_Tick
    lwz r3, 0x124(r29)
    lwz r0, 0x1f8(r3)
    cmpwi r0, 0xa
    bne fn_80151234_L_80151B50
    li r4, 0x0
    bl KartDriver_GetJointByIdx
    bl Mtx44_GetPitchOfPosZ_Padded
    fneg f1, f1
    lwz r3, 0x124(r29)
    bl KartDriver_TickAction_79268_AndSetSlot5aEulerZ
    fn_80151234_L_80151B50:
    addi r0, r26, 0x38c
    li r3, 0x1
    stbx r3, r31, r0
    b fn_80151234_L_80151B7C
    fn_80151234_L_80151B60:
    addi r0, r26, 0x38c
    li r3, 0x0
    stbx r3, r31, r0
    li r4, 0x0
    li r5, 0x0
    lwz r3, 0x150(r29)
    bl TornadoEffect_SetColorPairC8CC
    fn_80151234_L_80151B7C:
    addi r26, r26, 0x1
    addi r28, r28, 0xc
    cmpwi r26, 0xb
    addi r27, r27, 0x30
    addi r29, r29, 0x4
    blt fn_80151234_L_801519B4
    li r27, 0x0
    mr r26, r31
    fn_80151234_L_80151B9C:
    lwz r3, 0x124(r26)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151BB0
    lwz r3, 0x304(r3)
    bl ItemEffectBus_TickTornadoCooldown
    fn_80151234_L_80151BB0:
    addi r27, r27, 0x1
    addi r26, r26, 0x4
    cmpwi r27, 0xb
    blt fn_80151234_L_80151B9C
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r0, 0x28(r3)
    cmplwi r0, 0x0
    beq fn_80151234_L_80151BE8
    lwz r3, 0x1c(r31)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151BE8
    bl CourseEnvironment_UpdateAndCullZones_Timed
    fn_80151234_L_80151BE8:
    lwz r7, 0x3620(r30)
    lwz r6, 0x3624(r30)
    lwz r5, 0x3628(r30)
    lwz r4, 0x362c(r30)
    lwz r3, 0x3630(r30)
    lwz r0, 0x3634(r30)
    stw r7, 0x2c(r1)
    stw r6, 0x30(r1)
    stw r5, 0x34(r1)
    stw r4, 0x20(r1)
    stw r3, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0x8(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151C50
    addi r4, r1, 0x2c
    bl CObj_LoadProjMatrix
    lwz r0, 0x8(r31)
    addi r4, r1, 0x20
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x28(r3)
    bl CObj_ApplyScissor
    fn_80151234_L_80151C50:
    bl ItemObjectManager_Update
    lwz r9, 0x20(r1)
    addi r3, r1, 0x14
    lwz r8, 0x24(r1)
    addi r4, r1, 0x8
    lwz r7, 0x28(r1)
    lwz r6, 0x2c(r1)
    lwz r5, 0x30(r1)
    lwz r0, 0x34(r1)
    stw r9, 0x8(r1)
    stw r8, 0xc(r1)
    stw r7, 0x10(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl VfxSlotMgr_Update
    bl fn_801A1280
    li r27, 0x0
    mr r26, r31
    fn_80151234_L_80151C9C:
    lwz r3, 0x3f0(r26)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151CEC
    lwz r0, 0x4b0(r26)
    cmpwi r0, 0x2
    bne fn_80151234_L_80151CEC
    lfs f1, lbl_806D8098(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne fn_80151234_L_80151CEC
    lwz r0, 0x8(r31)
    cmpwi r0, 0x14
    beq fn_80151234_L_80151CEC
    lwz r3, 0x3f0(r26)
    li r4, 0x1
    bl Sprite_Destroy
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x3f0(r26)
    stw r0, 0x4b0(r26)
    fn_80151234_L_80151CEC:
    addi r27, r27, 0x1
    addi r26, r26, 0x4
    cmpwi r27, 0x30
    blt fn_80151234_L_80151C9C
    lwz r3, 0x574(r31)
    cmplwi r3, 0x0
    beq fn_80151234_L_80151EE4
    lwz r0, 0x8(r31)
    lfs f1, lbl_806D80B8(r2)
    cmpwi r0, 0x10
    lfs f2, lbl_806D8070(r2)
    lfs f31, lbl_806D80BC(r2)
    lfs f30, lbl_806D8064(r2)
    bne fn_80151234_L_80151DEC
    lwz r5, 0xc(r31)
    cmpwi r5, 0x0
    blt fn_80151234_L_80151D60
    cmpwi r5, 0x28
    bgt fn_80151234_L_80151D60
    xoris r4, r5, 0x8000
    lis r0, 0x4330
    stw r4, 0x6c(r1)
    lfd f1, lbl_806D80A0(r2)
    stw r0, 0x68(r1)
    lfs f3, lbl_806D8148(r2)
    lfd f0, 0x68(r1)
    fsubs f0, f0, f1
    fmuls f30, f3, f0
    b fn_80151234_L_80151D9C
    fn_80151234_L_80151D60:
    cmpwi r5, 0x28
    blt fn_80151234_L_80151D9C
    cmpwi r5, 0x3a
    bgt fn_80151234_L_80151D9C
    xoris r4, r5, 0x8000
    lis r0, 0x4330
    stw r4, 0x6c(r1)
    lfd f3, lbl_806D80A0(r2)
    stw r0, 0x68(r1)
    lfs f0, lbl_806D8150(r2)
    lfd f1, 0x68(r1)
    lfs f4, lbl_806D814C(r2)
    fsubs f1, f1, f3
    fsubs f0, f1, f0
    fmuls f30, f4, f0
    fn_80151234_L_80151D9C:
    cmpwi r5, 0x0
    lfs f1, lbl_806D80B8(r2)
    blt fn_80151234_L_80151DDC
    cmpwi r5, 0x14
    bgt fn_80151234_L_80151DDC
    xoris r4, r5, 0x8000
    lis r0, 0x4330
    stw r4, 0x6c(r1)
    lfd f3, lbl_806D80A0(r2)
    stw r0, 0x68(r1)
    lfs f4, lbl_806D8158(r2)
    lfd f2, 0x68(r1)
    lfs f0, lbl_806D8154(r2)
    fsubs f2, f2, f3
    fmadds f2, f4, f2, f0
    b fn_80151234_L_80151E78
    fn_80151234_L_80151DDC:
    cmpwi r5, 0x14
    blt fn_80151234_L_80151E78
    lfs f2, lbl_806D815C(r2)
    b fn_80151234_L_80151E78
    fn_80151234_L_80151DEC:
    cmpwi r0, 0x11
    bne fn_80151234_L_80151E78
    lwz r0, 0xc(r31)
    cmpwi r0, 0x0
    blt fn_80151234_L_80151E64
    cmpwi r0, 0x14
    bgt fn_80151234_L_80151E64
    xoris r4, r0, 0x8000
    lis r0, 0x4330
    stw r4, 0x6c(r1)
    lfd f6, lbl_806D80A0(r2)
    stw r0, 0x68(r1)
    lfs f4, lbl_806D8160(r2)
    lfd f0, 0x68(r1)
    stw r4, 0x74(r1)
    fsubs f3, f0, f6
    lfs f5, lbl_806D8164(r2)
    stw r0, 0x70(r1)
    lfs f2, lbl_806D815C(r2)
    lfd f0, 0x70(r1)
    fmadds f1, f4, f3, f1
    stw r4, 0x7c(r1)
    fsubs f4, f0, f6
    lfs f3, lbl_806D8168(r2)
    stw r0, 0x78(r1)
    lfd f0, 0x78(r1)
    fmadds f2, f5, f4, f2
    fsubs f0, f0, f6
    fmadds f31, f3, f0, f31
    b fn_80151234_L_80151E78
    fn_80151234_L_80151E64:
    cmpwi r0, 0x14
    blt fn_80151234_L_80151E78
    lfs f1, lbl_806D816C(r2)
    lfs f2, lbl_806D8170(r2)
    lfs f31, lbl_806D8174(r2)
    fn_80151234_L_80151E78:
    lfs f0, lbl_806D8178(r2)
    fmuls f31, f31, f0
    bl fn_8013D660
    lfs f1, lbl_806D8064(r2)
    lwz r3, 0x574(r31)
    fmr f3, f1
    lfs f2, lbl_806D817C(r2)
    bl fn_8013D634
    lfs f1, lbl_806D8064(r2)
    fmr f2, f30
    lwz r3, 0x574(r31)
    fmr f3, f1
    bl fn_8013D59C
    lfs f0, lbl_806D8180(r2)
    lwz r3, 0x574(r31)
    fmuls f1, f31, f0
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lwz r3, 0x574(r31)
    lfs f1, lbl_806D8068(r2)
    bl fn_8013D4B0
    lwz r3, 0x574(r31)
    bl fn_8013D704
    lwz r3, 0x574(r31)
    li r4, 0x7
    bl fn_8013DAC8
    fn_80151234_L_80151EE4:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    lmw r24, 0x80(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

extern "C" asm void fn_80151F08(void) { /* 0x80151F08 size:0x7BC */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stmw r25, 0x14(r1)
    lis r7, lbl_8048FF80@ha
    lis r6, lbl_80490010@ha
    mr r26, r3
    lis r8, lbl_8048F178@ha
    addi r3, r7, lbl_8048FF80@l
    addi r0, r6, lbl_80490010@l
    stw r3, 0x0(r26)
    mr r27, r4
    mr r29, r5
    addi r28, r8, lbl_8048F178@l
    stw r0, 0x0(r26)
    bl DrawManager_GetOrCreate
    bl fn_80121210
    bl DMAChannelManager_Init
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    bl fn_80169E20
    cmpwi r3, 0x2
    beq fn_80151F08_L_80151FB8
    bge fn_80151F08_L_80151FCC
    cmpwi r3, 0x1
    bge fn_80151F08_L_80151F80
    b fn_80151F08_L_80151FCC
    fn_80151F08_L_80151F80:
    bl IsCardValid
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_80151F08_L_80151FA4
    addi r3, r28, 0x444
    li r0, 0x33
    stw r3, 0x578(r26)
    stw r0, 0x57c(r26)
    b fn_80151F08_L_80151FDC
    fn_80151F08_L_80151FA4:
    addi r3, r28, 0x840
    li r0, 0x2e
    stw r3, 0x578(r26)
    stw r0, 0x57c(r26)
    b fn_80151F08_L_80151FDC
    fn_80151F08_L_80151FB8:
    addi r3, r28, 0x840
    li r0, 0x2e
    stw r3, 0x578(r26)
    stw r0, 0x57c(r26)
    b fn_80151F08_L_80151FDC
    fn_80151F08_L_80151FCC:
    addi r3, r28, 0x48
    li r0, 0x33
    stw r3, 0x578(r26)
    stw r0, 0x57c(r26)
    fn_80151F08_L_80151FDC:
    cmpwi r29, -0x1
    bge fn_80151F08_L_80151FE8
    li r29, -0x1
    fn_80151F08_L_80151FE8:
    cmpwi r29, 0x14
    ble fn_80151F08_L_80151FF4
    li r29, 0x14
    fn_80151F08_L_80151FF4:
    li r0, -0x1
    cmpwi r29, 0x0
    stw r0, 0xc(r26)
    li r0, 0x0
    stb r0, 0x10(r26)
    bge fn_80151F08_L_80152018
    stw r0, 0x4(r26)
    stw r0, 0x8(r26)
    b fn_80151F08_L_80152024
    fn_80151F08_L_80152018:
    li r0, 0x1
    stw r0, 0x4(r26)
    stw r29, 0x8(r26)
    fn_80151F08_L_80152024:
    li r4, 0x0
    li r6, 0xa
    stw r4, 0x18(r26)
    li r3, -0x1
    subfic r0, r6, 0xb
    slwi r5, r6, 2
    stb r27, 0x11(r26)
    stw r3, 0x14(r26)
    stw r4, 0x1c(r26)
    stw r4, 0x20(r26)
    stw r4, 0x24(r26)
    stw r4, 0x28(r26)
    stw r4, 0x2c(r26)
    stw r4, 0x30(r26)
    stw r4, 0x34(r26)
    stw r4, 0x38(r26)
    stw r4, 0x3c(r26)
    stw r4, 0x40(r26)
    stw r4, 0x44(r26)
    stw r4, 0x48(r26)
    stw r4, 0x4c(r26)
    stw r4, 0x50(r26)
    stw r4, 0x54(r26)
    stw r4, 0x58(r26)
    stw r4, 0x5c(r26)
    stw r4, 0x60(r26)
    stw r4, 0x64(r26)
    stw r4, 0x68(r26)
    stw r4, 0x6c(r26)
    stw r4, 0x70(r26)
    stw r4, 0x74(r26)
    stw r4, 0x78(r26)
    stw r4, 0x7c(r26)
    stw r4, 0x80(r26)
    stw r4, 0x84(r26)
    stw r4, 0x88(r26)
    stw r4, 0x8c(r26)
    stw r4, 0x90(r26)
    stw r4, 0x94(r26)
    stw r4, 0x98(r26)
    stw r4, 0x9c(r26)
    stw r4, 0xa0(r26)
    stw r4, 0xa4(r26)
    stw r4, 0xa8(r26)
    stw r4, 0xac(r26)
    stw r4, 0xb0(r26)
    stw r4, 0xb4(r26)
    stw r4, 0xb8(r26)
    stw r4, 0xbc(r26)
    stw r4, 0xc0(r26)
    stw r4, 0xc4(r26)
    stw r4, 0xc8(r26)
    stw r4, 0xcc(r26)
    stw r4, 0xd0(r26)
    stw r4, 0xd4(r26)
    stw r4, 0xd8(r26)
    stw r4, 0xdc(r26)
    stw r4, 0xe0(r26)
    stw r4, 0xe4(r26)
    stw r4, 0xe8(r26)
    stw r4, 0xec(r26)
    stw r4, 0xf0(r26)
    stw r4, 0xf4(r26)
    stw r4, 0xf8(r26)
    stw r4, 0xfc(r26)
    stw r4, 0x100(r26)
    stw r4, 0x104(r26)
    stw r4, 0x108(r26)
    stw r4, 0x10c(r26)
    stw r4, 0x110(r26)
    stw r4, 0x114(r26)
    stw r4, 0x118(r26)
    stw r4, 0x11c(r26)
    stw r4, 0x120(r26)
    stw r4, 0x124(r26)
    stw r4, 0x128(r26)
    stw r4, 0x12c(r26)
    stw r4, 0x130(r26)
    stw r4, 0x134(r26)
    stw r4, 0x138(r26)
    stw r4, 0x13c(r26)
    stw r4, 0x140(r26)
    stw r4, 0x144(r26)
    stw r4, 0x148(r26)
    mtctr r0
    cmpwi r6, 0xb
    bge fn_80151F08_L_80152190
    fn_80151F08_L_80152180:
    addi r0, r5, 0x124
    addi r5, r5, 0x4
    stwx r4, r26, r0
    bdnz fn_80151F08_L_80152180
    fn_80151F08_L_80152190:
    li r3, 0x0
    li r5, 0xa
    stw r3, 0x150(r26)
    subfic r0, r5, 0xb
    slwi r4, r5, 2
    stw r3, 0x154(r26)
    stw r3, 0x158(r26)
    stw r3, 0x15c(r26)
    stw r3, 0x160(r26)
    stw r3, 0x164(r26)
    stw r3, 0x168(r26)
    stw r3, 0x16c(r26)
    stw r3, 0x170(r26)
    stw r3, 0x174(r26)
    mtctr r0
    cmpwi r5, 0xb
    bge fn_80151F08_L_801521E4
    fn_80151F08_L_801521D4:
    addi r0, r4, 0x150
    addi r4, r4, 0x4
    stwx r3, r26, r0
    bdnz fn_80151F08_L_801521D4
    fn_80151F08_L_801521E4:
    li r0, 0x3
    li r10, 0x0
    mtctr r0
    fn_80151F08_L_801521F0:
    addi r9, r10, 0x3f0
    li r11, 0x0
    stwx r11, r26, r9
    addi r8, r10, 0x3f4
    addi r7, r10, 0x3f8
    addi r6, r10, 0x3fc
    stwx r11, r26, r8
    addi r5, r10, 0x400
    addi r4, r10, 0x404
    addi r3, r10, 0x408
    stwx r11, r26, r7
    addi r0, r10, 0x40c
    addi r9, r10, 0x410
    addi r8, r10, 0x414
    stwx r11, r26, r6
    addi r7, r10, 0x418
    addi r6, r10, 0x41c
    stwx r11, r26, r5
    addi r5, r10, 0x420
    stwx r11, r26, r4
    addi r4, r10, 0x424
    stwx r11, r26, r3
    addi r3, r10, 0x428
    stwx r11, r26, r0
    addi r0, r10, 0x42c
    addi r10, r10, 0x40
    stwx r11, r26, r9
    stwx r11, r26, r8
    stwx r11, r26, r7
    stwx r11, r26, r6
    stwx r11, r26, r5
    stwx r11, r26, r4
    stwx r11, r26, r3
    stwx r11, r26, r0
    bdnz fn_80151F08_L_801521F0
    li r0, 0x3
    mtctr r0
    fn_80151F08_L_80152284:
    addi r9, r11, 0x4b0
    li r10, 0x0
    stwx r10, r26, r9
    addi r8, r11, 0x4b4
    addi r7, r11, 0x4b8
    addi r6, r11, 0x4bc
    stwx r10, r26, r8
    addi r5, r11, 0x4c0
    addi r4, r11, 0x4c4
    addi r3, r11, 0x4c8
    stwx r10, r26, r7
    addi r0, r11, 0x4cc
    addi r9, r11, 0x4d0
    addi r8, r11, 0x4d4
    stwx r10, r26, r6
    addi r7, r11, 0x4d8
    addi r6, r11, 0x4dc
    stwx r10, r26, r5
    addi r5, r11, 0x4e0
    stwx r10, r26, r4
    addi r4, r11, 0x4e4
    stwx r10, r26, r3
    addi r3, r11, 0x4e8
    stwx r10, r26, r0
    addi r0, r11, 0x4ec
    addi r11, r11, 0x40
    stwx r10, r26, r9
    stwx r10, r26, r8
    stwx r10, r26, r7
    stwx r10, r26, r6
    stwx r10, r26, r5
    stwx r10, r26, r4
    stwx r10, r26, r3
    stwx r10, r26, r0
    bdnz fn_80151F08_L_80152284
    li r3, 0x8
    li r0, 0x1
    stw r3, g_cupId(r13)
    li r3, 0x37c
    stw r0, g_longRoundFlag(r13)
    stw r10, g_courseVariantIdx(r13)
    bl Alloc
    mr. r27, r3
    beq fn_80151F08_L_80152338
    bl InputManager_Init
    fn_80151F08_L_80152338:
    stw r27, 0x1c(r26)
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, 0x24(r26)
    li r3, 0x2c
    bl Alloc
    mr. r27, r3
    beq fn_80151F08_L_80152370
    lfs f1, lbl_806D80C0(r2)
    li r4, 0x200
    lfs f2, lbl_806D8184(r2)
    li r5, 0x200
    lwz r6, 0x24(r26)
    bl Camera_Create
    fn_80151F08_L_80152370:
    stw r27, 0x20(r26)
    li r3, 0x0
    lwz r4, 0x20(r26)
    bl SetActiveCamera
    lwz r0, 0x20(r26)
    li r27, 0x0
    lis r3, lbl_80367200@ha
    lfs f31, lbl_806D8064(r2)
    stw r0, g_raceCamera(r13)
    addi r28, r3, lbl_80367200@l
    mr r31, r27
    mr r30, r27
    mr r29, r27
    fn_80151F08_L_801523A4:
    addi r0, r31, 0x124
    li r5, 0x0
    stwx r5, r26, r0
    addi r4, r31, 0x150
    addi r3, r30, 0x17c
    addi r0, r27, 0x38c
    stwx r5, r26, r4
    add r3, r26, r3
    stbx r5, r26, r0
    bl PSMTXIdentity
    addi r3, r29, 0x398
    lbz r0, 0x8(r28)
    stfsx f31, r26, r3
    addi r3, r29, 0x39c
    cmplwi r0, 0x0
    stfsx f31, r26, r3
    beq fn_80151F08_L_80152490
    li r3, 0x384
    bl Alloc
    mr. r25, r3
    beq fn_80151F08_L_801523FC
    bl KartDriver_New_Empty
    fn_80151F08_L_801523FC:
    addi r0, r31, 0x124
    stwx r25, r26, r0
    lwzx r3, r26, r0
    cmplwi r3, 0x0
    beq fn_80151F08_L_80152430
    addi r6, r30, 0x17c
    lwz r5, 0x0(r28)
    mr r7, r27
    li r4, 0x0
    add r6, r26, r6
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_Init
    fn_80151F08_L_80152430:
    li r3, 0x154
    bl Alloc
    mr. r25, r3
    beq fn_80151F08_L_80152464
    lfs f1, lbl_806D8064(r2)
    addi r0, r31, 0x124
    lwzx r5, r26, r0
    li r4, 0x0
    fmr f2, f1
    lwz r6, 0x0(r28)
    fmr f3, f1
    li r7, 0x1
    bl TornadoEffect_Ctor
    fn_80151F08_L_80152464:
    addi r0, r31, 0x150
    lfs f1, lbl_806D8064(r2)
    stwx r25, r26, r0
    lfs f2, lbl_806D8068(r2)
    lwzx r3, r26, r0
    bl TireEffect_ResetSpin
    cmpwi r27, 0x0
    bne fn_80151F08_L_80152490
    addi r0, r31, 0x124
    lwzx r0, r26, r0
    stw r0, g_playerRenderObj(r13)
    fn_80151F08_L_80152490:
    addi r27, r27, 0x1
    addi r30, r30, 0x30
    cmpwi r27, 0xb
    addi r29, r29, 0x8
    addi r28, r28, 0xc
    addi r31, r31, 0x4
    blt fn_80151F08_L_801523A4
    li r0, 0x6
    li r28, 0x0
    mtctr r0
    fn_80151F08_L_801524B8:
    addi r0, r28, 0x3f0
    li r3, 0x0
    stwx r3, r26, r0
    addi r0, r28, 0x4b0
    addi r5, r28, 0x3f4
    addi r4, r28, 0x4b4
    stwx r3, r26, r0
    addi r0, r28, 0x3f8
    addi r27, r28, 0x4b8
    addi r12, r28, 0x3fc
    stwx r3, r26, r5
    addi r11, r28, 0x4bc
    addi r10, r28, 0x400
    addi r9, r28, 0x4c0
    stwx r3, r26, r4
    addi r8, r28, 0x404
    addi r7, r28, 0x4c4
    addi r6, r28, 0x408
    stwx r3, r26, r0
    addi r5, r28, 0x4c8
    addi r4, r28, 0x40c
    addi r0, r28, 0x4cc
    stwx r3, r26, r27
    addi r28, r28, 0x20
    stwx r3, r26, r12
    stwx r3, r26, r11
    stwx r3, r26, r10
    stwx r3, r26, r9
    stwx r3, r26, r8
    stwx r3, r26, r7
    stwx r3, r26, r6
    stwx r3, r26, r5
    stwx r3, r26, r4
    stwx r3, r26, r0
    bdnz fn_80151F08_L_801524B8
    li r0, 0x3
    mtctr r0
    fn_80151F08_L_8015254C:
    addi r0, r3, 0x28
    li r31, 0x0
    stwx r31, r26, r0
    addi r0, r3, 0x7c
    addi r7, r3, 0xd0
    addi r6, r3, 0x2c
    stwx r31, r26, r0
    addi r5, r3, 0x80
    addi r4, r3, 0xd4
    addi r0, r3, 0x30
    stwx r31, r26, r7
    addi r30, r3, 0x84
    addi r29, r3, 0xd8
    addi r28, r3, 0x34
    stwx r31, r26, r6
    addi r27, r3, 0x88
    addi r12, r3, 0xdc
    addi r11, r3, 0x38
    stwx r31, r26, r5
    addi r10, r3, 0x8c
    addi r9, r3, 0xe0
    addi r8, r3, 0x3c
    stwx r31, r26, r4
    addi r7, r3, 0x90
    addi r6, r3, 0xe4
    addi r5, r3, 0x40
    stwx r31, r26, r0
    addi r4, r3, 0x94
    addi r0, r3, 0xe8
    addi r3, r3, 0x1c
    stwx r31, r26, r30
    stwx r31, r26, r29
    stwx r31, r26, r28
    stwx r31, r26, r27
    stwx r31, r26, r12
    stwx r31, r26, r11
    stwx r31, r26, r10
    stwx r31, r26, r9
    stwx r31, r26, r8
    stwx r31, r26, r7
    stwx r31, r26, r6
    stwx r31, r26, r5
    stwx r31, r26, r4
    stwx r31, r26, r0
    bdnz fn_80151F08_L_8015254C
    lwz r4, 0x8(r26)
    mr r3, r26
    bl fn_801502AC
    lis r3, lbl_8041BC00@ha
    addi r3, r3, lbl_8041BC00@l
    lwz r3, 0xba4(r3)
    bl FileLoader_Open
    lis r3, lbl_8041BC00@ha
    addi r3, r3, lbl_8041BC00@l
    lwz r3, 0xbb8(r3)
    bl FileLoader_Open
    li r28, 0x0
    mr r27, r28
    b fn_80151F08_L_80152684
    fn_80151F08_L_80152638:
    lwz r0, 0x578(r26)
    add r5, r0, r27
    lwz r4, 0x8(r5)
    cmpwi r4, 0x4
    beq fn_80151F08_L_80152660
    subi r0, r4, 0x5
    cmplwi r0, 0x2
    ble fn_80151F08_L_80152660
    cmpwi r4, 0x8
    bne fn_80151F08_L_8015267C
    fn_80151F08_L_80152660:
    lwz r3, 0x0(r5)
    lwz r0, 0x8(r26)
    cmpw r3, r0
    bge fn_80151F08_L_8015267C
    lwz r5, 0xc(r5)
    mr r3, r26
    bl fn_8015061C
    fn_80151F08_L_8015267C:
    addi r27, r27, 0x14
    addi r28, r28, 0x1
    fn_80151F08_L_80152684:
    lwz r0, 0x57c(r26)
    cmpw r28, r0
    blt fn_80151F08_L_80152638
    li r3, -0x1
    li r0, 0x0
    stw r3, 0x570(r26)
    stw r0, 0x574(r26)
    bl fn_8013DBF8
    mr r3, r26
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    lmw r25, 0x14(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" asm void DrawColoredQuad(int r, int g, int b, int a, float x, float y, float w, float h) { /* 0x801526C4 size:0x26C */
    nofralloc
    stwu r1, -0x110(r1)
    mflr r0
    stw r0, 0x114(r1)
    stfd f31, 0x100(r1)
    psq_st f31, 0x108(r1), 0, 0
    stfd f30, 0xf0(r1)
    psq_st f30, 0xf8(r1), 0, 0
    stfd f29, 0xe0(r1)
    psq_st f29, 0xe8(r1), 0, 0
    stfd f28, 0xd0(r1)
    psq_st f28, 0xd8(r1), 0, 0
    stmw r25, 0xb4(r1)
    fmr f28, f1
    lis r7, lbl_80363D30@ha
    fmr f29, f2
    mr r25, r3
    mr r26, r4
    mr r27, r5
    fmr f30, f3
    mr r28, r6
    fmr f31, f4
    addi r29, r7, lbl_80363D30@l
    li r3, 0x0
    li r4, 0x7
    li r5, 0x1
    bl GXSetZMode
    li r3, 0x0
    bl GXSetZCompLoc
    li r3, 0x1
    li r4, 0x4
    li r5, 0x5
    li r6, 0x0
    bl GXSetBlendMode
    lfs f1, lbl_806D8064(r2)
    lfs f3, lbl_806D80C4(r2)
    fmr f2, f1
    lfs f4, lbl_806D80C8(r2)
    fmr f5, f1
    lfs f6, lbl_806D8068(r2)
    bl GXSetViewport
    li r3, 0x0
    li r4, 0x0
    li r5, 0x280
    li r6, 0x1e0
    bl GXSetScissor
    lfs f1, lbl_806D8064(r2)
    addi r3, r1, 0x64
    lfs f2, lbl_806D80C8(r2)
    fmr f3, f1
    lfs f4, lbl_806D80C4(r2)
    fmr f5, f1
    lfs f6, lbl_806D80BC(r2)
    bl C_MTXOrtho
    addi r3, r1, 0x64
    li r4, 0x1
    bl GXSetProjection
    lwz r30, 0x30b0(r29)
    addi r3, r1, 0x34
    lwz r31, 0x30b4(r29)
    addi r4, r1, 0x28
    lwz r12, 0x30b8(r29)
    addi r5, r1, 0x1c
    lwz r11, 0x30bc(r29)
    addi r6, r1, 0x10
    lwz r10, 0x30c0(r29)
    lwz r9, 0x30c4(r29)
    lwz r8, 0x30c8(r29)
    lwz r7, 0x30cc(r29)
    lwz r0, 0x30d0(r29)
    stw r30, 0x28(r1)
    stw r31, 0x2c(r1)
    stw r12, 0x30(r1)
    stw r11, 0x1c(r1)
    stw r10, 0x20(r1)
    stw r9, 0x24(r1)
    stw r8, 0x10(r1)
    stw r7, 0x14(r1)
    stw r0, 0x18(r1)
    bl C_MTXLookAt
    addi r3, r1, 0x34
    li r4, 0x0
    bl GXLoadPosMtxImm
    li r3, 0x0
    bl GXSetCurrentMtx
    li r3, 0x0
    bl GXSetNumTexGens
    li r3, 0x1
    bl GXSetNumTevStages
    li r3, 0x1
    bl GXSetNumChans
    li r3, 0x0
    li r4, 0x4
    bl GXSetTevOp
    li r3, 0x0
    li r4, 0xff
    li r5, 0xff
    li r6, 0x4
    bl GXSetTevOrder
    li r3, 0x4
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl GXSetChanCtrl
    lwz r0, lbl_806DCF38(r2)
    addi r4, r1, 0x8
    li r3, 0x4
    stw r0, 0xc(r1)
    stb r25, 0xc(r1)
    stb r26, 0xd(r1)
    stb r27, 0xe(r1)
    stb r28, 0xf(r1)
    lwz r0, 0xc(r1)
    stw r0, 0x8(r1)
    bl GXSetChanMatColor
    bl GXClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0x9
    li r5, 0x0
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GXBegin
    lis r3, 0xcc01
    fadds f0, f28, f30
    stfs f28, -0x8000(r3)
    fadds f1, f29, f31
    stfs f29, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f29, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f1, -0x8000(r3)
    stfs f28, -0x8000(r3)
    stfs f1, -0x8000(r3)
    psq_l f31, 0x108(r1), 0, 0
    lfd f31, 0x100(r1)
    psq_l f30, 0xf8(r1), 0, 0
    lfd f30, 0xf0(r1)
    psq_l f29, 0xe8(r1), 0, 0
    lfd f29, 0xe0(r1)
    psq_l f28, 0xd8(r1), 0, 0
    lfd f28, 0xd0(r1)
    lmw r25, 0xb4(r1)
    lwz r0, 0x114(r1)
    mtlr r0
    addi r1, r1, 0x110
    blr
}

extern "C" void fn_80152930(VObj *p) {
    delete p;
}

extern "C" Base *fn_80152968(Base *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FE14;
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
        self->vt = lbl_8048FE3C;
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

extern "C" asm void fn_80152C00(void) { /* 0x80152C00 size:0x904 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stfd f29, 0x70(r1)
    psq_st f29, 0x78(r1), 0, 0
    stfd f28, 0x60(r1)
    psq_st f28, 0x68(r1), 0, 0
    stfd f27, 0x50(r1)
    psq_st f27, 0x58(r1), 0, 0
    stfd f26, 0x40(r1)
    psq_st f26, 0x48(r1), 0, 0
    stfd f25, 0x30(r1)
    psq_st f25, 0x38(r1), 0, 0
    stmw r27, 0x1c(r1)
    mr r31, r3
    lwz r0, 0x4(r3)
    cmpwi r0, 0x9
    beq fn_80152C00_L_801534B8
    lwz r0, lbl_806D10A0(r13)
    lwz r3, 0x14(r31)
    cmplwi r0, 0x0
    subi r27, r3, 0x1
    bne fn_80152C00_L_80152C70
    li r0, 0x0
    fn_80152C00_L_80152C70:
    lfs f25, lbl_806D8064(r2)
    mr r30, r0
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D818C(r2)
    fmr f28, f25
    fcmpo cr0, f1, f0
    bge fn_80152C00_L_80152CA4
    fdivs f0, f1, f0
    lfs f1, lbl_806D80C4(r2)
    lfs f2, lbl_806D8190(r2)
    fmuls f0, f1, f0
    fadds f25, f2, f0
    fsubs f28, f1, f0
    fn_80152C00_L_80152CA4:
    cmpwi r3, 0x4
    li r4, -0x1
    li r28, -0x1
    beq fn_80152C00_L_80152D10
    bge fn_80152C00_L_80152CD0
    cmpwi r3, 0x2
    beq fn_80152C00_L_80152CF0
    bge fn_80152C00_L_80152D00
    cmpwi r3, 0x1
    bge fn_80152C00_L_80152CE0
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152CD0:
    cmpwi r3, 0x6
    beq fn_80152C00_L_80152D30
    bge fn_80152C00_L_80152D3C
    b fn_80152C00_L_80152D20
    fn_80152C00_L_80152CE0:
    lfs f26, lbl_806D8194(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152CF0:
    lfs f26, lbl_806D8194(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152D00:
    lfs f26, lbl_806D8198(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152D10:
    lfs f26, lbl_806D819C(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152D20:
    lfs f26, lbl_806D81A0(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    b fn_80152C00_L_80152D3C
    fn_80152C00_L_80152D30:
    lfs f26, lbl_806D81A4(r2)
    li r4, 0x1d62
    li r28, 0x1d62
    fn_80152C00_L_80152D3C:
    lfs f1, lbl_806D819C(r2)
    li r3, 0x0
    lfs f2, lbl_806D8070(r2)
    li r5, 0x0
    bl fn_801698B4
    lfs f1, lbl_806D81A8(r2)
    mr r4, r28
    lfs f2, lbl_806D8070(r2)
    li r3, 0x0
    li r5, 0x0
    bl fn_801698B4
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x0
    lfs f2, lbl_806D81AC(r2)
    li r4, 0x865
    li r5, 0x0
    bl fn_801698B4
    lfs f0, lbl_806D81B0(r2)
    addi r4, r27, 0x76c
    lfs f2, lbl_806D81B4(r2)
    li r3, 0x0
    fadds f1, f0, f25
    li r5, 0x0
    bl fn_801698B4
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80152C00_L_80152DCC
    lfs f0, lbl_806D81B8(r2)
    lis r3, lbl_803677B0@ha
    addi r4, r3, lbl_803677B0@l
    lfs f2, lbl_806D81BC(r2)
    fadds f1, f0, f28
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80168A4C
    b fn_80152C00_L_80152DEC
    fn_80152C00_L_80152DCC:
    lfs f0, lbl_806D81B8(r2)
    lis r3, lbl_803677C8@ha
    addi r4, r3, lbl_803677C8@l
    lfs f2, lbl_806D81BC(r2)
    fadds f1, f0, f28
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80168A4C
    fn_80152C00_L_80152DEC:
    lfs f0, lbl_806D80B8(r2)
    li r3, 0x0
    lfs f2, lbl_806D80F0(r2)
    li r4, 0x76a
    fadds f27, f0, f25
    li r5, 0x0
    fmr f1, f27
    bl fn_801698B4
    lfs f0, lbl_806D81C0(r2)
    slwi r29, r27, 1
    lfs f2, lbl_806D81C4(r2)
    addi r4, r29, 0x750
    fadds f29, f0, f25
    li r3, 0x0
    li r5, 0x0
    fmr f1, f29
    bl fn_801698B4
    fadds f30, f25, f26
    lfs f2, lbl_806D81C4(r2)
    li r3, 0x0
    li r4, 0x769
    li r5, 0x0
    fmr f1, f30
    bl fn_801698B4
    lfs f0, lbl_806D81C8(r2)
    li r3, 0x0
    lfs f2, lbl_806D81CC(r2)
    li r4, 0x75c
    fadds f26, f0, f28
    li r5, 0x0
    fmr f1, f26
    bl fn_801698B4
    fmr f1, f26
    lfs f2, lbl_806D81D0(r2)
    li r3, 0x0
    li r4, 0x75d
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f27
    lfs f2, lbl_806D81D4(r2)
    li r3, 0x0
    li r4, 0x76a
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f29
    lfs f2, lbl_806D81D8(r2)
    addi r4, r29, 0x751
    li r3, 0x0
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f30
    lfs f2, lbl_806D81D8(r2)
    li r3, 0x0
    li r4, 0x769
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f26
    lfs f2, lbl_806D81DC(r2)
    li r3, 0x0
    li r4, 0x75c
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f26
    lfs f2, lbl_806D81E0(r2)
    li r3, 0x0
    li r4, 0x75d
    li r5, 0x0
    bl fn_801698B4
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x0
    li r7, 0x0
    bl TaRecord_GetTime_Indexed
    fmr f25, f1
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x0
    li r7, 0x0
    bl TaRecord_GetEntry_Indexed
    lfs f0, lbl_806D81E4(r2)
    mr r28, r3
    lfs f2, lbl_806D808C(r2)
    mr r4, r28
    fadds f31, f0, f28
    li r3, 0x0
    fmr f1, f31
    creqv 6, 6, 6
    bl fn_80167DDC
    lbz r3, 0xc(r28)
    extsb r3, r3
    bl fn_8013BFCC
    lfs f0, lbl_806D81E8(r2)
    mr r4, r3
    lfs f2, lbl_806D81EC(r2)
    li r3, 0x0
    fadds f30, f0, f28
    li r5, 0x0
    fmr f1, f30
    bl fn_801698B4
    lfs f0, lbl_806D8090(r2)
    li r27, 0x0
    lfs f27, lbl_806D81F0(r2)
    lis r29, 0x4330
    fadds f29, f0, f28
    lfd f26, lbl_806D80A0(r2)
    fn_80152C00_L_80152F98:
    fmr f1, f25
    mr r3, r27
    bl fn_80167744
    subfic r0, r27, 0x7
    addi r4, r3, 0x778
    xoris r0, r0, 0x8000
    stw r29, 0x8(r1)
    lfs f2, lbl_806D808C(r2)
    li r3, 0x0
    stw r0, 0xc(r1)
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f26
    fmadds f1, f27, f0, f29
    bl fn_801698B4
    addi r27, r27, 0x1
    cmpwi r27, 0x8
    blt fn_80152C00_L_80152F98
    cmplwi r30, 0x0
    beq fn_80152C00_L_80153064
    lbz r6, 0xc(r28)
    mr r3, r30
    lbz r4, 0xd(r28)
    li r7, 0x0
    lbz r5, 0xe(r28)
    extsb r6, r6
    bl get_title_name
    mr. r27, r3
    beq fn_80152C00_L_80153064
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80152C00_L_80153040
    lfs f0, lbl_806D81F4(r2)
    mr r4, r27
    lfs f2, lbl_806D81F8(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D81FC(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    b fn_80152C00_L_80153064
    fn_80152C00_L_80153040:
    lfs f0, lbl_806D81F4(r2)
    mr r4, r27
    lfs f2, lbl_806D81F8(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D8200(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    fn_80152C00_L_80153064:
    fmr f1, f31
    lfs f2, lbl_806D8204(r2)
    mr r4, r28
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80167DDC
    lbz r3, 0xc(r28)
    extsb r3, r3
    bl fn_8013BFCC
    fmr f1, f30
    mr r4, r3
    lfs f2, lbl_806D8208(r2)
    li r3, 0x0
    li r5, 0x0
    bl fn_801698B4
    lfs f27, lbl_806D81F0(r2)
    li r27, 0x0
    lfd f26, lbl_806D80A0(r2)
    lis r29, 0x4330
    fn_80152C00_L_801530B0:
    fmr f1, f25
    mr r3, r27
    bl fn_80167744
    subfic r0, r27, 0x7
    addi r4, r3, 0x778
    xoris r0, r0, 0x8000
    stw r29, 0x8(r1)
    lfs f2, lbl_806D8204(r2)
    li r3, 0x0
    stw r0, 0xc(r1)
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f26
    fmadds f1, f27, f0, f29
    bl fn_801698B4
    addi r27, r27, 0x1
    cmpwi r27, 0x8
    blt fn_80152C00_L_801530B0
    cmplwi r30, 0x0
    beq fn_80152C00_L_8015317C
    lbz r6, 0xc(r28)
    mr r3, r30
    lbz r4, 0xd(r28)
    li r7, 0x0
    lbz r5, 0xe(r28)
    extsb r6, r6
    bl get_title_name
    mr. r29, r3
    beq fn_80152C00_L_8015317C
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80152C00_L_80153158
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D8070(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D81FC(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    b fn_80152C00_L_8015317C
    fn_80152C00_L_80153158:
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D8070(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D8200(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    fn_80152C00_L_8015317C:
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x1
    li r7, 0x0
    bl TaRecord_GetTime_Indexed
    fmr f25, f1
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x1
    li r7, 0x0
    bl TaRecord_GetEntry_Indexed
    fmr f1, f31
    mr r28, r3
    lfs f2, lbl_806D820C(r2)
    mr r4, r28
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80167DDC
    lbz r3, 0xc(r28)
    extsb r3, r3
    bl fn_8013BFCC
    fmr f1, f30
    mr r4, r3
    lfs f2, lbl_806D8210(r2)
    li r3, 0x0
    li r5, 0x0
    bl fn_801698B4
    lfs f26, lbl_806D81F0(r2)
    li r27, 0x0
    lfd f27, lbl_806D80A0(r2)
    lis r29, 0x4330
    fn_80152C00_L_80153200:
    fmr f1, f25
    mr r3, r27
    bl fn_80167744
    subfic r0, r27, 0x7
    addi r4, r3, 0x778
    xoris r0, r0, 0x8000
    stw r29, 0x8(r1)
    lfs f2, lbl_806D820C(r2)
    li r3, 0x0
    stw r0, 0xc(r1)
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f27
    fmadds f1, f26, f0, f29
    bl fn_801698B4
    addi r27, r27, 0x1
    cmpwi r27, 0x8
    blt fn_80152C00_L_80153200
    cmplwi r30, 0x0
    beq fn_80152C00_L_801532CC
    lbz r6, 0xc(r28)
    mr r3, r30
    lbz r4, 0xd(r28)
    li r7, 0x0
    lbz r5, 0xe(r28)
    extsb r6, r6
    bl get_title_name
    mr. r29, r3
    beq fn_80152C00_L_801532CC
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80152C00_L_801532A8
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D8214(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D81FC(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    b fn_80152C00_L_801532CC
    fn_80152C00_L_801532A8:
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D8214(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D8200(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    fn_80152C00_L_801532CC:
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x1
    li r7, 0x1
    bl TaRecord_GetTime_Indexed
    fmr f26, f1
    lwz r5, 0x14(r31)
    li r3, 0x0
    li r4, 0x1
    li r6, 0x1
    li r7, 0x1
    bl TaRecord_GetEntry_Indexed
    fmr f1, f31
    mr r28, r3
    lfs f2, lbl_806D8100(r2)
    mr r4, r28
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80167DDC
    lbz r3, 0xc(r28)
    extsb r3, r3
    bl fn_8013BFCC
    fmr f1, f30
    mr r4, r3
    lfs f2, lbl_806D8218(r2)
    li r3, 0x0
    li r5, 0x0
    bl fn_801698B4
    lfs f31, lbl_806D81F0(r2)
    li r27, 0x0
    lfd f30, lbl_806D80A0(r2)
    lis r29, 0x4330
    fn_80152C00_L_80153350:
    fmr f1, f26
    mr r3, r27
    bl fn_80167744
    subfic r0, r27, 0x7
    addi r4, r3, 0x778
    xoris r0, r0, 0x8000
    stw r29, 0x8(r1)
    lfs f2, lbl_806D8100(r2)
    li r3, 0x0
    stw r0, 0xc(r1)
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f30
    fmadds f1, f31, f0, f29
    bl fn_801698B4
    addi r27, r27, 0x1
    cmpwi r27, 0x8
    blt fn_80152C00_L_80153350
    cmplwi r30, 0x0
    beq fn_80152C00_L_8015341C
    lbz r6, 0xc(r28)
    mr r3, r30
    lbz r4, 0xd(r28)
    li r7, 0x0
    lbz r5, 0xe(r28)
    extsb r6, r6
    bl get_title_name
    mr. r29, r3
    beq fn_80152C00_L_8015341C
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80152C00_L_801533F8
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D821C(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D81FC(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    b fn_80152C00_L_8015341C
    fn_80152C00_L_801533F8:
    lfs f0, lbl_806D81F4(r2)
    mr r4, r29
    lfs f2, lbl_806D821C(r2)
    li r3, 0x0
    fadds f1, f0, f28
    lfs f3, lbl_806D8200(r2)
    lfs f4, lbl_806D8068(r2)
    creqv 6, 6, 6
    bl fn_80168910
    fn_80152C00_L_8015341C:
    lbz r0, 0x10(r31)
    cmplwi r0, 0x0
    bne fn_80152C00_L_80153430
    li r0, 0x1
    stb r0, 0x10(r31)
    fn_80152C00_L_80153430:
    lfs f1, lbl_806D8060(r2)
    lfs f2, 0x8(r31)
    fcmpo cr0, f2, f1
    bge fn_80152C00_L_8015345C
    fdivs f0, f2, f1
    lfs f3, lbl_806D8068(r2)
    lfs f2, lbl_806D8064(r2)
    fsubs f1, f3, f0
    bl Saturate_Double
    stfs f1, 0xc(r31)
    b fn_80152C00_L_80153490
    fn_80152C00_L_8015345C:
    lfs f0, lbl_806D8220(r2)
    fsubs f0, f0, f1
    fcmpo cr0, f2, f0
    ble fn_80152C00_L_80153488
    fsubs f0, f2, f0
    lfs f2, lbl_806D8064(r2)
    lfs f3, lbl_806D8068(r2)
    fdivs f1, f0, f1
    bl Saturate_Double
    stfs f1, 0xc(r31)
    b fn_80152C00_L_80153490
    fn_80152C00_L_80153488:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0xc(r31)
    fn_80152C00_L_80153490:
    lfs f2, 0x8(r31)
    lfs f1, lbl_806D8068(r2)
    lfs f0, lbl_806D8220(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x8(r31)
    cror eq, gt, eq
    bne fn_80152C00_L_801534B8
    li r0, 0x9
    stw r0, 0x4(r31)
    fn_80152C00_L_801534B8:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    psq_l f29, 0x78(r1), 0, 0
    lfd f29, 0x70(r1)
    psq_l f28, 0x68(r1), 0, 0
    lfd f28, 0x60(r1)
    psq_l f27, 0x58(r1), 0, 0
    lfd f27, 0x50(r1)
    psq_l f26, 0x48(r1), 0, 0
    lfd f26, 0x40(r1)
    psq_l f25, 0x38(r1), 0, 0
    lfd f25, 0x30(r1)
    lmw r27, 0x1c(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

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
        self->vt = lbl_8048FE64;
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

extern "C" asm void fn_8015376C(void) { /* 0x8015376C size:0x2D0 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    stw r30, 0xb8(r1)
    stw r29, 0xb4(r1)
    stw r28, 0xb0(r1)
    mr r28, r3
    lis r3, lbl_80363D30@ha
    addi r29, r3, lbl_80363D30@l
    addi r3, r28, 0x34
    bl fn_801F6804
    lfs f1, lbl_806D8064(r2)
    li r3, 0xff
    lfs f3, lbl_806D80C4(r2)
    li r4, 0xff
    fmr f2, f1
    lfs f4, lbl_806D80C8(r2)
    li r5, 0xff
    li r6, 0xff
    bl DrawColoredQuad
    li r3, 0x0
    li r4, 0x7
    li r5, 0x1
    bl GXSetZMode
    li r3, 0x0
    bl GXSetZCompLoc
    li r3, 0x1
    li r4, 0x4
    li r5, 0x5
    li r6, 0x0
    bl GXSetBlendMode
    lfs f1, lbl_806D8064(r2)
    lfs f3, lbl_806D80C4(r2)
    fmr f2, f1
    lfs f4, lbl_806D80C8(r2)
    lfs f5, lbl_806D806C(r2)
    lfs f6, lbl_806D8068(r2)
    bl GXSetViewport
    li r3, 0x0
    li r4, 0x0
    li r5, 0x280
    li r6, 0x1e0
    bl GXSetScissor
    lfs f1, lbl_806D8228(r2)
    addi r3, r1, 0x64
    lfs f2, lbl_806D822C(r2)
    lfs f3, lbl_806D8064(r2)
    lfs f4, lbl_806D8230(r2)
    lfs f5, lbl_806D8234(r2)
    lfs f6, lbl_806D80BC(r2)
    bl C_MTXOrtho
    addi r3, r1, 0x64
    li r4, 0x1
    bl GXSetProjection
    lwz r30, 0x30f8(r29)
    addi r3, r1, 0x34
    lwz r31, 0x30fc(r29)
    addi r4, r1, 0x28
    lwz r12, 0x3100(r29)
    addi r5, r1, 0x1c
    lwz r11, 0x3104(r29)
    addi r6, r1, 0x10
    lwz r10, 0x3108(r29)
    lwz r9, 0x310c(r29)
    lwz r8, 0x3110(r29)
    lwz r7, 0x3114(r29)
    lwz r0, 0x3118(r29)
    stw r30, 0x28(r1)
    stw r31, 0x2c(r1)
    stw r12, 0x30(r1)
    stw r11, 0x1c(r1)
    stw r10, 0x20(r1)
    stw r9, 0x24(r1)
    stw r8, 0x10(r1)
    stw r7, 0x14(r1)
    stw r0, 0x18(r1)
    bl C_MTXLookAt
    addi r3, r1, 0x34
    li r4, 0x0
    bl GXLoadPosMtxImm
    li r3, 0x0
    bl GXSetCurrentMtx
    li r3, 0x1
    bl GXSetNumTexGens
    li r3, 0x0
    li r4, 0x1
    li r5, 0x4
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    li r3, 0x1
    bl GXSetNumTevStages
    li r3, 0x1
    bl GXSetNumChans
    li r3, 0x0
    li r4, 0x1
    bl GXSetTevOp
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x4
    bl GXSetTevOrder
    li r3, 0x4
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl GXSetChanCtrl
    lwz r5, lbl_806D7F64(r2)
    addi r4, r1, 0x8
    lbz r0, 0xc(r28)
    li r3, 0x4
    stw r5, 0xc(r1)
    stb r0, 0xf(r1)
    lwz r0, 0xc(r1)
    stw r0, 0x8(r1)
    bl GXSetChanMatColor
    addi r3, r28, 0x14
    li r4, 0x0
    bl GXLoadTexObj
    bl GXClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0x9
    li r5, 0x0
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0xd
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xd
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GXBegin
    lfs f5, lbl_806D8238(r2)
    lis r4, 0xcc01
    lfs f4, lbl_806D823C(r2)
    addi r3, r28, 0x34
    stfs f5, -0x8000(r4)
    lfs f3, lbl_806D8064(r2)
    stfs f4, -0x8000(r4)
    lfs f2, lbl_806D8240(r2)
    stfs f3, -0x8000(r4)
    lfs f1, lbl_806D8068(r2)
    stfs f3, -0x8000(r4)
    lfs f0, lbl_806D8244(r2)
    stfs f2, -0x8000(r4)
    stfs f4, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f3, -0x8000(r4)
    stfs f2, -0x8000(r4)
    stfs f0, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f5, -0x8000(r4)
    stfs f0, -0x8000(r4)
    stfs f3, -0x8000(r4)
    stfs f1, -0x8000(r4)
    bl fn_801F6804
    lwz r0, 0xc4(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r29, 0xb4(r1)
    lwz r28, 0xb0(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

extern "C" void fn_80153A3C(VObj *p) {
    delete p;
}

extern "C" PalObj *fn_80153A74(PalObj *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FE8C;
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

extern "C" asm void fn_80153C00(void) { /* 0x80153C00 size:0x2D0 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    stw r30, 0xb8(r1)
    stw r29, 0xb4(r1)
    stw r28, 0xb0(r1)
    mr r28, r3
    lis r3, lbl_80363D30@ha
    addi r29, r3, lbl_80363D30@l
    addi r3, r28, 0x34
    bl fn_801F6804
    lfs f1, lbl_806D8064(r2)
    li r3, 0xff
    lfs f3, lbl_806D80C4(r2)
    li r4, 0xff
    fmr f2, f1
    lfs f4, lbl_806D80C8(r2)
    li r5, 0xff
    li r6, 0xff
    bl DrawColoredQuad
    li r3, 0x0
    li r4, 0x7
    li r5, 0x1
    bl GXSetZMode
    li r3, 0x0
    bl GXSetZCompLoc
    li r3, 0x1
    li r4, 0x4
    li r5, 0x5
    li r6, 0x0
    bl GXSetBlendMode
    lfs f1, lbl_806D8064(r2)
    lfs f3, lbl_806D80C4(r2)
    fmr f2, f1
    lfs f4, lbl_806D80C8(r2)
    lfs f5, lbl_806D806C(r2)
    lfs f6, lbl_806D8068(r2)
    bl GXSetViewport
    li r3, 0x0
    li r4, 0x0
    li r5, 0x280
    li r6, 0x1e0
    bl GXSetScissor
    lfs f1, lbl_806D8228(r2)
    addi r3, r1, 0x64
    lfs f2, lbl_806D822C(r2)
    lfs f3, lbl_806D8064(r2)
    lfs f4, lbl_806D8230(r2)
    lfs f5, lbl_806D8234(r2)
    lfs f6, lbl_806D80BC(r2)
    bl C_MTXOrtho
    addi r3, r1, 0x64
    li r4, 0x1
    bl GXSetProjection
    lwz r30, 0x30d4(r29)
    addi r3, r1, 0x34
    lwz r31, 0x30d8(r29)
    addi r4, r1, 0x28
    lwz r12, 0x30dc(r29)
    addi r5, r1, 0x1c
    lwz r11, 0x30e0(r29)
    addi r6, r1, 0x10
    lwz r10, 0x30e4(r29)
    lwz r9, 0x30e8(r29)
    lwz r8, 0x30ec(r29)
    lwz r7, 0x30f0(r29)
    lwz r0, 0x30f4(r29)
    stw r30, 0x28(r1)
    stw r31, 0x2c(r1)
    stw r12, 0x30(r1)
    stw r11, 0x1c(r1)
    stw r10, 0x20(r1)
    stw r9, 0x24(r1)
    stw r8, 0x10(r1)
    stw r7, 0x14(r1)
    stw r0, 0x18(r1)
    bl C_MTXLookAt
    addi r3, r1, 0x34
    li r4, 0x0
    bl GXLoadPosMtxImm
    li r3, 0x0
    bl GXSetCurrentMtx
    li r3, 0x1
    bl GXSetNumTexGens
    li r3, 0x0
    li r4, 0x1
    li r5, 0x4
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    li r3, 0x1
    bl GXSetNumTevStages
    li r3, 0x1
    bl GXSetNumChans
    li r3, 0x0
    li r4, 0x1
    bl GXSetTevOp
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x4
    bl GXSetTevOrder
    li r3, 0x4
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl GXSetChanCtrl
    lwz r5, lbl_806D7F60(r2)
    addi r4, r1, 0x8
    lbz r0, 0xc(r28)
    li r3, 0x4
    stw r5, 0xc(r1)
    stb r0, 0xf(r1)
    lwz r0, 0xc(r1)
    stw r0, 0x8(r1)
    bl GXSetChanMatColor
    addi r3, r28, 0x14
    li r4, 0x0
    bl GXLoadTexObj
    bl GXClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0x9
    li r5, 0x0
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0xd
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xd
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GXBegin
    lfs f5, lbl_806D8238(r2)
    lis r4, 0xcc01
    lfs f4, lbl_806D823C(r2)
    addi r3, r28, 0x34
    stfs f5, -0x8000(r4)
    lfs f3, lbl_806D8064(r2)
    stfs f4, -0x8000(r4)
    lfs f2, lbl_806D8240(r2)
    stfs f3, -0x8000(r4)
    lfs f1, lbl_806D8068(r2)
    stfs f3, -0x8000(r4)
    lfs f0, lbl_806D8244(r2)
    stfs f2, -0x8000(r4)
    stfs f4, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f3, -0x8000(r4)
    stfs f2, -0x8000(r4)
    stfs f0, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f1, -0x8000(r4)
    stfs f5, -0x8000(r4)
    stfs f0, -0x8000(r4)
    stfs f3, -0x8000(r4)
    stfs f1, -0x8000(r4)
    bl fn_801F6790
    lwz r0, 0xc4(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r29, 0xb4(r1)
    lwz r28, 0xb0(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

extern "C" void fn_80153ED0(VObj *p) {
    delete p;
}

extern "C" asm void fn_80153F08(void) { /* 0x80153F08 size:0x1D8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    beq fn_80153F08_L_801540BC
    lis r4, lbl_8048FED8@ha
    li r3, 0x0
    addi r0, r4, lbl_8048FED8@l
    stw r0, 0x0(r30)
    bl SetCourseScene3D
    li r3, 0x0
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_80153F08_L_80153F5C
    li r3, 0x0
    bl fn_801909A4
    fn_80153F08_L_80153F5C:
    li r28, 0x0
    mr r29, r30
    fn_80153F08_L_80153F64:
    lwz r3, 0x4c(r29)
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    lwz r3, 0x34(r29)
    li r4, 0x1
    bl KartDriver_Dtor
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x6
    blt fn_80153F08_L_80153F64
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80153FAC
    li r4, 0x1
    bl Object_DtorWithGXSync
    fn_80153F08_L_80153FAC:
    lwz r3, 0x1a8(r30)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80153FD0
    beq fn_80153F08_L_80153FD0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80153F08_L_80153FD0:
    lwz r3, 0x1ac(r30)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80153FE4
    li r4, 0x1
    bl fn_80140810
    fn_80153F08_L_80153FE4:
    lwz r29, 0x1b4(r30)
    cmplwi r29, 0x0
    beq fn_80153F08_L_8015403C
    beq fn_80153F08_L_8015403C
    lwz r3, 0x0(r29)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80154014
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80153F08_L_80154014:
    lwz r3, 0x4(r29)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80154034
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80153F08_L_80154034:
    mr r3, r29
    bl MemoryManager_TimedFree
    fn_80153F08_L_8015403C:
    lwz r3, 0x1b8(r30)
    li r4, 0x1
    bl fn_801540E0
    lis r4, dtor_800869D0@ha
    lwz r3, 0x1bc(r30)
    addi r4, r4, dtor_800869D0@l
    bl __destroy_new_array
    li r0, 0x0
    stw r0, 0x1bc(r30)
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq fn_80153F08_L_80154080
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80153F08_L_80154080:
    li r0, 0x0
    stw r0, lbl_806D10AC(r13)
    bl fn_80121210
    bl clRom_PurgeAll
    li r3, 0x0
    bl SetResourceLoadingFlag
    cmplwi r30, 0x0
    beq fn_80153F08_L_801540AC
    lis r3, lbl_8048FF80@ha
    addi r0, r3, lbl_8048FF80@l
    stw r0, 0x0(r30)
    fn_80153F08_L_801540AC:
    extsh. r0, r31
    ble fn_80153F08_L_801540BC
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_80153F08_L_801540BC:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_801540E0(void *o, int flag) { /* 0x801540E0 size:0x224 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r4
    stw r30, 0x48(r1)
    mr. r30, r3
    stw r29, 0x44(r1)
    stw r28, 0x40(r1)
    beq fn_801540E0_L_801542E0
    li r29, 0x0
    mr r28, r30
    fn_801540E0_L_80154110:
    addi r4, r28, 0x18
    addi r3, r1, 0x20
    addi r0, r4, 0x4
    addi r5, r1, 0x24
    stw r0, 0x28(r1)
    addi r6, r1, 0x28
    lwz r0, 0x20(r28)
    stw r0, 0x24(r1)
    bl fn_80157D30
    addi r29, r29, 0x1
    addi r28, r28, 0xc
    cmpwi r29, 0x2
    blt fn_801540E0_L_80154110
    b fn_801540E0_L_80154178
    fn_801540E0_L_80154148:
    lwz r3, 0x14(r30)
    lwz r3, 0x10(r3)
    cmplwi r3, 0x0
    beq fn_801540E0_L_80154160
    li r4, 0x1
    bl fn_801F7CD8
    fn_801540E0_L_80154160:
    lwz r0, 0x14(r30)
    addi r3, r1, 0x34
    addi r4, r30, 0xc
    addi r5, r1, 0x38
    stw r0, 0x38(r1)
    bl fn_80157BE8
    fn_801540E0_L_80154178:
    lwz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne fn_801540E0_L_80154148
    b fn_801540E0_L_8015423C
    fn_801540E0_L_80154188:
    lwz r4, 0x8(r30)
    lwz r3, 0x10(r4)
    cmplwi r3, 0x0
    beq fn_801540E0_L_80154224
    lwz r0, 0x8(r4)
    srwi r0, r0, 29
    cmpwi r0, 0x2
    beq fn_801540E0_L_801541F4
    bge fn_801540E0_L_801541BC
    cmpwi r0, 0x0
    beq fn_801540E0_L_801541C8
    bge fn_801540E0_L_801541D4
    b fn_801540E0_L_80154220
    fn_801540E0_L_801541BC:
    cmpwi r0, 0x4
    bge fn_801540E0_L_80154220
    b fn_801540E0_L_80154214
    fn_801540E0_L_801541C8:
    li r4, 0x1
    bl Object_DtorWithGXSync
    b fn_801540E0_L_80154224
    fn_801540E0_L_801541D4:
    cmplwi r3, 0x0
    beq fn_801540E0_L_80154224
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    b fn_801540E0_L_80154224
    fn_801540E0_L_801541F4:
    cmplwi r3, 0x0
    beq fn_801540E0_L_80154224
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    b fn_801540E0_L_80154224
    fn_801540E0_L_80154214:
    li r4, 0x1
    bl LObjList_Destroy
    b fn_801540E0_L_80154224
    fn_801540E0_L_80154220:
    bl MemoryManager_TimedFree
    fn_801540E0_L_80154224:
    lwz r0, 0x8(r30)
    mr r4, r30
    addi r3, r1, 0x2c
    addi r5, r1, 0x30
    stw r0, 0x30(r1)
    bl fn_801579F0
    fn_801540E0_L_8015423C:
    lwz r0, 0x0(r30)
    cmplwi r0, 0x0
    bne fn_801540E0_L_80154188
    lis r4, fn_8014E04C@ha
    addi r3, r30, 0x18
    addi r4, r4, fn_8014E04C@l
    li r5, 0xc
    li r6, 0x2
    bl __destroy_arr
    addic. r0, r30, 0xc
    beq fn_801540E0_L_8015429C
    addic. r0, r30, 0xc
    beq fn_801540E0_L_8015429C
    addic. r0, r30, 0xc
    beq fn_801540E0_L_8015429C
    addi r7, r30, 0x10
    addi r3, r1, 0x14
    stw r7, 0x1c(r1)
    addi r4, r30, 0xc
    addi r5, r1, 0x18
    addi r6, r1, 0x1c
    lwz r0, 0x14(r30)
    stw r0, 0x18(r1)
    bl fn_80157B38
    fn_801540E0_L_8015429C:
    cmplwi r30, 0x0
    beq fn_801540E0_L_801542D0
    beq fn_801540E0_L_801542D0
    beq fn_801540E0_L_801542D0
    addi r0, r30, 0x4
    mr r4, r30
    stw r0, 0x10(r1)
    addi r3, r1, 0x8
    addi r5, r1, 0xc
    addi r6, r1, 0x10
    lwz r0, 0x8(r30)
    stw r0, 0xc(r1)
    bl fn_80157940
    fn_801540E0_L_801542D0:
    extsh. r0, r31
    ble fn_801540E0_L_801542E0
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_801540E0_L_801542E0:
    lwz r0, 0x54(r1)
    mr r3, r30
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    lwz r28, 0x40(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" asm void fn_80154304(void) { /* 0x80154304 size:0xCAC */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stmw r25, 0x54(r1)
    mr r29, r3
    lis r3, lbl_80363D30@ha
    lwz r0, 0x8(r29)
    addi r31, r3, lbl_80363D30@l
    cmpwi r0, 0x9
    beq fn_80154304_L_80154F94
    lbz r0, 0x28(r29)
    cmplwi r0, 0x0
    bne fn_80154304_L_8015435C
    li r3, 0x0
    li r4, 0x0
    bl ClSound_PlayBgmStream
    clrlwi. r0, r3, 24
    beq fn_80154304_L_8015435C
    li r0, 0x1
    stb r0, 0x28(r29)
    fn_80154304_L_8015435C:
    lbz r0, 0x29(r29)
    cmplwi r0, 0x0
    bne fn_80154304_L_80154384
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x29(r29)
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x2c(r29)
    stfs f0, 0x30(r29)
    b fn_80154304_L_80154394
    fn_80154304_L_80154384:
    lfs f1, 0x30(r29)
    lfs f0, lbl_806D8068(r2)
    fadds f0, f1, f0
    stfs f0, 0x30(r29)
    fn_80154304_L_80154394:
    lwz r4, 0x2c(r29)
    addi r3, r31, 0x3158
    lfs f0, 0x30(r29)
    slwi r0, r4, 3
    lfsx f1, r3, r0
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    bne fn_80154304_L_801543DC
    cmplwi r4, 0x9
    bne fn_80154304_L_801543CC
    lfs f0, lbl_806D8068(r2)
    fsubs f0, f1, f0
    stfs f0, 0x30(r29)
    b fn_80154304_L_801543DC
    fn_80154304_L_801543CC:
    addi r0, r4, 0x1
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x2c(r29)
    stfs f0, 0x30(r29)
    fn_80154304_L_801543DC:
    lwz r0, 0x2c(r29)
    addi r25, r31, 0x3158
    addi r25, r25, 0x4
    lwz r3, 0x1b8(r29)
    slwi r0, r0, 3
    lwzx r4, r25, r0
    bl fn_8014E028
    stw r3, 0x18(r29)
    lwz r0, 0x2c(r29)
    lwz r3, 0x1b8(r29)
    slwi r0, r0, 3
    lwzx r4, r25, r0
    bl fn_8014E004
    stw r3, 0x1c(r29)
    lwz r0, 0x2c(r29)
    lwz r3, 0x1b8(r29)
    slwi r0, r0, 3
    lwzx r4, r25, r0
    bl fn_8014DD5C
    stw r3, 0x20(r29)
    lwz r3, 0x18(r29)
    cmplwi r3, 0x0
    beq fn_80154304_L_801544AC
    lfs f1, 0x308c(r3)
    lfs f0, lbl_806D8064(r2)
    lfs f2, 0x30(r29)
    fcmpo cr0, f1, f0
    blt fn_80154304_L_80154460
    fcmpo cr0, f2, f0
    blt fn_80154304_L_80154460
    li r0, 0x1
    stb r0, 0x3084(r3)
    stfs f2, 0x308c(r3)
    fn_80154304_L_80154460:
    lwz r30, 0x18(r29)
    lfs f0, lbl_806D806C(r2)
    lfs f1, 0x3088(r30)
    fcmpu cr0, f0, f1
    beq fn_80154304_L_801544AC
    lbz r0, 0x3084(r30)
    cmplwi r0, 0x0
    beq fn_80154304_L_8015448C
    li r0, 0x0
    stb r0, 0x3084(r30)
    b fn_80154304_L_80154498
    fn_80154304_L_8015448C:
    lfs f0, 0x308c(r30)
    fadds f0, f0, f1
    stfs f0, 0x308c(r30)
    fn_80154304_L_80154498:
    lwz r3, 0x4(r30)
    lfs f1, 0x308c(r30)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r30)
    bl HSD_CObjAnim
    fn_80154304_L_801544AC:
    lwz r3, 0x20(r29)
    cmplwi r3, 0x0
    beq fn_80154304_L_801544C8
    lfs f1, 0x30(r29)
    bl Object_SetField8_AndDirty
    lwz r3, 0x20(r29)
    bl clNormal3D_Exec
    fn_80154304_L_801544C8:
    lwz r3, 0x18(r29)
    bl SetCourseScene3D
    lis r3, lbl_8048F1A8@ha
    mr r27, r29
    addi r28, r3, lbl_8048F1A8@l
    mr r26, r29
    li r30, 0x0
    fn_80154304_L_801544E4:
    lwz r3, 0x20(r29)
    lwz r4, 0x0(r28)
    bl ResolveJointByName
    stw r3, 0x184(r27)
    lwz r25, 0x184(r27)
    cmplwi r25, 0x0
    beq fn_80154304_L_80154590
    bne fn_80154304_L_80154514
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x47c
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80154304_L_80154514:
    cmplwi r25, 0x0
    beq fn_80154304_L_8015455C
    bne fn_80154304_L_80154530
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x25d
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_80154304_L_80154530:
    lwz r4, 0x14(r25)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80154304_L_8015454C
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80154304_L_8015454C
    li r3, 0x1
    fn_80154304_L_8015454C:
    clrlwi. r0, r3, 24
    beq fn_80154304_L_8015455C
    mr r3, r25
    bl HSD_JObjSetupMatrixSub
    fn_80154304_L_8015455C:
    addi r3, r25, 0x44
    addi r4, r26, 0x64
    bl PSMTXCopy
    addi r25, r30, 0x19c
    lbzx r0, r29, r25
    cmplwi r0, 0x0
    beq fn_80154304_L_801545B8
    lwz r3, 0x4c(r27)
    lfs f1, lbl_806D8064(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    li r0, 0x0
    stbx r0, r29, r25
    b fn_80154304_L_801545B8
    fn_80154304_L_80154590:
    addi r25, r30, 0x19c
    lbzx r0, r29, r25
    cmplwi r0, 0x0
    bne fn_80154304_L_801545B8
    lfs f0, lbl_806D8248(r2)
    stfs f0, 0x80(r26)
    lwz r3, 0x4c(r27)
    bl TornadoEffect_SetFlagC0
    li r0, 0x1
    stbx r0, r29, r25
    fn_80154304_L_801545B8:
    addi r30, r30, 0x1
    addi r27, r27, 0x4
    cmpwi r30, 0x6
    addi r26, r26, 0x30
    addi r28, r28, 0x4
    blt fn_80154304_L_801544E4
    li r25, 0x0
    mr r26, r29
    fn_80154304_L_801545D8:
    lwz r3, 0x34(r26)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_SnapshotAndFullReset
    addi r25, r25, 0x1
    addi r26, r26, 0x4
    cmplwi r25, 0x6
    blt fn_80154304_L_801545D8
    lfs f31, lbl_806D8064(r2)
    addi r30, r31, 0xeb0
    fn_80154304_L_801545FC:
    lfs f1, 0x0(r30)
    fcmpo cr0, f1, f31
    blt fn_80154304_L_801546EC
    lfs f0, 0xc(r29)
    fcmpu cr0, f0, f1
    bne fn_80154304_L_801546E4
    lbz r0, 0xc(r30)
    cmplwi r0, 0x0
    beq fn_80154304_L_80154688
    lwz r0, 0x4(r30)
    li r5, 0x1
    lwz r4, 0x8(r30)
    slwi r3, r0, 2
    addi r0, r3, 0x34
    lwzx r3, r29, r0
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventSet
    lwz r0, 0x4(r30)
    li r5, 0x1
    lwz r4, 0x8(r30)
    slwi r3, r0, 2
    addi r0, r3, 0x4c
    lwzx r3, r29, r0
    bl TornadoEffect_ApplyItemVisual_Secondary
    lwz r0, 0x8(r30)
    cmpwi r0, 0x32
    bne fn_80154304_L_801546E4
    lwz r0, 0x4(r30)
    lfs f0, lbl_806D824C(r2)
    slwi r3, r0, 2
    addi r0, r3, 0x34
    lwzx r3, r29, r0
    lwz r3, 0x304(r3)
    stfs f0, 0x28(r3)
    b fn_80154304_L_801546E4
    fn_80154304_L_80154688:
    lwz r0, 0x4(r30)
    lwz r4, 0x8(r30)
    slwi r3, r0, 2
    addi r0, r3, 0x34
    lwzx r3, r29, r0
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventClear
    lwz r0, 0x4(r30)
    lwz r4, 0x8(r30)
    slwi r3, r0, 2
    addi r0, r3, 0x4c
    lwzx r3, r29, r0
    bl TornadoEffect_ApplyItemVisual_Primary
    lwz r0, 0x8(r30)
    cmpwi r0, 0x32
    bne fn_80154304_L_801546E4
    lwz r0, 0x4(r30)
    lfs f0, lbl_806D8064(r2)
    slwi r3, r0, 2
    addi r0, r3, 0x34
    lwzx r3, r29, r0
    lwz r3, 0x304(r3)
    stfs f0, 0x28(r3)
    fn_80154304_L_801546E4:
    addi r30, r30, 0x10
    b fn_80154304_L_801545FC
    fn_80154304_L_801546EC:
    lfs f1, lbl_806D8250(r2)
    lfs f0, 0xc(r29)
    fcmpu cr0, f1, f0
    bne fn_80154304_L_80154714
    lwz r3, 0x54(r29)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x5c(r29)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x60(r29)
    bl TornadoEffect_SetFlagC0
    fn_80154304_L_80154714:
    lfs f1, lbl_806D8254(r2)
    lfs f0, 0xc(r29)
    fcmpu cr0, f1, f0
    bne fn_80154304_L_80154730
    lwz r3, 0x54(r29)
    lfs f1, lbl_806D8068(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    fn_80154304_L_80154730:
    lfs f1, lbl_806D8258(r2)
    lfs f0, 0xc(r29)
    fcmpu cr0, f1, f0
    bne fn_80154304_L_8015474C
    lwz r3, 0x60(r29)
    lfs f1, lbl_806D8068(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    fn_80154304_L_8015474C:
    lfs f1, lbl_806D825C(r2)
    lfs f0, 0xc(r29)
    fcmpu cr0, f1, f0
    bne fn_80154304_L_80154768
    lwz r3, 0x5c(r29)
    lfs f1, lbl_806D8068(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    fn_80154304_L_80154768:
    lfs f1, lbl_806D8260(r2)
    lfs f0, 0xc(r29)
    fcmpu cr0, f1, f0
    bne fn_80154304_L_801547A0
    lfs f1, lbl_806D8068(r2)
    li r0, 0x10
    stw r0, 0x1a4(r29)
    fmr f2, f1
    lwz r3, 0x58(r29)
    bl TireEffect_ResetSpin
    lfs f1, lbl_806D8068(r2)
    lwz r3, 0x4c(r29)
    fmr f2, f1
    bl TireEffect_ResetSpin
    fn_80154304_L_801547A0:
    li r25, 0x0
    mr r26, r29
    fn_80154304_L_801547A8:
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lwz r3, 0x34(r26)
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    lwz r3, 0x4c(r26)
    li r4, 0x0
    bl TornadoEffect_Tick
    lwz r0, 0x184(r26)
    cmplwi r0, 0x0
    beq fn_80154304_L_801547E8
    lwz r4, 0x1a4(r29)
    lwz r3, 0x4c(r26)
    mr r5, r4
    bl TornadoEffect_SetColorPairC8CC
    b fn_80154304_L_801547F8
    fn_80154304_L_801547E8:
    lwz r3, 0x4c(r26)
    li r4, 0x0
    li r5, 0x0
    bl TornadoEffect_SetColorPairC8CC
    fn_80154304_L_801547F8:
    addi r25, r25, 0x1
    addi r26, r26, 0x4
    cmpwi r25, 0x6
    blt fn_80154304_L_801547A8
    li r25, 0x0
    mr r26, r29
    fn_80154304_L_80154810:
    lwz r3, 0x34(r26)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_TickTornadoCooldown
    addi r25, r25, 0x1
    addi r26, r26, 0x4
    cmplwi r25, 0x6
    blt fn_80154304_L_80154810
    li r25, 0x0
    b fn_80154304_L_8015493C
    fn_80154304_L_80154834:
    lfs f2, 0xc(r29)
    lfs f0, 0x0(r7)
    fcmpo cr0, f2, f0
    blt fn_80154304_L_80154938
    lwz r5, 0x4(r4)
    addi r3, r7, 0x28
    lwz r6, 0x8(r4)
    li r4, 0x1
    lfs f0, lbl_806D8064(r2)
    fn_80154304_L_80154858:
    lfs f1, 0x0(r3)
    fcmpo cr0, f1, f0
    blt fn_80154304_L_80154938
    fcmpo cr0, f2, f1
    bgt fn_80154304_L_8015492C
    mulli r0, r4, 0x28
    li r4, 0x0
    add r3, r7, r0
    lfs f1, -0x28(r3)
    lfs f0, 0x0(r3)
    fsubs f3, f2, f1
    lfs f4, -0x4(r3)
    fsubs f2, f0, f1
    lfs f0, 0x24(r3)
    fsubs f1, f0, f4
    fdivs f0, f3, f2
    fmadds f1, f0, f1, f4
    stfs f1, 0x8(r1)
    lfs f4, -0x24(r3)
    lfs f2, 0x4(r3)
    lfs f9, -0x20(r3)
    lfs f1, 0x8(r3)
    fsubs f2, f2, f4
    lfs f7, -0x1c(r3)
    lfs f3, 0xc(r3)
    fsubs f6, f1, f9
    fmadds f1, f0, f2, f4
    lfs f31, -0x18(r3)
    lfs f2, 0x10(r3)
    fsubs f5, f3, f7
    lfs f13, -0x14(r3)
    fsubs f8, f2, f31
    lfs f4, 0x14(r3)
    fmadds f2, f0, f6, f9
    lfs f12, -0x10(r3)
    lfs f3, 0x18(r3)
    fsubs f9, f4, f13
    lfs f11, -0xc(r3)
    fsubs f6, f3, f12
    lfs f4, 0x1c(r3)
    fmadds f3, f0, f5, f7
    lfs f10, -0x8(r3)
    fsubs f7, f4, f11
    lfs f5, 0x20(r3)
    fmadds f4, f0, f8, f31
    lwz r3, 0x1b8(r29)
    fsubs f8, f5, f10
    fmadds f5, f0, f9, f13
    fmadds f6, f0, f6, f12
    fmadds f7, f0, f7, f11
    fmadds f8, f0, f8, f10
    bl fn_80154FB0
    b fn_80154304_L_80154938
    fn_80154304_L_8015492C:
    addi r3, r3, 0x28
    addi r4, r4, 0x1
    b fn_80154304_L_80154858
    fn_80154304_L_80154938:
    addi r25, r25, 0xc
    fn_80154304_L_8015493C:
    lwz r0, 0x24(r29)
    add r4, r0, r25
    lwz r7, 0x0(r4)
    cmplwi r7, 0x0
    bne fn_80154304_L_80154834
    lwz r3, 0x1a8(r29)
    cmplwi r3, 0x0
    beq fn_80154304_L_8015496C
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80154304_L_8015496C:
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D8264(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80154304_L_8015499C
    lfs f0, lbl_806D80B0(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne fn_80154304_L_8015499C
    li r0, 0x1
    stb r0, 0x1b0(r29)
    b fn_80154304_L_801549A4
    fn_80154304_L_8015499C:
    li r0, 0x0
    stb r0, 0x1b0(r29)
    fn_80154304_L_801549A4:
    lbz r0, 0x1b0(r29)
    cmplwi r0, 0x0
    beq fn_80154304_L_801549B8
    lwz r3, 0x1ac(r29)
    bl fn_80140344
    fn_80154304_L_801549B8:
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D8268(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80154304_L_80154C8C
    lwz r0, 0x1b4(r29)
    cmplwi r0, 0x0
    bne fn_80154304_L_80154ADC
    li r3, 0x98
    bl Alloc
    mr. r25, r3
    beq fn_80154304_L_80154AD8
    li r3, 0x20
    bl Alloc
    mr. r26, r3
    beq fn_80154304_L_80154A04
    addi r4, r31, 0x3860
    li r5, 0x0
    bl fn_8013D800
    fn_80154304_L_80154A04:
    stw r26, 0x0(r25)
    li r3, 0x20
    bl Alloc
    mr. r26, r3
    beq fn_80154304_L_80154A24
    addi r4, r31, 0x386c
    li r5, 0x0
    bl fn_8013D800
    fn_80154304_L_80154A24:
    stw r26, 0x4(r25)
    addi r4, r31, 0x311c
    li r5, 0x0
    addi r3, r2, -0x22F8  /* lbl_806D7F68 */
    stb r5, 0x8(r25)
    li r0, 0x1
    lfs f7, lbl_806D8064(r2)
    stw r5, 0xc(r25)
    lfs f1, 0x311c(r31)
    stfs f7, 0x10(r25)
    lfs f0, 0x4(r4)
    stb r0, 0x14(r25)
    lfs f2, 0x8(r4)
    stfs f1, 0x1c(r25)
    lfs f1, 0xc(r4)
    stfs f0, 0x20(r25)
    lfs f0, 0x10(r4)
    stfs f7, 0x6c(r25)
    lfs f6, 0x14(r4)
    stb r0, 0x15(r25)
    lfs f5, 0x18(r4)
    stfs f2, 0x24(r25)
    lfs f4, 0x1c(r4)
    stfs f1, 0x28(r25)
    lfs f3, 0x20(r4)
    stfs f7, 0x70(r25)
    lfs f2, 0x24(r4)
    stb r0, 0x16(r25)
    lfs f1, lbl_806D7F68(r2)
    stfs f0, 0x2c(r25)
    lfs f0, 0x4(r3)
    stfs f6, 0x30(r25)
    stfs f7, 0x74(r25)
    stb r0, 0x17(r25)
    stfs f5, 0x34(r25)
    stfs f4, 0x38(r25)
    stfs f7, 0x78(r25)
    stb r0, 0x18(r25)
    stfs f3, 0x3c(r25)
    stfs f2, 0x40(r25)
    stfs f7, 0x7c(r25)
    stb r0, 0x80(r25)
    stfs f1, 0x84(r25)
    stfs f0, 0x88(r25)
    stfs f7, 0x94(r25)
    fn_80154304_L_80154AD8:
    stw r25, 0x1b4(r29)
    fn_80154304_L_80154ADC:
    lwz r3, 0x1b4(r29)
    cmplwi r3, 0x0
    beq fn_80154304_L_80154C8C
    lwz r0, 0xc(r3)
    cmpwi r0, 0x0
    bne fn_80154304_L_80154AFC
    li r0, 0x1
    stw r0, 0xc(r3)
    fn_80154304_L_80154AFC:
    lwz r28, 0x1b4(r29)
    lbz r0, 0x8(r28)
    cmplwi r0, 0x0
    bne fn_80154304_L_80154B18
    li r0, 0x1
    stb r0, 0x8(r28)
    b fn_80154304_L_80154B28
    fn_80154304_L_80154B18:
    lfs f1, 0x10(r28)
    lfs f0, lbl_806D8068(r2)
    fadds f0, f1, f0
    stfs f0, 0x10(r28)
    fn_80154304_L_80154B28:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x1
    bne fn_80154304_L_80154C8C
    mr r27, r28
    mr r25, r28
    addi r26, r31, 0x3144
    li r30, 0x0
    fn_80154304_L_80154B44:
    addi r31, r30, 0x14
    lbzx r0, r28, r31
    cmplwi r0, 0x0
    beq fn_80154304_L_80154BE8
    lfs f2, 0x10(r28)
    lfs f1, 0x0(r26)
    fcmpo cr0, f2, f1
    bge fn_80154304_L_80154B74
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x44(r27)
    stfs f0, 0x48(r27)
    b fn_80154304_L_80154BD0
    fn_80154304_L_80154B74:
    lfs f0, lbl_806D826C(r2)
    fadds f0, f0, f1
    fcmpo cr0, f2, f0
    bge fn_80154304_L_80154BB0
    fsubs f1, f2, f1
    lfs f0, lbl_806D80AC(r2)
    lfs f2, lbl_806D8064(r2)
    lfs f3, lbl_806D8068(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lfs f0, lbl_806D8270(r2)
    fmuls f0, f0, f1
    stfs f0, 0x44(r27)
    stfs f0, 0x48(r27)
    b fn_80154304_L_80154BD0
    fn_80154304_L_80154BB0:
    lfs f1, 0x6c(r25)
    lfs f0, lbl_806D8200(r2)
    fadds f0, f1, f0
    stfs f0, 0x6c(r25)
    lfs f1, 0x20(r27)
    lfs f0, 0x6c(r25)
    fadds f0, f1, f0
    stfs f0, 0x20(r27)
    fn_80154304_L_80154BD0:
    lfs f1, 0x20(r27)
    lfs f0, lbl_806D8274(r2)
    fcmpo cr0, f1, f0
    ble fn_80154304_L_80154BE8
    li r0, 0x0
    stbx r0, r28, r31
    fn_80154304_L_80154BE8:
    addi r30, r30, 0x1
    addi r27, r27, 0x8
    cmpwi r30, 0x5
    addi r25, r25, 0x4
    addi r26, r26, 0x4
    blt fn_80154304_L_80154B44
    lbz r0, 0x80(r28)
    cmplwi r0, 0x0
    beq fn_80154304_L_80154C8C
    lfs f1, 0x10(r28)
    lfs f0, lbl_806D826C(r2)
    fcmpo cr0, f1, f0
    bge fn_80154304_L_80154C44
    lfs f0, lbl_806D80AC(r2)
    lfs f2, lbl_806D8064(r2)
    fdivs f1, f1, f0
    lfs f3, lbl_806D8068(r2)
    bl Saturate_Double
    lfs f0, lbl_806D8278(r2)
    fmuls f0, f0, f1
    stfs f0, 0x8c(r28)
    stfs f0, 0x90(r28)
    b fn_80154304_L_80154C74
    fn_80154304_L_80154C44:
    lfs f2, 0x94(r28)
    lfs f1, lbl_806D811C(r2)
    lfs f0, lbl_806D827C(r2)
    fadds f1, f2, f1
    stfs f1, 0x94(r28)
    lfs f2, 0x88(r28)
    lfs f1, 0x94(r28)
    fadds f1, f2, f1
    stfs f1, 0x88(r28)
    lfs f1, 0x90(r28)
    fadds f0, f1, f0
    stfs f0, 0x90(r28)
    fn_80154304_L_80154C74:
    lfs f1, 0x88(r28)
    lfs f0, lbl_806D8274(r2)
    fcmpo cr0, f1, f0
    ble fn_80154304_L_80154C8C
    li r0, 0x0
    stb r0, 0x80(r28)
    fn_80154304_L_80154C8C:
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D8280(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80154304_L_80154E64
    fsubs f1, f1, f0
    lfs f0, lbl_806D8124(r2)
    lfs f2, lbl_806D8064(r2)
    lfs f3, lbl_806D8068(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r0, 0x4(r29)
    fmr f31, f1
    cmpwi r0, 0x2
    beq fn_80154304_L_80154D2C
    bge fn_80154304_L_80154D80
    cmpwi r0, 0x1
    bge fn_80154304_L_80154CD8
    b fn_80154304_L_80154D80
    fn_80154304_L_80154CD8:
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D819C(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x55
    li r5, 0x0
    bl fn_80169468
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D81A8(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x56
    li r5, 0x0
    bl fn_80169468
    b fn_80154304_L_80154DF8
    fn_80154304_L_80154D2C:
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D819C(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x3a9
    li r5, 0x0
    bl fn_80169468
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D81A8(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x3aa
    li r5, 0x0
    bl fn_80169468
    b fn_80154304_L_80154DF8
    fn_80154304_L_80154D80:
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D819C(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x9c6
    li r5, 0x0
    bl fn_80169468
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D81A8(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8070(r2)
    fmr f5, f3
    li r4, 0x9c8
    li r5, 0x0
    bl fn_80169468
    lfs f3, lbl_806D8068(r2)
    fmr f6, f31
    lfs f1, lbl_806D81A8(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D8284(r2)
    fmr f5, f3
    li r4, 0x582
    li r5, 0x0
    bl fn_80169468
    fn_80154304_L_80154DF8:
    lwz r3, 0x1bc(r29)
    lfs f1, lbl_806D8288(r2)
    lfs f2, lbl_806D80D0(r2)
    bl fn_801F93EC
    lfs f1, lbl_806D8068(r2)
    lwz r3, 0x1bc(r29)
    fmr f2, f1
    bl fn_801F93D0
    bl fn_801F8E58
    lwz r4, 0x1bc(r29)
    li r5, 0x0
    bl fn_801F8A34
    lwz r3, 0x1bc(r29)
    lfs f1, lbl_806D8288(r2)
    lfs f2, lbl_806D828C(r2)
    addi r3, r3, 0x230
    bl fn_801F93EC
    lfs f1, lbl_806D8068(r2)
    lwz r3, 0x1bc(r29)
    fmr f2, f1
    addi r3, r3, 0x230
    bl fn_801F93D0
    bl fn_801F8E58
    lwz r4, 0x1bc(r29)
    li r5, 0x0
    addi r4, r4, 0x230
    bl fn_801F8A34
    fn_80154304_L_80154E64:
    lwz r3, 0x18(r29)
    addi r4, r1, 0x3c
    bl CObj_LoadProjMatrix
    lwz r3, 0x18(r29)
    addi r4, r1, 0x30
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x30(r1)
    addi r3, r1, 0x24
    lwz r8, 0x34(r1)
    addi r4, r1, 0x18
    lwz r7, 0x38(r1)
    lwz r6, 0x3c(r1)
    lwz r5, 0x40(r1)
    lwz r0, 0x44(r1)
    stw r9, 0x18(r1)
    stw r8, 0x1c(r1)
    stw r7, 0x20(r1)
    stw r6, 0x24(r1)
    stw r5, 0x28(r1)
    stw r0, 0x2c(r1)
    bl VfxSlotMgr_Update
    bl GXDrawDone
    lwz r28, 0x1b8(r29)
    lwz r0, 0xc(r28)
    cmplwi r0, 0x0
    beq fn_80154304_L_80154F30
    lwz r31, 0x14(r28)
    addi r25, r28, 0x10
    li r30, 0x0
    b fn_80154304_L_80154F28
    fn_80154304_L_80154EE0:
    lwz r0, 0xc(r31)
    cmpwi r0, 0x0
    ble fn_80154304_L_80154EF4
    stw r30, 0xc(r31)
    b fn_80154304_L_80154F24
    fn_80154304_L_80154EF4:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq fn_80154304_L_80154F08
    li r4, 0x1
    bl fn_801F7CD8
    fn_80154304_L_80154F08:
    stw r31, 0x14(r1)
    addi r3, r1, 0x10
    addi r4, r28, 0xc
    addi r5, r1, 0x14
    bl fn_80157BE8
    lwz r31, 0x10(r1)
    b fn_80154304_L_80154F28
    fn_80154304_L_80154F24:
    lwz r31, 0x4(r31)
    fn_80154304_L_80154F28:
    cmplw r31, r25
    bne fn_80154304_L_80154EE0
    fn_80154304_L_80154F30:
    lfs f0, 0xc(r29)
    lfs f3, lbl_806D8068(r2)
    lfs f4, lbl_806D8060(r2)
    fadds f1, f0, f3
    lfs f0, lbl_806D8290(r2)
    fsubs f0, f0, f4
    stfs f1, 0xc(r29)
    lfs f1, 0xc(r29)
    fcmpo cr0, f1, f0
    ble fn_80154304_L_80154F70
    fsubs f0, f1, f0
    lfs f2, lbl_806D8064(r2)
    fdivs f1, f0, f4
    bl Saturate_Double
    stfs f1, 0x10(r29)
    b fn_80154304_L_80154F78
    fn_80154304_L_80154F70:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x10(r29)
    fn_80154304_L_80154F78:
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D8290(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80154304_L_80154F94
    li r0, 0x9
    stw r0, 0x8(r29)
    fn_80154304_L_80154F94:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    lmw r25, 0x54(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

extern "C" asm void fn_80154FB0(void) { /* 0x80154FB0 size:0x3AC */
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
    stfd f28, 0x180(r1)
    psq_st f28, 0x188(r1), 0, 0
    stfd f27, 0x170(r1)
    psq_st f27, 0x178(r1), 0, 0
    stfd f26, 0x160(r1)
    psq_st f26, 0x168(r1), 0, 0
    stfd f25, 0x150(r1)
    psq_st f25, 0x158(r1), 0, 0
    stfd f24, 0x140(r1)
    psq_st f24, 0x148(r1), 0, 0
    stfd f23, 0x130(r1)
    psq_st f23, 0x138(r1), 0, 0
    stfd f22, 0x120(r1)
    psq_st f22, 0x128(r1), 0, 0
    stfd f21, 0x110(r1)
    psq_st f21, 0x118(r1), 0, 0
    stfd f20, 0x100(r1)
    psq_st f20, 0x108(r1), 0, 0
    stmw r26, 0xe8(r1)
    mr r29, r4
    fmr f21, f1
    fmr f22, f2
    cmplwi r29, 0x2
    fmr f23, f3
    lfs f29, 0x1c8(r1)
    fmr f24, f4
    fmr f25, f5
    fmr f26, f6
    mr r28, r3
    fmr f27, f7
    mr r30, r6
    fmr f28, f8
    bge fn_80154FB0_L_801552E8
    cmplwi r5, 0x50
    bge fn_80154FB0_L_801552E8
    mulli r27, r5, 0x14
    lis r3, lbl_803644D0@ha
    lfs f0, lbl_806D8064(r2)
    addi r0, r3, lbl_803644D0@l
    lfs f2, lbl_806D811C(r2)
    add r3, r0, r27
    lfs f1, 0xc(r3)
    fcmpu cr0, f0, f25
    lfs f0, 0x10(r3)
    fmuls f1, f2, f1
    fmuls f0, f2, f0
    fmuls f31, f23, f1
    fmuls f30, f24, f0
    beq fn_80154FB0_L_801550E4
    fmr f1, f25
    bl LookupSin
    fmr f0, f1
    fmr f1, f25
    fmr f20, f0
    bl LookupCos
    lfs f0, lbl_806D8064(r2)
    fmr f3, f31
    fcmpo cr0, f20, f0
    bge fn_80154FB0_L_801550C4
    fneg f20, f20
    fn_80154FB0_L_801550C4:
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f1, f0
    bge fn_80154FB0_L_801550D4
    fneg f1, f1
    fn_80154FB0_L_801550D4:
    fmuls f2, f30, f20
    fmuls f0, f30, f1
    fmadds f31, f31, f1, f2
    fmadds f30, f3, f20, f0
    fn_80154FB0_L_801550E4:
    fsubs f1, f21, f31
    lfs f0, lbl_806D80C4(r2)
    fcmpo cr0, f1, f0
    bgt fn_80154FB0_L_801552E8
    fadds f3, f21, f31
    lfs f2, lbl_806D8064(r2)
    fcmpo cr0, f3, f2
    blt fn_80154FB0_L_801552E8
    fsubs f1, f22, f30
    lfs f0, lbl_806D80C8(r2)
    fcmpo cr0, f1, f0
    bgt fn_80154FB0_L_801552E8
    fcmpo cr0, f3, f2
    bge fn_80154FB0_L_80155120
    b fn_80154FB0_L_801552E8
    fn_80154FB0_L_80155120:
    lis r3, lbl_803644D0@ha
    addi r0, r3, lbl_803644D0@l
    add r31, r0, r27
    lwz r27, 0x0(r31)
    cmplwi r27, 0xc
    blt fn_80154FB0_L_80155140
    li r27, 0x0
    b fn_80154FB0_L_801551D8
    fn_80154FB0_L_80155140:
    lwz r0, 0xc(r28)
    cmplwi r0, 0x0
    beq fn_80154FB0_L_80155184
    lwz r4, 0x14(r28)
    addi r3, r28, 0x10
    b fn_80154FB0_L_8015517C
    fn_80154FB0_L_80155158:
    lwz r0, 0x8(r4)
    cmplw r0, r27
    bne fn_80154FB0_L_80155178
    lwz r3, 0xc(r4)
    addi r0, r3, 0x1
    stw r0, 0xc(r4)
    lwz r27, 0x10(r4)
    b fn_80154FB0_L_801551D8
    fn_80154FB0_L_80155178:
    lwz r4, 0x4(r4)
    fn_80154FB0_L_8015517C:
    cmplw r4, r3
    bne fn_80154FB0_L_80155158
    fn_80154FB0_L_80155184:
    li r0, 0x1
    stw r27, 0x18(r1)
    li r3, 0x4
    stw r0, 0x1c(r1)
    bl Alloc
    mr. r26, r3
    beq fn_80154FB0_L_801551B4
    lis r4, lbl_8048F178@ha
    slwi r0, r27, 2
    addi r4, r4, lbl_8048F178@l
    lwzx r4, r4, r0
    bl fn_801F7D50
    fn_80154FB0_L_801551B4:
    addi r0, r28, 0x10
    stw r26, 0x20(r1)
    addi r3, r1, 0x8
    addi r4, r28, 0xc
    stw r0, 0xc(r1)
    addi r5, r1, 0xc
    addi r6, r1, 0x18
    bl fn_80157C60
    lwz r27, 0x20(r1)
    fn_80154FB0_L_801551D8:
    cmplwi r27, 0x0
    beq fn_80154FB0_L_801552E8
    addi r26, r1, 0x28
    mr r3, r26
    bl fn_801F7E98
    stw r27, 0x24(r1)
    mr r3, r27
    mr r4, r26
    bl fn_801F7344
    lwz r3, 0x24(r1)
    mr r4, r26
    li r5, 0x0
    bl fn_801F7198
    mr r3, r26
    addi r4, r31, 0x4
    li r5, 0x0
    li r6, 0x0
    bl fn_801F6D58
    fmr f1, f21
    lfs f3, lbl_806D8068(r2)
    fmr f2, f22
    mr r3, r26
    bl fn_801F70F0
    fmr f1, f23
    mr r3, r26
    fmr f2, f24
    bl fn_801F6ED0
    fmr f1, f25
    mr r3, r26
    bl fn_801F6EEC
    lfs f0, lbl_806D8090(r2)
    mr r3, r26
    fmuls f3, f0, f26
    fmuls f2, f0, f27
    fmuls f1, f0, f28
    fmuls f0, f0, f29
    fctiwz f3, f3
    fctiwz f2, f2
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f3, 0xc0(r1)
    stfd f2, 0xc8(r1)
    lwz r4, 0xc4(r1)
    stfd f1, 0xd0(r1)
    lwz r5, 0xcc(r1)
    stfd f0, 0xd8(r1)
    lwz r6, 0xd4(r1)
    lwz r7, 0xdc(r1)
    bl fn_801F6EAC
    clrlwi. r0, r30, 31
    beq fn_80154FB0_L_801552B4
    mr r3, r26
    li r4, 0x4
    li r5, 0x1
    bl fn_801F6E84
    fn_80154FB0_L_801552B4:
    rlwinm. r0, r30, 0, 30, 30
    beq fn_80154FB0_L_801552C4
    li r0, 0x1
    stw r0, 0x54(r1)
    fn_80154FB0_L_801552C4:
    mulli r4, r29, 0xc
    addi r3, r1, 0x10
    addi r5, r1, 0x14
    addi r6, r1, 0x24
    addi r4, r4, 0x18
    add r4, r28, r4
    addi r0, r4, 0x4
    stw r0, 0x14(r1)
    bl fn_80157DE0
    fn_80154FB0_L_801552E8:
    psq_l f31, 0x1b8(r1), 0, 0
    lfd f31, 0x1b0(r1)
    psq_l f30, 0x1a8(r1), 0, 0
    lfd f30, 0x1a0(r1)
    psq_l f29, 0x198(r1), 0, 0
    lfd f29, 0x190(r1)
    psq_l f28, 0x188(r1), 0, 0
    lfd f28, 0x180(r1)
    psq_l f27, 0x178(r1), 0, 0
    lfd f27, 0x170(r1)
    psq_l f26, 0x168(r1), 0, 0
    lfd f26, 0x160(r1)
    psq_l f25, 0x158(r1), 0, 0
    lfd f25, 0x150(r1)
    psq_l f24, 0x148(r1), 0, 0
    lfd f24, 0x140(r1)
    psq_l f23, 0x138(r1), 0, 0
    lfd f23, 0x130(r1)
    psq_l f22, 0x128(r1), 0, 0
    lfd f22, 0x120(r1)
    psq_l f21, 0x118(r1), 0, 0
    lfd f21, 0x110(r1)
    psq_l f20, 0x108(r1), 0, 0
    lfd f20, 0x100(r1)
    lmw r26, 0xe8(r1)
    lwz r0, 0x1c4(r1)
    mtlr r0
    addi r1, r1, 0x1c0
    blr
}

extern "C" void *dtor_8015535C(void *self, short flag) {
    if (self != 0) {
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" unsigned char fn_80155398(StateObj *o) {
    return o->state8 == 9;
}

extern "C" asm void fn_801553AC(void) { /* 0x801553AC size:0x2F4 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr r31, r3
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq fn_801553AC_L_801554E8
    lwz r3, 0x18(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_801553AC_L_801554E8
    lwz r3, 0x1c(r31)
    bl LObjList_ApplyForCObj
    lwz r3, 0x18(r31)
    bl CObj_DebugVizPathFlush
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_801553AC_L_80155408
    li r3, 0x0
    fn_801553AC_L_80155408:
    bl clDrawMan_Buckets_Reset
    lwz r3, 0x14(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    li r27, 0x0
    mr r29, r31
    fn_801553AC_L_80155420:
    lwz r3, 0x184(r29)
    cmplwi r3, 0x0
    beq fn_801553AC_L_8015546C
    li r4, 0x10
    bl HSD_JObjClearFlagsAll
    lwz r3, 0x4c(r29)
    bl KartItem_DispatchEffectRenderByState
    lwz r3, 0x184(r29)
    li r4, 0x0
    li r5, 0x7
    li r6, 0x0
    bl HSD_JObjDispAll
    lwz r3, 0x4c(r29)
    bl KartItem_FlushPendingRender_v2
    lwz r3, 0x4c(r29)
    bl TornadoEffect_SubmitRender
    lwz r3, 0x184(r29)
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    fn_801553AC_L_8015546C:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0x6
    blt fn_801553AC_L_80155420
    lwz r3, 0x20(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_801553AC_L_801554A0
    li r3, 0x0
    fn_801553AC_L_801554A0:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_801553AC_L_801554B4
    li r3, 0x0
    fn_801553AC_L_801554B4:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x1a8(r31)
    cmplwi r3, 0x0
    beq fn_801553AC_L_801554D4
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_801553AC_L_801554D4:
    lwz r3, 0x18(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_801553AC_L_801554E8:
    lbz r0, 0x1b0(r31)
    cmplwi r0, 0x0
    beq fn_801553AC_L_801554FC
    lwz r3, 0x1ac(r31)
    bl fn_8014017C
    fn_801553AC_L_801554FC:
    li r3, 0x0
    bl fn_8011F994
    li r30, 0x0
    lwz r28, 0x1b8(r31)
    fn_801553AC_L_8015550C:
    cmplwi r30, 0x2
    bge fn_801553AC_L_80155574
    lwz r0, 0x18(r28)
    cmplwi r0, 0x0
    beq fn_801553AC_L_80155574
    li r3, 0x0
    bl GX_EndDraw
    lwz r29, 0x20(r28)
    addi r27, r28, 0x1c
    b fn_801553AC_L_80155548
    fn_801553AC_L_80155534:
    lwz r3, 0x8(r29)
    addi r4, r29, 0xc
    lfs f1, lbl_806D806C(r2)
    bl fn_801F7B74
    lwz r29, 0x4(r29)
    fn_801553AC_L_80155548:
    cmplw r29, r27
    bne fn_801553AC_L_80155534
    bl GX_BeginDraw
    stw r27, 0x10(r1)
    addi r3, r1, 0x8
    addi r4, r28, 0x18
    addi r5, r1, 0xc
    lwz r0, 0x20(r28)
    addi r6, r1, 0x10
    stw r0, 0xc(r1)
    bl fn_80157D30
    fn_801553AC_L_80155574:
    addi r30, r30, 0x1
    addi r28, r28, 0xc
    cmplwi r30, 0x2
    blt fn_801553AC_L_8015550C
    lwz r27, 0x1b4(r31)
    cmplwi r27, 0x0
    beq fn_801553AC_L_8015564C
    lwz r0, 0xc(r27)
    cmpwi r0, 0x1
    bne fn_801553AC_L_8015564C
    li r30, 0x0
    mr r28, r27
    fn_801553AC_L_801555A4:
    addi r0, r30, 0x14
    lbzx r0, r27, r0
    cmplwi r0, 0x0
    beq fn_801553AC_L_801555F8
    lfs f1, 0x1c(r28)
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f1, f0
    ble fn_801553AC_L_801555F8
    lwz r3, 0x4(r27)
    lfs f2, 0x20(r28)
    bl fn_8013D660
    lfs f1, 0x44(r28)
    lwz r3, 0x4(r27)
    fmr f3, f1
    lfs f2, 0x48(r28)
    bl fn_8013D608
    lwz r3, 0x4(r27)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_801553AC_L_801555F8:
    addi r30, r30, 0x1
    addi r28, r28, 0x8
    cmpwi r30, 0x5
    blt fn_801553AC_L_801555A4
    lbz r0, 0x80(r27)
    cmplwi r0, 0x0
    beq fn_801553AC_L_8015564C
    lwz r3, 0x0(r27)
    lfs f1, 0x84(r27)
    lfs f2, 0x88(r27)
    bl fn_8013D660
    lfs f1, 0x8c(r27)
    lwz r3, 0x0(r27)
    fmr f3, f1
    lfs f2, 0x90(r27)
    bl fn_8013D608
    lwz r3, 0x0(r27)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_801553AC_L_8015564C:
    lfs f4, 0x10(r31)
    lfs f1, lbl_806D8064(r2)
    fcmpo cr0, f4, f1
    ble fn_801553AC_L_8015568C
    lfs f0, lbl_806D8090(r2)
    fmr f2, f1
    lfs f3, lbl_806D80C4(r2)
    li r3, 0x0
    fmuls f0, f0, f4
    lfs f4, lbl_806D80C8(r2)
    li r4, 0x0
    li r5, 0x0
    fctiwz f0, f0
    stfd f0, 0x18(r1)
    lwz r6, 0x1c(r1)
    bl DrawColoredQuad
    fn_801553AC_L_8015568C:
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" Base *fn_801556A0(Base *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8048FF20;
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
        self->vt = lbl_8048FF3C;
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
        fn_801540E0(self->obj4C, 1);
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

extern "C" asm void fn_801558CC(void) { /* 0x801558CC size:0x16F4 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stfd f30, 0x90(r1)
    psq_st f30, 0x98(r1), 0, 0
    stmw r26, 0x78(r1)
    mr r28, r3
    lwz r0, 0x4(r3)
    cmpwi r0, 0x9
    beq fn_801558CC_L_80156F9C
    lbz r0, 0x24(r28)
    cmplwi r0, 0x0
    bne fn_801558CC_L_80155910
    li r0, 0x1
    stb r0, 0x24(r28)
    fn_801558CC_L_80155910:
    lfs f0, 0x8(r28)
    lfs f2, lbl_806D8220(r2)
    fcmpo cr0, f0, f2
    bge fn_801558CC_L_80155934
    li r0, 0xa
    stw r0, 0x28(r28)
    lfs f0, 0x8(r28)
    stfs f0, 0x2c(r28)
    b fn_801558CC_L_80155984
    fn_801558CC_L_80155934:
    lfs f1, lbl_806D80EC(r2)
    fcmpo cr0, f0, f1
    bge fn_801558CC_L_80155958
    li r0, 0xb
    stw r0, 0x28(r28)
    lfs f0, 0x8(r28)
    fsubs f0, f0, f2
    stfs f0, 0x2c(r28)
    b fn_801558CC_L_80155984
    fn_801558CC_L_80155958:
    li r0, 0xc
    stw r0, 0x28(r28)
    lfs f0, 0x8(r28)
    fsubs f0, f0, f1
    stfs f0, 0x2c(r28)
    lfs f0, 0x2c(r28)
    fcmpo cr0, f0, f2
    cror eq, gt, eq
    bne fn_801558CC_L_80155984
    lfs f0, lbl_806D8294(r2)
    stfs f0, 0x2c(r28)
    fn_801558CC_L_80155984:
    lwz r3, 0x4c(r28)
    lwz r4, 0x28(r28)
    bl fn_8014E028
    stw r3, 0x18(r28)
    lwz r3, 0x4c(r28)
    lwz r4, 0x28(r28)
    bl fn_8014E004
    stw r3, 0x1c(r28)
    lwz r3, 0x4c(r28)
    lwz r4, 0x28(r28)
    bl fn_8014DD5C
    stw r3, 0x20(r28)
    lwz r3, 0x18(r28)
    cmplwi r3, 0x0
    beq fn_801558CC_L_80155A34
    lfs f1, 0x308c(r3)
    lfs f0, lbl_806D8064(r2)
    lfs f2, 0x2c(r28)
    fcmpo cr0, f1, f0
    blt fn_801558CC_L_801559E8
    fcmpo cr0, f2, f0
    blt fn_801558CC_L_801559E8
    li r0, 0x1
    stb r0, 0x3084(r3)
    stfs f2, 0x308c(r3)
    fn_801558CC_L_801559E8:
    lwz r29, 0x18(r28)
    lfs f0, lbl_806D806C(r2)
    lfs f1, 0x3088(r29)
    fcmpu cr0, f0, f1
    beq fn_801558CC_L_80155A34
    lbz r0, 0x3084(r29)
    cmplwi r0, 0x0
    beq fn_801558CC_L_80155A14
    li r0, 0x0
    stb r0, 0x3084(r29)
    b fn_801558CC_L_80155A20
    fn_801558CC_L_80155A14:
    lfs f0, 0x308c(r29)
    fadds f0, f0, f1
    stfs f0, 0x308c(r29)
    fn_801558CC_L_80155A20:
    lwz r3, 0x4(r29)
    lfs f1, 0x308c(r29)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r29)
    bl HSD_CObjAnim
    fn_801558CC_L_80155A34:
    lwz r3, 0x20(r28)
    cmplwi r3, 0x0
    beq fn_801558CC_L_80155A50
    lfs f1, 0x2c(r28)
    bl Object_SetField8_AndDirty
    lwz r3, 0x20(r28)
    bl clNormal3D_Exec
    fn_801558CC_L_80155A50:
    lwz r3, 0x18(r28)
    bl SetCourseScene3D
    mr r31, r28
    li r29, 0x0
    addi r30, r13, -0x74F8  /* lbl_806CF828 */
    fn_801558CC_L_80155A64:
    lwz r3, 0x34(r31)
    lwz r3, 0xc(r3)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_SnapshotAndFullReset
    lwz r3, 0x20(r28)
    lwz r4, 0x0(r30)
    bl ResolveJointByName
    stw r3, 0x3c(r31)
    lwz r26, 0x3c(r31)
    cmplwi r26, 0x0
    beq fn_801558CC_L_80155B54
    bne fn_801558CC_L_80155AA4
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x47c
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_801558CC_L_80155AA4:
    cmplwi r26, 0x0
    beq fn_801558CC_L_80155AEC
    bne fn_801558CC_L_80155AC0
    addi r3, r2, -0x212C  /* lbl_806D8134 */
    li r4, 0x25d
    addi r5, r2, -0x2124  /* lbl_806D813C */
    bl __assert
    fn_801558CC_L_80155AC0:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_801558CC_L_80155ADC
    rlwinm. r0, r4, 0, 25, 25
    beq fn_801558CC_L_80155ADC
    li r3, 0x1
    fn_801558CC_L_80155ADC:
    clrlwi. r0, r3, 24
    beq fn_801558CC_L_80155AEC
    mr r3, r26
    bl HSD_JObjSetupMatrixSub
    fn_801558CC_L_80155AEC:
    lwz r27, 0x34(r31)
    addi r3, r26, 0x44
    addi r4, r27, 0x14
    bl PSMTXCopy
    lfs f0, 0x20(r27)
    addi r26, r29, 0x44
    stfs f0, 0x44(r27)
    lfs f0, 0x30(r27)
    stfs f0, 0x48(r27)
    lfs f0, 0x40(r27)
    stfs f0, 0x4c(r27)
    lbzx r0, r28, r26
    cmplwi r0, 0x0
    beq fn_801558CC_L_80155BB4
    lwz r3, 0x34(r31)
    lfs f1, lbl_806D8064(r2)
    lwz r3, 0x10(r3)
    bl TornadoEffect_ClearFlagC0AndSetC4
    lwz r3, 0x34(r31)
    lfs f1, lbl_806D8064(r2)
    lwz r3, 0x10(r3)
    lfs f2, lbl_806D8068(r2)
    bl TireEffect_ResetSpin
    li r0, 0x0
    stbx r0, r28, r26
    b fn_801558CC_L_80155BB4
    fn_801558CC_L_80155B54:
    addi r26, r29, 0x44
    lbzx r0, r28, r26
    cmplwi r0, 0x0
    bne fn_801558CC_L_80155BB4
    lfs f1, lbl_806D8064(r2)
    addi r3, r1, 0x48
    lfs f2, lbl_806D8248(r2)
    fmr f3, f1
    bl PSMTXTrans
    lwz r27, 0x34(r31)
    addi r3, r1, 0x48
    addi r4, r27, 0x14
    bl PSMTXCopy
    lfs f0, 0x20(r27)
    stfs f0, 0x44(r27)
    lfs f0, 0x30(r27)
    stfs f0, 0x48(r27)
    lfs f0, 0x40(r27)
    stfs f0, 0x4c(r27)
    lwz r3, 0x34(r31)
    lwz r3, 0x10(r3)
    bl TornadoEffect_SetFlagC0
    li r0, 0x1
    stbx r0, r28, r26
    fn_801558CC_L_80155BB4:
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lwz r3, 0x34(r31)
    fmr f2, f1
    lwz r3, 0xc(r3)
    bl RenderObj_ItemStateMachine_Timed
    lwz r3, 0x34(r31)
    li r4, 0x0
    lwz r3, 0x10(r3)
    bl TornadoEffect_Tick
    lwz r3, 0x34(r31)
    lwz r3, 0xc(r3)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_TickTornadoCooldown
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x2
    addi r31, r31, 0x4
    blt fn_801558CC_L_80155A64
    lfs f2, 0x8(r28)
    lfs f1, lbl_806D8220(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne fn_801558CC_L_80155C60
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f2, f0
    bge fn_801558CC_L_80155C60
    fcmpu cr0, f1, f2
    bne fn_801558CC_L_80155C40
    lwz r4, 0x38(r28)
    lwz r3, 0x48(r28)
    lwz r4, 0xc(r4)
    bl fn_80173B68
    lwz r3, 0x48(r28)
    bl fn_80173C34
    fn_801558CC_L_80155C40:
    lfs f1, lbl_806D8298(r2)
    lfs f0, 0x8(r28)
    fcmpu cr0, f1, f0
    bne fn_801558CC_L_80155C58
    lwz r3, 0x48(r28)
    bl fn_80173BE8
    fn_801558CC_L_80155C58:
    lwz r3, 0x48(r28)
    bl fn_801737F0
    fn_801558CC_L_80155C60:
    lfs f3, 0x8(r28)
    lfs f1, lbl_806D829C(r2)
    fcmpo cr0, f3, f1
    cror eq, gt, eq
    bne fn_801558CC_L_801561D8
    lfs f0, lbl_806D82A0(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_801561D8
    lfs f0, lbl_806D80BC(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_80155C9C
    fsubs f1, f3, f1
    lfs f0, lbl_806D818C(r2)
    fdivs f30, f1, f0
    b fn_801558CC_L_80155CC8
    fn_801558CC_L_80155C9C:
    lfs f0, lbl_806D82A4(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne fn_801558CC_L_80155CC4
    fsubs f1, f3, f0
    lfs f0, lbl_806D818C(r2)
    lfs f2, lbl_806D8068(r2)
    fdivs f0, f1, f0
    fsubs f30, f2, f0
    b fn_801558CC_L_80155CC8
    fn_801558CC_L_80155CC4:
    lfs f30, lbl_806D8068(r2)
    fn_801558CC_L_80155CC8:
    lfs f0, lbl_806D829C(r2)
    lfs f1, lbl_806D82A8(r2)
    fsubs f0, f3, f0
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    fmr f31, f1
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f31, f0
    bge fn_801558CC_L_80155CF0
    fneg f31, f31
    fn_801558CC_L_80155CF0:
    lwz r0, 0x10(r28)
    cmpwi r0, 0x1
    bne fn_801558CC_L_80155F34
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x46
    fmr f4, f3
    lfs f1, lbl_806D82AC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B0(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82B4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8070(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82BC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82C0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82C4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x48
    fmr f4, f3
    lfs f1, lbl_806D82C8(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x44
    fmr f4, f3
    lfs f1, lbl_806D82BC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82CC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x49
    fmr f4, f3
    lfs f1, lbl_806D82D0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82D4(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fmuls f0, f30, f31
    lfs f3, lbl_806D8068(r2)
    lfs f1, lbl_806D82D8(r2)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D82DC(r2)
    stfs f0, 0x8(r1)
    fmr f6, f3
    fmr f7, f3
    lfs f5, lbl_806D8064(r2)
    fmr f8, f3
    lwz r3, 0x4c(r28)
    li r5, 0x4a
    li r6, 0x1
    bl fn_80154FB0
    b fn_801558CC_L_801561D8
    fn_801558CC_L_80155F34:
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1c
    fmr f4, f3
    lfs f1, lbl_806D82AC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B0(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82B4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8070(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82BC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82C0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82C4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82E0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82E4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1e
    fmr f4, f3
    lfs f1, lbl_806D82E8(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1a
    fmr f4, f3
    lfs f1, lbl_806D82EC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82CC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f30, 0x8(r1)
    li r5, 0x1f
    fmr f4, f3
    lfs f1, lbl_806D82D0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82D4(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fmuls f0, f30, f31
    lfs f3, lbl_806D8068(r2)
    lfs f1, lbl_806D82D8(r2)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D82DC(r2)
    stfs f0, 0x8(r1)
    fmr f6, f3
    fmr f7, f3
    lfs f5, lbl_806D8064(r2)
    fmr f8, f3
    lwz r3, 0x4c(r28)
    li r5, 0x20
    li r6, 0x1
    bl fn_80154FB0
    fn_801558CC_L_801561D8:
    lfs f3, 0x8(r28)
    lfs f1, lbl_806D82F0(r2)
    fcmpo cr0, f3, f1
    cror eq, gt, eq
    bne fn_801558CC_L_801567C0
    lfs f0, lbl_806D82F4(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_801567C0
    lfs f0, lbl_806D82E4(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_80156214
    fsubs f1, f3, f1
    lfs f0, lbl_806D818C(r2)
    fdivs f31, f1, f0
    b fn_801558CC_L_80156240
    fn_801558CC_L_80156214:
    lfs f0, lbl_806D8274(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne fn_801558CC_L_8015623C
    fsubs f1, f3, f0
    lfs f0, lbl_806D818C(r2)
    lfs f2, lbl_806D8068(r2)
    fdivs f0, f1, f0
    fsubs f31, f2, f0
    b fn_801558CC_L_80156240
    fn_801558CC_L_8015623C:
    lfs f31, lbl_806D8068(r2)
    fn_801558CC_L_80156240:
    lfs f0, lbl_806D82F0(r2)
    fsubs f1, f3, f0
    bl __cvt_fp2unsigned
    lis r4, 0x38e4
    subi r0, r4, 0x71c7
    mulhwu r0, r0, r3
    srwi r0, r0, 1
    mulli r0, r0, 0x9
    subf r26, r0, r3
    cmplwi r26, 0x5
    blt fn_801558CC_L_80156270
    subfic r26, r26, 0x9
    fn_801558CC_L_80156270:
    lwz r0, 0x10(r28)
    cmpwi r0, 0x1
    bne fn_801558CC_L_80156520
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x46
    fmr f4, f3
    lfs f1, lbl_806D82AC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82F8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82B4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8070(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82BC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82C0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82C4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82E0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D82E4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8300(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x48
    fmr f4, f3
    lfs f1, lbl_806D8304(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x45
    fmr f4, f3
    lfs f1, lbl_806D8214(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D8308(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    addi r5, r26, 0x3e
    stfs f31, 0x8(r1)
    li r4, 0x0
    fmr f4, f3
    lfs f1, lbl_806D830C(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D8310(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    b fn_801558CC_L_801567C0
    fn_801558CC_L_80156520:
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1c
    fmr f4, f3
    lfs f1, lbl_806D82AC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82F8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82B4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8070(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82BC(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82C0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82C4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82E0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D82E4(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8300(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1e
    fmr f4, f3
    lfs f1, lbl_806D8304(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82FC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1b
    fmr f4, f3
    lfs f1, lbl_806D8214(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D8308(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    addi r5, r26, 0x14
    stfs f31, 0x8(r1)
    li r4, 0x0
    fmr f4, f3
    lfs f1, lbl_806D830C(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D8310(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fn_801558CC_L_801567C0:
    lfs f3, 0x8(r28)
    lfs f1, lbl_806D8314(r2)
    fcmpo cr0, f3, f1
    cror eq, gt, eq
    bne fn_801558CC_L_80156CC8
    lfs f0, lbl_806D8318(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_80156CC8
    lfs f0, lbl_806D831C(r2)
    fcmpo cr0, f3, f0
    bge fn_801558CC_L_801567FC
    fsubs f1, f3, f1
    lfs f0, lbl_806D818C(r2)
    fdivs f31, f1, f0
    b fn_801558CC_L_80156828
    fn_801558CC_L_801567FC:
    lfs f0, lbl_806D8320(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne fn_801558CC_L_80156824
    fsubs f1, f3, f0
    lfs f0, lbl_806D818C(r2)
    lfs f2, lbl_806D8068(r2)
    fdivs f0, f1, f0
    fsubs f31, f2, f0
    b fn_801558CC_L_80156828
    fn_801558CC_L_80156824:
    lfs f31, lbl_806D8068(r2)
    fn_801558CC_L_80156828:
    lfs f0, lbl_806D8314(r2)
    lfs f1, lbl_806D82A8(r2)
    fsubs f0, f3, f0
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    fmr f30, f1
    lfs f0, lbl_806D8064(r2)
    fcmpo cr0, f30, f0
    bge fn_801558CC_L_80156850
    fneg f30, f30
    fn_801558CC_L_80156850:
    lwz r0, 0x10(r28)
    cmpwi r0, 0x1
    bne fn_801558CC_L_80156A94
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x46
    fmr f4, f3
    lfs f1, lbl_806D8324(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B0(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8328(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8288(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D832C(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8330(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x47
    fmr f4, f3
    lfs f1, lbl_806D8334(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x48
    fmr f4, f3
    lfs f1, lbl_806D8218(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x43
    fmr f4, f3
    lfs f1, lbl_806D8338(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82CC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x49
    fmr f4, f3
    lfs f1, lbl_806D82D0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82D4(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fmuls f0, f31, f30
    lfs f3, lbl_806D8068(r2)
    lfs f1, lbl_806D82D8(r2)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D82DC(r2)
    stfs f0, 0x8(r1)
    fmr f6, f3
    fmr f7, f3
    lfs f5, lbl_806D8064(r2)
    fmr f8, f3
    lwz r3, 0x4c(r28)
    li r5, 0x4a
    li r6, 0x1
    bl fn_80154FB0
    b fn_801558CC_L_80156CC8
    fn_801558CC_L_80156A94:
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1c
    fmr f4, f3
    lfs f1, lbl_806D8324(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B0(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8328(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8288(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D832C(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8330(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1d
    fmr f4, f3
    lfs f1, lbl_806D8334(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1e
    fmr f4, f3
    lfs f1, lbl_806D8218(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82B8(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x19
    fmr f4, f3
    lfs f1, lbl_806D82D8(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82CC(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    stfs f31, 0x8(r1)
    li r5, 0x1f
    fmr f4, f3
    lfs f1, lbl_806D82D0(r2)
    fmr f6, f3
    lwz r3, 0x4c(r28)
    fmr f7, f3
    lfs f2, lbl_806D82D4(r2)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fmuls f0, f31, f30
    lfs f3, lbl_806D8068(r2)
    lfs f1, lbl_806D82D8(r2)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D82DC(r2)
    stfs f0, 0x8(r1)
    fmr f6, f3
    fmr f7, f3
    lfs f5, lbl_806D8064(r2)
    fmr f8, f3
    lwz r3, 0x4c(r28)
    li r5, 0x20
    li r6, 0x1
    bl fn_80154FB0
    fn_801558CC_L_80156CC8:
    lwz r0, 0x10(r28)
    cmpwi r0, 0x1
    bne fn_801558CC_L_80156D5C
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    lfs f1, lbl_806D833C(r2)
    li r5, 0x4b
    stfs f3, 0x8(r1)
    fmr f4, f3
    fmr f6, f3
    lfs f2, lbl_806D82E4(r2)
    fmr f7, f3
    lwz r3, 0x4c(r28)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    lfs f1, 0x30(r28)
    lfs f0, lbl_806D818C(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_801558CC_L_80156DE0
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    lfs f1, lbl_806D8340(r2)
    li r5, 0x4c
    stfs f3, 0x8(r1)
    fmr f4, f3
    fmr f6, f3
    lfs f2, lbl_806D8344(r2)
    fmr f7, f3
    lwz r3, 0x4c(r28)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    b fn_801558CC_L_80156DE0
    fn_801558CC_L_80156D5C:
    lfs f1, 0x30(r28)
    lfs f0, lbl_806D818C(r2)
    fcmpo cr0, f1, f0
    bge fn_801558CC_L_80156DA8
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    lfs f1, lbl_806D8348(r2)
    li r5, 0x21
    stfs f3, 0x8(r1)
    fmr f4, f3
    fmr f6, f3
    lfs f2, lbl_806D82E4(r2)
    fmr f7, f3
    lwz r3, 0x4c(r28)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    b fn_801558CC_L_80156DE0
    fn_801558CC_L_80156DA8:
    lfs f3, lbl_806D8068(r2)
    li r4, 0x0
    lfs f1, lbl_806D8348(r2)
    li r5, 0x22
    stfs f3, 0x8(r1)
    fmr f4, f3
    fmr f6, f3
    lfs f2, lbl_806D82E4(r2)
    fmr f7, f3
    lwz r3, 0x4c(r28)
    fmr f8, f3
    lfs f5, lbl_806D8064(r2)
    li r6, 0x0
    bl fn_80154FB0
    fn_801558CC_L_80156DE0:
    lfs f2, 0x30(r28)
    lfs f1, lbl_806D8068(r2)
    lfs f0, lbl_806D81B4(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x30(r28)
    cror eq, gt, eq
    bne fn_801558CC_L_80156E08
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x30(r28)
    fn_801558CC_L_80156E08:
    lfs f1, 0x8(r28)
    lfs f0, lbl_806D8220(r2)
    fcmpo cr0, f1, f0
    bge fn_801558CC_L_80156E2C
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne fn_801558CC_L_80156E28
    li r3, 0x0
    fn_801558CC_L_80156E28:
    bl clItemBoxManager_Update
    fn_801558CC_L_80156E2C:
    lfs f1, 0x8(r28)
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_801558CC_L_80156E44
    bl fn_8013A534
    fn_801558CC_L_80156E44:
    lwz r3, 0x18(r28)
    addi r4, r1, 0x3c
    bl CObj_LoadProjMatrix
    lwz r3, 0x18(r28)
    addi r4, r1, 0x30
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x30(r1)
    addi r3, r1, 0x24
    lwz r8, 0x34(r1)
    addi r4, r1, 0x18
    lwz r7, 0x38(r1)
    lwz r6, 0x3c(r1)
    lwz r5, 0x40(r1)
    lwz r0, 0x44(r1)
    stw r9, 0x18(r1)
    stw r8, 0x1c(r1)
    stw r7, 0x20(r1)
    stw r6, 0x24(r1)
    stw r5, 0x28(r1)
    stw r0, 0x2c(r1)
    bl VfxSlotMgr_Update
    bl GXDrawDone
    lwz r27, 0x4c(r28)
    lwz r0, 0xc(r27)
    cmplwi r0, 0x0
    beq fn_801558CC_L_80156F10
    lwz r30, 0x14(r27)
    addi r26, r27, 0x10
    li r29, 0x0
    b fn_801558CC_L_80156F08
    fn_801558CC_L_80156EC0:
    lwz r0, 0xc(r30)
    cmpwi r0, 0x0
    ble fn_801558CC_L_80156ED4
    stw r29, 0xc(r30)
    b fn_801558CC_L_80156F04
    fn_801558CC_L_80156ED4:
    lwz r3, 0x10(r30)
    cmplwi r3, 0x0
    beq fn_801558CC_L_80156EE8
    li r4, 0x1
    bl fn_801F7CD8
    fn_801558CC_L_80156EE8:
    stw r30, 0x14(r1)
    addi r3, r1, 0x10
    addi r4, r27, 0xc
    addi r5, r1, 0x14
    bl fn_80157BE8
    lwz r30, 0x10(r1)
    b fn_801558CC_L_80156F08
    fn_801558CC_L_80156F04:
    lwz r30, 0x4(r30)
    fn_801558CC_L_80156F08:
    cmplw r30, r26
    bne fn_801558CC_L_80156EC0
    fn_801558CC_L_80156F10:
    lfs f1, lbl_806D8060(r2)
    lfs f2, 0x8(r28)
    fcmpo cr0, f2, f1
    bge fn_801558CC_L_80156F3C
    fdivs f0, f2, f1
    lfs f3, lbl_806D8068(r2)
    lfs f2, lbl_806D8064(r2)
    fsubs f1, f3, f0
    bl Saturate_Double
    stfs f1, 0xc(r28)
    b fn_801558CC_L_80156F70
    fn_801558CC_L_80156F3C:
    lfs f0, lbl_806D834C(r2)
    fsubs f0, f0, f1
    fcmpo cr0, f2, f0
    ble fn_801558CC_L_80156F68
    fsubs f0, f2, f0
    lfs f2, lbl_806D8064(r2)
    lfs f3, lbl_806D8068(r2)
    fdivs f1, f0, f1
    bl Saturate_Double
    stfs f1, 0xc(r28)
    b fn_801558CC_L_80156F70
    fn_801558CC_L_80156F68:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0xc(r28)
    fn_801558CC_L_80156F70:
    lfs f2, 0x8(r28)
    lfs f1, lbl_806D8068(r2)
    lfs f0, lbl_806D834C(r2)
    fadds f1, f2, f1
    stfs f1, 0x8(r28)
    lfs f1, 0x8(r28)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_801558CC_L_80156F9C
    li r0, 0x9
    stw r0, 0x4(r28)
    fn_801558CC_L_80156F9C:
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    psq_l f30, 0x98(r1), 0, 0
    lfd f30, 0x90(r1)
    lmw r26, 0x78(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" unsigned char fn_80156FC0(StateObj *o) {
    return o->state == 9;
}

extern "C" asm void fn_80156FD4(void) { /* 0x80156FD4 size:0x26C */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr r31, r3
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq fn_80156FD4_L_8015722C
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80156FD4_L_8015722C
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80156FD4_L_8015716C
    lwz r3, 0x1c(r31)
    bl LObjList_ApplyForCObj
    lwz r3, 0x18(r31)
    bl CObj_DebugVizPathFlush
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80156FD4_L_80157038
    li r3, 0x0
    fn_80156FD4_L_80157038:
    bl clDrawMan_Buckets_Reset
    lwz r3, 0x14(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    li r27, 0x0
    mr r29, r31
    fn_80156FD4_L_80157050:
    lwz r3, 0x3c(r29)
    cmplwi r3, 0x0
    beq fn_80156FD4_L_801570A8
    li r4, 0x10
    bl HSD_JObjClearFlagsAll
    lwz r3, 0x34(r29)
    lwz r3, 0x10(r3)
    bl KartItem_DispatchEffectRenderByState
    lwz r3, 0x3c(r29)
    li r4, 0x0
    li r5, 0x7
    li r6, 0x0
    bl HSD_JObjDispAll
    lwz r3, 0x34(r29)
    lwz r3, 0x10(r3)
    bl KartItem_FlushPendingRender_v2
    lwz r3, 0x34(r29)
    lwz r3, 0x10(r3)
    bl TornadoEffect_SubmitRender
    lwz r3, 0x3c(r29)
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    fn_80156FD4_L_801570A8:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0x2
    blt fn_80156FD4_L_80157050
    lwz r3, 0x20(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80156FD4_L_801570DC
    li r3, 0x0
    fn_80156FD4_L_801570DC:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80156FD4_L_801570F0
    li r3, 0x0
    fn_80156FD4_L_801570F0:
    bl clDrawMan_Buckets_Dispatch
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D8220(r2)
    fcmpo cr0, f1, f0
    bge fn_80156FD4_L_80157118
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne fn_80156FD4_L_80157114
    li r3, 0x0
    fn_80156FD4_L_80157114:
    bl clItemBoxManager_Draw
    fn_80156FD4_L_80157118:
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80156FD4_L_80157130
    bl fn_80139810
    fn_80156FD4_L_80157130:
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D8220(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80156FD4_L_80157158
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f1, f0
    bge fn_80156FD4_L_80157158
    lwz r3, 0x48(r31)
    bl fn_801737CC
    fn_80156FD4_L_80157158:
    lwz r3, 0x18(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_80156FD4_L_8015716C:
    li r30, 0x0
    lwz r28, 0x4c(r31)
    fn_80156FD4_L_80157174:
    cmplwi r30, 0x2
    bge fn_80156FD4_L_801571DC
    lwz r0, 0x18(r28)
    cmplwi r0, 0x0
    beq fn_80156FD4_L_801571DC
    li r3, 0x0
    bl GX_EndDraw
    lwz r29, 0x20(r28)
    addi r27, r28, 0x1c
    b fn_80156FD4_L_801571B0
    fn_80156FD4_L_8015719C:
    lwz r3, 0x8(r29)
    addi r4, r29, 0xc
    lfs f1, lbl_806D806C(r2)
    bl fn_801F7B74
    lwz r29, 0x4(r29)
    fn_80156FD4_L_801571B0:
    cmplw r29, r27
    bne fn_80156FD4_L_8015719C
    bl GX_BeginDraw
    stw r27, 0x10(r1)
    addi r3, r1, 0x8
    addi r4, r28, 0x18
    addi r5, r1, 0xc
    lwz r0, 0x20(r28)
    addi r6, r1, 0x10
    stw r0, 0xc(r1)
    bl fn_80157D30
    fn_80156FD4_L_801571DC:
    addi r30, r30, 0x1
    addi r28, r28, 0xc
    cmplwi r30, 0x2
    blt fn_80156FD4_L_80157174
    lfs f4, 0xc(r31)
    lfs f1, lbl_806D8064(r2)
    fcmpo cr0, f4, f1
    ble fn_80156FD4_L_8015722C
    lfs f0, lbl_806D8090(r2)
    fmr f2, f1
    lfs f3, lbl_806D80C4(r2)
    li r3, 0x0
    fmuls f0, f0, f4
    lfs f4, lbl_806D80C8(r2)
    li r4, 0x0
    li r5, 0x0
    fctiwz f0, f0
    stfd f0, 0x18(r1)
    lwz r6, 0x1c(r1)
    bl DrawColoredQuad
    fn_80156FD4_L_8015722C:
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" void fn_80157240(VObj *p) {
    delete p;
}

extern "C" CamPanel *fn_80157278(CamPanel *self, short flag) {
    if (self != 0) {
        NamCamObj *cam;
        self->vt = lbl_8048FF64;
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

extern "C" asm void fn_80157378(void) { /* 0x80157378 size:0x360 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stfd f29, 0x20(r1)
    psq_st f29, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    lwz r0, 0x4(r3)
    cmpwi r0, 0x9
    beq fn_80157378_L_801576A8
    lfs f4, 0xc(r30)
    lfs f3, lbl_806D8354(r2)
    fcmpo cr0, f4, f3
    cror eq, lt, eq
    bne fn_80157378_L_801573DC
    fdivs f1, f4, f3
    lfs f2, lbl_806D8350(r2)
    lfs f0, lbl_806D81D4(r2)
    fnmsubs f31, f2, f1, f0
    b fn_80157378_L_801573F4
    fn_80157378_L_801573DC:
    lfs f0, lbl_806D835C(r2)
    lfs f2, lbl_806D8350(r2)
    fsubs f1, f4, f0
    lfs f0, lbl_806D8358(r2)
    fdivs f1, f1, f3
    fnmsubs f31, f2, f1, f0
    fn_80157378_L_801573F4:
    lfs f0, lbl_806D8294(r2)
    lwz r0, 0x18(r30)
    fdivs f4, f4, f0
    lfs f3, lbl_806D8360(r2)
    lfs f2, lbl_806D8358(r2)
    cmpwi r0, 0x1
    lfs f1, lbl_806D8368(r2)
    lfs f0, lbl_806D8364(r2)
    fnmsubs f30, f3, f4, f2
    fnmsubs f29, f1, f4, f0
    bne fn_80157378_L_80157488
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x0
    lfs f2, lbl_806D8070(r2)
    li r4, 0x72
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f31
    lfs f2, lbl_806D836C(r2)
    li r3, 0x0
    li r4, 0x71
    li r5, 0x1
    bl fn_801698B4
    fmr f1, f30
    lfs f2, lbl_806D8370(r2)
    li r3, 0x0
    li r4, 0x71
    li r5, 0x1
    bl fn_801698B4
    fmr f1, f29
    lfs f2, lbl_806D8374(r2)
    lfs f3, lbl_806D8378(r2)
    li r3, 0x0
    li r4, 0x70
    li r5, 0x0
    bl fn_801696E4
    b fn_80157378_L_801574EC
    fn_80157378_L_80157488:
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x0
    lfs f2, lbl_806D8070(r2)
    li r4, 0x9
    li r5, 0x0
    bl fn_801698B4
    fmr f1, f31
    lfs f2, lbl_806D836C(r2)
    li r3, 0x0
    li r4, 0x8
    li r5, 0x1
    bl fn_801698B4
    fmr f1, f30
    lfs f2, lbl_806D8370(r2)
    li r3, 0x0
    li r4, 0x8
    li r5, 0x1
    bl fn_801698B4
    fmr f1, f29
    lfs f2, lbl_806D8374(r2)
    lfs f3, lbl_806D8378(r2)
    li r3, 0x0
    li r4, 0x7
    li r5, 0x0
    bl fn_801696E4
    fn_80157378_L_801574EC:
    lfs f3, lbl_806D837C(r2)
    li r3, 0x1
    lfs f1, lbl_806D80B8(r2)
    li r4, 0x55c
    fmr f4, f3
    lfs f2, lbl_806D81C0(r2)
    li r5, 0x0
    bl fn_801697C0
    lbz r0, 0x1c(r30)
    cmplwi r0, 0x0
    beq fn_80157378_L_80157530
    lfs f1, lbl_806D80B8(r2)
    li r3, 0x1
    lfs f2, lbl_806D80E0(r2)
    li r4, 0x50d
    li r5, 0x0
    bl fn_801698B4
    fn_80157378_L_80157530:
    lwz r31, 0x10(r30)
    cmplwi r31, 0x0
    beq fn_80157378_L_80157580
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_80157378_L_80157580
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq fn_80157378_L_80157580
    addi r3, r1, 0x8
    li r4, 0x0
    bl NamCam_GetImageHandle
    cmpwi r3, 0x1
    bne fn_80157378_L_80157580
    lwz r3, 0x8(r1)
    addi r5, r1, 0xc
    lwz r4, 0x4(r31)
    bl NamCam_LoadImage
    li r0, 0x1
    stb r0, 0x1(r31)
    fn_80157378_L_80157580:
    lfs f2, 0xc(r30)
    lfs f1, lbl_806D8068(r2)
    lfs f0, lbl_806D8220(r2)
    fadds f1, f2, f1
    stfs f1, 0xc(r30)
    lfs f1, 0xc(r30)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80157378_L_801575AC
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0xc(r30)
    fn_80157378_L_801575AC:
    lwz r0, 0x4(r30)
    lfs f29, lbl_806D8060(r2)
    cmpwi r0, 0x1
    beq fn_80157378_L_80157644
    bge fn_80157378_L_801575CC
    cmpwi r0, 0x0
    bge fn_80157378_L_801575D8
    b fn_80157378_L_801576A8
    fn_80157378_L_801575CC:
    cmpwi r0, 0x3
    bge fn_80157378_L_801576A8
    b fn_80157378_L_8015766C
    fn_80157378_L_801575D8:
    lfs f0, 0x8(r30)
    lfs f3, lbl_806D8068(r2)
    fadds f0, f0, f3
    stfs f0, 0x8(r30)
    lfs f0, 0x8(r30)
    fcmpo cr0, f0, f29
    bge fn_80157378_L_8015760C
    fdivs f0, f0, f29
    lfs f2, lbl_806D8064(r2)
    fsubs f1, f3, f0
    bl Saturate_Double
    stfs f1, 0x14(r30)
    b fn_80157378_L_80157614
    fn_80157378_L_8015760C:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x14(r30)
    fn_80157378_L_80157614:
    lfs f1, 0x8(r30)
    lfs f0, lbl_806D80EC(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80157378_L_801576A8
    li r3, 0x5
    bl SetSyncTarget
    li r0, 0x1
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r30)
    stfs f0, 0x8(r30)
    b fn_80157378_L_801576A8
    fn_80157378_L_80157644:
    lfs f0, lbl_806D8064(r2)
    stfs f0, 0x14(r30)
    bl PcbSync_AllKartsInValidSelectState
    clrlwi. r0, r3, 24
    beq fn_80157378_L_801576A8
    li r0, 0x2
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r30)
    stfs f0, 0x8(r30)
    b fn_80157378_L_801576A8
    fn_80157378_L_8015766C:
    lfs f3, lbl_806D8068(r2)
    lfs f0, 0x8(r30)
    lfs f2, lbl_806D8064(r2)
    fadds f0, f0, f3
    stfs f0, 0x8(r30)
    lfs f0, 0x8(r30)
    fdivs f1, f0, f29
    bl Saturate_Double
    stfs f1, 0x14(r30)
    lfs f0, 0x8(r30)
    fcmpo cr0, f0, f29
    cror eq, gt, eq
    bne fn_80157378_L_801576A8
    li r0, 0x9
    stw r0, 0x4(r30)
    fn_80157378_L_801576A8:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    psq_l f29, 0x28(r1), 0, 0
    lfd f29, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r0, 0x54(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
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

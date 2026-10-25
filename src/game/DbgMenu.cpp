/* Debug menu and its test scenes (0x800CE54C..0x800D2BE0).
 * NonMatching: these are C++ classes whose vtables (.data 0x8041C99C..)
 * and new/delete extab actions belong to this TU; the scene ctors and
 * dtors are written out by hand against the existing vtable labels. */

class InputPlayer {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual unsigned char IsHeld(int mask);
    virtual unsigned char IsPressed(int mask);
};

class DbgScene {
public:
    virtual unsigned char Update();
    virtual void Render();
    virtual ~DbgScene();
};

class DbgModel {
public:
    virtual ~DbgModel();
};

typedef DbgScene *(*DbgSceneCtor)(void);

typedef struct SceneObj {
    void *vt;
    void *obj;
} SceneObj;

typedef struct DbgMenuEntry {
    DbgSceneCtor ctor;
    char *name;
} DbgMenuEntry;

typedef struct DbgMenu {
    void *vt;
    int sel;
    DbgScene *sub;
} DbgMenu;

typedef struct PaletteSet {
    void *pal;
    int count;
    unsigned char *rgb;
    unsigned char *ci;
    int color;
} PaletteSet;

typedef struct PaletteEntry {
    int unk0;
    void *ci;
} PaletteEntry;

typedef struct ResNode {
    signed char type;
    unsigned char pad[3];
    void *data;
} ResNode;

typedef struct SceneHdr {
    void *vt;
} SceneHdr;

typedef struct SceneWords {
    void *vt;
    int w4;
    int w8;
    int wC;
    int w10;
} SceneWords;

typedef struct SceneF2 {
    void *vt;
    float x;
    float y;
} SceneF2;

typedef struct Sprite {
    unsigned char pad0[4];
    int w4;
    unsigned char pad8[4];
    float x;
    float y;
} Sprite;

typedef struct SpritePair {
    void *vt;
    Sprite *s[4];
} SpritePair;

typedef struct SceneTpl {
    void *vt;
    int w4;
    int w8;
    unsigned char padC[0x24];
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    unsigned char pad44[0x60];
    int wA4;
    int wA8;
    int wAC;
} SceneTpl;

typedef struct SceneItem {
    void *vt;
    int item;
    DbgModel *model;
    int flags;
} SceneItem;

typedef struct ResCtrl {
    int id;
    unsigned char pad4[0xC];
    unsigned char flag10;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    unsigned char pad20[8];
    float w28;
    unsigned char pad2C[4];
    float w;
    unsigned char pad34[0x24];
} ResCtrl;

typedef struct ScrollEntry {
    int id;
    float x;
    float y;
    float w;
} ScrollEntry;

typedef struct ScaleVec {
    float a[3];
    float b[3];
    float c;
} ScaleVec;

extern "C" {
extern void *Alloc(unsigned long size);
extern void MemoryManager_TimedFree(void *p);
extern void GameMode_BaseInit(void *self);
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
extern void OverlayText(int layer, int flag, int row, char *fmt, ...);
extern void fn_8002CFB8(int r, int g, int b, int a);
extern void PreloadResource(int id);
extern void fn_80120A08(int id);
extern void DrawManager_GetOrCreate(void);
extern void fn_80121210(void);
extern void DMAChannelManager_Init(void);
extern void SoundChannels_ClearAll(void);
extern void ItemObjectManager_Init(void);
extern void CourseObjectManager_Init(void);
extern void TEXLoadPalette_Retry(PaletteSet *set, char *name);
extern PaletteEntry *TEXGetPaletteEntry(void *pal, int i);
extern void TEXBindPaletteEntry_CI(void *pal, void *rgb, void *ci, int color, int i);
extern void TEXBindPaletteEntry_RGB(void *pal, void *rgb, int i);
extern void *FUN_8003b120(unsigned long size);
extern void ResCtrl_Init(ResCtrl *r);
extern void fn_80121E10(ResCtrl *r);
extern int SpriteHandle_CreateDefault(ResCtrl *r, int type);
extern void fn_8011FAFC(ResCtrl *r, int type);
extern void clNormal3D_Construct(void *p, char *name, int a);
extern void Sprite_InitWithAnim(void *p, int id, int a, int b);
extern void Sprite_AdvanceAnim(Sprite *s, float t);
extern void fn_801A0004(Sprite *s);
extern void Sprite_Destroy(Sprite *s, int flag);
extern void fn_8019FEF4(Sprite *s);
extern void fn_801A1280(void);
extern void fn_8011FAB8(void);
extern void SetTimerModeEnabled(int on);
extern void SetReverseRoundFlag(int on);
extern void fn_80209AC4(int a, int b);
extern int fn_80209A84(void);
extern void fn_8013DBF8(void);
extern void fn_8013DB9C(void);
extern ScaleVec *fn_8013BE98(int item);
extern void *ItemRes_LookupByKey_Thunk(int item);
extern void fn_8013D800(void *p, void *res, int a);
extern void fn_8013D738(DbgModel *p, float a, float b);
extern void fn_8013D660(DbgModel *p, float a, float b);
extern void fn_8013D634(DbgModel *p, float x, float y, float z);
extern void fn_8013D59C(DbgModel *p, float x, float y, float z);
extern void fn_8013D608(DbgModel *p, float x, float y, float z);
extern void fn_8013D4B0(DbgModel *p, float t);
extern void fn_8013DAC8(DbgModel *p, int a);
extern void fn_8013D940(int a);
extern int Item_GetDescriptorField0(int item, int a);
extern void fn_801695E0(int a, int id, int b, float x, float y, float z);
extern void fn_8020B234(void *p, int a);
extern void fn_8020AF08(void *p, int flag);
extern void fn_8020AFD4(void *p);
extern unsigned char fn_8020B07C(void *p);
extern SceneHdr *DbgScene05_TplTest2_Reset(SceneHdr *p);

extern DbgMenuEntry lbl_8041C920[];
extern int lbl_806CF330;
extern int lbl_806CF32C;
extern char lbl_806D5870[4];
extern char lbl_806D5874[4];
extern void *lbl_8041C99C[];
extern void *lbl_8041C9D4[];
extern void *lbl_8041C9F4[];
extern void *lbl_8041CA14[];
extern void *lbl_8041CA34[];
extern void *lbl_8041CA54[];
extern void *lbl_8041CA74[];
extern void *lbl_8041CA94[];
extern void *lbl_8041CAB4[];
extern void *lbl_8041CAD4[];
extern void *lbl_8041CAF4[];
extern void *lbl_8041CB34[];
extern void *lbl_8041CB54[];
extern void *lbl_8041CB74[];
extern void *lbl_8041CB94[];
extern int lbl_806D14C4;
extern int lbl_806D14C0;
extern int lbl_8041C7E0[16];
extern PaletteSet lbl_8063825C;
extern PaletteSet lbl_806382AC;
extern char lbl_8032D064[];
extern char lbl_8032D084[];
extern char lbl_8032D098[];
extern ScrollEntry lbl_8041C8C0[];
extern float lbl_806D14C8;
extern signed char lbl_806D14CC;
extern const float lbl_806D5878;
extern const float lbl_806D587C;
extern const float lbl_806D5880;
extern const float lbl_806D5884;
extern const float lbl_806D5888;
extern const float lbl_806D588C;
extern const float lbl_806D5890;
extern const float lbl_806D5894;
extern const float lbl_806D5898;
extern const float lbl_806D589C;
extern const float lbl_806D58A0;
extern const float lbl_806D58A4;
extern const float lbl_806D58A8;
extern int g_gameMode;
extern int g_ccClass;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_roundIndex;
}


typedef struct JointEntry {
    char name[0x10];
    int a;
    int b;
} JointEntry;

typedef struct JointTable {
    JointEntry e[0x22];
} JointTable;

typedef struct SceneJoint {
    void *vt;
    DbgModel *view;
    int sel;
} SceneJoint;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Particle {
    float x;
    float y;
    int id;
    int type;
    unsigned char done;
    unsigned char pad11[3];
    unsigned char anim[0xE8];
    int handle;
} Particle;

extern "C" {
extern void fn_8014D4B8(DbgModel *p);
extern unsigned char fn_8014D4F0(void);
extern void fn_8014D540(void *p, int a, int b);
extern JointTable lbl_8032CC64;
extern void GXSetZCompLoc(int a);
extern void GXSetZMode(int a, int b, int c);
extern void GXSetCullMode(int a);
extern void GXSetViewport(float x, float y, float w, float h, float n, float f);
extern void C_MTXOrtho(float m[4][4], float t, float b, float l, float r, float n, float f);
extern void GXSetProjection(float m[4][4], int type);
extern void GXSetScissor(int x, int y, int w, int h);
extern void C_MTXLookAt(float m[3][4], Vec3 *eye, Vec3 *up, Vec3 *at);
extern void GXLoadPosMtxImm(float m[3][4], int id);
extern void GXSetCurrentMtx(int id);
extern void GXSetAlphaCompare(int a, int b, int c, int d, int e);
extern void GXSetChanCtrl(int a, int b, int c, int d, int e, int f, int g);
extern void Object_SetColorRGBA(void *o, int a, float r, float g, float b, float al);
extern void Object_SetJObjPositionXYZ(void *o, float x, float y, float z);
extern void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);
extern void clNormal3D_Exec(void *o);
extern void Object_DriveAnimMatrix(void *o);
extern void Object_RenderJObjTree(void *o, int a);
extern void DbgScene_DrawTexturedQuad(PaletteSet *set, ResCtrl *r, int a);
extern void AnimState_Reset(void *anim, void *src);
extern unsigned char AnimState_Step(void *anim);
extern float Rand_RangeFloat(float lo, float hi);
extern void SpriteHandle_Destroy(int h);
extern void DbgScene_PreloadResourceTree(ResNode *tree);
extern unsigned char lbl_8041C8A0[];
extern Particle lbl_80618C68[500];
extern char lbl_80638068[500];
extern void *lbl_8041CB14[];
extern char lbl_806D58CC[8];
extern const float lbl_806D58AC;
extern const float lbl_806D58B0;
extern const float lbl_806D58B4;
extern const float lbl_806D58B8;
extern const float lbl_806D58BC;
extern const float lbl_806D58C0;
extern const float lbl_806D58C4;
extern const float lbl_806D58C8;
extern const float lbl_806D58D4;
extern const float lbl_806D5908;
extern const float lbl_806D5904;
extern const float lbl_806D58F4;
extern const float lbl_806D58F0;
extern const float lbl_806D58EC;
extern const float lbl_806D58E8;
extern const float lbl_806D58E4;
extern const float lbl_806D58E0;
}


typedef union WGPipe {
    unsigned char u8;
    float f32;
} WGPipe;

#define GXFIFO (*(volatile WGPipe *)0xCC008000)

typedef struct TexHeader {
    unsigned short height;
    unsigned short width;
} TexHeader;

typedef struct TexPalEntry {
    TexHeader *tex;
    void *ci;
} TexPalEntry;

typedef struct ResCtrlFull {
    int id;
    int unk4;
    int mode;
    int unkC;
    unsigned char flag10;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    float width;
    float height;
    unsigned char pad28[0xC];
    int colors[4];
    unsigned char pad44[0x14];
} ResCtrlFull;

extern "C" {
extern void GXSetBlendMode(int a, int b, int c, int d);
extern void GXSetNumTexGens(int n);
extern void GXSetTexCoordGen2(int a, int b, int c, int d, int e, int f);
extern void GXSetNumChans(int n);
extern void GXSetNumTevStages(int n);
extern void GXSetTevOrder(int a, int b, int c, int d);
extern void GXSetTevOp(int a, int b);
extern void GXSetTevColorIn(int a, int b, int c, int d, int e);
extern void GXSetTevColorOp(int a, int b, int c, int d, int e, int f);
extern void GXSetTevAlphaIn(int a, int b, int c, int d, int e);
extern void GXSetTevAlphaOp(int a, int b, int c, int d, int e, int f);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int a, int b);
extern void GXSetVtxAttrFmt(int a, int b, int c, int d, int e);
extern void GXLoadTexObj(void *obj, int id);
extern void GXLoadTlut(void *obj, int id);
extern void GXBegin(int prim, int fmt, int n);
}


class Scene3D {
public:
    virtual ~Scene3D();
    virtual unsigned char Begin();
    virtual void End();
};

class InputAxes {
public:
    virtual void v8();
    virtual void vC();
    virtual float StickX();
    virtual void v14();
    virtual float StickZ();
    virtual float StickY();
};

typedef struct TplScene {
    void *vt;
    int state;
    int inited;
    unsigned char quit;
    unsigned char next;
    unsigned char save;
    unsigned char inc;
    unsigned char dec;
    unsigned char b11;
    unsigned char b12;
    unsigned char b13;
    unsigned char b14;
    unsigned char pad15[3];
    float yawP;
    float yawN;
    float pitchP;
    float pitchN;
    float zoomP;
    float zoomN;
    int sel;
    int cup;
    int lr;
    int rev;
    int variant;
    Vec3 pos;
    Vec3 target;
    float yaw;
    float pitch;
    float dist;
    int mode;
    int savedMode;
    Vec3 saved;
    float t;
    Vec3 a;
    Vec3 b;
    Vec3 c;
    void *env;
    Scene3D *scene;
    void *obj;
} TplScene;

typedef struct NameEntry {
    char *name;
} NameEntry;

extern "C" {
extern char lbl_8032CB38[];
extern void *lbl_8041AC24[];
extern DbgModel *lbl_806D10D0;
extern DbgModel *lbl_806D10AC;
extern char lbl_806D58F8[8];
extern char lbl_806D5900[4];
extern void CourseEnvironment_Dtor(void *p, int flag);
extern void Object_DtorWithGXSync(void *p, int flag);
extern void ItemObjectManager_Reset(void);
extern void VfxSlotMgr_Shutdown(void);
extern void ClRomTable_PurgeAll(void);
extern void SceneDrawList_Reset(void);
extern void clDrawMan_Buckets_Reset(DbgModel *m);
extern void clDrawMan_EndFrame_NoOp(DbgModel *m);
extern void clDrawMan_Buckets_Dispatch(DbgModel *m);
extern void CObj_DebugVizPathFlush(Scene3D *s);
extern void CourseEnvironment_RenderObjects_Timed(void *e);
extern void Subsystem36c_DispatchPass2_Timed(void *e);
extern void clItemBoxManager_Draw(DbgModel *m);
extern void clItemBoxManager_Update(DbgModel *m);
extern void Object_JObjUpdate_870(void *o, int flags);
extern void Object_SetJObjPositionVec(void *o, Vec3 *v);
extern void InputManager_Init(void *p);
extern NameEntry *GetKartModelNameEntry(int a, int b);
extern void Scene3D_Init(void *p, char *name);
extern void GetStartPosition(int a, float *x, float *y, float *z);
extern float GetCourseStartYaw(void);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateX(Vec3 *dst, Vec3 *src, float a);
extern void Vec2_RotateY(Vec3 *dst, Vec3 *src, float a);
extern void Vec3_Add_DestFirst(Vec3 *dst, Vec3 *a, Vec3 *b);
extern void Vec3_Subtract_DestFirst(Vec3 *dst, Vec3 *a, Vec3 *b);
extern void Vec3_Copy(Vec3 *dst, Vec3 *src);
extern void Vec3_Lerp(Vec3 *dst, Vec3 *a, Vec3 *b, float t);
extern float Vec3_HorizontalYawTo(Vec3 *a, Vec3 *b);
extern float Vec3_PitchTo(Vec3 *a, Vec3 *b);
extern float fn_800D3184(Vec3 *a, Vec3 *b);
extern float BuildOrientationFromYaw(float a);
extern void GetCourseBgmEntry(void);
extern void SoundDriver_GetOrCreate(void);
extern void DebugPrintf(char *fmt, ...);
extern void CObj_LoadIntoGX(Scene3D *s, Vec3 *v);
extern void CObj_ApplyViewport(Scene3D *s, Vec3 *v);
extern void SetCourseScene3D(Scene3D *s);
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *e);
extern float FAbs_FloatAsDouble(float x);
extern void DbgScene03_TplTest_PollInput(TplScene *s);
extern void DbgScene03_TplTest_SelectStage(TplScene *s);
extern void DbgScene03_TplTest_UpdateCamera(TplScene *s);
}

#define STR(off) (str + (off))



extern "C" {
extern int lbl_806CF320;
extern int lbl_8041C860[];
extern void *lbl_8041C820[16];
extern char lbl_806D5914[8];
extern void AnimState_New(void *anim, void *src);
}

static inline void SceneBase_Init(void *p)
{
    ((SceneHdr *)p)->vt = lbl_8041C9D4;
}

#define Pad0() InputMgr_GetPlayer(GetInputManager(), 0)
static inline InputPlayer *Pad0_unused(void)
{
    return InputMgr_GetPlayer(GetInputManager(), 0);
}

extern "C" void DbgMenu_TickSubScene(DbgMenu *self)
{
    if (self->sub != 0) {
        self->sub->Render();
    }
}

extern "C" int DbgMenu_HandleInput(DbgMenu *self)
{
    if (self->sub == 0) {
        InputPlayer *pad = Pad0();
        int i;

        if (pad->IsHeld(0x400) == 1) {
            return -4;
        }
        if (pad->IsHeld(0x40) == 1) {
            self->sel = (self->sel + lbl_806CF330 - 1) % lbl_806CF330;
        }
        if (pad->IsHeld(0x80) == 1) {
            self->sel = (self->sel + lbl_806CF330 + 1) % lbl_806CF330;
        }
        if (pad->IsHeld(1) == 1) {
            self->sub = lbl_8041C920[self->sel].ctor();
        }
        OverlayText(2, 0, self->sel, lbl_806D5870);
        for (i = 0; i < lbl_806CF330; i++) {
            OverlayText(2, 2, i, lbl_806D5874, lbl_8041C920[i].name);
        }
    } else if (self->sub->Update()) {
        delete self->sub;
        self->sub = 0;
        fn_8002CFB8(0, 0, 0, 0);
    }
    return -2;
}

extern "C" SceneWords *DbgScene00_SpriteViewer_Ctor(void)
{
    SceneWords *p = (SceneWords *)Alloc(0xC);
    if (p != 0) {
        GameMode_BaseInit(p);
        p->vt = lbl_8041C99C;
        p->w4 = 8;
        p->w8 = 0;
    }
    return p;
}

extern "C" SceneHdr *DbgScene01_SprMng2Test_Ctor(void)
{
    SceneHdr *p = (SceneHdr *)Alloc(4);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CB94;
        lbl_806D14C4 = 0x2AFA;
        PreloadResource(0x2AFA);
    }
    return p;
}

extern "C" SceneF2 *DbgScene02_MapViewer_Ctor(void)
{
    SceneF2 *p = (SceneF2 *)Alloc(0xC);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CB74;
        p->x = 320.0f;
        p->y = 240.0f;
        fn_8002CFB8(0xFF, 0xFF, 0xFF, 0);
        fn_8002CFB8(0x64, 0x64, 0x64, 0);
    }
    return p;
}

extern "C" SceneTpl *DbgScene03_TplTest_Ctor(void)
{
    SceneTpl *p = (SceneTpl *)Alloc(0xB0);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CB54;
        DrawManager_GetOrCreate();
        fn_80121210();
        DMAChannelManager_Init();
        SoundChannels_ClearAll();
        ItemObjectManager_Init();
        CourseObjectManager_Init();
        p->w4 = 0;
        p->w8 = 0;
        p->w30 = 0;
        p->w34 = 1;
        p->w38 = 0;
        p->w3C = 0;
        p->w40 = 0;
        p->wA4 = 0;
        p->wA8 = 0;
        p->wAC = 0;
    }
    return p;
}

static inline int NextPaletteColor(void)
{
    int c = lbl_8041C7E0[lbl_806D14C0++];
    if (lbl_806D14C0 >= 16) {
        lbl_806D14C0 = 0;
    }
    return c;
}

#define LOAD_PALETTE_SET(set, name)                                                   \
    TEXLoadPalette_Retry(&set, name);                                                 \
    if (set.pal != 0) {                                                               \
        int i;                                                                        \
        set.count = *(int *)((unsigned char *)set.pal + 4);                           \
        set.rgb = (unsigned char *)FUN_8003b120(set.count << 5);                      \
        set.ci = (unsigned char *)FUN_8003b120(set.count * 0xC);                      \
        for (i = 0; i < set.count; i++) {                                             \
            if (TEXGetPaletteEntry(set.pal, i)->ci != 0) {                            \
                set.color = lbl_8041C7E0[lbl_806D14C0++];                             \
                if (lbl_806D14C0 >= 16) {                                             \
                    lbl_806D14C0 = 0;                                                 \
                }                                                                     \
                TEXBindPaletteEntry_CI(set.pal, set.rgb + i * 0x20, set.ci + i * 0xC, \
                                       set.color, i);                                 \
            } else {                                                                  \
                TEXBindPaletteEntry_RGB(set.pal, set.rgb + i * 0x20, i);              \
            }                                                                         \
        }                                                                             \
    }

extern "C" SceneHdr *DbgScene04_AnmTest_Ctor(void)
{
    SceneHdr *p = (SceneHdr *)Alloc(4);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CB34;
        LOAD_PALETTE_SET(lbl_8063825C, lbl_8032D064)
    }
    return p;
}

extern "C" DbgScene *DbgScene05_TplTest2_Ctor(void)
{
    void *p = Alloc(4);
    if (p != 0) {
        DbgScene05_TplTest2_Reset((SceneHdr *)p);
    }
    return (DbgScene *)p;
}

extern "C" SceneHdr *DbgScene06_SprMng2Test_Ctor(void)
{
    SceneHdr *p = (SceneHdr *)Alloc(4);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CAF4;
        LOAD_PALETTE_SET(lbl_806382AC, lbl_8032D084)
        fn_8002CFB8(0, 0x80, 0, 0);
    }
    return p;
}

extern "C" SceneHdr *DbgScene07_ScrEffTest_Ctor(void)
{
    SceneHdr *p = (SceneHdr *)Alloc(4);
    if (p != 0) {
        ResCtrl r;
        SceneBase_Init(p);
        p->vt = lbl_8041CAD4;
        ResCtrl_Init(&r);
        fn_80121E10(&r);
        r.id = 0x868;
        r.flag10 = 1;
        r.x = 320.0f;
        r.y = 240.0f;
        r.z = 1.0f;
        SpriteHandle_CreateDefault(&r, 0);
    }
    return p;
}

static inline void AtrTest_Init(SceneObj *self)
{
    void *n;
    SceneBase_Init(self);
    self->vt = lbl_8041CAB4;
    n = Alloc(0x5C);
    if (n != 0) {
        clNormal3D_Construct(n, lbl_8032D098, 1);
    }
    self->obj = n;
}

extern "C" SceneObj *DbgScene08_AtrTest_Ctor(void)
{
    SceneObj *p = (SceneObj *)Alloc(8);
    if (p != 0) {
        AtrTest_Init(p);
    }
    return p;
}

extern "C" SceneWords *DbgScene09_Flash_Ctor(void)
{
    SceneWords *p = (SceneWords *)Alloc(0xC);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CA94;
        p->w4 = 0;
        p->w8 = 0x1C;
    }
    return p;
}

static inline Sprite *NewSprite(int id)
{
    Sprite *s = (Sprite *)Alloc(0x30);
    if (s != 0) {
        Sprite_InitWithAnim(s, id, 1, 0);
    }
    return s;
}

extern "C" SpritePair *DbgScene10_TtlTest_Ctor(void)
{
    SpritePair *p = (SpritePair *)Alloc(0x14);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CA74;
        p->s[0] = 0;
        p->s[1] = 0;
        p->s[2] = 0;
        p->s[3] = 0;
        p->s[0] = NewSprite(0x13D);
        p->s[0]->x = 320.0f;
        p->s[0]->y = 240.0f;
        p->s[1] = NewSprite(0x10B);
        p->s[1]->x = 320.0f;
        p->s[1]->y = 240.0f;
    }
    return p;
}

extern "C" SceneHdr *DbgScene11_Empty_Ctor(void)
{
    SceneHdr *p = (SceneHdr *)Alloc(4);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CA54;
    }
    return p;
}

extern "C" SpritePair *DbgScene12_PrzTest_Ctor(void)
{
    SpritePair *p = (SpritePair *)Alloc(8);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CA34;
        p->s[0] = NewSprite(0x138);
        p->s[0]->w4 = 0;
        fn_8019FEF4(p->s[0]);
    }
    return p;
}

static inline void SetupRaceDefaults(void)
{
    SetTimerModeEnabled(1);
    g_gameMode = 0;
    g_ccClass = 0;
    g_cupId = 1;
    g_longRoundFlag = 0;
    SetReverseRoundFlag(0);
    g_courseVariantIdx = 0;
    g_roundIndex = 0;
    fn_80209AC4(1, 0);
}

extern "C" SceneItem *DbgScene13_PrxTest2_Ctor(void)
{
    SceneItem *p = (SceneItem *)Alloc(0x10);
    if (p != 0) {
        SceneBase_Init(p);
        p->vt = lbl_8041CA14;
        p->flags = 3;
        SetupRaceDefaults();
        p->item = fn_80209A84();
        if (p->flags & 1) {
            ScaleVec *v;
            void *m;
            fn_8013DBF8();
            v = fn_8013BE98(p->item);
            m = Alloc(0x20);
            if (m != 0) {
                fn_8013D800(m, ItemRes_LookupByKey_Thunk(p->item), 1);
            }
            p->model = (DbgModel *)m;
            fn_8013D738(p->model, 0.0f, 1.0f);
            fn_8013D660(p->model, 114.0f, 358.0f);
            fn_8013D634(p->model, 0.02f * v->a[0], 0.02f * v->a[1], 0.02f * v->a[2]);
            fn_8013D59C(p->model, 0.017453292f * v->b[0], 0.017453292f * v->b[1], 0.017453292f * v->b[2]);
            {
                float s = 0.02f * v->c;
                fn_8013D608(p->model, s, s, s);
            }
            PreloadResource(0x14E2);
        }
        if (p->flags & 2) {
            PreloadResource(0x14E2);
            PreloadResource(Item_GetDescriptorField0(p->item, 0));
        }
    }
    return p;
}

extern "C" SceneObj *TestMenuRaceStart_Ctor(void)
{
    SceneObj *p = (SceneObj *)Alloc(8);
    if (p != 0) {
        void *m;
        SceneBase_Init(p);
        p->vt = lbl_8041C9F4;
        SetupRaceDefaults();
        m = Alloc(0x24);
        if (m != 0) {
            fn_8020B234(m, 0x12C);
        }
        p->obj = m;
    }
    return p;
}

extern "C" SceneObj *TestMenuRaceStart_Dtor(SceneObj *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041C9F4;
        if (self->obj != 0) {
            fn_8020AF08(self->obj, 1);
            self->obj = 0;
        }
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuRaceStart_Render(SceneObj *self)
{
    if (self->obj != 0) {
        fn_8020AFD4(self->obj);
    }
}

extern "C" unsigned char TestMenuRaceStart_Update(SceneObj *self)
{
    if (Pad0()->IsHeld(1) == 1) {
        return 1;
    }
    if (self->obj != 0 && fn_8020B07C(self->obj)) {
        fn_8020AF08(self->obj, 1);
        self->obj = 0;
    }
    return 0;
}

extern "C" SceneItem *TestMenuItemDesc_Dtor(SceneItem *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CA14;
        if (self->flags & 1) {
            delete self->model;
            fn_8013DB9C();
            fn_80120A08(0x14E2);
        }
        if (self->flags & 2) {
            fn_80120A08(0x14E2);
            fn_80120A08(Item_GetDescriptorField0(self->item, 0));
        }
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuItemDesc_Render(SceneItem *self)
{
    if (self->flags & 1) {
        fn_8011FAB8();
        fn_8013D940(7);
    }
    if (self->flags & 2) {
        fn_8011FAB8();
    }
}

extern "C" unsigned char TestMenuItemDesc_Update(SceneItem *self)
{
    if (Pad0()->IsHeld(1) == 1) {
        return 1;
    }
    if (self->flags & 1) {
        fn_801695E0(0, 0x14E2, 0, 113.0f, 374.0f, 1.0f);
        fn_8013D4B0(self->model, 1.0f);
        fn_8013DAC8(self->model, 7);
    }
    if (self->flags & 2) {
        fn_801695E0(0, 0x14E2, 0, 413.0f, 374.0f, 1.0f);
        fn_801695E0(0, Item_GetDescriptorField0(self->item, 0), 0, 413.0f, 374.0f, 1.0f);
    }
    return 0;
}

extern "C" SceneHdr *TestMenuScrollList_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CA34;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuScrollList_Render(void)
{
    fn_8011FAB8();
}

extern "C" unsigned char TestMenuScrollList_Update(SpritePair *self)
{
    ScrollEntry *e;
    InputPlayer *pad;
    int i;

    if (!lbl_806D14CC) {
        lbl_806D14CC = 1;
        lbl_806D14C8 = -0.2f;
    }
    pad = Pad0();
    if (pad->IsHeld(0x400) == 1) {
        return 1;
    }
    if (pad->IsPressed(1) == 1) {
        for (i = 0, e = lbl_8041C8C0; i < lbl_806CF32C; i++, e++) {
            ResCtrl r;
            ResCtrl_Init(&r);
            fn_80121E10(&r);
            r.id = e->id;
            r.flag10 = 1;
            r.x = e->x;
            r.y = lbl_806D14C8 + e->y;
            r.z = 1.0f;
            r.w28 = e->w;
            fn_8011FAFC(&r, 7);
        }
    }
    fn_801A1280();
    Sprite_AdvanceAnim(self->s[0], 0.0165f);
    fn_801A0004(self->s[0]);
    return 0;
}

extern "C" SceneHdr *TestMenuPageD_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CA54;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_800CF754(void)
{
}

extern "C" unsigned char TestMenuPageD_Update(void)
{
    return Pad0()->IsHeld(0x400) == 1;
}

extern "C" SpritePair *TestMenuFourSprite_Dtor(SpritePair *self, short flag)
{
    if (self != 0) {
        int i;
        self->vt = lbl_8041CA74;
        for (i = 0; i < 4; i++) {
            if (self->s[i] != 0) {
                Sprite_Destroy(self->s[i], 1);
            }
        }
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuFourSprite_Render(void)
{
    fn_8011FAB8();
}

extern "C" unsigned char TestMenuFourSprite_Update(SpritePair *self)
{
    int i;

    if (Pad0()->IsHeld(0x400) == 1) {
        return 1;
    }
    fn_801A1280();
    for (i = 0; i < 4; i++) {
        if (self->s[i] != 0) {
            Sprite_AdvanceAnim(self->s[i], 0.0165f);
            fn_801A0004(self->s[i]);
        }
    }
    return 0;
}

extern "C" SceneJoint *TestMenuJointBrowser_Dtor(SceneJoint *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CA94;
        if (self->view != 0) {
            delete self->view;
        }
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuJointBrowser_Render(SceneJoint *self)
{
    if (self->view != 0) {
        fn_8014D4B8(self->view);
    }
    fn_8011FAB8();
}

extern "C" unsigned char TestMenuJointBrowser_Update(SceneJoint *self)
{
    InputPlayer *pad = Pad0();

    if (pad->IsHeld(0x400) == 1) {
        return 1;
    }
    if (!self->view) {
        JointTable t = lbl_8032CC64;

        if (pad->IsHeld(2)) {
            self->sel++;
        }
        if (pad->IsHeld(4)) {
            self->sel--;
        }
        if (pad->IsHeld(0x80)) {
            self->sel++;
        }
        self->sel = (self->sel + 0x22) % 0x22;
        OverlayText(2, 0, 0, lbl_806D5874, t.e[self->sel].name);
        if (pad->IsHeld(1)) {
            void *m = Alloc(0x44);
            if (m != 0) {
                fn_8014D540(m, t.e[self->sel].a, t.e[self->sel].b);
            }
            self->view = (DbgModel *)m;
        }
    } else if (fn_8014D4F0()) {
        delete self->view;
        self->view = 0;
    }
    return 0;
}

extern "C" SceneHdr *TestMenuModelView_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CAB4;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline void DbgScene_Setup2D(void)
{
    float proj[4][4];
    float view[3][4];
    Vec3 eye;
    Vec3 up;
    Vec3 at;
    float d;

    GXSetZCompLoc(0);
    GXSetZMode(0, 7, 1);
    GXSetCullMode(2);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    C_MTXOrtho(proj, 240.0f, -240.0f, -320.0f, 320.0f, 100.0f, 1000.0f);
    GXSetProjection(proj, 1);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    up.x = 0.0f;
    up.y = -1.0f;
    up.z = 0.0f;
    d = up.y * up.x;
    eye.x = 320.0f - d;
    eye.y = 240.0f - d;
    eye.z = -300.0f;
    at.x = eye.x;
    at.y = eye.y;
    at.z = up.x;
    C_MTXLookAt(view, &eye, &up, &at);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetAlphaCompare(4, 0, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
}

extern "C" void TestMenuModelView_Render(SceneObj *self)
{
    DbgScene_Setup2D();
    Object_SetColorRGBA(self->obj, 0, 1.0f, 1.0f, 1.0f, 1.0f);
    Object_SetJObjPositionXYZ(self->obj, 100.0f, 100.0f, 0.0f);
    Object_SetJObjScaleXYZ(self->obj, 1.0f, 1.0f, 1.0f);
    clNormal3D_Exec(self->obj);
    Object_DriveAnimMatrix(self->obj);
    Object_RenderJObjTree(self->obj, 7);
}

extern "C" unsigned char TestMenuModelView_Update(void)
{
    return Pad0()->IsHeld(0x400) == 1;
}

extern "C" SceneHdr *TestMenuFwp_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CAD4;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuFwp_Render(void)
{
    fn_8011FAB8();
}

extern "C" unsigned char TestMenuFwp_Update(void)
{
    if (Pad0()->IsHeld(0x400) == 1) {
        return 1;
    }
    OverlayText(1, 0, 1, lbl_806D58CC, 0xF8);
    return 0;
}

extern "C" SceneHdr *TestMenuModelText_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CAF4;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void TestMenuModelText_Render(void)
{
    ResCtrl r;

    DbgScene_Setup2D();
    ResCtrl_Init(&r);
    fn_80121E10(&r);
    r.flag10 = 1;
    r.x = 0.0f;
    r.y = 0.0f;
    r.z = 1.0f;
    DbgScene_DrawTexturedQuad(&lbl_806382AC, &r, 0);
}

extern "C" unsigned char DbgScene05_TplTest2_InputCheck(void)
{
    return Pad0()->IsHeld(0x400) == 1;
}

extern "C" SceneHdr *DbgScene05_TplTest2_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CB14;
        fn_80121210();
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void DbgScene05_TplTest2_SetupBlit(void)
{
    fn_8011FAB8();
}

static inline void Particle_Reset(Particle *e, void *anim)
{
    e->x = 0.0f;
    e->y = 0.0f;
    e->id = -1;
    e->type = 0;
    e->done = 0;
    AnimState_Reset(e->anim, anim);
}

static inline int Particle_Spawn(void *anim)
{
    int i;

    if (anim == 0) {
        return 0;
    }
    for (i = 0; i < 500; i++) {
        if (!lbl_80638068[i]) {
            Particle *e = &lbl_80618C68[i];
            Particle_Reset(e, anim);
            e->handle = 0;
            lbl_80638068[i] = 1;
            return i + 1;
        }
    }
    return 0;
}

static inline void Particle_SetPos(int h, float x, float y)
{
    if (h != 0) {
        lbl_80618C68[h - 1].x = x;
        lbl_80618C68[h - 1].y = y;
    }
}

static inline void Particle_SetState(int h, char state)
{
    if (h != 0) {
        lbl_80638068[h - 1] = state;
    }
}

extern "C" unsigned char DbgScene05_TplTest2_Update(void)
{
    int i;
    int h;

    if (Pad0()->IsHeld(0x400) == 1) {
        return 1;
    }
    h = Particle_Spawn(lbl_8041C8A0);
    Particle_SetPos(h, Rand_RangeFloat(0.0f, 640.0f), Rand_RangeFloat(0.0f, 480.0f));
    Particle_SetState(h, 2);
    for (i = 0; i < 500; i++) {
        Particle *e = &lbl_80618C68[i];
        if (lbl_80638068[i]) {
            e->done = AnimState_Step(e->anim);
            if (e->handle == 0 && e->id != -1) {
                ResCtrl r;
                ResCtrl_Init(&r);
                fn_80121E10(&r);
                r.id = e->id;
                e->handle = (int)SpriteHandle_CreateDefault(&r, e->type);
            }
            if (lbl_80638068[i] == 2 && e->done) {
                SpriteHandle_Destroy(e->handle);
                Particle_Reset(e, 0);
                e->handle = 0;
                lbl_80638068[i] = 0;
            }
        }
    }
    return 0;
}

extern "C" SceneHdr *DbgScene05_TplTest2_Reset(SceneHdr *self)
{
    int i;

    SceneBase_Init(self);
    self->vt = lbl_8041CB14;
    for (i = 0; i < 500; i++) {
        Particle_Reset(&lbl_80618C68[i], 0);
        lbl_80618C68[i].handle = 0;
        lbl_80638068[i] = 0;
    }
    DbgScene_PreloadResourceTree((ResNode *)lbl_8041C8A0);
    return self;
}

extern "C" SceneHdr *DbgScene04_AnmTest_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CB34;
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline void Vtx(float *p, float *t)
{
    GXFIFO.f32 = p[0];
    GXFIFO.f32 = p[1];
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.f32 = t[0];
    GXFIFO.f32 = t[1];
    GXFIFO.f32 = t[0];
    GXFIFO.f32 = t[1];
}

extern "C" void DbgScene04_AnmTest_Draw(void)
{
    ResCtrlFull r;
    float pos[4][2];
    float uv[4][2];
    TexPalEntry *e0;
    TexPalEntry *e1;
    float hw;
    float hh;
    int i;
    PaletteSet *set;

    ResCtrl_Init((ResCtrl *)&r);
    fn_80121E10((ResCtrl *)&r);
    r.mode = 2;
    r.flag10 = 0;
    r.x = 0.0f;
    r.y = 0.0f;
    r.z = 1.0f;
    r.width = 640.0f;
    r.height = 480.0f;
    r.colors[0] = -1;
    r.colors[1] = -1;
    r.colors[2] = -1;
    r.colors[3] = -1;
    fn_8011FAFC((ResCtrl *)&r, 0);
    fn_8011FAB8();
    DbgScene_Setup2D();
    GXSetBlendMode(1, 4, 5, 0xF);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
    GXSetNumChans(1);
    GXSetNumTevStages(2);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 1, 1, 0xFF);
    GXSetTevOp(0, 0);
    GXSetTevColorIn(1, 0, 0xF, 0xF, 0xF);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(1, 7, 4, 0, 7);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 0, 4, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetVtxDesc(0xE, 1);
    GXSetVtxAttrFmt(0, 0xE, 1, 4, 0);
    set = &lbl_8063825C;
    e0 = (TexPalEntry *)TEXGetPaletteEntry(set->pal, 0);
    e1 = (TexPalEntry *)TEXGetPaletteEntry(lbl_8063825C.pal, 1);
    GXLoadTexObj(lbl_8063825C.rgb, 0);
    if (e0->ci != 0) {
        GXLoadTlut(set->ci, 0);
    }
    GXLoadTexObj(set->rgb + 0x20, 1);
    if (e1->ci != 0) {
        GXLoadTlut(set->ci + 0xC, 1);
    }
    hw = e0->tex->width / 2.0f;
    hh = e0->tex->height / 2.0f;
    pos[0][0] = 320.0f - hw;
    pos[0][1] = 240.0f - hh;
    pos[1][0] = 320.0f + hw;
    pos[1][1] = 240.0f - hh;
    pos[2][0] = 320.0f + hw;
    pos[2][1] = 240.0f + hh;
    pos[3][0] = 320.0f - hw;
    pos[3][1] = 240.0f + hh;
    uv[0][0] = 0.0f;
    uv[0][1] = 0.0f;
    uv[1][0] = 1.0f;
    uv[1][1] = 0.0f;
    uv[2][0] = 1.0f;
    uv[2][1] = 1.0f;
    uv[3][0] = 0.0f;
    uv[3][1] = 1.0f;
    GXBegin(0x80, 0, 4);
    for (i = 0; i < 4; i++) {
        Vtx(pos[i], uv[i]);
    }
}

extern "C" unsigned char DbgScene04_AnmTest_InputCheck(void)
{
    return Pad0()->IsHeld(0x400) == 1;
}

extern "C" TplScene *DbgScene03_TplTest_Dtor(TplScene *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CB54;
        if (self->env != 0) {
            CourseEnvironment_Dtor(self->env, 1);
        }
        if (self->scene != 0) {
            delete self->scene;
        }
        if (self->obj != 0) {
            Object_DtorWithGXSync(self->obj, 1);
        }
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        SceneDrawList_Reset();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline DbgModel *DrawMan(void)
{
    DbgModel *m = lbl_806D10AC;
    return m == 0 ? 0 : m;
}

static inline DbgModel *ItemBoxMan(void)
{
    DbgModel *m = lbl_806D10D0;
    return m == 0 ? 0 : m;
}

extern "C" void DbgScene03_TplTest_Draw(TplScene *self)
{
    if (self->scene != 0 && self->env != 0 && self->scene->Begin()) {
        clDrawMan_Buckets_Reset(DrawMan());
        CObj_DebugVizPathFlush(self->scene);
        CourseEnvironment_RenderObjects_Timed(self->env);
        Subsystem36c_DispatchPass2_Timed(self->env);
        clItemBoxManager_Draw(ItemBoxMan());
        Object_JObjUpdate_870(self->obj, 0x800);
        Object_SetJObjPositionVec(self->obj, &self->target);
        Object_SetJObjScaleXYZ(self->obj, 1.0f, 1.0f, 1.0f);
        Object_DriveAnimMatrix(self->obj);
        clNormal3D_Exec(self->obj);
        Object_SetColorRGBA(self->obj, 0, 1.0f, 1.0f, 1.0f, 1.0f);
        Object_RenderJObjTree(self->obj, 7);
        clDrawMan_EndFrame_NoOp(DrawMan());
        clDrawMan_Buckets_Dispatch(DrawMan());
        self->scene->End();
    }
}

static inline void OrbitOffset(Vec3 *v, TplScene *self, float d)
{
    GetSpawnPosition(v, 0.0f, 0.0f, d);
    Vec2_RotateX(v, v, self->pitch);
    Vec2_RotateY(v, v, self->yaw);
}

static inline int TurnYawPitch(TplScene *self)
{
    int changed = 0;

    if (lbl_806D58E8 < self->yawP || lbl_806D58E8 < self->yawN) {
        self->yaw = BuildOrientationFromYaw(lbl_806D58E4 * self->yawP + self->yaw);
        self->yaw = BuildOrientationFromYaw(self->yaw - lbl_806D58E4 * self->yawN);
        changed = 1;
    }
    if (lbl_806D58E8 < self->pitchP || lbl_806D58E8 < self->pitchN) {
        self->pitch = BuildOrientationFromYaw(lbl_806D58E4 * self->pitchP + self->pitch);
        self->pitch = BuildOrientationFromYaw(self->pitch - lbl_806D58E4 * self->pitchN);
        changed = 1;
    }
    return changed;
}

static inline int Zoom(TplScene *self, int changed)
{
    if (lbl_806D58E8 < self->zoomP || lbl_806D58E8 < self->zoomN) {
        self->dist = lbl_806D58EC * self->zoomP + self->dist;
        self->dist = self->dist - lbl_806D58EC * self->zoomN;
        changed = 1;
    }
    return changed;
}

static inline void LerpPos(TplScene *self, Vec3 b, Vec3 a)
{
    Vec3_Lerp(&self->pos, &b, &a, self->t);
}

extern "C" void DbgScene03_TplTest_UpdateCamera(TplScene *self)
{
    char *str = lbl_8032CB38;
    int row;

    if (self->inited == 0) {
        void *m;
        g_cupId = self->cup;
        g_longRoundFlag = self->lr;
        SetReverseRoundFlag(self->rev);
        g_courseVariantIdx = self->variant;
        m = Alloc(0x37C);
        if (m != 0) {
            InputManager_Init(m);
        }
        self->env = m;
        m = Alloc(0x3084);
        if (m != 0) {
            Scene3D_Init(m, GetKartModelNameEntry(0, -1)->name);
        }
        self->scene = (Scene3D *)m;
        GetStartPosition(0, &self->pos.x, &self->pos.y, &self->pos.z);
        self->pos.y += lbl_806D58E0;
        self->yaw = lbl_806D58E4 * GetCourseStartYaw();
        self->pitch = 0.0f;
        self->dist = 100.0f;
        OrbitOffset(&self->target, self, self->dist);
        Vec3_Add_DestFirst(&self->target, &self->pos, &self->target);
        m = Alloc(0x5C);
        if (m != 0) {
            clNormal3D_Construct(m, (char *)lbl_8041AC24[0x46], 1);
        }
        self->obj = m;
        self->mode = 0;
        Vec3_Copy(&self->c, &self->target);
        Vec3_Copy(&self->a, &self->pos);
        Vec3_Copy(&self->b, &self->pos);
        GetCourseBgmEntry();
        SoundDriver_GetOrCreate();
        self->inited = 1;
    }
    if (self->next) {
        self->mode = (self->mode + 1) % 4;
        if (self->mode == 2) {
            Vec3_Copy(&self->pos, &self->a);
        }
        if (self->mode == 3) {
            Vec3_Copy(&self->pos, &self->b);
        }
        self->yaw = Vec3_HorizontalYawTo(&self->pos, &self->target);
        self->pitch = Vec3_PitchTo(&self->pos, &self->target);
        self->dist = fn_800D3184(&self->pos, &self->target);
    }
    switch (self->mode) {
    case 0: {
        int changed = TurnYawPitch(self);
        if (lbl_806D58E8 < self->zoomP || lbl_806D58E8 < self->zoomN) {
            Vec3 v;
            OrbitOffset(&v, self, lbl_806D58EC * self->zoomP);
            Vec3_Add_DestFirst(&self->pos, &self->pos, &v);
            OrbitOffset(&v, self, lbl_806D58F0 * self->zoomN);
            Vec3_Add_DestFirst(&self->pos, &self->pos, &v);
            changed = 1;
        }
        if (changed) {
            Vec3 v;
            OrbitOffset(&v, self, self->dist);
            Vec3_Add_DestFirst(&self->target, &self->pos, &v);
            Vec3_Copy(&self->c, &self->target);
            Vec3_Copy(&self->a, &self->pos);
            Vec3_Copy(&self->b, &self->pos);
        }
        break;
    }
    case 1: {
        int changed = Zoom(self, TurnYawPitch(self));
        if (changed) {
            Vec3 v;
            OrbitOffset(&v, self, self->dist);
            Vec3_Add_DestFirst(&self->target, &self->pos, &v);
            Vec3_Copy(&self->c, &self->target);
        }
        break;
    }
    case 2:
    case 3: {
        int changed = Zoom(self, TurnYawPitch(self));
        if (changed) {
            Vec3 v;
            OrbitOffset(&v, self, self->dist);
            Vec3_Subtract_DestFirst(&self->pos, &self->target, &v);
            if (self->mode == 2) {
                Vec3_Copy(&self->a, &self->pos);
            } else {
                Vec3_Copy(&self->b, &self->pos);
            }
        }
        break;
    }
    case 4: {
        LerpPos(self, self->b, self->a);
        self->t = self->t + lbl_806D58F4;
        if (1.0f < self->t) {
            self->mode = self->savedMode;
            Vec3_Copy(&self->pos, &self->saved);
        }
        break;
    }
    }
    if (self->mode != 4 && self->save) {
        self->savedMode = self->mode;
        Vec3_Copy(&self->saved, &self->pos);
        self->mode = 4;
        self->t = 0.0f;
    }
    row = 0;
    OverlayText(2, 0, row++, STR(0x574));
    switch (self->mode) {
    case 0:
        OverlayText(2, 0, row++, STR(0x580));
        break;
    case 1:
        OverlayText(2, 0, row++, STR(0x58C));
        break;
    case 2:
        OverlayText(2, 0, row++, STR(0x59C));
        break;
    case 3:
        OverlayText(2, 0, row++, STR(0x5AC));
        break;
    case 4:
        OverlayText(2, 0, row++, lbl_806D58F8);
        break;
    }
    row++;
    OverlayText(2, 0, row++, STR(0x5BC), self->c.x, self->c.y, self->c.z);
    OverlayText(2, 0, row++, STR(0x5D0), self->a.x, self->a.y, self->a.z);
    OverlayText(2, 0, row, STR(0x5E4), self->b.x, self->b.y, self->b.z);
    if (Pad0()->IsHeld(0x800)) {
        DebugPrintf(STR(0x5F8), self->c.x, self->c.z, self->a.x, self->a.z);
    }
    CObj_LoadIntoGX(self->scene, &self->pos);
    CObj_ApplyViewport(self->scene, &self->target);
    SetCourseScene3D(self->scene);
    clItemBoxManager_Update(ItemBoxMan());
    CourseEnvironment_UpdateAndCullZones_Timed(self->env);
    if (self->quit) {
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        CourseEnvironment_Dtor(self->env, 1);
        self->env = 0;
        delete self->scene;
        self->scene = 0;
        Object_DtorWithGXSync(self->obj, 1);
        self->obj = 0;
        self->state = 0;
        self->inited = 0;
    }
}

extern "C" void DbgScene03_TplTest_SelectStage(TplScene *self)
{
    char *str = lbl_8032CB38;
    int row;

    if (self->next) {
        self->sel = (self->sel + 1) % 4;
    }
    if (self->inc) {
        switch (self->sel) {
        case 0:
            self->cup = (self->cup + 8) % 9;
            break;
        case 1:
            self->lr = (self->lr + 1) % 2;
            break;
        case 2:
            self->rev = (self->rev + 1) % 2;
            break;
        case 3:
            self->variant = (self->variant + 3) % 4;
            break;
        }
    } else if (self->dec) {
        switch (self->sel) {
        case 0:
            self->cup = (self->cup + 10) % 9;
            break;
        case 1:
            self->lr = (self->lr + 3) % 2;
            break;
        case 2:
            self->rev = (self->rev + 3) % 2;
            break;
        case 3:
            self->variant = (self->variant + 5) % 4;
            break;
        }
    }
    row = 0;
    OverlayText(2, 0, row++, STR(0x60C));
    OverlayText(2, 0, self->sel + 1, lbl_806D5900);
    switch (self->cup) {
    case 0:
        OverlayText(2, 2, row++, STR(0x618));
        break;
    case 1:
        OverlayText(2, 2, row++, STR(0x624));
        break;
    case 2:
        OverlayText(2, 2, row++, STR(0x638));
        break;
    case 3:
        OverlayText(2, 2, row++, STR(0x648));
        break;
    case 4:
        OverlayText(2, 2, row++, STR(0x658));
        break;
    case 5:
        OverlayText(2, 2, row++, STR(0x668));
        break;
    case 6:
        OverlayText(2, 2, row++, STR(0x678));
        break;
    case 7:
        OverlayText(2, 2, row++, STR(0x688));
        break;
    case 8:
        OverlayText(2, 2, row++, STR(0x698));
        break;
    }
    switch (self->lr) {
    case 0:
        OverlayText(2, 2, row++, STR(0x6AC));
        break;
    case 1:
        OverlayText(2, 2, row++, STR(0x6B8));
        break;
    }
    switch (self->rev) {
    case 0:
        OverlayText(2, 2, row++, STR(0x6C4));
        break;
    case 1:
        OverlayText(2, 2, row++, STR(0x6D8));
        break;
    }
    switch (self->variant) {
    case 0:
        OverlayText(2, 2, row, STR(0x6EC));
        break;
    case 1:
        OverlayText(2, 2, row, STR(0x700));
        break;
    case 2:
        OverlayText(2, 2, row, STR(0x714));
        break;
    case 3:
        OverlayText(2, 2, row, STR(0x724));
        break;
    }
    if (self->quit) {
        self->state = 1;
        self->inited = 0;
    }
}

extern "C" void DbgScene03_TplTest_PollInput(TplScene *self)
{
    InputPlayer *pad;
    float x;
    float y;
    float z;
    float neg;
    float pos;
    unsigned char hasNeg;
    unsigned char hasPos;
    unsigned char useY;
    unsigned char useZ;
    float vn;
    float vp;

    self->quit = 0;
    self->next = 0;
    self->save = 0;
    self->inc = 0;
    self->dec = 0;
    self->b11 = 0;
    self->b12 = 0;
    self->b13 = 0;
    self->b14 = 0;
    self->yawP = 0.0f;
    self->yawN = 0.0f;
    self->pitchP = 0.0f;
    self->pitchN = 0.0f;
    self->zoomP = 0.0f;
    self->zoomN = 0.0f;
    pad = Pad0();
    x = ((InputAxes *)pad)->StickX();
    y = ((InputAxes *)pad)->StickY();
    z = ((InputAxes *)pad)->StickZ();
    neg = 0.0f;
    if (x < neg) {
        neg = FAbs_FloatAsDouble(x);
    }
    pos = 0.0f;
    if (0.0f < x) {
        pos = FAbs_FloatAsDouble(x);
    }
    hasNeg = 0;
    hasPos = 0;
    useY = 0;
    useZ = 0;
    if (0.2f < neg) {
        hasNeg = 1;
    }
    if (0.2f < pos) {
        hasPos = 1;
    }
    if (0.2f < y) {
        useY = 1;
    }
    if (0.2f < z) {
        useZ = 1;
    }
    vn = 0.0f;
    vp = vn;
    if (hasNeg) {
        vn = 1.25f * (neg - 0.2f);
    }
    if (hasPos) {
        vp = 1.25f * (pos - 0.2f);
    }
    if (useZ) {
        if (pad->IsHeld(0x10) == 1) {
            self->b13 = 1;
        }
        if (pad->IsHeld(0x20) == 1) {
            self->b14 = 1;
        }
        self->zoomP = vn;
        self->zoomN = vp;
    } else if (useY) {
        if (pad->IsHeld(0x10) == 1) {
            self->b11 = 1;
        }
        if (pad->IsHeld(0x20) == 1) {
            self->b12 = 1;
        }
        self->pitchP = vn;
        self->pitchN = vp;
    } else {
        if (pad->IsHeld(0x10) == 1) {
            self->inc = 1;
        }
        if (pad->IsHeld(0x20) == 1) {
            self->dec = 1;
        }
        self->yawP = vn;
        self->yawN = vp;
    }
    if (pad->IsHeld(0x2000) == 1) {
        if (pad->IsPressed(0x100) == 1 && pad->IsPressed(0x200) == 1) {
            self->save = 1;
        } else {
            self->next = 1;
        }
    }
    if (pad->IsHeld(0x400) == 1) {
        self->quit = 1;
    }
}

extern "C" unsigned char DbgScene03_TplTest_InputCheck(TplScene *self)
{
    DbgScene03_TplTest_PollInput(self);
    switch (self->state) {
    case 0:
        DbgScene03_TplTest_SelectStage(self);
        break;
    case 1:
        DbgScene03_TplTest_UpdateCamera(self);
        break;
    }
    return 0;
}

extern "C" SceneHdr *DbgScene02_MapViewer_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CB74;
        fn_80121210();
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void DbgScene02_MapViewer_SetupBlit(void)
{
    fn_8011FAB8();
}

extern "C" unsigned char DbgScene02_MapViewer_InputCheck(void)
{
    ResCtrl r;

    if (Pad0()->IsHeld(0x400) == 1) {
        return 1;
    }
    ResCtrl_Init(&r);
    fn_80121E10(&r);
    r.id = 0xBFF;
    r.flag10 = 1;
    r.x = 150.0f;
    r.y = 240.0f;
    r.z = 1.0f;
    fn_8011FAFC(&r, 0);
    fn_80121E10(&r);
    r.id = 0x1E91;
    r.flag10 = 1;
    r.x = 300.0f;
    r.y = 240.0f;
    r.z = 1.0f;
    fn_8011FAFC(&r, 0);
    return 0;
}

extern "C" SceneHdr *DbgScene01_SprMng2Test_Dtor(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041CB94;
        fn_80121210();
        if (self != 0) {
            self->vt = lbl_8041C9D4;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void DbgScene01_SprMng2Test_SetupBlit(void)
{
    fn_8011FAB8();
}

extern "C" unsigned char DbgScene01_SprMng2Test_InputCheck(void)
{
    InputPlayer *pad = Pad0();
    int prev;
    ResCtrl r;

    if (pad->IsHeld(0x400) == 1) {
        return 1;
    }
    prev = lbl_806D14C4;
    if (pad->IsHeld(0x20) || (pad->IsPressed(0x20) && pad->IsPressed(1))) {
        if (++lbl_806D14C4 >= 0x2B00) {
            lbl_806D14C4 = 0;
        }
    } else if (pad->IsHeld(0x10) || (pad->IsPressed(0x10) && pad->IsPressed(1))) {
        if (--lbl_806D14C4 <= -1) {
            lbl_806D14C4 = 0x2AFF;
        }
    } else if (pad->IsHeld(4) || pad->IsHeld(2)) {
        int i;

        for (i = 0; i < lbl_806CF320; i++) {
            if (i == lbl_806CF320 - 1) {
                if (lbl_8041C860[i] <= lbl_806D14C4) {
                    break;
                }
            } else if (lbl_8041C860[i] <= lbl_806D14C4 && lbl_806D14C4 < lbl_8041C860[i + 1]) {
                break;
            }
        }
        if (pad->IsHeld(4)) {
            i++;
        } else {
            i--;
        }
        if (i <= -1) {
            i = lbl_806CF320 - 1;
        }
        if (lbl_806CF320 <= i) {
            i = 0;
        }
        lbl_806D14C4 = lbl_8041C860[i];
    }
    OverlayText(2, 0, 0, lbl_806D5914, lbl_806D14C4);
    if (prev != lbl_806D14C4) {
        fn_80120A08(prev);
    }
    ResCtrl_Init(&r);
    fn_80121E10(&r);
    r.id = lbl_806D14C4;
    r.flag10 = 1;
    r.x = 320.0f;
    r.y = 240.0f;
    r.z = 1.0f;
    fn_8011FAFC(&r, 1);
    return 0;
}

extern "C" void DbgScene_PreloadResourceTree(ResNode *tree)
{
    int i;
    signed char count = 1;

    for (i = 0; tree[i].type != 0xD; i++) {
        switch (tree[i].type) {
        case 0: {
            int *ids = (int *)tree[i].data;
            count = 0;
            while (ids[count] != -1 && ids[count] != -2) {
                count++;
            }
            break;
        }
        case 1: {
            int j;
            for (j = 0; j < count; j++) {
                PreloadResource(((int *)tree[i].data)[j]);
            }
            break;
        }
        case 0xC:
            DbgScene_PreloadResourceTree((ResNode *)tree[i].data);
            break;
        }
    }
}

extern "C" Particle *DbgScene_AnimSlot_Init(Particle *e)
{
    AnimState_New(e->anim, 0);
    Particle_Reset(e, 0);
    e->handle = 0;
    return e;
}

static inline void QuadVtx(float x, float y, float u, float v)
{
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.u8 = 0xFF;
    GXFIFO.f32 = u;
    GXFIFO.f32 = v;
}

extern "C" void DbgScene_DrawTexturedQuad(PaletteSet *set, ResCtrl *r, int idx)
{
    TexPalEntry *e;
    float x;
    float y;
    float w;
    float h;

    GXSetBlendMode(1, 4, 5, 0xF);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 0, 4, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    e = (TexPalEntry *)TEXGetPaletteEntry(set->pal, idx);
    if (e->ci != 0) {
        int k;
        for (k = 0; k < 16; k++) {
            if (set->color == lbl_8041C7E0[k]) {
                break;
            }
        }
        if (lbl_8041C820[k] != set->ci) {
            GXLoadTlut(set->ci + idx * 0xC, set->color);
            lbl_8041C820[k] = set->ci;
        }
        GXLoadTexObj(set->rgb + idx * 0x20, 0);
    } else {
        GXLoadTexObj(set->rgb + idx * 0x20, 0);
    }
    w = e->tex->width;
    h = e->tex->height;
    x = r->x;
    y = r->y;
    GXBegin(0x80, 0, 4);
    QuadVtx(x, y, lbl_806D5884, lbl_806D5884);
    QuadVtx(x + w, y, lbl_806D5880, lbl_806D5884);
    QuadVtx(x + w, y + h, lbl_806D5880, lbl_806D5880);
    QuadVtx(x, y + h, lbl_806D5884, lbl_806D5880);
}

extern "C" SceneHdr *dtor_800D2B98(SceneHdr *self, short flag)
{
    if (self != 0) {
        self->vt = lbl_8041C9D4;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

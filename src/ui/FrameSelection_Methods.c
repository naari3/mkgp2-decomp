/*
 * FrameSelection method bundle (compiled as C++: -lang=c++ -Cpp_exceptions on).
 *
 *   FrameSelection_Init    @ 0x801C4EA8 (size 0x4F8) - asm (see #if 0 below)
 *   FrameSelection_Confirm @ 0x801C53A0 (size 0x2FC) - C++
 *   FrameSelection_Draw    @ 0x801C569C (size 0x1F4) - C++
 *   FrameSelection_Update  @ 0x801C5890 (size 0x3A4) - C++
 *
 * Init is the clFlowChara ctor (vtable lbl_8049AC7C = g_charaStatTable+0x224);
 * Confirm/Draw/Update operate on the NamCam confirm scene layout.
 *
 * Confirm/Draw/Update carry plain 8-byte extab entries that CW auto-emits;
 * Init keeps its manual .extab_user emission. tools/extab_order.json puts
 * the four entries back in address order. Mangled C++ references are bridged
 * with --redefine-sym via tools/extab_user_renames.json (entry for this TU):
 *   Confirm__15clFlowNamcamRecFv -> FrameSelection_Confirm
 *   __ct__6SpriteFiii            -> Sprite_InitWithAnim
 *   __nw__FUl / __dl__FPv        -> Alloc / MemoryManager_TimedFree
 *
 * Register-identity notes (docs/notes/frameselection-native-20261025.md):
 *   - Confirm: the post-early-return body is a static inline helper. Written
 *     inline, `self` (param web) is colored first and takes r31; through the
 *     inlined helper the target's player=r31 / self=r30 coloring comes out.
 *     auto_inline is switched off around Confirm so Update keeps its bl.
 *   - Update: the NamCam capture pump is an inline NamCamObj member, which
 *     puts the namcam pointer in r30 as in the target.
 */

typedef float f32;
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" {
/* --- callees --- */
extern void SpriteSystem_EnsureInit(void);
extern void SetSyncTarget(int);
extern void SetCourseParams(int, int, int, int);
extern void PreloadResource(int);
extern int GetFrameIdxFromVisualIdx(void *self, int visualIdx);
extern int GetCoinMilage(void *playerData);
extern u8 IsCardValid(void);
extern int GetTextureByIdAndLang(int id, int lang);
extern void TexMgr_SetTexture(void *self, int tex, ...);
extern void TexMgr_Apply(void *self);
extern void SetScreenBrightness(f32 brightness);
extern void InitBGM(void);
extern void SetupBgSprites(int);
extern void InitRumbleController(int);
extern void PlaySoundDSP(int);
extern void *GetInputManager(void);
extern void *InputMgr_GetPlayer(void *mgr, int index);
extern u8 Sprite_AdvanceAnim(void *spr, f32 dt);
extern void SetRumbleMode(int, int, int);
extern void Sprite_Destroy(void *spr, int flag);
extern void GX_BeginDraw(void);
extern void GX_ResetVertex(void);
extern int GetDisplayBufferIndex(void);
extern void *GetDisplayContext(void);
extern void DrawNamCamImage(void *ctx, void *tex, int w, int h, int fmt, u16 left, u16 top, u16 right, u16 bottom, int, int, int);
extern void GX_EndDraw(int);
extern void SoundMgr_Play(int);
extern void fn_801A0004(void *spr);
extern void fn_8011FAB8(void);
extern void fn_801A1280(void);
extern void FlashFadeOverlay_Draw(void *overlay, f32, f32, f32, f32, f32, f32);
extern void fn_801A1174(int, int, int, int, int);
extern void fn_801A1128(f32, f32);
extern void fn_801A0DF0(void);
extern void RumbleUpdate(void);
extern u8 IsSyncReached(void);
extern void ResetIOPorts(void);
extern u8 GetVBlankFlag(void);
extern int NamCam_GetImageHandle(void *out, int);
extern void NamCam_LoadImage(void *handle, void *tex, void *out);
extern void StartScreenFade(f32);
extern void PlayCursorMoveSE(void);
extern void Sprite_SetAnimTime(void *spr, f32 time);

/* --- referenced only by the FrameSelection_Init asm body --- */
extern void InitializeFrameSelection(void *self); /* clFlowBase ctor */
extern void ResCtrl_Init(void *self);
extern void *Alloc(unsigned long size);
extern void Sprite_CreateWithParams(void *self, int id, int flag, f32 x, f32 y, f32 sx, f32 sy, f32 t, f32 a);
extern void TexMgr_Init(void *self);
extern void Scene3D_Init(void *self, const char *path);
extern void SceneModel_Init(void *self, const char *path, int);
extern void MemoryManager_TimedFree(void *p);
extern void dtor_80082960(void *self);  /* ResCtrl dtor */
extern void dtor_800869D0(void *self);  /* TexMgr dtor */
extern void dtor_801BA14C(void *self);  /* clFlowBase dtor */
extern u8 g_charaStatTable[];
extern const unsigned int lbl_8039AA40[];

/* --- data --- */
extern u8 g_playerData[];
extern u8 lbl_80598A60[];
extern u8 g_namCamFlag;
extern u8 g_confirmFlag;
extern int g_gameMode;
extern int g_consecutiveWinsTier;

/* --- .sdata2 constants --- */
extern const f32 FLOAT_INIT_Z_DEPTH;
extern const f32 FLOAT_ARROW_LEFT_X;
extern const f32 FLOAT_ARROW_Y;
extern const f32 FLOAT_ARROW_LEFT_SCALE_X;
extern const f32 FLOAT_ARROW_SCALE;
extern const f32 FLOAT_SPRITE_INIT_TIME;
extern const f32 FLOAT_FULL_ALPHA;
extern const f32 FLOAT_ARROW_RIGHT_X;
extern const f32 FLOAT_ARROW_RIGHT_OFFSET;
extern const f32 FLOAT_TEX_SCALE;
extern const f32 FLOAT_TEX_POS_Y;
extern const f32 FLOAT_TEX_POS_X;
extern const f32 FLOAT_BRIGHTNESS_DARK;
extern const f32 FLOAT_CURSOR_LEFT_X;
extern const f32 FLOAT_CURSOR_Y;
extern const f32 FLOAT_CURSOR_RIGHT_X;
extern const f32 FLOAT_DELTA_TIME;
extern const f32 FLOAT_DELTA_TIME_2X;
extern const f32 FLOAT_FADE_OFFSET;
extern const f32 FLOAT_NAMCAM_BOTTOM;
extern const f32 FLOAT_NAMCAM_LEFT;
extern const f32 FLOAT_NAMCAM_TOP;
extern const f32 FLOAT_NAMCAM_RIGHT;
extern const f32 FLOAT_UNFOCUSED_ALPHA;
extern const f32 FLOAT_UNFOCUSED_SCALE;
extern const f32 FLOAT_FOCUSED_SCALE;
extern const f32 FLOAT_TITLE_STEP_X;
extern const f32 FLOAT_TITLE_BASE_X;
extern const f32 FLOAT_TITLE_POS_Y;
extern const f32 FLOAT_ANIM_RESET;
extern const f32 lbl_806D9C10;
extern const f32 lbl_806D9C14;
extern const f32 lbl_806D9C18;
extern const f32 lbl_806D9C1C;
extern const f32 lbl_806D9C20;
extern const f32 lbl_806D9C24;
extern const f32 lbl_806D9C28;
}

struct Sprite {
    int field_0x00; /* 0x00 */
    int field_0x04; /* 0x04 */
    char _pad8[4];
    f32 posX;       /* 0x0C */
    f32 posY;       /* 0x10 */
    f32 scaleX;     /* 0x14 */
    f32 scaleY;     /* 0x18 */
    char _pad1C[4];
    f32 alpha;      /* 0x20 */
    char _pad24[0x30 - 0x24];
    Sprite(int id, int flag, f32 x, f32 y, f32 sx, f32 sy, f32 t, f32 a);
    Sprite(int id, int flag, int anim);
};

struct NamCamObj {
    u8 flag_0x00;
    u8 flag_0x01;
    char _pad2[2];
    void *tex; /* 0x04 */

    void Pump() {
        int out[2];
        void *handle;

        if (GetVBlankFlag() != 0) {
            if (flag_0x00 != 0) {
                if (NamCam_GetImageHandle(&handle, 0) == 1) {
                    NamCam_LoadImage(handle, tex, &out);
                    flag_0x01 = 1;
                }
            }
        }
    }
};

struct InputState {
    char _pad0[4];
    u8 field_0x04;  /* 0x04 */
    char _pad5[0x14 - 0x5];
    int field_0x14; /* 0x14 - stick delta */
    int field_0x18; /* 0x18 */
    int field_0x1c; /* 0x1c */
};

extern "C" InputState *g_pInputState;

static inline InputState *GetInput(void) {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

struct InputPlayer {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual unsigned int vf8(int);
};

typedef struct clFlowNamcamRec {
    /* 0x00 */ void *vtbl;
    /* 0x04 */ int visualIdx;
    /* 0x08 */ int field_0x08;
    /* 0x0C */ u8 flag_0x0c;
    /* 0x0D */ u8 available[0xB];
    /* 0x18 */ u8 flag_0x18;
    /* 0x19 */ u8 flag_0x19;
    /* 0x1A */ u8 pad_0x1a[2];
    /* 0x1C */ int counter;
    /* 0x20 */ int field_0x20;
    /* 0x24 */ int field_0x24;
    /* 0x28 */ int field_0x28;
    /* 0x2C */ int field_0x2c;
    /* 0x30 */ Sprite *spr_0x30;
    /* 0x34 */ Sprite *spr_0x34;
    /* 0x38 */ Sprite *spr_0x38;
    /* 0x3C */ Sprite *spr_0x3c;
    /* 0x40 */ Sprite *slots_0x40[2];
    /* 0x48 */ Sprite *cursorL;
    /* 0x4C */ Sprite *cursorR;
    /* 0x50 */ Sprite *sprites_0x50[0xB];
    /* 0x7C */ Sprite *sprites_0x7c[0xB];
    /* 0xA8 */ Sprite *spr_0xa8;
    /* 0xAC */ NamCamObj *namcam;

    int Confirm();
} clFlowNamcamRec;

/* ------------------------------------------------------------------ */
/* FrameSelection_Init (0x801C4EA8) - native candidate, parked          */
/* ------------------------------------------------------------------ */
/* The C++ ctor below reaches 99.906% (same size, 1272 bytes) once this TU
 * owns the .data/.rodata ranges it addresses through CSE'd base registers
 * (split lines and the generated data definitions are kept in this block;
 * see docs/notes/frameselection-native-20261025.md). Only the prologue
 * pool-base pair differs: target `lis r5, .data / lis r4, .rodata`, ours
 * the other way round (dest registers r30/r29 identical).
 * Observed: adding a probe function before the ctor that uses the .rodata
 * pool (several uses across calls) makes the ctor 100.0%; the pool symbols
 * `...data.0` / `...rodata.0` are then created in the opposite order.
 * Hypothesis: CW orders the two base loads by pool-symbol creation order,
 * i.e. by the first pooled reference in the TU. In the original TU that
 * would be clFlowChara_Update (its prologue loads lbl_8039AA40), which is a
 * separate TU here, so Init stays asm. */
#if 0
struct FrameParam {
    short iconId1;   /* 0x00 */
    short iconId2;   /* 0x02 */
    short iconId3;   /* 0x04 */
    short pad_0x06;  /* 0x06 */
    int field_0x8;   /* 0x08 - zeroed by the ctor */
    f32 x;           /* 0x0C */
    f32 y;           /* 0x10 */
    f32 z;           /* 0x14 */
}; /* size 0x18 */

/* .data 0x8049AA58..0x8049AC90 (emission order = target address order).
 * The ctor addresses this pool through one CSE'd base (r30 =
 * g_charaStatTable); the vtable store is base+0x224. */
extern "C" {

extern char lbl_806CFDC0[8]; /* .sdata - clFlowBase RTTI */
extern char lbl_806CFDC8[8]; /* .sdata - clFlowChara RTTI {name, bases} */
extern void clFlowChara_Destructor(void);
extern void clFlowChara_Update(void);
extern void fn_801C3AA4(void);

/* 0x8049AA58 - per-character kart stat bytes */
u8 g_charaStatTable[0x78] = {
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x04, 0x04, 0x05, 0x02, 0x02,
    0x02, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x04, 0x04, 0x05, 0x02, 0x02,
    0x03, 0x03, 0x03, 0x04, 0x02, 0x03, 0x05, 0x02, 0x02, 0x03, 0x03, 0x03,
    0x04, 0x02, 0x03, 0x02, 0x03, 0x04, 0x02, 0x03, 0x04, 0x01, 0x04, 0x05,
    0x04, 0x02, 0x03, 0x01, 0x04, 0x05, 0x03, 0x02, 0x04, 0x01, 0x04, 0x05,
    0x04, 0x02, 0x03, 0x02, 0x03, 0x04, 0x03, 0x02, 0x04, 0x04, 0x02, 0x03,
    0x02, 0x03, 0x04, 0x03, 0x02, 0x04, 0x03, 0x03, 0x04, 0x03, 0x03, 0x04,
    0x02, 0x04, 0x05, 0x05, 0x02, 0x03, 0x02, 0x04, 0x05, 0x04, 0x02, 0x04,
    0x02, 0x04, 0x05, 0x05, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x02, 0x04,
    0x05, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x02, 0x04, 0x00, 0x00, 0x00,
};

/* 0x8049AAD0 - per-frame resource/icon params */
FrameParam FrameParam_ARRAY_8049aad0[13] = {
    { 0x169B, 0x16A9, 0x167F, 0, 0, -40.0f, 132.0f, 134.0f },
    { 0x169C, 0x16A9, 0x1680, 0, 0, -40.0f, 196.0f, 134.0f },
    { 0x169D, 0x16A9, 0x1681, 0, 0, -40.0f, 260.0f, 134.0f },
    { 0x169E, 0x16A9, 0x1682, 0, 0, -40.0f, 324.0f, 134.0f },
    { 0x169F, 0x16AA, 0x1683, 0, 0, -40.0f, 388.0f, 134.0f },
    { 0x16A0, 0x16AA, 0x1684, 0, 0, -40.0f, 452.0f, 134.0f },
    { 0x16A1, 0x16AA, 0x1685, 0, 0, -40.0f, 516.0f, 134.0f },
    { 0x16A2, 0x16AB, 0x1687, 0, 0, 40.0f, 165.0f, 202.0f },
    { 0x16A3, 0x16AB, 0x1686, 0, 0, 40.0f, 229.0f, 202.0f },
    { 0x16A4, 0x16AB, 0x1688, 0, 0, 40.0f, 293.0f, 202.0f },
    { 0x16A5, 0x16A8, 0x1689, 0, 0, 40.0f, 364.0f, 204.0f },
    { 0x16A6, 0x16A8, 0x168A, 0, 0, 40.0f, 428.0f, 204.0f },
    { 0x16A7, 0x16A8, 0x168B, 0, 0, 40.0f, 492.0f, 204.0f },
};

/* 0x8049AC08 - cursor position per selectable frame {x, y} */
f32 g_tierCursorPosTable[13][2] = {
    { 82.0f, 135.0f },
    { 146.0f, 135.0f },
    { 210.0f, 135.0f },
    { 274.0f, 135.0f },
    { 338.0f, 135.0f },
    { 402.0f, 135.0f },
    { 466.0f, 135.0f },
    { 115.0f, 203.0f },
    { 179.0f, 203.0f },
    { 243.0f, 203.0f },
    { 314.0f, 203.0f },
    { 378.0f, 203.0f },
    { 442.0f, 203.0f },
};

/* 0x8049AC70 - clFlowChara RTTI base list */
void *lbl_8049AC70[3] = { lbl_806CFDC0, 0, 0 };

/* 0x8049AC7C - clFlowChara vtable { rtti, offset, dtor, Update, fn } */
void *lbl_8049AC7C[5] = {
    lbl_806CFDC8, 0, (void *)clFlowChara_Destructor, (void *)clFlowChara_Update,
    (void *)fn_801C3AA4
};

} /* extern "C" */

/* .rodata 0x8039AA40..0x8039B05C (emission order = target address order).
 * The ctor addresses this pool through one CSE'd base (r29 = lbl_8039AA40). */
extern "C" {

/* 0x8039AA40 - keyframe float curves (raw bits) */
extern const unsigned int lbl_8039AA40[0xFF] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};

/* 0x8039AE3C / 0x8039AE70 - coin-mileage unlock thresholds */
extern const int g_frameUnlockThresholds_Partial[13] = { 30, 1470, 1230, 150, 750, 1350, 270, 630, 990, 390, 1110, 510, 870 };
extern const int g_frameUnlockThresholds_Full[13] = { 1590, 3030, 2790, 1710, 2310, 2910, 1830, 2190, 2550, 1950, 2670, 2070, 2430 };

/* 0x8039AEA4 - per-frame texture id table */
extern const int g_tierTextureIdTable[13] = { 2, 2, 3, 1, 3, 0, 3, 1, 2, 0, 1, 2, 0 };
extern const f32 s_tierTexAux[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 140.0f, 220.0f };

/* 0x8039AEF4.. - kart demo file names + pointer table (0x8039B014) */
extern const char lbl_8039AEF4[] = "kart_demo_mario.dat";
extern const char lbl_8039AF08[] = "kart_demo_luigi.dat";
extern const char lbl_8039AF1C[] = "kart_demo_pacman.dat";
extern const char lbl_8039AF34[] = "kart_demo_waluigi.dat";
extern const char lbl_8039AF4C[] = "kart_demo_peach.dat";
extern const char lbl_8039AF60[] = "kart_demo_yoshi.dat";
extern const char lbl_8039AF74[] = "kart_demo_monster.dat";
extern const char lbl_8039AF8C[] = "kart_demo_mametch.dat";
extern const char lbl_8039AFA4[] = "kart_demo_mspacman.dat";
extern const char lbl_8039AFBC[] = "kart_demo_kinopio.dat";
extern const char lbl_8039AFD4[] = "kart_demo_wario.dat";
extern const char lbl_8039AFE8[] = "kart_demo_donkey.dat";
extern const char lbl_8039B000[] = "kart_demo_koopa.dat";
extern const char *const lbl_8039B014[13] = {
    lbl_8039AEF4,
    lbl_8039AF08,
    lbl_8039AF1C,
    lbl_8039AF34,
    lbl_8039AF4C,
    lbl_8039AF60,
    lbl_8039AF74,
    lbl_8039AF8C,
    lbl_8039AFA4,
    lbl_8039AFBC,
    lbl_8039AFD4,
    lbl_8039AFE8,
    lbl_8039B000
};

/* 0x8039B048 - scene model file loaded by the ctor */
extern const char lbl_8039B048[0x14] = "select_mario.dat";

} /* extern "C" */

struct clFlowBase {
    clFlowBase();
    ~clFlowBase();
};

struct ResCtrl {
    int resId;      /* 0x00 */
    char _pad4[4];
    int mode;       /* 0x08 */
    char _padC[4];
    u8 flag;        /* 0x10 */
    char _pad11[3];
    f32 posY;       /* 0x14 */
    f32 posX;       /* 0x18 */
    f32 alpha;      /* 0x1C */
    f32 fD;         /* 0x20 */
    f32 fE;         /* 0x24 */
    f32 fF;         /* 0x28 */
    f32 scaleX;     /* 0x2C */
    f32 scaleY;     /* 0x30 */
    ResCtrl();
    ~ResCtrl();
}; /* size 0x34 */

struct TexMgr {
    char _opaque[0x230];
    TexMgr();
    ~TexMgr() {}
};

struct Scene3D {
    char _opaque[0x3084];
    Scene3D(const char *path);
};

struct SceneModel {
    char _opaque[0x28];
    SceneModel(const char *path, int);
};

struct FrameSelection : clFlowBase {
    void *vptr;                    /* 0x000 */
    int visualIdx;                 /* 0x004 */
    int field_0x08;                /* 0x008 */
    u8 flag_0x0c;                  /* 0x00C */
    char _pad0D[3];
    int field_0x10;                /* 0x010 */
    int unk_0x14[13];              /* 0x014..0x048 */
    Sprite *cursorL;               /* 0x048 */
    Sprite *cursorR;               /* 0x04C */
    Sprite *spr_0x50;              /* 0x050 */
    Sprite *spr_0x54;              /* 0x054 */
    Sprite *spr_0x58;              /* 0x058 */
    int field_0x5c;                /* 0x05C */
    int field_0x60;                /* 0x060 */
    u8 flag_0x64;                  /* 0x064 */
    u8 flag_0x65;                  /* 0x065 */
    char _pad66[0x6C - 0x66];
    f32 field_0x6c;                /* 0x06C */
    Scene3D *scene3D;              /* 0x070 */
    SceneModel *sceneModel;        /* 0x074 */
    char _pad78[0xA8 - 0x78];
    int states_0xa8[13];           /* 0x0A8 */
    int arr_0xdc[13];              /* 0x0DC */
    int arr_0x110[13];             /* 0x110 */
    int arr_0x144[13];             /* 0x144 */
    TexMgr *texMgr;                /* 0x178 */
    ResCtrl resCtrl;               /* 0x17C */

    FrameSelection();
}; /* size 0x1B0 */

FrameSelection::FrameSelection() : vptr(lbl_8049AC7C) {
    int i;
    int j;
    int mileage;

    SpriteSystem_EnsureInit();
    SetSyncTarget(0xd);
    SetCourseParams(7, 0, 0, 0);
    PreloadResource(0x167f);
    PreloadResource(0x169b);
    PreloadResource(0x16ac);
    PreloadResource(0x16ae);
    PreloadResource(0x16ad);
    PreloadResource(0x16af);
    for (i = 0; i < 0xd; i++) {
        PreloadResource((int)FrameParam_ARRAY_8049aad0[i].iconId1);
        PreloadResource((int)FrameParam_ARRAY_8049aad0[i].iconId2);
    }
    PreloadResource(0x16af);
    PreloadResource(0x16a8);
    PreloadResource(0x1d55);
    PreloadResource(0x1d3e);
    PreloadResource(0x186c);
    PreloadResource(0x16b0);
    PreloadResource(0x16cc);
    PreloadResource(0x1d5c);
    for (i = 0; i < 0xd; i++) {
        unk_0x14[i] = 0;
        FrameParam_ARRAY_8049aad0[i].field_0x8 = 0;
    }
    visualIdx = 0;
    field_0x60 = -1;
    field_0x08 = 0;
    flag_0x0c = 0;
    field_0x10 = 0;
    field_0x5c = 0;
    scene3D = 0;
    sceneModel = 0;
    field_0x6c = FLOAT_INIT_Z_DEPTH;
    flag_0x64 = 0;
    flag_0x65 = 0;
    cursorL = new Sprite(0x9c, 1, FLOAT_ARROW_LEFT_X, FLOAT_ARROW_Y,
                         FLOAT_ARROW_LEFT_SCALE_X, FLOAT_ARROW_SCALE,
                         FLOAT_SPRITE_INIT_TIME, FLOAT_FULL_ALPHA);
    cursorR = new Sprite(0x9c, 1, FLOAT_ARROW_RIGHT_X, FLOAT_ARROW_Y,
                         FLOAT_ARROW_SCALE, FLOAT_ARROW_SCALE,
                         FLOAT_SPRITE_INIT_TIME, FLOAT_FULL_ALPHA);
    spr_0x50 = 0;
    spr_0x54 = 0;
    spr_0x58 = 0;
    texMgr = new TexMgr;
    for (i = 0; i < 0xd; i++) {
        int f = GetFrameIdxFromVisualIdx(this, i);
        if (f == (s8)g_playerData[0x1b8]) {
            visualIdx = i;
            break;
        }
    }
    if (cursorL != 0) {
        Sprite *spr = cursorL;
        f32 x = g_tierCursorPosTable[visualIdx][0];
        f32 y = g_tierCursorPosTable[visualIdx][1];

        spr->posX = x;
        spr->posY = y;
        cursorL->field_0x04 = 5;
    }
    if (cursorR != 0) {
        Sprite *spr = cursorR;
        f32 x = FLOAT_ARROW_RIGHT_OFFSET + g_tierCursorPosTable[visualIdx][0];
        f32 y = g_tierCursorPosTable[visualIdx][1];

        spr->posX = x;
        spr->posY = y;
        cursorR->field_0x04 = 5;
    }
    mileage = GetCoinMilage(g_playerData);
    for (int k = 0; k < 0xd; k++) {
        arr_0xdc[k] = 0;
        arr_0x110[k] = 0;
        arr_0x144[k] = 0;
        j = GetFrameIdxFromVisualIdx(this, k);
        if (mileage >= g_frameUnlockThresholds_Full[j]) {
            states_0xa8[j] = 2;
        } else if (mileage >= g_frameUnlockThresholds_Partial[j]) {
            states_0xa8[j] = 1;
        } else {
            states_0xa8[j] = 0;
        }
        if (IsCardValid() == 0) {
            states_0xa8[j] = 1;
        }
    }
    scene3D = new Scene3D(lbl_8039B048);
    sceneModel = new SceneModel(lbl_8039B048, 1);
    TexMgr tm;

    TexMgr_SetTexture(&tm, GetTextureByIdAndLang(
                               g_tierTextureIdTable[GetFrameIdxFromVisualIdx(this, visualIdx)] + 0x95, -1));
    TexMgr_Apply(&tm);
    resCtrl.resId = 0x1d5c;
    resCtrl.scaleX = FLOAT_TEX_SCALE;
    resCtrl.scaleY = FLOAT_TEX_SCALE;
    resCtrl.flag = 1;
    resCtrl.posY = FLOAT_TEX_POS_Y;
    resCtrl.posX = FLOAT_TEX_POS_X;
    resCtrl.alpha = FLOAT_FULL_ALPHA;
    {
        InputState *in = GetInput();

        if (in != 0) {
            in = GetInput();
            in->field_0x04 = 1;
            in->field_0x18 = 0;
            in->field_0x1c = 0;
        }
    }
    SetScreenBrightness(FLOAT_BRIGHTNESS_DARK);
    InitBGM();
    SetupBgSprites(1);
    InitRumbleController(1);
}

#endif

/* FrameSelection_Init asm body + manual extab emit */
extern "C" {
#include "src/ui/FrameSelection_Init.inc"
}

/* ------------------------------------------------------------------ */
/* FrameSelection_Confirm (0x801C53A0)                                 */
/* ------------------------------------------------------------------ */
static inline int ConfirmTick(clFlowNamcamRec *self) {
    InputPlayer *player;
    u8 confirmed;

    self->counter++;
    if (self->counter == 0x168) {
        Sprite *spr;

        self->cursorL = new Sprite(0x5b, 1, 0);
        self->cursorR = new Sprite(0x5b, 1, 0);
        spr = self->cursorL;
        spr->posX = FLOAT_CURSOR_LEFT_X;
        spr->posY = FLOAT_CURSOR_Y;
        spr = self->cursorR;
        spr->posX = FLOAT_CURSOR_RIGHT_X;
        spr->posY = FLOAT_CURSOR_Y;
    }
    if (self->counter == 0x1e0) {
        PlaySoundDSP(0x276);
    }
    if (self->counter == 0x21c) {
        PlaySoundDSP(0x277);
    }
    if (self->counter == 0x258) {
        PlaySoundDSP(0x278);
    }
    confirmed = 0;
    player = (InputPlayer *)InputMgr_GetPlayer(GetInputManager(), 0);
    if (self->cursorL != 0) {
        if (Sprite_AdvanceAnim(self->cursorL, FLOAT_DELTA_TIME) == 0) {
            confirmed = 1;
        }
    }
    if (self->namcam->flag_0x01 != 0) {
        if (player->vf8(0x2000) != 0) {
            confirmed = 1;
        }
    }
    if (self->cursorR != 0) {
        Sprite_AdvanceAnim(self->cursorR, FLOAT_DELTA_TIME);
    }
    if (confirmed != 0) {
        SetRumbleMode(0, 1, 1);
        Sprite_Destroy(self->cursorL, 1);
        Sprite_Destroy(self->cursorR, 1);
        self->cursorL = 0;
        self->cursorR = 0;
        if (self->namcam->flag_0x01 != 0) {
            void *ctx;
            int cfgX;
            int cfgY;

            GX_BeginDraw();
            GX_ResetVertex();
            cfgX = *(int *)(lbl_80598A60 + 0x4c);
            cfgY = *(int *)(lbl_80598A60 + 0x48);
            GetDisplayBufferIndex();
            ctx = GetDisplayContext();
            DrawNamCamImage(ctx, self->namcam->tex, 0x140, 0xf0, 6,
                            (int)FLOAT_NAMCAM_LEFT - cfgX - 7,
                            (int)FLOAT_NAMCAM_TOP - cfgY - 0xa,
                            (int)FLOAT_NAMCAM_RIGHT - cfgX - 7,
                            (int)FLOAT_NAMCAM_BOTTOM - cfgY - 0xa,
                            0x80, 0x80, 4);
            GX_EndDraw(0);
            self->flag_0x19 = 1;
            SoundMgr_Play(0x16);
            g_namCamFlag = 1;
            g_confirmFlag = 1;
        }
        g_consecutiveWinsTier = self->visualIdx;
        if (g_gameMode == 0) {
            self->field_0x2c = 0x15;
        } else if (g_gameMode == 1) {
            self->field_0x2c = 0x17;
        }
        self->field_0x24 = 0x50;
        return -1;
    }
    return self->field_0x2c;
}

#pragma auto_inline off
int clFlowNamcamRec::Confirm() {
    if (field_0x2c != -1) {
        return field_0x2c;
    }
    return ConfirmTick(this);
}
#pragma auto_inline reset

/* ------------------------------------------------------------------ */
/* FrameSelection_Draw (0x801C569C)                                    */
/* ------------------------------------------------------------------ */
extern "C" void FrameSelection_Draw(clFlowNamcamRec *self) {
    int i;
    f32 dw;
    f32 dh;

    fn_801A0004(self->spr_0x30);
    fn_8011FAB8();
    fn_801A1280();
    dw = *(int *)(lbl_80598A60 + 0x4c);
    dh = *(int *)(lbl_80598A60 + 0x48);
    if (self->flag_0x18 == 0) {
        FlashFadeOverlay_Draw(self->namcam, lbl_806D9C10, lbl_806D9C14,
                              lbl_806D9C18, lbl_806D9C1C, dw, dh);
    }
    for (i = 0; i < 0xb; i++) {
        if (i != self->visualIdx) {
            fn_801A0004(self->sprites_0x50[i]);
        }
    }
    fn_801A0004(self->spr_0x34);
    fn_801A0004(self->sprites_0x7c[self->visualIdx]);
    fn_801A0004(self->sprites_0x50[self->visualIdx]);
    fn_801A1174(0x18dd, 5, 0, 0, 0);
    fn_801A1128(lbl_806D9C20, lbl_806D9C24);
    fn_801A0DF0();
    if (self->field_0x24 == 0 && self->flag_0x0c == 0) {
        if (self->slots_0x40[self->field_0x20] != 0) {
            fn_801A0004(self->slots_0x40[self->field_0x20]);
        }
        if (self->spr_0x38 != 0) {
            fn_801A0004(self->spr_0x38);
        }
        if (self->spr_0x3c != 0) {
            fn_801A0004(self->spr_0x3c);
        }
        if (self->cursorL != 0) {
            fn_801A0004(self->cursorL);
        }
        if (self->cursorR != 0) {
            fn_801A0004(self->cursorR);
        }
    }
    if (self->field_0x24 != 0) {
        if (self->spr_0xa8 != 0) {
            fn_801A0004(self->spr_0xa8);
        }
    }
    if (self->flag_0x18 != 0) {
        fn_801A1174(0x50d, 5, 0, 0, 0);
        fn_801A1128(lbl_806D9C20, lbl_806D9C28);
        fn_801A0DF0();
    }
}

/* ------------------------------------------------------------------ */
/* FrameSelection_Update (0x801C5890)                                  */
/* ------------------------------------------------------------------ */
extern "C" int FrameSelection_Update(clFlowNamcamRec *self) {
    int i;
    int prev;
    int count;
    InputState *input;

    RumbleUpdate();
    if (self->field_0x24 != 0) {
        Sprite_AdvanceAnim(self->spr_0x30, FLOAT_DELTA_TIME);
        Sprite_AdvanceAnim(self->spr_0x34, FLOAT_DELTA_TIME);
        if (self->spr_0xa8 != 0) {
            Sprite_AdvanceAnim(self->spr_0xa8, FLOAT_DELTA_TIME_2X);
        }
        if (--self->field_0x24 == 0) {
            self->flag_0x0c = 1;
            StartScreenFade(FLOAT_FADE_OFFSET);
            return self->field_0x2c;
        }
        return -1;
    }
    if (self->flag_0x0c != 0) {
        Sprite_AdvanceAnim(self->spr_0x30, FLOAT_DELTA_TIME);
        SetSyncTarget(0x14);
        if (self->field_0x28 == 0) {
            if (IsSyncReached() != 0) {
                self->field_0x28 = 8;
            }
        } else {
            if (--self->field_0x28 <= 0) {
                if (self->flag_0x19 != 0) {
                    ResetIOPorts();
                }
                self->field_0x2c = 0x19;
            }
        }
        return self->field_0x2c;
    }
    Sprite_AdvanceAnim(self->spr_0x30, FLOAT_DELTA_TIME);
    self->namcam->Pump();
    input = GetInput();
    if (input != 0) {
        prev = self->visualIdx;
        if (GetInput()->field_0x14 > 0) {
            for (count = 0xb; count != 0; count--) {
                if (++self->visualIdx >= 0xb) {
                    self->visualIdx = 0;
                }
                if (self->available[self->visualIdx] != 0) {
                    break;
                }
            }
        } else if (GetInput()->field_0x14 < 0) {
            for (count = 0xb; count != 0; count--) {
                if (--self->visualIdx < 0) {
                    self->visualIdx = 0xa;
                }
                if (self->available[self->visualIdx] != 0) {
                    break;
                }
            }
        }
        if (prev != self->visualIdx) {
            Sprite *spr;

            self->sprites_0x50[prev]->alpha = FLOAT_UNFOCUSED_ALPHA;
            spr = self->sprites_0x50[prev];
            spr->scaleX = FLOAT_UNFOCUSED_SCALE;
            spr->scaleY = FLOAT_UNFOCUSED_SCALE;
            self->sprites_0x50[self->visualIdx]->alpha = FLOAT_FOCUSED_SCALE;
            spr = self->sprites_0x50[self->visualIdx];
            spr->scaleX = FLOAT_FOCUSED_SCALE;
            spr->scaleY = FLOAT_FOCUSED_SCALE;
            spr = self->spr_0x34;
            spr->posX = FLOAT_TITLE_STEP_X * (f32)self->visualIdx + FLOAT_TITLE_BASE_X;
            spr->posY = FLOAT_TITLE_POS_Y;
            PlayCursorMoveSE();
        }
    }
    for (i = 0; i < 0xb; i++) {
        Sprite_AdvanceAnim(self->sprites_0x50[i], FLOAT_DELTA_TIME);
        Sprite_AdvanceAnim(self->sprites_0x7c[i], FLOAT_DELTA_TIME);
    }
    Sprite_AdvanceAnim(self->spr_0x34, FLOAT_DELTA_TIME);
    if (self->slots_0x40[self->field_0x20] != 0) {
        if (Sprite_AdvanceAnim(self->slots_0x40[self->field_0x20], FLOAT_DELTA_TIME) == 0) {
            self->field_0x20 = (self->field_0x20 + 1) % 2;
            Sprite_SetAnimTime(self->slots_0x40[self->field_0x20], FLOAT_ANIM_RESET);
        }
    }
    if (self->spr_0x38 != 0) {
        Sprite_AdvanceAnim(self->spr_0x38, FLOAT_DELTA_TIME);
    }
    if (self->spr_0x3c != 0) {
        Sprite_AdvanceAnim(self->spr_0x3c, FLOAT_DELTA_TIME);
    }
    return self->Confirm();
}

#include "game/singleton.h"
/*
 * FrameSelection method bundle (compiled as C++: -lang=c++ -Cpp_exceptions on).
 *
 *   FrameSelection_Init    @ 0x801C4EA8 - the clFlowChara ctor, in src/game/clFlowChara.cpp
 *   FrameSelection_Confirm @ 0x801C53A0 (size 0x2FC) - C++
 *   FrameSelection_Draw    @ 0x801C569C (size 0x1F4) - C++
 *   FrameSelection_Update  @ 0x801C5890 (size 0x3A4) - C++
 *
 * Confirm/Draw/Update operate on the NamCam confirm scene layout.
 *
 * Confirm/Draw/Update carry plain 8-byte extab entries that CW auto-emits. Mangled C++ references are bridged
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
extern void GXTexModeSync(void);
extern int GetDisplayBufferIndex(void);
extern void *GetDisplayContext(int index);
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
    return SINGLETON_INSTANCE(g_pInputState);
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


/* FrameSelection_Init (the clFlowChara ctor) lives in src/game/clFlowChara.cpp. */

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
            GXTexModeSync();
            cfgX = *(int *)(lbl_80598A60 + 0x4c);
            cfgY = *(int *)(lbl_80598A60 + 0x48);
            ctx = GetDisplayContext(GetDisplayBufferIndex());
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

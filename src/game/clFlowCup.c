
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D12E4[1];
/* clFlowCup extab bundle: generated from target assembly. */
/*
 * clFlowCup_Draw   @ 0x801C7360 (0x3CC)
 * clFlowCup_Update @ 0x801C772C (0x11C8)
 * clFlowCup_Dtor   @ 0x801C88F4 (0x1C0)
 * clFlowCup_Init   @ 0x801C8AB4 (0x7D4)
 *
 * Keep fragment order equal to target extab/extabindex and .text order.
 */
struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0xF];
    int value14;
    int value18;
    int value1C;
};

struct CupSpr {
    unsigned char pad_00[0xC];
    float x;
    float y;
    float sx;
    float sy;
    float rot;
    float alpha;
    unsigned char pad_24[0xC];

    CupSpr(int id, int loop, float x, float y, float sx, float sy, float rot, float a);
    CupSpr(int id, int loop, int c);
};

struct CupSlot {
    CupSpr *sprite;
    CupSpr *sub;
    int anim;
    int pad;
};

struct CupPair {
    CupSpr *a;
    CupSpr *b;
};

#include "game/types/CupSide.h"

struct clFlowCup {
    void *vtbl;
    int round;
    int x08;
    int state;
    unsigned char advance;
    unsigned char pad_11[3];
    int timer;
    CupSpr *sprite18;
    CupSpr *sprite1C;
    unsigned char pad_20[0xC];
    CupSlot slots[9];
    int musicSel;
    unsigned char showC0;
    unsigned char pad_C1[3];
    int pairSel[4];
    float brightness;
    CupPair pairs[4];
    CupSpr *spriteF8;
    CupSpr *spriteFC;
    unsigned char pad_100[8];
    CupSpr *sprite108;
    CupSpr *sprite10C;
    unsigned char show110;
    unsigned char show111;
    unsigned char pad_112[2];
    float alpha114;
    unsigned char mode;
    unsigned char pad_119[3];
    float x11C;
    float x120;
    CupSpr *icons[9];
    CupSpr *sprite148;
    CupSpr *sprite14C;
    CupSpr *sprite150;
    unsigned char unlock154;
    unsigned char unlock155;
};

struct CupName {
    short id0;
    short id1;
    float xEn;
    float xJp;
};

struct CupMark {
    short x0;
    short id;
    float x;
    float y;
};

struct SpriteInfo {
    float x;
    float y;
    float pad8[3];
    float r;
    float g;
    float b;
    float a;
    float pad24[5];
};

#ifdef __cplusplus
extern "C" {
#endif
extern void *clFlowCup_Dtor_data_8049AE5C[];
extern CupName clFlowCup_data_8049ADE4[];
extern const float lbl_806D9CA4;
extern InputState *g_pInputState;
extern int g_roundIndex;
void fn_80169C44(void);
void SetScreenBrightness(float);
void Sprite_Destroy(void *, int);
void MemoryManager_TimedFree(void *);
void fn_80120A08(int);
void fn_801A1678(void);
void dtor_801BA14C(void *, int);

/* === extracted from auto_clFlowCup_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8019FF8C(void *spr, int id, SpriteInfo *out);
extern void fn_801A0004(void *spr);
extern void fn_801A0DF0(void);
extern void fn_801A0FD4(float r, float g, float b, float a);
extern void fn_801A10DC(float sx, float sy);
extern void fn_801A1128(float x, float y);
extern void fn_801A1174(int id, int layer, int a, int b, int c);
extern int isJapanese(void);

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D9C88;
extern const float lbl_806D9CA8;
extern const float lbl_806D9CAC;
extern const float lbl_806D9CB0;
extern const float lbl_806D9CB4;
extern const float lbl_806D9CB8;
extern const float lbl_806D9CBC;
extern const float lbl_806D9CC0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern CupMark clFlowCup_data_8049AD58[];

/* --- function index (1 fns, .text 0x801C7360..0x801C772C) ---
 * [  0] 0x801C7360 size:0x3CC   global clFlowCup_Draw
 */

/* --- forward decls --- */
/* --- asm function bodies (.text order = fn address order) --- */
static inline void DrawSprite(void *spr) {
    if (spr != 0) {
        fn_801A0004(spr);
    }
}

static inline void DrawSide(clFlowCup *self) {
    if (self->sprite108 != 0 && self->show110 != 0) {
        fn_801A0004(self->sprite108);
    }
    if (self->sprite10C != 0 && self->show111 != 0) {
        fn_801A0004(self->sprite10C);
    }
}

void clFlowCup_Draw(clFlowCup *self) {
    int i;
    int j;
    int k;

    if (self->spriteF8 != 0) {
        fn_801A0004(self->spriteF8);
    }
    if (self->sprite18 != 0) {
        fn_801A0004(self->sprite18);
    }
    if (self->slots[8].sub != 0) {
        fn_801A0004(self->slots[8].sub);
    }
    if (self->spriteFC != 0) {
        fn_801A0004(self->spriteFC);
    }
    for (i = 0; i < 9; i++) {
        if (i != self->round && self->slots[i].sprite != 0) {
            DrawSprite(self->slots[i].sprite);
        }
    }
    if (self->state != 4 && self->round % 2 == 1) {
        DrawSide(self);
    }
    if (self->slots[self->round].sprite != 0) {
        fn_801A0004(self->slots[self->round].sprite);
        if (self->mode == 1) {
            SpriteInfo info;

            fn_8019FF8C(self->slots[self->round].sprite, clFlowCup_data_8049AD58[self->round].id, &info);
            fn_801A1174(0x15F4, 5, 0, 0, 0);
            fn_801A1128(info.x - lbl_806D9CA8, lbl_806D9CAC + info.y);
            fn_801A10DC(lbl_806D9CB0, lbl_806D9CB0);
            fn_801A0FD4(info.r, info.g, info.b, info.a);
            fn_801A0DF0();
        }
    }
    if (self->state != 4 && self->round % 2 == 0) {
        DrawSide(self);
    }
    fn_801A1174(clFlowCup_data_8049ADE4[self->round].id0, 4, 0, 0, 0);
    fn_801A1128(lbl_806D9CB4, lbl_806D9CB8);
    fn_801A0FD4(lbl_806D9C88, lbl_806D9C88, lbl_806D9C88, self->alpha114);
    fn_801A0DF0();
    fn_801A1174(clFlowCup_data_8049ADE4[self->round].id1, 4, 0, 0, 0);
    if (isJapanese() == 0) {
        fn_801A1128(clFlowCup_data_8049ADE4[self->round].xEn, lbl_806D9CB8);
    } else {
        fn_801A1128(clFlowCup_data_8049ADE4[self->round].xJp, lbl_806D9CB8);
    }
    fn_801A0FD4(lbl_806D9C88, lbl_806D9C88, lbl_806D9C88, self->alpha114);
    fn_801A0DF0();
    fn_801A1174(0x174C, 4, 0, 0, 0);
    fn_801A1128(lbl_806D9CBC, lbl_806D9CC0);
    fn_801A0FD4(lbl_806D9C88, lbl_806D9C88, lbl_806D9C88, self->alpha114);
    fn_801A0DF0();
    for (j = 0; j < 4; j++) {
        if (self->pairSel[j] != -1) {
            fn_801A0004((&self->pairs[j].a)[self->pairSel[j]]);
        }
    }
    if (self->sprite1C != 0) {
        fn_801A0004(self->sprite1C);
    }
    if (self->state == 4) {
        fn_801A0004(self->sprite14C);
        fn_801A0004(self->sprite148);
        fn_801A0004(self->sprite150);
        for (k = 0; k < 9; k++) {
            fn_801A0004(self->icons[k]);
        }
    }
}



static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

/* === clFlowCup_Update (C++) === */
extern void *Alloc(unsigned long size);
extern void CupTile_StateChange(clFlowCup *self, int idx, int mode);
extern void *GetInputManager(void);
extern void *InputMgr_GetPlayer(void *mgr, int idx);
extern void RumbleUpdate(void);
extern void SetCourseParams(int course, int a, int b, int c);
extern void SetRumbleMode(int a, int b, int c);
extern unsigned char Sprite_AdvanceAnim(CupSpr *spr, float step);
extern void Sprite_CreateWithParams(void *spr, int id, int loop, float x, float y, float sx, float sy, float rot, float a);
extern void Sprite_InitWithAnim(void *spr, int id, int loop, int c);
extern void Sprite_SetAnimParam(CupSpr *spr, int a, int b);
extern void Sprite_SetupAnim(CupSpr *spr, int id, int loop, int c);
extern void fn_801699D8(int a, int b);
extern void fn_8019FF6C(CupSpr *spr, int v);
extern void fn_801A0550(CupSpr *spr);
extern void fn_801B7C64(void);
extern void fn_801B7CAC(void);
extern void fn_801B85DC(int a, int b, int c);
extern void fn_801B87D8(void);
extern void fn_801C64DC(clFlowCup *self, int round);
extern void fn_801C6744(clFlowCup *self, int idx);
extern unsigned char fn_801D5C88(void *data, int cc);

extern unsigned int g_ccClass;
extern signed char lbl_806D184C;
extern unsigned char lbl_806D184D;
extern const double lbl_806D9C68;
extern const float lbl_806D9C70;
extern const float lbl_806D9C74;
extern const float lbl_806D9C7C;
extern const float lbl_806D9C80;
extern const float lbl_806D9C90;
extern const float lbl_806D9C94;
extern const float lbl_806D9CA0;
extern const float lbl_806D9CC4;
extern const float lbl_806D9CC8;
extern const float lbl_806D9CCC;
extern const float lbl_806D9CD0;
extern const float lbl_806D9CD4;
extern const float lbl_806D9CD8;
extern const float lbl_806D9CDC;
extern const float lbl_806D9CE0;

extern unsigned int g_playerData[];
extern const CupSide clFlowCup_Update_rodata_8039B228[];
extern short clFlowCup_Update_data_8049ADD0[];

/* --- function index (1 fns, .text 0x801C772C..0x801C88F4) ---
 * [  0] 0x801C772C size:0x11C8  global clFlowCup_Update
 */

/* --- forward decls --- */
int clFlowCup_Update(clFlowCup *self);


static inline void SetPairAlpha(clFlowCup *self, float a) {
    self->pairs[0].a->alpha = a;
    self->pairs[0].b->alpha = a;
    self->pairs[1].a->alpha = a;
    self->pairs[1].b->alpha = a;
    self->pairs[2].a->alpha = a;
    self->pairs[2].b->alpha = a;
    self->pairs[3].a->alpha = a;
    self->pairs[3].b->alpha = a;
    self->sprite1C->alpha = a;
    self->alpha114 = a;
}

static inline void PlayCupMusic(clFlowCup *self, int sel) {
    if (self->slots[8].sub != 0 && self->slots[8].anim == 1) {
        self->musicSel = sel;
        Sprite_SetupAnim(self->slots[8].sub, 0x183, 0, 0);
        Sprite_SetAnimParam(self->slots[8].sub, 0x1744, clFlowCup_Update_data_8049ADD0[self->musicSel]);
        fn_801A0550(self->slots[8].sub);
        fn_8019FF6C(self->slots[8].sub, 1);
    }
}

static inline void SetX(CupSpr *spr, float x) {
    spr->x = x;
}

static inline void SetPos(CupSpr *spr, float x, float y) {
    spr->x = x;
    spr->y = y;
}

static inline void SetScale(CupSpr *spr, float sx, float sy) {
    spr->sx = sx;
    spr->sy = sy;
}

static inline void UpdateSides(clFlowCup *self) {
    CupSpr *spr;

    fn_801C64DC(self, self->round);
    self->show110 = 0;
    spr = self->sprite108;
    if (spr != 0) {
        SetPos(spr, clFlowCup_Update_rodata_8039B228[self->round].x0, clFlowCup_Update_rodata_8039B228[self->round].y0);
        self->sprite108->rot = lbl_806D9C68 * clFlowCup_Update_rodata_8039B228[self->round].rot0;
        SetScale(self->sprite108, lbl_806D9C70, lbl_806D9C70);
        if (self->round != 0 || self->mode == 1) {
            self->show110 = 1;
        }
    }
    self->show111 = 0;
    spr = self->sprite10C;
    if (spr != 0) {
        { float x = clFlowCup_Update_rodata_8039B228[self->round].x1; SetPos(spr, x, clFlowCup_Update_rodata_8039B228[self->round].y1); }
        self->sprite10C->rot = lbl_806D9C68 * clFlowCup_Update_rodata_8039B228[self->round].rot1;
        SetScale(self->sprite10C, lbl_806D9C70, lbl_806D9C70);
        if (self->round != 7) {
            self->show111 = 1;
        }
        if (self->mode == 0 && fn_801D5C88(g_playerData, g_ccClass) == 1) {
            self->show111 = 1;
        }
        if (self->mode == 0 && self->round == 6 && self->unlock154 == 0) {
            self->show111 = 0;
        }
        if (self->mode == 1 && self->round == 6 && self->unlock155 == 0) {
            self->show111 = 0;
        }
    }
}

int clFlowCup_Update(clFlowCup *self) {
    int i;
    int j;

    RumbleUpdate();
    if (self->advance != 0) {
        self->state++;
        self->advance = 0;
    }
    self->timer++;
    switch (self->state) {
    case 0:
        if (self->timer == 1) {
            CupTile_StateChange(self, 0, 1);
        }
        if (self->timer == 6) {
            CupTile_StateChange(self, 1, 1);
        }
        if (self->timer == 10) {
            CupTile_StateChange(self, 2, 1);
        }
        if (self->timer == 14) {
            CupTile_StateChange(self, 3, 1);
        }
        if (self->timer == 18) {
            CupTile_StateChange(self, 4, 1);
        }
        if (self->timer == 20) {
            CupTile_StateChange(self, 5, 1);
        }
        if (self->timer == 22) {
            CupTile_StateChange(self, 6, 1);
        }
        if (self->timer == 26) {
            CupTile_StateChange(self, 7, 1);
        }
        if (self->timer == 30) {
            if (self->mode == 1) {
                Sprite_SetupAnim(self->spriteF8, 0x18E, 1, 0);
                Sprite_SetupAnim(self->spriteFC, 0x1C7, 1, 0);
            } else {
                Sprite_SetupAnim(self->spriteF8, 0x184, 1, 0);
                Sprite_SetupAnim(self->spriteFC, 0x1DD, 1, 0);
                Sprite_SetAnimParam(self->spriteFC, 0x1AD4, 0x1AE3);
            }
        }
        if (self->timer == 40) {
            if (self->mode == 1) {
                self->sprite18 = new CupSpr(0x18F, 1, lbl_806D9CC4, lbl_806D9CC8, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
            } else {
                self->sprite18 = new CupSpr(0x185, 1, lbl_806D9CC4, lbl_806D9CC8, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
            }
            self->showC0 = 1;
        }
        if (self->timer == 60) {
            self->sprite108 = new CupSpr(0x9C, 1, 0);
            self->sprite10C = new CupSpr(0x9C, 1, 0);
            fn_8019FF6C(self->sprite108, 1);
            fn_8019FF6C(self->sprite10C, 1);
            CupTile_StateChange(self, self->round, 4);
            UpdateSides(self);
            SetScreenBrightness(self->brightness);
            lbl_806D184C = 1;
            lbl_806D184D = 0;
            self->advance = 1;
            fn_801699D8(0, 1);
        }
        if (self->timer >= 18 && self->timer <= 30) {
            SetPairAlpha(self, ((float)self->timer - lbl_806D9CCC) / lbl_806D9C90);
        }
        break;
    case 1: {
        int prev = self->round;
        int st;

        if (input_state() != 0) {
            { InputState *st = input_state(); self->round += st->value14; }
            if (self->round > 6) {
                if (self->mode == 0 && self->unlock154 == 0) {
                    self->round = 6;
                }
                if (self->mode == 1 && self->unlock155 == 0) {
                    self->round = 6;
                }
            }
            if (self->round > 7) {
                self->round = 7;
                if (self->mode == 0 && fn_801D5C88(g_playerData, g_ccClass) == 1) {
                    Sprite_SetupAnim(self->sprite148, 0x18F, 1, 0);
                    Sprite_SetupAnim(self->sprite14C, 0x18E, 1, 0);
                    Sprite_SetupAnim(self->sprite150, 0x1C7, 1, 0);
                    self->mode = 1;
                    self->round = 0;
                    self->state = 4;
                    self->timer = 0;
                }
            }
            if (self->round < 0) {
                self->round = 0;
                if (self->mode == 1) {
                    Sprite_SetupAnim(self->sprite148, 0x185, 1, 0);
                    Sprite_SetupAnim(self->sprite14C, 0x184, 1, 0);
                    Sprite_SetupAnim(self->sprite150, 0x1DD, 1, 0);
                    Sprite_SetAnimParam(self->sprite150, 0x1AD4, 0x1AE3);
                    self->mode = 0;
                    self->round = 7;
                    self->state = 4;
                    self->timer = 0;
                }
            }
        }
        if (prev != self->round) {
            CupTile_StateChange(self, prev, 2);
            CupTile_StateChange(self, self->round, 4);
            PlayCupMusic(self, self->round);
            UpdateSides(self);
            fn_801B7CAC();
        }
        st = self->x08;
        switch (st) {
        case -1:
            self->brightness -= lbl_806D9CA0;
            InputMgr_GetPlayer(GetInputManager(), 0);
            if (input_state()->value18 == 1 || self->brightness < lbl_806D9C80) {
                SetRumbleMode(0, 1, 1);
                if (input_state() != 0) {
                    InputState *state = input_state();

                    state->active = 0;
                    state->value18 = 0;
                    state->value1C = 0;
                }
                if (self->round == 0) {
                    SetCourseParams(7, 0, 0, 0);
                }
                if (self->round == 1) {
                    SetCourseParams(1, 0, 0, 0);
                }
                if (self->round == 2) {
                    SetCourseParams(8, 0, 0, 0);
                }
                if (self->round == 3) {
                    SetCourseParams(2, 0, 0, 0);
                }
                if (self->round == 4) {
                    SetCourseParams(3, 0, 0, 0);
                }
                if (self->round == 5) {
                    SetCourseParams(4, 0, 0, 0);
                }
                if (self->round == 6) {
                    SetCourseParams(5, 0, 0, 0);
                }
                if (self->round == 7) {
                    SetCourseParams(6, 0, 0, 0);
                }
                self->x08 = 0x1B;
                self->brightness = lbl_806D9CA4;
                fn_801B7C64();
            }
            SetScreenBrightness(self->brightness);
            st = self->x08;
            break;
        }
        if (st != -1) {
            for (i = 0; i < 9; i++) {
                if (i == self->round) {
                    CupTile_StateChange(self, i, 5);
                } else {
                    CupTile_StateChange(self, i, 3);
                }
            }
            Sprite_Destroy(self->sprite18, 1);
            Sprite_Destroy(self->sprite108, 1);
            Sprite_Destroy(self->sprite10C, 1);
            self->sprite18 = 0;
            self->timer = 0;
            self->sprite108 = 0;
            self->sprite10C = 0;
            self->advance = 1;
            lbl_806D184C = -1;
            fn_801B85DC(0x15, self->mode, 0);
        }
        break;
    }
    case 2:
        if (self->timer == 60) {
            CupTile_StateChange(self, self->round, 6);
            fn_801B87D8();
            if (self->slots[8].sub != 0 && self->slots[8].anim == 1) {
                self->slots[8].anim = 2;
                Sprite_SetupAnim(self->slots[8].sub, 0x35, 0, 0);
                Sprite_SetAnimParam(self->slots[8].sub, 0x1744, clFlowCup_Update_data_8049ADD0[self->musicSel]);
                fn_801A0550(self->slots[8].sub);
            }
            self->showC0 = 0;
            self->timer = 0;
            self->advance = 1;
            fn_801699D8(0, 0);
        }
        break;
    case 3:
        if (self->timer <= 10) {
            SetPairAlpha(self, lbl_806D9C88 - (float)self->timer / lbl_806D9CD0);
            self->x11C = lbl_806D9CD4 * ((float)self->timer / lbl_806D9CD0);
        }
        if (self->timer >= 22 && self->slots[8].sub == 0) {
            return self->x08;
        }
        break;
    case 4: {
        float base;
        const CupMark *mark;

        if (self->mode == 1) {
            self->x120 = lbl_806D9CD4 * ((float)self->timer / lbl_806D9CD8);
        } else {
            self->x120 = lbl_806D9C94 * ((float)self->timer / lbl_806D9CD8);
        }
        if (self->timer <= 10) {
            self->x11C = lbl_806D9CD4 * ((float)self->timer / lbl_806D9CD0);
        }
        if (self->timer >= 20) {
            self->x120 = lbl_806D9C80;
            self->x11C = lbl_806D9C80;
            self->state = 1;
            self->timer = 0;
            if (self->mode == 0) {
                self->round = 7;
                Sprite_SetupAnim(self->sprite18, 0x185, 1, 0);
                Sprite_SetupAnim(self->spriteF8, 0x184, 1, 0);
                Sprite_SetupAnim(self->spriteFC, 0x1DD, 0, 0);
                Sprite_SetAnimParam(self->spriteFC, 0x1AD4, 0x1AE3);
                fn_801A0550(self->spriteFC);
            } else {
                self->round = 0;
                Sprite_SetupAnim(self->sprite18, 0x18F, 1, 0);
                Sprite_SetupAnim(self->spriteF8, 0x18E, 1, 0);
                Sprite_SetupAnim(self->spriteFC, 0x1C7, 1, 0);
            }
        }
        base = lbl_806D9C94 + self->x120;
        if (self->mode == 0) {
            base = lbl_806D9CD4 + self->x120;
        }
        for (i = 0; i < 8; i++) {
            SetX(self->slots[i].sprite, self->x120 + clFlowCup_data_8049AD58[i].x);
            SetX(self->icons[i], base + clFlowCup_data_8049AD58[i].x);
        }
        {
            float x = lbl_806D9CC4 + base;

            self->sprite148->x = x;
            self->sprite14C->x = x;
        }
        if (self->timer >= 10) {
            self->sprite150->x = lbl_806D9C94 * ((float)(self->timer - 10) / lbl_806D9CD0) + lbl_806D9CDC;
        } else {
            self->sprite150->x = lbl_806D9CDC;
        }
        break;
    }
    }
    if (self->spriteFC != 0) {
        self->spriteFC->x = lbl_806D9CE0 + self->x11C;
        Sprite_AdvanceAnim(self->spriteFC, lbl_806D9C7C);
    }
    if (self->spriteF8 != 0) {
        self->spriteF8->x = lbl_806D9C74 + self->x120;
        Sprite_AdvanceAnim(self->spriteF8, lbl_806D9C7C);
    }
    if (self->sprite18 != 0) {
        SetPos(self->sprite18, lbl_806D9CC4 + self->x120, lbl_806D9CC8);
        Sprite_AdvanceAnim(self->sprite18, lbl_806D9C7C);
    }
    for (i = 0; i < 9; i++) {
        fn_801C6744(self, i);
    }
    if (self->slots[8].sub != 0 && Sprite_AdvanceAnim(self->slots[8].sub, lbl_806D9C7C) == 0) {
        if (self->slots[8].anim == 0) {
            self->slots[8].anim++;
            PlayCupMusic(self, self->musicSel);
        }
        if (self->slots[8].anim == 2) {
            Sprite_Destroy(self->slots[8].sub, 1);
            self->slots[8].sub = 0;
            self->slots[8].anim++;
        }
    }
    for (j = 0; j < 4; j++) {
        if (self->pairSel[j] != -1) {
            Sprite_AdvanceAnim((&self->pairs[j].a)[self->pairSel[j]], lbl_806D9C7C);
        }
    }
    if (self->sprite1C != 0) {
        Sprite_AdvanceAnim(self->sprite1C, lbl_806D9C7C);
    }
    if (self->sprite108 != 0) {
        Sprite_AdvanceAnim(self->sprite108, lbl_806D9C7C);
    }
    if (self->sprite10C != 0) {
        Sprite_AdvanceAnim(self->sprite10C, lbl_806D9C7C);
    }
    return -1;
}


/* === extracted from auto_clFlowCup_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

/* --- function index (1 fns, .text 0x801C88F4..0x801C8AB4) ---
 * [  0] 0x801C88F4 size:0x1C0   global clFlowCup_Dtor
 */

/* --- forward decls --- */
#pragma exceptions on


static inline int GetRound(clFlowCup *self) {
    int round = 0;
    if (self->mode == 1) {
        round = 4;
    }
    return round;
}

extern "C" clFlowCup *clFlowCup_Dtor(clFlowCup *self, short flags) {
    int round;
    int i;
    int j;

    if (self != 0) {
        self->vtbl = clFlowCup_Dtor_data_8049AE5C;
        fn_80169C44();
        g_roundIndex = GetRound(self);
        if (input_state() != 0) {
            InputState *state = input_state();

            state->active = 0;
            state->value18 = 0;
            state->value1C = 0;
        }
        SetScreenBrightness(lbl_806D9CA4);
        fn_80120A08(clFlowCup_data_8049ADE4[0].id1);
        fn_80120A08(clFlowCup_data_8049ADE4[0].id0);
        Sprite_Destroy(self->sprite108, 1);
        Sprite_Destroy(self->sprite10C, 1);
        Sprite_Destroy(self->sprite18, 1);
        Sprite_Destroy(self->spriteF8, 1);
        Sprite_Destroy(self->spriteFC, 1);
        Sprite_Destroy(self->sprite1C, 1);
        Sprite_Destroy(self->slots[8].sub, 1);
        Sprite_Destroy(self->sprite148, 1);
        Sprite_Destroy(self->sprite14C, 1);
        Sprite_Destroy(self->sprite150, 1);
        for (i = 0; i < 9; i++) {
            Sprite_Destroy(self->slots[i].sprite, 1);
            Sprite_Destroy(self->icons[i], 1);
        }
        for (j = 0; j < 4; j++) {
            Sprite_Destroy(self->pairs[j].a, 1);
            Sprite_Destroy(self->pairs[j].b, 1);
        }
        fn_801A1678();
        dtor_801BA14C(self, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset



/* === clFlowCup_Init (C++ ctor) === */
/* === .data 0x8049AD58..0x8049AE70 (owned by this TU) === */
extern char clFlowCup_data_806CFDE0[];
extern char clFlowCup_data_806CFDE8[];

CupMark clFlowCup_data_8049AD58[10] = {
    { 0x1777, 0x1780, 90.0f, 185.0f },
    { 0x1778, 0x1781, 161.0f, 263.0f },
    { 0x1779, 0x1782, 221.0f, 185.0f },
    { 0x177A, 0x1783, 292.0f, 263.0f },
    { 0x177B, 0x1784, 353.0f, 185.0f },
    { 0x177C, 0x1785, 424.0f, 263.0f },
    { 0x177D, 0x1786, 484.0f, 185.0f },
    { 0x177E, 0x1787, 555.0f, 263.0f },
    { 0x177F, 0x1787, 555.0f, 263.0f },
    { 0, 0, 0.0f, 0.0f },
};

short clFlowCup_Update_data_8049ADD0[10] = {
    0x1744, 0x1745, 0x1746, 0x1747, 0x1748, 0x1749, 0x174A, 0x174B, 0, 0,
};

CupName clFlowCup_data_8049ADE4[9] = {
    { 0x1758, 0x1729, 127.0f, 142.0f },
    { 0x1758, 0x172A, 117.0f, 137.0f },
    { 0x1759, 0x172B, 137.0f, 157.0f },
    { 0x1759, 0x172C, 102.0f, 102.0f },
    { 0x1759, 0x172D, 117.0f, 137.0f },
    { 0x175A, 0x172E, 132.0f, 152.0f },
    { 0x175A, 0x172F, 112.0f, 152.0f },
    { 0x175A, 0x1730, 132.0f, 162.0f },
    { 0, 0, 0.0f, 0.0f },
};

void *clFlowCup_data_8049AE50[3] = { clFlowCup_data_806CFDE0, 0, 0 };

void *clFlowCup_Dtor_data_8049AE5C[5] = {
    clFlowCup_data_806CFDE8, 0, (void *)clFlowCup_Dtor, (void *)clFlowCup_Update, (void *)clFlowCup_Draw,
};

extern void InitBGM(void);
extern void InitRumbleController(int);
extern unsigned char IsCardValid(void);
extern void PCBComm_PackAndTriggerCardSnapshot(void);
extern void PreloadResource(int);
extern void SetSyncTarget(int);
extern void SetupBgSprites(int);
extern void SpriteSystem_EnsureInit(void);
extern int fn_801A0310(CupSpr *spr, int id);
extern unsigned char fn_801D5B8C(void *data, int cc, int idx, int n);

extern const float lbl_806D9C78;
extern const float lbl_806D9CE4;
extern const float lbl_806D9CE8;
extern const float lbl_806D9CEC;
extern const float lbl_806D9CF0;
extern const float lbl_806D9CF4;
extern const float lbl_806D9CF8;
extern const float lbl_806D9CFC;
extern const float lbl_806D9D00;
extern const float lbl_806D9D04;

#ifdef __cplusplus
}
#endif

#include "game/types/FlowBase.h"

struct CupIconDef {
    short anim;
    short id;
    float x;
    float y;
};


struct CupFlow : FlowBase {
    int round;
    int x08;
    int state;
    unsigned char advance;
    unsigned char pad_11[3];
    int timer;
    CupSpr *sprite18;
    CupSpr *sprite1C;
    int slots[9][4];
    CupSpr *musicSel;
    int musicB4;
    int musicB8;
    int musicBC;
    unsigned char showC0;
    unsigned char pad_C1[3];
    int pairSel[4];
    float brightness;
    CupSpr *pairs[2][4];
    CupSpr *spriteF8;
    CupSpr *spriteFC;
    int handle100;
    int handle104;
    CupSpr *sprite108;
    CupSpr *sprite10C;
    unsigned char show110;
    unsigned char show111;
    unsigned char pad_112[2];
    float alpha114;
    unsigned char mode;
    unsigned char pad_119[3];
    float x11C;
    float x120;
    CupSpr *icons[9];
    CupSpr *sprite148;
    CupSpr *sprite14C;
    CupSpr *sprite150;
    unsigned char unlock154;
    unsigned char unlock155;

    CupFlow();
};

static inline void SetXY(CupSpr *s, float x, float y) {
    s->x = x;
    s->y = y;
}

static inline void SetScale(CupSpr *s, float v) {
    s->sx = v;
    s->sy = v;
}

CupFlow::CupFlow() {
    int i;
    int count;
    vt = clFlowCup_Dtor_data_8049AE5C;
    SpriteSystem_EnsureInit();
    PCBComm_PackAndTriggerCardSnapshot();
    SetSyncTarget(0x15);
    PreloadResource(clFlowCup_data_8049ADE4[0].id0);
    PreloadResource(clFlowCup_data_8049ADE4[0].id1);
    PreloadResource(0x1736);
    PreloadResource(0x1AE3);
    PreloadResource(0x1777);
    PreloadResource(0x178B);
    PreloadResource(0x194C);
    PreloadResource(0x195E);
    PreloadResource(0x196F);
    PreloadResource(0x197C);
    PreloadResource(0x1780);
    PreloadResource(0x1794);
    PreloadResource(0x1744);
    PreloadResource(0x175E);
    PreloadResource(0x1EA2);
    PreloadResource(0x1EAA);
    PreloadResource(0x1EB2);
    PreloadResource(0x1EBA);
    PreloadResource(0x1863);
    PreloadResource(0x18BA);
    for (i = 0; i < 9; i++) {
        slots[i][0] = 0;
        slots[i][1] = 0;
        slots[i][2] = 0;
        slots[i][3] = 0;
    }
    round = 0;
    x08 = -1;
    state = 0;
    advance = 0;
    timer = 0;
    sprite18 = 0;
    musicSel = 0;
    musicB4 = 0;
    sprite1C = 0;
    musicB8 = 0;
    showC0 = 0;
    alpha114 = lbl_806D9C80;
    brightness = lbl_806D9CD8;
    mode = fn_801D5C88(g_playerData, g_ccClass);
    spriteF8 = 0;
    spriteFC = 0;
    sprite108 = 0;
    sprite10C = 0;
    x120 = lbl_806D9C80;
    x11C = lbl_806D9C80;
    handle100 = 0;
    handle104 = 0;
    unlock154 = 0;
    unlock155 = 0;
    unlock154 = lbl_806D12E4[g_ccClass];
    if (mode == 1) {
        unlock154 = 1;
    }
    {
        void *pd = g_playerData;
        int n = 0;
        for (int k = 1; k < 9; k++) {
            if (fn_801D5B8C(pd, g_ccClass, k, 7) == 1) {
                n++;
            }
        }
        count = n;
    }
    unlock155 = count >= 7;
    if (!IsCardValid()) {
        unlock154 = unlock155 = 1;
    }
    pairs[0][0] = new CupSpr(0x186, 1, lbl_806D9CE4, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[0][2] = new CupSpr(0x187, 1, lbl_806D9CC8, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[1][0] = new CupSpr(0x188, 1, lbl_806D9CEC, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[1][2] = new CupSpr(0x189, 1, lbl_806D9CF0, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[0][1] = new CupSpr(0x18A, 1, lbl_806D9CE4, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[0][3] = new CupSpr(0x18B, 1, lbl_806D9CC8, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[1][1] = new CupSpr(0x18C, 1, lbl_806D9CEC, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairs[1][3] = new CupSpr(0x18D, 1, lbl_806D9CF0, lbl_806D9CE8, 1.0f, 1.0f, 0.0f, 0.0f);
    pairSel[0] = -1;
    pairSel[1] = -1;
    pairSel[2] = -1;
    pairSel[3] = -1;
    sprite1C = new CupSpr(0x1DE, 1, lbl_806D9CF4, lbl_806D9C78, 1.0f, 1.0f, 0.0f, 0.0f);
    handle100 = fn_801A0310(sprite1C, 0x175B);
    handle104 = fn_801A0310(sprite1C, 0x1EA3);
    fn_801C64DC((clFlowCup *)this, round);
    for (int k = 0; k < 9; k++) {
        icons[k] = new CupSpr(0x180, 1, 0);
        Sprite_SetAnimParam(icons[k], 0x1777, clFlowCup_data_8049AD58[k].x0);
        SetXY(icons[k], lbl_806D9C94 + clFlowCup_data_8049AD58[k].x, clFlowCup_data_8049AD58[k].y);
        SetScale(icons[k], lbl_806D9C70);
    }
    sprite148 = new CupSpr(0x18F, 1, lbl_806D9CF8, lbl_806D9CC8, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
    sprite14C = new CupSpr(0x18E, 1, lbl_806D9CFC, lbl_806D9D00, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
    sprite150 = new CupSpr(0x1C7, 0, lbl_806D9CDC, lbl_806D9D04, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
    if (mode == 1) {
        spriteF8 = new CupSpr(0x3A, 0, lbl_806D9C74, lbl_806D9D00, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
        spriteFC = new CupSpr(0x1C7, 0, lbl_806D9CE0, lbl_806D9D04, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
    } else {
        spriteF8 = new CupSpr(0x38, 0, lbl_806D9C74, lbl_806D9D00, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
        spriteFC = new CupSpr(0xC8, 0, lbl_806D9CE0, lbl_806D9D04, lbl_806D9C88, lbl_806D9C88, lbl_806D9C80, lbl_806D9C88);
        Sprite_SetAnimParam(spriteFC, 0x1AD4, 0x1AE3);
    }
    if (input_state() != 0) {
        InputState *s = input_state();
        s->active = 1;
        s->value18 = 0;
        s->value1C = 0;
    }
    InitBGM();
    SetScreenBrightness(lbl_806D9CA4);
    SetupBgSprites(1);
    if (musicSel == 0) {
        musicB4 = 0;
        musicBC = 0;
        musicSel = new CupSpr(0x36, 0, 0);
        Sprite_SetAnimParam(musicSel, 0x1744, clFlowCup_Update_data_8049ADD0[0]);
        fn_801A0550(musicSel);
        SetXY(musicSel, lbl_806D9C74, lbl_806D9C78);
    }
    InitRumbleController(1);
}

#pragma exceptions reset

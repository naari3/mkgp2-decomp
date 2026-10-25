
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

struct CupSide {
    float x0;
    float y0;
    float rot0;
    float x1;
    float y1;
    float rot1;
};

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
    int x8;
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
extern char lbl_8049AE5C[];
extern CupName lbl_8049ADE4[];
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
extern CupMark lbl_8049AD58[];

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

            fn_8019FF8C(self->slots[self->round].sprite, lbl_8049AD58[self->round].id, &info);
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
    fn_801A1174(lbl_8049ADE4[self->round].id0, 4, 0, 0, 0);
    fn_801A1128(lbl_806D9CB4, lbl_806D9CB8);
    fn_801A0FD4(lbl_806D9C88, lbl_806D9C88, lbl_806D9C88, self->alpha114);
    fn_801A0DF0();
    fn_801A1174(lbl_8049ADE4[self->round].id1, 4, 0, 0, 0);
    if (isJapanese() == 0) {
        fn_801A1128(lbl_8049ADE4[self->round].xEn, lbl_806D9CB8);
    } else {
        fn_801A1128(lbl_8049ADE4[self->round].xJp, lbl_806D9CB8);
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
extern const CupSide lbl_8039B228[];
extern short lbl_8049ADD0[];

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
        Sprite_SetAnimParam(self->slots[8].sub, 0x1744, lbl_8049ADD0[self->musicSel]);
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
        SetPos(spr, lbl_8039B228[self->round].x0, lbl_8039B228[self->round].y0);
        self->sprite108->rot = lbl_806D9C68 * lbl_8039B228[self->round].rot0;
        SetScale(self->sprite108, lbl_806D9C70, lbl_806D9C70);
        if (self->round != 0 || self->mode == 1) {
            self->show110 = 1;
        }
    }
    self->show111 = 0;
    spr = self->sprite10C;
    if (spr != 0) {
        { float x = lbl_8039B228[self->round].x1; SetPos(spr, x, lbl_8039B228[self->round].y1); }
        self->sprite10C->rot = lbl_806D9C68 * lbl_8039B228[self->round].rot1;
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
                Sprite_SetAnimParam(self->slots[8].sub, 0x1744, lbl_8049ADD0[self->musicSel]);
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
            SetX(self->slots[i].sprite, self->x120 + lbl_8049AD58[i].x);
            SetX(self->icons[i], base + lbl_8049AD58[i].x);
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
        self->vtbl = lbl_8049AE5C;
        fn_80169C44();
        g_roundIndex = GetRound(self);
        if (input_state() != 0) {
            InputState *state = input_state();

            state->active = 0;
            state->value18 = 0;
            state->value1C = 0;
        }
        SetScreenBrightness(lbl_806D9CA4);
        fn_80120A08(lbl_8049ADE4[0].id1);
        fn_80120A08(lbl_8049ADE4[0].id0);
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



/* === extracted from auto_clFlowCup_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void InitBGM();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void IsCardValid();
extern void PCBComm_PackAndTriggerCardSnapshot();
extern void PreloadResource();
extern void SetSyncTarget();
extern void SetupBgSprites();
extern void SpriteSystem_EnsureInit();
extern void fn_801A0310();
extern void fn_801D5B8C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D9C78;
extern const float lbl_806D9C88;
extern unsigned int lbl_806D9CE4;
extern unsigned int lbl_806D9CE8;
extern unsigned int lbl_806D9CEC;
extern unsigned int lbl_806D9CF0;
extern unsigned int lbl_806D9CF4;
extern unsigned int lbl_806D9CF8;
extern unsigned int lbl_806D9CFC;
extern unsigned int lbl_806D9D00;
extern unsigned int lbl_806D9D04;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern CupMark lbl_8049AD58[];

/* --- function index (1 fns, .text 0x801C8AB4..0x801C9288) ---
 * [  0] 0x801C8AB4 size:0x7D4   global clFlowCup_Init
 */

/* --- forward decls --- */
asm void clFlowCup_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; unsigned int f79; void *f80; unsigned int f81; void *f82; unsigned int f83; unsigned int f84; void *f85; unsigned int f86; void *f87; unsigned int f88; unsigned int f89; void *f90; unsigned int f91; void *f92; unsigned int f93; unsigned int f94; void *f95; unsigned int f96; void *f97; unsigned int f98; unsigned int f99; void *f100; unsigned int f101; void *f102; unsigned int f103; unsigned int f104; void *f105; unsigned int f106; void *f107; unsigned int f108; unsigned int f109; void *f110; unsigned int f111; void *f112; unsigned int f113; unsigned int f114; void *f115; unsigned int f116; void *f117; unsigned int f118; unsigned int f119; void *f120; unsigned int f121; void *f122; unsigned int f123; unsigned int f124; void *f125; unsigned int f126; void *f127; unsigned int f128; unsigned int f129; void *f130; unsigned int f131; void *f132; unsigned int f133; unsigned int f134; void *f135; unsigned int f136; void *f137; unsigned int f138; unsigned int f139; void *f140; unsigned int f141; void *f142; unsigned int f143; unsigned int f144; void *f145; unsigned int f146; void *f147; unsigned int f148; unsigned int f149; void *f150; unsigned int f151; void *f152; unsigned int f153; unsigned int f154; void *f155; unsigned int f156; void *f157; unsigned int f158; unsigned int f159; void *f160; unsigned int f161; void *f162; unsigned int f163; unsigned int f164; void *f165; } extab_clFlowCup_Init = { 0x308A0000, 0x0000003C, 0x00930138, 0x000002B4, 0x00000130, 0x000002C0, 0x00000138, 0x000002EC, 0x00000144, 0x000002F8, 0x00000138, 0x00000324, 0x00000158, 0x00000330, 0x00000138, 0x0000035C, 0x0000016C, 0x00000368, 0x00000138, 0x00000394, 0x00000180, 0x000003A0, 0x00000138, 0x000003CC, 0x00000194, 0x000003D8, 0x00000138, 0x00000404, 0x000001A8, 0x00000410, 0x00000138, 0x0000043C, 0x000001BC, 0x0000045C, 0x00000138, 0x00000488, 0x000001D0, 0x00000498, 0x000F0138, 0x000004EC, 0x000001E4, 0x00000504, 0x00110138, 0x00000574, 0x000001F8, 0x00000580, 0x00000138, 0x000005AC, 0x0000020C, 0x000005B8, 0x00000138, 0x000005E4, 0x00000220, 0x000005FC, 0x00000138, 0x00000628, 0x00000234, 0x00000634, 0x00000138, 0x00000660, 0x00000248, 0x00000670, 0x00000138, 0x0000069C, 0x0000025C, 0x000006A8, 0x00000138, 0x000006D4, 0x00000270, 0x000006E8, 0x001D0138, 0x00000774, 0x00000284, 0x00000788, 0x00090138, 0x00000000, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowCup_Init = {
    (void *)&clFlowCup_Init, 0x000007D4, (void *)&extab_clFlowCup_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowCup_Init(void) { /* 0x801C8AB4 size:0x7D4 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stmw r26, 0x8(r1)
    lis r4, lbl_8049AD58@ha
    mr r31, r3
    addi r30, r4, lbl_8049AD58@l
    bl InitializeFrameSelection
    addi r0, r30, 0x104
    stw r0, 0x0(r31)
    bl SpriteSystem_EnsureInit
    bl PCBComm_PackAndTriggerCardSnapshot
    li r3, 0x15
    bl SetSyncTarget
    lha r3, 0x8c(r30)
    bl PreloadResource
    addi r3, r30, 0x8c
    lha r3, 0x2(r3)
    bl PreloadResource
    li r3, 0x1736
    bl PreloadResource
    li r3, 0x1ae3
    bl PreloadResource
    li r3, 0x1777
    bl PreloadResource
    li r3, 0x178b
    bl PreloadResource
    li r3, 0x194c
    bl PreloadResource
    li r3, 0x195e
    bl PreloadResource
    li r3, 0x196f
    bl PreloadResource
    li r3, 0x197c
    bl PreloadResource
    li r3, 0x1780
    bl PreloadResource
    li r3, 0x1794
    bl PreloadResource
    li r3, 0x1744
    bl PreloadResource
    li r3, 0x175e
    bl PreloadResource
    li r3, 0x1ea2
    bl PreloadResource
    li r3, 0x1eaa
    bl PreloadResource
    li r3, 0x1eb2
    bl PreloadResource
    li r3, 0x1eba
    bl PreloadResource
    li r3, 0x1863
    bl PreloadResource
    li r3, 0x18ba
    bl PreloadResource
    li r0, 0x3
    li r11, 0x0
    mtctr r0
    clFlowCup_Init_L_801C8BAC:
    addi r0, r11, 0x20
    li r10, 0x0
    stwx r10, r31, r0
    addi r4, r11, 0x24
    addi r3, r11, 0x28
    addi r0, r11, 0x2c
    stwx r10, r31, r4
    addi r9, r11, 0x30
    addi r8, r11, 0x34
    addi r7, r11, 0x38
    stwx r10, r31, r3
    addi r6, r11, 0x3c
    addi r5, r11, 0x40
    addi r4, r11, 0x44
    stwx r10, r31, r0
    addi r3, r11, 0x48
    addi r0, r11, 0x4c
    addi r11, r11, 0x30
    stwx r10, r31, r9
    stwx r10, r31, r8
    stwx r10, r31, r7
    stwx r10, r31, r6
    stwx r10, r31, r5
    stwx r10, r31, r4
    stwx r10, r31, r3
    stwx r10, r31, r0
    bdnz clFlowCup_Init_L_801C8BAC
    stw r10, 0x4(r31)
    li r0, -0x1
    lis r3, g_playerData@ha
    lfs f1, lbl_806D9C80(r2)
    stw r0, 0x8(r31)
    addi r3, r3, g_playerData@l
    lfs f0, lbl_806D9CD8(r2)
    stw r10, 0xc(r31)
    stb r10, 0x10(r31)
    stw r10, 0x14(r31)
    stw r10, 0x18(r31)
    stw r10, 0xb0(r31)
    stw r10, 0xb4(r31)
    stw r10, 0x1c(r31)
    stw r10, 0xb8(r31)
    stb r10, 0xc0(r31)
    stfs f1, 0x114(r31)
    stfs f0, 0xd4(r31)
    lwz r4, g_ccClass(r13)
    bl fn_801D5C88
    stb r3, 0x118(r31)
    li r0, 0x0
    lfs f0, lbl_806D9C80(r2)
    la r3, lbl_806D12E4(r13)  /* lbl_806D12E4 */
    stw r0, 0xf8(r31)
    stw r0, 0xfc(r31)
    stw r0, 0x108(r31)
    stw r0, 0x10c(r31)
    stfs f0, 0x120(r31)
    stfs f0, 0x11c(r31)
    stw r0, 0x100(r31)
    stw r0, 0x104(r31)
    stb r0, 0x154(r31)
    stb r0, 0x155(r31)
    lwz r0, g_ccClass(r13)
    lbzx r0, r3, r0
    stb r0, 0x154(r31)
    lbz r0, 0x118(r31)
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C8CC0
    li r0, 0x1
    stb r0, 0x154(r31)
    clFlowCup_Init_L_801C8CC0:
    lis r3, g_playerData@ha
    li r29, 0x0
    addi r0, r3, g_playerData@l
    li r27, 0x1
    mr r28, r0
    clFlowCup_Init_L_801C8CD4:
    lwz r4, g_ccClass(r13)
    mr r3, r28
    mr r5, r27
    li r6, 0x7
    bl fn_801D5B8C
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C8CF8
    addi r29, r29, 0x1
    clFlowCup_Init_L_801C8CF8:
    addi r27, r27, 0x1
    cmpwi r27, 0x9
    blt clFlowCup_Init_L_801C8CD4
    li r0, 0x7
    srawi r4, r29, 31
    srwi r3, r0, 31
    subfc r0, r0, r29
    adde r0, r4, r3
    stb r0, 0x155(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne clFlowCup_Init_L_801C8D34
    li r0, 0x1
    stb r0, 0x155(r31)
    stb r0, 0x154(r31)
    clFlowCup_Init_L_801C8D34:
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8D68
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x186
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CE4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8D68:
    stw r27, 0xd8(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8DA0
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x187
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CC8(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8DA0:
    stw r27, 0xe0(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8DD8
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x188
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CEC(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8DD8:
    stw r27, 0xe8(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E10
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x189
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF0(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E10:
    stw r27, 0xf0(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E48
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18a
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CE4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E48:
    stw r27, 0xdc(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E80
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18b
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CC8(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E80:
    stw r27, 0xe4(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8EB8
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18c
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CEC(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8EB8:
    stw r27, 0xec(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8EF0
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18d
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF0(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8EF0:
    stw r27, 0xf4(r31)
    li r0, -0x1
    li r3, 0x30
    stw r0, 0xc4(r31)
    stw r0, 0xc8(r31)
    stw r0, 0xcc(r31)
    stw r0, 0xd0(r31)
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8F3C
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1de
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9C78(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8F3C:
    stw r27, 0x1c(r31)
    li r4, 0x175b
    lwz r3, 0x1c(r31)
    bl fn_801A0310
    stw r3, 0x100(r31)
    li r4, 0x1ea3
    lwz r3, 0x1c(r31)
    bl fn_801A0310
    stw r3, 0x104(r31)
    mr r3, r31
    lwz r4, 0x4(r31)
    bl fn_801C64DC
    lfs f30, lbl_806D9C94(r2)
    addi r28, r30, 0x0
    lfs f31, lbl_806D9C70(r2)
    li r27, 0x0
    li r29, 0x0
    clFlowCup_Init_L_801C8F80:
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C8FA0
    li r4, 0x180
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Init_L_801C8FA0:
    addi r0, r29, 0x124
    li r4, 0x1777
    stwx r26, r31, r0
    lwzx r3, r31, r0
    lha r5, 0x0(r28)
    bl Sprite_SetAnimParam
    lfs f0, 0x4(r28)
    addi r0, r29, 0x124
    lfs f1, 0x8(r28)
    addi r27, r27, 0x1
    fadds f0, f30, f0
    lwzx r3, r31, r0
    cmpwi r27, 0x9
    addi r29, r29, 0x4
    addi r28, r28, 0xc
    stfs f0, 0xc(r3)
    stfs f1, 0x10(r3)
    lwzx r3, r31, r0
    stfs f31, 0x14(r3)
    stfs f31, 0x18(r3)
    blt clFlowCup_Init_L_801C8F80
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9028
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18f
    lfs f1, lbl_806D9CF8(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9CC8(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9028:
    stw r26, 0x148(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9060
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18e
    lfs f1, lbl_806D9CFC(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9060:
    stw r26, 0x14c(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9098
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1c7
    lfs f1, lbl_806D9CDC(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9098:
    stw r26, 0x150(r31)
    lbz r0, 0x118(r31)
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C911C
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C90DC
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x3a
    lfs f1, lbl_806D9C74(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C90DC:
    stw r26, 0xf8(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9114
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1c7
    lfs f1, lbl_806D9CE0(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9114:
    stw r26, 0xfc(r31)
    b clFlowCup_Init_L_801C919C
    clFlowCup_Init_L_801C911C:
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9150
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x38
    lfs f1, lbl_806D9C74(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9150:
    stw r26, 0xf8(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9188
    lfs f3, lbl_806D9C88(r2)
    li r4, 0xc8
    lfs f1, lbl_806D9CE0(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9188:
    stw r26, 0xfc(r31)
    li r4, 0x1ad4
    li r5, 0x1ae3
    lwz r3, 0xfc(r31)
    bl Sprite_SetAnimParam
    clFlowCup_Init_L_801C919C:
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowCup_Init_L_801C91B0
    li r0, 0x0
    b clFlowCup_Init_L_801C91B4
    clFlowCup_Init_L_801C91B0:
    mr r0, r4
    clFlowCup_Init_L_801C91B4:
    cmplwi r0, 0x0
    beq clFlowCup_Init_L_801C91DC
    cmplwi r4, 0x0
    bne clFlowCup_Init_L_801C91C8
    li r4, 0x0
    clFlowCup_Init_L_801C91C8:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowCup_Init_L_801C91DC:
    bl InitBGM
    lfs f1, lbl_806D9CA4(r2)
    bl SetScreenBrightness
    li r3, 0x1
    bl SetupBgSprites
    lwz r0, 0xb0(r31)
    cmplwi r0, 0x0
    bne clFlowCup_Init_L_801C9258
    li r0, 0x0
    li r3, 0x30
    stw r0, 0xb4(r31)
    stw r0, 0xbc(r31)
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9228
    li r4, 0x36
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Init_L_801C9228:
    stw r26, 0xb0(r31)
    li r4, 0x1744
    lwz r3, 0xb0(r31)
    lha r5, 0x78(r30)
    bl Sprite_SetAnimParam
    lwz r3, 0xb0(r31)
    bl fn_801A0550
    lwz r3, 0xb0(r31)
    lfs f1, lbl_806D9C74(r2)
    lfs f0, lbl_806D9C78(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    clFlowCup_Init_L_801C9258:
    li r3, 0x1
    bl InitRumbleController
    mr r3, r31
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lmw r26, 0x8(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

#ifdef __cplusplus
}
#endif



struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0xF];
    int delta;
    int value18;
    int value1C;
};

struct ResCtrl {
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    unsigned char flipX;
    unsigned char flipY;
    char pad46[2];
    int tail[4];
};

struct Sprite {
    char pad0[0xC];
    float x;
    float y;
    float sx;
    float sy;
    float rot;
    float alpha;
};

struct RoundSlot {
    int mode;
    int state;
    int step;
    int count;
    Sprite *spr;
};

struct SprFlag {
    Sprite *spr;
    unsigned char visible;
    unsigned char x5;
    int x8;
};

struct clFlowRound {
    void *vtbl;
    int round;
    int unlocked;
    char padC[0x1C - 0xC];
    int x1C;
    unsigned char x20;
    int x24;
    Sprite *spr28;
    RoundSlot slots[4];
    int x7C;
    int x80;
    int x84;
    Sprite *spr88;
    unsigned char x8C;
    float x90;
    ResCtrl layer94;
    Sprite *sprEC;
    Sprite *sprF0;
    ResCtrl layerF4;
    unsigned char mode;
    float alpha150;
    float alpha154;
    float alpha158;
    Sprite *spr15C;
    Sprite *spr160;
    unsigned char show164;
    unsigned char show165;
    SprFlag *flag168;
};

extern "C" {
struct RoundPos {
    short id0;
    short id1;
    float x;
    float y;
};

RoundPos clFlowRound_data_8049AE70[4] = { { 6481, 6476, 84.0f, 200.0f }, { 6482, 6477, 208.0f, 260.0f }, { 6483, 6478, 323.0f, 200.0f }, { 6484, 6479, 456.0f, 260.0f } };
struct RoundResPair {
    short a;
    short b;
};

static RoundResPair s_roundRes[8][4] = {
    { { 6758, 6624 }, { 6759, 6625 }, { 6758, 6624 }, { 6759, 6625 } },
    { { 6686, 6576 }, { 6687, 6577 }, { 6686, 6576 }, { 6687, 6577 } },
    { { 6741, 6612 }, { 6740, 6613 }, { 6741, 6612 }, { 6740, 6613 } },
    { { 6650, 6552 }, { 6651, 6553 }, { 6650, 6552 }, { 6651, 6553 } },
    { { 6632, 6540 }, { 6633, 6541 }, { 6632, 6540 }, { 6633, 6541 } },
    { { 6704, 6588 }, { 6705, 6589 }, { 6704, 6588 }, { 6705, 6589 } },
    { { 6668, 6564 }, { 6669, 6565 }, { 6668, 6564 }, { 6669, 6565 } },
    { { 6722, 6600 }, { 6723, 6601 }, { 6722, 6600 }, { 6723, 6601 } }
};
static int s_roundB0[4] = { 0, 0, 0, 0 };
static int s_roundAnim[18] = {
    401, 446, 442, 60, 128, 60, 62, 130, 62, 61, 129, 61, 59, 127, 114, 400, 445, 441
};
static short s_roundTitle[10] = { 6511, 6512, 6513, 6514, 6515, 6516, 6517, 6518, 0, 0 };
short clFlowRound_Draw_data_8049AF8C[10] = {
    -1, 1, 3, 4, 5, 6, 7, 0,
    2, 0
};
short clFlowRound_Draw_data_8049AFA0[8] = {
    5869, 5870, 5871, 5872, 5893, 5894, 5895, 5896
};
extern char clFlowRound_data_806CFDF8[];
extern char clFlowRound_data_806CFE00[];
int clFlowRound_Update(clFlowRound *self);
void clFlowRound_Draw(clFlowRound *self);
clFlowRound *clFlowRound_Dtor(clFlowRound *self, short flags);
void *clFlowRound_data_8049AFB0[3] = { clFlowRound_data_806CFDF8, 0, 0 };
static void *clFlowRound_vtbl[5] = {
    clFlowRound_data_806CFE00, 0, (void *)clFlowRound_Dtor, (void *)clFlowRound_Update, (void *)clFlowRound_Draw
};

void *Alloc(unsigned long size);
void DebugPrintf(const char *fmt, ...);
void InitBGM(void);
void InitRumbleController(int);
void InitializeFrameSelection(void *self);
void PreloadResource(int id);
void ResCtrl_Init(ResCtrl *ctrl);
int RoundCupIsCompleted(void *data, int cc, int cup, int mirror);
unsigned char RoundIsUnlocked(void *data, int round);
void SetScreenBrightness(float);
void SetSyncTarget(int);
void SetupBgSprites(int);
void SpriteSystem_EnsureInit(void);
void Sprite_CreateWithParams(void *spr, int id, int flag, float a, float b, float c, float d, float e, float f);
void Sprite_InitWithAnim(void *spr, int id, int a, int b);
void Sprite_SetAnimParam(void *spr, int a, int b);
void fn_801A0550(void *spr);
void fn_801B8540(int);
void fn_801B85DC(int, int, int);
void fn_801C9288(clFlowRound *self, int i, int flag);
extern int g_ccClass;
extern int g_cupId;
extern InputState *g_pInputState;
extern int g_roundIndex;
extern const float lbl_806D9D10;
extern const float lbl_806D9D14;
extern const float lbl_806D9D28;
extern const float lbl_806D9D38;
extern const float lbl_806D9D3C;
extern const float lbl_806D9D48;
extern const float lbl_806D9D68;
extern const float lbl_806D9D6C;
extern const float lbl_806D9D70;
extern const float lbl_806D9D74;
extern const float lbl_806D9D78;
extern const float lbl_806D9D80;
extern const float lbl_806D9D98;
extern const float lbl_806D9D9C;
extern const float lbl_806D9DA0;
extern const float lbl_806D9DA4;
extern const float lbl_806D9DA8;
extern const float lbl_806D9DAC;
extern char g_playerData[];
extern short clFlowRound_Init_rodata_8039B308[][3];
extern char lbl_8039B3B4[];
}


struct RoundArrow {
    float lx;
    float ly;
    float lrot;
    float rx;
    float ry;
    float rrot;
};

struct CourseParams {
    int a;
    int b;
    int c;
};

extern "C" {
void RumbleUpdate(void);
void *GetInputManager(void);
void InputMgr_GetPlayer(void *mgr, int idx);
unsigned char IsItemSelectAllowed(void);
void SetCourseParams(int cup, int a, int b, int c);
void SetRumbleMode(int a, int b, int c);
unsigned char Sprite_AdvanceAnim(void *spr, float dt);
void Sprite_Destroy(void *spr, int flag);
void Sprite_SetupAnim(void *spr, int id, int a, int b);
void fn_801699D8(int a, int b);
void fn_8019FF6C(void *spr, int flag);
void fn_801B7C64(void);
void fn_801B7CAC(void);
void fn_801B8434(void);
void fn_801B87D8(void);
CourseParams *fn_801BA060(int round);
extern signed char lbl_806D184C;
extern signed char lbl_806D184D;
extern const double lbl_806D9D08;
extern const float lbl_806D9D18;
extern const float lbl_806D9D1C;
extern const float lbl_806D9D20;
extern const float lbl_806D9D24;
extern const float lbl_806D9D44;
extern const float lbl_806D9D7C;
extern const float lbl_806D9D84;
extern const float lbl_806D9D88;
extern const float lbl_806D9D8C;
extern const float lbl_806D9D90;
extern const float lbl_806D9D94;
extern RoundArrow clFlowRound_Update_rodata_8039B338[];
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

union RoundColor {
    unsigned int rgba;
    struct {
        unsigned int rgb : 24;
        unsigned int a : 8;
    } c;
};

static inline void SetPos(Sprite *spr, float x, float y) {
    spr->x = x;
    spr->y = y;
}

static inline void SetScale(Sprite *spr, float x, float y) {
    spr->sx = x;
    spr->sy = y;
}

static inline void PlaceArrows(clFlowRound *self) {
    self->show164 = 0;
    if (self->spr15C != 0) {
        { float x = clFlowRound_Update_rodata_8039B338[self->round].lx; float y = clFlowRound_Update_rodata_8039B338[self->round].ly; SetPos(self->spr15C, x, y); }
        self->spr15C->rot = lbl_806D9D08 * clFlowRound_Update_rodata_8039B338[self->round].lrot;
        if (self->round != 0) {
            self->show164 = 1;
        }
    }
    self->show165 = 0;
    if (self->spr160 != 0) {
        { float x = clFlowRound_Update_rodata_8039B338[self->round].rx; float y = clFlowRound_Update_rodata_8039B338[self->round].ry; SetPos(self->spr160, x, y); }
        self->spr160->rot = lbl_806D9D08 * clFlowRound_Update_rodata_8039B338[self->round].rrot;
        if (self->round != 3 && self->round < self->unlocked - 1) {
            self->show165 = 1;
        }
    }
}

static inline void SetTitle(clFlowRound *self, int idx) {
    if (self->spr88 != 0 && self->x80 == 1) {
        self->x84 = idx;
        Sprite_SetupAnim(self->spr88, 0x1BF, 0, 0);
        Sprite_SetAnimParam(self->spr88, 0x1970, s_roundTitle[clFlowRound_Draw_data_8049AF8C[g_cupId]]);
        fn_801A0550(self->spr88);
        fn_8019FF6C(self->spr88, 1);
    }
}

static inline void ShowFlag(SprFlag *flag) {
    if (flag->visible != 1 || flag->x5 != 0) {
        flag->visible = 1;
        flag->x5 = 0;
        flag->x8 = 0;
    }
}

static inline void HideFlag(SprFlag *flag) {
    if (flag->visible != 0 && flag->x5 != 1) {
        flag->x5 = 1;
        flag->x8 = 0;
    }
}

extern "C" int clFlowRound_Update(clFlowRound *self) {
    int i;
    int j;
    int prev;
    int round;
    float dy;
    float t;
    float ndy;
    RoundSlot *slot;
    RoundPos *pos;
    SprFlag *flag;

    RumbleUpdate();
    if (self->x20 != 0) {
        self->x1C++;
        self->x20 = 0;
    }
    self->x24++;
    switch (self->x1C) {
    case 0:
        if (self->x24 <= 12) {
            t = (lbl_806D9D1C * (float)self->x24) / lbl_806D9D20;
            self->layer94.Show(lbl_806D9D68 - t, lbl_806D9D6C, lbl_806D9D28);
            if (self->sprF0 != 0) {
                self->sprF0->x = lbl_806D9D70 + t;
            }
            self->layerF4.Show(lbl_806D9D74 + t, lbl_806D9D78, lbl_806D9D28);
        }
        if (self->x24 >= 3 && self->x24 <= 8) {
            self->alpha150 = (float)(self->x24 - 3) / lbl_806D9D7C;
        }
        if (self->x24 >= 20 && self->x24 <= 25) {
            t = ((float)self->x24 - lbl_806D9D80) / lbl_806D9D7C;
            if (self->spr28 != 0) {
                self->spr28->alpha = t;
            }
        }
        if (self->x24 >= 25) {
            t = (float)(self->x24 - 25) / lbl_806D9D7C;
            if (self->sprEC != 0) {
                self->sprEC->alpha = t;
            }
            self->alpha154 = t;
            self->alpha158 = t;
        }
        if (self->x24 == 30) {
            fn_801C9288(self, self->round, 4);
            SetScreenBrightness(self->x90);
            lbl_806D184C = 1;
            lbl_806D184D = 0;
            PlaceArrows(self);
            self->x8C = 1;
            self->x20 = 1;
            fn_801699D8(0, 1);
            if (self->mode == 1 && self->round <= 1) {
                flag = self->flag168;
                if (flag != 0) {
                    ShowFlag(flag);
                }
            }
        }
        break;
    case 1:
        prev = self->round;
        if (input_state() != 0) {
            { InputState *st = input_state(); self->round += st->delta; }
            if (self->round > self->unlocked - 1) {
                self->round = self->unlocked - 1;
            }
            if (self->round < 0) {
                self->round = 0;
            }
        }
        if (prev != self->round) {
            fn_801C9288(self, prev, 2);
            fn_801C9288(self, self->round, 4);
            PlaceArrows(self);
            SetTitle(self, self->round);
            fn_801B7CAC();
            flag = self->flag168;
            if (flag != 0) {
                if (self->mode == 1 && self->round <= 1) {
                    if (flag->visible == 0) {
                        ShowFlag(flag);
                    }
                } else {
                    HideFlag(flag);
                }
            }
        }
        switch (self->x7C) {
        case -1:
            self->x90 -= lbl_806D9D44;
            InputMgr_GetPlayer(GetInputManager(), 0);
            if (input_state()->value18 == 1 || self->x90 < lbl_806D9D38) {
                if (input_state() != 0) {
                    InputState *state = input_state();

                    state->active = 0;
                    state->value18 = 0;
                    state->value1C = 0;
                }
                SetRumbleMode(0, 1, 1);
                {
                    int base = 0;
                    int r = self->round;
                    CourseParams *p;

                    if (self->mode == 1) {
                        base = 4;
                    }
                    round = r + base;
                    p = fn_801BA060(round);
                    g_roundIndex = round;
                    SetCourseParams(g_cupId, p->a, p->b, p->c);
                }
                if (IsItemSelectAllowed()) {
                    self->x7C = 0x21;
                } else {
                    self->x7C = 0x25;
                }
                self->x90 = lbl_806D9D48;
                fn_801B7C64();
                self->show164 = 0;
                self->show165 = 0;
            }
            SetScreenBrightness(self->x90);
            break;
        }
        if (self->x7C != -1) {
            for (i = 0; i < 4; i++) {
                if (i == self->round) {
                    fn_801C9288(self, i, 5);
                } else {
                    fn_801C9288(self, i, 3);
                }
            }
            Sprite_Destroy(self->spr28, 1);
            fn_801B87D8();
            lbl_806D184C = -1;
            self->spr28 = 0;
            self->x24 = 0;
            self->x8C = 0;
            self->x20 = 1;
        }
        break;
    case 2:
        if (self->x24 <= 5) {
            t = lbl_806D9D28 - (float)self->x24 / lbl_806D9D7C;
            if (self->sprEC != 0) {
                self->sprEC->alpha = t;
            }
            if (self->spr28 != 0) {
                self->spr28->alpha = t;
            }
            {
                unsigned int c = 0xFFFFFF00;

                c = __rlwimi(c, (int)(lbl_806D9D84 * t), 0, 24, 31);
                self->layer94.SetColor(c);
            }
        }
        if (self->x24 >= 40) {
            t = lbl_806D9D28 - (float)(self->x24 - 40) / lbl_806D9D7C;
            {
                unsigned int c = 0xFFFFFF00;

                c = __rlwimi(c, (int)(lbl_806D9D84 * t), 0, 24, 31);
                self->layerF4.SetColor(c);
            }
        }
        if (self->x24 == 45) {
            Sprite_SetupAnim(self->sprF0, 0xC7, 1, 0);
            Sprite_SetAnimParam(self->sprF0, 0x1AD4, 0x1AE4);
            fn_801C9288(self, self->round, 6);
            fn_801B8434();
            if (self->spr88 != 0 && self->x80 == 1) {
                self->x80 = 2;
                Sprite_SetupAnim(self->spr88, 0x83, 0, 0);
                Sprite_SetAnimParam(self->spr88, 0x1970, s_roundTitle[clFlowRound_Draw_data_8049AF8C[g_cupId]]);
                fn_801A0550(self->spr88);
            }
            self->x24 = 0;
            self->x20 = 1;
            flag = self->flag168;
            if (flag != 0) {
                HideFlag(flag);
            }
            fn_801699D8(0, 0);
        }
        break;
    case 3:
        if (self->x24 <= 5) {
            self->alpha154 = lbl_806D9D28 - (float)self->x24 / lbl_806D9D7C;
        }
        if (self->x24 <= 6) {
            self->alpha150 = lbl_806D9D28 - (float)self->x24 / lbl_806D9D88;
        }
        if (self->x24 <= 7) {
            self->alpha158 = lbl_806D9D28 - (float)self->x24 / lbl_806D9D8C;
        }
        if (self->x24 == 15) {
            self->sprF0->x = lbl_806D9D90;
        }
        if (self->x24 == 45) {
            return self->x7C;
        }
        break;
    }
    flag = self->flag168;
    if (flag != 0 && flag->visible != 0) {
        if (flag->x8 <= 8) {
            if (flag->x5 == 0) {
                t = (float)flag->x8 * lbl_806D9D94;
            } else {
                t = lbl_806D9D28 - (float)flag->x8 * lbl_806D9D94;
            }
            flag->spr->alpha = t;
            if (flag->x8++ == 8 && flag->x5 != 0) {
                flag->visible = 0;
                flag->x5 = 0;
            }
        }
        Sprite_AdvanceAnim(flag->spr, lbl_806D9D18);
    }
    if (self->spr15C != 0) {
        Sprite_AdvanceAnim(self->spr15C, lbl_806D9D18);
    }
    if (self->spr160 != 0) {
        Sprite_AdvanceAnim(self->spr160, lbl_806D9D18);
    }
    if (self->sprF0 != 0) {
        Sprite_AdvanceAnim(self->sprF0, lbl_806D9D18);
    }
    if (self->sprEC != 0) {
        Sprite_AdvanceAnim(self->sprEC, lbl_806D9D18);
    }
    if (self->spr28 != 0) {
        Sprite_AdvanceAnim(self->spr28, lbl_806D9D18);
    }
    ndy = -lbl_806D9D24;
    for (j = 0; j < 4; j++) {
        if (self->slots[j].spr != 0 && Sprite_AdvanceAnim(self->slots[j].spr, lbl_806D9D18) != 1) {
            switch (self->slots[j].mode) {
            case 1:
                if (self->slots[j].step == 0) {
                    self->slots[j].count++;
                    self->slots[j].spr->x = (lbl_806D9D1C + clFlowRound_data_8049AE70[j].x) - (lbl_806D9D1C * (float)self->slots[j].count) / lbl_806D9D20;
                    if (self->slots[j].count >= 12) {
                        self->slots[j].step++;
                        fn_8019FF6C(self->slots[j].spr, 1);
                    }
                }
                break;
            case 5: {
                int anim;
                RoundResPair *res;

                dy = lbl_806D9D24;
                anim = s_roundAnim[self->slots[j].state];
                res = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][j];
                if (j == 2 || j == 4) {
                    dy = ndy;
                }
                if (self->slots[j].spr == 0) {
                    Sprite *spr = (Sprite *)Alloc(0x30);
                    if (spr != 0) {
                        Sprite_InitWithAnim(spr, anim, 0, 0);
                    }
                    self->slots[j].spr = spr;
                } else {
                    Sprite_SetupAnim(self->slots[j].spr, anim, 0, 0);
                }
                switch (self->slots[j].state) {
                case 0:
                    Sprite_SetAnimParam(self->slots[j].spr, 0x1951, clFlowRound_data_8049AE70[j].id0);
                    Sprite_SetAnimParam(self->slots[j].spr, 0x19B0, res->b);
                    break;
                case 1:
                    Sprite_SetAnimParam(self->slots[j].spr, 0x194C, clFlowRound_data_8049AE70[j].id1);
                    Sprite_SetAnimParam(self->slots[j].spr, 0x19B0, res->b);
                    break;
                case 2:
                    Sprite_SetAnimParam(self->slots[j].spr, 0x194C, clFlowRound_data_8049AE70[j].id1);
                    Sprite_SetAnimParam(self->slots[j].spr, 0x19B0, res->b);
                    break;
                }
                Sprite_SetAnimParam(self->slots[j].spr, 0x1A1E, res->a);
                fn_801A0550(self->slots[j].spr);
                SetPos(self->slots[j].spr, clFlowRound_data_8049AE70[j].x, clFlowRound_data_8049AE70[j].y + dy);
                SetScale(self->slots[j].spr, lbl_806D9D28, lbl_806D9D28);
                fn_8019FF6C(self->slots[j].spr, 1);
                break;
            }
            case 3:
            case 6:
                Sprite_Destroy(self->slots[j].spr, 1);
                self->slots[j].mode = 0;
                self->slots[j].spr = 0;
                break;
            }
        }
    }
    if (self->spr88 != 0 && Sprite_AdvanceAnim(self->spr88, lbl_806D9D18) == 0) {
        if (self->x80 == 0) {
            self->x80++;
            SetTitle(self, self->x84);
        }
        if (self->x80 == 2) {
            Sprite_Destroy(self->spr88, 1);
            self->spr88 = 0;
            self->x80++;
        }
    }
    return -1;
}

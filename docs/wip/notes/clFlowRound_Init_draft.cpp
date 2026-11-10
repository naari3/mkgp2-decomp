
struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0x13];
    int value18;
    int value1C;
};

struct ResCtrl {
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
};

struct RoundSlot {
    Sprite *spr;
    int x4;
    int state;
    int xC;
    int x10;
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
    RoundSlot slots[4];
    Sprite *spr78;
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
static short s_roundRes[8][8] = {
        6758, 6624, 6759, 6625, 6758, 6624, 6759, 6625,
        6686, 6576, 6687, 6577, 6686, 6576, 6687, 6577,
        6741, 6612, 6740, 6613, 6741, 6612, 6740, 6613,
        6650, 6552, 6651, 6553, 6650, 6552, 6651, 6553,
        6632, 6540, 6633, 6541, 6632, 6540, 6633, 6541,
        6704, 6588, 6705, 6589, 6704, 6588, 6705, 6589,
        6668, 6564, 6669, 6565, 6668, 6564, 6669, 6565,
        6722, 6600, 6723, 6601, 6722, 6600, 6723, 6601
};
static int s_roundB0[22] = {
        0, 0, 0, 0, 401, 446, 442, 60,
        128, 60, 62, 130, 62, 61, 129, 61,
        59, 127, 114, 400, 445, 441
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
void clFlowRound_Update(void);
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
unsigned char RoundCupIsCompleted(void *data, int cc, int cup, int mirror);
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

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

extern "C" clFlowRound *clFlowRound_Init(clFlowRound *self) {
    short cup;
    int i;
    int base;
    int first;
    int level;
    Sprite *spr;

    InitializeFrameSelection(self);
    self->vtbl = clFlowRound_vtbl;
    ResCtrl_Init(&self->layer94);
    ResCtrl_Init(&self->layerF4);
    SpriteSystem_EnsureInit();
    cup = clFlowRound_Draw_data_8049AF8C[g_cupId];
    SetSyncTarget(0x1B);
    PreloadResource(clFlowRound_Draw_data_8049AFA0[cup]);
    PreloadResource(clFlowRound_Draw_data_8049AFA0[cup] + 12);
    PreloadResource(s_roundRes[cup][1]);
    PreloadResource(s_roundRes[cup][1] + 6);
    PreloadResource(s_roundRes[cup][0]);
    PreloadResource(s_roundRes[cup][0] + 9);
    PreloadResource(s_roundRes[cup][3]);
    PreloadResource(s_roundRes[cup][3] + 6);
    PreloadResource(s_roundRes[cup][2]);
    PreloadResource(s_roundRes[cup][2] + 9);
    PreloadResource(clFlowRound_Init_rodata_8039B308[cup][0]);
    PreloadResource(clFlowRound_Init_rodata_8039B308[cup][0] + 9);
    PreloadResource(0x194C);
    PreloadResource(0x195E);
    PreloadResource(0x196F);
    PreloadResource(0x197C);
    PreloadResource(0x1DEC);
    PreloadResource(0x195B);
    PreloadResource(0x196D);
    PreloadResource(0x1863);
    PreloadResource(0x18BA);
    PreloadResource(0x1843);
    PreloadResource(0x189A);
    PreloadResource(0x196E);
    PreloadResource(0x197B);
    first = 1;
    self->mode = g_roundIndex >= 4;
    self->unlocked = 0;
    base = self->mode == 1 ? 4 : 0;
    for (i = 0; i < 4; i++) {
        self->slots[i].x4 = 0;
        self->slots[i].xC = 0;
        self->slots[i].x10 = 0;
        self->slots[i + 1].spr = 0;
        if (RoundIsUnlocked(g_playerData, base + i)) {
            self->slots[i].state = 0;
            self->unlocked++;
        } else if ((unsigned char)first) {
            self->slots[i].state = 1;
            first = 0;
            self->unlocked++;
        } else {
            self->slots[i].state = 2;
        }
        fn_801C9288(self, i, 1);
    }
    self->round = 0;
    self->x7C = -1;
    self->x1C = 0;
    self->x20 = 0;
    self->x24 = 0;
    self->slots[0].spr = 0;
    self->sprEC = 0;
    self->flag168 = 0;
    self->spr88 = 0;
    self->x80 = 0;
    self->x8C = 0;
    self->x90 = lbl_806D9D80;
    self->alpha150 = lbl_806D9D38;
    self->alpha154 = lbl_806D9D38;
    self->alpha158 = lbl_806D9D38;
    spr = (Sprite *)Alloc(0x30);
    if (spr != 0) {
        Sprite_CreateWithParams(spr, 0x1C0, 1, lbl_806D9D98, lbl_806D9D9C, lbl_806D9D28, lbl_806D9D28, lbl_806D9D38, lbl_806D9D38);
    }
    self->slots[0].spr = spr;
    for (i = 3; i >= 0; i--) {
        if (RoundIsUnlocked(g_playerData, base + i) == 1) {
            self->round = i == 3 ? 3 : i + 1;
            break;
        }
    }
    level = 0;
    if (RoundIsUnlocked(g_playerData, self->mode == 1 ? 7 : 3) == 1) {
        level = 1;
    }
    if (RoundCupIsCompleted(g_playerData, g_ccClass, g_cupId, self->mode == 1 ? 1 : 0)) {
        level = 2;
    }
    self->layer94.resId = clFlowRound_Init_rodata_8039B308[g_cupId - 1][level];
    self->layer94.flag = 1;
    self->layer94.x = lbl_806D9D68;
    self->layer94.y = lbl_806D9D6C;
    self->layer94.z = lbl_806D9D28;
    self->layer94.colors[0] = -1;
    self->layer94.colors[1] = -1;
    self->layer94.colors[2] = -1;
    self->layer94.colors[3] = -1;
    if (RoundIsUnlocked(g_playerData, self->mode == 1 ? 7 : 3) == 1) {
        spr = (Sprite *)Alloc(0x30);
        if (spr != 0) {
            Sprite_CreateWithParams(spr, 0x85, 1, lbl_806D9DA0, lbl_806D9DA4, lbl_806D9D28, lbl_806D9D28, lbl_806D9D38, lbl_806D9D38);
        }
        self->sprEC = spr;
    }
    spr = (Sprite *)Alloc(0x30);
    if (spr != 0) {
        Sprite_CreateWithParams(spr, 0x1DD, 0, lbl_806D9DA8, lbl_806D9D78, lbl_806D9D28, lbl_806D9D28, lbl_806D9D38, lbl_806D9D28);
    }
    self->sprF0 = spr;
    Sprite_SetAnimParam(self->sprF0, 0x1AD4, 0x1AE4);
    if (self->mode == 1) {
        PreloadResource(0x15F4);
        PreloadResource(0x15FE);
        spr = self->sprF0;
        spr->x = lbl_806D9D70;
        spr->y = lbl_806D9D78;
        self->layerF4.resId = 0x15F4;
        self->layerF4.flag = 1;
        self->layerF4.x = lbl_806D9D74;
        self->layerF4.y = lbl_806D9D78;
        self->layerF4.z = lbl_806D9D28;
    } else {
        self->layerF4.resId = 0x1ECD;
    }
    spr = (Sprite *)Alloc(0x30);
    if (spr != 0) {
        Sprite_CreateWithParams(spr, 0x9C, 1, lbl_806D9D38, lbl_806D9D38, lbl_806D9D3C, lbl_806D9D3C, lbl_806D9D38, lbl_806D9D28);
    }
    self->spr15C = spr;
    spr = (Sprite *)Alloc(0x30);
    if (spr != 0) {
        Sprite_CreateWithParams(spr, 0x9C, 1, lbl_806D9D38, lbl_806D9D38, lbl_806D9D3C, lbl_806D9D3C, lbl_806D9D38, lbl_806D9D28);
    }
    self->spr160 = spr;
    self->show164 = 0;
    self->show165 = 0;
    if (self->mode == 1) {
        SprFlag *flag = (SprFlag *)Alloc(0xC);
        if (flag != 0) {
            flag->visible = 0;
            flag->x5 = 0;
            flag->x8 = 0;
            spr = (Sprite *)Alloc(0x30);
            if (spr != 0) {
                Sprite_CreateWithParams(spr, 0x9E, 1, lbl_806D9DAC, lbl_806D9DAC, lbl_806D9D28, lbl_806D9D28, lbl_806D9D38, lbl_806D9D38);
            }
            flag->spr = spr;
        }
        self->flag168 = flag;
    }
    if (input_state() != 0) {
        InputState *state = input_state();

        state->active = 1;
        state->value18 = 0;
        state->value1C = 0;
    }
    SetScreenBrightness(lbl_806D9D48);
    fn_801B85DC(0x1B, self->mode, 0);
    fn_801B8540(0);
    InitBGM();
    SetupBgSprites(1);
    if (self->spr88 == 0) {
        self->x80 = 0;
        self->x84 = 0;
        spr = (Sprite *)Alloc(0x30);
        if (spr != 0) {
            Sprite_InitWithAnim(spr, 0x84, 0, 0);
        }
        self->spr88 = spr;
        Sprite_SetAnimParam(self->spr88, 0x1970, s_roundTitle[clFlowRound_Draw_data_8049AF8C[g_cupId]]);
        fn_801A0550(self->spr88);
        spr = self->spr88;
        spr->x = lbl_806D9D10;
        spr->y = lbl_806D9D14;
    }
    DebugPrintf(lbl_8039B3B4);
    InitRumbleController(1);
    return self;
}

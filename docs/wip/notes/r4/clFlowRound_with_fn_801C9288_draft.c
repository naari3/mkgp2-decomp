/* clFlowRound: the round (race 1-4) select flow of a cup.
 * A real polymorphic class with RTTI: the ctor stores the vtable between the
 * clFlowProcess base ctor and the ResCtrl member ctors, and -inline deferred
 * makes CW pool the compiler-generated vtable with the TU's .data.
 * Draw and Update stay C/asm functions that the vtable reaches by rename.
 */

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
    ResCtrl();
    ~ResCtrl() {}
};

struct Sprite {
    char pad0[0xC];
    float x;
    float y;
    float sx;
    float sy;
    char pad1C[0x30 - 0x1C];
    void Position(float px, float py) { x = px; y = py; }
    void Scale(float s) { sx = s; sy = s; }
    Sprite(int id, int flag, float a, float b, float c, float d, float e, float f);
    Sprite(int id, int a, int b);
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
    inline SprFlag();
};

struct clFlowProcess {
    clFlowProcess();
    virtual ~clFlowProcess();
};

struct clFlowRound : clFlowProcess {
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
    clFlowRound();
    virtual ~clFlowRound();
    virtual int Update();
    virtual void Draw();
};

/* Field view used by the C Draw/Update code. */
struct RoundViewSlot {
    void *spr;
    int x4;
    int x8;
    int xC;
    void *sub;
};

struct RoundView {
    void *vtbl;
    int mirror;
    char pad8[0x28 - 0x8];
    RoundViewSlot slots[5];
    char pad8C[0x94 - 0x8C];
    char layer94[0xEC - 0x94];
    void *sprEC;
    void *sprF0;
    char layerF4[0x150 - 0xF4];
    float alpha150;
    float alpha154;
    float alpha158;
    void *spr15C;
    void *spr160;
    unsigned char show164;
    unsigned char show165;
    char pad166[2];
    SprFlag *flag168;
};

void *operator new(unsigned long size);
void operator delete(void *p);

extern "C" {
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
struct RoundTileOwner;
int fn_801C9288(RoundTileOwner *self, int index, int state);
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
short GetCourseShortIdByCupAndMirror(int cup, int mirror);
void fn_8011FAFC(void *obj, int layer);
void fn_801A0004(void *spr);
void fn_801A0DF0(void);
void fn_801A0FD4(float r, float g, float b, float a);
void fn_801A10DC(float sx, float sy);
void fn_801A1128(float x, float y);
void fn_801A1174(int id, int layer, int a, int b, int c);
extern const float lbl_806D9D4C;
extern const float lbl_806D9D50;
extern const float lbl_806D9D54;
extern const float lbl_806D9D58;
extern const float lbl_806D9D5C;
extern const float lbl_806D9D60;
extern const float lbl_806D9D64;
void MemoryManager_TimedFree(void *);
void Sprite_Destroy(void *, int);
void fn_80120A08(int);
void fn_80169C44(void);
void fn_801A1678(void);
void Alloc();
void GetInputManager();
void InputMgr_GetPlayer();
void IsItemSelectAllowed();
void RumbleUpdate();
void SetCourseParams();
void SetRumbleMode();
void Sprite_AdvanceAnim();
void Sprite_SetupAnim(void *spr, int id, int a, int b);
void fn_801699D8();
void fn_8019FF6C(void *spr, int flag);
void fn_801B7C64();
void fn_801B7CAC();
void fn_801B8434();
void fn_801B87D8();
void fn_801BA060();
void targets();
void clFlowRound_Update(void);
extern unsigned int lbl_806D184C;
extern unsigned int lbl_806D184D;
extern unsigned int lbl_806D9D08;
extern unsigned int lbl_806D9D18;
extern unsigned int lbl_806D9D1C;
extern unsigned int lbl_806D9D20;
extern unsigned int lbl_806D9D24;
extern unsigned int lbl_806D9D30;
extern unsigned int lbl_806D9D44;
extern unsigned int lbl_806D9D7C;
extern unsigned int lbl_806D9D84;
extern unsigned int lbl_806D9D88;
extern unsigned int lbl_806D9D8C;
extern unsigned int lbl_806D9D90;
extern unsigned int lbl_806D9D94;
void clFlowRound_Draw(RoundView *self);

/* === .data 0x8049AE70..0x8049AFD0 === */
struct RoundPos {
    short id0;
    short id1;
    float x;
    float y;
};

RoundPos clFlowRound_data_8049AE70[4] = { { 6481, 6476, 84.0f, 200.0f }, { 6482, 6477, 208.0f, 260.0f }, { 6483, 6478, 323.0f, 200.0f }, { 6484, 6479, 456.0f, 260.0f } };
/* Per cup: the four round tiles' (id, alternate) resources; row 8 is unused. */
struct RoundTileParams { short id, alternate; };
static RoundTileParams s_roundRes[9][4] = {
    { { 6758, 6624 }, { 6759, 6625 }, { 6758, 6624 }, { 6759, 6625 } },
    { { 6686, 6576 }, { 6687, 6577 }, { 6686, 6576 }, { 6687, 6577 } },
    { { 6741, 6612 }, { 6740, 6613 }, { 6741, 6612 }, { 6740, 6613 } },
    { { 6650, 6552 }, { 6651, 6553 }, { 6650, 6552 }, { 6651, 6553 } },
    { { 6632, 6540 }, { 6633, 6541 }, { 6632, 6540 }, { 6633, 6541 } },
    { { 6704, 6588 }, { 6705, 6589 }, { 6704, 6588 }, { 6705, 6589 } },
    { { 6668, 6564 }, { 6669, 6565 }, { 6668, 6564 }, { 6669, 6565 } },
    { { 6722, 6600 }, { 6723, 6601 }, { 6722, 6600 }, { 6723, 6601 } },
    { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } }
};
/* Tile animation per state (rows) and tile variant (columns). */
static int s_roundAnim[6][3] = {
    { 401, 446, 442 }, { 60, 128, 60 }, { 62, 130, 62 },
    { 61, 129, 61 }, { 59, 127, 114 }, { 400, 445, 441 }
};
static short s_roundTitle[10] = { 6511, 6512, 6513, 6514, 6515, 6516, 6517, 6518, 0, 0 };
short clFlowRound_Draw_data_8049AF8C[10] = {
    -1, 1, 3, 4, 5, 6, 7, 0,
    2, 0
};
short clFlowRound_Draw_data_8049AFA0[8] = {
    5869, 5870, 5871, 5872, 5893, 5894, 5895, 5896
};

/* === .sdata 0x806CFDF0 (RTTI objects follow) === */
short clFlowRound_data_806CFDF0[4] = { 0x1977, 0x1978, 0x1979, 0x197A };

/* === .rodata 0x8039B308..0x8039B3C8 (class names and the debug string follow) === */
extern const short clFlowRound_Init_rodata_8039B308[8][3];
extern const float clFlowRound_Update_rodata_8039B338[24];
const short clFlowRound_Init_rodata_8039B308[8][3] = {
    { 0x1A24, 0x1A25, 0x1A26 }, { 0x1A00, 0x1A01, 0x1A02 }, { 0x19EE, 0x19EF, 0x19F0 },
    { 0x1A36, 0x1A37, 0x1A38 }, { 0x1A12, 0x1A13, 0x1A14 }, { 0x1A48, 0x1A49, 0x1A4A },
    { 0x1A6C, 0x1A6D, 0x1A6E }, { 0x1A5A, 0x1A5B, 0x1A5C },
};
const float clFlowRound_Update_rodata_8039B338[24] = {
    0.0f, 0.0f, 0.0f, 144.0f, 204.0f, -40.0f, 124.0f, 195.0f, 150.0f, 260.0f, 195.0f, 40.0f,
    254.0f, 204.0f, -150.0f, 388.0f, 204.0f, -40.0f, 384.0f, 195.0f, 150.0f, 0.0f, 0.0f, 0.0f,
};
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

/* Draw is generated in place; with -inline deferred the rest of the TU is
 * generated at the end in reverse order (Init after Dtor in .text). */
#pragma defer_codegen off
/* fn_801C9288 (0x801C9288): sets one round tile to a new state and
 * (re)builds its sprite. It indexes this TU's .data tables through the
 * section anchor, so it lives here, generated in place ahead of Draw. */
struct RoundTileSlot {
    int state, variant, timer, frame;
    Sprite *sprite;
};
struct RoundTileOwner { char opaque[0x2C]; RoundTileSlot slots[5]; };
extern "C" {
extern const float lbl_806D9D40;
#pragma push
#pragma opt_common_subs off
int fn_801C9288(RoundTileOwner *self, int index, int state) {
    RoundTileSlot *slot = &self->slots[index];
    if (state == 1) { if (slot->state != 0) return 0; }
    else { if (slot->state == 0) return 0; }
    slot->state = state;
    slot->timer = 0;
    slot->frame = 0;
    switch (state) {
    case 1: {
        int anim = s_roundAnim[0][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    case 2: {
        int anim = s_roundAnim[5][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 3: {
        int anim = s_roundAnim[4][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    case 4: {
        int anim = s_roundAnim[3][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(1.0f);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 5: {
        int anim = s_roundAnim[2][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(1.0f);
        break;
    }
    case 6: {
        int anim = s_roundAnim[1][slot->variant];
        RoundTileParams *param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        RoundPos *pos = &clFlowRound_data_8049AE70[index];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    }
    return 1;
}
#pragma pop
}
#pragma exceptions off
extern "C" {
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowRound_Draw[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Draw = {
    (void *)&clFlowRound_Draw, 0x00000284, (void *)extab_clFlowRound_Draw
};

static inline void DrawSprite(void *spr) {
    if (spr != 0) {
        fn_801A0004(spr);
    }
}

void clFlowRound_Draw(RoundView *self) {
    short cup;
    int i;

    if (self->sprF0 != 0) {
        fn_801A0004(self->sprF0);
    }
    if (self->slots[0].spr != 0) {
        fn_801A0004(self->slots[0].spr);
    }
    if (self->slots[4].sub != 0) {
        fn_801A0004(self->slots[4].sub);
    }
    if (self->sprEC != 0) {
        fn_801A0004(self->sprEC);
    }
    fn_8011FAFC(self->layer94, 5);
    fn_8011FAFC(self->layerF4, 5);

    cup = clFlowRound_Draw_data_8049AF8C[g_cupId];
    fn_801A1174(clFlowRound_data_806CFDF0[self->mirror], 5, 0, 0, 0);
    fn_801A1128(lbl_806D9D4C, lbl_806D9D50);
    fn_801A0FD4(lbl_806D9D28, lbl_806D9D28, lbl_806D9D28, self->alpha158);
    fn_801A0DF0();

    fn_801A1174(clFlowRound_Draw_data_8049AFA0[cup], 5, 0, 0, 0);
    fn_801A1128(lbl_806D9D54, lbl_806D9D58);
    fn_801A0FD4(lbl_806D9D28, lbl_806D9D28, lbl_806D9D28, self->alpha150);
    fn_801A0DF0();

    fn_801A1174(GetCourseShortIdByCupAndMirror(g_cupId, self->mirror), 5, 0, 0, 0);
    fn_801A1128(lbl_806D9D5C, lbl_806D9D60);
    fn_801A10DC(lbl_806D9D64, lbl_806D9D64);
    fn_801A0FD4(lbl_806D9D28, lbl_806D9D28, lbl_806D9D28, self->alpha154);
    fn_801A0DF0();

    if (self->mirror % 2 == 0 && self->slots[self->mirror + 1].spr != 0) {
        DrawSprite(self->slots[self->mirror + 1].spr);
    }
    for (i = 0; i < 4; i++) {
        if (i != self->mirror && self->slots[i + 1].spr != 0) {
            DrawSprite(self->slots[i + 1].spr);
        }
    }
    if (self->mirror % 2 == 1 && self->slots[self->mirror + 1].spr != 0) {
        DrawSprite(self->slots[self->mirror + 1].spr);
    }
    if (self->flag168 != 0 && self->flag168->visible != 0) {
        fn_801A0004(self->flag168->spr);
    }
    if (self->spr15C != 0 && self->show164 == 1) {
        fn_801A0004(self->spr15C);
    }
    if (self->spr160 != 0 && self->show165 == 1) {
        fn_801A0004(self->spr160);
    }
}


/* === extracted from auto_clFlowRound_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

/* --- function index (1 fns, .text 0x801C9EAC..0x801CADBC) ---
 * [  0] 0x801C9EAC size:0xF10   global clFlowRound_Update
 */

/* --- forward decls --- */
asm void clFlowRound_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_clFlowRound_Update = { 0x488A0000, 0x00000CF4, 0x00000010, 0x00000000, 0x8A800017, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Update = {
    (void *)&clFlowRound_Update, 0x00000F10, (void *)&extab_clFlowRound_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowRound_Update(void) { /* 0x801C9EAC size:0xF10 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stmw r23, 0x1c(r1)
    lis r4, clFlowRound_data_8049AE70@ha
    mr r31, r3
    addi r30, r4, clFlowRound_data_8049AE70@l
    bl RumbleUpdate
    lbz r0, 0x20(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801C9EFC
    lwz r3, 0x1c(r31)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x1c(r31)
    stb r0, 0x20(r31)
    clFlowRound_Update_L_801C9EFC:
    lwz r3, 0x24(r31)
    addi r0, r3, 0x1
    stw r0, 0x24(r31)
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x2
    beq clFlowRound_Update_L_801CA654
    bge clFlowRound_Update_L_801C9F28
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801C9F34
    bge clFlowRound_Update_L_801CA230
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801C9F28:
    cmpwi r0, 0x4
    bge clFlowRound_Update_L_801CA914
    b clFlowRound_Update_L_801CA834
    clFlowRound_Update_L_801C9F34:
    lwz r0, 0x24(r31)
    cmpwi r0, 0xc
    bgt clFlowRound_Update_L_801C9FCC
    xoris r0, r0, 0x8000
    lis r3, 0x4330
    stw r0, 0xc(r1)
    li r0, 0x1
    lfd f1, lbl_806D9D30(r2)
    stw r3, 0x8(r1)
    lfs f4, lbl_806D9D1C(r2)
    lfd f0, 0x8(r1)
    lfs f3, lbl_806D9D20(r2)
    fsubs f0, f0, f1
    lfs f2, lbl_806D9D68(r2)
    stb r0, 0xa4(r31)
    lfs f1, lbl_806D9D6C(r2)
    fmuls f4, f4, f0
    lfs f0, lbl_806D9D28(r2)
    fdivs f3, f4, f3
    fsubs f2, f2, f3
    stfs f2, 0xa8(r31)
    stfs f1, 0xac(r31)
    stfs f0, 0xb0(r31)
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801C9FA8
    lfs f0, lbl_806D9D70(r2)
    fadds f0, f0, f3
    stfs f0, 0xc(r3)
    clFlowRound_Update_L_801C9FA8:
    lfs f0, lbl_806D9D74(r2)
    li r0, 0x1
    stb r0, 0x104(r31)
    fadds f2, f0, f3
    lfs f1, lbl_806D9D78(r2)
    lfs f0, lbl_806D9D28(r2)
    stfs f2, 0x108(r31)
    stfs f1, 0x10c(r31)
    stfs f0, 0x110(r31)
    clFlowRound_Update_L_801C9FCC:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x3
    blt clFlowRound_Update_L_801CA00C
    cmpwi r3, 0x8
    bgt clFlowRound_Update_L_801CA00C
    subi r3, r3, 0x3
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r3, 0xc(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    stfs f0, 0x150(r31)
    clFlowRound_Update_L_801CA00C:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x14
    blt clFlowRound_Update_L_801CA05C
    cmpwi r0, 0x19
    bgt clFlowRound_Update_L_801CA05C
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lwz r3, 0x28(r31)
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r3, 0x0
    lfd f0, 0x8(r1)
    lfs f1, lbl_806D9D80(r2)
    fsubs f2, f0, f2
    lfs f0, lbl_806D9D7C(r2)
    fsubs f1, f2, f1
    fdivs f0, f1, f0
    beq clFlowRound_Update_L_801CA05C
    stfs f0, 0x20(r3)
    clFlowRound_Update_L_801CA05C:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x19
    blt clFlowRound_Update_L_801CA0A8
    subi r3, r3, 0x19
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    lwz r4, 0xec(r31)
    stw r3, 0xc(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r4, 0x0
    stw r0, 0x8(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    beq clFlowRound_Update_L_801CA0A0
    stfs f0, 0x20(r4)
    clFlowRound_Update_L_801CA0A0:
    stfs f0, 0x154(r31)
    stfs f0, 0x158(r31)
    clFlowRound_Update_L_801CA0A8:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x1e
    bne clFlowRound_Update_L_801CA914
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x4
    bl fn_801C9288
    lfs f1, 0x90(r31)
    bl SetScreenBrightness
    li r5, 0x1
    li r0, 0x0
    stb r5, lbl_806D184C(r13)
    stb r0, lbl_806D184D(r13)
    stb r0, 0x164(r31)
    lwz r6, 0x15c(r31)
    cmplwi r6, 0x0
    beq clFlowRound_Update_L_801CA144
    lwz r0, 0x4(r31)
    lis r3, clFlowRound_Update_rodata_8039B338@ha
    addi r4, r3, clFlowRound_Update_rodata_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    lfsx f0, r4, r0
    add r3, r4, r0
    lfs f2, 0x4(r3)
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r0, 0x4(r31)
    lwz r3, 0x15c(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x8(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801CA144
    stb r5, 0x164(r31)
    clFlowRound_Update_L_801CA144:
    li r0, 0x0
    stb r0, 0x165(r31)
    lwz r5, 0x160(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA1C4
    lwz r0, 0x4(r31)
    lis r3, clFlowRound_Update_rodata_8039B338@ha
    addi r4, r3, clFlowRound_Update_rodata_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    add r3, r4, r0
    lfs f0, 0xc(r3)
    lfs f2, 0x10(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x160(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x14(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r4, 0x4(r31)
    cmpwi r4, 0x3
    beq clFlowRound_Update_L_801CA1C4
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    cmpw r4, r0
    bge clFlowRound_Update_L_801CA1C4
    li r0, 0x1
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA1C4:
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x8c(r31)
    li r4, 0x1
    stb r0, 0x20(r31)
    bl fn_801699D8
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA914
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    bgt clFlowRound_Update_L_801CA914
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA914
    lbz r0, 0x4(r4)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA218
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA218:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stb r0, 0x5(r4)
    stw r0, 0x8(r4)
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA230:
    lwz r5, g_pInputState(r13)
    lwz r4, 0x4(r31)
    cmplwi r5, 0x0
    bne clFlowRound_Update_L_801CA248
    li r0, 0x0
    b clFlowRound_Update_L_801CA24C
    clFlowRound_Update_L_801CA248:
    mr r0, r5
    clFlowRound_Update_L_801CA24C:
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA29C
    cmplwi r5, 0x0
    bne clFlowRound_Update_L_801CA260
    li r5, 0x0
    clFlowRound_Update_L_801CA260:
    lwz r3, 0x4(r31)
    lwz r0, 0x14(r5)
    add r0, r3, r0
    stw r0, 0x4(r31)
    lwz r3, 0x8(r31)
    lwz r0, 0x4(r31)
    subi r3, r3, 0x1
    cmpw r0, r3
    ble clFlowRound_Update_L_801CA288
    stw r3, 0x4(r31)
    clFlowRound_Update_L_801CA288:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bge clFlowRound_Update_L_801CA29C
    li r0, 0x0
    stw r0, 0x4(r31)
    clFlowRound_Update_L_801CA29C:
    lwz r0, 0x4(r31)
    cmpw r4, r0
    beq clFlowRound_Update_L_801CA4AC
    mr r3, r31
    li r5, 0x2
    bl fn_801C9288
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x4
    bl fn_801C9288
    li r0, 0x0
    stb r0, 0x164(r31)
    lwz r5, 0x15c(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA334
    lwz r0, 0x4(r31)
    lis r3, clFlowRound_Update_rodata_8039B338@ha
    addi r4, r3, clFlowRound_Update_rodata_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    lfsx f0, r4, r0
    add r3, r4, r0
    lfs f2, 0x4(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x15c(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x8(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801CA334
    li r0, 0x1
    stb r0, 0x164(r31)
    clFlowRound_Update_L_801CA334:
    li r0, 0x0
    stb r0, 0x165(r31)
    lwz r5, 0x160(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA3B4
    lwz r0, 0x4(r31)
    lis r3, clFlowRound_Update_rodata_8039B338@ha
    addi r4, r3, clFlowRound_Update_rodata_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    add r3, r4, r0
    lfs f0, 0xc(r3)
    lfs f2, 0x10(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x160(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x14(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r4, 0x4(r31)
    cmpwi r4, 0x3
    beq clFlowRound_Update_L_801CA3B4
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    cmpw r4, r0
    bge clFlowRound_Update_L_801CA3B4
    li r0, 0x1
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA3B4:
    lwz r0, 0x88(r31)
    lwz r3, 0x4(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA424
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CA424
    stw r3, 0x84(r31)
    li r4, 0x1bf
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowRound_Update_L_801CA424:
    bl fn_801B7CAC
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA4AC
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA484
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    bgt clFlowRound_Update_L_801CA484
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    bne clFlowRound_Update_L_801CA4AC
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA46C
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA4AC
    clFlowRound_Update_L_801CA46C:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stb r0, 0x5(r4)
    stw r0, 0x8(r4)
    b clFlowRound_Update_L_801CA4AC
    clFlowRound_Update_L_801CA484:
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA4AC
    lbz r0, 0x5(r4)
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CA4AC
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x5(r4)
    stw r0, 0x8(r4)
    clFlowRound_Update_L_801CA4AC:
    lwz r0, 0x7c(r31)
    cmpwi r0, -0x1
    beq clFlowRound_Update_L_801CA4BC
    b clFlowRound_Update_L_801CA5D8
    clFlowRound_Update_L_801CA4BC:
    lfs f1, 0x90(r31)
    lfs f0, lbl_806D9D44(r2)
    fsubs f0, f1, f0
    stfs f0, 0x90(r31)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA4EC
    li r3, 0x0
    b clFlowRound_Update_L_801CA4F0
    clFlowRound_Update_L_801CA4EC:
    mr r3, r4
    clFlowRound_Update_L_801CA4F0:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x1
    beq clFlowRound_Update_L_801CA50C
    lfs f1, 0x90(r31)
    lfs f0, lbl_806D9D38(r2)
    fcmpo cr0, f1, f0
    bge clFlowRound_Update_L_801CA5CC
    clFlowRound_Update_L_801CA50C:
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA51C
    li r0, 0x0
    b clFlowRound_Update_L_801CA520
    clFlowRound_Update_L_801CA51C:
    mr r0, r4
    clFlowRound_Update_L_801CA520:
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA544
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA534
    li r4, 0x0
    clFlowRound_Update_L_801CA534:
    li r0, 0x0
    stb r0, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowRound_Update_L_801CA544:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lbz r0, 0x14c(r31)
    li r3, 0x0
    lwz r4, 0x4(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA56C
    li r3, 0x4
    clFlowRound_Update_L_801CA56C:
    add r26, r4, r3
    mr r3, r26
    bl fn_801BA060
    stw r26, g_roundIndex(r13)
    mr r6, r3
    lwz r3, g_cupId(r13)
    lwz r4, 0x0(r6)
    lwz r5, 0x4(r6)
    lwz r6, 0x8(r6)
    bl SetCourseParams
    bl IsItemSelectAllowed
    clrlwi. r0, r3, 24
    beq clFlowRound_Update_L_801CA5AC
    li r0, 0x21
    stw r0, 0x7c(r31)
    b clFlowRound_Update_L_801CA5B4
    clFlowRound_Update_L_801CA5AC:
    li r0, 0x25
    stw r0, 0x7c(r31)
    clFlowRound_Update_L_801CA5B4:
    lfs f0, lbl_806D9D48(r2)
    stfs f0, 0x90(r31)
    bl fn_801B7C64
    li r0, 0x0
    stb r0, 0x164(r31)
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA5CC:
    lfs f1, 0x90(r31)
    bl SetScreenBrightness
    lwz r0, 0x7c(r31)
    clFlowRound_Update_L_801CA5D8:
    cmpwi r0, -0x1
    beq clFlowRound_Update_L_801CA914
    li r24, 0x0
    clFlowRound_Update_L_801CA5E4:
    lwz r0, 0x4(r31)
    cmpw r24, r0
    bne clFlowRound_Update_L_801CA604
    mr r3, r31
    mr r4, r24
    li r5, 0x5
    bl fn_801C9288
    b clFlowRound_Update_L_801CA614
    clFlowRound_Update_L_801CA604:
    mr r3, r31
    mr r4, r24
    li r5, 0x3
    bl fn_801C9288
    clFlowRound_Update_L_801CA614:
    addi r24, r24, 0x1
    cmpwi r24, 0x4
    blt clFlowRound_Update_L_801CA5E4
    lwz r3, 0x28(r31)
    li r4, 0x1
    bl Sprite_Destroy
    bl fn_801B87D8
    li r0, -0x1
    li r3, 0x0
    stb r0, lbl_806D184C(r13)
    li r0, 0x1
    stw r3, 0x28(r31)
    stw r3, 0x24(r31)
    stb r3, 0x8c(r31)
    stb r0, 0x20(r31)
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA654:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x5
    bgt clFlowRound_Update_L_801CA6D8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lwz r3, 0xec(r31)
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r3, 0x0
    lfd f1, 0x8(r1)
    lfs f0, lbl_806D9D7C(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D9D28(r2)
    fdivs f0, f1, f0
    fsubs f1, f2, f0
    beq clFlowRound_Update_L_801CA69C
    stfs f1, 0x20(r3)
    clFlowRound_Update_L_801CA69C:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA6AC
    stfs f1, 0x20(r3)
    clFlowRound_Update_L_801CA6AC:
    lfs f0, lbl_806D9D84(r2)
    li r3, -0x100
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r0, 0xc(r1)
    rlwimi r3, r0, 0, 24, 31
    stw r3, 0xc8(r31)
    stw r3, 0xcc(r31)
    stw r3, 0xd0(r31)
    stw r3, 0xd4(r31)
    clFlowRound_Update_L_801CA6D8:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x28
    blt clFlowRound_Update_L_801CA740
    subi r3, r3, 0x28
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    li r4, -0x100
    stw r3, 0xc(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D9D84(r2)
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    fmuls f0, f2, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r0, 0x14(r1)
    rlwimi r4, r0, 0, 24, 31
    stw r4, 0x128(r31)
    stw r4, 0x12c(r31)
    stw r4, 0x130(r31)
    stw r4, 0x134(r31)
    clFlowRound_Update_L_801CA740:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x2d
    bne clFlowRound_Update_L_801CA914
    lwz r3, 0xf0(r31)
    li r4, 0xc7
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xf0(r31)
    li r4, 0x1ad4
    li r5, 0x1ae4
    bl Sprite_SetAnimParam
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x6
    bl fn_801C9288
    bl fn_801B8434
    lwz r0, 0x88(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA7E8
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CA7E8
    li r0, 0x2
    li r4, 0x83
    stw r0, 0x80(r31)
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    clFlowRound_Update_L_801CA7E8:
    li r4, 0x0
    li r3, 0x1
    stw r4, 0x24(r31)
    stb r3, 0x20(r31)
    lwz r5, 0x168(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA824
    lbz r0, 0x4(r5)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA824
    lbz r0, 0x5(r5)
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CA824
    stb r3, 0x5(r5)
    stw r4, 0x8(r5)
    clFlowRound_Update_L_801CA824:
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA834:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x5
    bgt clFlowRound_Update_L_801CA870
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x154(r31)
    clFlowRound_Update_L_801CA870:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x6
    bgt clFlowRound_Update_L_801CA8AC
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D88(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x150(r31)
    clFlowRound_Update_L_801CA8AC:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x7
    bgt clFlowRound_Update_L_801CA8E8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D8C(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x158(r31)
    clFlowRound_Update_L_801CA8E8:
    lwz r0, 0x24(r31)
    cmpwi r0, 0xf
    bne clFlowRound_Update_L_801CA900
    lfs f0, lbl_806D9D90(r2)
    lwz r3, 0xf0(r31)
    stfs f0, 0xc(r3)
    clFlowRound_Update_L_801CA900:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x2d
    bne clFlowRound_Update_L_801CA914
    lwz r3, 0x7c(r31)
    b clFlowRound_Update_L_801CAD98
    clFlowRound_Update_L_801CA914:
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA9D4
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA9D4
    lwz r3, 0x8(r4)
    cmpwi r3, 0x8
    bgt clFlowRound_Update_L_801CA9C8
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    bne clFlowRound_Update_L_801CA96C
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D94(r2)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fmuls f0, f1, f0
    b clFlowRound_Update_L_801CA994
    clFlowRound_Update_L_801CA96C:
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f3, lbl_806D9D30(r2)
    stw r0, 0x8(r1)
    lfs f1, lbl_806D9D94(r2)
    lfd f2, 0x8(r1)
    lfs f0, lbl_806D9D28(r2)
    fsubs f2, f2, f3
    fnmsubs f0, f2, f1, f0
    clFlowRound_Update_L_801CA994:
    lwz r3, 0x0(r4)
    stfs f0, 0x20(r3)
    lwz r3, 0x8(r4)
    addi r0, r3, 0x1
    cmpwi r3, 0x8
    stw r0, 0x8(r4)
    bne clFlowRound_Update_L_801CA9C8
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA9C8
    li r0, 0x0
    stb r0, 0x4(r4)
    stb r0, 0x5(r4)
    clFlowRound_Update_L_801CA9C8:
    lwz r3, 0x0(r4)
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9D4:
    lwz r3, 0x15c(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA9E8
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9E8:
    lwz r3, 0x160(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA9FC
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9FC:
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA10
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA10:
    lwz r3, 0xec(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA24
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA24:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA38
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA38:
    lfs f0, lbl_806D9D24(r2)
    mr r29, r31
    addi r28, r30, 0x0
    li r26, 0x0
    fneg f30, f0
    li r27, 0x0
    clFlowRound_Update_L_801CAA50:
    lwz r3, 0x3c(r29)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CACB0
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CACB0
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x4
    beq clFlowRound_Update_L_801CACB0
    bge clFlowRound_Update_L_801CAA98
    cmpwi r0, 0x2
    beq clFlowRound_Update_L_801CACB0
    bge clFlowRound_Update_L_801CAC98
    cmpwi r0, 0x1
    bge clFlowRound_Update_L_801CAAA8
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAA98:
    cmpwi r0, 0x6
    beq clFlowRound_Update_L_801CAC98
    bge clFlowRound_Update_L_801CACB0
    b clFlowRound_Update_L_801CAB2C
    clFlowRound_Update_L_801CAAA8:
    lwz r0, 0x34(r29)
    cmpwi r0, 0x0
    bne clFlowRound_Update_L_801CACB0
    lwz r3, 0x38(r29)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    addi r0, r3, 0x1
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x38(r29)
    lfs f4, lbl_806D9D1C(r2)
    lwz r0, 0x38(r29)
    lfs f1, 0x4(r28)
    xoris r0, r0, 0x8000
    lfs f0, lbl_806D9D20(r2)
    stw r0, 0x14(r1)
    fadds f3, f4, f1
    lwz r3, 0x3c(r29)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fmuls f1, f4, f1
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0xc(r3)
    lwz r0, 0x38(r29)
    cmpwi r0, 0xc
    blt clFlowRound_Update_L_801CACB0
    lwz r3, 0x34(r29)
    li r4, 0x1
    addi r0, r3, 0x1
    stw r0, 0x34(r29)
    lwz r3, 0x3c(r29)
    bl fn_8019FF6C
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAB2C:
    lwz r3, g_cupId(r13)
    addi r4, r30, 0x11c
    lwz r0, 0x30(r29)
    cmpwi r26, 0x2
    slwi r5, r3, 1
    addi r3, r30, 0xc0
    lhax r5, r4, r5
    slwi r0, r0, 2
    addi r4, r30, 0x30
    lfs f31, lbl_806D9D24(r2)
    slwi r5, r5, 4
    lwzx r25, r3, r0
    add r24, r5, r27
    add r24, r4, r24
    beq clFlowRound_Update_L_801CAB70
    cmpwi r26, 0x4
    bne clFlowRound_Update_L_801CAB74
    clFlowRound_Update_L_801CAB70:
    fmr f31, f30
    clFlowRound_Update_L_801CAB74:
    lwz r3, 0x3c(r29)
    cmplwi r3, 0x0
    bne clFlowRound_Update_L_801CABA8
    li r3, 0x30
    bl Alloc
    mr. r23, r3
    beq clFlowRound_Update_L_801CABA0
    mr r4, r25
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowRound_Update_L_801CABA0:
    stw r23, 0x3c(r29)
    b clFlowRound_Update_L_801CABB8
    clFlowRound_Update_L_801CABA8:
    mr r4, r25
    li r5, 0x0
    li r6, 0x0
    bl Sprite_SetupAnim
    clFlowRound_Update_L_801CABB8:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x1
    beq clFlowRound_Update_L_801CAC04
    bge clFlowRound_Update_L_801CABD4
    cmpwi r0, 0x0
    bge clFlowRound_Update_L_801CABE0
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CABD4:
    cmpwi r0, 0x3
    bge clFlowRound_Update_L_801CAC48
    b clFlowRound_Update_L_801CAC28
    clFlowRound_Update_L_801CABE0:
    lwz r3, 0x3c(r29)
    li r4, 0x1951
    lha r5, 0x0(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CAC04:
    lwz r3, 0x3c(r29)
    li r4, 0x194c
    lha r5, 0x2(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CAC28:
    lwz r3, 0x3c(r29)
    li r4, 0x194c
    lha r5, 0x2(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    clFlowRound_Update_L_801CAC48:
    lwz r3, 0x3c(r29)
    li r4, 0x1a1e
    lha r5, 0x0(r24)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    bl fn_801A0550
    lfs f0, 0x8(r28)
    li r4, 0x1
    lwz r3, 0x3c(r29)
    lfs f1, 0x4(r28)
    fadds f2, f0, f31
    lfs f0, lbl_806D9D28(r2)
    stfs f1, 0xc(r3)
    stfs f2, 0x10(r3)
    lwz r3, 0x3c(r29)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r3, 0x3c(r29)
    bl fn_8019FF6C
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAC98:
    lwz r3, 0x3c(r29)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x2c(r29)
    stw r0, 0x3c(r29)
    clFlowRound_Update_L_801CACB0:
    addi r26, r26, 0x1
    addi r28, r28, 0xc
    cmpwi r26, 0x4
    addi r27, r27, 0x4
    addi r29, r29, 0x14
    blt clFlowRound_Update_L_801CAA50
    lwz r3, 0x88(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAD94
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne clFlowRound_Update_L_801CAD94
    lwz r3, 0x80(r31)
    cmpwi r3, 0x0
    bne clFlowRound_Update_L_801CAD68
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    lwz r0, 0x88(r31)
    lwz r3, 0x84(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CAD68
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CAD68
    stw r3, 0x84(r31)
    li r4, 0x1bf
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowRound_Update_L_801CAD68:
    lwz r0, 0x80(r31)
    cmpwi r0, 0x2
    bne clFlowRound_Update_L_801CAD94
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x88(r31)
    lwz r3, 0x80(r31)
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    clFlowRound_Update_L_801CAD94:
    li r3, -0x1
    clFlowRound_Update_L_801CAD98:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lmw r23, 0x1c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

}
#pragma exceptions reset
#pragma defer_codegen reset

inline SprFlag::SprFlag() {
    visible = 0;
    x5 = 0;
    x8 = 0;
    spr = new Sprite(0x9E, 1, lbl_806D9DAC, lbl_806D9DAC, 1.0f, 1.0f, 0.0f, 0.0f);
}

clFlowRound::clFlowRound() {
#define self this
    int first;
    short cup;
    int i;
    int base;
    int level;
    Sprite *spr;

    SpriteSystem_EnsureInit();
    cup = clFlowRound_Draw_data_8049AF8C[g_cupId];
    SetSyncTarget(0x1B);
    PreloadResource(clFlowRound_Draw_data_8049AFA0[cup]);
    PreloadResource(clFlowRound_Draw_data_8049AFA0[cup] + 12);
    PreloadResource(s_roundRes[cup][0].alternate);
    PreloadResource(s_roundRes[cup][0].alternate + 6);
    PreloadResource(s_roundRes[cup][0].id);
    PreloadResource(s_roundRes[cup][0].id + 9);
    PreloadResource(s_roundRes[cup][1].alternate);
    PreloadResource(s_roundRes[cup][1].alternate + 6);
    PreloadResource(s_roundRes[cup][1].id);
    PreloadResource(s_roundRes[cup][1].id + 9);
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
        if (RoundIsUnlocked(g_playerData, i + base)) {
            self->slots[i].state = 0;
            self->unlocked++;
        } else if ((unsigned char)first) {
            self->slots[i].state = 1;
            first = 0;
            self->unlocked++;
        } else {
            self->slots[i].state = 2;
        }
        fn_801C9288((RoundTileOwner *)self, i, 1);
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
    self->slots[0].spr = new Sprite(0x1C0, 1, lbl_806D9D98, lbl_806D9D9C, 1.0f, 1.0f, 0.0f, 0.0f);
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
        self->sprEC = new Sprite(0x85, 1, lbl_806D9DA0, lbl_806D9DA4, 1.0f, 1.0f, 0.0f, 0.0f);
    }
    self->sprF0 = new Sprite(0x1DD, 0, lbl_806D9DA8, lbl_806D9D78, lbl_806D9D28, lbl_806D9D28, lbl_806D9D38, lbl_806D9D28);
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
    self->spr15C = new Sprite(0x9C, 1, lbl_806D9D38, lbl_806D9D38, lbl_806D9D3C, lbl_806D9D3C, lbl_806D9D38, lbl_806D9D28);
    self->spr160 = new Sprite(0x9C, 1, lbl_806D9D38, lbl_806D9D38, lbl_806D9D3C, lbl_806D9D3C, lbl_806D9D38, lbl_806D9D28);
    self->show164 = 0;
    self->show165 = 0;
    if (self->mode == 1) {
        self->flag168 = new SprFlag;
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
        self->spr88 = new Sprite(0x84, 0, 0);
        Sprite_SetAnimParam(self->spr88, 0x1970, s_roundTitle[clFlowRound_Draw_data_8049AF8C[g_cupId]]);
        fn_801A0550(self->spr88);
        spr = self->spr88;
        spr->x = lbl_806D9D10;
        spr->y = lbl_806D9D14;
    }
    DebugPrintf("after_constructer\n");
    InitRumbleController(1);
}
#undef self

clFlowRound::~clFlowRound() {
    SprFlag *owned;
    int i;

    fn_80169C44();
    if (input_state() != 0) {
        InputState *state = input_state();

        state->active = 0;
        state->value18 = 0;
        state->value1C = 0;
    }
    SetScreenBrightness(lbl_806D9D48);
    fn_80120A08(clFlowRound_Draw_data_8049AFA0[clFlowRound_Draw_data_8049AF8C[g_cupId]]);
    fn_80120A08(clFlowRound_data_806CFDF0[0]);
    Sprite_Destroy(spr160, 1);
    Sprite_Destroy(spr15C, 1);
    Sprite_Destroy(sprEC, 1);
    Sprite_Destroy(spr88, 1);
    Sprite_Destroy(slots[0].spr, 1);
    Sprite_Destroy(sprF0, 1);
    {
        owned = flag168;

        if (owned != 0) {
            Sprite_Destroy(owned->spr, 1);
            MemoryManager_TimedFree(owned);
        }
    }
    for (i = 0; i < 4; i++) {
        Sprite_Destroy(slots[i + 1].spr, 1);
    }
    fn_801A1678();
}

/* clFlowRound: the round (race 1-4) select flow of a cup.
 * A real polymorphic class with RTTI: the ctor stores the vtable between the
 * clFlowProcess base ctor and the ResCtrl member ctors, and -inline deferred
 * makes CW pool the compiler-generated vtable with the TU's .data.
 * Draw and Update stay C/asm functions that the vtable reaches by rename.
 */

#include "game/types/size_t.h"
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
    char pad14[0x30 - 0x14];
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

void *operator new(size_t size);
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
int fn_801C9288(clFlowRound *self, int i, int flag);
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
void clFlowRound_Draw(RoundView *self);

/* === .data 0x8049AE70..0x8049AFD0 === */
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

/* === .sdata 0x806CFDF0 (RTTI objects follow) === */
short clFlowRound_data_806CFDF0[4] = { 0x1977, 0x1978, 0x1979, 0x197A };

/* === .rodata 0x8039B308..0x8039B3C8 (class names and the debug string follow) === */
extern const short clFlowRound_Init_rodata_8039B308[8][3];
struct RoundArrow {
    float lx;
    float ly;
    float lrot;
    float rx;
    float ry;
    float rrot;
};
extern const RoundArrow clFlowRound_Update_rodata_8039B338[4];
const short clFlowRound_Init_rodata_8039B308[8][3] = {
    { 0x1A24, 0x1A25, 0x1A26 }, { 0x1A00, 0x1A01, 0x1A02 }, { 0x19EE, 0x19EF, 0x19F0 },
    { 0x1A36, 0x1A37, 0x1A38 }, { 0x1A12, 0x1A13, 0x1A14 }, { 0x1A48, 0x1A49, 0x1A4A },
    { 0x1A6C, 0x1A6D, 0x1A6E }, { 0x1A5A, 0x1A5B, 0x1A5C },
};
const RoundArrow clFlowRound_Update_rodata_8039B338[4] = {
    { 0.0f, 0.0f, 0.0f, 144.0f, 204.0f, -40.0f }, { 124.0f, 195.0f, 150.0f, 260.0f, 195.0f, 40.0f },
    { 254.0f, 204.0f, -150.0f, 388.0f, 204.0f, -40.0f }, { 384.0f, 195.0f, 150.0f, 0.0f, 0.0f, 0.0f },
};
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}


/* fn_801C9288: sets one round tile's state and (re)creates its sprite. It reads the TU's
 * .data tables through the section anchor, so it lives here, ahead of Draw. */
namespace tile {
struct Spr {
    char opaque[0xC];
    float x, y, sx, sy;
    void Position(float px, float py) { x = px; y = py; }
    void Scale(float s) { sx = s; sy = s; }
};
struct Slot { int state, variant, timer, frame; Spr *sprite; };
struct Owner { char opaque[0x2C]; Slot slots[5]; };
}
extern "C" {
void Sprite_SetupAnim(void *spr, int id, int a, int b);
void fn_8019FF6C(void *spr, int flag);
extern const float lbl_806D9D40;
#pragma defer_codegen off
/* fakematch (pragma): the target loads the offset constant again for the negated arm
 * (`lfs f31,C; ... lfs f0,C; fneg f31,f0`); natural code has no pragma and CSEs the load. */
#pragma push
#pragma opt_common_subs off
int fn_801C9288(::clFlowRound *self_, int index, int state) {
    tile::Owner *self = (tile::Owner *)self_;
    tile::Slot *slot = &self->slots[index];
    if (state == 1) { if (slot->state != 0) return 0; }
    else { if (slot->state == 0) return 0; }
    slot->state = state;
    slot->timer = 0;
    slot->frame = 0;
    switch (state) {
    case 1: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D3C);
        break;
    }
    case 2: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[15 + slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D3C);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 3: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[12 + slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D3C);
        break;
    }
    case 4: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[9 + slot->variant];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D28);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 5: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[6 + slot->variant];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D28);
        break;
    }
    case 6: {
        int anim;
        RoundResPair *param;
        RoundPos *pos;
        pos = &clFlowRound_data_8049AE70[index];
        param = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][index];
        anim = s_roundAnim[3 + slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = (tile::Spr *)new ::Sprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id0);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->id1);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->b);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->a);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(lbl_806D9D3C);
        break;
    }
    }
    return 1;
}
#pragma pop
#pragma defer_codegen reset
}

/* Draw is generated in place; with -inline deferred the rest of the TU is
 * generated at the end in reverse order (Init after Dtor in .text). */
#pragma defer_codegen off
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


}
/* clFlowRound_Update (0x801C9EAC). The vtable reaches it by rename; it works on
 * its own field view of the object. */
namespace upd {
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
void *Alloc(unsigned long size);
}
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
}


#pragma exceptions on
static inline InputState *input_state(void) {
    InputState *state = (InputState *)g_pInputState;

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
        SetPos(self->spr15C, clFlowRound_Update_rodata_8039B338[self->round].lx, clFlowRound_Update_rodata_8039B338[self->round].ly);
        self->spr15C->rot = lbl_806D9D08 * clFlowRound_Update_rodata_8039B338[self->round].lrot;
        if (self->round != 0) {
            self->show164 = 1;
        }
    }
    self->show165 = 0;
    if (self->spr160 != 0) {
        SetPos(self->spr160, clFlowRound_Update_rodata_8039B338[self->round].rx, clFlowRound_Update_rodata_8039B338[self->round].ry);
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
    int prev;
    int next;
    int round;
    int anim;
    RoundResPair *res;
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
            fn_801C9288((::clFlowRound *)self, self->round, 4);
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
            fn_801C9288((::clFlowRound *)self, prev, 2);
            fn_801C9288((::clFlowRound *)self, self->round, 4);
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
        next = self->x7C;
        switch (next) {
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
            next = self->x7C;
            break;
        }
        if (next != -1) {
            for (int i = 0; i < 4; i++) {
                if (i == self->round) {
                    fn_801C9288((::clFlowRound *)self, i, 5);
                } else {
                    fn_801C9288((::clFlowRound *)self, i, 3);
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
                unsigned char al = (int)(lbl_806D9D84 * t);
                unsigned int c = 0xFFFFFF00 | al;

                self->layer94.SetColor(c);
            }
        }
        if (self->x24 >= 40) {
            t = lbl_806D9D28 - (float)(self->x24 - 40) / lbl_806D9D7C;
            {
                unsigned char al = (int)(lbl_806D9D84 * t);
                unsigned int c = 0xFFFFFF00 | al;

                self->layerF4.SetColor(c);
            }
        }
        if (self->x24 == 45) {
            Sprite_SetupAnim(self->sprF0, 0xC7, 1, 0);
            Sprite_SetAnimParam(self->sprF0, 0x1AD4, 0x1AE4);
            fn_801C9288((::clFlowRound *)self, self->round, 6);
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
    for (int j = 0; j < 4; j++) {
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
                dy = lbl_806D9D24;
                res = &s_roundRes[clFlowRound_Draw_data_8049AF8C[g_cupId]][j];
                anim = s_roundAnim[self->slots[j].state];
                if (j == 2 || j == 4) {
                    dy = ndy;
                }
                if (self->slots[j].spr == 0) {
                    self->slots[j].spr = (Sprite *)new ::Sprite(anim, 0, 0);
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
                /* fakematch: natural code is `clFlowRound_data_8049AE70[j].y + dy`; `y - -dy`
                 * keeps the operands in source order (fadds f2,f0,f31). */
                SetPos(self->slots[j].spr, clFlowRound_data_8049AE70[j].x, clFlowRound_data_8049AE70[j].y - -dy);
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

#pragma exceptions off
}
extern "C" {
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
    PreloadResource(s_roundRes[cup][0].b);
    PreloadResource(s_roundRes[cup][0].b + 6);
    PreloadResource(s_roundRes[cup][0].a);
    PreloadResource(s_roundRes[cup][0].a + 9);
    PreloadResource(s_roundRes[cup][1].b);
    PreloadResource(s_roundRes[cup][1].b + 6);
    PreloadResource(s_roundRes[cup][1].a);
    PreloadResource(s_roundRes[cup][1].a + 9);
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
        fn_801C9288((::clFlowRound *)self, i, 1);
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

#include "game/types/pmf.h"
#include "game/Menu801F0CC0_private.h"
#include "game/fn_801F27B4_private.h"

/* Menu layout coordinates (separate objects: the menu methods reach them through the
 * section anchor, base + object offset, then + element offset), followed by two
 * dynamically initialized method tables. */
static float menuGeometryA[66] = {
    0.0f, 0.0f, 0.0f, 0.0f,
    256.0f, 0.0f, 0.0f, 0.0f,
    512.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 256.0f, 0.0f, 0.0f,
    256.0f, 256.0f, 0.0f, 0.0f,
    512.0f, 256.0f, 0.0f, 0.0f,
    0.0f, 25.0f, 0.0f, 0.0f,
    320.0f, 97.0f, 320.0f, 25.0f,
    0.0f, 97.0f, 320.0f, 88.0f,
    158.0f, 352.0f, 0.0f, 410.0f,
    324.0f, 28.0f, 96.0f, 380.0f,
    320.0f, 62.0f, 150.0f, 62.0f,
    398.0f, 380.0f, 320.0f, 0.0f,
    150.0f, 62.0f, 115.0f, 122.0f,
    0.0f, 184.0f, 409.0f, 226.0f,
    55.0f, 386.0f, 0.0f, 438.0f,
    232.0f, 40.0f,
};
static MenuRect801F menuSelectRects[2] = {
    {55.0f, 386.0f, 0.0f, 0.0f},
    {355.0f, 386.0f, 0.0f, 0.0f},
};
static float menuOptionArt[50] = {
    0.0f, 27.0f, 0.0f, 0.0f,
    640.0f, 90.0f, 160.0f, 239.0f,
    0.0f, 90.0f, 284.0f, 201.0f,
    480.0f, 239.0f, 284.0f, 90.0f,
    284.0f, 201.0f, 57.0f, 340.0f,
    493.0f, 341.0f, 531.0f, 137.0f,
    145.0f, 364.0f, 0.0f, 377.0f,
    351.0f, 50.0f, 110.0f, 419.0f,
    0.0f, 291.0f, 420.0f, 37.0f,
    288.0f, 202.0f, 568.0f, 90.0f,
    64.0f, 75.0f, 632.0f, 90.0f,
    -64.0f, 75.0f, 568.0f, 90.0f,
    64.0f, 75.0f,
};
static MenuRect801F menuOptionTabA[2] = {
    {0.0f, 377.0f, 351.0f, 50.0f},
    {0.0f, 427.0f, 351.0f, 50.0f},
};
static MenuRect801F menuOptionTabB[3] = {
    {0.0f, 327.0f, 420.0f, 37.0f},
    {0.0f, 291.0f, 420.0f, 37.0f},
    {320.0f, 271.0f, 0.0f, 0.0f},
};
static MenuRect801F menuLevelGauge[7] = {
    {159.0f, 157.0f, 0.0f, 0.0f},
    {223.0f, 125.0f, 0.0f, 0.0f},
    {288.0f, 110.0f, 0.0f, 0.0f},
    {355.0f, 110.0f, 0.0f, 0.0f},
    {420.0f, 125.0f, 0.0f, 0.0f},
    {483.0f, 157.0f, 0.0f, 0.0f},
    {320.0f, 392.0f, 0.0f, 0.0f},
};
static MenuRect801F menuLevelLabel[7] = {
    {368.0f, 258.0f, 264.0f, 176.0f},
    {0.0f, 0.0f, 296.0f, 236.0f},
    {592.0f, 0.0f, 298.0f, 236.0f},
    {296.0f, 0.0f, 296.0f, 252.0f},
    {632.0f, 258.0f, 300.0f, 234.0f},
    {0.0f, 258.0f, 368.0f, 262.0f},
    {932.0f, 0.0f, 64.0f, 75.0f},
};
static MenuRect801F menuLevelIcon[6] = {
    {0.0f, 0.0f, 256.0f, 41.0f},
    {0.0f, 41.0f, 256.0f, 44.0f},
    {0.0f, 85.0f, 256.0f, 41.0f},
    {0.0f, 126.0f, 256.0f, 42.0f},
    {0.0f, 168.0f, 256.0f, 45.0f},
    {0.0f, 213.0f, 256.0f, 43.0f},
};
/* MWCC emits the default ptmf records and the .ctors initializer. */
static MenuMethod801F liveA[14] = {
    PMF_OF(&MenuReceiver801F::fn_801F2400),
    PMF_OF(&MenuReceiver801F::fn_801F2370),
    PMF_OF(&MenuReceiver801F::fn_801F21C8),
    PMF_OF(&MenuReceiver801F::fn_801F20A0),
    PMF_OF(&MenuReceiver801F::fn_801F1EE0),
    PMF_OF(&MenuReceiver801F::fn_801F1C58),
    PMF_OF(&MenuReceiver801F::fn_801F1AC8),
    PMF_OF(&MenuReceiver801F::fn_801F19C8),
    PMF_OF(&MenuReceiver801F::fn_801F1664),
    PMF_OF(&MenuReceiver801F::fn_801F140C),
    PMF_OF(&MenuReceiver801F::fn_801F1244),
    PMF_OF(&MenuReceiver801F::fn_801F0ECC),
    PMF_OF(&MenuReceiver801F::fn_801F0D04),
    PMF_OF(&MenuReceiver801F::fn_801F0CC0)
};
static MenuMethod801F liveB[14] = {
    PMF_OF(&MenuReceiver801F::fn_801F230C),
    PMF_OF(&MenuReceiver801F::fn_801F230C),
    PMF_OF(&MenuReceiver801F::fn_801F1FE4),
    PMF_OF(&MenuReceiver801F::fn_801F1FE4),
    PMF_OF(&MenuReceiver801F::fn_801F1BC8),
    PMF_OF(&MenuReceiver801F::fn_801F1BC8),
    PMF_OF(&MenuReceiver801F::fn_801F190C),
    PMF_OF(&MenuReceiver801F::fn_801F190C),
    PMF_OF(&MenuReceiver801F::fn_801F15D4),
    PMF_OF(&MenuReceiver801F::fn_801F115C),
    PMF_OF(&MenuReceiver801F::fn_801F115C),
    PMF_OF(&MenuReceiver801F::fn_801F0E3C),
    PMF_OF(&MenuReceiver801F::fn_801F0E3C),
    PMF_OF(&MenuReceiver801F::fn_801F0CBC)
};
#ifndef __MWERKS__
/* Menu801F0CC0_private.h declares these two tables for this unit as
 * lbl_804E5050 / lbl_804E51A0 with Menu801F as the class; the build gives
 * the statics those names after compiling (tools/extab_user_renames.json). */
#define lbl_804E5050 ((Menu801FMethod *)liveA)
#define lbl_804E51A0 ((Menu801FMethod *)liveB)
#endif

static inline unsigned int MenuRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    return (r << 24) | ((g & 255) << 16) | ((b & 255) << 8) | (a & 255);
}

/* GC/2.6: `0xFFFFFF00 | alpha` gives the target's li -0x100 + rlwimi / or
 * (regalloc_patterns §11); 1.3.2 needs __rlwimi and colors it differently. */
static inline unsigned int WithAlpha(unsigned int color, unsigned char alpha) {
    return color | alpha;
}

/* Loops in a static inline: only an inlined loop gets the target's
 * `mr rOff, rI` strength-reduction init (see fn_801F230C). */
static inline void SetColorRange(Menu801F *self, int from, int to, unsigned int c) {
    for (int i = from; i < to; i++) fn_801F6E98(&self->sprites[i], c);
}
static inline void SetAlphaRange(Menu801F *self, int from, int to, unsigned char alpha) {
    int i;
    unsigned int c = 0xFFFFFF00 | alpha;
    for (i = from; i < to; ++i) fn_801F6E98(&self->sprites[i], c);
}

static inline void SetAlpha2(Menu801F *self, int from, int to, int nextFrom, int nextTo, unsigned char alpha) {
    unsigned int c;
    int offset;
    int i;
    c = 0xFFFFFF00 | alpha;
    i = from;
    offset = from * sizeof(MenuSprite801F);
    for (; i < to; ++i, offset += sizeof(MenuSprite801F)) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    i = nextFrom;
    offset = nextFrom * sizeof(MenuSprite801F);
    for (; i < nextTo; ++i, offset += sizeof(MenuSprite801F)) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
}

static inline void DrawRange(Menu801F *self, int from, int to, float z) {
    for (int i = from; i < to; i++) fn_801F7B74(self->context, &self->sprites[i], z);
}
static inline void SetColor2(Menu801F *self, int a, int b, int x, int y, unsigned int c) {
    SetColorRange(self, a, b, c);
    SetColorRange(self, x, y, c);
}


// Shared option artwork; inlined by both input handlers.
static inline void SetOption(Menu801F *self) {
    if (self->option == 0) {
        fn_801F6ED0(&self->sprites[20], lbl_806DA568, lbl_806DA568);
        fn_801F6ED0(&self->sprites[21], lbl_806DA56C, lbl_806DA56C);
        fn_801F6D58(&self->sprites[23], &menuOptionTabA[0], 0, 0);
        fn_801F6D58(&self->sprites[24], &menuOptionTabB[0], 0, 0);
        fn_801F6C2C(&self->sprites[25], (MenuRect801F *)menuOptionArt + 9, 1, 0);
    } else {
        fn_801F6ED0(&self->sprites[20], lbl_806DA56C, lbl_806DA56C);
        fn_801F6ED0(&self->sprites[21], lbl_806DA568, lbl_806DA568);
        fn_801F6D58(&self->sprites[23], &menuOptionTabA[1], 0, 0);
        fn_801F6D58(&self->sprites[24], &menuOptionTabB[1], 0, 0);
        fn_801F6C2C(&self->sprites[25], (MenuRect801F *)menuOptionArt + 9, 0, 0);
    }
}

extern "C" void fn_801F0CC0(Menu801F *self) {
    if (!self->active) { clCGameDemoWC_StubBlr_800adda0(self); clCGameDemoWC_StubBlr_800adda4(); }
    self->active = 1;
}

/* The target indexes sprites[i] without strength reduction in this function. */
#pragma opt_strength_reduction off
extern "C" void fn_801F0D04(Menu801F *self) {
    unsigned int v = fn_8020A788(self->fade.p);
    unsigned int c = MenuRGBA(v, v, v, 255);
    for (int i = 26; i < 32; ++i) fn_801F6E98(&self->sprites[i], c);
    for (int i = 32; i < 35; ++i) fn_801F6E98(&self->sprites[i], c);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        for (int i = 26; i < 32; ++i) fn_801F6E98(&self->sprites[i], 255);
        for (int i = 32; i < 35; ++i) fn_801F6E98(&self->sprites[i], 255);
        self->state = 13;
    }
}
#pragma opt_strength_reduction reset

extern "C" void fn_801F0E3C(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 26, 32, lbl_806DA550);
    DrawRange(self, 32, 35, lbl_806DA550);
}

extern "C" void fn_801F0ECC(Menu801F *self) {
    int offset;
    int i;
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    float v = input->v2();
    if (v >= lbl_806DA550 && v <= lbl_806DA554) self->level = 0;
    else if (v > lbl_806DA554 && v <= lbl_806DA558) self->level = 1;
    else if (v > lbl_806DA558 && v <= lbl_806DA55C) self->level = 2;
    else if (v > lbl_806DA55C && v <= lbl_806DA560) self->level = 3;
    else if (v > lbl_806DA560 && v <= lbl_806DA564) self->level = 4;
    else if (v > lbl_806DA564 && v <= lbl_806DA568) self->level = 5;
    fn_801F6D58(&self->sprites[32], &menuLevelLabel[self->level], 0, 0);
    fn_801F7040(&self->sprites[33], &menuLevelGauge[self->level], lbl_806DA568);
    fn_801F6D58(&self->sprites[34], &menuLevelIcon[self->level], 0, 0);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        SetColorRange(self, 6, 12, 0xFFFFFF00);
        SetColorRange(self, 19, 26, 0xFFFFFF00);
        self->state = 10;
    }
    if (input->Pressed(0x100) == 1) {
        fn_8020A7CC(self->fade.p, 255, 0, 22);
        self->state = 12;
    }
}

extern "C" void fn_801F115C(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 6, 12, lbl_806DA550);
    DrawRange(self, 19, 26, lbl_806DA550);
    DrawRange(self, 26, 32, lbl_806DA550);
    DrawRange(self, 32, 35, lbl_806DA550);
}

extern "C" void fn_801F1244(Menu801F *self) {
    unsigned int c;
    unsigned int c2;
    int offset;
    int i;
    unsigned char v;
    v = fn_8020A788(self->fade.p);
    c = 0xFFFFFF00 | v;
    i = 6;
    offset = 0x378;
    for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    i = 19;
    offset = 0xafc;
    for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    c2 = 0xFFFFFF00 | (unsigned char)(255 - v);
    i = 26;
    offset = 0xf08;
    for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c2);
    i = 32;
    offset = 0x1280;
    for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c2);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        i = 19;
        offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        i = 26;
        offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        i = 32;
        offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        self->state = 8;
    }
}

extern "C" void fn_801F140C(Menu801F *self) {
    unsigned int c;
    unsigned int c2;
    int offset;
    int i;
    unsigned char v;
    v = fn_8020A788(self->fade.p);
    c = 0xFFFFFF00 | (unsigned char)(255 - v);
    i = 6;
    offset = 0x378;
    for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    i = 19;
    offset = 0xafc;
    for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    c2 = 0xFFFFFF00 | v;
    i = 26;
    offset = 0xf08;
    for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c2);
    i = 32;
    offset = 0x1280;
    for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c2);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        i = 19;
        offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        i = 26;
        offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        i = 32;
        offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        self->state = 11;
    }
}

extern "C" void fn_801F15D4(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 6, 12, lbl_806DA550);
    DrawRange(self, 19, 26, lbl_806DA550);
}

extern "C" void fn_801F1664(Menu801F *self) {
    int i;
    int offset;
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Pressed(0x10) == 1) self->option = 0;
    else if (input->Pressed(0x20) == 1) self->option = 1;
    SetOption(self);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        SetColorRange(self, 12, 19, 0xFFFFFF00);
        self->state = 7;
    }
    if (input->Pressed(0x100) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        SetColorRange(self, 26, 32, 0xFFFFFF00);
        SetColorRange(self, 32, 35, 0xFFFFFF00);
        self->state = 9;
    }
}

extern "C" void fn_801F190C(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 6, 12, lbl_806DA550);
    DrawRange(self, 19, 26, lbl_806DA550);
    DrawRange(self, 12, 19, lbl_806DA550);
}

extern "C" void fn_801F19C8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, v);
    SetColorRange(self, 12, 19, c);
    SetAlphaRange(self, 19, 26, (unsigned char)(255 - v));
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        SetColorRange(self, 12, 26, 0xFFFFFFFF);
        self->state = 5;
    }
}

extern "C" void fn_801F1AC8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    SetColorRange(self, 12, 19, c);
    SetAlphaRange(self, 19, 26, v);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        SetColorRange(self, 12, 26, 0xFFFFFFFF);
        self->state = 8;
    }
}

extern "C" void fn_801F1BC8(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 6, 12, lbl_806DA550);
    DrawRange(self, 12, 19, lbl_806DA550);
}

extern "C" void fn_801F1C58(Menu801F *self) {
    int offset;
    int i;
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Pressed(0x10) == 1) self->selection = 0;
    else if (input->Pressed(0x20) == 1) self->selection = 1;
    fn_801F6F7C(&self->sprites[18], &menuSelectRects[self->selection], lbl_806DA568);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 255, 0, 22);
        SetColorRange(self, 0, 6, 0xFFFFFF00);
        self->state = 3;
    }
    if (input->Pressed(0x100) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        SetColorRange(self, 19, 26, 0xFFFFFF00);
        SetOption(self);
        self->state = 6;
    }
}

extern "C" void fn_801F1EE0(Menu801F *self) {
    unsigned int c;
    int offset;
    int i;
    unsigned int v = fn_8020A788(self->fade.p);
    c = (v << 24) | ((v & 255) << 16) | ((v & 255) << 8) | 255;
    i = 6;
    offset = 0x378;
    for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        i = 6;
        offset = 0x378;
        for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        StrPcb_RunAndWaitIdle(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        self->state = 5;
        clCGameDemoWC_StubBlr_800adda8(2);
    }
}

extern "C" void fn_801F1FE4(Menu801F *self) {
    int offset;
    int i;
    DrawRange(self, 6, 12, lbl_806DA550);
    DrawRange(self, 12, 19, lbl_806DA550);
    DrawRange(self, 0, 6, lbl_806DA550);
}

extern "C" void fn_801F20A0(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    SetColorRange(self, 0, 6, c);
    SetAlphaRange(self, 12, 19, v);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        SetColorRange(self, 0, 6, 0xFFFFFFFF);
        SetColorRange(self, 12, 19, 0xFFFFFF00);
        self->state = 1;
    }
}

extern "C" void fn_801F21C8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, v);
    SetColorRange(self, 0, 6, c);
    SetAlphaRange(self, 12, 19, (unsigned char)(255 - v));
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        SetColorRange(self, 0, 6, 0xFFFFFF00);
        SetColorRange(self, 12, 19, 0xFFFFFFFF);
        StrPcb_RunAndWaitIdle(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        self->state = 5;
        clCGameDemoWC_StubBlr_800adda8(2);
    }
}

static inline void DrawSprites6(Menu801F *self) {
    for (int i = 0; i < 6; i++) fn_801F7B74(self->context, &self->sprites[i], lbl_806DA550);
}
/* The loop sits in an inline helper: only an inlined loop gets the target's
 * `mr rOff, rI` strength-reduction init (see docs/archive/per_fn_matching_strategy.md). */
static inline void DrawFirstSprites(Menu801F *self) {
    for (int i = 0; i < 6; i++) fn_801F7B74(self->context, &self->sprites[i], lbl_806DA550);
}

extern "C" void fn_801F230C(Menu801F *self) {
    DrawFirstSprites(self);
}

extern "C" void fn_801F2370(Menu801F *self) {
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400)) {
        fn_8020A7CC(self->fade.p, 255, 0, 22);
        fn_801F6F7C(&self->sprites[18], &menuSelectRects[self->selection], lbl_806DA568);
        self->state = 2;
    }
}

extern "C" void fn_801F2400(Menu801F *self) {
    unsigned int c;
    int offset;
    int i;
    unsigned int v = fn_8020A788(self->fade.p);
    c = (v << 24) | ((v & 255) << 16) | ((v & 255) << 8) | 255;
    i = 0;
    offset = 0x0;
    for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        SetColorRange(self, 0, 6, 0xFFFFFFFF);
        self->state = 1;
    }
}

extern "C" void fn_801F24E8(Menu801F *self) {
    GX_EndDraw(0);
    PMF_CALL(self, lbl_804E51A0[self->state % 14])();
    GX_BeginDraw();
}

extern "C" void fn_801F2560(Menu801F *self) {
    PMF_CALL(self, lbl_804E5050[self->state % 14])();
}

Menu801F::~Menu801F() {
    delete[] sprites;
    fn_801F7CD8(context, 1);
}

extern "C" void fn_801F2690(FlowFaderI *self) { delete self; }

extern "C" {
extern void *FlowFaderI_vtable_804E5284[];
extern void *FlowFader_vtable_80419DC8[];
extern void MemoryManager_TimedFree(void *p);

static inline void BaseDtor(void **self) {
    if (self != 0) {
        *self = FlowFader_vtable_80419DC8;
    }
}

void **fn_801F26C8(void **self, short flag) {
    if (self != 0) {
        *self = FlowFaderI_vtable_804E5284;
        BaseDtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
}

/* Owning holder whose throw() destructor deletes the held object. */
class Owned801F2724 {
public:
    virtual ~Owned801F2724();
};

struct Holder801F2724 {
    Owned801F2724 *p;
    ~Holder801F2724() throw();
};

Holder801F2724::~Holder801F2724() throw() { delete p; }

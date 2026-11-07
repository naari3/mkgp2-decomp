#include "game/Menu801F0CC0_private.h"

static inline unsigned int MenuRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    return (r << 24) | ((g & 255) << 16) | ((b & 255) << 8) | (a & 255);
}

static inline unsigned int WithAlpha(unsigned int color, unsigned char alpha) {
    return __rlwimi(color, alpha, 0, 24, 31);
}

// Shared option artwork; inlined by both input handlers.
static inline void SetOption(Menu801F *self, char *table) {
    if (self->option == 0) {
        fn_801F6ED0(&self->sprites[20], lbl_806DA568, lbl_806DA568);
        fn_801F6ED0(&self->sprites[21], lbl_806DA56C, lbl_806DA56C);
        fn_801F6D58(&self->sprites[23], table + 0x1F0, 0, 0);
        fn_801F6D58(&self->sprites[24], table + 0x210, 0, 0);
        fn_801F6C2C(&self->sprites[25], table + 0x128 + 0x90, 1, 0);
    } else {
        fn_801F6ED0(&self->sprites[20], lbl_806DA56C, lbl_806DA56C);
        fn_801F6ED0(&self->sprites[21], lbl_806DA568, lbl_806DA568);
        fn_801F6D58(&self->sprites[23], table + 0x1F0 + 0x10, 0, 0);
        fn_801F6D58(&self->sprites[24], table + 0x210 + 0x10, 0, 0);
        fn_801F6C2C(&self->sprites[25], table + 0x128 + 0x90, 0, 0);
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
    {
        i = 26;
        offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 32;
        offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F0ECC(Menu801F *self) {
    char *table = lbl_804E4C28;
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
    fn_801F6D58(&self->sprites[32], &((MenuRect801F *)(table + 0x2B0))[self->level], 0, 0);
    fn_801F7040(&self->sprites[33], &((MenuRect801F *)(table + 0x240))[self->level], lbl_806DA568);
    fn_801F6D58(&self->sprites[34], &((MenuRect801F *)(table + 0x320))[self->level], 0, 0);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        {
            i = 6;
            offset = 0x378;
            for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            i = 19;
            offset = 0xafc;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
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
    {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 19;
        offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 26;
        offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 32;
        offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F1244(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = 0xFFFFFF00;
    c = WithAlpha(c, v);
    {
        int i = 6;
        int offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    {
        int i = 19;
        int offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = 0xFFFFFF00;
    d = WithAlpha(d, (unsigned char)(255 - v));
    {
        int i = 26;
        int offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    {
        int i = 32;
        int offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 6;
            int offset = 0x378;
            for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        {
            int i = 19;
            int offset = 0xafc;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        {
            int i = 26;
            int offset = 0xf08;
            for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            int i = 32;
            int offset = 0x1280;
            for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        self->state = 8;
    }
}

extern "C" void fn_801F140C(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = 0xFFFFFF00;
    c = WithAlpha(c, (unsigned char)(255 - v));
    {
        int i = 6;
        int offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    {
        int i = 19;
        int offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = 0xFFFFFF00;
    d = WithAlpha(d, v);
    {
        int i = 26;
        int offset = 0xf08;
        for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    {
        int i = 32;
        int offset = 0x1280;
        for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 6;
            int offset = 0x378;
            for (; i < 12; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            int i = 19;
            int offset = 0xafc;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            int i = 26;
            int offset = 0xf08;
            for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        {
            int i = 32;
            int offset = 0x1280;
            for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        self->state = 11;
    }
}

extern "C" void fn_801F15D4(Menu801F *self) {
    int offset;
    int i;
    {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 19;
        offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F1664(Menu801F *self) {
    char *table = lbl_804E4C28;
    int i;
    int offset;
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Pressed(0x10) == 1) self->option = 0;
    else if (input->Pressed(0x20) == 1) self->option = 1;
    SetOption(self, table);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        {
            i = 12;
            offset = 0x6f0;
            for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        self->state = 7;
    }
    if (input->Pressed(0x100) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        {
            i = 26;
            offset = 0xf08;
            for (; i < 32; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            i = 32;
            offset = 0x1280;
            for (; i < 35; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        self->state = 9;
    }
}

extern "C" void fn_801F190C(Menu801F *self) {
    int offset;
    int i;
    {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 19;
        offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 12;
        offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F19C8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, v);
    {
        int i = 12;
        int offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    {
        int i = 19;
        int offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 12;
            int offset = 0x6f0;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        self->state = 5;
    }
}

extern "C" void fn_801F1AC8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    {
        int i = 12;
        int offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = WithAlpha(0xFFFFFF00, v);
    {
        int i = 19;
        int offset = 0xafc;
        for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 12;
            int offset = 0x6f0;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        self->state = 8;
    }
}

extern "C" void fn_801F1BC8(Menu801F *self) {
    int offset;
    int i;
    {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 12;
        offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F1C58(Menu801F *self) {
    char *table = lbl_804E4C28;
    int offset;
    int i;
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Pressed(0x10) == 1) self->selection = 0;
    else if (input->Pressed(0x20) == 1) self->selection = 1;
    fn_801F6F7C(&self->sprites[18], &((MenuRect801F *)(table + 0x108))[self->selection], lbl_806DA568);
    if (input->Pressed(2) == 1) {
        fn_8020A7CC(self->fade.p, 255, 0, 22);
        {
            i = 0;
            offset = 0x0;
            for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        self->state = 3;
    }
    if (input->Pressed(0x100) == 1) {
        fn_8020A7CC(self->fade.p, 0, 255, 22);
        {
            i = 19;
            offset = 0xafc;
            for (; i < 26; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        SetOption(self, table);
        self->state = 6;
    }
}

extern "C" void fn_801F1EE0(Menu801F *self) {
    int offset;
    int i;
    unsigned int v = fn_8020A788(self->fade.p);
    unsigned int c = MenuRGBA(v, v, v, 255);
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
    {
        i = 6;
        offset = 0x378;
        for (; i < 12; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 12;
        offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
    {
        i = 0;
        offset = 0x0;
        for (; i < 6; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F20A0(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    {
        int i = 0;
        int offset = 0x0;
        for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = WithAlpha(0xFFFFFF00, v);
    {
        int i = 12;
        int offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 0;
            int offset = 0x0;
            for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            int i = 12;
            int offset = 0x6f0;
            for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        self->state = 1;
    }
}

extern "C" void fn_801F21C8(Menu801F *self) {
    unsigned char v = fn_8020A788(self->fade.p);
    unsigned int c = WithAlpha(0xFFFFFF00, v);
    {
        int i = 0;
        int offset = 0x0;
        for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    }
    unsigned int d = WithAlpha(0xFFFFFF00, (unsigned char)(255 - v));
    {
        int i = 12;
        int offset = 0x6f0;
        for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), d);
    }
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        {
            int i = 0;
            int offset = 0x0;
            for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFF00);
        }
        {
            int i = 12;
            int offset = 0x6f0;
            for (; i < 19; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        }
        StrPcb_RunAndWaitIdle(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        self->state = 5;
        clCGameDemoWC_StubBlr_800adda8(2);
    }
}

extern "C" void fn_801F230C(Menu801F *self) {
    int i;
    int offset;
    {
        i = 0;
        offset = 0x0;
        for (; i < 6; ++i, offset += 0x94) fn_801F7B74(self->context, (MenuSprite801F *)((char *)self->sprites + offset), lbl_806DA550);
    }
}

extern "C" void fn_801F2370(Menu801F *self) {
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400)) {
        fn_8020A7CC(self->fade.p, 255, 0, 22);
        fn_801F6F7C(&self->sprites[18], lbl_804E4D30 + self->selection * 16, lbl_806DA568);
        self->state = 2;
    }
}

extern "C" void fn_801F2400(Menu801F *self) {
    int offset;
    int i;
    unsigned int v = fn_8020A788(self->fade.p);
    unsigned int c = MenuRGBA(v, v, v, 255);
    i = 0;
    offset = 0x0;
    for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), c);
    self->fade.p->Step();
    if (self->fade.p->Done()) {
        i = 0;
        offset = 0x0;
        for (; i < 6; ++i, offset += 0x94) fn_801F6E98((MenuSprite801F *)((char *)self->sprites + offset), 0xFFFFFFFF);
        self->state = 1;
    }
}

extern "C" void fn_801F24E8(Menu801F *self) {
    GX_EndDraw(0);
    (self->*lbl_804E51A0[self->state % 14])();
    GX_BeginDraw();
}

extern "C" void fn_801F2560(Menu801F *self) {
    (self->*lbl_804E5050[self->state % 14])();
}

Menu801F::~Menu801F() {
    delete[] sprites;
    fn_801F7CD8(context, 1);
}

extern "C" void fn_801F2690(FlowFaderI *self) { delete self; }

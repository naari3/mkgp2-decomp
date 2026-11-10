/*
 * SeqMenuScene (debug sequence-select menu scene) @ 0x8002F9B4..0x8002FD4C.
 *
 * 4 fns, each its own singleton dtk reversed-extab group; contiguous, so
 * one TU covers all four plus their extab (0x80005880..0x800058A0) and
 * extabindex (0x8001F4CC..0x8001F4FC) ranges. All extab bodies are the
 * plain 8-byte "no cleanup" descriptors CW auto-emits under
 * -Cpp_exceptions on, so no manual .extab_user emit is needed.
 *
 * Compiled as C++ (-lang=c++, Vtable_CallSlot2.cpp precedent): the input
 * button polling in HandleInput is a real virtual call (both vtable loads
 * routed through r12: `lwz r12, 0x0(r3); lwz r12, 0x20(r12)`), which the
 * CW 1.3.2 C front end never emits from function-pointer chains (it picks
 * a scratch GPR for the vtable). Virtual slot +0x20 = 8-byte vtable
 * header + 6 preceding virtuals.
 *
 * Object layout (0x14 bytes):
 *   +0x00 vtable (SeqMenuScene_data_803F56A4)
 *   +0x04 MenuEntry *entries   (0xC-stride table, 0 field0 terminates)
 *   +0x08 int count
 *   +0x0C int cursor
 *   +0x10 int blink            (frame counter & 0x1F, cursor blink)
 *
 * MenuEntry layout (0xC bytes):
 *   +0x00 field0 (nonzero while valid; table terminator = 0)
 *   +0x04 char *label
 *   +0x09 u8 hidden (skip in draw / cursor never rests here)
 */

typedef struct MenuEntry {
    unsigned int field0;   /* 0x0 */
    char *label;           /* 0x4 */
    unsigned char pad8;    /* 0x8 */
    unsigned char hidden;  /* 0x9 */
} MenuEntry;

#include "game/types/SeqMenuScene.h"

/* Input player object: virtual button-state query at vtable +0x20. */
struct InputObject {
    virtual unsigned char vf08();
    virtual unsigned char vf0c();
    virtual unsigned char vf10();
    virtual unsigned char vf14();
    virtual unsigned char vf18();
    virtual unsigned char vf1c();
    virtual unsigned char checkButton(unsigned int mask); /* +0x20 */
};

extern "C" {

extern void DeadCounter_Set_806d0fb8(int);
extern void OverlayText(int, int, int, const char *, ...);
extern InputObject **GetInputManager(void);
extern InputObject *InputMgr_GetPlayer(InputObject **mgr, unsigned int playerIdx);
extern void GameMode_BaseInit(void *self);
extern void *dtor_8002CDF4(void *self, short flag);
extern void MemoryManager_TimedFree(void *);

extern char SeqMenuScene_data_803F56A4[];          /* SeqMenuScene vtable @ .data:0x803F56A4 */
extern const char lbl_806D22C8[8];   /* header string  @ .sdata2:0x806D22C8 */
extern const char lbl_806D22D0[3];   /* cursor string  @ .sdata2:0x806D22D0 */

void SeqMenuScene_DrawDebugList(SeqMenuScene *self) {
    short row;
    int i;

    DeadCounter_Set_806d0fb8(0x10);
    OverlayText(2, 1, 0, lbl_806D22C8);
    row = 6;
    for (i = 0; i < self->count; i++) {
        if (self->entries[i].hidden == 0) {
            OverlayText(2, 3, row, self->entries[i].label);
            if (self->blink < 0x18 && self->cursor == i) {
                OverlayText(2, 1, row, lbl_806D22D0);
            }
            row++;
        }
    }
    DeadCounter_Set_806d0fb8(0x10);
}

int SeqMenuScene_HandleInput(SeqMenuScene *self) {
    int dir;
    unsigned char decide;
    InputObject *p;

    dir = 0;
    decide = 0;
    self->blink = self->blink + 1;
    self->blink = self->blink & 0x1F;
    p = InputMgr_GetPlayer(GetInputManager(), 0);
    if (p->checkButton(0x40) == 1) {
        dir = -1;
    } else if (p->checkButton(0x80) == 1 || p->checkButton(0x800) == 1) {
        dir = 1;
    } else if (p->checkButton(0x401) == 1) {
        decide = 1;
    }

    if (decide == 1) {
        self->blink = 0;
        return self->cursor;
    }
    if (dir != 0) {
        do {
            self->cursor = self->cursor + dir;
            if (self->cursor < 0) {
                self->cursor = self->count - 1;
            } else if (self->cursor >= self->count) {
                self->cursor = 0;
            }
            self->blink = 0;
        } while (self->entries[self->cursor].hidden != 0);
    }
    return -2;
}

void *SeqMenuScene_Dtor(SeqMenuScene *self, short flag) {
    if (self != 0) {
        self->vtable = SeqMenuScene_data_803F56A4;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void *SeqMenuScene_Init(SeqMenuScene *self, MenuEntry *entries) {
    GameMode_BaseInit(self);
    self->vtable = SeqMenuScene_data_803F56A4;
    self->entries = entries;
    self->blink = 0;
    self->count = 0;
    while (self->entries[self->count].field0 != 0) {
        self->count++;
    }
    self->cursor = 0;
    for (;;) {
        if (self->entries[self->cursor].hidden == 0) break;
        self->cursor++;
        self->cursor %= self->count;
        self->blink = 0;
    }
    return self;
}

} /* extern "C" */

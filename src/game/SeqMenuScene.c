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
 *   +0x00 vtable (lbl_803F56A4)
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

typedef struct SeqMenuScene {
    char *vtable;       /* 0x00 */
    MenuEntry *entries; /* 0x04 */
    int count;          /* 0x08 */
    int cursor;         /* 0x0C */
    int blink;          /* 0x10 */
} SeqMenuScene;

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

extern char lbl_803F56A4[];          /* SeqMenuScene vtable @ .data:0x803F56A4 */
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
        self->vtable = lbl_803F56A4;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

/*
 * SeqMenuScene_Init: asm_fn retreat (99.22% best C attempt).
 *
 * Pseudo-C (verified against the asm below; everything except the second
 * loop's temp register identities was reproduced from this source):
 *
 *   void *SeqMenuScene_Init(SeqMenuScene *self, MenuEntry *entries) {
 *       GameMode_BaseInit(self);
 *       self->vtable = lbl_803F56A4;
 *       self->entries = entries;
 *       self->blink = 0;
 *       self->count = 0;
 *       while (self->entries[self->count].field0 != 0) {
 *           self->count++;
 *       }
 *       self->cursor = 0;
 *       while (self->entries[self->cursor].hidden != 0) {  // top-tested
 *           self->cursor = self->cursor + 1;
 *           self->cursor = self->cursor % self->count;
 *           self->blink = 0;
 *       }
 *       return self;
 *   }
 *
 * Residue: second loop's three volatile temp webs come out rotated one
 * register (mine zero=r5/cursor=r6/entries=r4 vs target r6/r4/r5).
 * Source-closed under while(1)+break / goto / do-while(1) / commuted
 * addressing / named-local home / one-home-per-variable / Init-only-TU
 * (7 probe builds, diff stagnant at the same 7 register-field bytes).
 * An inline asm island pin (Game_Shutdown.c precedent) also fails: the
 * island's hardcoded r0/r3-r6 get reserved function-wide, which shifts
 * loop1 temps to r7/r8 and swaps the self/entries callee-saved homes.
 * Register-identity-only residue -> park as asm_fn per strategy 14.2.
 */
asm void SeqMenuScene_Init(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    mr r30, r4
    bl GameMode_BaseInit
    lis r3, lbl_803F56A4@ha
    li r0, 0x0
    addi r3, r3, lbl_803F56A4@l
    stw r3, 0x0(r31)
    stw r30, 0x4(r31)
    stw r0, 0x10(r31)
    stw r0, 0x8(r31)
    b Init_L_8002FCCC
Init_L_8002FCC0:
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
Init_L_8002FCCC:
    lwz r0, 0x8(r31)
    lwz r3, 0x4(r31)
    mulli r0, r0, 0xc
    lwzx r0, r3, r0
    cmplwi r0, 0x0
    bne Init_L_8002FCC0
    li r6, 0x0
    stw r6, 0xc(r31)
Init_L_8002FCEC:
    lwz r4, 0xc(r31)
    lwz r5, 0x4(r31)
    mulli r3, r4, 0xc
    addi r0, r3, 0x9
    lbzx r0, r5, r0
    cmplwi r0, 0x0
    beq Init_L_8002FD30
    addi r0, r4, 0x1
    stw r0, 0xc(r31)
    lwz r4, 0xc(r31)
    lwz r3, 0x8(r31)
    divw r0, r4, r3
    mullw r0, r0, r3
    subf r0, r0, r4
    stw r0, 0xc(r31)
    stw r6, 0x10(r31)
    b Init_L_8002FCEC
Init_L_8002FD30:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/*
 * Manual extab/extabindex emit for the asm_fn (asm void fns never
 * auto-emit exception tables; CW links auto-emitted `extab` first, then
 * the renamed `.extab_user` sections, so the asm_fn being last in
 * address order keeps target layout). tools/postprocess_extab_user.py
 * renames the section + symbols to @etb_80005898 / @eti_8001F4F0 per
 * tools/extab_user_renames.json.
 */
#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned int extab_SeqMenuScene_Init[2] = {
    0x10080000, 0x00000000
};

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    const void *extab;
} extabindex_SeqMenuScene_Init = {
    (void *)&SeqMenuScene_Init, 0x000000CC, (const void *)&extab_SeqMenuScene_Init
};

} /* extern "C" */

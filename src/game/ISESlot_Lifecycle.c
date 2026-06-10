/*
 * ISESlot lifecycle trio @ 0x80049D78..0x80049EDC.
 *
 *   ISESlot_Init      @ 0x80049D78 (size 0xC8) — arm a slot. Refuses if
 *       already armed. For mode 6 the slot resolves a secondary race
 *       context slot via the +0x90 link index of the slot indexed by
 *       `b`; a negative link index aborts the init. On success fills
 *       the parameter fields, resets state to 5 and raises the armed
 *       flag.
 *   ISESlot_Dtor      @ 0x80049E40 (size 0x84) — deleting-dtor shaped
 *       teardown: same disarm sequence as ISESlot_Deactivate (notify
 *       the bound ItemObject with byte 2 unless type 0x51), then
 *       optionally MemoryManager_TimedFree(self) when the short flag
 *       is > 0. Returns self in r3.
 *   ISESlot_Construct @ 0x80049EC4 (size 0x18) — zero the pointer/flag
 *       fields (no extab entry, hence #pragma exceptions off).
 *
 * ISESlot layout (see also sound/ISESlot.c, game/ISESlot_Deactivate.c):
 *   +0x00 f32   timer/initial value (lbl_806D26C8 sdata2 const)
 *   +0x04 u8    armed/active flag
 *   +0x05 u8    cleanup-pending flag
 *   +0x08 s32   state (FrameUpdate dispatch; Init resets to 5)
 *   +0x0C s32   (Init zeroes)
 *   +0x10 s32   param `b` (mode-6: race context slot index)
 *   +0x14 s32   effect type id (0x51 compared in Dtor/Deactivate)
 *   +0x18 void* bound ItemObject handle
 *   +0x1C s32   param `a`
 *   +0x20 void* resolved race context slot (mode 6 only)
 *   size 0x24
 *
 * CW 1.3.2, -Cpp_exceptions on (extab pair auto-emitted for Init:
 * 0x280A0000 r27-r31, Dtor: 0x10080000 r30-r31), -use_lmw_stmw on
 * (Init prologue uses stmw r27/lmw r27).
 */

typedef struct ISESlot {
    float field_0x00;      /* +0x00 */
    unsigned char active;  /* +0x04 */
    unsigned char pending; /* +0x05 */
    unsigned char pad_0x06[2];
    int state;             /* +0x08 */
    int field_0x0c;        /* +0x0C */
    int field_0x10;        /* +0x10 */
    int typeId;            /* +0x14 */
    void *boundItem;       /* +0x18 */
    int field_0x1c;        /* +0x1C */
    void *ctxSlot;         /* +0x20 */
} ISESlot; /* size 0x24 */

extern void *GetRaceContextPtr(void);
extern void *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void ItemObject_SetByte18c(void *item, int val);
extern void MemoryManager_TimedFree(void *);
extern float lbl_806D26C8; /* sdata2 float const */

/*
 * ISESlot_Init is asm_fn: all 50 instructions are emitted identically by C
 * (see git history for the 98%-fuzzy C body), but CW 1.3.2's scheduler
 * interleaves the final li/lfs/stw constant-store block differently
 * (expected: li r5,0; lfs; li r4,5; stw 0x10; li r0,1; li r3,1 — generated
 * always hoists all li above the lfs). 3 source-order variants failed to
 * steer it, so the function is kept as asm with a manually emitted extab
 * pair (approach B); ISESlot_Dtor below stays plain C with CW auto-emit
 * (approach A). Mix is fine per docs/per_fn_matching_strategy.md §14.1.
 */
asm void ISESlot_Init(void);

void *ISESlot_Dtor(ISESlot *self, short freeFlag);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ISESlot_Init[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_ISESlot_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ISESlot_Init = {
    (void *)&ISESlot_Init, 0x000000C8, (void *)extab_ISESlot_Init
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ISESlot_Dtor = {
    (void *)&ISESlot_Dtor, 0x00000084, (void *)extab_ISESlot_Dtor
};

asm void ISESlot_Init(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r27, r3
    mr r28, r4
    mr r29, r6
    mr r30, r7
    lbz r0, 0x4(r3)
    cmplwi r0, 0x1
    bne ISESlot_Init_L_80049DAC
    li r3, 0x0
    b ISESlot_Init_L_80049E2C
    ISESlot_Init_L_80049DAC:
    li r0, 0x0
    cmpwi r5, 0x6
    stw r0, 0x18(r27)
    stb r0, 0x4(r27)
    bne ISESlot_Init_L_80049DF4
    bl GetRaceContextPtr
    mr r4, r29
    bl RaceContextSlot_GetIfAlive
    lwz r31, 0x90(r3)
    cmpwi r31, 0x0
    bge ISESlot_Init_L_80049DE0
    li r3, 0x0
    b ISESlot_Init_L_80049E2C
    ISESlot_Init_L_80049DE0:
    bl GetRaceContextPtr
    mr r4, r31
    bl RaceContextSlot_GetIfAlive
    stw r3, 0x20(r27)
    b ISESlot_Init_L_80049DF8
    ISESlot_Init_L_80049DF4:
    stw r0, 0x20(r27)
    ISESlot_Init_L_80049DF8:
    stw r28, 0x1c(r27)
    li r5, 0x0
    lfs f0, lbl_806D26C8(r2)
    li r4, 0x5
    stw r29, 0x10(r27)
    li r0, 0x1
    li r3, 0x1
    stw r30, 0x14(r27)
    stfs f0, 0x0(r27)
    stb r5, 0x5(r27)
    stw r4, 0x8(r27)
    stb r0, 0x4(r27)
    stw r5, 0xc(r27)
    ISESlot_Init_L_80049E2C:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

#pragma exceptions off
void *ISESlot_Dtor(ISESlot *self, short freeFlag) {
    if (self != 0) {
        if (self->active != 0) {
            if (self->typeId != 0x51 && self->boundItem != 0) {
                ItemObject_SetByte18c(self->boundItem, 2);
            }
            self->boundItem = 0;
            self->active = 0;
        }
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset

#pragma exceptions off
void ISESlot_Construct(ISESlot *self) {
    self->field_0x1c = 0;
    self->field_0x10 = 0;
    self->boundItem = 0;
    self->active = 0;
}
#pragma exceptions reset

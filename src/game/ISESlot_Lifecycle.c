/*
 * ISESlot lifecycle trio @ 0x80049D78..0x80049EDC.
 *
 *   ISESlot_Init      @ 0x80049D78 (size 0xC8) -- arm a slot. Refuses if
 *       already armed. For mode 6 the slot resolves a secondary race
 *       context slot via the +0x90 link index of the slot indexed by
 *       `b`; a negative link index aborts the init. On success fills
 *       the parameter fields, resets state to 5 and raises the armed
 *       flag.
 *   ISESlot_Dtor      @ 0x80049E40 (size 0x84) -- deleting-dtor shaped
 *       teardown: same disarm sequence as ISESlot_Deactivate (notify
 *       the bound ItemObject with byte 2 unless type 0x51), then
 *       optionally MemoryManager_TimedFree(self) when the short flag
 *       is > 0. Returns self in r3.
 *   ISESlot_Construct @ 0x80049EC4 (size 0x18) -- zero the pointer/flag
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

void *ISESlot_Dtor(ISESlot *self, short freeFlag);
typedef struct CoinJumpFlasher_Partial CoinJumpFlasher_Partial;
void CoinJumpFlasher_Toggle(CoinJumpFlasher_Partial *self);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ISESlot_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_CoinJumpFlasher_Toggle[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ISESlot_Dtor = {
    (void *)&ISESlot_Dtor, 0x00000084, (void *)extab_ISESlot_Dtor
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinJumpFlasher_Toggle = {
    (void *)&CoinJumpFlasher_Toggle, 0x00000058, (void *)extab_CoinJumpFlasher_Toggle
};

/* Literal zero is externalized to lbl_806D26C8 by postprocess_sdata2. */
int ISESlot_Init(ISESlot *self, int a, int mode, int b, int type) {
    if (self->active == 1) {
        return 0;
    }
    self->boundItem = 0;
    self->active = 0;
    if (mode == 6) {
        void *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), b);
        int index = *(int *)((char *)slot + 0x90);
        if (index < 0) {
            return 0;
        }
        self->ctxSlot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), index);
    } else {
        self->ctxSlot = 0;
    }
    self->field_0x1c = a;
    self->field_0x10 = b;
    self->typeId = type;
    self->field_0x00 = 0.0f;
    self->pending = 0;
    self->state = 5;
    self->active = 1;
    self->field_0x0c = 0;
    return 1;
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

struct CoinJumpFlasher_Partial {
    unsigned char pad_0x00[0x20];
    unsigned char armed;
    unsigned char pad_0x21[0x17];
    void *coinSystem;
    unsigned char pad_0x3c[0xc3];
    unsigned char togglePhase;
};

extern void FinalLapCoinJump_SetEnable(void *coinSystem, int enabled);

#pragma exceptions off
void CoinJumpFlasher_Toggle(CoinJumpFlasher_Partial *self) {
    if (self->armed != 0) {
        if (self->togglePhase == 1) {
            self->togglePhase = 0;
        } else {
            self->togglePhase = 1;
        }
        FinalLapCoinJump_SetEnable(self->coinSystem, self->togglePhase);
    }
}
#pragma exceptions reset

#pragma exceptions off
void CoinJumpFlasher_SetArmed(CoinJumpFlasher_Partial *self, unsigned char armed) {
    self->armed = armed;
}
#pragma exceptions reset

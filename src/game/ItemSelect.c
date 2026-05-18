/*
 * game/ItemSelect.c
 *
 * Player-side item-selection state: slot table helpers + lifecycle.
 *
 * Slot table (used by ItemSelect_GetSlotItemId, ItemSelect_AddSlotItem,
 * ItemSelect_Init):
 *
 *   struct SlotEntry {   // 8 bytes
 *       int field_0;     // +0x0  (unread in helpers; written by AddSlotItem
 *                        //         via next entry's "slot8")
 *       int itemId;      // +0x4  (compared / written)
 *   };
 *
 * The number of usable slots depends on a global mode flag at
 * lbl_806CF110 (sdata): when == 1, the loop bound is 4 (maxSlot=3);
 * otherwise the loop bound is 6 (maxSlot=5).
 *
 * Field offsets in the wider ItemSelect state object (the `self` arg of
 * Reset/Dtor/Init):
 *   +0x00     vtable / first slot entry
 *   +0x04..0x50  SlotEntry[N] (N=4 or 6, see above)
 *   +0x54..0x60  three -1 sentinels + three zero words (init-cleared block)
 *   +0x60     byte_0x60 (init to 0)
 *   +0x61     byte_0x61 (init to 1)
 *   +0x64..0x6C  three zero words
 *   +0x70     word_0x70 (init to -1)
 *   +0x74     word_0x74 (init to 0)
 *   +0x78     child object pointer (Alloc(0x44) result; freed in Dtor)
 *   +0x7C     mode byte (mirrors Init `mode` arg; controls PCB-sync side effects)
 *   +0x80     word_0x80 (init to 0; zeroed in Reset/Dtor on state==1)
 *
 * PCB-sync side effect (when self->mode == 1): if the corresponding
 * debounce-enable flag (lbl_80598A60+0x44 or +0x45) is 1, clear the
 * matching status bit (4 for slot44, 8 for slot45) on the StrPcb
 * singleton (fn_80038574 = StrPcb_GetInstance, fn_80038050 =
 * StrPcb_ClearStatusBits).
 *
 * The TU is wired as `extab_padding=b"\x00\x00"` + `extra_cflags=
 * ["-Cpp_exceptions on"]` because ItemSelect_Reset/Dtor/Init each have a
 * target extab/extabindex entry (Saved-GPR-range r30-r31 / r29-r31).
 * Reset and Dtor get auto-emitted by CW under `#pragma exceptions on`;
 * Init has a DELETEPOINTER PC action covering the post-Alloc /
 * fn_8023EA80 call site, which is not expressible in C, so its extab is
 * emitted manually via __declspec(section ".extab_user") + the
 * postprocess_extab_user.py rename hook (same pattern as
 * game/ServiceMenu.c).
 *
 * Function addresses / sizes (verified vs target asm):
 *   ItemSelect_GetSlotItemId @ 0x80060D40 (size 0x40)  no extab
 *   ItemSelect_AddSlotItem   @ 0x80060D80 (size 0x64)  no extab
 *   ItemSelect_Reset         @ 0x80060DE4 (size 0x98)  extab @0x80007DE8 (8B)
 *   ItemSelect_Dtor          @ 0x80060E7C (size 0xB0)  extab @0x80007DF0 (8B)
 *   ItemSelect_Init          @ 0x80060F2C (size 0x128) extab @0x80007DF8 (0x18B)
 */

typedef struct SlotEntry {
    int field_0;
    int itemId;
} SlotEntry;

extern int lbl_806CF110;
extern unsigned char lbl_80598A60[0x4A];

/* StrPcb-side helpers (renamed in Ghidra; not yet promoted in symbols.txt) */
extern void *fn_80038574(void);
extern void fn_80038050(void *pcb, int mask);

/* Heap / child-object helpers */
extern void *Alloc(int size);
extern void fn_8023E808(void *child, int flag);   /* child-obj free */
extern void fn_8023EA80(void *child, int mode);   /* child-obj init  */
extern void dtor_8003AFB8(void *self);            /* MemoryManager_TimedFree */

/* forward decl needed by manual extabindex emit for ItemSelect_Init */
void *ItemSelect_Init(void *self, void *vtable, int mode);

#pragma exceptions off

int ItemSelect_GetSlotItemId(SlotEntry *arr, int idx) {
    int maxSlot;
    if (idx <= -1) {
        maxSlot = (lbl_806CF110 == 1) ? 3 : 5;
        if (maxSlot + 1 <= idx) {
            return -1;
        }
    }
    return arr[idx].itemId;
}

int ItemSelect_AddSlotItem(SlotEntry *arr, int itemId, int slot8) {
    SlotEntry *cursor = arr;
    int mode = lbl_806CF110;
    int i = 0;
    while (i < ((mode == 1) ? 3 : 5) + 1) {
        if (cursor->itemId == 0) {
            arr[i].itemId = itemId;
            (&arr[i].itemId)[1] = slot8;
            return 1;
        }
        cursor++;
        i++;
    }
    return 0;
}

#pragma exceptions on

void ItemSelect_Reset(unsigned char *self, unsigned char newValue) {
    void *pcb;
    if (self[0x7c] == 1) {
        *(int *)(self + 0x80) = 0;
        if (self[0x7c] == 1) {
            if (lbl_80598A60[0x44] == 1) {
                pcb = fn_80038574();
                fn_80038050(pcb, 4);
            }
            if (lbl_80598A60[0x45] == 1) {
                pcb = fn_80038574();
                fn_80038050(pcb, 8);
            }
        }
    }
    self[0x7c] = newValue;
}

void *ItemSelect_Dtor(unsigned char *self, short freeSelf) {
    void *pcb;
    if (self != 0) {
        fn_8023E808(*(void **)(self + 0x78), 1);
        *(int *)(self + 0x78) = 0;
        *(int *)(self + 0x80) = 0;
        if (self[0x7c] == 1) {
            if (lbl_80598A60[0x44] == 1) {
                pcb = fn_80038574();
                fn_80038050(pcb, 4);
            }
            if (lbl_80598A60[0x45] == 1) {
                pcb = fn_80038574();
                fn_80038050(pcb, 8);
            }
        }
        if (freeSelf > 0) {
            dtor_8003AFB8(self);
        }
    }
    return self;
}

#pragma exceptions reset

/* --- ItemSelect_Init: manual extab emit (DELETEPOINTER cleanup) ---
 * Mirror of target @etb_80007DF8: size 0x18 with one DELETEPOINTER action
 * covering up to PC=0xAC (the bl fn_8023EA80 call site), destructor =
 * dtor_8003AFB8, pointer register = r29.
 *
 * Header word 0x18080000:
 *   - 1 PC range (action count)
 *   - r29..r31 saved-GPR range (bit pattern 0x18 in upper nibble?)
 *   - Large Frame
 * Action word 0x8A80001D:
 *   - Type DELETEPOINTER + end bit
 *   - Pointer source register r29 (bits 0..4 = 0x1D mod ... encoded form)
 * (Encoding read directly from auto_ItemSelect_Init_text.s; do not modify.)
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_ItemSelect_Init = {
    0x18080000, 0x000000AC, 0x00000010, 0x00000000, 0x8A80001D, (void *)&dtor_8003AFB8
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ItemSelect_Init = {
    (void *)&ItemSelect_Init, 0x00000128, (void *)&extab_ItemSelect_Init
};

/* ItemSelect_Init: asm_fn retreat after 3 C attempts diverged on
 * callee-save register allocation (CW132 assigned mode -> r29 + child ->
 * r30; target wants mode -> r30 + child -> r29). The decl-order /
 * inner-block / explicit-local_mode workarounds all reproduced the
 * swapped pattern, suggesting CW's allocator picks the swap based on
 * something we cannot reach from the C surface.
 *
 * The function body is copied verbatim from
 * build/GNLJ82/asm/auto_ItemSelect_Init_text.s. extab/extabindex are
 * emitted manually above (no #pragma exceptions on/off needed for the
 * asm_fn body itself; the manual emit covers it). */
asm void *ItemSelect_Init(void *self, void *vtable, int mode) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r6, 0x0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r5
    mr r5, r31
    stw r29, 0x14(r1)
    stw r4, 0x0(r3)
    li r4, 0x0
    b ItemSelect_Init_L_80060F6C
ItemSelect_Init_L_80060F60:
    stw r4, 0x4(r5)
    addi r5, r5, 0x8
    addi r6, r6, 0x1
ItemSelect_Init_L_80060F6C:
    lwz r0, lbl_806CF110(r13)
    li r3, 0x5
    cmpwi r0, 0x1
    bne ItemSelect_Init_L_80060F80
    li r3, 0x3
ItemSelect_Init_L_80060F80:
    addi r0, r3, 0x1
    cmpw r6, r0
    blt ItemSelect_Init_L_80060F60
    li r5, -0x1
    li r4, 0x0
    stw r5, 0x54(r31)
    li r0, 0x1
    li r3, 0x44
    stw r5, 0x58(r31)
    stw r5, 0x5c(r31)
    stw r4, 0x64(r31)
    stw r4, 0x68(r31)
    stw r4, 0x6c(r31)
    stb r0, 0x61(r31)
    stb r4, 0x60(r31)
    stw r4, 0x74(r31)
    stw r5, 0x70(r31)
    bl Alloc
    mr. r29, r3
    beq ItemSelect_Init_L_80060FD8
    mr r4, r30
    bl fn_8023EA80
ItemSelect_Init_L_80060FD8:
    stw r29, 0x78(r31)
    li r0, 0x0
    stb r30, 0x7c(r31)
    stw r0, 0x80(r31)
    lbz r0, 0x7c(r31)
    cmplwi r0, 0x1
    bne ItemSelect_Init_L_80061034
    lis r3, lbl_80598A60@ha
    addi r3, r3, lbl_80598A60@l
    lbz r0, 0x44(r3)
    cmplwi r0, 0x1
    bne ItemSelect_Init_L_80061014
    bl fn_80038574
    li r4, 0x4
    bl fn_80038050
ItemSelect_Init_L_80061014:
    lis r3, lbl_80598A60@ha
    addi r3, r3, lbl_80598A60@l
    lbz r0, 0x45(r3)
    cmplwi r0, 0x1
    bne ItemSelect_Init_L_80061034
    bl fn_80038574
    li r4, 0x8
    bl fn_80038050
ItemSelect_Init_L_80061034:
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

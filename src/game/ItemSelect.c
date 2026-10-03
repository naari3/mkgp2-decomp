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
 * singleton (StrPcb_GetInstance = StrPcb_GetInstance, StrPcb_ClearStatusBits =
 * StrPcb_ClearStatusBits).
 *
 * The TU is wired as `extab_padding=b"\x00\x00"` + `extra_cflags=
 * ["-Cpp_exceptions on"]` because ItemSelect_Reset/Dtor/Init each have a
 * target extab/extabindex entry (Saved-GPR-range r30-r31 / r29-r31).
 * All three tables are compiler-generated. Init uses a C++ island and
 * a genuine child new expression, with TU-local symbol bridges for the
 * observed constructor and allocator ABI. Its DELETEPOINTER action
 * covers constructor failure without manually encoding exception data.
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
extern void *StrPcb_GetInstance(void);
extern void StrPcb_ClearStatusBits(void *pcb, int mask);

/* Heap / child-object helpers */
extern void *Alloc(int size);
extern void fn_8023E808(void *child, int flag);   /* child-obj free */
extern void fn_8023EA80(void *child, int mode);   /* child-obj init  */
extern void MemoryManager_TimedFree(void *self);            /* MemoryManager_TimedFree */

/* Init retains the ordinary three-argument C ABI. */
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
                pcb = StrPcb_GetInstance();
                StrPcb_ClearStatusBits(pcb, 4);
            }
            if (lbl_80598A60[0x45] == 1) {
                pcb = StrPcb_GetInstance();
                StrPcb_ClearStatusBits(pcb, 8);
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
                pcb = StrPcb_GetInstance();
                StrPcb_ClearStatusBits(pcb, 4);
            }
            if (lbl_80598A60[0x45] == 1) {
                pcb = StrPcb_GetInstance();
                StrPcb_ClearStatusBits(pcb, 8);
            }
        }
        if (freeSelf > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset

/* The child constructor's observed ABI is (self, mode), and its layout
 * reaches +0x40. A real new expression supplies allocation-failure cleanup. */
#pragma cplusplus on
#pragma exceptions on
class ItemSelectChild {
    unsigned char storage[0x44];
public:
    ItemSelectChild(int mode);
};

extern "C" void *ItemSelect_Init(void *selfArg, void *vtable, int mode) {
    unsigned char *self = (unsigned char *)selfArg;
    SlotEntry *cursor = (SlotEntry *)self;
    int i = 0;
    *(void **)self = vtable;
    while (i < ((lbl_806CF110 == 1) ? 3 : 5) + 1) {
        cursor->itemId = 0;
        cursor++;
        i++;
    }
    *(int *)(self + 0x54) = -1;
    *(int *)(self + 0x58) = -1;
    *(int *)(self + 0x5c) = -1;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    self[0x61] = 1;
    self[0x60] = 0;
    *(int *)(self + 0x74) = 0;
    *(int *)(self + 0x70) = -1;
    *(ItemSelectChild **)(self + 0x78) = new ItemSelectChild(mode);
    self[0x7c] = mode;
    *(int *)(self + 0x80) = 0;
    if (self[0x7c] == 1) {
        if (lbl_80598A60[0x44] == 1) {
            StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
        }
        if (lbl_80598A60[0x45] == 1) {
            StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
        }
    }
    return self;
}
#pragma cplusplus off

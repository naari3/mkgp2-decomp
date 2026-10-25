/* ItemHolder_Init (0x801E8FB8): ItemHolder ctor. The base ctor (vtable lbl_804E4AF0) binds the
 * race slot whose owner id matches; the derived ctor installs vtable lbl_804E4B44.
 * __ct__10ItemHolderFUiiii is renamed to ItemHolder_Init via tools/extab_user_renames.json. */

extern "C" void *GetRaceContextPtr(void);
extern "C" char *RaceContextSlot_GetIfAlive(void *ctx, int slot);
extern "C" char lbl_804E4AF0[];
extern "C" char lbl_804E4B44[];

struct HolderBase {
    void *vt; unsigned int owner; int x8; int xC; int x10; int slot; int x18; int x1C; int x20; int x24; int x28;
    HolderBase(unsigned int o, int a, int b, int c) {
        vt = lbl_804E4AF0; owner = o; x8 = a; xC = b; x10 = c; x18 = -1; x1C = 0; x20 = 0; x28 = 0; x24 = 0;
        for (int i = 0; i < 0x80; i++) {
            char *p = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
            if (p != 0 && *(unsigned int *)(p + 0xB4) == o) { slot = i; break; }
        }
    }
};
struct ItemHolder : HolderBase {
    ItemHolder(unsigned int o, int a, int b, int c);
};

#pragma exceptions on
ItemHolder::ItemHolder(unsigned int o, int a, int b, int c) : HolderBase(o, a, b, c) { vt = lbl_804E4B44; }
#pragma exceptions reset

// Ownership-dependent item aliases. Tables remain owned by the original data TU.
struct Items { unsigned char pad[0xB4]; unsigned char slots[60]; unsigned char aliases[104]; };
struct AliasRow { int source; int ownedIndex; int result; };
struct PlayerView { unsigned char pad[0x1B8]; signed char character; };
extern "C" {
extern int lbl_803159B8[60];
extern AliasRow lbl_80315AA8[104];
extern int *lbl_803FED28[6];
extern PlayerView g_playerData;
int ItemAlias_DestToSource(int, unsigned char*);
}
static inline int OwnedAlias(Items* self, const AliasRow* row, int item) {
    if (row->source == item && self->aliases[row->ownedIndex] == 1) return row->result;
    return -1;
}
static inline int Resolve(Items* self, int slot) {
    if (slot < 0 || (unsigned int)slot >= 60) return 0;
    const AliasRow* row;
    int item = lbl_803159B8[slot];
    int i;
    if (item >= 0x115 && item <= 0x11A) {
        item -= 0x115;
        item = lbl_803FED28[item][g_playerData.character];
    }
    row = lbl_80315AA8;
    for (i = 0; i < 104; ++i) {
        int alias = OwnedAlias(self, row, item);
        if (alias >= 0) { item = alias; break; }
        ++row;
    }
    return item;
}
extern "C" int Items_ResolveOwnedAlias(Items* self, int slot) {
    if (slot < 0 || (unsigned int)slot >= 60) return 0;
    const AliasRow* row;
    int item = lbl_803159B8[slot];
    int i;
    if (item >= 0x115 && item <= 0x11A) {
        item -= 0x115;
        item = lbl_803FED28[item][g_playerData.character];
    }
    row = lbl_80315AA8;
    for (i = 0; i < 104; ++i) {
        int alias = OwnedAlias(self, row, item);
        if (alias >= 0) { item = alias; break; }
        ++row;
    }
    return item;
}
extern "C" unsigned char Items_PlayerOwnsAnyAlias(Items* self, int wanted, unsigned char aliasMode) {
    signed char wantedFlag = 0;
    int wantedSource = ItemAlias_DestToSource((unsigned char)wanted, (unsigned char*)&wantedFlag);
    for (int i = 0; i < 60; ++i) {
        if (self->slots[i] == 1) {
            int resolved = Resolve(self, i);
            unsigned char found = 0;
            if (0 == aliasMode) { if (wanted == resolved) found = 1; }
            else {
                signed char resolvedFlag = 0;
                int source = ItemAlias_DestToSource((unsigned char)resolved, (unsigned char*)&resolvedFlag);
                if (source == wantedSource) {
                    if (1 == resolvedFlag && (signed char)wantedFlag == 0) found = 1;
                    else if ((signed char)resolvedFlag == 0 && (signed char)0 == wantedFlag) found = 1;
                    else if ((signed char)1 == resolvedFlag && wantedFlag == 1) found = 1;
                }
                if (0x3F == wanted && 0x3D == source) found = 1;
                if (0x3A == wanted && source == 0x39) found = 1;
                if (0x33 == wanted && 0x32 == source) found = 1;
            }
            if (found == 1) return 1;
        }
    }
    return 0;
}

#ifndef GAME_ITEMSELECTALLOWED_PRIVATE_H
#define GAME_ITEMSELECTALLOWED_PRIVATE_H
/* The original rodata block combines eight cups, four rounds, three slots,
 * the default slot IDs, and two diagnostic format strings. */
struct ItemSelectionDefaults { int values[3]; };
extern int g_cupId, g_roundIndex;
extern unsigned char lbl_806D1264[3], lbl_806D12AD;
extern unsigned char g_playerData[];
extern unsigned char fn_801D6F30(void *, int, int);
extern void DebugPrintf(const char *, ...);

static inline unsigned char IsSpecialItemRound(void) {
    if (g_roundIndex == 3 || g_roundIndex == 7) return 1;
    if (g_cupId == 5) return 1;
    if (g_cupId == 6 && (g_roundIndex == 0 || g_roundIndex == 4)) return 1;
    return 0;
}
static inline int SelectRoundItem(const int (*table)[4][3], int cup, int round, int slot) {
    int item, replacement, c, r;
    if (cup < 1 || cup > 8) return 0x3D;
    if (round < 0 || round > 7) return 0x3D;
    c = cup - 1;
    r = round;
    if (round >= 4) r = round - 4;
    item = table[c][r][slot];
    if (lbl_806D12AD == 1) {
        void *player = g_playerData;
        replacement = 0;
        if (item == 0x39) replacement = 0x3A;
        else if (item == 0x32) replacement = 0x33;
        else if (item == 0x3D) replacement = 0x3F;
        if (replacement != 0 && fn_801D6F30(player, replacement, 0) == 1)
            item = replacement;
    }
    return item;
}
#endif

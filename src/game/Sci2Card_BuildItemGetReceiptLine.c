#include "game/Sci2CardItemReceiptPrivate.h"

static inline int Receipt_ItemClass(int item)
{
    signed char alias;
    int source = ItemAlias_DestToSource(item, (unsigned char *)&alias);
    int i;
    for (i = 0; i < 67; i++) {
        if (source == lbl_80317E00[i]) return (signed char)alias;
    }
    if (alias == 1) return 2;
    return -1;
}
static inline unsigned char Receipt_IsSpecialItem(int item)
{
    int i;
    for (i = 0; i < 12; i++) {
        if (item == lbl_80317F0C[i]) return 1;
    }
    return 0;
}
char *Sci2Card_BuildItemGetReceiptLine(void)
{
    ItemReceiptTables *tables = &lbl_803FFDF0;
    int count = fn_801D5E80(&g_playerData);
    unsigned char extra;
    const char *ones;
    const char *tens;
    const char *hundreds;
    ReceiptPlayer *player = &g_playerData;
    unsigned char ordinary;
    unsigned char special;
    int remaining;
    if (count >= fn_801D5DE8(&g_playerData)) {
        if (isJapanese() == 0) return (char *)tables->english[6];
        else return (char *)tables->japanese[6];
    }
    extra = fn_801D5F40(player);
    ordinary = 0;
    special = 0;
    remaining = fn_801D5DE8(player) - count;
    if (player->item != 0x7F) {
        int itemClass = Receipt_ItemClass(g_playerData.item);
        if (itemClass >= 0 && itemClass <= 1) ordinary = 1;
        if (Receipt_IsSpecialItem(player->item) == 1) special = 1;
    }
    memset(lbl_805AC5A4, 0, 64);
    if (count / 100 == 0) hundreds = lbl_806D35E4;
    else hundreds = tables->digits[count / 100];
    if (count < 10) tens = lbl_806D35D4;
    else tens = tables->digits[(count / 10) % 10];
    if (count <= 0) ones = lbl_806D35D4;
    else ones = tables->digits[count % 10];
    if (g_playerData.cardVersion >= 49 && extra == 1) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[2], hundreds, tens, ones);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[2], hundreds, tens, ones);
        }
    }
    else if (g_playerData.cardVersion >= 49 && count == 14) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[1], hundreds, tens, ones);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[1], hundreds, tens, ones);
        }
    }
    else if (ordinary == 1) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[4], hundreds, tens, ones);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[4], hundreds, tens, ones);
        }
    }
    else if (special == 1) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[7], hundreds, tens, ones);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[7], hundreds, tens, ones);
        }
    }
    else if (remaining <= 5) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[5], hundreds, tens, ones, tables->digits[remaining]);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[5], hundreds, tens, ones, tables->digits[remaining]);
        }
    }
    else if (1) {
        if (isJapanese() == 0) {
            sprintf(lbl_805AC5A4, tables->english[0], hundreds, tens, ones);
        } else {
            sprintf(lbl_805AC5A4, tables->japanese[0], hundreds, tens, ones);
        }
    }
    return lbl_805AC5A4;
}

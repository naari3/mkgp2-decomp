#include "game/Sci2CardItemReceiptPrivate.h"

/* Digit glyphs followed by the English and Japanese receipt formats. */
extern const char lbl_806D3594[];
extern const char lbl_806D3598[];
extern const char lbl_806D359C[];
extern const char lbl_806D35A0[];
extern const char lbl_806D35A4[];
extern const char lbl_806D35A8[];
extern const char lbl_806D35AC[];
extern const char lbl_806D35B0[];
extern const char lbl_806D35B4[];
extern const char lbl_806D35B8[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317F3C[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317F58[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317F74[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317F90[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317FAC[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317FC8[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80317FE4[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_80318000[];
extern const char lbl_8031801C[];
extern const char lbl_80318038[];
extern const char lbl_80318054[];
extern const char lbl_80318070[];
extern const char lbl_8031808C[];
extern const char lbl_803180A8[];
extern const char Sci2Card_BuildRetryReceiptLine_rodata_803180C4[];
extern const char lbl_803180E0[];
const char *Sci2Card_BuildRetryReceiptLine_data_803FFDF0[10] = {
    lbl_806D3594, lbl_806D3598, lbl_806D359C, lbl_806D35A0, lbl_806D35A4, lbl_806D35A8, lbl_806D35AC, lbl_806D35B0, lbl_806D35B4, lbl_806D35B8
};
static const char *receiptEnglish[8] = {
    Sci2Card_BuildRetryReceiptLine_rodata_80317F3C, Sci2Card_BuildRetryReceiptLine_rodata_80317F58, Sci2Card_BuildRetryReceiptLine_rodata_80317F74, Sci2Card_BuildRetryReceiptLine_rodata_80317F90, Sci2Card_BuildRetryReceiptLine_rodata_80317FAC, Sci2Card_BuildRetryReceiptLine_rodata_80317FC8, Sci2Card_BuildRetryReceiptLine_rodata_80317FE4, Sci2Card_BuildRetryReceiptLine_rodata_80318000
};
static const char *receiptJapanese[8] = {
    lbl_8031801C, lbl_80318038, lbl_80318054, lbl_80318070, lbl_8031808C, lbl_803180A8, Sci2Card_BuildRetryReceiptLine_rodata_803180C4, lbl_803180E0
};


static inline int Receipt_ItemClass(int item)
{
    signed char alias;
    int source = ItemAlias_DestToSource(item, (unsigned char *)&alias);
    int i;
    for (i = 0; i < 67; i++) {
        if (source == Sci2Card_BuildItemGetReceiptLine_rodata_80317E00[i]) return (signed char)alias;
    }
    if (alias == 1) return 2;
    return -1;
}
static inline unsigned char Receipt_IsSpecialItem(int item)
{
    int i;
    for (i = 0; i < 12; i++) {
        if (item == Sci2Card_BuildItemGetReceiptLine_rodata_80317F0C[i]) return 1;
    }
    return 0;
}
static inline int Sub_i(int a, int b) { return a - b; }
static inline int SubL_i(int a, int b) { return Sub_i(a, b); }
char *Sci2Card_BuildItemGetReceiptLine(void)
{
    const char *hundreds;
    const char *tens;
    const char *ones;
    ReceiptPlayer *player = &g_playerData;
    unsigned char extra;
    int count = fn_801D5E80(player);
    unsigned char special;
    unsigned char ordinary;
    int remaining;
    if (count >= fn_801D5DE8(&g_playerData)) {
        if (isJapanese() == 0) return (char *)receiptEnglish[6];
        else return (char *)receiptJapanese[6];
    }
    extra = fn_801D5F40(player);
    ordinary = 0;
    special = 0;
    remaining = SubL_i(fn_801D5DE8(player), count);
    if (player->item != 0x7F) {
        int itemClass = Receipt_ItemClass(g_playerData.item);
        if (itemClass >= 0 && itemClass <= 1) ordinary = 1;
        if (Receipt_IsSpecialItem(player->item) == 1) special = 1;
    }
    memset(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, 0, 64);
    if (count / 100 == 0) hundreds = lbl_806D35E4;
    else hundreds = Sci2Card_BuildRetryReceiptLine_data_803FFDF0[count / 100];
    if (count < 10) tens = lbl_806D35D4;
    else tens = Sci2Card_BuildRetryReceiptLine_data_803FFDF0[(count / 10) % 10];
    if (count <= 0) ones = lbl_806D35D4;
    else ones = Sci2Card_BuildRetryReceiptLine_data_803FFDF0[count % 10];
    if (g_playerData.cardVersion >= 49 && extra == 1) {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[2], hundreds, tens, ones);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[2], hundreds, tens, ones);
        }
    }
    else if (g_playerData.cardVersion >= 49 && count == 14) {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[1], hundreds, tens, ones);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[1], hundreds, tens, ones);
        }
    }
    else if (ordinary == 1) {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[4], hundreds, tens, ones);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[4], hundreds, tens, ones);
        }
    }
    else if (special == 1) {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[7], hundreds, tens, ones);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[7], hundreds, tens, ones);
        }
    }
    else if (remaining <= 5) {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[5], hundreds, tens, ones, Sci2Card_BuildRetryReceiptLine_data_803FFDF0[remaining]);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[5], hundreds, tens, ones, Sci2Card_BuildRetryReceiptLine_data_803FFDF0[remaining]);
        }
    }
    else {
        if (isJapanese() == 0) {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptEnglish[0], hundreds, tens, ones);
        } else {
            sprintf(Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4, receiptJapanese[0], hundreds, tens, ones);
        }
    }
    return Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4;
}

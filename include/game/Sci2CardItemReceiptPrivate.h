#ifndef SCI2CARD_ITEM_RECEIPT_PRIVATE_H
#define SCI2CARD_ITEM_RECEIPT_PRIVATE_H
/* Only the player fields consumed by receipt composition are known here. */
typedef struct ReceiptPlayer {
    unsigned char pad0[0xD];
    unsigned char item;
    unsigned char padE[0x198 - 0xE];
    signed char cardVersion;
} ReceiptPlayer;
extern ReceiptPlayer g_playerData;
extern const char *Sci2Card_BuildRetryReceiptLine_data_803FFDF0[10];
extern const int Sci2Card_BuildItemGetReceiptLine_rodata_80317E00[67];
extern const int Sci2Card_BuildItemGetReceiptLine_rodata_80317F0C[12];
extern char Sci2Card_BuildItemGetReceiptLine_bss_805AC5A4[64];
extern const char lbl_806D35D4[3];
extern const char lbl_806D35E4[4];
extern int fn_801D5E80(ReceiptPlayer *);
extern int fn_801D5DE8(ReceiptPlayer *);
extern unsigned char fn_801D5F40(ReceiptPlayer *);
extern int ItemAlias_DestToSource(int, unsigned char *);
extern int isJapanese(void);
extern void *memset(void *, int, unsigned long);
extern int sprintf(char *, const char *, ...);
#endif

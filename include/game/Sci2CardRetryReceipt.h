#ifndef GAME_SCI2CARDRETRYRECEIPT_H
#define GAME_SCI2CARDRETRYRECEIPT_H
#include "game/Sci2CardReceipt.h"
extern void *memset(void *, int, unsigned long);
extern int sprintf(char *, const char *, ...);
extern char *strcat(char *, const char *);
extern int isJapanese(void);
extern const char *Sci2Card_GetReceiptStringEntry(int);
extern void Sci2Card_SendCmdLedSet(void *, int, int);
extern void Sci2Card_SendCmdRegister(void *, char *, unsigned char, unsigned char, unsigned char);
extern const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317948[];
extern const char *Sci2Card_BuildRetryReceiptLine_data_803FFDF0[];
extern const char *Sci2Card_BuildRetryReceiptLine_data_806CF0F0[2];
extern unsigned char lbl_806D1225;
extern char Sci2Card_BuildRetryReceiptLine_bss_806D1230[7];
extern const char lbl_806D35BC[2], lbl_806D35C0[4], lbl_806D35C4[3];
extern const char lbl_806D35C8[7], lbl_806D35D0[4], lbl_806D35D4[3];
extern const char lbl_806D35D8[4], lbl_806D35DC[5];
typedef struct RetryReceiptFormat {
    const char *format;
    unsigned char rows;
    unsigned char reserved[3];
} RetryReceiptFormat;
#endif

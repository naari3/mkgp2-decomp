#ifndef GAME_CARD_RW_READ_WRITE_PAGE_PRIVATE_H
#define GAME_CARD_RW_READ_WRITE_PAGE_PRIVATE_H
#include "game/CardDataCheck_Private.h"
typedef unsigned char (*ReadWriteTick)();
struct ReadWriteStep { ReadWriteTick tick; unsigned char checkError; unsigned char pad[3]; };
struct ReadWritePage {
    unsigned char pad0[8];
    int blink;
    unsigned char padC[4];
    int next;
    unsigned char pad14[8];
    int selection;
    unsigned char pad20[12];
    int step;
    unsigned char pad30[0x2b];
    unsigned char failed;
    unsigned char pad5C[4];
    CardCheckData cardData;
    void *text;
    void *data;
    int field278;
    ReadWriteTick tick;
    int field280;
    int error;
};
extern "C" {
extern MenuItem CardRW_ReadWriteTest_Page_data_803FCA80[];
extern ReadWriteStep CardRW_ReadWriteTest_Page_data_803FDB98[];
void Backup_PublishShadowCopy_Inline();
void CardRW_TestTopMenu_Page(ReadWritePage *, int, int);
unsigned char CardRW_ErrorDisplay(ReadWritePage *, int, int, int);
int Sci2Card_GetPrintErrorCode();
void *Sci2Card_Singleton_Get();
void Sci2Card_GetResponseStatus(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted(void *);
unsigned char Sci2Card_IsStatus2Two(void *);
unsigned char Sci2Card_IsStatus2Three(void *);
unsigned char Sci2Card_IsStatus2Five(void *);
unsigned char Sci2Card_IsStatus2A(void *);
unsigned char Sci2Card_IsStatus3Five(void *);
}
static inline int ReadWrite_CheckError()
{
    int error = 1;
    void *card = Sci2Card_Singleton_Get();
    if (Sci2Card_IsRetryExhausted(card) == 1) error = 101;
    else if (Sci2Card_IsStatus2Two(card) == 1) error = 102;
    else if (Sci2Card_IsStatus2Three(card) == 1) error = 104;
    else if (Sci2Card_IsStatus2Five(card) == 1) error = 105;
    else if (Sci2Card_IsStatus2A(card) == 1) error = 106;
    else if (Sci2Card_IsStatus3Five(card) == 1) error = 2;
    return error;
}
static inline void ReadWrite_DrawItems(ReadWritePage *self, MenuItem *it, int sel)
{
    int i;
    for (i = 0; it[i].text != 0; i++) {
        if (i != sel || self->blink <= 30) {
            if (self->text != 0)
                DrawText(self->text, it[i].x * 14, it[i].y * 24, 7, 1.0f, it[i].text);
        }
    }
}
#endif

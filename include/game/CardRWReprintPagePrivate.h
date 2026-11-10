#ifndef GAME_CARD_RW_REPRINT_PAGE_PRIVATE_H
#define GAME_CARD_RW_REPRINT_PAGE_PRIVATE_H
#include "game/TestMenuPage.h"
typedef unsigned char (*ReprintTick)();
struct ReprintStep { ReprintTick tick; unsigned char checkError; unsigned char pad[3]; };
struct ReprintPage {
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
    unsigned char pad5C[0x214];
    void *text;
    unsigned char pad274[8];
    ReprintTick tick;
    int field280;
    int error;
};
extern "C" {
extern MenuItem CardRW_Reprint_Page_data_803FCCCC[];
extern ReprintStep CardRW_Reprint_Page_data_803FDD88[];
void CardRW_TestTopMenu_Page(ReprintPage *, int, int);
unsigned char CardRW_ErrorDisplay(ReprintPage *, int, int, int);
int Sci2Card_GetPrintErrorCode();
unsigned char Sci2Card_GetByteFlag1224();
void *Sci2Card_Singleton_Get();
void Sci2Card_GetResponseStatus(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted(void *);
unsigned char Sci2Card_IsStatus2Two(void *);
unsigned char Sci2Card_IsStatus2Three(void *);
unsigned char Sci2Card_IsStatus2Five(void *);
unsigned char Sci2Card_IsStatus2A(void *);
unsigned char Sci2Card_IsStatus3Five(void *);
}
static inline int Reprint_CheckError()
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
static inline void Reprint_DrawItems(ReprintPage *self, MenuItem *it, int sel)
{
    int i;
    for (i = 0; it[i].text != 0; i++) {
        if (i != sel || self->blink <= 30) {
            if (self->text != 0)
                DrawText(self->text, it[i].x * 14, it[i].y * 24, 7, 1.0f, it[i].text);
        }
    }
}
static inline unsigned char Reprint_HasFatalError(ReprintPage *self)
{
    int error = self->error;
    if (error == 1) return 0;
    if (self->text == 0) return 0;
    if (error == 101) return 1;
    if (error == 102) return 1;
    if (error == 104) return 1;
    if (error == 100) return 1;
    if (error == 105) return 1;
    if (error == 106) return 1;
    if (error == 2) return 1;
    if (error == 6) return 1;
    if (error == 7) return 1;
    if (error == 255) return 1;
    return 0;
}
#endif

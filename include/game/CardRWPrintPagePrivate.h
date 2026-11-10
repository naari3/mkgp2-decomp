#ifndef GAME_CARD_RW_PRINT_PAGE_PRIVATE_H
#define GAME_CARD_RW_PRINT_PAGE_PRIVATE_H
#include "game/TestMenuPage.h"
typedef unsigned char (*PrintTick)();
struct PrintStep { PrintTick tick; unsigned char checkError; unsigned char pad[3]; };
struct PrintPage {
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
    PrintTick tick;
    int field280;
    int error;
};
extern "C" {
extern MenuItem CardRW_PrintTest_Page_data_803FCB40[];
extern PrintStep CardRW_PrintTest_Page_data_803FDC18[];
void CardRW_TestTopMenu_Page(PrintPage *, int, int);
unsigned char CardRW_ErrorDisplay(PrintPage *, int, int, int);
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
static inline int Print_CheckError()
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
static inline void Print_DrawItems(PrintPage *self, MenuItem *it, int sel)
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

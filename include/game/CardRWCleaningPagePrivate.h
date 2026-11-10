#ifndef GAME_CARD_RW_CLEANING_PAGE_PRIVATE_H
#define GAME_CARD_RW_CLEANING_PAGE_PRIVATE_H
#include "game/TestMenuPage.h"
typedef unsigned char (*CleaningTick)();
struct CleaningStep {
    CleaningTick tick;
    unsigned char checkError;
    unsigned char pad[3];
};
struct CleaningPage {
    unsigned char pad0[8];
    int blink;
    unsigned char padC[4];
    int next;
    unsigned char pad14[8];
    int selection;
    unsigned char pad20[12];
    int step;
    unsigned char pad30[0x240];
    void *text;
    unsigned char pad274[8];
    CleaningTick tick;
    int field280;
    int error;
};
extern "C" {
extern MenuItem CardRW_CleaningTest_Page_data_803FCA20[];
extern CleaningStep CardRW_CleaningTest_Page_data_803FDB58[];
void Backup_PublishShadowCopy();
void Backup_PublishShadowCopy_Inline();
void CardRW_TestTopMenu_Page(CleaningPage *, int, int);
unsigned char CardRW_ErrorDisplay(CleaningPage *, int, int, int);
int Sci2Card_GetPrintErrorCode();
void *Sci2Card_Singleton_Get();
void Sci2Card_GetResponseStatus(void *, unsigned char *, unsigned char *, unsigned char *);
}
static inline void Cleaning_DrawItems(CleaningPage *self, MenuItem *it, int sel)
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

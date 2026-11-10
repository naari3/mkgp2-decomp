#ifndef GAME_CARD_RW_HARDWARE_INIT_PAGE_PRIVATE_H
#define GAME_CARD_RW_HARDWARE_INIT_PAGE_PRIVATE_H
#include "game/TestMenuPage.h"
struct HardwareInitPage {
    unsigned char pad0[8];
    int blink;
    unsigned char padC[4];
    int next;
    unsigned char pad14[8];
    int selection;
    unsigned char pad20[12];
    int step;
    int error;
    unsigned char pad34[0x23C];
    void *text;
    unsigned char pad274[8];
    int field27C;
};
extern "C" {
extern MenuItem CardRW_HardwareInit_Page_data_803FCD2C[];
extern char lbl_806D2DB4[5];
void CardRW_TestTopMenu_Page(HardwareInitPage *, int, int);
unsigned char CardRW_ErrorDisplay(HardwareInitPage *, int, int, int);
void *Sci2Card_Singleton_Get();
void Sci2Card_SendCmdRetry(void *, int);
unsigned char Sci2Card_IsIdleOrExhausted(void *);
unsigned char Sci2Card_IsStatusOkNonTerm(void *);
unsigned char Sci2Card_IsRetryExhausted(void *);
unsigned char Sci2Card_IsStatus2Two(void *);
unsigned char Sci2Card_IsStatus2Three(void *);
unsigned char Sci2Card_IsStatus2Five(void *);
unsigned char Sci2Card_IsStatus2A(void *);
unsigned char Sci2Card_IsStatus3Five(void *);
unsigned char CardPrintJob_KickFontTransfer();
unsigned char CardPrintJob_TickFontTransfer();
void Sci2Card_GetResponseStatus(void *, unsigned char *, unsigned char *, unsigned char *);
}
static inline void HardwareInit_DrawItems(HardwareInitPage *self, MenuItem *it, int sel)
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

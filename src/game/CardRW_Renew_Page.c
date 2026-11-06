/* Card reader renew test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/TestMenuPage.h"

typedef unsigned char (*RenewTick)();
struct RenewStep { RenewTick tick; unsigned char checkError; unsigned char pad[3]; };
struct RenewPage {
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
    RenewTick tick;
    int field280;
    int error;
};

/* Card renew counters inside the player data record. */
struct RenewCount {
    unsigned char remaining;
    unsigned char used;
};
struct RenewPlayerData {
    unsigned char pad0[0x198];
    RenewCount renew;
};

extern "C" {
extern RenewPlayerData g_playerData;
extern MenuItem lbl_803FCD8C[];
extern RenewStep lbl_803FDDD8[];
void CardRW_TestTopMenu_Page(RenewPage *, int, int);
unsigned char CardRW_ErrorDisplay(RenewPage *, int, int, int);
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

static inline int Renew_CheckError()
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

static inline void Renew_DrawItems(RenewPage *self, MenuItem *it, int sel)
{
    int i;
    for (i = 0; it[i].text != 0; i++) {
        if (i != sel || self->blink <= 30) {
            if (self->text != 0)
                DrawText(self->text, it[i].x * 14, it[i].y * 24, 7, 1.0f, it[i].text);
        }
    }
}

static inline unsigned char Renew_HasFatalError(RenewPage *self)
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

extern "C" int CardRW_Renew_Page(RenewPage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->tick = 0;
        self->error = 1;
        self->failed = 0;
    }
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->step == 0) {
            if (self->error == 1 && input->Pressed(0x800)) {
                self->blink = 31;
                if (++self->selection > 1) self->selection = 0;
            }
            if (input->Pressed(0x1000)) {
                if (self->selection == 0) {
                    self->selection = 100;
                    self->step = 1;
                    self->blink = 0;
                    self->tick = lbl_803FDDD8[self->step].tick;
                    self->error = 1;
                    self->failed = 0;
                    self->error = Renew_CheckError();
                    if (self->error != 1) {
                        self->failed = 1;
                        self->blink = 31;
                        self->step = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 9);
                }
            }
        } else {
            if (self->tick != 0) {
                if (self->tick() == 1) {
                    if (!self->failed && lbl_803FDDD8[self->step].checkError) {
                        self->error = Sci2Card_GetPrintErrorCode();
                        if (CardRW_ErrorDisplay(self, 0, 1, 1)) {
                            self->step = 12;
                            self->failed = 1;
                        }
                    }
                    if (self->step == 2 && !Sci2Card_GetByteFlag1224()) {
                        self->step = 0;
                        self->failed = 0;
                    }
                    if (self->step == 4) {
                        RenewCount *count = &g_playerData.renew;
                        count->remaining = 50;
                        count->used = 0;
                    }
                    ++self->step;
                    self->tick = lbl_803FDDD8[self->step].tick;
                }
                if (self->failed && Renew_HasFatalError(self)) self->blink = 31;
            } else {
                unsigned char leave = 1;
                if (CardRW_ErrorDisplay(self, 0, 1, 0) && !input->Pressed(0x1000)) leave = 0;
                if (!Renew_HasFatalError(self) || leave) {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 9);
                }
            }
        }
    }
    if (phase == 2) {
        Renew_DrawItems(self, lbl_803FCD8C, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 1) && self->text != 0) {
            switch (self->step) {
            case 1: case 2:
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x2024);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 312, 7, 1.0f, strings + 0x2038);
                break;
            case 3: case 4:
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x204c);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 312, 7, 1.0f, strings + 0x2064);
                break;
            case 5: case 6:
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x207c);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 312, 7, 1.0f, strings + 0x1c58);
                break;
            case 7: case 8: case 9: case 10: case 11: case 12:
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x2090);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 288, 7, 1.0f, strings + 0x2064);
                break;
            case 13: case 14:
                if (self->error == 1)
                    DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x20a4);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 288, 7, 1.0f, strings + 0x1c58);
                break;
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset

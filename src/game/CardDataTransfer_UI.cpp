/*
 * CardDataTransfer_UI @ 0x8006D308..0x8006DB90: the card data transfer
 * test page. Runs the step table at lbl_803FDC98 (one card R/W task per
 * step) and shows the reader/writer status or error. NonMatching: the
 * constant 1 for step/status is not shared with the status default in r30,
 * and the menu-table loop gets different registers.
 */
#include "game/TestMenuPage.h"

struct CardStep {
    unsigned char (*fn)(void);
    unsigned char checkError;
};

extern "C" {
extern MenuItem lbl_803FCC00[];
extern CardStep lbl_803FDC98[];
extern unsigned char g_playerData[];
void PlayerData_ResetForFlow(void);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_IsRetryExhausted(void *card);
unsigned char Sci2Card_IsStatus2Two(void *card);
unsigned char Sci2Card_IsStatus2Three(void *card);
unsigned char Sci2Card_IsStatus2Five(void *card);
unsigned char Sci2Card_IsStatus2A(void *card);
unsigned char Sci2Card_IsStatus3Five(void *card);
int Sci2Card_GetPrintErrorCode(void);
unsigned char Sci2Card_GetByteFlag1224(void);
void Sci2Card_GetResponseStatus(void *card, unsigned char *a, unsigned char *b, unsigned char *c);
unsigned char CardRW_ErrorDisplay(TestPage *self, int a, int b, int c);
int CardRW_TestTopMenu_Page(TestPage *self, int phase, int arg);
}

#define STEP(self) (*(int *)((char *)(self) + 0x2C))
#define STEP_FN(self) (*(unsigned char (**)(void))((char *)(self) + 0x27C))
#define STATUS(self) (*(int *)((char *)(self) + 0x284))
#define SHOWN(self) (*(unsigned char *)((char *)(self) + 0x5B))

static inline unsigned char CardDataTransfer_IsError(TestPage *self)
{
    int s = STATUS(self);

    if (s == 1) {
        return 0;
    }
    if (self->text == 0) {
        return 0;
    }
    if (s == 0x65) {
        return 1;
    }
    if (s == 0x66) {
        return 1;
    }
    if (s == 0x68) {
        return 1;
    }
    if (s == 0x64) {
        return 1;
    }
    if (s == 0x69) {
        return 1;
    }
    if (s == 0x6A) {
        return 1;
    }
    if (s == 2) {
        return 1;
    }
    if (s == 6) {
        return 1;
    }
    if (s == 7) {
        return 1;
    }
    if (s == 0xFF) {
        return 1;
    }
    return 0;
}

#pragma exceptions on

extern "C" int CardDataTransfer_UI(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    InputPlayer *pl;

    if (phase == 0) {
        self->sub = 1;
        STEP(self) = 0;
        STEP_FN(self) = 0;
        STATUS(self) = 1;
        SHOWN(self) = 0;
        PlayerData_ResetForFlow();
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (STEP(self) == 0) {
            if (STATUS(self) == 1 && pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->sub > 1) {
                    self->sub = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->sub == 0) {
                    void *card;
                    int st;

                    st = 1;
                    self->sub = 0x64;
                    STEP(self) = 1;
                    self->blink = 0;
                    STEP_FN(self) = lbl_803FDC98[STEP(self)].fn;
                    STATUS(self) = 1;
                    SHOWN(self) = 0;
                    card = Sci2Card_Singleton_Get();
                    if (Sci2Card_IsRetryExhausted(card) == 1) {
                        st = 0x65;
                    } else if (Sci2Card_IsStatus2Two(card) == 1) {
                        st = 0x66;
                    } else if (Sci2Card_IsStatus2Three(card) == 1) {
                        st = 0x68;
                    } else if (Sci2Card_IsStatus2Five(card) == 1) {
                        st = 0x69;
                    } else if (Sci2Card_IsStatus2A(card) == 1) {
                        st = 0x6A;
                    } else if (Sci2Card_IsStatus3Five(card) == 1) {
                        st = 2;
                    }
                    STATUS(self) = st;
                    if (STATUS(self) != 1) {
                        SHOWN(self) = 1;
                        self->blink = 0x1F;
                        STEP(self) = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 5);
                }
            }
        } else if (STEP_FN(self) != 0) {
            if (STEP_FN(self)() == 1) {
                if (SHOWN(self) == 0 && lbl_803FDC98[STEP(self)].checkError) {
                    STATUS(self) = Sci2Card_GetPrintErrorCode();
                    if (CardRW_ErrorDisplay(self, 0, 1, 1)) {
                        STEP(self) = 0x10;
                        SHOWN(self) = 1;
                    }
                }
                if (STEP(self) == 2 && !Sci2Card_GetByteFlag1224()) {
                    STEP(self) = 0;
                    SHOWN(self) = 0;
                }
                if (STEP(self) == 4) {
                    if (g_playerData[0x199] != 0) {
                        STEP(self) = 0x10;
                        STATUS(self) = 5;
                        SHOWN(self) = 1;
                    } else {
                        g_playerData[0x199] = 1;
                    }
                }
                if (STEP(self) == 8) {
                    g_playerData[0x199] = 0;
                }
                STEP(self)++;
                STEP_FN(self) = lbl_803FDC98[STEP(self)].fn;
            }
            if (SHOWN(self) && CardDataTransfer_IsError(self)) {
                self->blink = 0x1F;
            }
        } else {
            unsigned char done = 1;

            if (CardRW_ErrorDisplay(self, 0, 1, 0) && !pl->Pressed(0x1000)) {
                done = 0;
            }
            if (!CardDataTransfer_IsError(self) || done) {
                self->next = 5;
                CardRW_TestTopMenu_Page(self, 0, 5);
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FCC00, self->sub + 3);
        if (self->text != 0) {
            unsigned char c;
            unsigned char b;
            unsigned char a;

            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 0xA8, 0x48, 7, 1.0f, pool + 0x1C78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 1) && self->text != 0) {
            DrawText(self->text, 0x2A, 0x60, 4, 1.0f, pool + 0x21F0);
            DrawText(self->text, 0x2A, 0x78, 4, 1.0f, pool + 0x2214);
            DrawText(self->text, 0x2A, 0x90, 4, 1.0f, pool + 0x2238);
            switch (STEP(self)) {
            case 1:
            case 2:
                DrawText(self->text, 0x54, 0x108, 7, 1.0f, pool + 0x225C);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0x138, 7, 1.0f, pool + 0x2038);
                }
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                DrawText(self->text, 0x54, 0x108, 7, 1.0f, pool + 0x204C);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0x138, 7, 1.0f, pool + 0x2064);
                }
                break;
            case 9:
            case 10:
                DrawText(self->text, 0x54, 0x108, 7, 1.0f, pool + 0x207C);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0x138, 7, 1.0f, pool + 0x1C58);
                }
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                DrawText(self->text, 0x54, 0x108, 7, 1.0f, pool + 0x2090);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0x120, 7, 1.0f, pool + 0x2064);
                }
                break;
            case 17:
            case 18:
                if (STATUS(self) == 1) {
                    DrawText(self->text, 0x54, 0x108, 7, 1.0f, pool + 0x2278);
                }
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0x120, 7, 1.0f, pool + 0x1C58);
                }
                break;
            }
        }
    }
    return 1;
}

#pragma exceptions reset

/* CardDataCheck_UI @ 0x8006DB90: operator card-data check page.
 * The local drawing helper preserves the original cursor/index lifetimes. */
#include "game/CardDataCheck_Private.h"

extern "C" {
extern MenuItem lbl_803FCBA0[];
extern CardCheckStep lbl_803FDC58[];
extern unsigned char g_playerData[];
void fn_801D7610(void *, int);
void Backup_PublishShadowCopy_Inline(void);
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

static inline unsigned char CardDataCheck_IsError(TestPage *self)
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

static inline void CardDataCheck_DrawItems(TestPage *self)
{
    int i;
    int sel = self->sub + 3;
    MenuItem *it;

    for (it = lbl_803FCBA0, i = 0; it->text != 0; ++it, ++i) {
        if (i != sel || self->blink <= 0x1E) {
            if (self->text != 0) {
                DrawText(self->text, it->x * 14, it->y * 24, 7, 1.0f, it->text);
            }
        }
    }
}

#pragma exceptions on

extern "C" int CardDataCheck_UI(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    InputPlayer *pl;

    if (phase == 0) {
        self->sub = 1;
        STEP(self) = 0;
        STEP_FN(self) = 0;
        STATUS(self) = 1;
        CardCheckData *backup = CardCheck_BackupData(self);
        CardCheckData *page = CardCheck_PageData(self);
        page->enabled = backup->enabled;
        page->settings = backup->settings;
        page->records = backup->records;
        page->count = backup->count;
        page->flag = backup->flag;
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
                    int st;
                    void *card;
                    self->sub = 0x64;
                    STEP(self) = 1;
                    self->blink = 0;
                    STEP_FN(self) = lbl_803FDC58[STEP(self)].fn;
                    STATUS(self) = 1;
                    fn_801D7610(g_playerData, 1);
                    st = 1;
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
                    CardRW_TestTopMenu_Page(self, 0, 4);
                }
            }
        } else if (STEP_FN(self) != 0) {
            if (STEP_FN(self)() == 1) {
                if (lbl_803FDC58[STEP(self)].checkError) {
                    STATUS(self) = Sci2Card_GetPrintErrorCode();
                }
                if (STEP(self) == 2 && !Sci2Card_GetByteFlag1224()) {
                    STEP(self) = 0;
                }
                STEP(self)++;
                STEP_FN(self) = lbl_803FDC58[STEP(self)].fn;
            }
        } else {
            unsigned char done = 1;
            if (CardRW_ErrorDisplay(self, 0, 1, 0) && !pl->Pressed(0x1000)) {
                done = 0;
            }
            if (!CardDataCheck_IsError(self) || done) {
                CardCheckData *backup = CardCheck_BackupData(self);
                CardCheckData *page = CardCheck_PageData(self);
                backup->enabled = page->enabled;
                backup->settings = page->settings;
                backup->records = page->records;
                backup->count = page->count;
                backup->flag = page->flag;
                Backup_PublishShadowCopy_Inline();
                self->next = 5;
                CardRW_TestTopMenu_Page(self, 0, 4);
            }
        }
    }
    if (phase == 2) {
        CardDataCheck_DrawItems(self);
        if (self->text != 0) {
            unsigned char c;
            unsigned char b;
            unsigned char a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 0xA8, 0x48, 7, 1.0f, pool + 0x1C78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 1) && self->text != 0) {
            switch (STEP(self)) {
            case 1:
            case 2:
                DrawText(self->text, 0x54, 0xC0, 7, 1.0f, pool + 0x2290);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0xF0, 7, 1.0f, pool + 0x2038);
                }
                break;
            case 3:
            case 4:
                DrawText(self->text, 0x54, 0xC0, 7, 1.0f, pool + 0x22AC);
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0xF0, 7, 1.0f, pool + 0x2064);
                }
                break;
            case 5:
            case 6:
                if (g_playerData[0x1A0]) {
                    DrawText(self->text, 0x54, 0xC0, 7, 1.0f, pool + 0x22BC);
                } else if (g_playerData[0x199]) {
                    DrawText(self->text, 0x54, 0xC0, 7, 1.0f, pool + 0x22D8);
                } else {
                    DrawText(self->text, 0x54, 0xC0, 7, 1.0f, pool + 0x22F8);
                }
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x54, 0xF0, 7, 1.0f, pool + 0x1C58);
                }
                break;
            }
        }
    }
    return 1;
}

#pragma exceptions reset

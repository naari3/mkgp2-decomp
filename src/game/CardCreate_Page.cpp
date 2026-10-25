/*
 * CardCreate_Page @ 0x8006AD0C..0x8006B32C: the card create test page.
 * Edits the fields of a test player card (character, three cc classes,
 * three flags, a rank, a coin count and one more flag), then builds the
 * player data and writes it to a card. Owns its jump table in .data.
 *
 * NonMatching: the option name lookups. The target addresses each table as
 * its own pooled object (addi rT, base, off; lwzx), which suggests the
 * tables were static data of this TU; through the extern pool they come
 * out as add + lwz off. The rest matches.
 */
#include "game/TestMenuPage.h"

struct CardCreateState {
    int phase;              /* 0x00: 0 edit, 1 save, 2 card write, 3 done */
    int cursor;             /* 0x04 */
    int timer;              /* 0x08 */
    int character;          /* 0x0C */
    int cc[3];              /* 0x10 */
    unsigned char flag[3];  /* 0x1C */
    unsigned char pad_1F;
    int rank;               /* 0x20 */
    int coins;              /* 0x24: in hundreds */
    unsigned char extra;    /* 0x28 */
};

struct CardCreatePage {
    TestPage base;
    unsigned char pad_278[8];
    CardCreateState *state; /* 0x280 */
};

/* Option name tables (0x803FBF80). */
struct CardCreateNames {
    const char *cc0[3];
    const char *cc1[3];
    const char *cc2[3];
    const char *character[13];
    const char *rank[16];
};

extern "C" {
extern CardCreateNames lbl_803FBF80;
extern const char *lbl_806CEF28[2];
extern const char *lbl_806CEF30[2];
extern const char *lbl_806CEF38[2];
extern const char *lbl_806CEF40[2];
extern const char lbl_806D2D68[5];
extern const char lbl_806D2DB0[2];
extern unsigned char g_playerData[];
void *Alloc(unsigned long size);
void MemoryManager_TimedFree(void *p);
int WrapInRange(int v, int lo, int hi);
void PlayerData_Construct(void *, int, int, int, int, unsigned char, unsigned char, unsigned char,
                          const char *, int, unsigned char);
void card_save_trigger(int);
unsigned char CardSave_Tick(void);
void card_rw_kick_state_machine(void);
unsigned char card_rw_state_machine(void);
void CardRW_TestTopMenu_Page(CardCreatePage *self, int phase, int arg);
}

#pragma exceptions on

extern "C" int CardCreate_Page(CardCreatePage *self, int phase)
{
    CardCreateNames *names = &lbl_803FBF80;
    char *pool = lbl_8030E598;
    CardCreateState *st;
    InputPlayer *pl;
    unsigned char up;
    unsigned char ok;
    void *text;
    int coins;
    int y;

    if (phase == 0) {
        st = (CardCreateState *)Alloc(sizeof(CardCreateState));
        if (st != 0) {
            st->character = 0;
            st->cc[0] = 0;
            st->cc[1] = 0;
            st->cc[2] = 0;
            st->flag[0] = 0;
            st->flag[1] = 0;
            st->flag[2] = 0;
            st->rank = 0;
            st->coins = 0;
            st->cursor = 0;
            st->extra = 0;
            st->phase = 0;
            st->timer = 0;
        }
        self->state = st;
    }
    if (phase == 1) {
        up = 0;
        ok = 0;
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (pl->Pressed(0x800)) {
            up = 1;
        }
        if (pl->Pressed(0x1000)) {
            ok = 1;
        }
        st = self->state;
        if (st->phase == 0) {
            if (up == 1) {
                st->cursor = WrapInRange(st->cursor + 1, 0, 10);
            } else if (ok == 1) {
                switch (st->cursor) {
                case 0:
                    st->character = WrapInRange(st->character + 1, 0, 12);
                    break;
                case 1:
                    st->cc[0] = WrapInRange(st->cc[0] + 1, 0, 2);
                    break;
                case 2:
                    st->cc[1] = WrapInRange(st->cc[1] + 1, 0, 2);
                    break;
                case 3:
                    st->cc[2] = WrapInRange(st->cc[2] + 1, 0, 2);
                    break;
                case 4:
                    st->flag[0] = st->flag[0] != 1;
                    break;
                case 5:
                    st->flag[1] = st->flag[1] != 1;
                    break;
                case 6:
                    st->flag[2] = st->flag[2] != 1;
                    break;
                case 7:
                    st->rank = WrapInRange(st->rank + 1, 0, 16);
                    break;
                case 8:
                    st->coins = WrapInRange(st->coins + 1, 0, 40);
                    break;
                case 9:
                    st->extra = st->extra != 1;
                    break;
                case 10:
                    if (st->coins <= 0) {
                        coins = 0;
                    } else {
                        coins = st->coins * 100 - 1;
                    }
                    PlayerData_Construct(g_playerData, st->character, st->cc[0], st->cc[1], st->cc[2],
                                         st->flag[0], st->flag[1], st->flag[2], names->rank[st->rank],
                                         coins, st->extra);
                    card_save_trigger(0);
                    st->phase = 1;
                    break;
                }
            }
        } else if (st->phase == 1) {
            if (CardSave_Tick() == 1) {
                st->phase = 2;
                card_rw_kick_state_machine();
            }
        } else if (st->phase == 2) {
            if (card_rw_state_machine() == 1) {
                st->phase = 3;
            }
        }
        st->timer++;
        if (st->phase == 3) {
            MemoryManager_TimedFree(self->state);
            self->base.next = 5;
            CardRW_TestTopMenu_Page(self, 0, 10);
        }
    }
    if (phase == 2) {
        text = self->base.text;
        if (text != 0) {
            st = self->state;
            DrawText(text, 0xE, 0x18, 7, 1.0f, pool + 0x1F50);
            DrawText(text, 0x1C, 0x48, 7, 1.0f, pool + 0x1F5C, names->character[st->character]);
            DrawText(text, 0x1C, 0x60, 7, 1.0f, pool + 0x1F70, names->cc0[st->cc[0]]);
            DrawText(text, 0x1C, 0x78, 7, 1.0f, pool + 0x1F84, names->cc1[st->cc[1]]);
            DrawText(text, 0x1C, 0x90, 7, 1.0f, pool + 0x1F98, names->cc2[st->cc[2]]);
            DrawText(text, 0x1C, 0xA8, 7, 1.0f, pool + 0x1FAC, lbl_806CEF28[st->flag[0] != 0]);
            DrawText(text, 0x1C, 0xC0, 7, 1.0f, pool + 0x1FC0, lbl_806CEF30[st->flag[1] != 0]);
            DrawText(text, 0x1C, 0xD8, 7, 1.0f, pool + 0x1FD4, lbl_806CEF38[st->flag[2] != 0]);
            DrawText(text, 0x1C, 0xF0, 7, 1.0f, pool + 0x1FE8, names->rank[st->rank]);
            if (st->coins <= 0) {
                coins = 0;
            } else {
                coins = st->coins * 100 - 1;
            }
            DrawText(text, 0x1C, 0x108, 7, 1.0f, pool + 0x1FFC, coins);
            DrawText(text, 0x1C, 0x120, 7, 1.0f, pool + 0x2010, lbl_806CEF40[st->extra != 0]);
            DrawText(text, 0x1C, 0x138, 7, 1.0f, lbl_806D2D68);
            if (st->cursor == 10) {
                y = 0x138;
            } else {
                y = (st->cursor + 3) * 24;
            }
            st->timer &= 0x1F;
            if (st->timer < 0x18) {
                DrawText(text, 0xE, y, 7, 1.0f, lbl_806D2DB0);
            }
        }
    }
    return 1;
}

#pragma exceptions reset

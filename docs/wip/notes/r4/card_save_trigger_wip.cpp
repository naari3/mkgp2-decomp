/*
 * Card save trigger, 0x80093C28..0x8009450C.
 * Snapshots g_playerData into the card shadow (inlined card_force_backup_now)
 * and either starts the read/write state machine or a cleaning cycle.
 */
#pragma inline_max_size(10000)
#include "game/CardLoadShadowPrivate.h"
extern "C" {
extern unsigned char lbl_806D122A, g_cardCmdResult, lbl_806D1225, lbl_806D1248;
extern unsigned char lbl_806D1228, lbl_806D1227, lbl_806CF0D4;
extern unsigned int g_cardSaveStartTick;
extern int lbl_806D1210, lbl_806CF0E4, lbl_806D1220, g_cardRwSubState;
extern int lbl_806D124C, lbl_806CF0D0, lbl_806CF0E8;
unsigned int OSGetTick(void);
unsigned char ServiceLatch_CheckTriggered(void);
unsigned char card_rw_state_machine(void);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_SendCmdCleaning(void *card);
void card_backup(void);
int rand(void);
void SoundMgr_PlaySE(int id);
void fn_801D647C(struct CardPlayerSnapshot *pd, unsigned char a, unsigned char b, unsigned char c, int d);
}

static inline void CaptureSnapshot(void)
{
    struct CardBackupSnapshot *bk = &lbl_80598A60;
    bk->player = g_playerData;
    bk->captured = 1;
    card_backup();
}

static inline bool BeginRW(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    g_cardCmdResult = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return false;
    }
    return true;
}

extern "C" unsigned char card_save_trigger(unsigned char mode)
{
    void *card;

    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    g_cardCmdResult = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    card = Sci2Card_Singleton_Get();
    lbl_806D1225 = mode;
    lbl_806D1248 = 0;
    if (mode == 1) {
        CaptureSnapshot();
        g_playerData.byte199 = 1;
        if (lbl_806D1228 != 1) {
            g_cardSaveStartTick = OSGetTick();
            if (BeginRW()) {
                lbl_806D1227 = 0;
                lbl_806D1220 = 0;
                g_cardRwSubState = 0;
                card_rw_state_machine();
            }
        }
        lbl_806D124C = 0;
        lbl_806CF0D4 = 1;
    } else {
        bool a, b, c;
        g_cardCmdResult = Sci2Card_SendCmdCleaning(card);
        lbl_806D124C = 1;
        lbl_806CF0D0 = 4;
        lbl_806CF0D4 = 1;
        a = rand() % 20 == 0;
        b = rand() % 20 == 0;
        c = rand() % 20 == 0;
        if (a == 1 || b == 1 || c == 1) {
            SoundMgr_PlaySE(0xab);
        }
        fn_801D647C(&g_playerData, a, b, c, 0);
        CaptureSnapshot();
    }
    lbl_806CF0E8 = 3;
    return 1;
}

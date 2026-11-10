#pragma inline_max_size(1000)
#pragma cplusplus on
extern "C" {
#include "game/CardLoadShadowPrivate.h"
extern unsigned char lbl_806D1228, lbl_806D122A, g_cardCmdResult, lbl_806D1227;
extern unsigned int g_cardSaveStartTick;
extern int lbl_806D1210, lbl_806CF0E4, lbl_806D1220, g_cardRwSubState;
extern int lbl_806D124C, lbl_806CF0D0;
unsigned int OSGetTick(void);
unsigned char ServiceLatch_CheckTriggered(void);
unsigned char card_rw_state_machine(void);
void card_backup(void);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_SendCmdCleaning(void *);

unsigned char CardSave_Tick_CaptureAndStart(void)
{
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (card_rw_state_machine() == 1) {
        unsigned char result = 0;
        switch (lbl_806D1210) {
        case 0:
        case 7:
            if (lbl_806D1228 != 1) {
                g_cardSaveStartTick = OSGetTick();
                lbl_806D1210 = 0;
                lbl_806D122A = 1;
                g_cardCmdResult = 0;
                lbl_806CF0E4 = 5;
                if (!ServiceLatch_CheckTriggered()) {
                    lbl_806D1210 = 1;
                } else {
                    lbl_806D1227 = 0;
                    lbl_806D1220 = 0;
                    g_cardRwSubState = 0;
                    card_rw_state_machine();
                }
            }
            break;
        case 1:
        case 3:
            g_playerData.byte199 = 0;
            g_playerData.byte198 = 50;
            lbl_80598A60.captured = 1;
            lbl_80598A60.player = g_playerData;
            card_backup();
            lbl_806D124C = 1;
            lbl_806D1210 = 0;
            lbl_806D122A = 1;
            g_cardCmdResult = 0;
            lbl_806CF0E4 = 5;
            g_cardCmdResult = Sci2Card_SendCmdCleaning(Sci2Card_Singleton_Get());
            lbl_806CF0D0 = 4;
            break;
        case 2:
        case 5:
        case 100:
        case 101:
        default:
            result = 1;
            break;
        }
        return result;
    }
    return 0;
}
}
#pragma cplusplus reset

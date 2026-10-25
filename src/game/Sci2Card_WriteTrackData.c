/* Card track-data write and eject steps, 0x80095C5C..0x80096034. */
#include "game/Sci2CardReceipt.h"

extern void *card_pack(void *source, void *destination, int mode);
extern unsigned char card_send_track_data(void *card, void *data, int size, int flags);
extern unsigned char card_eject(void *card);
extern unsigned char card_eject_state_machine(void);

extern int lbl_806CF0D0;
extern int lbl_806CF0D8;
extern int lbl_806D1220;
extern unsigned char lbl_806D1227;
extern unsigned char lbl_806CF0D4;
extern unsigned char lbl_805AC55C[];

/* 0x80095C5C: send the packed track data and wait for the reply. */
unsigned char Sci2Card_WriteTrackData_PollState(void)
{
    void *card;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get();
    if (lbl_806D121C == 0) {
        lbl_806D121C = card_send_track_data(card, lbl_805AC55C, 0x45, 0);
        return 0;
    }
    if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm(card)) {
            Sci2Card_SetFailCode();
            return 1;
        }
        lbl_806D122A = 0;
        lbl_806D1210 = 1;
        lbl_806D122B = 0;
        return 1;
    }
    return 0;
}

/* 0x80095E3C: pack the player data and start sending it to the card. */
unsigned char Sci2Card_WriteTrackData_StartFlow(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    card_pack(g_playerData, lbl_805AC55C, 1);
    lbl_806D121C = card_send_track_data(Sci2Card_Singleton_Get(), lbl_805AC55C, 0x45, 0);
    return 1;
}

static inline unsigned char Eject_IsPending(void)
{
    return lbl_806D1227 != 0;
}

/* 0x80095EC8: eject the card and wait for the eject to finish. */
unsigned char Sci2Card_EjectAndFinalize_Step(void)
{
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }
    switch (lbl_806D1220) {
    case 0:
    case 1:
    case 2:
    case 3:
        return 0;
    case 4:
        lbl_806CF0D0 = 2;
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        if (!ServiceLatch_CheckTriggered()) {
            lbl_806D1210 = 1;
        } else {
            lbl_806D1227 = 0;
            lbl_806D121C = card_eject(Sci2Card_Singleton_Get());
            lbl_806CF0D4 = 0;
        }
        lbl_806CF0D8 = 1;
        lbl_806D1220++;
    case 5:
        if (Eject_IsPending() == 1) {
            lbl_806CF0D0 = 3;
        }
        if (card_eject_state_machine() == 1) {
            if (lbl_806D1210 != 0 && lbl_806D1210 != 1) {
                lbl_806D1220--;
                return 0;
            }
            lbl_806CF0E8 = 3;
            lbl_806CF0D0 = 5;
            lbl_806CF0D8 = 2;
            return 1;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

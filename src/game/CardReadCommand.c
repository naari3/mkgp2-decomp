/* Card read/write command entry points. The command state is shared with
 * the card state machines; byte-sized flags must stay distinct from status
 * and substate words. */
extern unsigned int OSGetTick(void);
extern unsigned char ServiceLatch_CheckTriggered(void);
extern unsigned char card_rw_state_machine(void);
extern unsigned char card_read_state_machine(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdOptions(void *card, unsigned char read,
                                           unsigned char option);

extern int lbl_806CF0D8;
extern int lbl_806CF0DC;
extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern int lbl_806D1214;
extern unsigned char lbl_806D121C;
extern int lbl_806D1220;
extern unsigned char lbl_806D1227;
extern unsigned char lbl_806D1228;
extern unsigned char lbl_806D122A;
extern unsigned int lbl_806D122C;

unsigned char card_rw_kick_state_machine(void)
{
    if (lbl_806D1228 == 1) {
        return 0;
    }

    lbl_806D122C = OSGetTick();
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    lbl_806D1227 = 0;
    lbl_806D1220 = 0;
    lbl_806CF0D8 = 0;
    card_rw_state_machine();
    return 1;
}

unsigned char card_read_tick(void)
{
    if (!ServiceLatch_CheckTriggered()) {
        return 1;
    }

    if (card_read_state_machine() == 1) {
        if (lbl_806D1210 == 1 && lbl_806D1214 != 5) {
            lbl_806CF0DC = 0;
        }
        return 1;
    }
    return 0;
}

unsigned char card_send_read_cmd_init(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
    } else {
        void *card = Sci2Card_Singleton_Get();
        lbl_806D121C = Sci2Card_SendCmdOptions(card, 1, 0);
    }
    lbl_806CF0DC = -1;
    return 1;
}

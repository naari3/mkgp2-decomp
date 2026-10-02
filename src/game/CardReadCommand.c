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

/* Near-match retained for retry: 96.07% with GC/1.3.2, exceptions off. The switch emits
 * beq + b instead of the target's single bne. A plain if/else emits an extra
 * clrlwi./beq, and early return duplicates the shared completion stores.
 * Those probes used the game library's default flags, before exceptions on
 * was added for the two exact C functions' exception records. */
#if 0
unsigned char card_send_read_cmd_init(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    switch (ServiceLatch_CheckTriggered()) {
    case 0:
        lbl_806D1210 = 1;
        break;
    default:
        lbl_806D121C = Sci2Card_SendCmdOptions(Sci2Card_Singleton_Get(), 1, 0);
        break;
    }
    lbl_806CF0DC = -1;
    return 1;
}
#endif

asm unsigned char card_send_read_cmd_init(void);

/* The preceding C functions use compiler-generated exception records.
 * Only the parked initializer needs a manual record, after both C records. */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_card_send_read_cmd_init[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_card_send_read_cmd_init = {
    (void *)&card_send_read_cmd_init, 0x70, (void *)extab_card_send_read_cmd_init
};

asm unsigned char card_send_read_cmd_init(void)
{
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    li r3, 0x1
    stw r0, 0x14(r1)
    li r0, 0x5
    stw r4, lbl_806D1210(r13)
    stb r3, lbl_806D122A(r13)
    stb r4, lbl_806D121C(r13)
    stw r0, lbl_806CF0E4(r13)
    bl ServiceLatch_CheckTriggered
    clrlwi. r0, r3, 24
    bne card_send_read_cmd_init_L_80097690
    li r0, 0x1
    stw r0, lbl_806D1210(r13)
    b card_send_read_cmd_init_L_800976A4
card_send_read_cmd_init_L_80097690:
    bl Sci2Card_Singleton_Get
    li r4, 0x1
    li r5, 0x0
    bl Sci2Card_SendCmdOptions
    stb r3, lbl_806D121C(r13)
card_send_read_cmd_init_L_800976A4:
    li r0, -0x1
    li r3, 0x1
    stw r0, lbl_806CF0DC(r13)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

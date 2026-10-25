extern unsigned char ServiceLatch_CheckTriggered(void);

extern unsigned char lbl_806D1229;

/* 0x80092918: arm the card registration once the service latch fires. */
void CardRegister_KickoffArm(void)
{
    if (ServiceLatch_CheckTriggered()) {
        lbl_806D1229 = 1;
    }
}

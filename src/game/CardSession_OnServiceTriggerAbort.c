extern unsigned char ServiceLatch_CheckTriggered(void);

extern int lbl_806CF0E0;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1228;

/* 0x80092408: abort a pending card session when the service latch fires. */
unsigned char CardSession_OnServiceTriggerAbort(void)
{
    if (!ServiceLatch_CheckTriggered()) {
        return 1;
    }
    if (lbl_806D1224 == 0) {
        return 1;
    }
    lbl_806D1228 = 1;
    lbl_806CF0E0 = 0;
    return 1;
}

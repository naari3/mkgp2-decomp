extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1237;

void card_ping_clear_pending_flag(void) {
    if (lbl_806D1224 == 0) {
        lbl_806D1237 = 0;
    }
}

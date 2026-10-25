/*
 * 0x8020F220: card session flag reset.
 */

extern "C" {
extern unsigned char lbl_806D1A38;
extern unsigned char lbl_806D1A39;
extern unsigned char lbl_806D1A3A;
extern unsigned char lbl_806D1A3B;
extern unsigned char lbl_806D1A3C;
extern unsigned char lbl_806D1A3D;
extern unsigned char lbl_806D1A3E;
extern int lbl_806D1A40;
extern int lbl_806D1A44;
void card_ping_clear_pending_flag(void);

void fn_8020F220(void) {
    lbl_806D1A38 = 0;
    lbl_806D1A39 = 0;
    lbl_806D1A3B = 0;
    lbl_806D1A3A = 0;
    lbl_806D1A3E = 0;
    lbl_806D1A3D = 0;
    lbl_806D1A3C = 0;
    lbl_806D1A40 = 0;
    lbl_806D1A44 = 0;
    card_ping_clear_pending_flag();
}
}

extern unsigned char lbl_806D1227;

unsigned int card_is_ejected(void) {
    return lbl_806D1227 != 0;
}

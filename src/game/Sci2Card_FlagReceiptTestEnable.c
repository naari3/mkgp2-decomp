extern int lbl_806D1214;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1226;

void Sci2Card_FlagReceiptTestEnable(void) {
    lbl_806D1226 = 1;
}

unsigned char Sci2Card_GetReceiptTestFlag(void) {
    return lbl_806D1226;
}

int Sci2Card_GetUnpackStatusCode(void) {
    return lbl_806D1214;
}

unsigned char Sci2Card_GetByteFlag1224(void) {
    return lbl_806D1224;
}

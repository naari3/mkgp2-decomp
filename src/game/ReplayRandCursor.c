extern unsigned int lbl_806D1320;

unsigned int ReplayRandCursor_Advance(void* self, unsigned int bound) {
    unsigned int result = lbl_806D1320 % bound;
    ++lbl_806D1320;
    return result;
}

void ReplayRandCursor_Reset(void* self) {
    lbl_806D1320 = 0;
}

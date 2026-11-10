extern unsigned int ReplayRandCursor_bss_806D1320;

unsigned int ReplayRandCursor_Advance(void* self, unsigned int bound) {
    unsigned int result = ReplayRandCursor_bss_806D1320 % bound;
    ++ReplayRandCursor_bss_806D1320;
    return result;
}

void ReplayRandCursor_Reset(void* self) {
    ReplayRandCursor_bss_806D1320 = 0;
}

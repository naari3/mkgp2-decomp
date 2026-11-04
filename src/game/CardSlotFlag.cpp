/* Local PCB status bit, with the saved status as the offline fallback. */
extern "C" unsigned char PcbSlot_IsReadyByIndex(int);
extern "C" unsigned char *PcbSlot_GetByIndex(int);
extern "C" unsigned char lbl_80598A60[];
#pragma exceptions on
extern "C" unsigned int fn_8023F714(void) {
    if (PcbSlot_IsReadyByIndex(0)) { unsigned int bit = PcbSlot_GetByIndex(0)[3] & 1; return (0U - bit | bit) >> 31; }
    else return lbl_80598A60[0x29];
}
#pragma exceptions reset

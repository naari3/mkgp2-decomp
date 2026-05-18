extern unsigned char lbl_805940EC[0x2004];
extern unsigned short lbl_806D0FB8[4];
extern unsigned int lbl_806CED48[2];

void DeadCounter_Set_ced48(unsigned int v) {
    lbl_806CED48[0] = v;
}

void Profiler_ResetWriteIndex(void) {
    lbl_805940EC[0] = 0;
}

void DeadCounter_Set_806d0fb8(int v) {
    if (v <= 0) return;
    lbl_806D0FB8[0] = (unsigned short)v;
}

void DeadCounters_PostBootReset(void) {
    lbl_806D0FB8[0] = 0x10;
    lbl_805940EC[0] = 0;
}

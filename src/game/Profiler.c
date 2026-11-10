extern unsigned char Profiler_bss_805940EC[0x2004];
extern unsigned short Profiler_bss_806D0FB8[4];
extern unsigned int DeadCounter_Set_ced48_data_806CED48[2];

void DeadCounter_Set_ced48(unsigned int v) {
    DeadCounter_Set_ced48_data_806CED48[0] = v;
}

void Profiler_ResetWriteIndex(void) {
    Profiler_bss_805940EC[0] = 0;
}

void DeadCounter_Set_806d0fb8(int v) {
    if (v <= 0) return;
    Profiler_bss_806D0FB8[0] = (unsigned short)v;
}

void DeadCounters_PostBootReset(void) {
    Profiler_bss_806D0FB8[0] = 0x10;
    Profiler_bss_805940EC[0] = 0;
}

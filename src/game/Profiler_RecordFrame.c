extern float g_metricsTable[0x31];

void Profiler_RecordFrame(int slot, float value) {
    unsigned char oob;
    if (slot < 0 || slot >= 0x30) {
        oob = 1;
    } else {
        oob = 0;
    }
    if (oob == 1) return;
    g_metricsTable[slot] += value;
}

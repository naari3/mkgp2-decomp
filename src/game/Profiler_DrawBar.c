extern float g_metricsTable[0x30];
extern char *lbl_802E9B7C[0x30];
extern char lbl_802E9C3C[];
extern void OverlayText(int, int x, int y, char *fmt, ...);

float Profiler_DrawBar(int x, int y, int index) {
    unsigned char invalid;
    float ratio;
    float value;

    if (index < 0 || index >= 0x30) {
        invalid = 1;
    } else {
        invalid = 0;
    }
    if (invalid == 1) {
        return 0.0f;
    }
    ratio = 0.0f;
    value = g_metricsTable[index];
    if (value > ratio) {
        ratio = value / 0.016666668f;
    }
    OverlayText(1, x, y + 3, lbl_802E9C3C, lbl_802E9B7C[index], ratio);
    return ratio;
}

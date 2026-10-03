/* Only the observed offset-zero vptr is modeled here. */
struct JvsInput {
    JvsInput();
    virtual ~JvsInput();
};

JvsInput::JvsInput() {}

extern "C" {
extern float g_metricsTable[49];
extern const float lbl_806D2478;
extern const float lbl_806D247C;

void MetricsTable_ResetAll(void) {
    for (int i = 0; i < 48; i++) {
        g_metricsTable[i] = lbl_806D2478;
    }
}

float MetricsTable_Get(int index) {
    unsigned char invalid;
    if (index < 0 || index >= 48) {
        invalid = 1;
    } else {
        invalid = 0;
    }
    if (invalid == 1) {
        return lbl_806D2478;
    }
    float value = g_metricsTable[index];
    float result = lbl_806D2478;
    if (value > result) {
        result = value / lbl_806D247C;
    }
    return result;
}
}

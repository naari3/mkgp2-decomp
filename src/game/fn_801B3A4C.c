typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

extern VoiceClip g_voicePlayCountTable[];

void fn_801B3A4C(void) {
}

VoiceClip *fn_801B3A50(int id) {
    if (id < 0) {
        do {
            id += 0x282;
        } while (id < 0);
    }
    if (id >= 0x282) {
        do {
            id -= 0x282;
        } while (id >= 0x282);
    }
    return &g_voicePlayCountTable[id];
}

int fn_801B3A88(int id) {
    if (id < 0) {
        do {
            id += 0x282;
        } while (id < 0);
    }
    if (id >= 0x282) {
        do {
            id -= 0x282;
        } while (id >= 0x282);
    }
    return id;
}

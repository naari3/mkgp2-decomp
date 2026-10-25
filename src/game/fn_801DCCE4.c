typedef struct PathCond {
    signed char mode;
    signed char cup;
    signed char ccClass;
    signed char round;
    unsigned char extra;
} PathCond;

typedef struct PathVariantEntry {
    PathCond cond;
    char pad[0x14 - sizeof(PathCond)];
} PathVariantEntry;

extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;
extern int lbl_806CFF0C;
extern PathVariantEntry lbl_804E3644[];

static inline unsigned char PathCond_Matches(PathCond c) {
    if (c.mode != -1 && c.mode != g_gameMode) {
        return 0;
    }
    if (c.cup != -1 && c.cup != g_cupId) {
        return 0;
    }
    if (c.ccClass != -1 && c.ccClass != g_ccClass) {
        return 0;
    }
    if (c.round != -1 && c.round != g_roundIndex) {
        return 0;
    }
    return 1;
}

int fn_801DCCE4(void) {
    int i;

    for (i = 0; i < lbl_806CFF0C; i++) {
        if (PathCond_Matches(lbl_804E3644[i].cond)) {
            return i;
        }
    }
    return -1;
}

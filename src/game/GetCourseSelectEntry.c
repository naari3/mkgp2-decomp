typedef struct CourseSelectEntry {
    char data[0x18];
} CourseSelectEntry;

typedef struct CupCourseEntry {
    char data[0xC];
} CupCourseEntry;

extern CourseSelectEntry lbl_8049A5A8[];
extern CupCourseEntry lbl_8049A248[][8];
extern int g_roundIndex;
extern int g_cupId;

CourseSelectEntry *GetCourseSelectEntry(int idx) {
    if (idx < 0) {
        idx = 0;
    }
    if (idx > 15) {
        idx = 15;
    }
    return &lbl_8049A5A8[idx];
}

CupCourseEntry *fn_801BA060(int round) {
    int cup;

    if (round == -1) {
        round = g_roundIndex;
    }
    if (g_cupId == 7) {
        cup = 0;
    } else if (g_cupId == 1) {
        cup = 1;
    } else if (g_cupId == 8) {
        cup = 2;
    } else if (g_cupId == 2) {
        cup = 3;
    } else if (g_cupId == 3) {
        cup = 4;
    } else if (g_cupId == 4) {
        cup = 5;
    } else if (g_cupId == 5) {
        cup = 6;
    } else if (g_cupId == 6) {
        cup = 7;
    } else {
        cup = 0;
    }
    return &lbl_8049A248[cup][round];
}

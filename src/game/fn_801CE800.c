/* Course select: applies the cup/variant pair at index and loads its course. */
typedef struct CupNames {
    short first;
    short second;
} CupNames;

typedef struct CourseSel {
    char pad0[0xCC];
    short *nameA;
    short *nameB;
    int course;
    char padD8[0xC];
    unsigned char dirty;
    float fadeE8;
    float fadeEC;
    float fadeF0;
} CourseSel;

extern CupNames lbl_8049B388[8];
extern const float lbl_806D9EDC;
extern const float lbl_806D9EE8;
extern const float lbl_806D9EEC;
void fn_80121E10(void *ctrl);
short GetCourseShortIdByCupAndMirror(int cup, int mirror);

#pragma force_active on
void fn_801CE800(CourseSel *sel, int index) {
    int cup = index / 2;
    int cupId;

    *sel->nameA = lbl_8049B388[cup].first;
    *sel->nameB = lbl_8049B388[cup].second;
    fn_80121E10(&sel->course);
    switch (cup) {
    case 0:
        cupId = 7;
        break;
    case 1:
        cupId = 1;
        break;
    case 2:
        cupId = 8;
        break;
    case 3:
        cupId = 2;
        break;
    case 4:
        cupId = 3;
        break;
    case 5:
        cupId = 4;
        break;
    case 6:
        cupId = 5;
        break;
    case 7:
        cupId = 6;
        break;
    default:
        cupId = 1;
        break;
    }
    sel->course = GetCourseShortIdByCupAndMirror(cupId, index % 2);
    sel->dirty = 1;
    sel->fadeE8 = lbl_806D9EE8;
    sel->fadeEC = lbl_806D9EEC;
    sel->fadeF0 = lbl_806D9EDC;
}

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern void *g_courseData;
extern char kDummyOnePointPath[];
extern void *CourseData_GetPath(void *courseData, int variant, int reverse);

static inline void *GetCourseData(void) {
    void *cd = g_courseData;
    if (cd == 0) {
        cd = 0;
    }
    return cd;
}

void *PathData_GetByContext(void *self, int variant) {
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int reverse = g_reverseRoundFlag;

    if (cup < 1 || cup >= 9) {
        return kDummyOnePointPath;
    }
    if (longRound < 0 || longRound >= 2) {
        return kDummyOnePointPath;
    }
    if (reverse < 0 || reverse >= 2) {
        return kDummyOnePointPath;
    }
    if (variant < 0) {
        variant = 0;
    } else if (variant >= 6) {
        variant = 5;
    }
    return CourseData_GetPath(GetCourseData(), variant, reverse);
}

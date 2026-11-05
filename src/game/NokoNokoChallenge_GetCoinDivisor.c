/* NonMatching: CW if-converts the cup-to-course helper, omitting the
 * target branch between its two subtraction arms. Earlier if/else, ternary,
 * reversed comparisons and GC/2.x probes also did not resolve it. MiniGame emits
 * the card-valid table before the card-invalid table.
 */
extern int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
struct CoinTable;
extern struct CoinTable *lbl_8048DFB8[8][3][2];
extern const float *lbl_8048E078[8][3][2];
extern const float *lbl_8048DAA8[8][3][2];
extern unsigned char IsCardValid(void);

static inline int course_index(void) {
    int cup = g_cupId;
    int course;

    if (cup >= 9) {
        course = cup - 9;
    } else {
        course = cup - 1;
    }
    return course;
}

static inline int round_half(void) {
    return g_roundIndex > 3;
}

struct CoinTable *NokoNokoChallenge_GetCoinDivisor(void) {
    int course = course_index();
    int half = round_half();
    int cc = g_ccClass;

    if (course < 0 || half < 0 || cc < 0) {
        return 0;
    }
    return lbl_8048DFB8[course][cc][half];
}

#pragma exceptions on
const float *MiniGame_GetCourseData(void) {
    int course = course_index();
    int half = round_half();
    int cc = g_ccClass;

    if (course < 0 || half < 0 || cc < 0) {
        return 0;
    }
    if (!IsCardValid()) {
        return lbl_8048E078[course][cc][half];
    }
    return lbl_8048DAA8[course][cc][half];
}
#pragma exceptions reset

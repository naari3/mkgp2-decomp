/* Cup-to-course helpers for the NokoNoko challenge coin tables. MiniGame
 * emits the card-valid table before the card-invalid table.
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
    int course = g_cupId;
    if (course >= 9) {
        course -= 9;
    } else {
        course -= 1;
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
    if (IsCardValid() == 0) {
        return lbl_8048E078[course][cc][half];
    } else {
        return lbl_8048DAA8[course][cc][half];
    }
}
#pragma exceptions reset

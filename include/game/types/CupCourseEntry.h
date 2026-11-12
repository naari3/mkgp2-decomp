#ifndef GAME_TYPES_CUPCOURSEENTRY_H
#define GAME_TYPES_CUPCOURSEENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared.
 * One round of a cup: the last three arguments of SetCourseParams
 * (clFlowRound reads it as its own `CourseParams`). */
typedef struct CupCourseEntry CupCourseEntry;
struct CupCourseEntry {
    /* 0x000 */ int longRound;   /* 1: the long course */
    /* 0x004 */ int variant;     /* course of the cup, 0..2 */
    /* 0x008 */ int reverse;     /* 1: reverse direction (rounds 5 to 8) */
};

#endif /* GAME_TYPES_CUPCOURSEENTRY_H */

#ifndef GAME_TYPES_COURSESELECTENTRY_H
#define GAME_TYPES_COURSESELECTENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CourseSelectEntry CourseSelectEntry;
struct CourseSelectEntry {
    /* 0x000 */ int cup;         /* the first three: arguments of SetCourseParams */
    /* 0x004 */ int longRound;
    /* 0x008 */ int variant;
    /* 0x00C */ int resource0C;  /* sprite ids */
    /* 0x010 */ int resource10;
    /* 0x014 */ int resource14;
};

#endif /* GAME_TYPES_COURSESELECTENTRY_H */

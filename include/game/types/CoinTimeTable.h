#ifndef GAME_TYPES_COINTIMETABLE_H
#define GAME_TYPES_COINTIMETABLE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CoinTimeTable CoinTimeTable;
struct CoinTimeTable {
    /* 0x000 */ float t[8][2][4];
};

#endif /* GAME_TYPES_COINTIMETABLE_H */

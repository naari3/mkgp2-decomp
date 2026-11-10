#ifndef GAME_TYPES_CARDTASKPRINTJOB_H
#define GAME_TYPES_CARDTASKPRINTJOB_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CardTaskPrintJob CardTaskPrintJob;
struct CardTaskPrintJob {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ unsigned long status;
};

#endif /* GAME_TYPES_CARDTASKPRINTJOB_H */

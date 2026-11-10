#ifndef GAME_TYPES_TAENTRY_H
#define GAME_TYPES_TAENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TaEntry TaEntry;
struct TaEntry {
    /* 0x000 */ unsigned short parts[5];
    /* 0x00A */ unsigned char pad_00A[0x2];
    /* 0x00C */ signed char chara;
    /* 0x00D */ unsigned char titleA;
    /* 0x00E */ unsigned char titleB;
    /* 0x00F */ unsigned char titleC;
};

#endif /* GAME_TYPES_TAENTRY_H */

#ifndef GAME_TYPES_RESULTFADER_H
#define GAME_TYPES_RESULTFADER_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ResultFader ResultFader;
struct ResultFader {
    /* 0x000 */ unsigned char pad_000[0x20];
    /* 0x020 */ float alpha;
};

#endif /* GAME_TYPES_RESULTFADER_H */

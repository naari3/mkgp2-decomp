#ifndef GAME_TYPES_DISPLAYCONTEXT_H
#define GAME_TYPES_DISPLAYCONTEXT_H

struct TextEntry;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DisplayContext DisplayContext;
struct DisplayContext {
    /* 0x000 */ void *fifo;
    /* 0x004 */ int f4;
    /* 0x008 */ int f8;
    /* 0x00C */ unsigned char alpha;
    /* 0x00D */ unsigned char pad_00D[0x3];
    /* 0x010 */ float f10;
    /* 0x014 */ char f14[0x74];
    /* 0x088 */ struct TextEntry *entries;
    /* 0x08C */ int count;
};

#endif /* GAME_TYPES_DISPLAYCONTEXT_H */

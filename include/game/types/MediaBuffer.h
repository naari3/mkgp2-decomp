#ifndef GAME_TYPES_MEDIABUFFER_H
#define GAME_TYPES_MEDIABUFFER_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MediaBuffer MediaBuffer;
struct MediaBuffer {
    /* 0x000 */ unsigned char busy;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ void *data;
};

#endif /* GAME_TYPES_MEDIABUFFER_H */

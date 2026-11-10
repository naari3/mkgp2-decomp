#ifndef GAME_TYPES_CLSTREAM_H
#define GAME_TYPES_CLSTREAM_H

typedef struct ClStream {
    unsigned char state;
    unsigned char pad1[3];
    struct ClStream *pair;
    unsigned char pad8[8];
    unsigned int flags;
    unsigned char pad14;
    unsigned char volume;
    unsigned char pad16[0x78 - 0x16];
} ClStream;

#endif /* GAME_TYPES_CLSTREAM_H */

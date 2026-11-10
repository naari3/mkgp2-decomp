#ifndef GAME_TYPES_ZPROBE_H
#define GAME_TYPES_ZPROBE_H

typedef struct ZProbe {
    unsigned char active;
    unsigned short x;
    unsigned short y;
    unsigned int z;
    struct ZProbe *next;
} ZProbe;

#endif /* GAME_TYPES_ZPROBE_H */

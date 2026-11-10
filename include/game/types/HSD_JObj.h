#ifndef GAME_TYPES_HSD_JOBJ_H
#define GAME_TYPES_HSD_JOBJ_H

typedef struct HSD_JObj {
    unsigned char pad00[0x14];
    unsigned int flags;
    unsigned char pad18[0x24];
    float translateY;
} HSD_JObj;

#endif /* GAME_TYPES_HSD_JOBJ_H */

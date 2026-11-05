#ifndef SPRITESLOT_WITHRESEED_PRIVATE_H
#define SPRITESLOT_WITHRESEED_PRIVATE_H
typedef struct SpriteAnimEntry {
    signed char loop; /* 0x0 */
    float start;      /* 0x4 */
    float end;        /* 0x8 */
} SpriteAnimEntry;

typedef struct SpriteClassEntry {
    unsigned char pad0[4];
    SpriteAnimEntry *anims; /* 0x4 */
    unsigned char pad8[0xC];
} SpriteClassEntry;

typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *model;       /* 0x04 */
    unsigned char cls; /* 0x08 */
    signed char anim;  /* 0x09 */
    signed char state; /* 0x0A */
    float frame;       /* 0x0C */
    unsigned char pad10[0x24];
    float matrix[12]; /* 0x34 */
} SpriteSlot;

#endif

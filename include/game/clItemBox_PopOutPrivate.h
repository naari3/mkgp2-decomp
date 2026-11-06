#ifndef CLITEMBOX_POP_OUT_PRIVATE_H
#define CLITEMBOX_POP_OUT_PRIVATE_H

/* Fields accessed by the pop-out animation step. */
typedef struct ItemBoxPopOut {
    float baseHeight;              /* 0x00 */
    unsigned char pad04[8];
    float height;                  /* 0x0C */
    unsigned char pad10[4];
    float rotation;                /* 0x14 */
    unsigned char pad18[0x14];
    float timer;                   /* 0x2C */
    float scale;                   /* 0x30 */
} ItemBoxPopOut;

#endif

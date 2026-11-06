#ifndef GAME_CLITEMBOX_STEPFN_BOBBINGPRIVATE_H
#define GAME_CLITEMBOX_STEPFN_BOBBINGPRIVATE_H

typedef struct ItemBoxBobbing {
    float baseHeight; /* 0x00 */
    unsigned char pad04[8];
    float height; /* 0x0C */
    unsigned char pad10[4];
    float rotation; /* 0x14 */
    unsigned char pad18[0x10];
    float phase; /* 0x28 */
} ItemBoxBobbing;

#endif

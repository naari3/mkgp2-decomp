#ifndef GAME_TYPES_JUMPDISTANCEMODE_H
#define GAME_TYPES_JUMPDISTANCEMODE_H

struct CarObject;
struct GoalPlane;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JumpDistanceMode JumpDistanceMode;
struct JumpDistanceMode {
    /* 0x000 */ void *vtbl;
    /* 0x004 */ unsigned char pad_004[0x4];
    /* 0x008 */ struct CarObject *car;
    /* 0x00C */ int xC;
    /* 0x010 */ unsigned char pad_010[0x4];
    /* 0x014 */ void *x14;
    /* 0x018 */ void *camera;
    /* 0x01C */ void *x1C;
    /* 0x020 */ unsigned char pad_020[0x18];
    /* 0x038 */ struct GoalPlane *goal;
    /* 0x03C */ unsigned char pad_03C[0x4];
    /* 0x040 */ float *marker;
    /* 0x044 */ unsigned char pad_044[0xC];
    /* 0x050 */ int state;
    /* 0x054 */ unsigned char pad_054[0x14];
    /* 0x068 */ float speed;
    /* 0x06C */ unsigned char pad_06C[0x4];
    /* 0x070 */ char *sim;
    /* 0x074 */ float launchTimer;
    /* 0x078 */ unsigned char pad_078[0x10];
    /* 0x088 */ unsigned char reached;
    /* 0x089 */ unsigned char pad_089[0x3];
};

#endif /* GAME_TYPES_JUMPDISTANCEMODE_H */

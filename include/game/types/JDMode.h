#ifndef GAME_TYPES_JDMODE_H
#define GAME_TYPES_JDMODE_H

#include "game/types/Vec3.h"

struct CarObject;
struct GoalPlane;
struct JDCamera;
struct JDCoins;
struct JDLanding;
struct JDTimer;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JDMode JDMode;
struct JDMode {
    /* 0x000 */ void *vtbl;  /* also: vptr */
    /* 0x004 */ int x4;
    /* 0x008 */ struct CarObject *car;
    /* 0x00C */ void *lakitu;
    /* 0x010 */ void *environment;
    /* 0x014 */ void *camera;
    /* 0x018 */ void *goalCamera;
    /* 0x01C */ void *x1C;
    /* 0x020 */ unsigned char pad_020[0x8];
    /* 0x028 */ void *hud;
    /* 0x02C */ struct JDTimer *display;  /* also: timer */
    /* 0x030 */ struct GoalPlane *goal;
    /* 0x034 */ struct GoalPlane *goal2;
    /* 0x038 */ unsigned char pad_038[0x4];
    /* 0x03C */ struct JDLanding *landing;
    /* 0x040 */ struct JDCamera *introCamera;  /* also: camState */
    /* 0x044 */ unsigned char active;
    /* 0x045 */ unsigned char reached;
    /* 0x046 */ unsigned char pad_046[0x2];
    /* 0x048 */ int endDelay;
    /* 0x04C */ int resultFrames;
    /* 0x050 */ int state;
    /* 0x054 */ float target;
    /* 0x058 */ float distance;
    /* 0x05C */ Vec3 last;
    /* 0x068 */ float speed;
    /* 0x06C */ unsigned char pad_06C[0x8];
    /* 0x074 */ float x74;
    /* 0x078 */ unsigned char pad_078[0x4];
    /* 0x07C */ struct JDCoins *coins;
    /* 0x080 */ int coinIdx;
    /* 0x084 */ int coinCount;
    /* 0x088 */ unsigned char pastGoal;
    /* 0x089 */ unsigned char pad_089[0x3];
};

#endif /* GAME_TYPES_JDMODE_H */

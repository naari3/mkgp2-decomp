#ifndef GAME_AI_FRAME_PAIR_PRIVATE_H
#define GAME_AI_FRAME_PAIR_PRIVATE_H
#include "game/AIFramePrivate.h"

/* Typed view of the eight 0x38-byte frame-tracking records. */
struct FramePairRecord {
    int kartId;
    AISpeedRender *driver;
    int rankDifference;
    int waypoint;
    int nearestKart;
    AISpeedRender *nearestDriver;
    float distanceSquared;
    int field1C;
    float field20;
    int field24, field28;
    float playerDistance;
    unsigned char inSpeedRange;
    unsigned char opaque31[3];
    float speedBonus;
};
#endif

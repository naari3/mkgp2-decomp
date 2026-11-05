#ifndef GAME_RIVAL_AVOIDANCE_UNLOCK_PRIVATE_H
#define GAME_RIVAL_AVOIDANCE_UNLOCK_PRIVATE_H
#include "game/PhysicsCollisionPrivate.h"
#include "game/AIPairPrivate.h"
struct RivalAvoidanceState {
    char reserved0[4];
    void *follower;
    char reserved8[8];
    int kartId;
    int pathId;
    char reserved18[0x64];
    float yaw;
    char reserved80[0x1d];
    unsigned char avoiding;
};
struct RivalPathEntry {
    int unknown;
    int valid;
    int reserved8;
    float *x;
    float *y;
    float *z;
};
struct RivalWaypoint { int valid; float x,y,z; };
extern "C" float lbl_806DA4D8, lbl_806DA4DC;
struct RivalAvoidanceCandidate {
    int id;
    float distance, angle;
    PhysicsPlainVec position;
    RivalAvoidanceCandidate() {
        id=-1;
        distance=1200000000.0f;
        position.x=20000.0f;
        position.y=20000.0f;
        position.z=20000.0f;
        angle=lbl_806DA42C;
    }
    ~RivalAvoidanceCandidate() {}
};
#endif

#ifndef GAME_RIVAL_AVOIDANCE_UNLOCK_PRIVATE_H
#define GAME_RIVAL_AVOIDANCE_UNLOCK_PRIVATE_H
#include "game/PhysicsCollisionPrivate.h"
#include "game/AIPairPrivate.h"
#include "game/types/RivalAvoidanceState.h"
#include "game/types/RivalPathEntry.h"
#include "game/types/RivalWaypoint.h"
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
        angle=0.0f;
    }
    ~RivalAvoidanceCandidate() {}
};
#endif

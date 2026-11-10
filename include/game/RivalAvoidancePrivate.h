#ifndef GAME_RIVAL_AVOIDANCE_PRIVATE_H
#define GAME_RIVAL_AVOIDANCE_PRIVATE_H
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
        distance=::lbl_806DA4D8;
        position.x=::lbl_806DA4DC;
        position.y=::lbl_806DA4DC;
        position.z=::lbl_806DA4DC;
        angle=lbl_806DA42C;
    }
    ~RivalAvoidanceCandidate() {}
};
#endif

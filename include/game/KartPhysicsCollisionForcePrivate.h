#ifndef GAME_KART_PHYSICS_COLLISION_FORCE_PRIVATE_H
#define GAME_KART_PHYSICS_COLLISION_FORCE_PRIVATE_H

#include "game/PhysicsCollisionPrivate.h"

/* PhysicsState fields used by collision-force integration. */
struct CollisionForceState {
    char unknown00[0x4C];
    PhysicsPlainVec position;
    PhysicsPlainVec previous;
    unsigned char applyForce;
    char unknown65[0x7C - 0x65];
    float yaw;
    float unknown80;
    float collisionYaw;
    char unknown88[0xA5 - 0x88];
    unsigned char airborne;
    char unknownA6[0xC0 - 0xA6];
    int landingTimer;
    char unknownC4[0xCC - 0xC4];
    PhysicsPlainVec push;
    PhysicsPlainVec impact;
};

#endif

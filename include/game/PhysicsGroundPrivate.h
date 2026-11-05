#ifndef GAME_PHYSICS_GROUND_PRIVATE_H
#define GAME_PHYSICS_GROUND_PRIVATE_H

#include "game/PhysicsCollisionPrivate.h"
#include "game/kartmove/collision_private.h"

/* PhysicsState, distinct from the owning KartMovement object. */
struct PhysicsGroundState {
    char unknown00[0xC];
    void *body;
    char unknown10[0x1C - 0x10];
    Vec3 corners[4];
    Vec3 position;
    Vec3 previous;
    char unknown64[0xA5 - 0x64];
    unsigned char airborne;
    char unknownA6[2];
    float jumpFields[6];
    int landingTimer;
    int transitMode;
    int transitTimer;
    char unknownCC[0x13C - 0xCC];
    float scale;
    char unknown140[0x154 - 0x140];
    float movementForce;
    int forceTimer;
    char unknown15C[0x168 - 0x15C];
    float fallingVelocity;
    unsigned char aboveGround;
};

struct PhysicsGroundMatrix {
    float m[4][4];
    PhysicsGroundMatrix() {}
    PhysicsGroundMatrix(const PhysicsGroundMatrix &other) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) m[i][j] = other.m[i][j];
    }
};

extern "C" {
extern Vec3 lbl_803BDE24;
extern float lbl_806DA428, lbl_806DA43C, lbl_806DA4A8, lbl_806DA4AC;
void QuadFrame_FromPackedCorners(float *, float *, float *);
void Mtx34_Orthonormalize(void *);
}

#endif

#ifndef GAME_GROUNDED_MOVEMENT_PRIVATE_H
#define GAME_GROUNDED_MOVEMENT_PRIVATE_H
#include "game/PhysicsCollisionPrivate.h"
#include "game/AIPairPrivate.h"

struct GroundedController {
    char reserved0[0x23c];
    void *lateralOffset;
};
/* PhysicsState, distinct from the larger KartMovement object. */
struct GroundedMovementState {
    virtual void Slot08();
    virtual float SteeringCorrection(float);
    void *follower;                         // 004
    GroundedController *controller;         // 008
    char reserved0C[4];
    int kartId;                             // 010
    char reserved14[0x38];
    PhysicsPlainVec position;                // 04c
    PhysicsPlainVec previous;                // 058
    unsigned char enabled;                  // 064
    char reserved65[3];
    float speed, minimumSpeed, targetYaw, maximumSpeed, targetPitch;
    float yaw, slip, matrixYaw;              // 07c..084
    unsigned char steeringEnabled;          // 088
    char reserved89[3];
    float turnVelocity, yawBias, turnStep, slipStrength;
    unsigned char avoidanceEnabled, fastSlip;
    char reserved9E[2];
    int steeringLock;                        // 0a0
    char reservedA4[0x1c];
    int collisionTimer;                      // 0c0
    char reservedC4[0x7c];
    float lateralPosition, lateralWander;    // 140
    int wanderTimer, avoidanceMode, avoidanceTimer;
    char reserved154[8];
    float avoidanceOffset;                  // 15c
    int selectedPath, previousSelectedPath;
    char reserved168[8];
    PhysicsPlainVec targetPosition;          // 170
    PhysicsPlainVec velocity;                // 17c
    char reserved188[4];
    int currentPath, previousPath;           // 18c
    float pathBlend;
};
struct GroundedWaypoint { union { int valid; float metadata; }; float x,y,z; };
#endif

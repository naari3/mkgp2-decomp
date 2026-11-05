#ifndef DRIVE_BEHAVIOR_PRIVATE_H
#define DRIVE_BEHAVIOR_PRIVATE_H

typedef struct DrivePair { int waypoint; int duration; } DrivePair;
typedef struct DriveRing {
    unsigned int capacity, count, head;
    DrivePair **data;
} DriveRing;
typedef struct DriveQueue {
    unsigned int blockSize;
    DriveRing blocks;
    unsigned int first, count;
} DriveQueue;
typedef struct DriveBehavior {
    unsigned char reserved00[8];
    int waypoint, remaining, direction;
    unsigned char itemLocked, flag15;
    unsigned char reserved16[2];
    float speedScale, acceleration, parameter20, phase;
    unsigned char flag28;
    unsigned char reserved29[7];
    float matrix[16];
    DriveQueue queue;
} DriveBehavior;

extern void *fn_801DB8F0(void);
extern int fn_801DB830(void *, int);
extern void DriveBehavior_HandleWpType(DriveBehavior *, int);
extern void fn_801E2F28(DriveQueue *);
extern DrivePair **fn_801E40C0(DriveRing *, unsigned int);
extern float lbl_806D18F4, lbl_806D18F8;
extern const float lbl_806D18FC;
#endif

#ifndef GAME_BIRIBIRILAND_PRIVATE_H
#define GAME_BIRIBIRILAND_PRIVATE_H
#include "game/MathInline.h"
typedef Vec3f Vec;

typedef struct BiribiriObstacle {
    Vec a, b, center, direction;
    float phase;
    unsigned char hit;
    unsigned char pad[3];
} BiribiriObstacle;
typedef struct BiribiriObstacles {
    void *model[7];
    BiribiriObstacle obstacles[9];
} BiribiriObstacles;
typedef struct BiribiriLightInfo {
    unsigned char pad[0x30];
    void (*release)(void *);
    void (*destroy)(void *);
} BiribiriLightInfo;
typedef struct BiribiriLight {
    BiribiriLightInfo *info;
    unsigned short references;
} BiribiriLight;
typedef struct BiribiriState {
    void *vtable;
    float baseTimer;
    void *car, *lakitu, *environment, *scene, *goalCamera, *camera;
    BiribiriLight *lights;
    void *hud;
    unsigned char visible, brake, finished, success;
    int resultTimer;
    BiribiriObstacles *obstacles;
    void *goal;
    Vec unused;
} BiribiriState;
#endif

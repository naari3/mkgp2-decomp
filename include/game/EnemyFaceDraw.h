#ifndef GAME_ENEMY_FACE_DRAW_H
#define GAME_ENEMY_FACE_DRAW_H
/* Private layout views for fn_8022BFA8. */
typedef float FaceMtx[3][4];
struct FaceDrawVec { float x, y, z; };
#include "game/types/Vec3c.h"
#include "game/types/FaceDrawKart.h"
struct FaceDrawSub {
    char pad00[0x40];
    FaceMtx m[2];
    char padA0[0x10];
    FaceMtx animMtx;
    int anim;
    unsigned char finished;
    char padE5[3];
    float alpha;
    int overlay;
    Vec3c offset;
};
struct FaceDrawModel {
    char pad00[4];
    unsigned char variant;
    char pad05[3];
    int face, left, right;
    float x, y, z, scale;
    char pad24[4];
    FaceDrawKart *kart;
    FaceDrawSub *sub;
    void *models[2];
    int timer;
};
#endif

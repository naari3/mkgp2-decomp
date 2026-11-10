#ifndef LAKITU_START_PRIVATE_H
#define LAKITU_START_PRIVATE_H
#include "game/mapobject/mapobject.h"
void *operator new(unsigned long);
void operator delete(void *);
struct LakituStart {
    int phase;
    float frame, released, ground, angle;
    Mtx matrix;
    clNormal3D *model;
    float x, y, z;
    int holdFrames;
    LakituStart(const void *, int, float, float, float);
};
extern "C" {
void PSMTXIdentity(Mtx);
void GetStartPosition(int, float *, int, float *);
void Terrain_GetGroundHeight(Vec3f *, float *, int, int);
void SetRaceStartFlag(int);
extern unsigned char g_lakituDropStarted;
extern int g_countdownPhase;
extern float LakituStart_Init_data_806CEDD0, LakituStart_data_806CEDC0, LakituStart_data_806CEDC8, LakituStart_data_806CEDC4;
extern const float lbl_806D2510, lbl_806D2538;
}
#endif

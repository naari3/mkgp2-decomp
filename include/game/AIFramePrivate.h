#include "game/types/reg_args.h"
#ifndef GAME_AI_FRAME_PRIVATE_H
#define GAME_AI_FRAME_PRIVATE_H
extern "C" {
#include "game/AISpeedPrivate.h"
}
#include "game/Collision.h"
struct AIFrameOwner : AISpeedOwner {
    char opaque10[8];
    unsigned char flag18, flag19;
    char opaque1A[0x12];
    int selectedKart;
};
struct AIFramePosition : Vec {
    AIFramePosition(float a, float b, float c) { x=a; y=b; z=c; }
    ~AIFramePosition() {}
};
static inline float &PlayerDistance(AIPairRecord *p) { return *(float *)&p->field2C; }
static inline unsigned char &InSpeedRange(AIPairRecord *p) { return *(unsigned char *)&p->field30; }
extern "C" {
extern void *g_pathSystem;
extern const float lbl_806DA3E8, lbl_806DA3EC, lbl_806DA3F0, lbl_806DA3F4;
extern const float lbl_806DA40C, lbl_806DA414;
float *KartDriver_GetKartRootMtx(void *);
int Waypoint_FindNearest(void *, int, float, float, float, float);
int Path_GetTotalCount(void *);
void *GetKartTuningGPSpeedParams(void *, int, int, int);
void *fn_801DE1B0();
float fn_801DE074();
float fn_801DDF8C();
int fn_801DCCE4();
float fn_801DCCBC(REG_ARGS1(int idx));
int fn_801DCC94(int);
float fn_801DCC6C(int);
}
#endif

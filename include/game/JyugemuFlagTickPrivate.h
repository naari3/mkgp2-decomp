#ifndef GAME_JYUGEMU_FLAG_TICK_PRIVATE_H
#define GAME_JYUGEMU_FLAG_TICK_PRIVATE_H

#include "sysdolphin/baselib/jobj.h"
extern "C" const char lbl_806D3060[7], lbl_806D3068[5], lbl_80311DB0[];
extern "C" const float lbl_806D3070;
extern "C" void __assert(const char *, int, const char *);
extern "C" HSD_JObj *Archive_GetRootJObj(void *);
extern "C" float (*KartDriver_GetKartRootMtx(void *))[4];
extern "C" void HSD_JObjSetMtxDirtySub(HSD_JObj *);
extern "C" void clNormal3D_Exec(void *);
extern "C" void Object_DriveAnimMatrix(void *);
/* Resource offsets are added to the kart root translation each frame. */
typedef struct FlagDesc { char pad[0x14]; float x,y,z,angle; } FlagDesc;
/* Tick is an inline member: the original object stays live across setters. */
struct Flag { void *object; FlagDesc *desc; void *driver; inline int Tick(); };
#include "game/types/JointTransform.h"
static inline JointTransform *Transform(HSD_JObj *j) { return (JointTransform *)j->_pad_1c; }
static inline unsigned char MatrixDirty(HSD_JObj *j) {
    unsigned int flags;
    unsigned char clean;
    if (!j) __assert(lbl_806D3060, 0x25d, lbl_806D3068);
    flags = j->flags;
    clean = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) clean = 1;
    return clean;
}
static inline void Dirty(HSD_JObj *j) {
    if (j && !MatrixDirty(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline void SetX(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D3060, 0x3b8, lbl_806D3068);
    Transform(j)->translation[0] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetY(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D3060, 0x3c6, lbl_806D3068);
    Transform(j)->translation[1] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetZ(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D3060, 0x3d4, lbl_806D3068);
    Transform(j)->translation[2] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void RotateY(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D3060, 0x2b8, lbl_806D3068);
    if (j->flags & 0x20000) __assert(lbl_806D3060, 0x2b9, lbl_80311DB0);
    Transform(j)->rotation[1] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}

#endif

#ifndef GAME_JYUGEMU_REVERSE_FLAG_TICK_PRIVATE_H
#define GAME_JYUGEMU_REVERSE_FLAG_TICK_PRIVATE_H

#include "sysdolphin/baselib/jobj.h"
#include "game/MathInline.h"
extern "C" const char lbl_806D308C[7], lbl_806D3094[5], lbl_80311DFC[];
typedef Vec3f Vec3;
extern "C" {
extern const float lbl_806D3078, lbl_806D307C, lbl_806D3080, lbl_806D3084, lbl_806D3088, lbl_806D309C, lbl_806D30A0;
extern unsigned char Jyugemu_ReverseFlag_data_806CEFC0[8];
void __assert(const char *, int, const char *);
HSD_JObj *Archive_GetRootJObj(void *);
float (*KartDriver_GetKartRootMtx(void *))[4];
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void clNormal3D_Exec(void *);
void Object_DriveAnimMatrix(void *);
void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *, Vec3 *);
void CObj_ApplyScissor(void *, Vec3 *);
void Vec3_Subtract(Vec3 *, Vec3 *, Vec3 *);
void Vec3_Normalize(Vec3 *, Vec3 *);
double sin(double);
double atan2(double, double);
}
struct ReverseFlag { void *object; void *driver; unsigned char state; unsigned char pad[3]; int timer; float phase; };
/* Mirror the HSD JObj setter inlines used by Jyugemu_Flag_Tick. */
#include "game/types/JointTransform.h"
static inline JointTransform *Transform(HSD_JObj *j) { return (JointTransform *)j->_pad_1c; }
static inline unsigned char MatrixDirty(HSD_JObj *j) {
    unsigned int flags;
    unsigned char clean;
    if (!j) __assert(lbl_806D308C, 0x25d, lbl_806D3094);
    flags = j->flags;
    clean = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) clean = 1;
    return clean;
}
static inline void Dirty(HSD_JObj *j) {
    if (j && !MatrixDirty(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline void SetX(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D308C, 0x3b8, lbl_806D3094);
    Transform(j)->translation[0] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetY(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D308C, 0x3c6, lbl_806D3094);
    Transform(j)->translation[1] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetZ(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D308C, 0x3d4, lbl_806D3094);
    Transform(j)->translation[2] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void RotateY(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D308C, 0x2b8, lbl_806D3094);
    if (j->flags & 0x20000) __assert(lbl_806D308C, 0x2b9, lbl_80311DFC);
    Transform(j)->rotation[1] = v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}

#endif

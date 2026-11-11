#ifndef GAME_TYPES_CLMRAIRSHIP_INLINES_H
#define GAME_TYPES_CLMRAIRSHIP_INLINES_H

#include "game/types/HSD_JObj.h"
#include "game/types/Vec3f.h"
#include "game/types/clNormal3D.h"

/* This file's inline joint setters pool their assertion strings locally. */
extern "C" {
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
void DebugPrintf(const char *, ...);
void Vec3_Subtract(const Vec3f *, const Vec3f *, Vec3f *);
void fn_80181EA4(const Vec3f *, const Vec3f *, const Vec3f *, Vec3f *, float);
double atan2(double, double);
extern char lbl_806D8EA8[7];
extern char lbl_806D8EB0[5];
void __assert(char *, int, char *);
void HSD_JObjDispAll(HSD_JObj *, int, int, int);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
}

struct AirShipPathState {
    HSD_JObj *joint[4];
    Vec3f *points;
    int count, index;
    Vec3f control[3];
    float time;
    Vec3f position;
    float yaw;
};

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x25D, lbl_806D8EB0);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (!clean) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, float x) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2A4, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2A5, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.x = x;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2B8, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2B9, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, float z) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2CC, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2CD, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.z = z;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslate(HSD_JObj *jobj, const Vec3f *translate) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x3A9, lbl_806D8EB0);
    }
    if (translate == 0) {
        __assert(lbl_806D8EA8, 0x3AA, "translate");
    }
    jobj->translate.x = translate->x;
    jobj->translate.y = translate->y;
    jobj->translate.z = translate->z;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

#endif

#include "mkgp2_names.h"
#include "jobj_unlock_private.h"

#include <math.h>
#include <string.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "displayfunc.h"
#include "dobj.h"
#include "fobj.h"
#include "id.h"
#include "mobj.h"
#include "mtx.h"
#include "pobj.h"
#include "robj.h"
#include "spline.h"
#include <dolphin/mtx.h>

double acos(double);

extern HSD_SList* lbl_806D21B4;
extern void (*lbl_806D21B8)(int, int, int, HSD_JObj*);
extern void (*lbl_806D21BC)(s32);
extern void (*lbl_806D21C0)(HSD_JObj*, s32);
#define ufc_callbacks lbl_806D21B4
#define dptcl_callback lbl_806D21B8
#define jsound_callback lbl_806D21BC
#define ptcltgt_callback lbl_806D21C0


typedef void (*ufc_callback)(HSD_JObj*, u32, f32);

static inline void JObjUnlockSetRotationX(HSD_JObj* jobj, f32 v, char* pool)
{
    if (!jobj) __assert(lbl_806D0DA0, 676, lbl_806D0DA8);
    if (jobj->flags & JOBJ_USE_QUATERNION) __assert(lbl_806D0DA0, 677, pool + 0x80);
    jobj->rotate.x = v;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) HSD_JObjSetMtxDirty(jobj);
}

static inline void JObjUnlockSetRotationY(HSD_JObj* jobj, f32 v, char* pool)
{
    if (!jobj) __assert(lbl_806D0DA0, 696, lbl_806D0DA8);
    if (jobj->flags & JOBJ_USE_QUATERNION) __assert(lbl_806D0DA0, 697, pool + 0x80);
    jobj->rotate.y = v;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) HSD_JObjSetMtxDirty(jobj);
}

static inline void JObjUnlockSetRotationZ(HSD_JObj* jobj, f32 v, char* pool)
{
    if (!jobj) __assert(lbl_806D0DA0, 716, lbl_806D0DA8);
    if (jobj->flags & JOBJ_USE_QUATERNION) __assert(lbl_806D0DA0, 717, pool + 0x80);
    jobj->rotate.z = v;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) HSD_JObjSetMtxDirty(jobj);
}

static inline void JObjUnlockCallCallbacks(HSD_JObj* jobj, enum_t type,
                                           HSD_ObjData* val, int byte_value)
{
    HSD_SList* node;
    for (node = ufc_callbacks; node != NULL; node = node->next) {
        ufc_callback cb = node->data;
        if (byte_value) cb(jobj, type, val->iv);
        else cb(jobj, type, val->fv);
    }
}

static inline void JObjUnlockPathPoint(HSD_JObj* jobj, HSD_ObjData* val,
                                       Vec3* p, char* pool)
{
    HSD_JObj* jp;
    if (val->fv < 0.0L) {
        val->fv = 0.0F;
    }
    if (1.0L < val->fv) {
        val->fv = 1.0F;
    }
    if (!jobj->aobj) __assert(lbl_806D0DB0, 590, pool + 0x64);
    jp = jobj->aobj->jobj;
    if (!jp) __assert(lbl_806D0DB0, 592, lbl_806D0DB8);
    if (!jp->u.spline) __assert(lbl_806D0DB0, 593, pool + 0x70);
    splArcLengthPoint(p, jp->u.spline, val->fv);
}

void JObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    char* pool = lbl_804FC9A8;
    HSD_JObj* jobj = obj;
    Vec3 p;
    HSD_RObj* robj;
    Mtx mtx;

    if (jobj != NULL) {
        switch (type) {
        case HSD_A_J_PATH:
            JObjUnlockPathPoint(jobj, val, &p, pool);
            HSD_JObjSetTranslateX(jobj, p.x);
            HSD_JObjSetTranslateY(jobj, p.y);
            HSD_JObjSetTranslateZ(jobj, p.z);
            break;
        case HSD_A_J_ROTX:
            if (jobj->flags & JOBJ_JOINT1) {
                robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    robj->u.ik_hint.rotate_x = val->fv;
                }
            }
            JObjUnlockSetRotationX(jobj, val->fv, pool);
            break;
        case HSD_A_J_ROTY:
            JObjUnlockSetRotationY(jobj, val->fv, pool);
            break;
        case HSD_A_J_ROTZ:
            JObjUnlockSetRotationZ(jobj, val->fv, pool);
            break;
        case HSD_A_J_TRAX:
            HSD_JObjSetTranslateX(jobj, val->fv);
            break;
        case HSD_A_J_TRAY:
            HSD_JObjSetTranslateY(jobj, val->fv);
            break;
        case HSD_A_J_TRAZ:
            HSD_JObjSetTranslateZ(jobj, val->fv);
            break;
        case HSD_A_J_SCAX:
            HSD_JObjSetScaleX(jobj, val->fv);
            break;
        case HSD_A_J_SCAY:
            HSD_JObjSetScaleY(jobj, val->fv);
            break;
        case HSD_A_J_SCAZ:
            HSD_JObjSetScaleZ(jobj, val->fv);
            break;
        case HSD_A_J_BRANCH:
            if (val->fv > 0.5) {
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_NODE:
            if (val->fv > 0.5) {
                HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_SETBYTE0:
        case HSD_A_J_SETBYTE1:
        case HSD_A_J_SETBYTE2:
        case HSD_A_J_SETBYTE3:
        case HSD_A_J_SETBYTE4:
        case HSD_A_J_SETBYTE5:
        case HSD_A_J_SETBYTE6:
        case HSD_A_J_SETBYTE7:
        case HSD_A_J_SETBYTE8:
        case HSD_A_J_SETBYTE9: {
            JObjUnlockCallCallbacks(jobj, type, val, 1);
            break;
        }
        case HSD_A_J_SETFLOAT0:
        case HSD_A_J_SETFLOAT1:
        case HSD_A_J_SETFLOAT2:
        case HSD_A_J_SETFLOAT3:
        case HSD_A_J_SETFLOAT4:
        case HSD_A_J_SETFLOAT5:
        case HSD_A_J_SETFLOAT6:
        case HSD_A_J_SETFLOAT7:
        case HSD_A_J_SETFLOAT8:
        case HSD_A_J_SETFLOAT9: {
            JObjUnlockCallCallbacks(jobj, type, val, 0);
            break;
        }
        case 0x28: {
            s32 iv = val->iv;
            s32 lo = iv & 0x3F;
            s32 hi = iv >> 6 & 0xFFFFFF;
            if (dptcl_callback != NULL) {
                dptcl_callback(0, lo, hi, jobj);
            }
        } break;
        case 0x29:
            if (jsound_callback != NULL) {
                jsound_callback(val->iv);
            }
            break;
        case 0x2A:
            if (ptcltgt_callback != NULL) {
                ptcltgt_callback(jobj, val->iv);
            }
            break;
        case 0x32:
            jobj->mtx[0][0] = val->p.x;
            jobj->mtx[1][0] = val->p.y;
            jobj->mtx[2][0] = val->p.z;
            break;
        case 0x33:
            jobj->mtx[0][1] = val->p.x;
            jobj->mtx[1][1] = val->p.y;
            jobj->mtx[2][1] = val->p.z;
            break;
        case 0x34:
            jobj->mtx[0][2] = val->p.x;
            jobj->mtx[1][2] = val->p.y;
            jobj->mtx[2][2] = val->p.z;
            break;
        case 0x35:
            jobj->mtx[0][3] = val->p.x;
            jobj->mtx[1][3] = val->p.y;
            jobj->mtx[2][3] = val->p.z;
            break;
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            if (jobj->parent != NULL) {
                HSD_MtxInverseConcat(jobj->parent->mtx, jobj->mtx, mtx);
            } else {
                PSMTXCopy(jobj->mtx, mtx);
            }
            if (type == 0x36U || type == 0x38U) {
                HSD_MtxGetTranslate(mtx, &jobj->translate);
            }
            if (type == 0x36U || type == 0x37U) {
                HSD_MtxGetRotation(mtx, (Vec3*) &jobj->rotate);
            }
            if (type == 0x36U || type == 0x39U) {
                HSD_MtxGetScale(mtx, &jobj->scale);
            }
            break;
        }
    }
}

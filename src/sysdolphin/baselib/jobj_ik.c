#include "mkgp2_names.h"
#include "jobj_rescue_private.h"

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

extern char lbl_806D0DB0[7];
extern char lbl_806D0DC4[4];
extern char lbl_806D0DC8[5];
#define JOBJ_ASSERT_eff lbl_806D0DC4
#define JOBJ_ASSERT_robj lbl_806D0DC8
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) \
    ((cond) ? ((void) 0) : __assert(lbl_806D0DB0, line, JOBJ_ASSERT_##cond))

static inline HSD_JObj* jobj_get_joint2(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

static inline HSD_JObj* jobj_get_effector(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

/// Note: this must not be declared inline, so that
/// the "eff" assertion string data is placed before "robj".
HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff)
{
    eff = jobj_get_effector(eff);
    HSD_ASSERT(2084, eff);
    if (HSD_RObjGetByType(eff->robj, REFTYPE_JOBJ, 1) != NULL) {
        return eff;
    } else {
        return NULL;
    }
}


/// @todo Variables @c var_f27 and @c var_f28 are used uninitialized
///       whenever 'if' condition is false.
void resolveIKJoint1(HSD_JObj* jobj)
{
    HSD_JObj* robj_4;
    HSD_JObj* var_r28;
    HSD_JObj* var_r31;
    Vec3* temp_r4;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f5;
    f32 temp_f5_2;
    Vec3 spBC = { 1.0F, 1.0F, 1.0F };
    static const Vec3 HSD_JObj_803B94C4 = { 0.0F, 0.0F, 0.0F };
    f32 var_f1;
    f32 var_f29;
    f32 var_f29_2;
    f32 var_f28;
    f32 var_f27;
    f32 temp_f26;
    f32 var_f4;
    f32 var_f4_2;
    Vec3 spB0;

    u8 _[4];

    f32 var_f4_3;
    f32 var_f4_4;
    f32 var_f5;
    s32 var_r30;
    HSD_RObj* robj;
    Vec3 sp98;
    Vec3 sp8C;
    Vec3 sp80;
    HSD_IKHint* new_var;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Mtx sp20;

    var_r30 = 0;
    var_f29 = 0.0F;
    var_r31 = jobj_get_joint2(jobj->child);
    spB0 = HSD_JObj_803B94C4;
    temp_r4 = jobj->scl;
    var_f5 = 1e-8F;
    if (temp_r4 != NULL) {
        spBC = *temp_r4;
    }
    robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x853, robj);
    new_var = &robj->u.ik_hint;
    temp_f26 = new_var->rotate_x;
    temp_f30 = new_var->bone_length * spBC.x;
    if (var_r31 != NULL) {
        robj = HSD_RObjGetByType(var_r31->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x85E, robj);
        var_f29 = robj->u.ik_hint.bone_length * var_r31->scale.x * spBC.x;
        var_r30 = robj->flags & 4 ? 1 : 0;
        var_r28 = jobj_get_effector_checked(var_r31->child);
    } else {
        var_r28 = jobj_get_effector_checked(jobj->child);
    }
    if (var_r28 != NULL) {
        if ((HSD_RObjGetByType(jobj->robj, REFTYPE_JOBJ, 3) == NULL) &&
            (jobj != NULL))
        {
            if (jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, HSD_JOBJ_METHOD(jobj)->update);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= 0xFFFFFFBF;
                }
            }
        }
        robj_4 = jobj->parent;
        if (robj_4 != NULL) {
            HSD_MtxGetTranslate(robj_4->mtx, &spB0);
        }
        HSD_RObjGetGlobalPosition(var_r28->robj, 1, &var_r28->translate);
        VECSubtract(&var_r28->translate, &spB0, &sp8C);
        temp_f31 = VECDotProduct(&sp8C, &sp8C);

        if (temp_f31 > var_f5) {
            sp68 = sp8C;
            if (HSD_RObjGetGlobalPosition(jobj->robj, 3, &sp5C)) {
                VECSubtract(&sp5C, &spB0, &sp5C);
                if (temp_f26 != 0.0F) {
                    PSMTXRotAxisRad(sp20, &sp68, temp_f26);
                    MTXMultVec(sp20, &sp5C, &sp5C);
                }
                VECCrossProduct(&sp68, &sp5C, &sp50);
                VECCrossProduct(&sp50, &sp68, &sp5C);
            } else {
                sp50.x = jobj->mtx[0][2];
                sp50.y = jobj->mtx[1][2];
                sp50.z = jobj->mtx[2][2];
                VECCrossProduct(&sp50, &sp68, &sp5C);
                VECCrossProduct(&sp68, &sp5C, &sp50);
            }
            var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp50, &sp50)));
            VECScale(&sp50, &sp80, var_f4);
            var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp5C, &sp5C)));
            VECScale(&sp5C, &sp74, var_f4_2);
            temp_f5 = temp_f30 * temp_f30;
            var_f28 = var_f29 * var_f29;
            temp_f1_7 = temp_f5 - var_f28;
            var_f27 = 0.25F * (((2.0F * (temp_f5 + var_f28)) - temp_f31) -
                               ((temp_f1_7 * temp_f1_7) / temp_f31));
            if (var_f27 < 0.0F) {
                var_f27 = 0.0F;
            }
            temp_f5_2 = (temp_f5 - var_f27) / temp_f31;
            var_f4_3 = sqrtf(1.0F / (1e-10F + temp_f5_2));
            var_f1 = temp_f5_2 * var_f4_3;
            var_f5 = sqrtf(1.0F / (1e-10F + var_f27));
            var_f29_2 = var_f27 * var_f5;
        } else {
            var_f1 = 0.0F;
            var_f29_2 = temp_f30;
        }
        if (var_r30 != 0) {
            var_f29_2 = -var_f29_2;
        }
        if ((var_f28 - var_f27) < temp_f31) {
            VECScale(&sp8C, &sp98, var_f1);
        } else {
            VECScale(&sp8C, &sp98, -var_f1);
        }
        VECScale(&sp74, &sp5C, var_f29_2);
        VECAdd(&sp98, &sp5C, &sp98);
        var_f4_4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp98, &sp98)));
        VECScale(&sp98, &sp98, var_f4_4);
        jobj->mtx[0][0] = sp98.x * spBC.x;
        jobj->mtx[1][0] = sp98.y * spBC.x;
        jobj->mtx[2][0] = sp98.z * spBC.x;
        VECCrossProduct(&sp80, &sp98, &sp5C);
        jobj->mtx[0][1] = sp5C.x * spBC.y;
        jobj->mtx[1][1] = sp5C.y * spBC.y;
        jobj->mtx[2][1] = sp5C.z * spBC.y;
        jobj->mtx[0][2] = sp80.x * spBC.z;
        jobj->mtx[1][2] = sp80.y * spBC.z;
        jobj->mtx[2][2] = sp80.z * spBC.z;
        jobj->mtx[0][3] = spB0.x;
        jobj->mtx[1][3] = spB0.y;
        jobj->mtx[2][3] = spB0.z;
    }
}

static const float jobj_ik_unit_vector[4] = { 1.0F, 1.0F, 1.0F, 0.0F };
#define HSD_JObj_803B94D0 (*(const Vec3*) jobj_ik_unit_vector)

void resolveIKJoint2(HSD_JObj* jobj)
{
    f32 angle;
    Vec3 spA0;
    Vec3 sp94;
    Vec3 sp88;
    Vec3 sp7C;
    Vec3 sp70;
    Vec3 sp64;
    Mtx sp34;
    Vec3 sp28;
    Vec3 sp1C;

    u8 _[4];

    HSD_JObj* var_r29;
    f32 temp_f1_4;
    f32 var_f1_2;
    f32 var_f31;
    f32 var_f4;
    f32 var_f4_2;
    s32 var_r27;
    s32 var_r30;
    HSD_RObj* temp_r28;
    HSD_RObj* temp_r29;
    HSD_RObj* robj;

    var_f31 = 1.0F;
    spA0 = HSD_JObj_803B94D0;
    var_r29 = jobj_get_effector_checked(jobj->child);
    if (var_r29 == NULL || jobj->parent == NULL) {
        return;
    }
    if (jobj->scl != NULL) {
        spA0 = *jobj->scl;
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp88.x = mtx[0][3];
        sp88.y = mtx[1][3];
        sp88.z = mtx[2][3];
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp7C.x = mtx[0][0];
        sp7C.y = mtx[1][0];
        sp7C.z = mtx[2][0];
    }
    var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp7C, &sp7C)));
    VECScale(&sp7C, &sp7C, var_f4);
    if (jobj->parent->scl != NULL) {
        var_f31 = jobj->parent->scl->x;
    }
    robj = HSD_RObjGetByType(jobj->parent->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x8FC, robj);
    VECScale(&sp7C, &sp7C, robj->u.ik_hint.bone_length * var_f31);
    VECAdd(&sp88, &sp7C, &sp94);
    VECSubtract(&var_r29->translate, &sp94, &sp7C);
    VECScale(&sp7C, &sp7C,
             sqrtf(1.0F / (1e-10F + VECDotProduct(&sp7C, &sp7C))));
    temp_r28 = HSD_RObjGetByType(jobj->robj, 0x20000000, 5);
    temp_r29 = HSD_RObjGetByType(jobj->robj, 0x20000000, 6);
    if ((temp_r28 != NULL) || (temp_r29 != NULL)) {
        var_r27 = 0;
        robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x91E, robj);
        var_r30 = robj->flags & 4 ? 1 : 0;
        {
            MtxPtr mtx = jobj->parent->mtx;
            sp28.x = mtx[0][0];
            sp28.y = mtx[1][0];
            sp28.z = mtx[2][0];
        }
        VECNormalize(&sp28, &sp28);
        temp_f1_4 = VECDotProduct(&sp28, &sp7C);
        if (temp_f1_4 >= 1.0F) {
            angle = 0.0F;
        } else if (temp_f1_4 <= -1.0F) {
            angle = M_PI;
        } else {
            angle = acos(temp_f1_4);
        }
        var_f1_2 = angle;
        if (var_r30 == 0) {
            var_f1_2 = -angle;
        }
        if (temp_r28 != NULL && var_f1_2 < temp_r28->u.limit) {
            var_f1_2 = temp_r28->u.limit;
            var_r27 = 1;
        } else if (temp_r29 != NULL) {
            if (temp_r29->u.limit < var_f1_2) {
                var_f1_2 = temp_r29->u.limit;
                var_r27 = 1;
            }
        }
        if (var_r27 != 0) {
            {
                MtxPtr mtx = jobj->parent->mtx;
                sp1C.x = mtx[0][2];
                sp1C.y = mtx[1][2];
                sp1C.z = mtx[2][2];
            }
            PSMTXRotAxisRad(sp34, &sp1C, var_f1_2);
            MTXMultVec(sp34, &sp28, &sp7C);
        }
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp64.x = mtx[0][2];
        sp64.y = mtx[1][2];
        sp64.z = mtx[2][2];
    }
    VECCrossProduct(&sp64, &sp7C, &sp70);
    var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp70, &sp70)));
    VECScale(&sp70, &sp70, var_f4_2);
    VECCrossProduct(&sp7C, &sp70, &sp64);
    jobj->mtx[0][0] = sp7C.x * spA0.x;
    jobj->mtx[1][0] = sp7C.y * spA0.x;
    jobj->mtx[2][0] = sp7C.z * spA0.x;
    jobj->mtx[0][1] = sp70.x * spA0.y;
    jobj->mtx[1][1] = sp70.y * spA0.y;
    jobj->mtx[2][1] = sp70.z * spA0.y;
    jobj->mtx[0][2] = sp64.x * spA0.z;
    jobj->mtx[1][2] = sp64.y * spA0.z;
    jobj->mtx[2][2] = sp64.z * spA0.z;
    jobj->mtx[0][3] = sp94.x;
    jobj->mtx[1][3] = sp94.y;
    jobj->mtx[2][3] = sp94.z;
}

void HSD_JObjSetupMatrixSub(HSD_JObj* jobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    HSD_JObj* parent;
    HSD_RObj* robj;
    f32 x_scale;

    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
    jobj->flags &= ~JOBJ_MTX_DIRTY;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX)) {
        switch (jobj->flags & JOBJ_JOINT) {
        case JOBJ_JOINT1:
            resolveIKJoint1(jobj);
            break;
        case JOBJ_JOINT2:
            resolveIKJoint2(jobj);
            break;
        case JOBJ_EFFECTOR:
            parent = jobj->parent;
            x_scale = 1.0F;
            if (parent != NULL) {
                robj = HSD_RObjGetByType(parent->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    sp1C.x = parent->mtx[0][3];
                    sp1C.y = parent->mtx[1][3];
                    sp1C.z = parent->mtx[2][3];
                    sp10.x = parent->mtx[0][0];
                    sp10.y = parent->mtx[1][0];
                    sp10.z = parent->mtx[2][0];
                    VECScale(
                        &sp10, &sp10,
                        sqrtf(1.0F / (1e-10F + VECDotProduct(&sp10, &sp10))));
                    if (parent->scl != NULL) {
                        x_scale = parent->scl->x;
                    }
                    VECScale(&sp10, &sp10,
                             robj->u.ik_hint.bone_length * x_scale);
                    VECAdd(&sp1C, &sp10, &sp28);
                    jobj->mtx[0][3] = sp28.x;
                    jobj->mtx[1][3] = sp28.y;
                    jobj->mtx[2][3] = sp28.z;
                }
            }
            break;
        default:
            if (jobj->robj != NULL && jobj != NULL && jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, HSD_JOBJ_METHOD(jobj)->update);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= ~JOBJ_MTX_DIRTY;
                }
            }
            break;
        }
        jobj->flags &= ~JOBJ_MTX_DIRTY;
    }
}

#pragma push
#pragma inline_max_size(600)
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj)
{
    jobj->flags |= 0x40;
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            if (!(child->flags & JOBJ_MTX_INDEP_PARENT)) {
                if (!HSD_JObjMtxIsDirty(child)) {
                    HSD_JObjSetMtxDirtySub(child);
                }
            }
            child = child->next;
        }
    }
}
#pragma pop

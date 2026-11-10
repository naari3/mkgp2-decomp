/* math.h declares fabs static inline; in the original it was a plain inline,
 * so the copy emitted where SetRoll does not inline it is weak and the linker
 * resolves the calls to the MSL fabs. */
#define fabs msl_inline_fabs
#include <math.h>
#undef fabs
inline double fabs(double f)
{
    return __fabs(f);
}
#include "cobj_private.h"

/* This file has its own static copy of functions the header declares extern.
 * Metrowerks accepts that; for other compilers the copy gets a name of its own. */
#ifndef __MWERKS__
#define makeProjectionMtx makeProjectionMtx__cobj
#define HSD_CObjSetScissor HSD_CObjSetScissor__cobj
#define HSD_CObjSetViewport HSD_CObjSetViewport__cobj
#endif

int ref_width = 640;
int ref_height = 480;
char lbl_806D0D50[7] = "cobj.c";
char lbl_806D0D58[5] = "cobj";
char lbl_806D0D60[2] = "0";

HSD_CObjInfo hsdCObj = { CObjInfoInit };
/* Assert texts of the dead-stripped HSD_CObjSetRefSize-style setter. */
char lbl_804FC50C[14] = "ref_width > 0";
char lbl_804FC51C[15] = "ref_height > 0";

/* ---- cobj.c ---- */

void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim)
{
    if (cobj == NULL) {
        return;
    }

    if (canim == NULL) {
        return;
    }

    if (cobj->aobj != NULL) {
        HSD_AObjRemove(cobj->aobj);
    }
    cobj->aobj = HSD_AObjLoadDesc(canim->aobjdesc);
    HSD_WObjAddAnim(HSD_CObjGetEyePositionWObj(cobj), canim->eye_anim);
    HSD_WObjAddAnim(HSD_CObjGetInterestWObj(cobj), canim->interest_anim);
}

void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_CObj* cobj = obj;
    Vec3 vec;

    if (cobj == NULL) {
        return;
    }

    switch (type) {
    case 1:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 2:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.y = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 3:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.z = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 5:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 6:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 7:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 9:
        HSD_CObjSetRoll(cobj, val->fv);
        break;
    case 10:
        HSD_CObjSetFov(cobj, val->fv);
        break;
    case 11:
        HSD_CObjSetNear(cobj, val->fv);
        break;
    case 12:
        HSD_CObjSetFar(cobj, val->fv);
        break;
    }
}

char lbl_804FC560[29] = "unkown type of render pass.\n";
char lbl_804FC580[13] = "cobj->eyepos";
char lbl_804FC590[15] = "cobj->interest";
Vec3 upvec2roll_data_804FC5A0 = { 0.0F, 0.0F, 0.0F };
Vec3 upvec2roll_data_804FC5AC = { 0.0F, 1.0F, 0.0F };
char HSD_CObjSetRoll_data_804FC5B8[56] = "illegal up vector.\0\0hsdIsDescendantOf(info, &hsdCObj)";
Vec3 CObjLoad_data_804FC5F0 = { 0.0F, 1.0F, 0.0F };

void HSD_CObjAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(cobj->aobj, cobj, HSD_COBJ_METHOD(cobj)->update);
    HSD_WObjInterpretAnim(cobj->eyepos);
    HSD_WObjInterpretAnim(cobj->interest);
}

void HSD_CObjReqAnim(HSD_CObj* cobj, float startframe)
{
    if (cobj == NULL) {
        return;
    }

    if (cobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(cobj->aobj, startframe);
    HSD_WObjReqAnim(cobj->eyepos, startframe);
    HSD_WObjReqAnim(cobj->interest, startframe);
}

/* ---- cobj_nm1.c ---- */

bool setupTopHalfCamera(HSD_CObj* cobj)
{
    GXProjectionType projection_type;
    Mtx44 p;

    f32 h_scale;
    f32 t;
    f32 b;
    f32 w;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    if (cobj->viewport.ymin >= rmode->efbHeight) {
        return 0;
    }
    left = cobj->viewport.xmin;
    right = cobj->viewport.xmax;
    top = cobj->viewport.ymin;
    bottom = cobj->viewport.ymax < rmode->efbHeight
                 ? cobj->viewport.ymax : rmode->efbHeight;
    width = right - left;
    height = bottom - top;
    GXSetScissor(left, top, width, height);
    top = cobj->viewport.ymin;
    bottom = cobj->viewport.ymax;
    left = cobj->viewport.xmin;
    right = cobj->viewport.xmax;
    height = (bottom < rmode->efbHeight ? bottom : rmode->efbHeight) - top;
    h_scale = height / (bottom - top);
    width = right - left;

    GXSetViewport(left, top, width, height, 0.0f, 1.0f);

    {
        int unused_2[1];

        switch (cobj->projection_type) {
        case PROJ_PERSPECTIVE:
            projection_type = GX_PERSPECTIVE;
            t = cobj->near *
                (float) tan((float) DegToRad(0.5 * cobj->projection_param.perspective.fov));
            w = t * cobj->projection_param.perspective.aspect;
            b = t * -(2.0f * h_scale - 1.0f);
            MTXFrustum(p, t, b, -w, w, cobj->near, cobj->far);
            break;
        case PROJ_FRUSTUM:
            projection_type = GX_PERSPECTIVE;
            MTXFrustum(
                p, cobj->projection_param.perspective.fov,
                -(h_scale * (cobj->projection_param.perspective.fov -
                             cobj->projection_param.perspective.aspect) -
                  cobj->projection_param.perspective.fov),
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        case PROJ_ORTHO:
            projection_type = GX_ORTHOGRAPHIC;
            MTXOrtho(p, cobj->projection_param.perspective.fov,
                     -(h_scale * (cobj->projection_param.perspective.fov -
                                  cobj->projection_param.perspective.aspect) -
                       cobj->projection_param.perspective.fov),
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near,
                     cobj->far);
            break;
        }
    }

    GXSetProjection(p, projection_type);

    return true;
}

/* ---- cobj_bottom.c ---- */

bool setupBottomHalfCamera(HSD_CObj* cobj)
{
    GXProjectionType projection_type;
    Mtx44 p;

    f32 top, bottom;
    f32 left, right;
    f32 width, height, hscale;
    f32 t, b, w, h;
    u32 screen_top;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    screen_top = rmode->efbHeight - 8;

    if (cobj->viewport.ymax < screen_top) {
        return 0;
    }

    top = cobj->scissor.top;
    left = cobj->scissor.left;
    right = cobj->scissor.right;
    top = (cobj->scissor.top > screen_top ? cobj->scissor.top : screen_top) -
          screen_top;
    bottom = cobj->scissor.bottom - screen_top;
    width = right - left;
    height = bottom - top;
    GXSetScissor(left, top, width, height);

    top = cobj->viewport.ymin;                   // lfs f4,0x14(r30)
    left = cobj->viewport.xmin;                  // lfs f1,0xc(r30)
    right = cobj->viewport.xmax;                 // lfs f3,0x10(r30)
    top = (top > screen_top ? top : screen_top); // fcmpo cr0, f4, f0
    bottom = cobj->viewport.ymax;                // lfs f10, 0x18(r30)
    width = right - left;                        // fsubs f3, f3, f1
    height = bottom - cobj->viewport.ymin;       // fsubs f0, f10, f4

    {
        int unused;
        t = top - screen_top;
        h = (bottom - screen_top) - t;

        hscale = h / height; // fdivs r29, f4, f0

        GXSetViewport(left, t, width, h, 0.0f, 1.0f);
    }

    {
        switch (cobj->projection_type) {
        case PROJ_PERSPECTIVE:
            projection_type = GX_PERSPECTIVE;
            b = cobj->near *
                (float) tan((float) DegToRad(0.5 * cobj->projection_param.perspective.fov));
            w = b * cobj->projection_param.perspective.aspect;
            t = b * (2.0f * hscale + -1.0f);
            MTXFrustum(p, t, -b, -w, w, cobj->near, cobj->far);
            break;
        case PROJ_FRUSTUM:
            projection_type = GX_PERSPECTIVE;
            h = (hscale * (cobj->projection_param.perspective.fov -
                           cobj->projection_param.perspective.aspect) +
                 cobj->projection_param.perspective.aspect);
            MTXFrustum(p, h, cobj->projection_param.perspective.aspect,
                       cobj->projection_param.frustum.left,
                       cobj->projection_param.frustum.right, cobj->near,
                       cobj->far);
            break;
        case PROJ_ORTHO:
            projection_type = GX_ORTHOGRAPHIC;
            MTXOrtho(p,
                     (hscale * (cobj->projection_param.perspective.fov -
                                cobj->projection_param.perspective.aspect) +
                      cobj->projection_param.perspective.aspect),
                     cobj->projection_param.perspective.aspect,
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near,
                     cobj->far);
            break;
        }
    }

    GXSetProjection(p, projection_type);

    return true;
}

/* ---- cobj_view.c ---- */

static inline GXProjectionType makeProjectionMtx(HSD_CObj* cobj, Mtx44 mtx)
{
    GXProjectionType projection_type;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        projection_type = GX_PERSPECTIVE;
        MTXPerspective(mtx, cobj->projection_param.perspective.fov,
                       cobj->projection_param.perspective.aspect, cobj->near,
                       cobj->far);
        break;
    case PROJ_FRUSTUM:
        projection_type = GX_PERSPECTIVE;
        MTXFrustum(mtx, cobj->projection_param.perspective.fov,
                   cobj->projection_param.perspective.aspect,
                   cobj->projection_param.frustum.left,
                   cobj->projection_param.frustum.right, cobj->near,
                   cobj->far);
        break;
    case PROJ_ORTHO:
        projection_type = GX_ORTHOGRAPHIC;
        MTXOrtho(mtx, cobj->projection_param.perspective.fov,
                 cobj->projection_param.perspective.aspect,
                 cobj->projection_param.frustum.left,
                 cobj->projection_param.frustum.right, cobj->near, cobj->far);
        break;
    }
    return projection_type;
}

static inline bool setupOffscreenCamera(HSD_CObj* cobj)
{
    Mtx44 mtx;

    GXSetViewport(cobj->viewport.xmin, cobj->viewport.ymin,
                  cobj->viewport.xmax - cobj->viewport.xmin,
                  cobj->viewport.ymax - cobj->viewport.ymin, 0.0f, 1.0f);
    GXSetScissor(cobj->scissor.left, cobj->scissor.top,
                 cobj->scissor.right - cobj->scissor.left,
                 cobj->scissor.bottom - cobj->scissor.top);
    GXSetProjection(mtx, makeProjectionMtx(cobj, mtx));
    return true;
}

static inline bool setupNormalCamera(HSD_CObj* cobj)
{
    GXProjectionType projection_type;
    Mtx44 p;

    f64 x_scale;
    f64 y_scale;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    x_scale = (f64) rmode->fbWidth / ref_width;
    y_scale = (f64) rmode->efbHeight / ref_height;

    left = cobj->viewport.xmin * x_scale;
    right = cobj->viewport.xmax * x_scale;
    top = cobj->viewport.ymin * y_scale;
    bottom = cobj->viewport.ymax * y_scale;

    width = right - left;
    height = bottom - top;

    if (rmode->field_rendering) {
        GXSetViewportJitter(left, top, width, height, 0.0f, 1.0f,
                            VIGetNextField());
    } else {
        GXSetViewport(left, top, width, height, 0.0f, 1.0f);
    }

    left = cobj->scissor.left * x_scale;
    right = cobj->scissor.right * x_scale;
    top = cobj->scissor.top * y_scale;
    bottom = cobj->scissor.bottom * y_scale;
    width = right - left;
    height = bottom - top;
    GXSetScissor(left, top, width, height);

    projection_type = makeProjectionMtx(cobj, p);
    GXSetProjection(p, projection_type);

    return true;
}

void HSD_CObjSetupViewingMtx(HSD_CObj* cobj)
{
    Vec3 eyepos;
    Vec3 up_vec;
    Vec3 interest;

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        if (HSD_CObjGetUpVector(cobj, &up_vec) == 0) {
            up_vec.x = 0.0F;
            up_vec.y = 1.0F;
            up_vec.z = 0.0F;
        }
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
}

bool HSD_CObjSetCurrent(HSD_CObj* cobj)
{
    HSD_RenderPass render_pass;
    bool result;

    if (cobj == NULL) {
        return false;
    }
    render_pass = HSD_GetCurrentRenderPass();
    _HSD_ZListClear();
    current = cobj;
    switch (render_pass) {
    case HSD_RP_OFFSCREEN:
        result = setupOffscreenCamera(cobj);
        break;
    case HSD_RP_SCREEN:
        result = setupNormalCamera(cobj);
        break;
    case HSD_RP_TOPHALF:
        result = setupTopHalfCamera(cobj);
        break;
    case HSD_RP_BOTTOMHALF:
        result = setupBottomHalfCamera(cobj);
        break;
    default:
        HSD_Panic(lbl_806D0D50, 663, lbl_804FC560);
        return false;
    }
    if (!result) {
        return false;
    } else {
        HSD_CObjSetupViewingMtx(cobj);
        return true;
    }
}

void HSD_CObjEndCurrent(void)
{
    _HSD_ZListSort();
    _HSD_ZListDisp();
}

HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    COBJ_ASSERT(700, cobj, lbl_806D0D58);
    return cobj->interest;
}

HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    COBJ_ASSERT(724, cobj, lbl_806D0D58);
    return cobj->eyepos;
}

void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    COBJ_ASSERT(748, cobj, lbl_806D0D58);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest)
{
    COBJ_ASSERT(760, cobj, lbl_806D0D58);
    HSD_WObjSetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    COBJ_ASSERT(772, cobj, lbl_806D0D58);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    COBJ_ASSERT(784, cobj, lbl_806D0D58);
    HSD_WObjSetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

float HSD_CObjGetEyeDistance(HSD_CObj* cobj)
{
    Vec3 position;
    Vec3 interest;
    Vec3 look_vector;

    if (cobj == NULL) {
        return 0.0f;
    }
    COBJ_ASSERT(831, cobj->eyepos, lbl_804FC580);
    COBJ_ASSERT(832, cobj->interest, lbl_804FC590);
    HSD_CObjGetEyePosition(cobj, &position);
    HSD_CObjGetInterest(cobj, &interest);
    VECSubtract(&interest, &position, &look_vector);
    return VECMag(&look_vector);
}

/* ---- cobj_nm2.c ---- */









extern inline int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye)
{
    Vec3 eyepos;
    Vec3 interest;

    int result;
    if (!cobj || !cobj->eyepos || !cobj->interest) {
        result = 0;
    } else {
        if (!eye) {
            return 0;
        }
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetInterest(cobj, &interest);
        VECSubtract(&interest, &eyepos, eye);
        result = vec_normalize_check(eye, eye) == 0;
    }
    return result;
}

extern inline float cobj_absf(float x)
{
    x = fabs(x);
    return x;
}

float upvec2roll(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;
    Vec3 eye;
    Mtx vmtx;
    f32 dot;

    if (!HSD_CObjGetEyeVector(cobj, &eye)) {
        dot = 0.0f;
    } else {
        dot = 1.0f - (float)fabs(VECDotProduct(up, &eye));
        if (dot < FLT_MIN) {
            dot = 0.0f;
        } else {
            C_MTXLookAt(vmtx, &orig, &uy, &eye);
            PSMTXMultVecSR(vmtx, up, &v);
            {
                float x = -v.x;
                float y = v.y;
                if (y == 0.0f) {
                    dot = x >= 0.0f ? 1.5707963267948966f : -1.5707963267948966f;
                } else {
                    dot = atan2(x, y);
                }
            }
        }
    }
    return dot;
}

extern inline f32 vec_get_x(Vec3* v)
{
    return v->x;
}

extern inline f64 vec_get_abs_y(Vec3* v)
{
    return cobj_absf(v->y);
}

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{
    int res;
    Vec3 eye;
    Vec3 v0;
    Vec3 v1;
    Mtx m;

    res = HSD_CObjGetEyeVector(cobj, &eye);
    if (!res) {
        return 0;
    }
    if (1.0 - cobj_absf(eye.y) < 0.0001) {
        v0.x = sqrtf(eye.y * eye.y + eye.z * eye.z);
        v0.y = eye.y * (-vec_get_x(&eye) / v0.x);
        v0.z = eye.z * (-eye.x / v0.x);
    } else {
        v0.y = sqrtf(eye.x * eye.x + eye.z * eye.z);
        v0.x = eye.x * (-eye.y / v0.y);
        v0.z = eye.z * (-eye.y / v0.y);
    }
    PSMTXRotAxisRad(m, &eye, -roll);
    PSMTXMultVecSR(m, &v0, &v1);
    VECNormalize(&v1, up);
    return 1;
}

/* ---- cobj_up.c ---- */

int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up)
{
    if (cobj == NULL || up == NULL) {
        return 0;
    }
    if ((cobj->flags & 1) != 0) {
        *up = cobj->u.up;
        return 1;
    }
    return roll2upvec(cobj, up, cobj->u.roll);
}

/* ---- cobj_nm3.c ---- */



















extern inline f32 cobj_get_up_x(Vec3* up)
{
    return up->x;
}

#pragma push
#pragma optimization_level 3
void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;
    /* The shared cobj data pool starts at its class descriptor. Its intervening
     * jump table is owned by cobj.c, so retain the existing external pool. */
    if (!cobj || !up) {
        return;
    }
    if ((cobj->flags & 1) != 0) {
        if (vec_normalize_check(up, &v)) {
            OSReport(HSD_CObjSetRoll_data_804FC5B8);
            __assert(lbl_806D0D50, 976, lbl_806D0D60);
        }
        if (cobj->u.up.x != cobj_get_up_x(&v) || cobj->u.up.y != v.y ||
            cobj->u.up.z != v.z)
        {
            HSD_CObjSetMtxDirty(cobj);
            cobj->u.up = v;
        }
    } else {
        HSD_CObjSetRoll(cobj, upvec2roll(cobj, up));
    }
}
#pragma pop


/* ---- cobj_mtx.c ---- */

void HSD_CObjSetMtxDirty(HSD_CObj* cobj)
{
    cobj->flags |= (1 << 30) | (1 << 31);
}

bool HSD_CObjMtxIsDirty(HSD_CObj* cobj)
{
    return (cobj->flags & (1 << 30)) ||
           (cobj->eyepos != NULL && (cobj->eyepos->flags & 2)) ||
           (cobj->interest != NULL && (cobj->interest->flags & 2));
}

void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx)
{
    PSMTXCopy(HSD_CObjGetViewingMtxPtr(cobj), mtx);
}

MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj)
{
    if (cobj->flags & (1 << 31)) {
        if (cobj->proj_mtx == NULL) {
            cobj->proj_mtx = HSD_MtxAlloc();
        }
        PSMTXInverse(cobj->view_mtx, *cobj->proj_mtx);
        HSD_CObjClearFlags(cobj, (1 << 31));
    }
    return *cobj->proj_mtx;
}

MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj)
{
    HSD_CObjSetupViewingMtx(cobj);
    return cobj->view_mtx;
}

MtxPtr HSD_CObjGetInvViewingMtxPtr(HSD_CObj* cobj)
{
    HSD_CObjSetupViewingMtx(cobj);
    return HSD_CObjGetInvViewingMtxPtrDirect(cobj);
}

/* ---- cobj_nm4.c ---- */











// Internal callers provide a local output vector.
















void HSD_CObjSetRoll(HSD_CObj* cobj, float roll)
{
    Vec3 up;

    if (!cobj) {
        return;
    }

    if ((cobj->flags & 1) != 0) {
        roll2upvec(cobj, &up, roll);
        HSD_CObjSetUpVector(cobj, &up);
    } else {
        if (cobj->u.roll != roll) {
            HSD_CObjSetMtxDirty(cobj);
        }
        cobj->u.roll = roll;
    }
}

/* ---- cobj_tail.c ---- */

HSD_ClassInfo* default_class = NULL;
HSD_CObj* current = NULL;







float HSD_CObjGetFov(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return 0.0f;
    }
    return cobj->projection_param.perspective.fov;
}

void HSD_CObjSetFov(HSD_CObj* cobj, float fov)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.fov = fov;
}

float HSD_CObjGetAspect(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return 0.0f;
    }
    return cobj->projection_param.perspective.aspect;
}

void HSD_CObjSetAspect(HSD_CObj* cobj, float aspect)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.aspect = aspect;
}

float HSD_CObjGetNear(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->near;
}

void HSD_CObjSetNear(HSD_CObj* cobj, float near)
{
    if (cobj != NULL) {
        cobj->near = near;
    }
}

float HSD_CObjGetFar(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->far;
}

void HSD_CObjSetFar(HSD_CObj* cobj, float far)
{
    if (cobj != NULL) {
        cobj->far = far;
    }
}

static inline void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor = *scissor;
}

void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top,
                          u16 bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor.left = left;
    cobj->scissor.right = right;
    cobj->scissor.top = top;
    cobj->scissor.bottom = bottom;
}

static inline void HSD_CObjSetViewport(HSD_CObj* cobj, HSD_RectS16* viewport)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.xmin = viewport->xmin;
    cobj->viewport.xmax = viewport->xmax;
    cobj->viewport.ymin = viewport->ymin;
    cobj->viewport.ymax = viewport->ymax;
}

void HSD_CObjSetViewportfx4(HSD_CObj* cobj, float left, float right, float top,
                            float bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.xmin = left;
    cobj->viewport.xmax = right;
    cobj->viewport.ymin = top;
    cobj->viewport.ymax = bottom;
}

int HSD_CObjGetProjectionType(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 1;
    }
    return cobj->projection_type;
}

void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = proj_type;
}

void HSD_CObjSetPerspective(HSD_CObj* cobj, float fov, float aspect)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_PERSPECTIVE;
    cobj->projection_param.perspective.fov = fov;
    cobj->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetFrustum(HSD_CObj* cobj, float top, float bottom, float left,
                        float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_FRUSTUM;
    cobj->projection_param.frustum.top = top;
    cobj->projection_param.frustum.bottom = bottom;
    cobj->projection_param.frustum.left = left;
    cobj->projection_param.frustum.right = right;
}

void HSD_CObjSetOrtho(HSD_CObj* cobj, float top, float bottom, float left,
                      float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_ORTHO;
    cobj->projection_param.ortho.top = top;
    cobj->projection_param.ortho.bottom = bottom;
    cobj->projection_param.ortho.left = left;
    cobj->projection_param.ortho.right = right;
}

void HSD_CObjGetPerspective(HSD_CObj* cobj, float* top, float* bottom)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.perspective.fov;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.perspective.aspect;
    }
}

void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags |= flags;
}

void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags &= ~flags;
}

HSD_CObj* HSD_CObjGetCurrent(void)
{
    return current;
}

HSD_CObj* HSD_CObjAlloc(void)
{
    HSD_CObj* cobj = HSD_COBJ(
        hsdNew(default_class ? default_class : &hsdCObj.parent.parent));
    COBJ_ASSERT(1936, cobj, lbl_806D0D58);
    return cobj;
}

static inline void CObjResetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags = (cobj->flags & 0xC0000000) | (flags & ~0xC0000000);
}

int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* desc)
{

    cobj->flags = desc->common.flags;
    CObjResetFlags(cobj, desc->common.flags);
    HSD_CObjSetViewport(cobj, &desc->common.viewport);
    HSD_CObjSetScissor(cobj, &desc->common.scissor);
    HSD_WObjInit(cobj->eyepos, desc->common.eyepos);
    HSD_WObjInit(cobj->interest, desc->common.interest);
    HSD_CObjSetNear(cobj, desc->common.nnear);
    HSD_CObjSetFar(cobj, desc->common.ffar);
    if (desc->common.flags & 1) {
        if (desc->common.up_vector != NULL) {
            HSD_CObjSetUpVector(cobj, desc->common.up_vector);
        } else {
            HSD_CObjSetUpVector(cobj, &CObjLoad_data_804FC5F0);
        }
    } else {
        HSD_CObjSetRoll(cobj, desc->common.roll);
    }
    switch (desc->common.projection_type) {
    case PROJ_PERSPECTIVE:
        HSD_CObjSetPerspective(cobj, desc->perspective.fov,
                               desc->perspective.aspect);
        break;
    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, desc->ortho.top, desc->ortho.bottom,
                         desc->ortho.left, desc->ortho.right);
        break;
    case PROJ_FRUSTUM:
        HSD_CObjSetFrustum(cobj, desc->frustum.top, desc->frustum.bottom,
                           desc->frustum.left, desc->frustum.right);
        break;
    default:
        COBJ_ASSERT(1982, 0, lbl_806D0D60);
        break;
    }
    return 0;
}

HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc)
{
    HSD_ClassInfo* info;
    HSD_CObj* cobj;

    if (desc != NULL) {
        if (desc->class_name == NULL ||
            (info = hsdSearchClassInfo(desc->class_name)) == NULL)
        {
            cobj = HSD_CObjAlloc();
        } else {
            cobj = hsdNew(info);
            COBJ_ASSERT(2021, cobj, lbl_806D0D58);
        }
        HSD_COBJ_METHOD(cobj)->load(cobj, desc);
        return cobj;
    }
    return NULL;
}

int CObjInit(HSD_Class* o)
{
    HSD_CObj* cobj;
    int status = HSD_OBJECT_PARENT_INFO(&hsdCObj)->init(o);
    if (status < 0) {
        return status;
    }
    cobj = HSD_COBJ(o);
    if (cobj != NULL) {
        HSD_CObjSetMtxDirty(cobj);
    }
    cobj->eyepos = HSD_WObjAlloc();
    cobj->interest = HSD_WObjAlloc();
    return 0;
}

void CObjRelease(HSD_Class* o)
{
    HSD_WObj* eyepos;
    HSD_WObj* interest;
    HSD_CObj* cobj = HSD_COBJ(o);

    HSD_AObjRemove(cobj->aobj);
    eyepos = HSD_CObjGetEyePositionWObj(cobj);
    HSD_WObjUnref(eyepos);
    interest = HSD_CObjGetInterestWObj(cobj);
    HSD_WObjUnref(interest);
    if (cobj->proj_mtx != NULL) {
        HSD_MtxFree(cobj->proj_mtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->release(o);
}

void CObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdCObj)) {
        current = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->amnesia(info);
}

/* ---- cobj_info_nm.c ---- */


void CObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdCObj), &hsdObj,
                     "sysdolphin_base_library", "hsd_cobj",
                     sizeof(HSD_CObjInfo), sizeof(HSD_CObj));

    HSD_CLASS_INFO(&hsdCObj)->init = CObjInit;
    HSD_CLASS_INFO(&hsdCObj)->release = CObjRelease;
    HSD_CLASS_INFO(&hsdCObj)->amnesia = CObjAmnesia;
    hsdCObj.load = CObjLoad;
    hsdCObj.update = CObjUpdateFunc;
}

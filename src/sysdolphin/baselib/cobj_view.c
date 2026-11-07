#include "cobj_private.h"

#define makeProjectionMtx cobj_inline_makeProjectionMtx
#define setupOffscreenCamera cobj_inline_setupOffscreenCamera
#define setupNormalCamera cobj_inline_setupNormalCamera
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

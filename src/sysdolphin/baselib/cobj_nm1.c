#include "cobj_private.h"

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
    bottom = cobj->viewport.ymax;
    bottom = bottom < rmode->efbHeight ? bottom : rmode->efbHeight;
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

#include "cobj_private.h"

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

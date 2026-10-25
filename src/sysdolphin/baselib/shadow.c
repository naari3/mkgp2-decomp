#include "shadow.h"

#include <math.h>
#include <string.h>

#include "class.h"
#include "cobj.h"
#include "debug.h"
#include "jobj.h"
#include "list.h"
#include "lobj.h"
#include "memory.h"
#include "mobj.h"
#include "mtx.h"
#include "object.h"
#include "perf.h"
#include "pobj.h"
#include "state.h"
#include "tev.h"
#include "tobj.h"
#include "util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

HSD_ObjAllocData shadow_alloc_data;

static void makeMatrix(HSD_Shadow* shadow);
// HSD mtx.c helper (unnamed yet): makes a vector perpendicular to src.
void fn_802D74F0(Vec3* src, Vec3* dst);

HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
    return &shadow_alloc_data;
}

void HSD_ShadowInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_ShadowGetAllocData(), sizeof(HSD_Shadow), 4);
}

HSD_TObj* makeShadowTObj(void)
{
    HSD_TObj* shadowTObj;
    shadowTObj = HSD_TObjAlloc();
    shadowTObj->src = 0;
    shadowTObj->wrap_s = 0;
    shadowTObj->wrap_t = 0;
    shadowTObj->flags = 0x540103;
    shadowTObj->imagedesc = HSD_ImageDescAlloc();
    return shadowTObj;
}

HSD_Shadow* HSD_ShadowAlloc(void)
{
    HSD_Shadow* shadow;

    shadow = HSD_ObjAlloc(HSD_ShadowGetAllocData());
    memset(shadow, 0, sizeof(HSD_Shadow));
    shadow->camera = HSD_CObjAlloc();
    shadow->texture = makeShadowTObj();

    shadow->scaleS = 0.5F;
    shadow->scaleT = -0.5F;
    shadow->transS = 0.5F;
    shadow->transT = 0.5F;
    shadow->intensity = 0;

    shadow->texture->imagedesc->format = 0;
    shadow->texture->imagedesc->width = 256;
    shadow->texture->imagedesc->height = 256;

    HSD_CObjSetViewportfx4(shadow->camera, 0.0f, 256.f, 0.0f, 256.f);
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

void HSD_ShadowRemove(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_TObj* tobj;

    if (shadow == NULL) {
        return;
    }
    if ((cobj = shadow->camera) != NULL) {
        if (ref_DEC(cobj)) {
            hsdDelete(cobj);
        }
    }
    HSD_ShadowDeleteObject(shadow, 0);
    if (shadow->active) {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
    if (shadow->texture->imagedesc->image_ptr != NULL) {
        HSD_Free(shadow->texture->imagedesc->image_ptr);
    }
    tobj = shadow->texture;
    HSD_ImageDescFree(tobj->imagedesc);
    HSD_TObjFree(tobj);
    HSD_ObjFree(HSD_ShadowGetAllocData(), shadow);
}

void HSD_ShadowInit(HSD_Shadow* shadow)
{
    HSD_ImageDesc* imagedesc;

    HSD_ASSERT(245, shadow);
    imagedesc = shadow->texture->imagedesc;
    GXSetTexCopySrc(0, 0, imagedesc->width, imagedesc->height);
    GXSetTexCopyDst(imagedesc->width, imagedesc->height, 0x20, 0);
}

void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height)
{
    u32 size;
    HSD_ImageDesc* idesc;

    HSD_ASSERT(277, shadow);
    HSD_ASSERT(278, width > 0);
    HSD_ASSERT(279, height > 0);

    idesc = shadow->texture->imagedesc;
    if (!idesc->image_ptr || idesc->width != width || idesc->height != height)
    {
        if (idesc->image_ptr) {
            HSD_Free(idesc->image_ptr);
        }

        size = GXGetTexBufferSize(width, height, GX_TF_I4, GX_FALSE, 0);
        HSD_ASSERT(0x122, size > 0);
        idesc->image_ptr = HSD_MemAlloc(size);
        idesc->width = width;
        idesc->height = height;

        HSD_CObjSetViewportfx4(shadow->camera, 0, width, 0, height);
        HSD_CObjSetScissorx4(shadow->camera, 0, width, 0, height);
    }
}

// mkgp2: FLT_EPSILON here is MSL's __float_epsilon, not melee's literal.
extern f32 __float_epsilon[];

void HSD_ShadowStartRender(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    HSD_SList* list;

    HSD_ASSERT(345, shadow);
    HSD_ASSERT(346, shadow->camera);
    HSD_ASSERT(347, shadow->texture);
    HSD_ASSERT(348, shadow->texture->imagedesc);

    cobj = shadow->camera;
    idesc = shadow->texture->imagedesc;

    if (shadow->active) {
            static HSD_Chan chan = {
                NULL,           GX_COLOR0A0,      0,
                { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, GX_FALSE,
                GX_SRC_REG,     GX_SRC_REG,       GX_LIGHT_NULL,
                GX_DF_CLAMP,    GX_AF_NONE,       NULL,
            };
            static HSD_TevDesc tev = {
                NULL,
                TEVCONF_MODE,
                GX_TEVSTAGE0,
                GX_TEXCOORD_NULL,
                GX_TEXMAP_NULL,
                GX_COLOR0A0,
                {
                    GX_TEV_ADD, GX_CC_ZERO,    GX_CC_ZERO,    GX_CC_ZERO,
                    GX_CC_RASC, GX_CS_SCALE_1, GX_TB_ZERO,    GX_TRUE,
                    GX_TEVPREV, GX_TEV_ADD,    GX_CA_ZERO,    GX_CA_ZERO,
                    GX_CA_ZERO, GX_CA_RASA,    GX_CS_SCALE_1, GX_TB_ZERO,
                    GX_TRUE,    GX_TEVPREV,    GX_TC_LINEAR,
                }
            };
            static HSD_PEDesc pedesc = {
                9, // ENABLE_COLOR_UPDATE | BEFORE_TEX,
                0,
                0,
                0,
                GX_BM_NONE,
                GX_BL_SRCALPHA,
                GX_BL_INVSRCALPHA,
                GX_LO_SET,
                GX_ALWAYS,
                GX_ALWAYS,
                GX_AOP_AND,
                GX_ALWAYS
            };

            Mtx44 proj;

            HSD_StateInitTev();
            HSD_SetupTevStageAll(&tev);

            HSD_StateSetNumTexGens();

            HSD_SetupPEMode(0, &pedesc);

            chan.mat_color.r = 255;
            chan.mat_color.g = 255;
            chan.mat_color.b = 255;

            HSD_SetupChannelAll(&chan);

            // mkgp2: clear the texture with a unit quad instead of
            // drawBackgroundRect.
            MTXOrtho(proj, 1.0F, 0.0F, 0.0F, 1.0F, -1.0F, 1.0F);
            GXSetProjection(proj, GX_ORTHOGRAPHIC);
            GXSetViewport(0.0F, 0.0F, idesc->width, idesc->height, 0.0F,
                          1.0F);
            GXSetScissor(0, 0, idesc->width, idesc->height);
            GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
            HSD_PerfCountMtxLoad();
            GXSetCurrentMtx(GX_PNMTX0);
            HSD_ClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U8, 0);
            HSD_StateSetCullMode(GX_CULL_BACK);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition2u8(0, 1);
            GXPosition2u8(1, 1);
            GXPosition2u8(1, 0);
            GXPosition2u8(0, 0);
            GXEnd();

            chan.mat_color.r = shadow->intensity;
            chan.mat_color.g = shadow->intensity;
            chan.mat_color.b = shadow->intensity;

            HSD_SetupChannelAll(&chan);

        if (shadow->objects != NULL &&
            HSD_CObjGetEyeDistance(cobj) >= __float_epsilon[0] &&
            HSD_CObjSetCurrent(cobj))
        {
            GXSetScissor(2, 2, idesc->width - 4, idesc->height - 4);
            for (list = shadow->objects; list != NULL; list = list->next) {
                HSD_JObjDispAll(list->data, NULL,
                                (HSD_TrspMask) (HSD_TRSP_OPA | HSD_TRSP_TEXEDGE),
                                RENDER_SHADOW);
            }
            HSD_CObjEndCurrent();
        }
    }
}

void HSD_ShadowEndRender(HSD_Shadow* shadow)
{
    HSD_ImageDesc* idesc;

    HSD_ASSERT(0x1ED, shadow);

    idesc = shadow->texture->imagedesc;
    if (!idesc->image_ptr) {
        HSD_ShadowSetSize(shadow, idesc->width, idesc->height);
    }

    GXCopyTex(idesc->image_ptr, GX_TRUE);
    GXPixModeSync();

    GXInvalidateTexAll();

    makeMatrix(shadow);
}

void fn_802C7240(HSD_CObj* cobj, Vec3* interest);
void fn_802C7384(HSD_CObj* cobj, Vec3* eye);
bool fn_802C5C68(HSD_LObj* lobj, Vec3* pos);

void fn_802DBB84(HSD_Shadow* shadow, HSD_LObj* lobj, f32 distance)
{
    Vec3 eye;
    Vec3 interest;
    Vec3 dir;

    HSD_ASSERT(0x211, shadow);
    HSD_ASSERT(0x212, lobj);

    switch (lobj->flags & LOBJ_TYPE_MASK) {
    case LOBJ_INFINITE:
        fn_802C7240(shadow->camera, &interest);
        fn_802C5C68(lobj, &dir);
        PSVECScale(&dir, &dir, distance / (__float_epsilon[0] + Vec3_Magnitude(&dir)));
        PSVECAdd(&interest, &dir, &eye);
        fn_802C7384(shadow->camera, &eye);
        break;
    case LOBJ_POINT:
    case LOBJ_SPOT:
        fn_802C5C68(lobj, &eye);
        fn_802C7384(shadow->camera, &eye);
        break;
    default:
        HSD_ASSERT(0x224, 0);
    }
}

void HSD_ShadowSetActive(HSD_Shadow* shadow, int active)
{
    HSD_ImageDesc* idesc;

    HSD_ASSERT(0x23A, shadow);

    if ((shadow->active && active) || (!shadow->active && !active)) {
        return;
    }

    shadow->active = active;
    if (active) {
        idesc = shadow->texture->imagedesc;
        if (!idesc->image_ptr) {
            HSD_ShadowSetSize(shadow, idesc->width, idesc->height);
        }

        HSD_MObjAddShadowTexture(shadow->texture);
    } else {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
}


void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    HSD_SList* list;

    if (!shadow || !jobj) {
        return;
    }

    for (list = shadow->objects; list; list = list->next) {
        if (list->data == jobj) {
            return;
        }
    }
    shadow->objects = HSD_SListAllocAndPrepend(shadow->objects, jobj);
    HSD_JObjRef(jobj);
}

void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    if (!shadow) {
        return;
    }

    if (jobj) {
        HSD_SList** list = &(shadow->objects);
        for (; *list; list = &((*list)->next)) {
            if ((*list)->data == jobj) {
                HSD_JObjUnref(jobj);
                (*list) = HSD_SListRemove(*list);
                return;
            }
        }
    } else {
        while (shadow->objects) {
            HSD_JObjUnref(shadow->objects->data);
            shadow->objects = HSD_SListRemove(shadow->objects);
        }
    }
}

static void makeMatrix(HSD_Shadow* shadow)
{
    Mtx Mprj;

    // mkgp2: a camera with no eye distance projects everything to (0, 0).
    if (HSD_CObjGetEyeDistance(shadow->camera) < __float_epsilon[0]) {
        static Mtx zero = {
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, 0.0F, 0.0F, 0.0F },
            { 0.0F, 0.0F, 0.0F, 1.0F },
        };
        PSMTXCopy(zero, shadow->texture->mtx);
        return;
    }

    switch (HSD_CObjGetProjectionType(shadow->camera)) {
    case PROJ_PERSPECTIVE:
        MTXLightPerspective(
            Mprj, shadow->camera->projection_param.perspective.fov,
            shadow->camera->projection_param.perspective.aspect,
            shadow->scaleS, shadow->scaleT, shadow->transS, shadow->transT);
        break;

    case PROJ_FRUSTUM:
        MTXLightFrustum(Mprj, shadow->camera->projection_param.frustum.top,
                        shadow->camera->projection_param.frustum.bottom,
                        shadow->camera->projection_param.frustum.left,
                        shadow->camera->projection_param.frustum.right,
                        shadow->camera->near, shadow->scaleS, shadow->scaleT,
                        shadow->transS, shadow->transT);
        break;

    case PROJ_ORTHO:
        MTXLightOrtho(Mprj, shadow->camera->projection_param.ortho.top,
                      shadow->camera->projection_param.ortho.bottom,
                      shadow->camera->projection_param.ortho.left,
                      shadow->camera->projection_param.ortho.right,
                      shadow->scaleS, shadow->scaleT, shadow->transS,
                      shadow->transT);
        break;

    default:
        HSD_ASSERT(0x2BB, 0);
    }

    MTXConcat(Mprj, HSD_CObjGetViewingMtxPtrDirect(shadow->camera),
              shadow->texture->mtx);
}

#define HSD_ASSERT2(line, text, cond)                                         \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, text))

extern f32 __float_min[];
double atan2(double, double);

void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right)
{
    HSD_CObj* cobj;
    float distance;

    HSD_ASSERT(722, shadow);

    cobj = shadow->camera;
    distance = HSD_CObjGetEyeDistance(cobj);
    if (distance < __float_epsilon[0]) {
        return;
    }

    switch (HSD_CObjGetProjectionType(cobj)) {
    case PROJ_PERSPECTIVE: {
        float width, height;

        if (fabs(top) > fabs(bottom)) {
            width = fabs(top);
        } else {
            width = fabs(bottom);
        }
        if (fabs(left) > fabs(right)) {
            height = fabs(left);
        } else {
            height = fabs(right);
        }
        HSD_CObjSetAspect(cobj, height / (width + __float_epsilon[0]));
        HSD_CObjSetFov(cobj, MTXRadToDeg((f32) atan2(width, distance)));
    } break;

    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, top, bottom, left, right);
        break;

    case PROJ_FRUSTUM: {
        float scale = HSD_CObjGetNear(cobj) / distance;
        if (scale < __float_epsilon[0]) {
            scale = __float_epsilon[0];
        }
        HSD_CObjSetFrustum(cobj, scale * top, scale * bottom, scale * left,
                           scale * right);
    } break;

    default:
        HSD_ASSERT(767, 0);
    }
}

static inline int ViewingRectNormalize(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (__fabsf(src->x) <= __float_min[0] && __fabsf(src->y) <= __float_min[0] &&
        __fabsf(src->z) <= __float_min[0])
    {
        return -1;
    }
    VECNormalize(src, dst);
    return 0;
}

void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest,
                         Vec3* upvector, int perspective)
{
    HSD_ASSERT(0x31E, rect);

    rect->invalid = 0;
    rect->origin = *position;
    VECSubtract(interest, position, &rect->eye_v);
    if (ViewingRectNormalize(&rect->eye_v, &rect->eye_vn) < 0) {
        rect->invalid = 1;
        return;
    }
    VECCrossProduct(&rect->eye_vn, upvector, &rect->right_v);
    if (ViewingRectNormalize(&rect->right_v, &rect->right_v) < 0) {
        fn_802D74F0(&rect->eye_vn, &rect->right_v);
        VECNormalize(&rect->right_v, &rect->right_v);
    }
    VECCrossProduct(&rect->right_v, &rect->eye_vn, &rect->up_v);
    rect->distance = VECMag(&rect->eye_v);

    rect->top = rect->right = -F32_MAX;
    rect->bottom = rect->left = F32_MAX;
    rect->perspective = perspective != 0;
}

int HSD_ViewingRectCheck(HSD_ViewingRect* rect)
{
    HSD_ASSERT(0x33C, rect);
    return !rect->invalid && rect->top > rect->bottom && rect->right > rect->left;
}

void HSD_ViewingRectAddSphere(HSD_ViewingRect* rect, Vec3* position,
                               f32 radius)
{
    float x, y, dot, scale;
    Vec3 o2p, e2p;

    HSD_ASSERT(937, rect);
    HSD_ASSERT(938, position);

    if (rect->invalid) {
        return;
    }
    VECSubtract(position, &rect->origin, &o2p);
    dot = VECDotProduct(&o2p, &rect->eye_vn);
    if (rect->perspective) {
        if (dot <= 0.0F) {
            return;
        }
        scale = rect->distance / dot;
        radius *= scale;
        if (rect->distance <= radius) {
            return;
        }
        VECScale(&o2p, &o2p, scale);
        VECSubtract(&o2p, &rect->eye_v, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);
        if (radius > 0.0F) {
            float a, d2, m, b, e;

            radius = radius * radius;
            d2 = rect->distance * rect->distance;
            m = VECDotProduct(&e2p, &e2p);
            a = d2 - radius;
            b = radius * sqrtf(m);
            e = radius * (d2 + m);
            HSD_ASSERT(967, a > 0.0F);
            e = sqrtf(b * b + a * e);
            radius = (b + e) / a;
        }
    } else {
        Vec3 tmp;
        VECScale(&rect->eye_vn, &tmp, dot);
        VECSubtract(&o2p, &tmp, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);
    }

    if (x + radius > rect->right) {
        rect->right = x + radius;
    }
    if (x - radius < rect->left) {
        rect->left = x - radius;
    }
    if (y + radius > rect->top) {
        rect->top = y + radius;
    }
    if (y - radius < rect->bottom) {
        rect->bottom = y - radius;
    }
}


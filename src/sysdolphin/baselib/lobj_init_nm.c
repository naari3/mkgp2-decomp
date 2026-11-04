#include "lobj_private.h"

#include "lobj_inline.h"
#undef __FILE__
#define __FILE__ "lobj.c"
HSD_LObjInfo* lobj_default_class = NULL;

HSD_SList* current_lights;
HSD_LObj* active_lights[MAX_GXLIGHT];
s32 nb_active_lights = 0;

s32 lightmask_diffuse;
s32 lightmask_specular;
s32 lightmask_attnfunc;
s32 lightmask_alpha;

static inline int LObjNormalizeNoCheck(Vec3* src, Vec3* dst)
{
    if (fabsf(src->x) <= LOBJ_FLT_MIN && fabsf(src->y) <= LOBJ_FLT_MIN &&
        fabsf(src->z) <= LOBJ_FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

void HSD_LObjSetupSpecularInit(Mtx pmtx)
{
    s32 num;
    HSD_LObj* lobj;
    int i;
    Vec3 cdir;
    Vec3 jpos;

    jpos.x = pmtx[0][3];
    jpos.y = pmtx[1][3];
    jpos.z = pmtx[2][3];
    if (LObjNormalizeNoCheck(&jpos, &cdir) != 0) {
        cdir.x = 0.0F;
        cdir.y = 0.0F;
        cdir.z = -1.0F;
    }

    num = nb_active_lights;
    for (i = 0; i < num; i++) {
        Vec3 half, ldir;
        if (0 <= i && i < MAX_GXLIGHT - 1) {
            lobj = active_lights[i];
        } else {
            lobj = NULL;
        }

        if (lobj->spec_id == GX_LIGHT_NULL) {
            continue;
        }

        switch (HSD_LObjGetType(lobj)) {
        case LOBJ_POINT:
        case LOBJ_SPOT:
            PSVECSubtract(&jpos, &lobj->lvec, &ldir);
            if (LObjNormalizeNoCheck(&ldir, &ldir) == 0) {
                PSVECAdd(&ldir, &cdir, &half);
            } else {
                half.x = 0.0F;
                half.y = 0.0F;
                half.z = 1.0F;
                goto set_dir;
            }
            break;

        case LOBJ_INFINITE:
            PSVECAdd(&lobj->lvec, &cdir, &half);
            break;

        default:
            HSD_ASSERT(634, 0);
        }
        if (LObjNormalizeNoCheck(&half, &half) != 0) {
            half.x = 0.0F;
            half.y = 0.0F;
            half.z = 1.0F;
        }
    set_dir:
        GXInitLightDir(&lobj->spec_lightobj, half.x, half.y, half.z);
        lobj->flags |= LOBJ_SPEC_DIRTY;
    }
}

static void setup_diffuse_lightobj(HSD_LObj* lobj)
{
    u32 _ = lobj->flags;

    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    lobj->flags |= LOBJ_DIFF_DIRTY;
    lightmask_diffuse |= lobj->id;

    switch (HSD_LObjGetType(lobj)) {
    case LOBJ_SPOT:
    case LOBJ_POINT:
        lightmask_attnfunc |= lobj->id;
        break;
    case LOBJ_INFINITE:
        break;
    default:
        HSD_ASSERT(642, 0);
    }

    if (lobj->flags & LOBJ_ALPHA) {
        lightmask_alpha |= lobj->id;
    }
}

static void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;

    lobj->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&lobj->spec_lightobj, lobj->color);
        lobj->shininess = 50.0F;

        x =
#ifdef MUST_MATCH
            x =
#endif
                lobj->shininess;

        x *= 0.5F;
        GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, x, 0.0F,
                        1.0F - x);
        switch (HSD_LObjGetType(lobj)) {
        case 2:
        case 3:
            HSD_LObjGetPosition(lobj, &lobj->lvec);
            MTXMultVec(mtx, &lobj->lvec, &lobj->lvec);
            break;
        case 1:
            HSD_LObjGetLightVector(lobj, &lobj->lvec);
            PSMTXMultVecSR(mtx, &lobj->lvec, &lobj->lvec);
            VECNormalize(&lobj->lvec, &lobj->lvec);
            break;
        default:
            HSD_ASSERT(680, 0);
        }
        lobj->flags |= 0x100;
        lightmask_specular |= spec_id;
    }
}

static void setup_infinite_lightobj(HSD_LObj* lobj, MtxPtr vmtx)
{
    Vec3 lpos;

    HSD_LObjGetPosition(lobj, &lpos);
    lpos.x *= 1048576.0F;
    lpos.y *= 1048576.0F;
    lpos.z *= 1048576.0F;
    MTXMultVec(vmtx, &lpos, &lpos);
    if (lobj->flags & LOBJ_DIFFUSE) {
        GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
        GXInitLightAttn(&lobj->lightobj, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }
    if (lobj->flags & LOBJ_SPECULAR) {
        GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    }
}

static void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;

    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, 1.0F, 0.0F, 0.0F, lobj->u.attn.k0,
                        lobj->u.attn.k1, lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.spot.ref_br;
        f32 ref_dist = lobj->u.spot.ref_dist;
        s32 dist_func = lobj->u.spot.dist_func;
        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, 0.0F, 0);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
    }
}

static void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    Vec3 ldir;

    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    HSD_LObjGetLightVector(lobj, &ldir);
    PSMTXMultVecSR(mtx, &ldir, &ldir);
    PSVECNormalize(&ldir, &ldir);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightDir(&lobj->lightobj, ldir.x, ldir.y, ldir.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, lobj->u.attn.a0, lobj->u.attn.a1,
                        lobj->u.attn.a2, lobj->u.attn.k0, lobj->u.attn.k1,
                        lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.point.ref_br;
        f32 ref_dist = lobj->u.point.ref_dist;
        f32 cutoff = lobj->u.point.cutoff;
        s32 spot_func = lobj->u.spot.spot_func;
        s32 dist_func = lobj->u.spot.dist_func;

        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, cutoff, spot_func);
    }
}

void HSD_LObjSetupInit(HSD_CObj* cobj)
{
    MtxPtr vmtx;
    int i, num, idx;
    HSD_SList* list;

    idx = 0;
    num = 0;

    lightmask_diffuse = GX_LIGHT_NULL;
    lightmask_specular = GX_LIGHT_NULL;
    lightmask_attnfunc = GX_LIGHT_NULL;
    lightmask_alpha = GX_LIGHT_NULL;
    vmtx = cobj->view_mtx;

    HSD_LObjClearActive();

    for (list = current_lights; idx < MAX_GXLIGHT - 1 && list;
         list = list->next)
    {
        HSD_LObj* lobj = list->data;
        u32 flags;
        u32 type;
        int ref_type;

        HSD_ASSERT(0x334, lobj);
        flags = lobj->flags;

        if (flags & LOBJ_HIDDEN) {
            continue;
        }

        type = HSD_LObjGetType(lobj);
        ref_type = flags & (LOBJ_DIFFUSE | LOBJ_SPECULAR);

        if (type != 0) {
            switch (ref_type) {
            case 8:
                if (num >= 8) {
                    continue;
                }
                break;
            case 4:
            case 12:
                break;
            default:
                continue;
            }
        }

        HSD_LObjSetActive(lobj);
        idx = HSD_LObjGetNbActive();

        lobj->spec_id = GX_LIGHT_NULL;

        switch (type) {
        case LOBJ_INFINITE:
            setup_infinite_lightobj(lobj, vmtx);
            break;
        case LOBJ_POINT:
            setup_point_lightobj(lobj, vmtx);
            break;
        case LOBJ_SPOT:
            setup_spot_lightobj(lobj, vmtx);
            break;
        case LOBJ_AMBIENT:
            continue;
        }

        switch (ref_type) {
        case LOBJ_DIFFUSE | LOBJ_SPECULAR:
        case LOBJ_DIFFUSE:
            setup_diffuse_lightobj(lobj);
            break;
        case LOBJ_SPECULAR:
            setup_spec_lightobj(lobj, vmtx, lobj->id);
            num++;
            break;
        }
    }

    if (!HSD_LObjGetActiveByID(256)) {
        for (; list; list = list->next) {
            HSD_LObj* lobj = list->data;
            HSD_ASSERT(0x372, lobj);

            if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT &&
                !(lobj->flags & LOBJ_HIDDEN))
            {
                HSD_LObjSetActive(lobj);
                break;
            }
        }
    }

    for (list = current_lights;
         list != NULL && num < MAX_GXLIGHT - 1 && idx < MAX_GXLIGHT - 1;
         list = list->next)
    {
        HSD_LObj* lobj = list->data;
        u32 flags = lobj->flags;

        if ((flags & 0x2C) != (LOBJ_SPECULAR | LOBJ_DIFFUSE)) {
            continue;
        }
        setup_spec_lightobj(lobj, vmtx, HSD_Index2LightID(idx++));
        num++;
    }

    for (i = 0; i < MAX_GXLIGHT - 1; i++) {
        HSD_LObj* lobj;

        if (!(lobj = HSD_LObjGetActiveByIndex(i))) {
            return;
        }
        HSD_LObjSetup(lobj, lobj->color, lobj->shininess);
    }
}

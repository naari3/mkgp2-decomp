#include "lobj_private.h"

#include "lobj_inline.h"
#undef __FILE__
#define __FILE__ "lobj.c"
#undef HSD_LObjGetPosition
#undef HSD_LObjGetInterest
extern int __float_epsilon[];
#define LOBJ_FLT_EPSILON (*(float*) __float_epsilon)
extern const Vec3 HSD_LObj_803B94A0_803F2BB8;
extern const Vec3 HSD_LObj_803B94AC_803F2BC4;

/* Shared assertion strings and constants from the original lobj TU. */
char lbl_804FC3E4[9] = "object.h";
char lbl_804FC3F0[39] = "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF";
char lbl_806D0D20[7] = "lobj.c";
char lbl_806D0D28[2] = "0";
char lbl_806D0D2C[7] = "lobj.h";
char lbl_806D0D34[5] = "lobj";
char lbl_806D0D3C[4] = "new";
char lbl_806D0D44[3] = "*p";
const double lbl_806DCBE0 = 0.5;
const float lbl_806DCBF0 = 255.0F;

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
    if (fabs(src->x) <= LOBJ_FLT_MIN && fabs(src->y) <= LOBJ_FLT_MIN &&
        fabs(src->z) <= LOBJ_FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

static inline int LObjNormalize(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    return LObjNormalizeNoCheck(src, dst);
}

static inline void LObjGetLightVector(HSD_LObj* lobj, Vec3* dir, int checked)
{
    Vec3 position = HSD_LObj_803B94A0_803F2BB8;
    Vec3 interest = HSD_LObj_803B94AC_803F2BC4;
    if (lobj == NULL) {
        return;
    }
    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    if ((checked ? LObjNormalize(dir, dir) : LObjNormalizeNoCheck(dir, dir)) != 0) {
        dir->x = 0.0F;
        dir->y = 0.0F;
        dir->z = 1.0F;
    }
}

static inline HSD_LObj* LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < MAX_GXLIGHT - 1) {
        return active_lights[idx];
    }
    return NULL;
}

static inline HSD_LObj* LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < MAX_GXLIGHT) {
        return active_lights[idx];
    }
    return NULL;
}

void HSD_LObjSetupSpecularInit(Mtx pmtx)
{
    HSD_LObj* lobj;
    s32 num;
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
        lobj = LObjGetActiveByIndex(i);

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
            __assert(lbl_806D0D20, 634, lbl_806D0D28);
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

static inline void setup_diffuse_lightobj(HSD_LObj* lobj)
{
    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    lobj->flags |= LOBJ_DIFF_DIRTY;

    switch (HSD_LObjGetType(lobj)) {
    case LOBJ_SPOT:
    case LOBJ_POINT:
        lightmask_attnfunc |= lobj->id;
        break;
    case LOBJ_INFINITE:
        break;
    default:
        __assert(lbl_806D0D20, 664, lbl_806D0D28);
    }

    if (lobj->flags & LOBJ_DIFFUSE) {
        lightmask_diffuse |= lobj->id;
    }
    if (lobj->flags & LOBJ_ALPHA) {
        lightmask_alpha |= lobj->id;
    }
}

static inline void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;

    lobj->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&lobj->spec_lightobj, lobj->color);
        lobj->shininess = 50.0F;

        x = lobj->shininess;

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
            LObjGetLightVector(lobj, &lobj->lvec, 1);
            PSMTXMultVecSR(mtx, &lobj->lvec, &lobj->lvec);
            VECNormalize(&lobj->lvec, &lobj->lvec);
            break;
        default:
            __assert(lbl_806D0D20, 704, lbl_806D0D28);
        }
        lobj->flags |= 0x100;
        lightmask_specular |= spec_id;
    }
}

static inline void setup_infinite_lightobj(HSD_LObj* lobj, MtxPtr vmtx)
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

static inline void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx)
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
        if (ref_dist < LOBJ_FLT_EPSILON) {
            ref_dist = LOBJ_FLT_EPSILON;
        }
        if (ref_br < LOBJ_FLT_EPSILON) {
            ref_br = LOBJ_FLT_EPSILON;
        }
        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, 0.0F, 0);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
    }
}

static inline void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    Vec3 ldir;

    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    LObjGetLightVector(lobj, &ldir, 0);
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
        if (ref_dist < LOBJ_FLT_EPSILON) {
            ref_dist = LOBJ_FLT_EPSILON;
        }
        if (ref_br < LOBJ_FLT_EPSILON) {
            ref_br = LOBJ_FLT_EPSILON;
        }

        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, cutoff, spot_func);
    }
}

static inline void LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA)) != 0) {
        if (lobj->hw_color.r != color.r || lobj->hw_color.g != color.g ||
            lobj->hw_color.b != color.b || lobj->hw_color.a != color.a)
        {
            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F,
                            1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

void HSD_LObjSetupInit(HSD_CObj* cobj)
{
    MtxPtr vmtx;
    int i, num, idx;
    HSD_SList* list;

    idx = 0;
    lightmask_diffuse = GX_LIGHT_NULL;
    lightmask_specular = GX_LIGHT_NULL;
    lightmask_attnfunc = GX_LIGHT_NULL;
    lightmask_alpha = GX_LIGHT_NULL;
    vmtx = cobj->view_mtx;
    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;

    for (list = current_lights; idx < MAX_GXLIGHT - 1 && list; list = list->next) {
        HSD_LObj* lobj = list->data;
        u32 flags;
        u32 type;
        int ref_type;

        if (lobj == NULL) {
            continue;
        }
        flags = lobj->flags;
        if (flags & LOBJ_HIDDEN) {
            continue;
        }
        type = HSD_LObjGetType(lobj);
        ref_type = flags & (LOBJ_DIFFUSE | LOBJ_SPECULAR | LOBJ_ALPHA);
        if (ref_type == 0) {
            continue;
        }
        HSD_LObjSetActive(lobj);
        idx = nb_active_lights;
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
        if (ref_type & (LOBJ_DIFFUSE | LOBJ_ALPHA)) {
            setup_diffuse_lightobj(lobj);
        } else if (ref_type & LOBJ_SPECULAR) {
            setup_spec_lightobj(lobj, vmtx, lobj->id);
        }
    }

    if (!LObjGetActiveByID(256)) {
        for (; list; list = list->next) {
            HSD_LObj* lobj = list->data;
            if (lobj != NULL && !(lobj->flags & LOBJ_HIDDEN) &&
                HSD_LObjGetType(lobj) == LOBJ_AMBIENT &&
                (lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA))) {
                HSD_LObjSetActive(lobj);
                break;
            }
        }
    }

    num = nb_active_lights;
    for (i = 0; idx < MAX_GXLIGHT - 1 && i < num; i++) {
        HSD_LObj* lobj = LObjGetActiveByIndex(i);
        if (lobj != NULL && (lobj->flags & LOBJ_SPECULAR) &&
            (lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA))) {
            setup_spec_lightobj(lobj, vmtx, HSD_Index2LightID(idx++));
        }
    }

    {
        int j;
        for (j = 0; j < num; j++) {
            HSD_LObj* lobj = LObjGetActiveByIndex(j);
            if (lobj != NULL) {
                LObjSetup(lobj, lobj->color, lobj->shininess);
            }
        }
    }
}

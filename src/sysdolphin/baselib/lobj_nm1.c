#include "lobj_private.h"
#undef __FILE__
#define __FILE__ "lobj.c"

/* ---- lobj.c ---- */

HSD_LObjInfo hsdLObj = { LObjInfoInit };

/// @private
static inline f32 LObjClamp(f32 x, f32 lo, f32 hi)
{
    if (x <= lo) {
        return lo;
    }
    if (x >= hi) {
        return hi;
    }
    return x;
}

void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv >= 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a0 = val->fv;
        } else {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a1 = val->fv;
        } else {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a2 = val->fv;
        } else {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    }
}

/* ---- lobj_vector_nm.c ---- */


static inline int LObjNormalize(Vec3* src, Vec3* dst)
{
    if (!src || !dst) {
        return -1;
    }
    if (fabsf(src->x) <= LOBJ_FLT_MIN && fabsf(src->y) <= LOBJ_FLT_MIN &&
        fabsf(src->z) <= LOBJ_FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = { 0.0F, 0.0F, 0.0F };
    Vec3 interest = { 0.0F, 0.0F, 0.0F };

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    if (LObjNormalize(dir, dir) != 0) {
        dir->x = 0.0F;
        dir->y = 0.0F;
        dir->z = 1.0F;
    }
}

/* ---- lobj_setup.c ---- */

static inline u32 LObjType(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || LObjType(lobj) == LOBJ_AMBIENT) {
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

/* ---- lobj_init_nm.c ---- */

#include "lobj_inline.h"
#undef HSD_LObjGetPosition
#undef HSD_LObjGetInterest
extern int __float_epsilon[];
#define LOBJ_FLT_EPSILON (*(float*) __float_epsilon)

/* Shared assertion strings and constants from the original lobj TU. */
char lbl_804FC3E4[9] = "object.h";
char lbl_804FC3F0[39] = "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF";
char lbl_806D0D20[7] = "lobj.c";
char lbl_806D0D28[2] = "0";
char lbl_806D0D2C[7] = "lobj.h";
char lbl_806D0D34[5] = "lobj";
char lbl_806D0D3C[4] = "new";
char LObjLoad_data_806D0D40[1] = "";
char lbl_806D0D44[3] = "*p";

HSD_LObjInfo* lobj_default_class = NULL;

HSD_SList* current_lights = NULL;
HSD_LObj* active_lights[MAX_GXLIGHT];
s32 nb_active_lights = 0;

s32 lightmask_diffuse = 0;
s32 lightmask_specular = 0;
s32 lightmask_attnfunc = 0;
s32 lightmask_alpha = 0;

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

static inline int LObjNormalizeInit(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    return LObjNormalizeNoCheck(src, dst);
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

static inline s32 LObjGetNbActive(void)
{
    return nb_active_lights;
}

#define HSD_LObjGetNbActive LObjGetNbActive

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

    num = HSD_LObjGetNbActive();
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

extern const f32 lbl_806DCBFC;

static inline void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;

    lobj->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&lobj->spec_lightobj, lobj->color);
        lobj->shininess = lbl_806DCBFC;

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
            HSD_LObjGetLightVector(lobj, &lobj->lvec);
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

#undef HSD_LObjGetFlags
#undef HSD_LObjSetFlags
#undef HSD_LObjClearFlags
#undef HSD_LObjGetType
#undef HSD_LObjSetActive
#undef HSD_LObjClearActive
#undef HSD_LObjGetPosition
#undef HSD_LObjGetInterest

/* ---- lobj_current.c ---- */

extern char lbl_804FC3E4[9];
extern char lbl_804FC3F0[39];
extern char lbl_806D0D2C[7];
extern char lbl_806D0D34[5];

static inline void PrivateRefINC(void* o)
{
    if (o != NULL) {
        HSD_OBJ(o)->ref_count++;
        ((HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF) ? ((void) 0) :
         __assert(lbl_804FC3E4, 93, lbl_804FC3F0));
    }
}

static inline u8 PrivatePriority(HSD_LObj* lobj)
{
    ((lobj) ? ((void) 0) : __assert(lbl_806D0D2C, 355, lbl_806D0D34));
    return lobj->priority;
}

static inline void LObjAddCurrentOne(HSD_LObj* lobj)
{
    HSD_SList* node;
    HSD_SList** p;

    if (lobj != NULL) {
        node = current_lights;
        while (node != NULL) {
            if (node->data == lobj) {
                HSD_LObjDeleteCurrent(lobj);
                break;
            }
            node = node->next;
        }
        PrivateRefINC(lobj);
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if (PrivatePriority((*p)->data) > PrivatePriority(lobj)) {
                break;
            }
        }
        *p = HSD_SListAllocAndPrepend(*p, lobj);
    }
}

void HSD_LObjAddCurrent(HSD_LObj* lobj)
{
    for (; lobj != NULL; lobj = lobj->next) {
        LObjAddCurrentOne(lobj);
    }
}

void HSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        hsdDelete(lobj);
    }
}

void HSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < MAX_GXLIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                HSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

static inline void LObjRemoveAll(void)
{
    int i;
    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
}

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        while (lobj != NULL) {
            HSD_LObjDeleteCurrent(lobj);
            lobj = lobj->next;
        }
        return;
    }
    LObjRemoveAll();
}

HSD_LObj* HSD_LObjGetCurrentByType(u16 flags)
{
    u32 type = flags & LOBJ_TYPE_MASK;
    HSD_SList* cur = current_lights;
    while (cur != NULL) {
        HSD_LObj* lobj = cur->data;
        if (type == (lobj->flags & LOBJ_TYPE_MASK)) {
            return lobj;
        }
        cur = cur->next;
    }
    return NULL;
}

/* ---- lobj_id.c ---- */

extern char lbl_806D0D20[7];
extern char lbl_806D0D28[2];
u32 HSD_LightID2Index(GXLightID id)
{
    u32 index;
    switch (id) {
    case GX_LIGHT0:
        index = 0;
        break;
    case GX_LIGHT1:
        index = 1;
        break;
    case GX_LIGHT2:
        index = 2;
        break;
    case GX_LIGHT3:
        index = 3;
        break;
    case GX_LIGHT4:
        index = 4;
        break;
    case GX_LIGHT5:
        index = 5;
        break;
    case GX_LIGHT6:
        index = 6;
        break;
    case GX_LIGHT7:
        index = 7;
        break;
    case GX_MAX_LIGHT:
        index = 8;
        break;
    default:
        __assert(lbl_806D0D20, 1192, lbl_806D0D28);
        break;
    }
    return index;
}

/* ---- lobj_index.c ---- */

s32 HSD_Index2LightID(u32 index)
{
    switch (index) {
    case 0:
        return GX_LIGHT0;
    case 1:
        return GX_LIGHT1;
    case 2:
        return GX_LIGHT2;
    case 3:
        return GX_LIGHT3;
    case 4:
        return GX_LIGHT4;
    case 5:
        return GX_LIGHT5;
    case 6:
        return GX_LIGHT6;
    case 7:
        return GX_LIGHT7;
    case 8:
        return GX_MAX_LIGHT;
    default:
        return GX_LIGHT_NULL;
    }
}

/* ---- lobj_position.c ---- */

static inline void PrivateHSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        hsdDelete(lobj);
    }
}

static inline void PrivateHSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < MAX_GXLIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                PrivateHSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

void HSD_LObjRemoveAll(HSD_LObj* lobj)
{
    HSD_LObj* next;
    HSD_LObj* cur;

    cur = lobj;
    while (cur != NULL) {
        next = cur->next;
        PrivateHSD_LObjDeleteCurrent(cur);
        PrivateHSD_LObjUnrefThis(cur);
        cur = next;
    }
}

bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}

/* ---- lobj_load.c ---- */

extern char lbl_806D0D20[7];
extern char lbl_806D0D3C[4];
extern char LObjLoad_data_806D0D40[1];
extern char lbl_806D0D44[3];
extern char lbl_804FC480[];

static inline void PrivateHSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

static inline void PrivateHSD_LObjSetColor(HSD_LObj* lobj, GXColor color)
{
    lobj->color = color;
}

static inline void PrivateHSD_LObjGetColor(HSD_LObj* lobj, GXColor* color)
{
    *color = lobj->color;
}

static inline void PrivateHSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func)
{
    if (lobj != NULL) {
        lobj->u.point.cutoff = cutoff;
        lobj->u.point.point_func = point_func;
    }
}

static inline void PrivateHSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func)
{
    if (lobj != NULL) {
        lobj->u.point.ref_dist = ref_dist;
        lobj->u.point.ref_br = ref_br;
        lobj->u.point.dist_func = dist_func;
    }
}

static inline void PrivateHSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.a0 = a0;
    lobj->u.attn.a1 = a1;
    lobj->u.attn.a2 = a2;
}

static inline void PrivateHSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.k0 = k0;
    lobj->u.attn.k1 = k1;
    lobj->u.attn.k2 = k2;
}

static inline void PrivateHSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2)
{
    PrivateHSD_LObjSetAttnA(lobj, a0, a1, a2);
    PrivateHSD_LObjSetAttnK(lobj, k0, k1, k2);
}

static inline HSD_LObjInfo* PrivateHSD_LObjGetDefaultClass(void)
{
    return lobj_default_class ? lobj_default_class : &hsdLObj;
}

static inline HSD_LObj* PrivateHSD_LObjAlloc(void)
{
    HSD_LObj* new = hsdNew(&PrivateHSD_LObjGetDefaultClass()->parent.parent);
    ((new) ? ((void) 0) : __assert(lbl_806D0D20, 1500, lbl_806D0D3C));
    return new;
}

static inline HSD_WObj* PrivateHSD_LObjGetPositionWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->position;
    }
    return NULL;
}

static inline HSD_WObj* PrivateHSD_LObjGetInterestWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->interest;
    }
    return NULL;
}

static inline void PrivateHSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->position);
    lobj->position = wobj;
}

static inline void PrivateHSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->interest);
    lobj->interest = wobj;
}

int LObjLoad(HSD_LObj* lobj, HSD_LightDesc* ldesc)
{
    PrivateHSD_LObjSetColor(lobj, ldesc->color);
    PrivateHSD_LObjSetFlags(lobj, ldesc->flags);
    switch (ldesc->flags & LOBJ_TYPE_MASK) {
    case LOBJ_AMBIENT:
        break;
    case LOBJ_INFINITE:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        break;
    case LOBJ_POINT:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            PrivateHSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            PrivateHSD_LObjSetAttnK(lobj, ldesc->u.attn->k0, ldesc->u.attn->k1,
                             ldesc->u.attn->k2);
        } else {
            PrivateHSD_LObjSetDistAttn(lobj, ldesc->u.point->ref_dist,
                                ldesc->u.point->ref_br,
                                ldesc->u.point->dist_func);
        }
        break;
    case LOBJ_SPOT:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        PrivateHSD_LObjSetInterestWObj(lobj, HSD_WObjLoadDesc(ldesc->interest));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            PrivateHSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            PrivateHSD_LObjSetAttn(lobj, ldesc->u.attn->a0, ldesc->u.attn->a1,
                            ldesc->u.attn->a2, ldesc->u.attn->k0,
                            ldesc->u.attn->k1, ldesc->u.attn->k2);
        } else {
            PrivateHSD_LObjSetDistAttn(lobj, ldesc->u.spot->ref_dist,
                                ldesc->u.spot->ref_br,
                                ldesc->u.spot->dist_func);
            PrivateHSD_LObjSetSpot(lobj, ldesc->u.spot->cutoff,
                            ldesc->u.spot->spot_func);
        }
        break;
    default:
        OSReport(lbl_804FC480, ldesc->flags);
        HSD_Panic(lbl_806D0D20, 1632, LObjLoad_data_806D0D40);
        break;
    }
    return 0;
}

HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc)
{
    HSD_LObj *top, **p = &top;

    for (; ldesc; ldesc = ldesc->next) {
        HSD_ClassInfo* info;

        if (!ldesc->class_name ||
            !(info = hsdSearchClassInfo(ldesc->class_name)))
        {
            *p = PrivateHSD_LObjAlloc();
        } else {
            *p = hsdNew(info);
            ((*p) ? ((void) 0) : __assert(lbl_806D0D20, 1666, lbl_806D0D44));
        }
        HSD_LOBJ_METHOD(*p)->load(*p, ldesc);
        p = &(*p)->next;
    }
    *p = NULL;

    return top;
}

void LObjRelease(HSD_Class* o)
{
    HSD_LObj* lobj = HSD_LOBJ(o);
    ///@todo Unused stack
    u8 _[8];

    HSD_AObjRemove(lobj->aobj);
    HSD_WObjUnref(PrivateHSD_LObjGetPositionWObj(lobj));
    HSD_WObjUnref(PrivateHSD_LObjGetInterestWObj(lobj));

    HSD_OBJECT_PARENT_INFO(&hsdLObj)->release(o);
}

void LObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(lobj_default_class)) {
        lobj_default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdLObj)) {
        current_lights = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdLObj)->amnesia(info);
}

/* ---- lobj_load_nm.c ---- */

extern int LObjLoad(HSD_LObj*, HSD_LightDesc*);
extern void LObjRelease(HSD_Class*);
extern void LObjAmnesia(HSD_ClassInfo*);
/* Shared strings used by the light position, load and class routines. */
char lbl_804FC43C[0x44] =
    "lobj->position\0\0"
    "lobj->interest\0\0"
    "hsdIsDescendantOf(info, &hsdLObj)";
char lbl_804FC480[33] = "unexpected lightdesc flags (%x)\n";

void LObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdLObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_lobj",
                     sizeof(HSD_LObjInfo), sizeof(HSD_LObj));
    HSD_CLASS_INFO(&hsdLObj)->release = LObjRelease;
    HSD_CLASS_INFO(&hsdLObj)->amnesia = LObjAmnesia;
    hsdLObj.load = LObjLoad;
    hsdLObj.update = LObjUpdateFunc;
}

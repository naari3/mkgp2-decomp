#include "fog.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "debug.h"
#include "object.h"
#include <dolphin/gx/GXPixel.h>
#include <dolphin/mtx.h>

static void FogInfoInit(void);
static void FogAdjInfoInit(void);

HSD_FogInfo hsdFog = { FogInfoInit };
HSD_ClassInfo hsdFogAdj = { FogAdjInfoInit };


u32 HSD_FogAdjGetFlags(HSD_FogAdj* adj);

static inline HSD_FogAdj* HSD_FogGetFogAdj(HSD_Fog* fog)
{
    return fog != NULL ? fog->fog_adj : NULL;
}

static inline s32 HSD_FogAdjGetCenter(HSD_FogAdj* adj)
{
    if (adj != NULL) {
        return adj->center;
    }
    return -1;
}

static inline s32 HSD_FogAdjGetWidth(HSD_FogAdj* adj)
{
    if (adj != NULL) {
        return adj->width;
    }
    return -1;
}

static inline Mtx44Ptr HSD_FogAdjGetMtx(HSD_FogAdj* adj)
{
    if (adj != NULL) {
        return adj->mtx;
    }
    return NULL;
}

struct HSD_FogSet_proj {
    f32 x0;
    f32 v[6];
};

void HSD_FogSet(HSD_Fog* fog)
{
    GXFogAdjTable tbl;
    f32 v[6];
    HSD_CObj* cobj;
    HSD_FogAdj* adj;
    u32 flags;
    s32 range;
    s32 width;
    Mtx44Ptr pmtx;
    struct HSD_FogSet_proj proj;

    if (fog == NULL) {
        GXColor color = { 0 };
        GXSetFog(0, 0.0F, 0.0F, 0.0F, 0.0F, color);
        return;
    }
    cobj = HSD_CObjGetCurrent();
    if (cobj == NULL) {
        HSD_Panic(__FILE__, 0x58, "You must specify CObj first.\n");
    }
    GXSetFog(fog->type, fog->start, fog->end, HSD_CObjGetNear(cobj),
             HSD_CObjGetFar(cobj), fog->color);

    adj = HSD_FogGetFogAdj(fog);
    flags = HSD_FogAdjGetFlags(adj);
    if (adj != NULL && (flags & 7)) {
        GXGetViewportv(v);
        if (flags & 1) {
            range = v[0] + v[2] * (HSD_FogAdjGetCenter(adj) + 320) / 640.0F;
        } else {
            range = v[0] + v[2] / 2.0F;
        }
        if (flags & 2) {
            width = HSD_FogAdjGetWidth(adj);
        } else {
            width = v[2];
        }
        if (flags & 4) {
            pmtx = HSD_FogAdjGetMtx(adj);
        } else {
            Mtx44 mtx;

            pmtx = mtx;
            memset(mtx, 0, sizeof(Mtx44));
            /// @todo Eliminate cast
            GXGetProjectionv((f32*) &proj);
            switch ((s32) proj.x0) {
            case 0:
                mtx[0][0] = proj.v[0];
                mtx[0][2] = proj.v[1];
                mtx[1][1] = proj.v[2];
                mtx[1][2] = proj.v[3];
                mtx[2][2] = proj.v[4];
                mtx[2][3] = proj.v[5];
                mtx[3][2] = -1.0F;
                break;
            default:
                mtx[0][0] = proj.v[0];
                mtx[0][3] = proj.v[1];
                mtx[1][1] = proj.v[2];
                mtx[1][3] = proj.v[3];
                mtx[2][2] = proj.v[4];
                mtx[2][3] = proj.v[5];
                mtx[3][3] = 1.0F;
                break;
            }
        }
        GXInitFogAdjTable(&tbl, width, pmtx);
        GXSetFogRangeAdj(1, range, &tbl);
        return;
    }
    GXSetFogRangeAdj(0, 0, NULL);
}

HSD_Fog* HSD_FogAlloc(void)
{
    HSD_Fog* fog = hsdNew(HSD_OBJECT_INFO(&hsdFog));
    HSD_ASSERT(0xA1, fog);
    return fog;
}

HSD_Fog* HSD_FogLoadDesc(HSD_FogDesc* desc)
{
    HSD_Fog* fog = HSD_FogAlloc();
    HSD_ASSERT(0xAE, fog);
    HSD_FogInit(fog, desc);
    if (desc->fogadjdesc != NULL) {
        fog->fog_adj = HSD_FogAdjLoadDesc(desc->fogadjdesc);
    }
    return fog;
}

void HSD_FogInit(HSD_Fog* fog, HSD_FogDesc* desc)
{
    if (fog != NULL) {
        if (desc != NULL) {
            fog->type = desc->type;
            fog->start = desc->start;
            fog->end = desc->end;
            fog->color = desc->color;
        } else {
            f32 v[6];
            GXGetViewportv(v);
            fog->type = GX_FOG_LIN;
            fog->start = v[4];
            fog->end = v[5];
            fog->color.r = 0xFF;
            fog->color.g = 0xFF;
            fog->color.b = 0xFF;
            fog->color.a = 0xFF;
        }
    }
}

HSD_FogAdj* HSD_FogAdjAlloc(void)
{
    HSD_FogAdj* adj = hsdNew(&hsdFogAdj);
    HSD_ASSERT(0xF9, adj);
    return adj;
}

HSD_FogAdj* HSD_FogAdjLoadDesc(HSD_FogAdjDesc* desc)
{
    HSD_FogAdj* adj = HSD_FogAdjAlloc();
    HSD_ASSERT(0x109, adj);
    HSD_FogAdjInit(adj, desc);
    return adj;
}

void HSD_FogAdjInit(HSD_FogAdj* adj, HSD_FogAdjDesc* desc)
{
    if (adj != NULL) {
        if (desc != NULL) {
            adj->flags = desc->flags;
            adj->width = desc->width;
            adj->center = desc->center;
            memcpy(adj->mtx, desc->mtx, sizeof(Mtx44));
        } else {
            adj->flags = 0;
            adj->width = 0;
            adj->center = 0;
            memset(adj->mtx, 0, sizeof(Mtx44));
        }
    }
}

u32 HSD_FogAdjGetFlags(HSD_FogAdj* adj)
{
    if (adj != NULL) {
        return adj->flags;
    }
    return 0;
}

static inline f32 FogClamp01(f32 x)
{
    if (x <= 0.0F) {
        return 0.0F;
    }
    if (x >= 1.0F) {
        return 1.0F;
    }
    return x;
}

static inline void HSD_FogAdjSetCenter(HSD_FogAdj* adj, s32 center)
{
    if (adj != NULL) {
        if (center <= -320) {
            adj->center = -320;
        } else if (center >= 320) {
            adj->center = 320;
        } else {
            adj->center = center;
        }
    }
}

static inline void HSD_FogAdjSetWidth(HSD_FogAdj* adj, s32 width)
{
    if (adj != NULL) {
        if (width <= 0) {
            adj->width = 0;
        } else if (width >= 640) {
            adj->width = 640;
        } else {
            adj->width = width;
        }
    }
}

void FogUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_Fog* fog = obj;
    if (fog != NULL) {
        switch (type) {
        case 1:
            fog->start = val->fv;
            return;
        case 2:
            fog->end = val->fv;
            return;
        case 5:
            fog->color.r = 255.0F * FogClamp01(val->fv);
            return;
        case 6:
            fog->color.g = 255.0F * FogClamp01(val->fv);
            return;
        case 7:
            fog->color.b = 255.0F * FogClamp01(val->fv);
            return;
        case 8:
            fog->color.a = 255.0F * FogClamp01(val->fv);
            return;
        case 20:
            HSD_FogAdjSetCenter(HSD_FogGetFogAdj(fog), val->fv);
            break;
        case 21:
            HSD_FogAdjSetWidth(HSD_FogGetFogAdj(fog), val->fv);
            break;
        }
    }
}

static void FogRelease(HSD_Fog* fog)
{
    if (fog->fog_adj != NULL) {
        HSD_FogAdj* adj = fog->fog_adj;
        if (ref_DEC(adj)) {
            hsdDelete(adj);
        }
    }
    HSD_AObjRemove(fog->aobj);
    HSD_OBJECT_PARENT_INFO(&hsdFog)->release((HSD_Class*) fog);
}

static void FogInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdFog), &hsdObj,
                     "sysdolphin_base_library", "hsd_fog", sizeof(HSD_FogInfo),
                     sizeof(HSD_Fog));
    HSD_CLASS_INFO(&hsdFog)->release = (void*) FogRelease;
    hsdFog.update = FogUpdateFunc;
}

static void FogAdjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdFogAdj), &hsdObj,
                     "sysdolphin_base_library", "hsd_fogadj",
                     sizeof(HSD_FogAdjInfo), sizeof(HSD_FogAdj));
}

#include "tobj.h"

#include <placeholder.h>
#include <string.h>

#include "aobj.h"
#include "cobj.h"
#include "debug.h"
#include "lobj.h"
#include "memory.h"
#include "mtx.h"
#include "tev.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#define FLT_EPSILON 1.00000001335e-10F

#include "tobj_private.h"
extern void* tobj_unk_ptr;
extern f32 tobj_unk_f0;
extern f32 tobj_unk_f1;
extern int tobj_unk_flag;
void fn_802D47F4(int);
void MakeTextureMtx(HSD_TObj* tobj)
{
    Vec3 scale;
    Mtx m;
    Vec3 trans;
    Quaternion rot;

    PAD_STACK(8);
    HSD_ASSERT(722, tobj->repeat_s && tobj->repeat_t);

    scale.x = fabsf(tobj->scale.x) < FLT_EPSILON
                  ? 0.0F
                  : (f32) tobj->repeat_s / tobj->scale.x;
    scale.y = fabsf(tobj->scale.y) < FLT_EPSILON
                  ? 0.0F
                  : (f32) tobj->repeat_t / tobj->scale.y;
    scale.z = tobj->scale.z;
    rot.x = tobj->rotate.x;
    rot.y = tobj->rotate.y;
    rot.z = -tobj->rotate.z;
    trans.x = -tobj->translate.x;
    trans.y =
        -(tobj->translate.y + (tobj->wrap_t == GX_MIRROR
                                   ? 1.0F / (tobj->repeat_t / tobj->scale.y)
                                   : 0.0F));
    trans.z = tobj->translate.z;

    MTXTrans(tobj->mtx, trans.x, trans.y, trans.z);
    HSD_MkRotationMtx(m, (Vec3*) &rot);
    MTXConcat(m, tobj->mtx, tobj->mtx);
    MTXScale(m, scale.x, scale.y, scale.z);
    MTXConcat(m, tobj->mtx, tobj->mtx);
}

static void TObjSetupMtx(HSD_TObj* tobj)
{
    int i;

    if (tobj_coord(tobj) == TEX_COORD_TOON) {
        return;
    }

    if (tobj->flags & TEX_MTX_DIRTY) {
        HSD_TOBJ_METHOD(tobj)->make_mtx(tobj);
        tobj->flags &= ~TEX_MTX_DIRTY;
    }

    switch (tobj_coord(tobj)) {
    case TEX_COORD_REFLECTION: {
        Mtx mtx;

        for (i = 0; i < 3; i++) {
            mtx[i][0] = 0.5F * tobj->mtx[i][0];
            mtx[i][1] = -0.5F * tobj->mtx[i][1];
            mtx[i][2] = 0.0F;
            mtx[i][3] = 0.5F * tobj->mtx[i][0] + 0.5F * tobj->mtx[i][1] +
                        tobj->mtx[i][2] + tobj->mtx[i][3];
        }
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    case TEX_COORD_HILIGHT: {
        HSD_LObj* lobj;

        if ((lobj = HSD_LObjGetCurrentByType(LOBJ_INFINITE)) != NULL) {
            HSD_CObj* cobj;
            Vec3 ldir, half;
            Mtx mtx;
            MtxPtr vmtx;

            cobj = HSD_CObjGetCurrent();
            HSD_ASSERT(0x2A8, cobj);
            vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);
            HSD_LObjGetLightVector(lobj, &ldir);
            MTXMultVecSR(vmtx, &ldir, &ldir);
            ldir.z += -1.0F;

            VECNormalize(&ldir, &half);

            half.x *= -0.5;
            half.y *= -0.5;
            half.z *= -0.5;

            mtx[0][0] = tobj->mtx[0][0] * half.x;
            mtx[0][1] = tobj->mtx[0][0] * half.y;
            mtx[0][2] = tobj->mtx[0][0] * half.z;
            mtx[0][3] = tobj->mtx[0][0] * 0.5F + tobj->mtx[0][3];
            mtx[1][0] = tobj->mtx[1][0] * half.x;
            mtx[1][1] = tobj->mtx[1][0] * half.y;
            mtx[1][2] = tobj->mtx[1][0] * half.z;
            mtx[1][3] = tobj->mtx[1][0] * 0.5F + tobj->mtx[1][3];
            mtx[2][0] = mtx[2][1] = mtx[2][2] = 0.0F;
            mtx[2][3] = 1.0F;

            GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
        } else {
            static Mtx zero = { 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
                                0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F };
            GXLoadTexMtxImm(zero, tobj->mtxid, GX_MTX3x4);
        }
    } break;

    case TEX_COORD_SHADOW: {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        Mtx mtx;

        MTXConcat(tobj->mtx, HSD_CObjGetInvViewingMtxPtrDirect(cobj), mtx);
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    default:
        if (tobj_bump(tobj)) {
            GXLoadTexMtxImm(tobj->mtx, tobj->mtxid, GX_MTX2x4);
        } else {
            GXLoadTexMtxImm(tobj->mtx, tobj->mtxid, GX_MTX3x4);
        }
        break;
    }
}

static void setupTextureCoordGen(HSD_TObj* tobj)
{
    u32 mtxid;
    GXTexGenSrc src;

    switch (tobj_coord(tobj)) {
    case TEX_COORD_SHADOW:
        GXSetTexCoordGen2(tobj->coord, GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0,
                          GX_DISABLE, tobj->mtxid);
        break;
    case TEX_COORD_REFLECTION:
    case TEX_COORD_HILIGHT:
        GXSetTexCoordGen2(tobj->coord, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                          GX_ENABLE, tobj->mtxid);
        break;
    default:
        if (tobj_bump(tobj)) {
            GXSetTexCoordGen(tobj->coord, GX_TG_MTX2x4, tobj->src,
                             tobj->mtxid);
        } else {
            GXSetTexCoordGen2(tobj->coord, GX_TG_MTX2x4, tobj->src,
                              GX_IDENTITY, GX_DISABLE, tobj->mtxid);
        }
    }
}

static void setupTextureCoordGenBump(HSD_TObj* bump)
{
    u32 mask;
    int i;
    static GXTexGenType func[] = {
        GX_TG_BUMP0, GX_TG_BUMP1, GX_TG_BUMP2, GX_TG_BUMP3,
        GX_TG_BUMP4, GX_TG_BUMP5, GX_TG_BUMP6, GX_TG_BUMP7,
    };

    mask = HSD_LObjGetLightMaskDiffuse();

    for (i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            break;
        }
    }
    if (i >= 8) {
        i = 0;
    }

    GXSetTexCoordGen((GXTexCoordID) (bump->coord + 1), func[i],
                     HSD_TexCoordID2TexGenSrc(bump->coord), GX_IDENTITY);
}

static void setupTextureCoordGenToon(HSD_TObj* toon)
{
    GXTexGenSrc src = toon->src;
    GXSetTexCoordGen(toon->coord, GX_TG_SRTG, src, GX_IDENTITY);
}

void HSD_TObjSetupTextureCoordGen(HSD_TObj* tobj)
{
    for (; tobj != NULL; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }
        if (tobj_bump(tobj)) {
            setupTextureCoordGen(tobj);
            setupTextureCoordGenBump(tobj);
        } else if (tobj_coord(tobj) == TEX_COORD_TOON) {
            setupTextureCoordGenToon(tobj);
        } else {
            setupTextureCoordGen(tobj);
        }
    }
}

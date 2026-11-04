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
void TObjMakeTExp(HSD_TObj* tobj, u32 lightmap, u32 lightmap_done,
                         HSD_TExp** c, HSD_TExp** a, HSD_TExp** list)
{
    HSD_TExp *e0, *e1;
    HSD_TExp *c_src, *a_src;
    HSD_TEInput c_sel, a_sel;
    int repeat = (lightmap_done & tobj_lightmap(tobj));

    c_src = HSD_TEXP_TEX;
    c_sel = HSD_TE_RGB;

    a_src = HSD_TEXP_TEX;
    a_sel = HSD_TE_A;

    e0 = HSD_TExpTev(list);

    if (tobj->tev && (tobj->tev->active & (TOBJ_TEVREG_ACTIVE_COLOR_TEV |
                                           TOBJ_TEVREG_ACTIVE_ALPHA_TEV)))
    {
        MakeColorGenTExp(lightmap, tobj, &c_src, &a_src, list, repeat);
    }

    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    switch (tobj_colormap(tobj)) {
    case TEX_COLORMAP_ALPHA_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, a_sel, a_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_RGB_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, c_sel, c_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_BLEND:
        e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, HSD_TE_X, e1,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_MODULATE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c, c_sel,
                        c_src, HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_REPLACE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, c_sel, c_src);
        break;
    case TEX_COLORMAP_NONE:
    case TEX_COLORMAP_PASS:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_ADD:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_SUB:
        HSD_TExpColorOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    default:
        HSD_ASSERT(1372, 0);
    }
    *c = e0;

    if (!repeat) {
        switch (tobj_alphamap(tobj)) {
        case TEX_ALPHAMAP_ALPHA_MASK:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, a_sel, a_src,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_BLEND:
            e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, HSD_TE_X, e1,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_MODULATE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a, a_sel,
                            a_src, HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_REPLACE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, a_sel,
                            a_src);
            break;
        case TEX_ALPHAMAP_NONE:
        case TEX_ALPHAMAP_PASS:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                            *a);
            break;
        case TEX_ALPHAMAP_ADD:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        case TEX_ALPHAMAP_SUB:
            HSD_TExpAlphaOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        default:
            HSD_ASSERT(1430, 0);
        }
        *a = e0;
    }
}

s32 HSD_TObjAssignResources(HSD_TObj* tobj_top)
{
    HSD_TObj* tobj;
    u32 texmap_no = 0;
    u32 texcoord_no = 0;
    u32 limit = 8;
    HSD_TObj* bump = NULL;
    HSD_TObj* toon = NULL;

    if (tobj_top == NULL) {
        return 0;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        } else if (tobj_bump(tobj)) {
            bump = tobj;
        }
    }

    if (toon) {
        limit -= 1;
    }
    if (bump) {
        limit -= 2;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            if (tobj != toon) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (tobj_bump(tobj)) {
            if (tobj != bump) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (texmap_no < limit) {
            tobj->id = HSD_Index2TexMap(texmap_no++);
            tobj->mtxid = HSD_TexMapID2PTTexMtx(tobj->id);
            switch (tobj_coord(tobj)) {
            case TEX_COORD_REFLECTION:
            case TEX_COORD_HILIGHT:
            case TEX_COORD_SHADOW:
                tobj->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        } else {
            tobj->id = GX_TEXMAP_NULL;
        }
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj->id != GX_TEXMAP_NULL && !tobj_bump(tobj)) {
            switch (tobj_coord(tobj)) {
            case TEX_COORD_UV:
                tobj->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        }
    }

    if (bump) {
        bump->id = HSD_Index2TexMap(texmap_no++);
        bump->mtxid = GX_TEXMTX9;
        bump->coord = HSD_Index2TexCoord(texcoord_no);
        texcoord_no += 2;
    }
    if (toon) {
        toon->id = HSD_Index2TexMap(texmap_no++);
        toon->coord = HSD_Index2TexCoord(texcoord_no++);
    }

    return (int) texcoord_no;
}

static int DifferentTluts(HSD_Tlut* t0, HSD_Tlut* t1)
{
    return
#ifdef MUST_MATCH
        (t0->lut != t0->lut) ||
#endif
        (t0->n_entries != t1->n_entries);
}

void HSD_TObjSetup(HSD_TObj* tobj)
{
    GXTlutObj tlutobj;
    GXTexObj texobj;
    int num;
    HSD_Tlut* tluts[8];
    int nb_tluts = 0;
    u32 tlut_name = GX_TLUT0;
    u32 big_tlut_name = GX_BIGTLUT0;
    int i;

    tobj_head = tobj;

    if (tobj == NULL) {
        return;
    }

    num = HSD_TObjAssignResources(tobj);
    if (num > 0) {
        HSD_StateRegisterTexGen(HSD_Index2TexCoord(num - 1));
    }

    for (; tobj; tobj = tobj->next) {
        static HSD_TexLODDesc default_lod = {
            GX_LIN_MIP_LIN, 0.0F, GX_FALSE, GX_FALSE, GX_ANISO_1,
        };
        HSD_TexLODDesc* lod;
        HSD_ImageDesc* imagedesc = tobj->imagedesc;
        GXTexFilter min_filter;

        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        TObjSetupMtx(tobj);
        HSD_ASSERT(1750, imagedesc);
        HSD_ASSERT(1751, imagedesc->image_ptr);

        lod = tobj->lod != NULL ? tobj->lod : &default_lod;
        min_filter = lod->minFilt;

        switch (imagedesc->format) {
        case GX_TF_C4:
        case GX_TF_C8:
        case GX_TF_C14X2: {
            HSD_Tlut* tlut;

            if (tobj->tlut_no != (u8) -1) {
                tlut = tobj->tluttbl[tobj->tlut_no];
            } else {
                tlut = tobj->tlut;
            }

            HSD_ASSERT(1767, tlut);

            for (i = 0; i < nb_tluts; i++) {
                if (!DifferentTluts(tluts[i], tlut)) {
                    break;
                }
            }
            if (i < nb_tluts) {
                tlut->tlut_name = tluts[i]->tlut_name;
            } else if (nb_tluts < 8) {
                if (tlut->n_entries > 256) {
                    tlut->tlut_name = big_tlut_name++;
                } else {
                    tlut->tlut_name = tlut_name++;
                }
                GXInitTlutObj(&tlutobj, tlut->lut, tlut->fmt, tlut->n_entries);
                GXLoadTlut(&tlutobj, tlut->tlut_name);
                tluts[nb_tluts++] = tlut;
            } else {
                tlut->tlut_name = GX_TLUT0;
            }

            GXInitTexObjCI(&texobj, imagedesc->image_ptr, imagedesc->width,
                           imagedesc->height, imagedesc->format, tobj->wrap_s,
                           tobj->wrap_t,
                           imagedesc->mipmap ? GX_TRUE : GX_FALSE,
                           tlut->tlut_name);
            if (min_filter == GX_LIN_MIP_LIN) {
                min_filter = GX_LIN_MIP_NEAR;
            }
        } break;

        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3:
        case GX_TF_RGBA8:
        case GX_TF_CMPR:
            GXInitTexObj(&texobj, imagedesc->image_ptr, imagedesc->width,
                         imagedesc->height, imagedesc->format, tobj->wrap_s,
                         tobj->wrap_t, imagedesc->mipmap ? GX_TRUE : GX_FALSE);
            break;

        default:
            HSD_ASSERT(1827, 0);
        }

        if (!imagedesc->mipmap) {
            min_filter &= 0x01;
        }
        GXInitTexObjLOD(&texobj, min_filter, tobj->magFilt, imagedesc->minLOD,
                        imagedesc->maxLOD, lod->LODBias, lod->bias_clamp,
                        lod->edgeLODEnable, lod->max_anisotropy);

        GXLoadTexObj(&texobj, tobj->id);
    }
}

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

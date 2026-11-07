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
extern char lbl_806D0C94[7];
extern char lbl_806D0CAC[2];
extern char lbl_806D0CB0[5];
void TObjSetupMtx_802BE3C4(HSD_TObj*);
static HSD_TexLODDesc default_lod = {
    GX_LIN_MIP_LIN, 0.0F, GX_FALSE, GX_FALSE, GX_ANISO_1,
};
static char setup_imagedesc[10] = "imagedesc";
static char setup_image_ptr[21] = "imagedesc->image_ptr";
static inline void CompareTlutEntries(HSD_Tlut* t0, HSD_Tlut* t1, int* different)
{
    *different = 1;
    if (t0->n_entries == t1->n_entries) {
        *different = 0;
    }
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
    int different;
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
        HSD_TexLODDesc* lod;
        HSD_ImageDesc* imagedesc = tobj->imagedesc;
        GXTexFilter min_filter;

        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        TObjSetupMtx_802BE3C4(tobj);
        if (!imagedesc) {
            __assert(lbl_806D0C94, 1750, setup_imagedesc);
        }
        if (!imagedesc->image_ptr) {
            __assert(lbl_806D0C94, 1751, setup_image_ptr);
        }

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

            if (!tlut) {
                __assert(lbl_806D0C94, 1767, lbl_806D0CB0);
            }

            for (i = 0; i < nb_tluts; i++) {
                CompareTlutEntries(tluts[i], tlut, &different);
                if (!different) {
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
            __assert(lbl_806D0C94, 1827, lbl_806D0CAC);
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

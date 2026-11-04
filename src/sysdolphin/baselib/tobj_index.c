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
extern char lbl_806D0CB8[4];
extern char lbl_806D0CBC[4];
extern char lbl_806D0CC0[4];
extern char lbl_806D0CC4[6];
#undef __FILE__
#define __FILE__ lbl_806D0C94
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, (line) == 2212 ? lbl_806D0CBC : (line) == 2241 ? lbl_806D0CB0 : (line) == 2284 ? lbl_806D0CC0 : (line) == 2327 ? lbl_806D0CC4 : lbl_806D0CAC))
#define HSD_Panic(file, line, msg) HSD_Panic(file, line, (line) == 2049 ? lbl_806D0CB8 : (msg))
u32 HSD_TGTex2Index(GXTexGenSrc tgtex)
{
    switch (tgtex) {
    case GX_TG_TEX0:
        return 0;
    case GX_TG_TEX1:
        return 1;
    case GX_TG_TEX2:
        return 2;
    case GX_TG_TEX3:
        return 3;
    case GX_TG_TEX4:
        return 4;
    case GX_TG_TEX5:
        return 5;
    case GX_TG_TEX6:
        return 6;
    case GX_TG_TEX7:
        return 7;
    default:
        HSD_ASSERT(1873, 0);
    }
    return GX_TG_TEX0;
}

GXTexGenSrc HSD_TexCoordID2TexGenSrc(GXTexCoordID coord)
{
    switch (coord) {
    case GX_TEXCOORD0:
        return GX_TG_TEXCOORD0;
    case GX_TEXCOORD1:
        return GX_TG_TEXCOORD1;
    case GX_TEXCOORD2:
        return GX_TG_TEXCOORD2;
    case GX_TEXCOORD3:
        return GX_TG_TEXCOORD3;
    case GX_TEXCOORD4:
        return GX_TG_TEXCOORD4;
    case GX_TEXCOORD5:
        return GX_TG_TEXCOORD5;
    case GX_TEXCOORD6:
        return GX_TG_TEXCOORD6;
    case GX_TEXCOORD7:
    default:
        HSD_ASSERT(1910, 0);
    }
    return GX_TG_TEXCOORD0;
}

u32 HSD_TexCoord2Index(GXTexCoordID coord_id)
{
    switch (coord_id) {
    case GX_TEXCOORD0:
        return 0;
    case GX_TEXCOORD1:
        return 1;
    case GX_TEXCOORD2:
        return 2;
    case GX_TEXCOORD3:
        return 3;
    case GX_TEXCOORD4:
        return 4;
    case GX_TEXCOORD5:
        return 5;
    case GX_TEXCOORD6:
        return 6;
    case GX_TEXCOORD7:
        return 7;
    default:
        HSD_ASSERT(1948, 0);
    }
    return GX_TEXCOORD0;
}

GXTexCoordID HSD_Index2TexCoord(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXCOORD0;
    case 1:
        return GX_TEXCOORD1;
    case 2:
        return GX_TEXCOORD2;
    case 3:
        return GX_TEXCOORD3;
    case 4:
        return GX_TEXCOORD4;
    case 5:
        return GX_TEXCOORD5;
    case 6:
        return GX_TEXCOORD6;
    case 7:
        return GX_TEXCOORD7;
    default:
        HSD_ASSERT(1972, 0);
    }
    return GX_TEXCOORD0;
}

u32 HSD_TexMtx2Index(GXTexMtx texmtx)
{
    switch (texmtx) {
    case GX_TEXMTX0:
        return 0;
    case GX_TEXMTX1:
        return 1;
    case GX_TEXMTX2:
        return 2;
    case GX_TEXMTX3:
        return 3;
    case GX_TEXMTX4:
        return 4;
    case GX_TEXMTX5:
        return 5;
    case GX_TEXMTX6:
        return 6;
    case GX_TEXMTX7:
        return 7;
    case GX_TEXMTX8:
        return 8;
    case GX_TEXMTX9:
        return 9;
    case GX_IDENTITY:
        return 10;
    default:
        HSD_Panic(__FILE__, 2017, "specified texmtx id desn't exist.\n");
    }
    return (u32) -1;
}

GXTexMtx HSD_Index2TexMtx(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMTX0;
    case 1:
        return GX_TEXMTX1;
    case 2:
        return GX_TEXMTX2;
    case 3:
        return GX_TEXMTX3;
    case 4:
        return GX_TEXMTX4;
    case 5:
        return GX_TEXMTX5;
    case 6:
        return GX_TEXMTX6;
    case 7:
        return GX_TEXMTX7;
    case 8:
        return GX_TEXMTX8;
    case 9:
        return GX_TEXMTX9;
    case 10:
        return GX_IDENTITY;
    default:
        OSReport("texmtx index exceed hardware limit (%d).\n", index);
        HSD_Panic(__FILE__, 2049, "");
    }
    return GX_IDENTITY;
}

GXTexMapID HSD_Index2TexMap(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMAP0;
    case 1:
        return GX_TEXMAP1;
    case 2:
        return GX_TEXMAP2;
    case 3:
        return GX_TEXMAP3;
    case 4:
        return GX_TEXMAP4;
    case 5:
        return GX_TEXMAP5;
    case 6:
        return GX_TEXMAP6;
    case 7:
        return GX_TEXMAP7;
    default:
        HSD_ASSERT(2087, 0);
    }
    return GX_TEXMAP0;
}

u32 HSD_TexMap2Index(GXTexMapID mapid)
{
    switch (mapid) {
    case GX_TEXMAP0:
        return 0;
    case GX_TEXMAP1:
        return 1;
    case GX_TEXMAP2:
        return 2;
    case GX_TEXMAP3:
        return 3;
    case GX_TEXMAP4:
        return 4;
    case GX_TEXMAP5:
        return 5;
    case GX_TEXMAP6:
        return 6;
    case GX_TEXMAP7:
        return 7;
    default:
        HSD_ASSERT(2111, 0);
    }
    return 0;
}

static inline void HSD_TObjRemove(HSD_TObj* tobj)
{
    hsdDelete(tobj);
}

void HSD_TObjRemoveAll(HSD_TObj* tobj)
{
    while (tobj) {
        HSD_TObj* next = tobj->next;
        HSD_TObjRemove(tobj);
        tobj = next;
    }
}

HSD_TObj* HSD_TObjGetNext(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return NULL;
    }

    return tobj->next;
}

#ifndef MUST_MATCH
void HSD_TObjSetDefaultClass(HSD_TObjInfo* info)
{
    if (info) {
        HSD_ASSERT(2027, hsdIsDescendantOf(info, &hsdTObj));
    }
    default_class = info;
}
#endif

static inline HSD_TObjInfo* HSD_TObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdTObj;
}

HSD_TObj* HSD_TObjAlloc(void)
{
    HSD_TObj* new = hsdNew(&HSD_TObjGetDefaultClass()->parent);
    HSD_ASSERT(2212, new);
    return new;
}

void HSD_TObjFree(HSD_TObj* tobj)
{
    if (tobj) {
        HSD_CLASS_METHOD(tobj)->destroy((HSD_Class*) tobj);
    }
}

HSD_Tlut* HSD_TlutAlloc(void)
{
    HSD_Tlut* tlut = hsdAllocMemPiece(sizeof(HSD_Tlut));
    HSD_ASSERT(2241, tlut);
    memset(tlut, 0, sizeof(HSD_Tlut));
    return tlut;
}

#ifndef MUST_MATCH
void HSD_TlutFree(HSD_Tlut* tlut)
{
    hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
}
#endif

void HSD_TlutRemove(HSD_Tlut* tlut)
{
    if (tlut) {
        hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
    }
}

HSD_TObjTev* HSD_TObjTevAlloc(void)
{
    HSD_TObjTev* tev = hsdAllocMemPiece(sizeof(HSD_TObjTev));
    HSD_ASSERT(2284, tev);
    memset(tev, 0, sizeof(HSD_TObjTev));
    return tev;
}

#ifndef MUST_MATCH
void HSD_TObjTevFree(HSD_TObjTev* tev)
{
    hsdFreeMemPiece(tev, sizeof(HSD_TObjTev));
}
#endif

#ifndef MUST_MATCH
void HSD_TObjTevRemove(HSD_TObjTev* tev)
{
    if (tev) {
        HSD_TObjTevFree(tev);
    }
}
#endif

HSD_ImageDesc* HSD_ImageDescAlloc(void)
{
    HSD_ImageDesc* idesc = hsdAllocMemPiece(sizeof(HSD_ImageDesc));
    HSD_ASSERT(2327, idesc);
    memset(idesc, 0, sizeof(HSD_ImageDesc));
    return idesc;
}

void HSD_ImageDescFree(HSD_ImageDesc* idesc)
{
    hsdFreeMemPiece(idesc, sizeof(HSD_ImageDesc));
}

#ifndef MUST_MATCH
void HSD_ImageDescCopyFromEFB(HSD_ImageDesc* idesc, u16 origx, u16 origy,
                              GXBool clear, bool sync)
{
    if (!idesc) {
        return;
    }

    GXSetTexCopySrc(origx, origy, idesc->width, idesc->height);
    GXSetTexCopyDst(idesc->width, idesc->height, idesc->format,
                    idesc->mipmap ? GX_TRUE : GX_FALSE);
    if (clear) {
        HSD_StateSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    GXCopyTex(idesc->image_ptr, clear);
    if (sync) {
        GXPixModeSync();
        GXInvalidateTexAll();
    }
}
#endif

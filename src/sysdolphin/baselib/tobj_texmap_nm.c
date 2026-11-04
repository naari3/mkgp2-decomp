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
char lbl_804FBA20[] = "unexpected texmap id.\n";
#define HSD_Panic(file, line, msg) HSD_Panic(file, line, lbl_804FBA20)
extern char lbl_806D0C94[7];
extern char lbl_806D0C9C[5];
#undef __FILE__
#define __FILE__ lbl_806D0C94
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, lbl_806D0C9C))
static u32 HSD_TexMapID2PTTexMtx(GXTexMapID id)
{
    switch (id) {
    case GX_TEXMAP0:
        return GX_PTTEXMTX0;
    case GX_TEXMAP1:
        return GX_PTTEXMTX1;
    case GX_TEXMAP2:
        return GX_PTTEXMTX2;
    case GX_TEXMAP3:
        return GX_PTTEXMTX3;
    case GX_TEXMAP4:
        return GX_PTTEXMTX4;
    case GX_TEXMAP5:
        return GX_PTTEXMTX5;
    case GX_TEXMAP6:
        return GX_PTTEXMTX6;
    case GX_TEXMAP7:
        return GX_PTTEXMTX7;
    default:
        HSD_Panic(__FILE__, 707, "unexpected texmap id.\n");
    }
    return 0;
}

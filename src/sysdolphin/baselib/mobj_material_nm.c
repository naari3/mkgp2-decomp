#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

#include "mobj_private.h"
extern char lbl_806D0CE8[7];
extern char lbl_806D0CF0[5];
extern char lbl_806D0D00[4];
extern char lbl_806D0D04[5];
extern char lbl_804FC270[14];
#undef __FILE__
#define __FILE__ lbl_806D0CE8
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, (line) == 839 ? lbl_804FC270 : (line) == 1148 ? lbl_806D0CF0 : (line) == 1176 ? lbl_806D0D00 : lbl_806D0D04))
HSD_Material* HSD_MaterialAlloc(void)
{
    HSD_Material* mat = hsdAllocMemPiece(sizeof(HSD_Material));
    HSD_ASSERT(1176, mat);
    memset(mat, 0, sizeof(HSD_Material));
    mat->alpha = 1.0F;
    return mat;
}

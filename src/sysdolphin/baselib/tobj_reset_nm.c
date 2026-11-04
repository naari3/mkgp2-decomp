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

extern f32 tobj_unk_f0;
extern f32 tobj_unk_f1;
extern int tobj_unk_flag;
void fn_802BD6C0(void)
{
    tobj_unk_flag = 0;
    tobj_unk_f0 = tobj_unk_f1 = 0.0F;
}


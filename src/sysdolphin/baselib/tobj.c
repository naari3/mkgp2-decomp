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

int tobj_unk_flag;
f32 tobj_unk_f1;
f32 tobj_unk_f0;
void* tobj_unk_ptr;
void fn_802BD6A4(void* p)
{
    tobj_unk_ptr = p;
}

void fn_802BD6AC(f32 a, f32 b)
{
    tobj_unk_f0 = a;
    tobj_unk_f1 = b;
    tobj_unk_flag = 1;
}

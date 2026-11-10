#ifndef MKGP2_COBJ_PRIVATE_H
#define MKGP2_COBJ_PRIVATE_H
#include "cobj.h"

#include <math.h>
extern double atan2(double, double);
extern double tan(double);
#include <placeholder.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "initialize.h"
#include "mtx.h"
#include "util.h"

extern float __float_min[];
#undef FLT_MIN
#define FLT_MIN (__float_min[0])

static inline int cobj_normalize_check(Vec3* src, Vec3* dst)
{
    if (!src || !dst) return -1;
    if (fabs(src->x) <= FLT_MIN && fabs(src->y) <= FLT_MIN &&
        fabs(src->z) <= FLT_MIN) return -1;
    PSVECNormalize(src, dst);
    return 0;
}
#define vec_normalize_check cobj_normalize_check
#include "video.h"
#include "wobj.h"
#include <dolphin/gx.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/mtx.h>
#include <dolphin/vi.h> // IWYU pragma: keep


#define default_class cobj_default_class
#define current cobj_current
extern HSD_CObjInfo hsdCObj;
extern HSD_ClassInfo* default_class;
extern HSD_CObj* current;
extern int HSD_CObjSetCurrent_data_806D0D48;
extern int HSD_CObjSetCurrent_data_806D0D4C;
#define ref_width HSD_CObjSetCurrent_data_806D0D48
#define ref_height HSD_CObjSetCurrent_data_806D0D4C
extern char lbl_806D0D50[7];
extern char lbl_806D0D58[5];
extern char lbl_806D0D60[2];
extern char lbl_804FC560[29];
extern char lbl_804FC580[13];
extern char lbl_804FC590[15];
extern char HSD_CObjSetRoll_data_804FC5B8[56];
extern Vec3 upvec2roll_data_804FC5A0;
extern Vec3 upvec2roll_data_804FC5AC;
extern Vec3 CObjLoad_data_804FC5F0;
#define orig upvec2roll_data_804FC5A0
#define uy upvec2roll_data_804FC5AC
#define DegToRad(a) ((a) * 0.01745329252F)
#define COBJ_ASSERT(line, cond, text) ((cond) ? (void) 0 : __assert(lbl_806D0D50, line, text))
void CObjUpdateFunc(void*, int, HSD_ObjData*);
int CObjInit(HSD_Class*);
int CObjLoad(HSD_CObj*, HSD_CObjDesc*);
void CObjInfoInit(void);
void CObjRelease(HSD_Class*);
void CObjAmnesia(HSD_ClassInfo*);
bool setupTopHalfCamera(HSD_CObj*);
bool setupBottomHalfCamera(HSD_CObj*);
float upvec2roll(HSD_CObj*, Vec3*);
int roll2upvec(HSD_CObj*, Vec3*, float);

#endif

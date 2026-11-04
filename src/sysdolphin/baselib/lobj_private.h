#ifndef MKGP2_LOBJ_PRIVATE_H
#define MKGP2_LOBJ_PRIVATE_H
#include "lobj.h"
#include <math.h>

extern int __float_min[];
#define LOBJ_FLT_MIN (*(float*) __float_min)

#include <placeholder.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h" // IWYU pragma: keep
#include "forward.h"
#include "list.h"
#include "object.h"
#include "wobj.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>

extern HSD_LObjInfo hsdLObj;
extern HSD_SList* current_lights;
extern HSD_LObj* active_lights[MAX_GXLIGHT];
extern s32 nb_active_lights;
extern s32 lightmask_diffuse;
extern s32 lightmask_specular;
extern s32 lightmask_attnfunc;
extern s32 lightmask_alpha;
extern HSD_LObjInfo* lobj_default_class;
extern void LObjInfoInit(void);
#endif

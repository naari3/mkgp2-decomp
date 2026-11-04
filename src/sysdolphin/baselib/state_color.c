#include "state.h"

#include "lobj.h"
#include "mobj.h"
#include "pobj.h"
#include "tev.h"
#include "texp.h"
#include "util.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

#include "state_private.h"
static inline f32 clampf(f32 x, f32 lo, f32 hi)
{
    if (x <= lo) {
        return lo;
    }
    if (x >= hi) {
        return hi;
    }
    return x;
}

void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          f32 alpha)
{
    matstate.ambient = ambient;
    matstate.diffuse = diffuse;
    matstate.specular = specular;
    matstate.alpha = 255.0F * clampf(alpha, 0.0F, 1.0F);
}

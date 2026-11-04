#include "lobj_private.h"

static inline u32 LObjType(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || LObjType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA)) != 0) {
        if (lobj->hw_color.r != color.r || lobj->hw_color.g != color.g ||
            lobj->hw_color.b != color.b || lobj->hw_color.a != color.a)
        {
            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F,
                            1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

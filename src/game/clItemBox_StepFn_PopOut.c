#include "game/clItemBox_PopOutPrivate.h"

extern double sin(double);

#pragma exceptions on
int clItemBox_StepFn_PopOut(ItemBoxPopOut *box)
{
    box->timer += 1.0f / 60.0f;
    /* The animation converts degrees to float radians before calling sin. */
    box->height = 3.0f * (float)sin((float)(0.017453292519943295 *
                                          (90.0f * box->timer))) + box->baseHeight;
    box->scale = box->timer;
    box->rotation += 0.0125f;
    if (box->timer >= 1.0f) {
        box->scale = 1.0f;
        return 1;
    }
    return 0;
}
#pragma exceptions reset

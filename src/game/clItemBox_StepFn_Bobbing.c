#include "game/clItemBox_StepFn_BobbingPrivate.h"

extern double sin(double);

#pragma exceptions on
int clItemBox_StepFn_Bobbing(ItemBoxBobbing *box)
{
    float wave;

    box->phase += 0.01f;
    wave = (float)sin((float)(0.017453292519943295 * (360.0f * box->phase)));
    box->height = 3.0f + box->baseHeight;
    box->height += 0.6f * (3.0f * wave);
    if (box->phase >= 1.0f) {
        box->phase -= 1.0f;
    }
    box->rotation += 1.0f / 60.0f;
    return 1;
}
#pragma exceptions reset

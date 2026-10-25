/* DrawEffect_Cb_KartTwoPlaneRing_Tick (0x800CA5EC): owns two child planes
 * (spawned on the first tick) and keeps each one pushed a fixed distance
 * from the parent along the camera->parent direction. */
#include "game/DrawEffectAccess.h"

extern unsigned char lbl_805DF3D0[];
extern void fn_800AF4F8(unsigned char *self);

typedef struct RingWork {
    unsigned char pad[0x10];
    unsigned char *kids[2];
} RingWork;

void DrawEffect_Cb_KartTwoPlaneRing_Tick(unsigned char *self)
{
    RingWork *work = (RingWork *)(self + 0xCC);
    float dist[2] = { 6.0f, -6.0f };
    float alpha[2] = { 0.5f, 0.1f };
    float scale[2] = { 6.0f, 5.0f };
    int i;

    switch (STATE) {
    case 0:
        for (i = 0; i < 2; i++) {
            work->kids[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (work->kids[i] != 0) {
                VfxSlot_BindResourceEx(SLOT(work->kids[i]), 0x8B, 0);
                *(float *)(work->kids[i] + 0x2C) = alpha[i];
                *(float *)(work->kids[i] + 0xB0) = scale[i];
                VfxSlot_SetScaleUniform(SLOT(work->kids[i]),
                                        *(float *)(work->kids[i] + 0xB0));
            }
        }
        STATE++;
    case 1:
        break;
    }

    for (i = 0; i < 2; i++) {
        if (work->kids[i] != 0) {
            Vec d;
            Vec p;
            Vec3_Subtract_DestFirst(&d, V(0x8C), (Vec *)(lbl_805DF3D0 + 0x80));
            Vec3_Scale(&d, &d, dist[i] * (1.0f / Vec3_Magnitude_Wrapper(&d)));
            Vec3_Add_DestFirst(V_(work->kids[i], 0x8C), V(0x8C), &d);
            p = *V_(work->kids[i], 0x8C);
            VfxSlot_SetPositionFromVec(SLOT(work->kids[i]), &p);
        }
    }
}

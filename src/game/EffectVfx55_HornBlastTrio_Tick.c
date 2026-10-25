/* EffectVfx55_HornBlastTrio_Tick (0x800C1860): horn blast made of three
 * child effects (resources 0x5C-0x5E) pinned to a kart hand joint; each
 * child's scale/alpha follow a 3-key curve over the timer.
 * NonMatching (98%): callee-saved register permutation only (self/ext and
 * the two hoisted function addresses of the spawn loop). */
#include "game/DrawEffectAccess.h"

typedef struct HornBlastCurve {
    float keys[3];
    float scale[3];
    float alpha[3];
} HornBlastCurve;

typedef struct HornBlastExt {
    unsigned char pad0[0x10];
    unsigned char *children[3];
    unsigned char pad1C[0x50 - 0x1C];
    unsigned char *driver;
    unsigned char pad54[0x84 - 0x54];
    float timer;
} HornBlastExt;

extern HornBlastCurve lbl_8041A1B8[3];
extern void fn_800AF4F8(unsigned char *self);
extern void EffectVfx_KartChildAttached_RenderHook(unsigned char *self);

void EffectVfx55_HornBlastTrio_Tick(unsigned char *self)
{
    HornBlastExt *ext;
    HornBlastCurve *curve;
    unsigned char **child;
    int i;
    int j;

    ext = (HornBlastExt *)(self + 0xCC);
    switch (STATE) {
    case 0:
        for (i = 0; i < 3; i++) {
            ext->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            *(void **)(self + 0x78) = EffectVfx_KartChildAttached_RenderHook;
            if (ext->children[i] != 0) {
                switch (i) {
                case 0:
                    VfxSlot_BindResourceEx(SLOT(ext->children[i]), 0x5C, 0);
                    break;
                case 1:
                    VfxSlot_BindResourceEx(SLOT(ext->children[i]), 0x5D, 0);
                    break;
                case 2:
                    VfxSlot_BindResourceEx(SLOT(ext->children[i]), 0x5E, 0);
                    break;
                }
                GetSpawnPosition(V_(ext->children[i], 0x30), 1.0f, 0.5f, 0.0f);
            }
        }
        ext->timer = 0.0f;
        STATE++;
    case 1:
        break;
    }

    ext->timer += 0.5f;
    if (7.0f < ext->timer) {
        DrawEffect_Free(ext->children[0]);
        DrawEffect_Free(ext->children[1]);
        DrawEffect_Free(ext->children[2]);
        ext->children[0] = 0;
        ext->children[1] = 0;
        ext->children[2] = 0;
        DrawEffect_Free(self);
        return;
    }

    if (I(0x10) == 0) {
        Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetJointByIdx(ext->driver, 0xA));
    } else {
        Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetJointByIdx(ext->driver, 0xB));
    }
    if (FinalLapCoinJump_CheckActiveForObject(ext->driver)) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }

    for (i = 0; i < 3; i++) {
        curve = &lbl_8041A1B8[i];
        if (ext->children[i] != 0) {
            Vec pos;

            Vec3_Copy(V_(ext->children[i], 0x8C), V(0x8C));
            if (curve->keys[0] <= ext->timer && ext->timer < curve->keys[2]) {
                for (j = 0; j < 2; j++) {
                    if (curve->keys[j] <= ext->timer && ext->timer < curve->keys[j + 1]) {
                        float f = (ext->timer - curve->keys[j]) * (1.0f / (curve->keys[j + 1] - curve->keys[j]));
                        *(float *)(ext->children[i] + 0xB0) =
                            f * (curve->scale[j + 1] - curve->scale[j]) + curve->scale[j];
                        *(float *)(ext->children[i] + 0x2C) =
                            f * (curve->alpha[j + 1] - curve->alpha[j]) + curve->alpha[j];
                    }
                }
            } else {
                *(float *)(ext->children[i] + 0xB0) = 0.0f;
                *(float *)(ext->children[i] + 0x2C) = 0.0f;
            }
            ext->children[i][0x28] = U8(0x28);
            pos = *V_(ext->children[i], 0x8C);
            VfxSlot_SetPositionFromVec(SLOT(ext->children[i]), &pos);
            VfxSlot_SetScaleUniform(SLOT(ext->children[i]), *(float *)(ext->children[i] + 0xB0));
        }
    }
}

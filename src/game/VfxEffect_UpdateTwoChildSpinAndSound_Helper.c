/* Update two orbiting children and maintain their positional sound. */
#include "game/DrawEffectAccess.h"

extern double sin(double);
extern int SoundMgr_CountActiveSEInstances(int sound);
#ifndef __MWERKS__ /* this unit passes the position as the address of its own copy (SoundMgr_PlaySE_Positional.c) */
#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress
#endif
extern void SoundMgr_PlaySE_Positional(int sound, const Vec *position, int channel);
extern void SoundMgr_PlaySE_WithChannel(int sound, const Vec *position, int channel);

#define CHILD (*(unsigned char **)(cursor + 0x10))
#define CF(o) (*(float *)(CHILD + (o)))
#define ANGLE (*(float *)(state + 0x84))
#define CHANNEL (*(signed char *)(state + 0xC4))

#pragma use_lmw_stmw on
void VfxEffect_UpdateTwoChildSpinAndSound_Helper(unsigned char *self,
                                                const Vec *position,
                                                float scale, float alpha)
{
    if (self != 0) {
        unsigned char *cursor;
        unsigned char *state = self + 0xCC;
        int i;
        float childScale;
        Vec3_Copy(V(0x8C), position);
        ANGLE = BuildOrientationFromYaw(0.26179933547973633f + ANGLE);
        childScale = 0.2f * scale;
        for (i = 0, cursor = state; i < 2; i++, cursor += 4) {
            if (CHILD != 0) {
                Vec3_Copy(V_(CHILD, 0x8C), position);
                CF(0x8C) += Rand_RangeFloat(-0.5f, 0.5f);
                CF(0x90) += Rand_RangeFloat(-0.5f, 0.5f);
                CF(0x94) += Rand_RangeFloat(-0.5f, 0.5f);
                if (i != 0) {
                    CF(0xA0) = ANGLE;
                } else {
                    CF(0xA0) = -ANGLE;
                }
                CF(0xB0) = childScale;
                if (i != 0) {
                    float pulse = (float)sin(ANGLE);
                    CF(0xB0) *= 0.2f * pulse + 1.0f;
                } else {
                    float pulse = (float)sin(BuildOrientationFromYaw(1.570796012878418f + ANGLE));
                    CF(0xB0) *= 0.2f * pulse + 1.0f;
                }
                CF(0x2C) = alpha;
                {
                    Vec pos = *V_(CHILD, 0x8C);
                    VfxSlot_SetPositionFromVec(SLOT(CHILD), &pos);
                }
                VfxSlot_SetRotationZ(SLOT(CHILD), CF(0xA0));
                VfxSlot_SetScaleUniform(SLOT(CHILD), CF(0xB0));
                *(unsigned char *)(CHILD + 0x28) = 1;
            }
        }
        if (CHANNEL < 0) {
            CHANNEL = SoundMgr_CountActiveSEInstances(0xBA);
            if (CHANNEL >= 0) {
                Vec pos = *V(0x8C);
                SoundMgr_PlaySE_Positional(0xBA, &pos, CHANNEL);
            }
        } else {
            Vec pos = *V(0x8C);
            SoundMgr_PlaySE_WithChannel(0xBA, &pos, CHANNEL);
        }
    }
}
#pragma use_lmw_stmw reset

/* DrawEffect_Cb_BurstSpawner_30Frame (0x800B69C4): over 30 frames, spawns
 * a burst of explosion pieces at the kart's joint 15 every 5 frames (four
 * on the first wave, one afterwards), coloured by variant. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51E8; /* 0.5 */
extern const float lbl_806D521C; /* deg->rad */
extern const float lbl_806D5220; /* -180.0 */
extern const float lbl_806D5224; /* 180.0 */
extern const float lbl_806D5230; /* -1.0 */
extern unsigned char lbl_80329E20[];
extern void Effect_ExplosionPiece_Update(unsigned char *e);

void DrawEffect_Cb_BurstSpawner_30Frame(unsigned char *self)
{
    unsigned char *tbl = lbl_80329E20;

    switch (STATE) {
    case 0:
        U32(0x180) = 30;
        U32(0x184) = 0;
        S8(0x190) = 0;
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        DrawEffect_Free(self);
        return;
    }
    if (U32(0x184) == 0) {
        int n = 4;
        int i;

        if (S8(0x190)) {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            unsigned char *e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
            if (e == 0) {
                continue;
            }
            Mtx44_GetTranslation_RowMajor(V_(e, 0x8C), KartDriver_GetJointByIdx(P(0x11C), 0xF));
            V_(e, 0x8C)->x += Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
            V_(e, 0x8C)->y += Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
            V_(e, 0x8C)->z += Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
            GetSpawnPosition(V_(e, 0xA4), 0.0f, 0.0f, lbl_806D51E8);
            Vec2_RotateX(V_(e, 0xA4), V_(e, 0xA4), lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224));
            Vec2_RotateY(V_(e, 0xA4), V_(e, 0xA4), lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224));
            *(signed char *)(e + 0x190) = 0;
            *(signed char *)(e + 0x191) = 2;
            *(signed char *)(e + 0x192) = 0;
            *(signed char *)(e + 0x193) = 1;
            *(void **)(e + 0x11C) = P(0x11C);
            switch (I(0x10)) {
            case 0:
                Vec3_Copy(V_(e, 0x120), (Vec *)(tbl + 0x664));
                break;
            case 1:
                Vec3_Copy(V_(e, 0x120), (Vec *)(tbl + 0x670));
                break;
            case 2:
                Vec3_Copy(V_(e, 0x120), (Vec *)(tbl + 0x67C));
                break;
            }
        }
        S8(0x190) = 1;
        U32(0x184) = 5;
    }
    TICK_TIMERS();
}

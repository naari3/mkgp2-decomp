/* CarrotItemEffect_Update (0x800B2164): the carrot worn on the driver's head.
 * The first tick sets up the sprite and the 600-frame life; the effect ends
 * early once its bus bit is gone (or, after 3 frames, when bit 16 is set it
 * clears bit 49).  While visible the sprite follows joint 15 of the kart,
 * scaled by 2 and offset per character. */
#include "game/types/Vec.h"

#include "game/ItemEffectBusPrivate.h"

#include "game/types/KartDriver.h"

typedef struct CarrotItemEffect {
    unsigned char pad000[0x14];
    unsigned char sprite[0x14]; /* 0x014 */
    signed char visible;        /* 0x028 */
    unsigned char pad029[0x48 - 0x29];
    float mtx[3][4];            /* 0x048 */
    unsigned char pad078[0xA0 - 0x78];
    Vec pos;                    /* 0x0A0 */
    unsigned char pad0AC[0xC8 - 0xAC];
    signed char state;          /* 0x0C8 */
    unsigned char pad0C9[0xF0 - 0xC9];
    unsigned int timers[4];     /* 0x0F0 */
    unsigned char pad100[0x188 - 0x100];
    KartDriver *driver;         /* 0x188 */
} CarrotItemEffect;

extern char lbl_803298F0[];
extern Vec CarrotItemEffect_Update_data_8041A000[];

extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float frame);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int n, int visible);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void ItemEffectBus_ClearMask(ItemEffectBus *bus, unsigned long long mask);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(KartDriver *driver);
extern void SpriteSlot_Container_Free(CarrotItemEffect *self);
extern void *KartDriver_GetJointByIdx(KartDriver *driver, int idx);
extern void Mtx_TransposeToMtx44(float dst[4][4], void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern int KartCharacterParam_GetIdentityIndex(KartDriver *driver);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern void Matrix4_Multiply(float dst[4][4], float a[4][4], float b[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);

#pragma exceptions on
void CarrotItemEffect_Update(CarrotItemEffect *self)
{
    ItemEffectBus *bus;
    float joint[4][4];
    float m[4][4];

    switch (self->state) {
    case 0:
        SpriteSlot_InitNonLoop(self->sprite, 0x8E);
        SpriteSlot_SetAnimFrameAndApplyScale(self->sprite, 1, 0.0f);
        SpriteSlot_SetJointVisibilityByName(self->sprite, lbl_803298F0, 0x10, 1);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self->sprite, 1);
        self->timers[0] = 600;
        self->timers[1] = 3;
        self->timers[2] = 60;
        self->state++;
    case 1:
        break;
    }

    if (self->timers[1] == 0) {
        bus = self->driver->itemBus;
        if ((bus->mask & 0x10000ULL) != 0) {
            self->timers[0] = 0;
            ItemEffectBus_ClearMask(bus, 0x2000000000000ULL);
        }
    }
    if (self->timers[2] == 0 && (self->driver->itemBus->mask & 0x2000000000000ULL) == 0) {
        self->timers[0] = 0;
    }

    if (FinalLapCoinJump_CheckActiveForObject(self->driver)) {
        self->visible = 0;
    } else {
        self->visible = 1;
    }

    if (self->timers[0] == 0) {
        SpriteSlot_Container_Free(self);
        return;
    }

    if (self->visible) {
        Mtx_TransposeToMtx44(joint, KartDriver_GetJointByIdx(self->driver, 15));
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, 2.0f);
        Mtx44_Translate(m, m, CarrotItemEffect_Update_data_8041A000[KartCharacterParam_GetIdentityIndex(self->driver)]);
        Matrix4_Multiply(m, m, joint);
        DbgScene_CopyMatrix3x4Transpose(self->mtx, m);
        Mtx44_GetTranslation_RowMajor(&self->pos, self->mtx);
    }

    if (self->timers[0] != 0) {
        self->timers[0]--;
    }
    if (self->timers[1] != 0) {
        self->timers[1]--;
    }
    if (self->timers[2] != 0) {
        self->timers[2]--;
    }
    if (self->timers[3] != 0) {
        self->timers[3]--;
    }
}
#pragma exceptions reset

/* BombItem_Tick (0x800FC854): the bomb held in the kart's hand.
 * State 1 keeps it on the hand joint until it is thrown (arm flag 1) or
 * discarded (arm flag 2). Once thrown, phase 0 starts the fuse (900 or 600
 * frames by team) and phase 1 grows it in and spawns the explosion item,
 * phase 2 detonates it when the fuse runs out or the kart loses the bomb
 * flag, and phase 3 fades it out. While thrown it rides in front of the
 * kart, lerped from the hand matrix. State 3 frees the item. */
#include "game/types/Vec.h"

typedef float Mtx44[4][4];
typedef float Mtx34[3][4];

typedef struct BombItem {
    unsigned char pad000[0x14];
    unsigned char slot[0x28 - 0x14]; /* 0x014 */
    unsigned char visible;    /* 0x028 */
    unsigned char pad029[0x2C - 0x29];
    float alpha;              /* 0x02C */
    unsigned char pad030[0x48 - 0x30];
    Mtx34 mtx;                /* 0x048 */
    unsigned char pad078[0xA0 - 0x78];
    Vec pos;                  /* 0x0A0 */
    unsigned char pad0AC[0xC4 - 0xAC];
    float scale;              /* 0x0C4 */
    signed char state;        /* 0x0C8 */
    signed char sub;          /* 0x0C9 */
    signed char phase;        /* 0x0CA */
    unsigned char pad0CB[0xF0 - 0xCB];
    unsigned int timers[4];   /* 0x0F0 */
    float grow;               /* 0x100 */
    unsigned char pad104[0x148 - 0x104];
    struct BombItem *blast;   /* 0x148 */
    unsigned char pad14C[0x180 - 0x14C];
    void *owner;              /* 0x180 */
    void *driver;             /* 0x184 */
    unsigned char pad188[0x18C - 0x188];
    signed char armed;        /* 0x18C */
    unsigned char pad18D[0x1DC - 0x18D];
    signed char team;         /* 0x1DC */
} BombItem;

typedef struct KartFlags {
    char pad[0x10];
    unsigned long long bits;
} KartFlags;

extern void BombExplosion_InitOrDestroy(BombItem *self);
extern void BombExplosion_UpdateShockwaveVfx(BombItem *blast, Mtx34 *mtx);
extern void DbgScene_CopyMatrix3x4Transpose(Mtx34 *dst, Mtx44 *src);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void GabyouItem_BuildLocalTransformFromHandJoint(BombItem *self, int flag, float a, float b, float c);
extern BombItem *ItemObject_AllocFromPool(void (*fn)(BombItem *));
extern void ItemObject_DecrementCategoryBudget(BombItem *self);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern float KartFxParam_GetConst1p5(void *driver);
extern void Matrix4_Identity(Mtx44 *m);
extern void Matrix4_Multiply(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
extern void Matrix4_PreMultiplyRotX(Mtx44 *dst, Mtx44 *src, float a);
extern void Matrix4_PreMultiplyTranslation(Mtx44 *dst, Mtx44 *src, float x, float y, float z);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, Mtx34 *mtx);
extern void Mtx44_Scale_Uniform(Mtx44 *dst, Mtx44 *src, float s);
extern void Mtx_Lerp(Mtx34 *dst, Mtx34 *a, Mtx34 *b, float t);
extern void Mtx_TransposeToMtx44(Mtx44 *dst, void *src);
extern void SoundMgr_PlaySE_Positional(unsigned int se, Vec pos, int ch);
extern void SpriteSlot_Container_Free(BombItem *self);
extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);

#define KART_FLAGS(drv) (*(KartFlags **)((unsigned char *)(drv) + 0x304))

void BombItem_Tick(BombItem *self)
{
    Mtx44 m;
    Mtx44 root;
    Mtx44 local;
    Mtx34 m34;

    switch (self->state) {
    case 0:
        SpriteSlot_InitNonLoop(self->slot, 0x52);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self->slot, 1);
        self->state = 1;
        self->sub = 0;
    case 1:
        switch (self->sub) {
        case 0:
            self->alpha = 0.0f;
            self->sub++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 2.0f, 2.356194f, 1.2f);
            if (FinalLapCoinJump_CheckActiveForObject(self->driver)) {
                self->visible = 0;
            } else {
                self->visible = 1;
            }
            switch (self->armed) {
            case 1:
                self->visible = 1;
                self->armed = 0;
                self->alpha = 1.0f;
                self->sub++;
                self->phase = 0;
                break;
            case 2:
                self->armed = 0;
                self->visible = 0;
                self->state = 3;
                self->sub = 0;
                break;
            }
            break;
        case 2:
            switch (self->phase) {
            case 0:
                self->grow = 0.0f;
                if (self->team) {
                    self->timers[0] = 900;
                } else {
                    self->timers[0] = 600;
                }
                SoundMgr_PlaySE_Positional(0x83, self->pos, 0);
                self->phase++;
            case 1:
                self->grow += 0.1f;
                if (1.0f < self->grow) {
                    self->grow = 1.0f;
                    self->blast = ItemObject_AllocFromPool(BombExplosion_InitOrDestroy);
                    if (self->blast != 0) {
                        self->blast->team = self->team;
                        self->blast->driver = self->driver;
                        self->blast->owner = self->owner;
                    }
                    self->phase++;
                }
                break;
            case 2:
                if ((KART_FLAGS(self->driver)->bits & 0x4000000) == 0) {
                    self->timers[0] = 0;
                }
                if (self->timers[0] == 0) {
                    if (self->blast != 0) {
                        self->blast->armed = 1;
                        BombExplosion_InitOrDestroy(self->blast);
                        self->blast = 0;
                    }
                    self->phase++;
                }
                break;
            case 3:
                self->alpha -= 0.1f;
                if (self->alpha < 0.0f) {
                    self->visible = 0;
                    self->state = 3;
                    self->sub = 0;
                }
                break;
            }
            if (FinalLapCoinJump_CheckActiveForObject(self->driver)) {
                self->visible = 0;
            } else {
                self->visible = 1;
            }
            Mtx_TransposeToMtx44(&root, KartDriver_GetKartRootMtx(self->driver));
            Matrix4_Identity(&local);
            Matrix4_PreMultiplyRotX(&local, &local, 0.087266445f);
            Matrix4_PreMultiplyTranslation(&local, &local, 0.0f, 3.0f, 10.0f);
            Matrix4_Multiply(&m, &local, &root);
            Matrix4_Identity(&local);
            Mtx44_Scale_Uniform(&local, &local, 1.5f);
            Matrix4_Multiply(&m, &local, &m);
            DbgScene_CopyMatrix3x4Transpose(&m34, &m);
            Mtx_Lerp(&self->mtx, &m34, &self->mtx, self->grow);
            Mtx44_GetTranslation_RowMajor(&self->pos, &self->mtx);
            self->scale = 1.5f * KartFxParam_GetConst1p5(self->driver);
            BombExplosion_UpdateShockwaveVfx(self->blast, &self->mtx);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
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

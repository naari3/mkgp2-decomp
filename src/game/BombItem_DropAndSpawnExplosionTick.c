/* BombItem_DropAndSpawnExplosionTick (0x800FBBD4): the dropped bomb's fuse.
 * State 0 waits for the arm flag, then lights the kart wave glow, plays the
 * fuse sound at the kart and starts a 10-frame countdown.  State 1 spawns the
 * explosion item (0x67) in front of the kart once the countdown runs out and
 * frees the bomb.  All four item timers tick down every frame. */
#include "game/types/Vec.h"

#include "game/types/DrawEffect.h"

#include "game/types/BombItem.h"

extern unsigned int Effect_KartWaveGlow_Update[];
extern const Vec BombItem_DropAndSpawnExplosionTick_rodata_8032FF40;

extern DrawEffect *DrawEffect_SpawnDirect(void *update);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void SoundMgr_PlaySE_Positional(unsigned int se, Vec pos, int ch);
extern BombItem *ItemObject_SpawnWithAlias(int id, int alias);
extern void Mtx_TransposeToMtx44(float dst[4][4], void *src);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec *, float m[4][4], Vec *);
static inline void Mtx44_TransformVec3_ByValue(Vec *out, float m[4][4], Vec in) { Mtx44_TransformVec3(out, m, &in); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
extern void ItemObject_DecrementCategoryBudget(BombItem *self);
extern void SpriteSlot_Container_Free(BombItem *self);

#pragma exceptions on
void BombItem_DropAndSpawnExplosionTick(BombItem *self)
{
    DrawEffect *glow;
    BombItem *blast;
    Vec pos;
    float m[4][4];

    switch (self->state) {
    case 0:
        if (self->armed) {
            glow = DrawEffect_SpawnDirect(Effect_KartWaveGlow_Update);
            if (glow != 0) {
                glow->driver = self->driver;
            }
            Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetKartRootMtx(self->driver));
            SoundMgr_PlaySE_Positional(0xB7, pos, 0);
            self->timers[0] = 10;
            self->state++;
        }
        break;
    case 1:
        if (self->timers[0] == 0) {
            blast = ItemObject_SpawnWithAlias(0x67, 0xFF);
            if (blast != 0) {
                blast->team = self->team;
                blast->tag = self->tag;
                Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(self->driver));
                Mtx44_TransformVec3(&blast->pos, m, BombItem_DropAndSpawnExplosionTick_rodata_8032FF40);
                blast->owner = self->owner;
                blast->driver = self->driver;
            }
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
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

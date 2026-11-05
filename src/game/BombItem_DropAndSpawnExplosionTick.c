/* BombItem_DropAndSpawnExplosionTick (0x800FBBD4): the dropped bomb's fuse.
 * State 0 waits for the arm flag, then lights the kart wave glow, plays the
 * fuse sound at the kart and starts a 10-frame countdown.  State 1 spawns the
 * explosion item (0x67) in front of the kart once the countdown runs out and
 * frees the bomb.  All four item timers tick down every frame. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct DrawEffect {
    unsigned char pad000[0x11C];
    void *driver; /* 0x11C */
} DrawEffect;

typedef struct BombItem {
    unsigned char pad000[0xA0];
    Vec pos;                  /* 0x0A0 */
    unsigned char pad0AC[0xC8 - 0xAC];
    signed char state;        /* 0x0C8 */
    unsigned char pad0C9[0xF0 - 0xC9];
    unsigned int timers[4];   /* 0x0F0 */
    unsigned char pad100[0x180 - 0x100];
    void *owner;              /* 0x180 */
    void *driver;             /* 0x184 */
    unsigned char pad188[0x18C - 0x188];
    signed char armed;        /* 0x18C */
    unsigned char pad18D[0x1DC - 0x18D];
    unsigned char team;       /* 0x1DC */
    unsigned char pad1DD[0x1E0 - 0x1DD];
    unsigned int tag;         /* 0x1E0 */
} BombItem;

extern unsigned int Effect_KartWaveGlow_Update[];
extern const Vec lbl_8032FF40;

extern DrawEffect *DrawEffect_SpawnDirect(void *update);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void SoundMgr_PlaySE_Positional(unsigned int se, Vec pos, int ch);
extern BombItem *ItemObject_SpawnWithAlias(int id, int alias);
extern void Mtx_TransposeToMtx44(float dst[4][4], void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
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
                Mtx44_TransformVec3(&blast->pos, m, lbl_8032FF40);
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

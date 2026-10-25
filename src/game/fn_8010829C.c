typedef struct Vec3 { float x, y, z; } Vec3;

extern void Effect_Explosion_Compound_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern void Item_PropagateHitToDriversInRadius(unsigned char *self, int a);
extern void SpriteSlot_Container_Free(void *self);
extern float lbl_806D6708;
extern float lbl_806D670C;
extern float lbl_806D66E4;
extern float lbl_806D6710;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_8010829C(unsigned char *self)
{
    Vec3 pos;

    switch ((signed char)self[0xC8]) {
    case 0:
        self[0x1C] = 0x9B;
        if (*(int *)(self + 0x8) == 0x63) {
            *(float *)(self + 0xC4) = lbl_806D6708;
        } else {
            *(float *)(self + 0xC4) = lbl_806D670C;
        }
        if (*(int *)(self + 0x8) == 0x63) {
            *(unsigned int *)(self + 0xF0) = 1;
        } else {
            *(unsigned int *)(self + 0xF0) = 0;
        }
        *(unsigned char **)(self + 0x138) = DrawEffect_SpawnDirect(Effect_Explosion_Compound_Update);
        if (*(unsigned char **)(self + 0x138)) {
            Vec3_Copy(*(unsigned char **)(self + 0x138) + 0x8C, self + 0xA0);
            if (*(int *)(self + 0x8) == 0x63) {
                *(float *)(*(unsigned char **)(self + 0x138) + 0xB0) = lbl_806D66E4;
            } else {
                *(float *)(*(unsigned char **)(self + 0x138) + 0xB0) = lbl_806D6710;
            }
            if (*(int *)(self + 0x8) == 0x63) {
                (*(unsigned char **)(self + 0x138))[0x190] = 0;
            } else {
                (*(unsigned char **)(self + 0x138))[0x190] = 1;
            }
        }
        pos = *(Vec3 *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0x60, &pos, 0);
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        if (*(int *)(self + 0x8) == 0x63 && *(unsigned int *)(self + 0xF0) != 0) {
            Item_PropagateHitToDriversInRadius(self, 0);
        }
        if (*(unsigned int *)(self + 0xF0) == 0) {
            if (*(unsigned char **)(self + 0x138)) {
                (*(unsigned char **)(self + 0x138))[0xC9] = 1;
            }
            *(unsigned char **)(self + 0x138) = 0;
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    }
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}

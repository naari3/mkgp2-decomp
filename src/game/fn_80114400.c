typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_80113F30(unsigned char *self, unsigned char *sub);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void Effect_DustScatter_Update(void);
extern void Effect_HitFlash_Update(void);
extern void EffectVfx82_FieldItemDropPuff_Tick(void);
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern float BuildOrientationFromYaw(float yaw);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80114400(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    Vec3 gpos;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x99);
        self[0x8C] = 2;
        self[0x8D] = 0;
        *(float *)(self + 0xC4) = 3.0f;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80113F30(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0: {
            int i;
            unsigned char *e;
            for (i = 0; i < 5; i++) {
                e = DrawEffect_SpawnDirect(Effect_DustScatter_Update);
                if (e) {
                    *(int *)(e + 0x10) = 2;
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, Rand_RangeFloat(0.8f, 1.2f));
                    Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-90.0f, -30.0f));
                    Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
                    *(int *)(e + 0x11C) = *(int *)(sub + 0x9C);
                }
            }
            self[0x28] = 0;
            self[0xC8] = 3;
        } break;
        case 4: {
            int i;
            unsigned char *e;
            for (i = 0; i < 5; i++) {
                e = DrawEffect_SpawnDirect(Effect_DustScatter_Update);
                if (e) {
                    *(int *)(e + 0x10) = 2;
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, Rand_RangeFloat(0.8f, 1.2f));
                    Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-90.0f, -30.0f));
                    Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
                    *(int *)(e + 0x11C) = *(int *)(sub + 0x9C);
                }
            }
            self[0x28] = 0;
            self[0xC8] = 3;
        } break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0: {
                int i;
                unsigned char *e;
                for (i = 0; i < 5; i++) {
                    e = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
                    if (e) {
                        *(int *)(e + 0x10) = 2;
                        Vec3_Copy(e + 0x8C, self + 0xA0);
                        *(int *)(e + 0xCC) = *(int *)(self + 0x9C);
                    }
                }
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x4) = 30;
                self[0xC9]++;
            }
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 3.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.5235987f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7: {
            int i;
            unsigned char *e;
            for (i = 0; i < 5; i++) {
                e = DrawEffect_SpawnDirect(Effect_DustScatter_Update);
                if (e) {
                    *(int *)(e + 0x10) = 2;
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, Rand_RangeFloat(0.8f, 1.2f));
                    Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-90.0f, -30.0f));
                    Vec2_RotateY(e + 0xA4, e + 0xA4,
                                 BuildOrientationFromYaw(0.017453289f * Rand_RangeFloat(90.0f, 270.0f) +
                                                         *(float *)(self + 0xB0)));
                }
            }
            e = DrawEffect_SpawnDirect(EffectVfx82_FieldItemDropPuff_Tick);
            if (e) {
                Vec3_Copy(e + 0x8C, self + 0xA0);
                GetSpawnPosition(e + 0x98, 0.0f, 3.141592f + *(float *)(self + 0xB0), 0.0f);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
        } break;
        case 5:
            switch ((signed char)self[0xC9]) {
            case 0:
                gpos = *(Vec3 *)(self + 0xA0);
                ItemObject_GetGroundTypeAt(&gpos, (float *)(sub + 0x14), 0);
                *(float *)(sub + 0x14) = *(float *)(self + 0xA4) - *(float *)(sub + 0x14);
                self[0xC9]++;
            case 1:
                Item_DecayVelocityScalar(self, 3.0f);
                Item_AdvanceProjectileSimple(self, sub + 0x14, 15.0f, 1.0f);
                *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
                if (*(float *)(self + 0x2C) < 0.0f) {
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                }
                break;
            }
            break;
        }
        break;
    case 3:
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}

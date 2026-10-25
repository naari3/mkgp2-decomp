/* ItemObject_Tick_Kind2b_Teresa (0x800E4760): Teresa (Boo) item. State 1
 * runs the hold/throw/homing logic (ItemObject_Teresa_GrabAndArc_Sub);
 * state 2 plays the ending picked by the end code in 0xCB: track the
 * robbed kart, burst into pieces, tether back to the owner, orbit the kart
 * or fade away. */
typedef struct Vec { float x, y, z; } Vec;

extern const char lbl_8032E630[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void ItemObject_Teresa_GrabAndArc_Sub(unsigned char *self, unsigned char *sub);
extern void ItemObject_Teresa_TrackToKart_Sub(unsigned char *self, unsigned char *sub);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_ExplosionPiece_Update(unsigned char *self);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateX(Vec *out, const Vec *in, float angle);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern void Vec3_Subtract_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void Vec3_Add_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void Vec3_Scale(Vec *out, const Vec *in, float s);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Teresa_Burst(unsigned char *self, unsigned char *sub)
{
    Vec jpos;
    Vec se;
    unsigned char *e;
    int i;

    JointByName_GetWorldPosition(&jpos, self + 0x14, lbl_8032E630);
    for (i = 0; i < 6; i++) {
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &jpos);
            GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f, 0.6f * Rand_RangeFloat(0.7f, 1.3f));
            Vec2_RotateX((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            e[0x190] = 1;
            e[0x191] = 2;
            e[0x192] = 1;
            *(void **)(e + 0x11C) = SP(0x9C);
            GetSpawnPosition((Vec *)(e + 0x120), 1.0f, 1.0f, 1.0f);
            e[0x193] = 1;
        }
    }
    se = *(Vec *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0x87, &se, 0);
    self[0x28] = 0;
    S8(0xC8) = 3;
    S8(0xC9) = 0;
}

static inline void Teresa_Fade(unsigned char *self, unsigned char *sub)
{
    switch (S8(0xC9)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        SU32(0x4) = 40;
        S8(0xC9)++;
    case 1:
        break;
    }
    Item_DecayVelocityScalar(self, 1.0f);
    Vec3_Scale((Vec *)(self + 0xB8), (Vec *)(self + 0xB8), 0.9f);
    if (SU32(0x4) == 0) {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
        }
    }
}

void ItemObject_Tick_Kind2b_Teresa(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x2B);
        self[0x8C] = 3;
        self[0x8D] = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        ItemObject_Teresa_GrabAndArc_Sub(self, sub);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            ItemObject_Teresa_TrackToKart_Sub(self, sub);
            break;
        case 1:
            Teresa_Burst(self, sub);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                SF(0x14) = 0.0f;
                SF(0x18) = F(0xC4);
                S8(0xC9)++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(sub + 0x14), SF(0x18), 0.08726645f, 0.08726645f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 4:
            Teresa_Burst(self, sub);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                Vec3_Subtract_DestFirst((Vec *)(sub + 0x34), (Vec *)(self + 0xA0), (Vec *)(P(0x9C) + 0xA0));
                SU32(0x4) = 30;
                S8(0xC9)++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, SU32(0x4), 0.0f, 0.2617993f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 7:
            Teresa_Burst(self, sub);
            break;
        case 9:
            Teresa_Fade(self, sub);
            break;
        case 5:
            Teresa_Fade(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst((Vec *)(self + 0xA0), (Vec *)(self + 0xA0), (Vec *)(self + 0xB8));
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    Timer_Tick((unsigned int *)(sub + 0x4));
    Timer_Tick((unsigned int *)(sub + 0x8));
    Timer_Tick((unsigned int *)(sub + 0xC));
    Timer_Tick((unsigned int *)(sub + 0x10));
}

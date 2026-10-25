/* ItemObject_Tick_Kind3dTo3f_GreenShell (0x800EFC84): per-frame tick of
 * the green shell items (kinds 0x3D..0x3F). State 1 is held/flying, state 2
 * dispatches on how the shell left the flying state: hit rebound, tether
 * back to the kart, shatter, orbit, or a fade on the ground. Kind 0x3F
 * also drives a spark spray, and the shell's trail effect follows it. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct GreenShellWork {
    unsigned char bounces;
    unsigned char pad1[3];
    unsigned int timers[4];
    float groundY;
    float spin;
    float phase;
    unsigned char pad20[0x34 - 0x20];
    Vec anchor;
    Vec rebound;
    unsigned char *eff;
    unsigned char *spark;
    unsigned char pad54[0x94 - 0x54];
    void *owner;
    void *driver;
    void *target;
    unsigned char padA0[0xF0 - 0xA0];
    unsigned char shellColor;
    unsigned char padF1[3];
    int shellTimer;
} GreenShellWork;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void Effect_SparkSprayCompound_Update(unsigned char *self);
extern void Effect_SpinBurst_Update(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void GreenShell_State1_Held(unsigned char *self, GreenShellWork *w);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloatMax(float max);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Vec3_Scale(void *out, void *in, float s);
extern void Vec3_Lerp(void *dst, Vec a, Vec b, float t);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double x);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Effect_SparkSpray_PlaceChildren(unsigned char *e, Vec pos, float scale, float alpha);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))

static inline float sinf(float x)
{
    return sin(x);
}

static inline void GreenShell_Spin(unsigned char *self, GreenShellWork *w)
{
    F(0xB0) = BuildOrientationFromYaw(F(0xB0) + w->spin);
    w->phase = BuildOrientationFromYaw(0.5235987f + w->phase);
    F(0xAC) = 0.785398f * sinf(w->phase);
    Item_DecayVelocityScalar(self, 1.75f);
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void GreenShell_Shatter(unsigned char *self, GreenShellWork *w, int copyTimer)
{
    unsigned char *e;
    int i;
    Vec v;
    Vec s;

    switch (I(0x8)) {
    case 0x3D:
    case 0x3F:
        for (i = 0; i < 15; i++) {
            e = DrawEffect_SpawnDirect(Effect_SpinBurst_Update);
            if (e != 0) {
                *(int *)(e + 0x10) = I(0x8);
                Vec3_Copy(e + 0x8C, self + 0xA0);
                GetSpawnPosition(&v, 0.0f, 0.0f, Rand_RangeFloatMax(7.0f));
                Vec2_RotateX(&v, &v, 0.017453289f * Rand_RangeFloat(-90.0f, -30.0f));
                Vec2_RotateY(&v, &v, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
                Vec3_Scale(&s, self + 0xB8, 0.2f);
                Vec3_Lerp(e + 0xA4, v, s, 0.5f);
                *(float *)(e + 0xB0) = 0.4f * F(0xC4);
                *(void **)(e + 0x11C) = w->target;
            }
        }
        break;
    case 0x3E:
        e = ItemObject_SpawnWithAlias(0x63, 0xFF);
        if (e != 0) {
            e[0x1DC] = w->shellColor;
            if (copyTimer) {
                *(int *)(e + 0x1E0) = w->shellTimer;
            }
            Vec3_Copy(e + 0xA0, self + 0xA0);
            *(void **)(e + 0x180) = w->owner;
            *(void **)(e + 0x184) = w->driver;
        }
        break;
    }
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void GreenShell_Break(unsigned char *self, GreenShellWork *w)
{
    GreenShell_Shatter(self, w, 0);
}

static inline void GreenShell_Rebound(unsigned char *self, GreenShellWork *w)
{
    Vec root;

    switch (S8(0xC9)) {
    case 0:
        Item_PrepareHitRebound(self, &w->rebound, &w->anchor, &w->timers[0]);
        self[0xC9]++;
    case 1:
        break;
    }
    if (w->timers[0] == 0) {
        if (w->bounces != 0) {
            ItemHit_Dispatch(self, 0, self + 0xA0, w->target);
        }
        GreenShell_Shatter(self, w, 1);
        return;
    }
    Vec3_AddNormalizedXZ(self, &w->rebound, w->anchor);
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(w->target));
    Vec3_Add_DestFirst(self + 0xA0, &root, &w->rebound);
    GreenShell_Spin(self, w);
}

static inline void GreenShell_FadeOnGround(unsigned char *self, GreenShellWork *w)
{
    float gy;

    switch (S8(0xC9)) {
    case 0:
        ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &w->groundY, 0);
        if (*(char *)(self + 0xCB) != 5) {
            w->timers[0] = 10;
        } else {
            w->timers[0] = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            F(0xBC) = 0.0f;
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (w->timers[0] == 0) {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(char *)(self + 0xCB) != 5) {
        F(0xBC) += -0.2f;
    }
    if (ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &gy, 0)) {
        F(0xA4) += gy - w->groundY;
        w->groundY = gy;
    }
    GreenShell_Spin(self, w);
}

void ItemObject_Tick_Kind3dTo3f_GreenShell(unsigned char *self)
{
    GreenShellWork *w = (GreenShellWork *)(self + 0xEC);

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 0x3D:
            SpriteSlot_InitNonLoop(self + 0x14, 0x41);
            break;
        case 0x3E:
            SpriteSlot_InitNonLoop(self + 0x14, 0x42);
            break;
        case 0x3F:
            SpriteSlot_InitNonLoop(self + 0x14, 0x43);
            break;
        }
        self[0x8C] = 3;
        self[0x8D] = 0;
        if (I(0x8) == 0x3F) {
            w->spark = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Update);
        }
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        GreenShell_State1_Held(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            GreenShell_Rebound(self, w);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                w->groundY = 0.0f;
                w->spin = F(0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &w->groundY, w->spin, 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            GreenShell_Break(self, w);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(&w->anchor, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                w->timers[0] = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.75f);
            if (Item_OrbitAnchorKart(self, &w->anchor, w->timers[0], 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            GreenShell_Break(self, w);
            break;
        case 9:
            GreenShell_FadeOnGround(self, w);
            break;
        case 5:
            GreenShell_FadeOnGround(self, w);
            break;
        }
        break;
    case 3:
        if (w->eff != 0) {
            w->eff[0xC9] = 1;
        }
        if (w->spark != 0) {
            w->spark[0xC9] = 1;
        }
        w->eff = 0;
        w->spark = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    if (w->eff != 0) {
        Vec3_Copy(w->eff + 0x8C, self + 0xA0);
        *(float *)(w->eff + 0xB0) = 0.7f * F(0xC4);
        *(float *)(w->eff + 0x2C) = F(0x2C);
        w->eff[0x28] = self[0x28];
    }
    if (w->spark != 0) {
        if (S8(0x28)) {
            Effect_SparkSpray_PlaceChildren(w->spark, *(Vec *)(self + 0xA0), 3.0f * F(0xC4), F(0x2C));
        } else {
            Effect_SparkSpray_PlaceChildren(w->spark, *(Vec *)(self + 0xA0), 3.0f * F(0xC4), 0.0f);
        }
    }
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    Timer_Tick(&w->timers[0]);
    Timer_Tick(&w->timers[1]);
    Timer_Tick(&w->timers[2]);
    Timer_Tick(&w->timers[3]);
}

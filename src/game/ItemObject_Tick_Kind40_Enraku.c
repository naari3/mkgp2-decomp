/* ItemObject_Tick_Kind40_Enraku (0x800F0EE0): per-frame tick of the
 * Enraku item. State 1 is held/flying, state 2 dispatches on how it left
 * the flying state: most endings drop a shell object (alias 0x65) and fade
 * out, others tether it back to the kart or orbit the hit kart. Its smoke
 * cloud effect follows the item's "enraku_smoke" joint. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct EnrakuWork {
    unsigned char pad0[4];
    unsigned int timers[4];
    float tether;
    float tetherScale;
    unsigned char pad1C[0x34 - 0x1C];
    Vec anchor;
    unsigned char pad40[0x4C - 0x40];
    unsigned char *eff;
    unsigned char pad50[0x94 - 0x50];
    void *owner;
    void *driver;
    void *target;
    unsigned char padA0[0xF0 - 0xA0];
    unsigned char shellColor;
    unsigned char padF1[3];
    int shellTimer;
} EnrakuWork;

extern const char lbl_8032F530[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void Enraku_State1_Held(unsigned char *self, EnrakuWork *w);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void Vec3_Scale(void *out, void *in, float s);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern float BuildOrientationFromYaw(float yaw);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(void *out, void *slot, const char *name);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern void Effect_SmokeCloud_DriveSubslots(unsigned char *e, Vec pos, Vec dir, float alpha);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))

static inline void Enraku_KillSmoke(EnrakuWork *w)
{
    if (w->eff != 0) {
        w->eff[0xC9] = 1;
    }
    w->eff = 0;
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_Tick_Kind40_Enraku(unsigned char *self)
{
    EnrakuWork *w = (EnrakuWork *)(self + 0xEC);
    unsigned char *o;
    Vec jp;
    Vec d;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x44);
        self[0x14] = 4;
        self[0x8C] = 2;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        Enraku_State1_Held(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            switch (S8(0xC9)) {
            case 0:
                o = ItemObject_SpawnWithAlias(0x65, 0xFF);
                if (o != 0) {
                    o[0x1DC] = w->shellColor;
                    *(int *)(o + 0x1E0) = w->shellTimer;
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    Vec3_Copy(o + 0xB8, self + 0xB8);
                    *(void **)(o + 0x180) = w->owner;
                    *(void **)(o + 0x184) = w->driver;
                }
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                w->tether = 0.0f;
                w->tetherScale = F(0xC4);
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &w->tether, w->tetherScale, 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            switch (S8(0xC9)) {
            case 0:
                o = ItemObject_SpawnWithAlias(0x65, 0xFF);
                if (o != 0) {
                    o[0x1DC] = w->shellColor;
                    *(int *)(o + 0x1E0) = w->shellTimer;
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    Vec3_Copy(o + 0xB8, self + 0xB8);
                    *(void **)(o + 0x180) = w->owner;
                    *(void **)(o + 0x184) = w->driver;
                }
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(&w->anchor, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                w->timers[0] = 30;
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, &w->anchor, w->timers[0], 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            switch (S8(0xC9)) {
            case 0:
                o = ItemObject_SpawnWithAlias(0x65, 0xFF);
                if (o != 0) {
                    o[0x1DC] = w->shellColor;
                    *(int *)(o + 0x1E0) = w->shellTimer;
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    Vec3_Copy(o + 0xB8, self + 0xB8);
                    *(void **)(o + 0x180) = w->owner;
                    *(void **)(o + 0x184) = w->driver;
                }
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 8:
            switch (S8(0xC9)) {
            case 0:
                o = ItemObject_SpawnWithAlias(0x65, 0xFF);
                if (o != 0) {
                    o[0x1DC] = w->shellColor;
                    *(int *)(o + 0x1E0) = w->shellTimer;
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    Vec3_Copy(o + 0xB8, self + 0xB8);
                    *(void **)(o + 0x180) = w->owner;
                    *(void **)(o + 0x184) = w->driver;
                }
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 9:
            switch (S8(0xC9)) {
            case 0:
                w->timers[0] = 10;
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            F(0xBC) += -0.1f;
            F(0xAC) = BuildOrientationFromYaw(0.34906578f + F(0xAC));
            Item_DecayVelocityScalar(self, 2.0f);
            if (w->timers[0] == 0) {
                F(0x2C) -= 0.05f;
                if (F(0x2C) < 0.0f) {
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                }
            }
            break;
        case 5:
            switch (S8(0xC9)) {
            case 0:
                o = ItemObject_SpawnWithAlias(0x65, 0xFF);
                if (o != 0) {
                    o[0x1DC] = w->shellColor;
                    *(int *)(o + 0x1E0) = w->shellTimer;
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    Vec3_Copy(o + 0xB8, self + 0xB8);
                    *(void **)(o + 0x180) = w->owner;
                    *(void **)(o + 0x184) = w->driver;
                }
                Enraku_KillSmoke(w);
                self[0xC9]++;
            case 1:
                break;
            }
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        }
        break;
    case 3:
        Enraku_KillSmoke(w);
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    if (w->eff != 0) {
        JointByName_GetWorldPosition(&jp, self + 0x14, lbl_8032F530);
        Vec3_Subtract_DestFirst(&d, &jp, self + 0xA0);
        Vec3_Scale(&d, &d, 1.0f / Vec3_Magnitude_Wrapper(&d));
        if (S8(0x28)) {
            Effect_SmokeCloud_DriveSubslots(w->eff, jp, d, F(0x2C));
        } else {
            Effect_SmokeCloud_DriveSubslots(w->eff, jp, d, 0.0f);
        }
    }
    Timer_Tick(&w->timers[0]);
    Timer_Tick(&w->timers[1]);
    Timer_Tick(&w->timers[2]);
    Timer_Tick(&w->timers[3]);
}

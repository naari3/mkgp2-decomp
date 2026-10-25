/* ItemObject_Tick_Kind41_KuppaShell (0x800F1F84): per-frame tick of the
 * Kuppa (Bowser) shell. State 1 is held/flying, state 2 dispatches on how
 * it left the flying state: tether back to the kart, break into a shell
 * pile, or keep rolling while it fades out. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct KuppaShellWork {
    unsigned char bounces;
    unsigned char pad1[3];
    unsigned int timers[4];
    float tether;
    float tetherScale;
} KuppaShellWork;

extern const char lbl_8032F548[];
extern const char lbl_8032F564[];
extern int g_ccClass;
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void KuppaShell_State1_Held(unsigned char *self, KuppaShellWork *w);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void ShellPile_Spawn(unsigned char *self, KuppaShellWork *w);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, void *groundY, float f);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
extern float FAbs_FloatAsDouble(float x);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))

static inline void KuppaShell_RollFade(unsigned char *self, KuppaShellWork *w)
{
    Vec n;
    int landed;
    float gy;

    switch (S8(0xC9)) {
    case 0:
        if (S8(0xCB) != 5) {
            w->timers[0] = 10;
        } else {
            w->timers[0] = 0;
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
    F(0xBC) += -0.2f;
    Item_AccelClampVelocity(self, g_ccClass == 0 ? 12.0f : 17.0f, g_ccClass == 0 ? 1.0f : 2.0f);
    F(0xB0) = BuildOrientationFromYaw(0.2617993f + F(0xB0));
    Item_DecayVelocityScalar(self, 8.0f);
    if (Item_CheckWallCollision(self, &n, 0)) {
        Item_BounceOffWall(self, n, 0, 0, 0.5f, 0.0f);
    }
    if (Item_AdvanceFallingDrop(self, &landed, &gy, 2.5f) && landed != 0) {
        F(0xBC) *= 0.1f;
        F(0xB4) = Item_ProbeLateralGroundPitch(*(Vec *)(self + 0xA0), F(0xB0), 5.0f, F(0xA4) - gy);
        if (0.2617993f < FAbs_FloatAsDouble(F(0xB4))) {
            if (0.0f < F(0xB4)) {
                Vec2_RotateY(self + 0xB8, self + 0xB8, 0.1f * -(F(0xB4) - 0.2617993f));
            } else {
                Vec2_RotateY(self + 0xB8, self + 0xB8, 0.1f * -(0.2617993f + F(0xB4)));
            }
        }
    }
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_Tick_Kind41_KuppaShell(unsigned char *self)
{
    KuppaShellWork *w = (KuppaShellWork *)(self + 0xEC);

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x45);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_8032F548, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_8032F564, 0x10, 1);
        self[0x8C] = 4;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        KuppaShell_State1_Held(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                w->tether = 0.0f;
                w->tetherScale = F(0xC4);
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
            ShellPile_Spawn(self, w);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 7:
            ShellPile_Spawn(self, w);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 9:
            KuppaShell_RollFade(self, w);
            break;
        case 5:
            KuppaShell_RollFade(self, w);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    Timer_Tick(&w->timers[0]);
    Timer_Tick(&w->timers[1]);
    Timer_Tick(&w->timers[2]);
    Timer_Tick(&w->timers[3]);
}

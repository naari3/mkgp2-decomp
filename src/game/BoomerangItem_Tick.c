/* BoomerangItem_Tick (0x800FFBB8): per-frame tick of the boomerang item.
 * On spawn it allocates its partner object (kind 0x57) and splits the two
 * blade joints between them. State 1 is held/flying, state 2 fades it out
 * or tethers it back to the kart. Each frame the partner follows the
 * item's "boomerang" joint, scaled by the spin pace. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct BoomerangWork {
    unsigned char thrown;
    unsigned char pad1[3];
    unsigned int timers[4];
    float pace;
    float tether;
    float tetherScale;
    unsigned char pad20[0x5C - 0x20];
    unsigned char *sub;
    unsigned char pad60[0x90 - 0x60];
    unsigned char spawned;
    unsigned char pad91[3];
    void *owner;
    void *driver;
    unsigned char pad9C[0xF0 - 0x9C];
    unsigned char shellColor;
} BoomerangWork;

extern const char lbl_80330398[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void fn_800D748C(void);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void Boomerang_LaunchAndTickStateMachine(unsigned char *self, BoomerangWork *w);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(void *out, void *slot, const char *name);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void BoomerangItem_Tick(unsigned char *self)
{
    const char *base = lbl_80330398;
    BoomerangWork *w = (BoomerangWork *)(self + 0xEC);
    float m[4][4];

    switch (S8(0xC8)) {
    case 0:
        w->spawned = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x55);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, base + 0x41C, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, base + 0x42C, 0x10, 1);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        w->thrown = 1;
        self[0x14] = 4;
        self[0x8C] = 4;
        self[0x8D] = 0;
        w->sub = ItemObject_AllocFromPool(fn_800D748C);
        if (w->sub != 0) {
            w->sub[0x1DC] = w->shellColor;
            w->sub[0x17C] = 1;
            *(int *)(w->sub + 0x8) = 0x57;
            *(unsigned char **)(w->sub + 0xE4) = self;
            SpriteSlot_InitNonLoop(w->sub + 0x14, 0x56);
            SpriteSlot_SetJointVisibilityByName(w->sub + 0x14, base + 0x41C, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(w->sub + 0x14, base + 0x42C, 0x10, 0);
            *(void **)(w->sub + 0x180) = w->owner;
            *(void **)(w->sub + 0x184) = w->driver;
            w->sub[0x8C] = 4;
            w->sub[0x8D] = 0;
        }
        w->pace = 1.0f;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        Boomerang_LaunchAndTickStateMachine(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 4:
            switch (S8(0xC9)) {
            case 0:
                if (S8(0xCB) != 5) {
                    w->timers[0] = 10;
                } else {
                    w->timers[0] = 0;
                }
                if (w->sub != 0) {
                    SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 0, 0.0f);
                }
                w->pace = 1.0f;
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
                    break;
                }
            }
            if (*(char *)(self + 0xCB) != 5) {
                F(0xBC) += -0.1f;
            }
            Item_DecayVelocityScalar(self, 4.5f);
            break;
        case 9:
            switch (S8(0xC9)) {
            case 0:
                if (S8(0xCB) != 5) {
                    w->timers[0] = 10;
                } else {
                    w->timers[0] = 0;
                }
                if (w->sub != 0) {
                    SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 0, 0.0f);
                }
                w->pace = 1.0f;
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
                    break;
                }
            }
            if (*(char *)(self + 0xCB) != 5) {
                F(0xBC) += -0.1f;
            }
            Item_DecayVelocityScalar(self, 4.5f);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                w->tether = 0.0f;
                w->tetherScale = F(0xC4);
                if (w->sub != 0) {
                    SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 0, 0.0f);
                }
                w->pace = 1.0f;
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &w->tether, w->tetherScale, 0.0f, 0.0f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 5:
            switch (S8(0xC9)) {
            case 0:
                if (S8(0xCB) != 5) {
                    w->timers[0] = 10;
                } else {
                    w->timers[0] = 0;
                }
                if (w->sub != 0) {
                    SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 0, 0.0f);
                }
                w->pace = 1.0f;
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
                    break;
                }
            }
            if (*(char *)(self + 0xCB) != 5) {
                F(0xBC) += -0.1f;
            }
            Item_DecayVelocityScalar(self, 4.5f);
            break;
        }
        break;
    case 3:
        SpriteSlot_Container_Free(w->sub);
        w->sub = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    if (w->thrown != 0) {
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, F(0xC4));
        Matrix4_PreMultiplyRotZ(m, m, F(0xB4));
        Matrix4_PreMultiplyRotX(m, m, F(0xAC));
        Matrix4_PreMultiplyRotY(m, m, F(0xB0));
        Mtx44_Translate(m, m, *(Vec *)(self + 0xA0));
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    }
    SpriteSlot_TickAnim(self + 0x14);
    if (w->sub != 0) {
        JointByName_GetWorldPosition(w->sub + 0xA0, self + 0x14, base + 0x440);
        *(float *)(w->sub + 0xC4) = F(0xC4) * w->pace;
        *(float *)(w->sub + 0x2C) = F(0x2C);
        w->sub[0x28] = self[0x28];
        SpriteSlot_SetTransform(w->sub + 0x14, *(Vec *)(w->sub + 0xA0), *(Vec *)(w->sub + 0xAC), *(float *)(w->sub + 0xC4));
    }
    Timer_Tick(&w->timers[0]);
    Timer_Tick(&w->timers[1]);
    Timer_Tick(&w->timers[2]);
    Timer_Tick(&w->timers[3]);
}

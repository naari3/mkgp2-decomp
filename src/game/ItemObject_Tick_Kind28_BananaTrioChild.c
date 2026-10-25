/* ItemObject_Tick_Kind28_BananaTrioChild (0x800E076C): one of the three
 * bananas orbiting a kart. I(0x10) picks the slot: it hides that banana's
 * joint and offsets the orbit start by 120 degrees per slot. It circles
 * the kart, faces it, and fades out once the driver's trio flag drops or
 * its 600-frame life ends. */
typedef struct Vec { float x, y, z; } Vec;

extern const char lbl_8032E060[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, Vec *pos, Vec *rot, float scale);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern float KartFxParam_GetConst1p5(void *driver);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Vec3_Scale(Vec *dst, const Vec *src, float scale);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern float Vec3_HorizontalYawTo(Vec *a, Vec *b);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define V(o) ((Vec *)(self + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_Tick_Kind28_BananaTrioChild(unsigned char *self)
{
    float root[4][4];
    Vec scaled;
    Vec kart;
    Vec local;
    Vec pos;
    Vec rot;
    const char *names = lbl_8032E060;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x28);
        switch (I(0x10)) {
        case 0:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x4F8, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x508, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x51C, 0x10, 1);
            break;
        case 1:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x4F8, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x508, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x51C, 0x10, 1);
            break;
        case 2:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x4F8, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x508, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x51C, 0x10, 0);
            break;
        }
        F(0x2C) = 0.0f;
        GetSpawnPosition(V(0x120), 0.0f, 3.0f, 5.0f);
        if (I(0x10) == 1) {
            Vec2_RotateY(V(0x120), V(0x120), 2.0943947f);
        }
        if (I(0x10) == 2) {
            Vec2_RotateY(V(0x120), V(0x120), 4.1887894f);
        }
        U32(0xF0) = 600;
        S8(0xC8) = 1;
    case 1:
        F(0xC4) = 2.0f * KartFxParam_GetConst1p5(P(0x184));
        Vec2_RotateY(V(0x120), V(0x120), 0.08726645f);
        if (P(0x184) != 0) {
            Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x184)));
            Vec3_Scale(&scaled, V(0x120), KartFxParam_GetConst1p5(P(0x184)));
            local = scaled;
            Mtx44_TransformVec3(V(0xA0), root, &local);
        }
        if (P(0x184) != 0) {
            Mtx44_GetTranslation_RowMajor(&kart, KartDriver_GetKartRootMtx(P(0x184)));
            F(0xB0) = Vec3_HorizontalYawTo(&kart, V(0xA0));
        }
        if (!(*(unsigned long long *)(*(unsigned char **)(P(0x184) + 0x304) + 0x10) & 0x20000000ULL)) {
            U32(0xF0) = 0;
        }
        if (U32(0xF0) != 0) {
            F(0x2C) += 0.1f;
            if (1.0f < F(0x2C)) {
                F(0x2C) = 1.0f;
            }
        } else {
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                SpriteSlot_Container_Free(self);
                return;
            }
        }
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    rot = *(Vec *)(self + 0xAC);
    pos = *(Vec *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, &pos, &rot, F(0xC4));
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

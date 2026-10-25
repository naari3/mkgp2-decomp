/* ItemObject_TickHornBlastShockwave (0x800DFF34): horn shockwave item.
 * Phase 0 shows the horn in the character's hand and fades it in, starting
 * the horn SE once it is triggered. Phase 1 grows the ring over the kart
 * (scaled by the Kinopio boost bonus) and hits drivers in range every 30
 * frames, then fades out. */
typedef struct Vec { float x, y, z; } Vec;
typedef struct { float v[3]; } FloatTriple;
typedef struct { unsigned char b[0x1EC]; } ItemObjectCopy;

extern const FloatTriple lbl_8032E540;
extern const FloatTriple lbl_8032E54C;
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_Container_Free(void *self);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void Item_RenderHandheldByCharacter(unsigned char *self, FloatTriple *a, FloatTriple *b, int c, float d);
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Item_PropagateHitToDriversInRadius(void *item, void *driver);
extern float KartCharacterParam_GetKinopioBoostBonus(void *driver);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_TickHornBlastShockwave(unsigned char *self)
{
    ItemObjectCopy hit;
    float root[4][4];
    float m[4][4];
    Vec pos;
    FloatTriple ofs;
    FloatTriple rot;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x2A);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        F(0x2C) = 0.0f;
        U32(0xF0) = 0;
        I(0x11C) = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
        S8(0xCA) = 0;
    case 1:
        switch (S8(0xC9)) {
        case 0:
            switch (S8(0xCA)) {
            case 0:
                F(0x2C) += 0.1f;
                if (1.0f < F(0x2C)) {
                    F(0x2C) = 1.0f;
                }
                if (self[0xEC] | (unsigned char)(S8(0x18C) == 1)) {
                    if (I(0x11C) == 0) {
                        pos = *(Vec *)(self + 0xA0);
                        SoundMgr_PlaySE_Positional(0xBF, &pos, 0);
                        I(0x11C) = 1;
                    }
                    S8(0xCA) = 1;
                }
                break;
            case 1:
                F(0x2C) -= 0.1f;
                if (F(0x2C) < 0.0f) {
                    F(0x2C) = 0.0f;
                    if (self[0xEC] != 0) {
                        S8(0xC9) = 1;
                        S8(0xCA) = 0;
                    } else {
                        if (I(0x11C) != 0) {
                            SoundMgr_StopSE_OrSpecial(0xBF, 0);
                            I(0x11C) = 0;
                        }
                        self[0x28] = 0;
                        ItemObject_DecrementCategoryBudget(self);
                        SpriteSlot_Container_Free(self);
                        return;
                    }
                }
                break;
            }
            rot = lbl_8032E54C;
            ofs = lbl_8032E540;
            Item_RenderHandheldByCharacter(self, &ofs, &rot, 0, 1.4f);
            break;
        case 1:
            switch (S8(0xCA)) {
            case 0:
                F(0x2C) += 0.1f;
                if (1.0f < F(0x2C)) {
                    F(0x2C) = 1.0f;
                }
                if (U32(0xF0) == 0) {
                    memcpy(&hit, self, sizeof(ItemObjectCopy));
                    *(int *)(hit.b + 0x8) = 0x2A;
                    hit.b[0x1C] = 0x9B;
                    hit.b[0x1DC] = self[0x1DC];
                    Vec3_Copy((Vec *)(hit.b + 0xA0), (Vec *)(self + 0xA0));
                    *(float *)(hit.b + 0xC4) = 200.0f;
                    Item_PropagateHitToDriversInRadius(&hit, P(0x184));
                    U32(0xF0) = 30;
                }
                if (S8(0x18C)) {
                    S8(0xCA) = 1;
                }
                break;
            case 1:
                F(0x2C) -= 0.1f;
                if (F(0x2C) < 0.0f) {
                    if (I(0x11C) != 0) {
                        SoundMgr_StopSE_OrSpecial(0xBF, 0);
                        I(0x11C) = 0;
                    }
                    F(0x2C) = 0.0f;
                    self[0x28] = 0;
                    ItemObject_DecrementCategoryBudget(self);
                    SpriteSlot_Container_Free(self);
                    return;
                }
                break;
            }
            F(0xC4) = 1.5f * KartCharacterParam_GetKinopioBoostBonus(P(0x184));
            Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x184)));
            Matrix4_Identity(m);
            Matrix4_PreMultiplyRotY(m, m, 3.141592f);
            Matrix4_PreMultiplyTranslation(m, m, 0.0f, 8.0f, -8.0f);
            Matrix4_Multiply(root, m, root);
            Matrix4_Identity(m);
            Mtx44_Scale_Uniform(m, m, F(0xC4));
            Matrix4_Multiply(root, m, root);
            DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
            Mtx44_GetTranslation_RowMajor((Vec *)(self + 0xA0), self + 0x48);
            break;
        }
        if ((int)self[0x18C] == 2) {
            self[0x18C] = 0;
            if (I(0x11C) != 0) {
                SoundMgr_StopSE_OrSpecial(0xBF, 0);
                I(0x11C) = 0;
            }
            self[0x28] = 0;
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

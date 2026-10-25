/* ShellPilePiece_Tick (0x800DF56C): one shell fragment from a shell pile.
 * The model (per item kind at +0xEC) shows only this piece's joint. The
 * piece is flung outward and tumbles while dropping, rides along with the
 * owning kart's motion, and fades out after 30 frames. */
typedef struct Vec { float x, y, z; } Vec;

extern unsigned char lbl_8041EEC0[];
extern const float lbl_806D5B60;
extern const float lbl_806D5B64;
extern const float lbl_806D5B68;
extern const float lbl_806D5B6C;
extern const float lbl_806D5B70;
extern const float lbl_806D5B74;
extern const float lbl_806D5B78;
extern const float lbl_806D5B7C;
extern const float lbl_806D5B80;
extern const float lbl_806D5B84;
extern const float lbl_806D5B88;
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_Container_Free(void *self);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern float Vec3_ToYaw(const Vec *v);
extern void Vec3_Scale(Vec *dst, const Vec *src, float scale);
extern float FAbs_FloatAsDouble(float x);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *v);
extern void Vec3_Subtract_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);

#define F(o) (*(float *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define V(o) ((Vec *)(self + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ShellPilePiece_Tick(unsigned char *self)
{
    float m[4][4];
    Vec cur;
    Vec delta;
    Vec half;
    Vec t0;
    Vec t1;
    Vec t2;
    Vec t3;
    unsigned char *base = lbl_8041EEC0;
    unsigned char *cfg;
    int i;

    switch (*(signed char *)(self + 0xC8)) {
    case 0:
        switch (self[0xEC]) {
        case 0x37:
            cfg = base + 0x630;
            break;
        case 0x38:
            cfg = base + 0x97C;
            break;
        case 0x77:
            cfg = base + 0xCC8;
            break;
        case 0x41:
            cfg = base + 0x1014;
            break;
        case 0x43:
            cfg = base + 0x1468;
            break;
        case 0x44:
            cfg = base + 0x18BC;
            break;
        case 0x42:
            break;
        }
        SpriteSlot_InitNonLoop(self + 0x14, cfg[0]);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, (const char *)(cfg + 0x41), 0x10, 1);
        for (i = 0; i < *(signed char *)(cfg + 0x81); i++) {
            SpriteSlot_SetJointVisibilityByName(self + 0x14, *(char **)(cfg + 0x84) + i * 0x58, 0x10, 1);
        }
        SpriteSlot_SetJointVisibilityByName(self + 0x14, *(char **)(cfg + 0x84) + *(int *)(self + 0x10) * 0x58, 0x10, 0);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        Vec2_RotateY(V(0xB8), V(0xB8), lbl_806D5B60 * Rand_RangeFloat(lbl_806D5B64, lbl_806D5B68));
        F(0x100) = Vec3_Magnitude_Wrapper(V(0xB8));
        F(0x104) = Vec3_ToYaw(V(0xB8));
        Vec3_Scale(V(0xB8), V(0xB8), lbl_806D5B6C * Rand_RangeFloat(lbl_806D5B70, lbl_806D5B74));
        F(0xBC) = FAbs_FloatAsDouble(F(0xBC));
        U32(0xF0) = 30;
        if (P(0x188) != 0) {
            Mtx44_GetTranslation_RowMajor(V(0x120), KartDriver_GetKartRootMtx(P(0x188)));
        }
        self[0xC8]++;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x188))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    F(0xBC) = F(0xBC) - lbl_806D5B78 * F(0x100);
    if (U32(0xF0) == 0) {
        F(0x2C) = F(0x2C) - lbl_806D5B7C;
        if (F(0x2C) < lbl_806D5B80) {
            SpriteSlot_Container_Free(self);
            return;
        }
    }
    Mtx_TransposeToMtx44(m, self + 0x48);
    t0 = *V(0xB8);
    Mtx44_Translate(m, m, &t0);
    if (P(0x188) != 0) {
        Mtx44_GetTranslation_RowMajor(&cur, KartDriver_GetKartRootMtx(P(0x188)));
        Vec3_Subtract_DestFirst(&delta, &cur, V(0x120));
        t1 = delta;
        Mtx44_Translate(m, m, &t1);
        Vec3_Copy(V(0x120), &cur);
    }
    Mtx44_GetTranslation_ColMajor(V(0xA0), m);
    Vec3_Scale(&half, V(0xA0), lbl_806D5B84);
    t2 = half;
    Mtx44_Translate(m, m, &t2);
    Matrix4_PreMultiplyRotY(m, m, -F(0x104));
    Matrix4_PreMultiplyRotX(m, m, lbl_806D5B88 * F(0x100));
    Matrix4_PreMultiplyRotY(m, m, F(0x104));
    t3 = *V(0xA0);
    Mtx44_Translate(m, m, &t3);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

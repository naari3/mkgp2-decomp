/* ShellPile_Spawn (0x800DF974): breaks a shell-type item (kind at +0x8)
 * into its configured pieces (ShellPilePiece_Tick). Each piece starts at
 * its rest pose in the item's (or a named joint's) matrix and is flung away
 * from the item's center. Not used in game mode 2. */
typedef struct Vec { float x, y, z; } Vec;

extern unsigned char lbl_8041EEC0[];
extern int g_gameMode;
extern void JointByName_GetMatrix4x4Transposed(float dst[4][4], void *slot, const char *name);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(unsigned char *));
extern void ShellPilePiece_Tick(unsigned char *self);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *v);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Vec3_Subtract_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_ExplosionPiece_Update(unsigned char *self);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void Vec2_RotateX(Vec *out, const Vec *in, float angle);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);

void ShellPile_Spawn(unsigned char *item, unsigned char *owner)
{
    float root[4][4];
    float m[4][4];
    float scale[4][4];
    Vec center;
    Vec local;
    unsigned char *base = lbl_8041EEC0;
    unsigned char *cfg;
    unsigned char *e;
    int i;

    if (item == 0) {
        return;
    }
    if (g_gameMode == 2) {
        return;
    }
    switch (*(int *)(item + 0x8)) {
    case 0x37:
    case 0x38:
    case 0x41:
    case 0x43:
    case 0x44:
    case 0x77:
        break;
    default:
        return;
    }
    switch (*(int *)(item + 0x8)) {
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
    if (*(signed char *)(cfg + 0x82)) {
        JointByName_GetMatrix4x4Transposed(root, item + 0x14, (const char *)(cfg + 1));
    } else {
        Mtx_TransposeToMtx44(root, item + 0x48);
    }
    Mtx44_GetTranslation_ColMajor(&center, root);
    for (i = 0; i < *(signed char *)(cfg + 0x81); i++) {
        e = ItemObject_AllocFromPool(ShellPilePiece_Tick);
        if (e != 0) {
            e[0xEC] = *(int *)(item + 0x8);
            *(int *)(e + 0x10) = (unsigned char)i;
            Matrix4_Identity(m);
            Matrix4_PreMultiplyRotX(m, m, 0.017453289f * *(float *)(*(unsigned char **)(cfg + 0x84) + i * 0x58 + 0x4C));
            local = *(Vec *)(*(unsigned char **)(cfg + 0x84) + i * 0x58 + 0x40);
            Mtx44_Translate(m, m, &local);
            Matrix4_Multiply(m, m, root);
            Mtx44_GetTranslation_ColMajor((Vec *)(e + 0xA0), m);
            Matrix4_Identity(scale);
            Mtx44_Scale_Uniform(scale, scale, *(float *)(cfg + 0x88));
            Matrix4_Multiply(m, scale, m);
            DbgScene_CopyMatrix3x4Transpose(e + 0x48, m);
            Vec3_Subtract_DestFirst((Vec *)(e + 0xB8), (Vec *)(e + 0xA0), &center);
            *(float *)(e + 0xC4) = *(float *)(item + 0xC4);
            *(void **)(e + 0x188) = *(void **)(owner + 0x9C);
        }
    }
    for (i = 0; i < 0; i++) {
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), (Vec *)(item + 0xA0));
            GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f, Rand_RangeFloat(0.7f, 1.3f));
            Vec2_RotateX((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            e[0x190] = 0;
            e[0x191] = 3;
            e[0x192] = 0;
            *(void **)(e + 0x11C) = *(void **)(owner + 0x9C);
            GetSpawnPosition((Vec *)(e + 0x120), 1.0f, 1.0f, 1.0f);
            e[0x193] = 0;
        }
    }
}

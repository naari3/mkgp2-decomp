/* GabyouItem_BuildOrUpdateAttachTransform (0x800DBEF8): place the gabyou
 * (thumbtack) item on the kart's hand joint, scaled per character class, and
 * build its attach matrix. With no item it only builds the matrix into dst. */
typedef struct Vec { float x, y, z; } Vec;

extern unsigned char lbl_8032D9C8[];

extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(Vec *dst, void *mtx);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern float Mtx44_GetYawOfPosZ_Padded(void *mtx);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern void Matrix4_Copy(float dst[4][4], float src[4][4]);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float dst[4][4], float a[4][4], float b[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Vec3_Copy(void *dst, const void *src);
extern float FAbs_FloatAsDouble(float x);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetMatrix4x4Transposed(float dst[4][4], void *slot, const unsigned char *name);

#define F(o) (*(float *)(item + (o)))

static inline float Gabyou_HandHeight(unsigned char *kart)
{
    switch (*(unsigned int *)(kart + 0x1F8)) {
    case 0:
        return 0.5f;
    case 1:
        return 0.5f;
    case 2:
        return 0.5f;
    case 3:
        return 0.3f;
    case 4:
        return 0.3f;
    case 5:
        return 0.3f;
    case 6:
        return 0.5f;
    case 7:
        return 0.2f;
    case 8:
        return 0.5f;
    case 9:
        return 0.5f;
    case 10:
        return 0.5f;
    case 11:
        return 0.5f;
    case 12:
        return 0.5f;
    }
    return 0.0f;
}

static inline float Gabyou_ClassScale(unsigned char *kart)
{
    switch (*(unsigned int *)(kart + 0x1F8)) {
    case 0:
        return 1.0f;
    case 1:
        return 1.0f;
    case 2:
        return 1.0f;
    case 3:
        return 1.0f;
    case 4:
        return 1.0f;
    case 5:
        return 0.8f;
    case 6:
        return 1.0f;
    case 7:
        return 1.0f;
    case 8:
        return 1.0f;
    case 9:
        return 1.0f;
    case 10:
        return 1.0f;
    case 11:
        return 1.0f;
    case 12:
        return 1.0f;
    }
    return 0.0f;
}

void GabyouItem_BuildOrUpdateAttachTransform(float dst[4][4], unsigned char *item, unsigned char *kart)
{
    unsigned char *base = lbl_8032D9C8;
    float m[4][4];
    float root[4][4];
    float mtx[4][4];
    float sm[4][4];
    Vec pos;
    Vec rot;
    Vec rootPos;
    Vec handPos;
    float scale;
    float frame;
    float a;
    float b;
    float t;
    float x;

    pos = *(Vec *)(base + 0x414);
    if (kart != 0) {
        Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetJointByIdx(kart, 0xC));
        pos.y += Gabyou_HandHeight(kart);
    }
    rot = *(Vec *)(base + 0x420);
    if (kart != 0) {
        rot.y = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(kart));
    }
    scale = 1.0f;
    if (kart != 0) {
        scale = Gabyou_ClassScale(kart);
    }
    if (item == 0) {
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, scale);
        Matrix4_PreMultiplyRotY(m, m, rot.y);
        Mtx44_Translate(m, m, pos);
        Matrix4_Copy(dst, m);
        return;
    }
    F(0xC4) = scale;
    pos.y += -1.5f * F(0xC4);
    Vec3_Copy(item + 0xA0, &pos);
    Vec3_Copy(item + 0xAC, &rot);
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(kart));
    Mtx44_GetTranslation_ColMajor(&rootPos, root);
    Mtx44_GetTranslation_RowMajor(&handPos, KartDriver_GetJointByIdx(kart, 0xC));
    Matrix4_Copy(mtx, root);
    Matrix4_PreMultiplyTranslation(mtx, mtx, -rootPos.x, -rootPos.y, -rootPos.z);
    Mtx44_Translate(mtx, mtx, handPos);
    Matrix4_Identity(sm);
    Mtx44_Scale_Uniform(sm, sm, F(0xC4));
    Matrix4_PreMultiplyTranslation(sm, sm, 0.0f, Gabyou_HandHeight(kart), 0.0f);
    Matrix4_Multiply(mtx, sm, mtx);
    DbgScene_CopyMatrix3x4Transpose(item + 0x48, mtx);
    if (kart != 0) {
        frame = *(float *)(kart + 0x1E0);
        a = 78.0f * (frame / 60.0f);
        x = F(0x20);
        b = a;
        t = x;
        if (39.0f < a) {
            b = a - 39.0f;
        }
        if (39.0f < x) {
            t -= 39.0f;
        }
        if (FAbs_FloatAsDouble(10.0f - t) < 1.3f) {
            if (FAbs_FloatAsDouble(b - (1.3f + t)) < 1.3f) {
                SpriteSlot_SetAnimFrameAndApplyScale(item + 0x14, item[0x1D], a);
                SpriteSlot_SetScale(item + 0x14, 0.0f);
            } else {
                SpriteSlot_SetAnimFrameAndApplyScale(item + 0x14, item[0x1D], 10.0f);
                SpriteSlot_SetScale(item + 0x14, 0.0f);
            }
        } else {
            SpriteSlot_SetScale(item + 0x14, 1.3f);
        }
        F(0x100) = frame;
    }
    item[0x28] = 1;
    SpriteSlot_TickAnim(item + 0x14);
    item[0x28] = 0;
    JointByName_GetMatrix4x4Transposed(dst, item + 0x14, base + 0x678);
}

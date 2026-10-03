/* Item_RenderHandheldByCharacter, 0x800DA890..0x800DABBC.
 * Complete target/callee assembly reconstruction; Ghidra was unavailable.
 * Views name only observed fields, not complete Item/KartDriver classes.
 * NonMatching: 99.729065% text; the initial scale/blend FP allocation differs.
 * The two jump tables, extab and extabindex match the target exactly.
 */
typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Matrix4[4][4];
typedef float Matrix3x4[3][4];
typedef struct KartDriverCharacterView {
    char pad0[0x1F8];
    unsigned int characterId;
} KartDriverCharacterView;
typedef struct ItemHandheldRenderView {
    char pad0[0x2C];
    float blend;
    char pad30[0x18];
    Matrix3x4 matrix;
    char pad78[0x28];
    Vec3 position;
    char padAC[0x18];
    float scale;
    char padC8[0xBC];
    KartDriverCharacterView *driver;
} ItemHandheldRenderView;

extern Matrix3x4 *KartDriver_GetKartRootMtx(KartDriverCharacterView *);
extern Matrix3x4 *KartDriver_GetJointByIdx(KartDriverCharacterView *, int);
extern void Mtx_TransposeToMtx44(Matrix4 out, const Matrix3x4 in);
extern void Mtx44_GetTranslation_ColMajor(Vec3 *, const Matrix4);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, const Matrix3x4);
extern void Matrix4_Copy(Matrix4 out, const Matrix4 in);
extern void Matrix4_PreMultiplyTranslation(Matrix4 out, const Matrix4 in,
                                           float x, float y, float z);
extern void Mtx44_Translate(Matrix4 out, const Matrix4 in, const Vec3 *);
extern void Matrix4_Identity(Matrix4);
extern void Matrix4_PreMultiplyRotX(Matrix4 out, const Matrix4 in, float);
extern void Matrix4_PreMultiplyRotZ(Matrix4 out, const Matrix4 in, float);
extern void Matrix4_PreMultiplyRotY(Matrix4 out, const Matrix4 in, float);
extern void Matrix4_Multiply(Matrix4 out, const Matrix4 a, const Matrix4 b);
extern void Mtx44_Scale_Uniform(Matrix4 out, const Matrix4 in, float);
extern void DbgScene_CopyMatrix3x4Transpose(Matrix3x4 out, const Matrix4 in);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;
extern const float lbl_806D5ACC;
extern const float lbl_806D5ADC;
extern const float lbl_806D5AEC;
extern const float lbl_806D5AFC;
extern const float lbl_806D5B1C;
extern const float lbl_806D5B20;

void Item_RenderHandheldByCharacter(ItemHandheldRenderView *item,
                                   const Vec3 *offset, const Vec3 *rotation,
                                   int mode, float baseScale)
{
    Matrix4 root;
    Matrix4 work;
    Matrix4 local;
    Vec3 rootPosition;
    Vec3 jointPosition;
    Vec3 translation;
    float characterScale;
    float scale;
    float height;
    float renderScale;
    float blendLimit;
    float blendValue;

    if (item == 0) return;
    switch (item->driver->characterId) {
    case 0: characterScale = lbl_806D5AB8; break;
    case 1: characterScale = lbl_806D5AB8; break;
    case 2: characterScale = lbl_806D5AB8; break;
    case 3: characterScale = lbl_806D5AB8; break;
    case 4: characterScale = lbl_806D5AB8; break;
    case 5: characterScale = lbl_806D5AEC; break;
    case 6: characterScale = lbl_806D5AB8; break;
    case 7: characterScale = lbl_806D5AB8; break;
    case 8: characterScale = lbl_806D5AB8; break;
    case 9: characterScale = lbl_806D5AB8; break;
    case 10: characterScale = lbl_806D5AB8; break;
    case 11: characterScale = lbl_806D5AB8; break;
    case 12: characterScale = lbl_806D5AB8; break;
    default: characterScale = lbl_806D5AC8; break;
    }
    scale = baseScale * characterScale;
    switch (mode) {
    case 0: item->scale = scale; break;
    case 1:
        blendValue = item->blend;
        blendLimit = lbl_806D5AB8;
        item->blend = blendValue + lbl_806D5AFC;
        if (blendLimit < item->blend) item->blend = blendLimit;
        item->scale = scale;
        break;
    case 2:
        item->scale += scale / lbl_806D5ADC;
        if (scale < item->scale) item->scale = scale;
        break;
    }

    Mtx_TransposeToMtx44(root, *KartDriver_GetKartRootMtx(item->driver));
    Mtx44_GetTranslation_ColMajor(&rootPosition, root);
    Mtx44_GetTranslation_RowMajor(&jointPosition,
                                  *KartDriver_GetJointByIdx(item->driver, 12));
    Matrix4_Copy(work, root);
    Matrix4_PreMultiplyTranslation(work, work,
        -rootPosition.x, -rootPosition.y, -rootPosition.z);
    translation = jointPosition;
    Mtx44_Translate(work, work, &translation);
    Matrix4_Identity(local);
    Matrix4_PreMultiplyRotX(local, local, rotation->x);
    Matrix4_PreMultiplyRotZ(local, local, rotation->z);
    Matrix4_PreMultiplyRotY(local, local, rotation->y);
    switch (item->driver->characterId) {
    case 0: height = lbl_806D5ACC; break;
    case 1: height = lbl_806D5ACC; break;
    case 2: height = lbl_806D5ACC; break;
    case 3: height = lbl_806D5B1C; break;
    case 4: height = lbl_806D5B1C; break;
    case 5: height = lbl_806D5B1C; break;
    case 6: height = lbl_806D5ACC; break;
    case 7: height = lbl_806D5B20; break;
    case 8: height = lbl_806D5ACC; break;
    case 9: height = lbl_806D5ACC; break;
    case 10: height = lbl_806D5ACC; break;
    case 11: height = lbl_806D5ACC; break;
    case 12: height = lbl_806D5ACC; break;
    default: height = lbl_806D5AC8; break;
    }
    renderScale = item->scale;
    Matrix4_PreMultiplyTranslation(local, local,
        offset->x * renderScale, offset->y * renderScale + height,
        offset->z * renderScale);
    Matrix4_Multiply(work, local, work);
    Matrix4_Identity(local);
    Mtx44_Scale_Uniform(local, local, item->scale);
    Matrix4_Multiply(work, local, work);
    DbgScene_CopyMatrix3x4Transpose(item->matrix, work);
    Mtx44_GetTranslation_RowMajor(&item->position, item->matrix);
}

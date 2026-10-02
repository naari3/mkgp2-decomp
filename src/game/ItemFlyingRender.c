/* Item_RenderFlyingFromKart, .text [0x800DA63C, 0x800DA740).
 * Reconstructed from complete target/callee disassembly; Ghidra unavailable.
 * The attachment builder receives the forwarded object in r4 and driver in r5.
 * Matrix helpers use destination-first arguments, including the final product.
 * NonMatching draft: 260 bytes, 99.62%; only the blend clamp f1/f2 webs differ.
 * The empty mode-0 case is required for the original switch branch structure.
 * Declaring named clamp temporaries did not change those FP homes.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;
typedef float Matrix4[4][4];
typedef float Matrix3x4[3][4];

typedef struct ItemFlyingRenderView {
    char pad0[0x2C];
    float renderBlend;
    char pad30[0x18];
    Matrix3x4 renderMatrix;
    char pad78[0x28];
    Vec3 position;
    char padAC[0x18];
    float scale;
    char padC8[0xBC];
    void *driver;
} ItemFlyingRenderView;

extern void GabyouItem_BuildOrUpdateAttachTransform(Matrix4 out,
                                                    void *attachment,
                                                    void *driver);
extern void Matrix4_Identity(Matrix4 out);
extern void Mtx44_Scale_Uniform(Matrix4 out, const Matrix4 in, float scale);
extern void Matrix4_PreMultiplyRotY(Matrix4 out, const Matrix4 in, float yaw);
extern void Matrix4_PreMultiplyTranslation(Matrix4 out, const Matrix4 in,
                                            float x, float y, float z);
extern void Matrix4_Multiply(Matrix4 out, const Matrix4 a, const Matrix4 b);
extern void DbgScene_CopyMatrix3x4Transpose(Matrix3x4 out, const Matrix4 in);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const Matrix3x4 in);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;
extern const float lbl_806D5AFC;

void Item_RenderFlyingFromKart(ItemFlyingRenderView *item, void *attachment,
                               int mode, float height, float yaw, float scale)
{
    Matrix4 attachmentTransform;
    Matrix4 localTransform;

    if (item == 0) {
        return;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        item->renderBlend += lbl_806D5AFC;
        if (lbl_806D5AB8 < item->renderBlend) {
            item->renderBlend = lbl_806D5AB8;
        }
        break;
    }
    item->scale = scale;
    GabyouItem_BuildOrUpdateAttachTransform(attachmentTransform, attachment,
                                            item->driver);
    Matrix4_Identity(localTransform);
    Mtx44_Scale_Uniform(localTransform, localTransform, item->scale);
    Matrix4_PreMultiplyRotY(localTransform, localTransform, yaw);
    Matrix4_PreMultiplyTranslation(localTransform, localTransform,
                                   lbl_806D5AC8, height * item->scale,
                                   lbl_806D5AC8);
    Matrix4_Multiply(attachmentTransform, localTransform, attachmentTransform);
    DbgScene_CopyMatrix3x4Transpose(item->renderMatrix, attachmentTransform);
    Mtx44_GetTranslation_RowMajor(&item->position, item->renderMatrix);
}

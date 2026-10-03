/* Target/callee-disassembly views; Ghidra type information was unavailable.
 * NonMatching: 336-byte body, 92.78571%; switch, extab, and index are exact.
 * Remaining difference is scheduling of vector-copy loads, argument addresses,
 * and the scale store near +0xE4..+0xFC. Keep all thirteen switch arms separate.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;
typedef float Matrix3x4[3][4];

typedef struct KartDriverCharacterView {
    char pad0[0x1F8];
    unsigned int characterId;
} KartDriverCharacterView;

typedef struct ItemRenderStateView {
    char pad0[0x18];
    float blend;
    char pad1C[0x18];
    Matrix3x4 matrix;
} ItemRenderStateView;

typedef struct ItemCharacterRenderView {
    char pad0[0x14];
    ItemRenderStateView render;
    char pad78[0x28];
    Vec3 position;
    char padAC[0x18];
    float scale;
    char padC8[0xBC];
    KartDriverCharacterView *driver;
} ItemCharacterRenderView;

extern void KartDriver_BuildJoint12EulerTransform(ItemRenderStateView *render,
    KartDriverCharacterView *driver, const Vec3 *offset, const Vec3 *euler,
    float scale);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const Matrix3x4 matrix);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;
extern const float lbl_806D5AEC;
extern const float lbl_806D5AFC;

void Item_RenderCharacterScaledFromJoint12(ItemCharacterRenderView *item,
    Vec3 offset, Vec3 euler, int mode, float scale)
{
    Vec3 offsetCopy;
    Vec3 eulerCopy;
    float characterScale;

    if (item == 0) {
        return;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        item->render.blend += lbl_806D5AFC;
        if (1.0f < item->render.blend) {
            item->render.blend = 1.0f;
        }
        break;
    }

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
    item->scale = scale * characterScale;
    eulerCopy = euler;
    offsetCopy = offset;
    KartDriver_BuildJoint12EulerTransform(&item->render, item->driver,
                                         &offsetCopy, &eulerCopy, item->scale);
    Mtx44_GetTranslation_RowMajor(&item->position, item->render.matrix);
}

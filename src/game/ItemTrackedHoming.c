/* Yaw-relative approach, .text [0x800DB784, 0x800DB864).
 * Reconstructed from complete authoritative target and callee disassembly;
 * Ghidra was unavailable.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern float Vec3_ToYaw(const Vec3 *v);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const void *matrix);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern float Vec3_HorizontalYawTo(const Vec3 *from, const Vec3 *to);
extern float BuildOrientationFromYaw(float yaw);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float yaw);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern float lbl_806D5ACC;

void Item_ComputeYawRelativeApproach(Vec3 *out, void *kart,
                                    const Vec3 *position, const Vec3 *direction)
{
    Vec3 approach;
    Vec3 kartPosition;
    Vec3 relativePosition;
    float yaw;

    Vec3_Copy(&approach, direction);
    Vec3_Magnitude_Wrapper(&approach);
    yaw = Vec3_ToYaw(&approach);
    Mtx44_GetTranslation_RowMajor(&kartPosition, KartDriver_GetKartRootMtx(kart));
    Vec3_Subtract_DestFirst(&relativePosition, position, direction);
    Vec2_RotateY(&approach, &approach, BuildOrientationFromYaw(
        -yaw + Vec3_HorizontalYawTo(&kartPosition, &relativePosition)));
    Vec3_Scale(&approach, &approach, lbl_806D5ACC);
    Vec3_Copy(out, &approach);
}

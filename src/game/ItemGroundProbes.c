/* Ground-pitch probes, .text [0x800DBA00, 0x800DBD48).
 * Complete target/callee disassembly was used; Ghidra was unavailable.
 * These functions take a Vec3 origin, not an Item object. Each ground query
 * consumes a separate integer-copied position and writes the working probe Y.
 * The initial 0.0f pitch must be a literal to keep CW's f31 load/copy order;
 * the existing shared-pool pass maps it to lbl_806D5AC8. The fallback probe
 * reloads that pool value, and its subtraction reverses the first-hit order.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float yaw);
extern void Vec3_Add_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern signed char ItemObject_GetGroundTypeAt(Vec3 *position, float *groundY, int mode);
extern float Vec3_ToPitch(const Vec3 *v);
extern float lbl_806D5AC8;

float Item_ProbeLateralGroundPitch(const Vec3 *origin, float yaw,
                                  float distance, float heightAdjustment)
{
    Vec3 probe;
    Vec3 firstPosition;
    Vec3 secondPosition;
    float pitch = 0.0f;

    GetSpawnPosition(&probe, -distance, pitch, pitch);
    Vec2_RotateY(&probe, &probe, yaw);
    Vec3_Add_DestFirst(&probe, &probe, origin);
    firstPosition = probe;
    if (ItemObject_GetGroundTypeAt(&firstPosition, &probe.y, 0) != 0) {
        probe.y += heightAdjustment;
        Vec3_Subtract_DestFirst(&probe, &probe, origin);
        pitch = Vec3_ToPitch(&probe);
    } else {
        GetSpawnPosition(&probe, distance, lbl_806D5AC8, lbl_806D5AC8);
        Vec2_RotateY(&probe, &probe, yaw);
        Vec3_Add_DestFirst(&probe, &probe, origin);
        secondPosition = probe;
        if (ItemObject_GetGroundTypeAt(&secondPosition, &probe.y, 0) != 0) {
            probe.y += heightAdjustment;
            Vec3_Subtract_DestFirst(&probe, origin, &probe);
            pitch = Vec3_ToPitch(&probe);
        }
    }
    return pitch;
}

float Item_ProbeForwardGroundPitch(const Vec3 *origin, float yaw,
                                  float distance, float heightAdjustment)
{
    Vec3 probe;
    Vec3 firstPosition;
    Vec3 secondPosition;
    float pitch = 0.0f;

    GetSpawnPosition(&probe, pitch, pitch, distance);
    Vec2_RotateY(&probe, &probe, yaw);
    Vec3_Add_DestFirst(&probe, &probe, origin);
    firstPosition = probe;
    if (ItemObject_GetGroundTypeAt(&firstPosition, &probe.y, 0) != 0) {
        probe.y += heightAdjustment;
        Vec3_Subtract_DestFirst(&probe, &probe, origin);
        pitch = Vec3_ToPitch(&probe);
    } else {
        GetSpawnPosition(&probe, lbl_806D5AC8, lbl_806D5AC8, -distance);
        Vec2_RotateY(&probe, &probe, yaw);
        Vec3_Add_DestFirst(&probe, &probe, origin);
        secondPosition = probe;
        if (ItemObject_GetGroundTypeAt(&secondPosition, &probe.y, 0) != 0) {
            probe.y += heightAdjustment;
            Vec3_Subtract_DestFirst(&probe, origin, &probe);
            pitch = Vec3_ToPitch(&probe);
        }
    }
    return pitch;
}

/* Complete 432-byte C candidate for 0x800DBD48..0x800DBEF8, 98.14815%.
 * The caller converts Vec3_ToYaw's f1 result to float, although the callee
 * itself rounds to single precision. Keep the caller's double declaration.
 * Remaining mismatch: target stores original f1 to the reused firstHeight
 * slot before argument moves; CW stores rounded f0 after fneg. Three bounded
 * approaches left this spill unchanged. Disabled to preserve both exact
 * ground-pitch functions and their linked TU boundaries; no asm substitute.
 */
#if 0
extern double Vec3_ToYaw(const Vec3 *v);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern float lbl_806D5AB8;
extern float lbl_806D5B18;

void Item_BendVelocityByGroundProbe(Vec3 *out, const Vec3 *origin,
                                    float yaw, float length, float bendAngle)
{
    Vec3 probe;
    Vec3 firstPosition;
    Vec3 secondPosition;
    float firstHeight;
    float secondHeight;

    GetSpawnPosition(out, 0.0f, 0.0f, length);
    Vec2_RotateY(out, out, yaw);
    firstPosition = *origin;
    if (ItemObject_GetGroundTypeAt(&firstPosition, &firstHeight, 0) != 0) {
        GetSpawnPosition(&probe, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5B18);
        Vec2_RotateY(&probe, &probe, yaw);
        Vec3_Add_DestFirst(&probe, origin, &probe);
        secondPosition = probe;
        if (ItemObject_GetGroundTypeAt(&secondPosition, &secondHeight, 0) != 0) {
            firstHeight = origin->y - firstHeight;
            probe.y = secondHeight + firstHeight;
            Vec3_Subtract_DestFirst(out, &probe, origin);
            {
                float reciprocal = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(out);
                Vec3_Scale(out, out, length * reciprocal);
            }
        }
    }
    {
        double currentYaw = Vec3_ToYaw(out);
        firstHeight = currentYaw;
        Vec2_RotateY(out, out, -(float)currentYaw);
    }
    Vec2_RotateX(out, out, bendAngle);
    Vec2_RotateY(out, out, firstHeight);
}
#endif

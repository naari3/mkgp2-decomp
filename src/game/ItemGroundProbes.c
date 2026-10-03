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

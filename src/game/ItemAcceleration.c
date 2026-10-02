/* Item_AccelClampVelocity, .text [0x800DA118, 0x800DA1E4).
 * Reconstructed from complete target/callee disassembly; Ghidra unavailable.
 * GetSpawnPosition is a vector setter (out r3, x/y/z f1/f2/f3), not a getter.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ItemAccelerationView {
    char pad0[0xB0];
    float yaw;
    char padB4[4];
    Vec3 velocity;
} ItemAccelerationView;

extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float yaw);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;

void Item_AccelClampVelocity(ItemAccelerationView *item, float maxSpeed,
                             float increment)
{
    float speed;
    float nextSpeed;
    float inverseSpeed;

    if (item == 0) {
        return;
    }
    speed = Vec3_Magnitude_Wrapper(&item->velocity);
    nextSpeed = speed + increment;
    if (maxSpeed < nextSpeed) {
        nextSpeed = maxSpeed;
    }
    if (lbl_806D5AC8 < nextSpeed) {
        if (lbl_806D5AC8 < speed) {
            /* Keep the reciprocal separate to preserve fmuls operand order. */
            inverseSpeed = lbl_806D5AB8 / speed;
            Vec3_Scale(&item->velocity, &item->velocity,
                       inverseSpeed * nextSpeed);
        } else {
            GetSpawnPosition(&item->velocity, lbl_806D5AC8, lbl_806D5AC8,
                              nextSpeed);
            Vec2_RotateY(&item->velocity, &item->velocity, item->yaw);
        }
    } else {
        GetSpawnPosition(&item->velocity, lbl_806D5AC8, lbl_806D5AC8,
                          lbl_806D5AC8);
    }
}

/* Tracked homing state, .text [0x800DB864, 0x800DBA00).
 * NonMatching: bounded three-approach stop at 99.41747% real-C text match.
 * Remaining initial targetY/lowSpeed FP homes and product operand order differ.
 * Reconstructed from complete target/callee assembly (Ghidra unavailable).
 * Only observed fields are named; this is not a full Item class layout.
 */
typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct ItemTrackedHomingView {
    char pad0[0xA0];
    Vec3 position;
    char padAC[0x18];
    float scale;
    signed char state;
    char padC9[0x43];
    float gain;
} ItemTrackedHomingView;

extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern double FAbs_FloatAsDouble(float value);
extern float Vec3_HorizontalMagnitude(const Vec3 *v);
extern void Vec3_ScaleXZ(Vec3 *out, const Vec3 *in, float scale);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float yaw);
extern float lbl_806D5AB8;
extern float lbl_806D5ACC;
extern float lbl_806D5AD8;
extern float lbl_806D5ADC;
extern float lbl_806D5AE0;
extern float lbl_806D5B08;
extern float lbl_806D5B34;

int Item_AdvanceTrackedHomingState(ItemTrackedHomingView *item, Vec3 *velocity,
                                  float step)
{
    Vec3 position;
    float lowSpeed;
    float targetY;
    float highSpeed;
    float desiredSpeed;
    float currentSpeed;
    float nextSpeed;

    if (item == 0 || velocity == 0) {
        return 1;
    }
    Vec3_Copy(&position, &item->position);
    targetY = lbl_806D5AD8 * item->scale;
    lowSpeed = item->gain * (lbl_806D5ADC * item->scale);
    highSpeed = item->gain * (lbl_806D5AE0 * item->scale);
    if (FAbs_FloatAsDouble(targetY - velocity->y) < step) {
        velocity->y = targetY;
    } else if (velocity->y < targetY) {
        velocity->y += step;
    } else {
        velocity->y -= step;
    }
    desiredSpeed = velocity->y * ((highSpeed - lowSpeed) / targetY) + lowSpeed;
    currentSpeed = Vec3_HorizontalMagnitude(velocity);
    Vec3_ScaleXZ(velocity, velocity, lbl_806D5AB8 / currentSpeed);
    if (FAbs_FloatAsDouble(desiredSpeed - currentSpeed) < lbl_806D5ACC * step) {
        nextSpeed = desiredSpeed;
    } else if (currentSpeed < desiredSpeed) {
        nextSpeed = currentSpeed + lbl_806D5ACC * step;
    } else {
        nextSpeed = currentSpeed - lbl_806D5ACC * step;
    }
    Vec3_ScaleXZ(velocity, velocity, nextSpeed);
    Vec2_RotateY(velocity, velocity, lbl_806D5B08 * (lbl_806D5B34 * step));
    return item->state == 2;
}

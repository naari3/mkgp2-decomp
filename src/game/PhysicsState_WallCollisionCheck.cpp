/* Native candidate: 56.565422% text. Volatile matrix storage retains
 * per-iteration loads; matrix codegen and stack/register layout remain open. */
#include "game/PhysicsCollisionPrivate.h"

static inline float CollisionLength(float squared)
{
    if (squared > lbl_806DA42C) {
        double estimate = __frsqrte(squared);
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        volatile float rounded = squared * estimate;
        return rounded;
    }
    return squared;
}

extern "C" void PhysicsState_WallCollisionCheck(char *self)
{
    float hitPosition[3];
    float hitNormal[3];
    volatile float original[16];
    volatile float rotation[16];
    float product[16];
    PH_B(self, 0x138) = 0;
    if (Terrain_RaycastWall(self + 0x58, self + 0x4C, hitPosition, hitNormal)) {
        PH_F(self, 0x4C) = hitPosition[0];
        PH_F(self, 0x50) = hitPosition[1];
        PH_F(self, 0x54) = hitPosition[2];
    }
    for (int n = 0; n < 16; ++n) original[n] = ((float *)(self + 0xE4))[n];
    float yaw = PH_F(self, 0x84);
    for (int n = 0; n < 16; ++n) rotation[n] = lbl_806DA42C;
    rotation[15] = rotation[10] = rotation[5] = rotation[0] = lbl_806DA450;
    float cosine = (float)cos(yaw);
    float sine = (float)sin(yaw);
    rotation[0] = cosine;
    rotation[8] = sine;
    rotation[10] = cosine;
    rotation[2] = -sine;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            product[row * 4 + col] =
                ((rotation[row * 4] * original[col] + rotation[row * 4 + 1] * original[4 + col]) +
                 rotation[row * 4 + 2] * original[8 + col]) + rotation[row * 4 + 3] * original[12 + col];
        }
    }
    /* The inlined multiply copies its product without transposing it. */
    for (int n = 0; n < 16; ++n) rotation[n] = product[n];
    for (int n = 0; n < 16; ++n) original[n] = rotation[n];
    original[12] = PH_F(self, 0x4C);
    original[13] = PH_F(self, 0x50);
    original[14] = PH_F(self, 0x54);
    unsigned char applied = 0;
    for (int corner = 0; corner < 4; ++corner) {
        PhysicsCollisionVec endpoint;
        PhysicsCollisionVec scaled(lbl_803BDD28[corner]);
        PhysicsCollisionVec correction;
        PhysicsCollisionVec normal;
        scaled.x *= PH_F(self, 0x13C);
        scaled.y *= PH_F(self, 0x13C);
        scaled.z *= PH_F(self, 0x13C);
        endpoint.x = original[12] + (original[0] * scaled.x + scaled.y * original[4] + scaled.z * original[8]);
        endpoint.y = original[13] + (original[1] * scaled.x + scaled.y * original[5] + scaled.z * original[9]);
        endpoint.z = original[14] + (original[2] * scaled.x + scaled.y * original[6] + scaled.z * original[10]);
        if (Terrain_RaycastWall(self + 0x4C, &endpoint, &correction, &normal)) {
            correction.x -= endpoint.x;
            correction.y -= endpoint.y;
            correction.z -= endpoint.z;
            correction.y = lbl_806DA42C;
            PH_F(self, 0x4C) += correction.x;
            PH_F(self, 0x50) += correction.y;
            PH_F(self, 0x54) += correction.z;
            original[12] = PH_F(self, 0x4C);
            original[13] = PH_F(self, 0x50);
            original[14] = PH_F(self, 0x54);
            if (!applied) {
                float length = CollisionLength((correction.x * correction.x + correction.y * correction.y) + correction.z * correction.z);
                float force = length;
                if (lbl_806DA49C < length) force = lbl_806DA49C;
                if (corner < 2) force *= lbl_806DA4A0;
                else force *= lbl_806DA4A4;
                PhysicsCollisionVec push(normal);
                push.x *= force;
                push.y *= force;
                push.z *= force;
                PH_F(self, 0xD8) += push.x;
                PH_F(self, 0xDC) += push.y;
                PH_F(self, 0xE0) += push.z;
                applied = 1;
            }
            PH_B(self, 0x138) = 1;
        }
    }
}

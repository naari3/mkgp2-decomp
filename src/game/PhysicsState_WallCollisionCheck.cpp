/* Native candidate: 63.242992% text. Flat matrix copy construction and
 * in-place multiplication recover aggregate assignment. Remaining input-load
 * hoisting and FP save allocation differ from the target. */
#include "game/PhysicsCollisionPrivate.h"
#include "game/PhysicsWallMatrixPrivate.h"

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
    PH_B(self, 0x138) = 0;
    if (Terrain_RaycastWall(self + 0x58, self + 0x4C, hitPosition, hitNormal)) {
        PH_F(self, 0x4C) = hitPosition[0];
        PH_F(self, 0x50) = hitPosition[1];
        PH_F(self, 0x54) = hitPosition[2];
    }
    PhysicsWallMatrix original(*(PhysicsWallMatrix *)(self + 0xE4));
    original.applyYaw(PH_F(self, 0x84));
    original.m[12] = PH_F(self, 0x4C);
    original.m[13] = PH_F(self, 0x50);
    original.m[14] = PH_F(self, 0x54);
    unsigned char applied = 0;
    for (int corner = 0; corner < 4; ++corner) {
        PhysicsCollisionVec endpoint;
        PhysicsCollisionVec scaled(lbl_803BDD28[corner]);
        PhysicsCollisionVec correction;
        PhysicsCollisionVec normal;
        scaled.x *= PH_F(self, 0x13C);
        scaled.y *= PH_F(self, 0x13C);
        scaled.z *= PH_F(self, 0x13C);
        endpoint.x = original.m[12] + (original.m[0] * scaled.x + scaled.y * original.m[4] + scaled.z * original.m[8]);
        endpoint.y = original.m[13] + (original.m[1] * scaled.x + scaled.y * original.m[5] + scaled.z * original.m[9]);
        endpoint.z = original.m[14] + (original.m[2] * scaled.x + scaled.y * original.m[6] + scaled.z * original.m[10]);
        if (Terrain_RaycastWall(self + 0x4C, &endpoint, &correction, &normal)) {
            correction.x -= endpoint.x;
            correction.y -= endpoint.y;
            correction.z -= endpoint.z;
            correction.y = lbl_806DA42C;
            PH_F(self, 0x4C) += correction.x;
            PH_F(self, 0x50) += correction.y;
            PH_F(self, 0x54) += correction.z;
            original.m[12] = PH_F(self, 0x4C);
            original.m[13] = PH_F(self, 0x50);
            original.m[14] = PH_F(self, 0x54);
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

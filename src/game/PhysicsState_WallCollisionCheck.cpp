/* Native candidate. Literal zeroes allow normal common-subexpression handling
 * and preserve the target's function size without optimisation pragmas.
 * Rotation-pointer lifetime and vector-operation registers remain non-exact. */
#include "game/PhysicsCollisionPrivate.h"
#include "game/PhysicsWallMatrixPrivate.h"

static inline void CollisionLength(float &squared)
{
    if (squared > 0.0f) {
        double estimate = __frsqrte(squared);
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - squared * (estimate * estimate));
        volatile float rounded = squared * estimate;
        squared = rounded;
    }
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
    original.setTranslation(PH_F(self, 0x4C), PH_F(self, 0x50), PH_F(self, 0x54));
    PhysicsCollisionVec endpoint;
    PhysicsCollisionVec *ep = &endpoint;
    unsigned char applied = 0;
    for (int corner = 0; corner < 4; ++corner) {
        PhysicsCollisionVec scaled;
        scaled.z = lbl_803BDD28[corner].z;
        scaled.y = lbl_803BDD28[corner].y;
        scaled.x = lbl_803BDD28[corner].x;
        PhysicsCollisionVec correction;
        PhysicsCollisionVec normal;
        scaled.x *= PH_F(self, 0x13C);
        scaled.y *= PH_F(self, 0x13C);
        scaled.z *= PH_F(self, 0x13C);
        endpoint.x = original.m[12] + (original.m[0] * scaled.x + scaled.y * original.m[4] + scaled.z * original.m[8]);
        endpoint.y = original.m[13] + (original.m[1] * scaled.x + scaled.y * original.m[5] + scaled.z * original.m[9]);
        endpoint.z = original.m[14] + (scaled.x * original.m[2] + scaled.y * original.m[6] + scaled.z * original.m[10]);
        if (Terrain_RaycastWall(self + 0x4C, ep, &correction, &normal)) {
            correction.x -= endpoint.x;
            correction.y -= endpoint.y;
            correction.z -= endpoint.z;
            correction.y = 0.0f;
            PH_F(self, 0x4C) += correction.x;
            PH_F(self, 0x50) += correction.y;
            PH_F(self, 0x54) += correction.z;
            original.setTranslation(PH_F(self, 0x4C), PH_F(self, 0x50), PH_F(self, 0x54));
            if (!applied) {
                float xx = correction.x * correction.x;
                float yy = correction.y * correction.y;
                float zz = correction.z * correction.z;
                float length = zz + (xx + yy);
                CollisionLength(length);
                float force = length;
                if (lbl_806DA49C < length) force = lbl_806DA49C;
                if (corner < 2) force *= lbl_806DA4A0;
                else force *= lbl_806DA4A4;
                PhysicsCollisionVec push;
                push.x = normal.x;
                push.z = normal.z;
                push.y = normal.y;
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

/* Native candidate: only two vector-copy store pairs remain non-exact. */
#include "game/PhysicsCollisionPrivate.h"

static inline PhysicsCollisionVec *WallEndpoint(PhysicsCollisionVec &value) {
    PhysicsCollisionVec *result = &value;
    return result;
}

static inline float WallRowProduct(const float *row, const float *column) {
    float value = row[0] * column[0];
    value += row[1] * column[4];
    value += row[2] * column[8];
    value += row[3] * column[12];
    return value;
}

/* Indexed rows let identity initialization and multiplication share a base. */
struct WallCollisionMatrix {
    float m[4][4];
    WallCollisionMatrix() {}
    void setTranslation(float x, float y, float z) {
        m[3][0] = x;
        m[3][1] = y;
        m[3][2] = z;
    }
    WallCollisionMatrix(const WallCollisionMatrix &other) {
        for (int i = 0; i < 16; ++i) ((float *)m)[i] = ((const float *)other.m)[i];
    }
    void identity() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) m[i][j] = 0.0f;
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = lbl_806DA450;
    }
    WallCollisionMatrix &operator*=(const WallCollisionMatrix &b) {
        WallCollisionMatrix result;
        const float *column;
        float *output = result.m[0];
        const float *right = b.m[0];
        int n = 0;
        for (int i = 0; i < 4; i++) {
            column = right;
            for (int j = 0; j < 4; j++, column++) {
                float value = WallRowProduct(m[i], column);
                output[n + j] = value;
            }
            n += 4;
        }
        for (int i = 0; i < 16; i++) ((float *)m)[i] = ((float *)result.m)[i];
        return *this;
    }
    WallCollisionMatrix(float yaw) {
        identity();
        float cosine = (float)cos(yaw);
        float sine = (float)sin(yaw);
        m[0][0] = cosine;
        m[2][0] = sine;
        m[2][2] = cosine;
        m[0][2] = -sine;
    }
    void applyYaw(float yaw) {
        WallCollisionMatrix rotation(yaw);
        rotation *= *this;
        *this = rotation;
    }
};

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
    WallCollisionMatrix original(*(WallCollisionMatrix *)(self + 0xE4));
    original.applyYaw(PH_F(self, 0x84));
    original.setTranslation(PH_F(self, 0x4C), PH_F(self, 0x50), PH_F(self, 0x54));
    PhysicsCollisionVec endpoint;
    PhysicsCollisionVec *ep = WallEndpoint(endpoint);
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
        endpoint.x = original.m[3][0] + (original.m[0][0] * scaled.x + scaled.y * original.m[1][0] + scaled.z * original.m[2][0]);
        endpoint.y = original.m[3][1] + (original.m[0][1] * scaled.x + scaled.y * original.m[1][1] + scaled.z * original.m[2][1]);
        endpoint.z = original.m[3][2] + (scaled.x * original.m[0][2] + scaled.y * original.m[1][2] + scaled.z * original.m[2][2]);
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

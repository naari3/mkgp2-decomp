/* Native candidate: 97.94372% text. Literal identity constants retain the
 * target FP save range and stack frame. Matrix operand scheduling and
 * register allocation remain unresolved; this TU stays NonMatching. */
#include "game/PhysicsGroundPrivate.h"

static inline void CopyGroundMatrix(PhysicsGroundMatrix &to, const PhysicsGroundMatrix &from)
{
    for (int i = 0; i < 16; ++i) ((float *)to.m)[i] = ((const float *)from.m)[i];
}

static inline void SetGroundTranslation(PhysicsGroundMatrix &matrix, float x, float y, float z)
{
    matrix.m[3][0] = x;
    matrix.m[3][1] = y;
    matrix.m[3][2] = z;
}

static inline void MultiplyGroundMatrix(PhysicsGroundMatrix &rotation,
                                        const PhysicsGroundMatrix &original)
{
    PhysicsGroundMatrix product;
    float value;
    int index = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            value = rotation.m[row][0] * original.m[0][col];
            value += rotation.m[row][1] * original.m[1][col];
            value += rotation.m[row][2] * original.m[2][col];
            value += rotation.m[row][3] * original.m[3][col];
            ((float *)product.m)[index + col] = value;
        }
        index += 4;
    }
    CopyGroundMatrix(rotation, product);
}

static inline void ApplyYaw(PhysicsGroundMatrix &original, float yaw)
{
    PhysicsGroundMatrix rotation;
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) rotation.m[row][col] = 0.0f;
    rotation.m[0][0] = rotation.m[1][1] = rotation.m[2][2] = rotation.m[3][3] = 1.0f;
    float cosine = (float)cos(yaw);
    float sine = (float)sin(yaw);
    rotation.m[0][0] = cosine;
    rotation.m[2][0] = sine;
    rotation.m[2][2] = cosine;
    rotation.m[0][2] = -sine;
    MultiplyGroundMatrix(rotation, original);
    original = rotation;
}

extern "C" void fn_801ED798(PhysicsGroundState *self, Vec3 *position,
                           PhysicsGroundMatrix *orientation, float yaw)
{
    self->aboveGround = 0;
    unsigned char wasAirborne = self->airborne;
    float airborneHeight = position->y;
    if (wasAirborne) {
        self->jumpFields[4] -= lbl_806DA4A8;
        airborneHeight += self->jumpFields[1] + self->jumpFields[4];
    }
    if (self->landingTimer > 0) --self->landingTimer;
    else self->landingTimer = 0;

    PhysicsGroundMatrix original;
    CopyGroundMatrix(original, *orientation);
    ApplyYaw(original, yaw);
    SetGroundTranslation(original, position->x, position->y, position->z);
    float penetration = lbl_806DA444 * self->scale;
    float fallbackPenetration = lbl_806DA428 * self->scale;
    for (int corner = 0; corner < 4; ++corner) {
        float height = 0.0f;
        CollisionVec scaled(lbl_803BDD28[corner].x, lbl_803BDD28[corner].y, lbl_803BDD28[corner].z);
        scaled.x *= self->scale;
        scaled.y *= self->scale;
        scaled.z *= self->scale;
        self->corners[corner].x = original.m[3][0] + (original.m[0][0] * scaled.x + scaled.y * original.m[1][0] + scaled.z * original.m[2][0]);
        self->corners[corner].y = original.m[3][1] + (original.m[0][1] * scaled.x + scaled.y * original.m[1][1] + scaled.z * original.m[2][1]);
        self->corners[corner].z = original.m[3][2] + (original.m[0][2] * scaled.x + scaled.y * original.m[1][2] + scaled.z * original.m[2][2]);
        Vec3 query = lbl_803BDE24;
        query.x = self->corners[corner].x;
        query.y = self->corners[corner].y;
        query.z = self->corners[corner].z;
        if (Terrain_GetGroundHeightWithPenetration(&query, &height, 0, 0, penetration)) {
            self->corners[corner].y = height;
        } else if (Terrain_GetGroundHeightWithPenetration(&query, &height, 0, 0, fallbackPenetration)) {
            self->corners[corner].y = height;
        } else {
            self->corners[corner].y = 0.0f;
        }
    }
    float packed[12];
    float frame[9];
    float groundHeight;
    for (int i = 0; i < 4; ++i) {
        int order = i ^ 1;
        packed[i * 3] = self->corners[order].x;
        packed[i * 3 + 1] = self->corners[order].y;
        packed[i * 3 + 2] = self->corners[order].z;
    }
    QuadFrame_FromPackedCorners(packed, frame, &groundHeight);
    orientation->m[0][0] = frame[0];
    orientation->m[0][1] = frame[1];
    orientation->m[0][2] = frame[2];
    orientation->m[1][0] = frame[3];
    orientation->m[1][1] = frame[4];
    orientation->m[1][2] = frame[5];
    orientation->m[2][0] = frame[6];
    orientation->m[2][1] = frame[7];
    orientation->m[2][2] = frame[8];
    Mtx34_Orthonormalize(orientation);
    if (wasAirborne) {
        if (airborneHeight <= groundHeight) {
            self->airborne = 0;
            for (int i = 0; i < 6; ++i) self->jumpFields[i] = 0.0f;
            self->landingTimer = 20;
            position->y = groundHeight;
        } else {
            position->y = airborneHeight;
        }
        self->fallingVelocity = 0.0f;
    } else {
        self->fallingVelocity += lbl_806DA4AC;
        position->y += self->fallingVelocity;
        if (position->y - lbl_806DA43C < groundHeight) {
            self->fallingVelocity = (groundHeight - self->previous.y) - lbl_806DA43C;
            if (0.0f < self->fallingVelocity) self->fallingVelocity = 0.0f;
            position->y = groundHeight;
        } else {
            self->aboveGround = 1;
        }
    }
}

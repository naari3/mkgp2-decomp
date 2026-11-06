/* Native candidate. Cleanup targets and local object offsets agree;
 * FP scheduling, flag tests and EH PC intervals still differ. */
#include "game/PhysicsCollisionPrivate.h"

static inline float WrapHitRadians(float yaw)
{
    while (lbl_806DA488 <= yaw) yaw -= lbl_806DA484;
    while (yaw < lbl_806DA48C) yaw += lbl_806DA484;
    return yaw;
}

static inline float WrapHitDegrees(float yaw)
{
    while (yaw >= lbl_806DA494) yaw -= lbl_806DA494;
    while (yaw < lbl_806DA42C) yaw += lbl_806DA494;
    return yaw;
}

static inline float RelativeHitYaw(float yaw, float heading)
{
    return WrapHitDegrees(lbl_806DA490 * WrapHitRadians(yaw - heading));
}

/* Native candidate. The flag words are a big-endian 64-bit mask. */
extern "C" int PhysicsState_KartCollisionCheck(char *self)
{
    PH_I(self, 0x128) = 0;
    char *strings = lbl_803BD920;
    unsigned char hit = 0;
    void *collision = PH_P(self, 0x124);
    PhysicsCollisionVec direction;
    float centerX, centerY, centerZ;
    float penetration = lbl_806DA42C;
    if (collision && PH_B(collision, 0)) {
        hit = 1;
        PH_P(self, 0x128) = KartController_GetRenderObj(Read_U32[PH_I(PH_P(collision, 4), 0x2C)]);
        void *other = PH_P(collision, 4);
        direction.set(PH_F(collision, 0xC), PH_F(collision, 0x10), PH_F(collision, 0x14));
        centerX = PH_F(other, 0x4C);
        centerY = PH_F(other, 0x50);
        centerZ = PH_F(other, 0x54);
        penetration = PH_F(collision, 8);
    }
    if (!hit && g_objCollChecker) {
        for (int slot = 0; slot < 4; ++slot) {
            PhysicsCollisionCar *car = GetPlayerCarBySlot(slot);
            if (car) {
                float *matrix = CarObject_GetTransformMatrix(car);
                float rotationMatrix[12];
                float rotation[4];
                Mtx4x4_TransposeTo4x3(matrix, rotationMatrix);
                HSD_MtxGetRotation(rotationMatrix, rotation);
                PhysicsPlainVec angles = *(PhysicsPlainVec *)(strings + 0x510);
                PhysicsPlainVec position = *(PhysicsPlainVec *)(strings + 0x51C);
                angles.set(lbl_806DA470 * rotation[0], lbl_806DA470 * rotation[1], lbl_806DA470 * rotation[2]);
                position.x = matrix[12];
                position.y = matrix[13];
                position.z = matrix[14];
                PhysicsCollisionShape shape(-1, 0);
                fn_802090F0(&shape, &position, &angles, lbl_806DA474, lbl_806DA478, lbl_806DA444);
                if (lbl_806DA42C < CollisionTest_CalcPenetration(g_objCollChecker, &shape, PH_P(self, 0x124))) {
                    hit = 1;
                    PhysicsPlainVec previous;
                    previous.set(PH_F(self, 0x58), PH_F(self, 0x5C), PH_F(self, 0x60));
                    PhysicsPlainVec otherPosition;
                    PhysicsPlainVec delta;
                    otherPosition.set(matrix[12], matrix[13], matrix[14]);
                    PH_P(self, 0x128) = CarObject_GetRenderObj(car);
                    centerX = matrix[12];
                    centerZ = matrix[14];
                    Vec3_Subtract(&previous, &otherPosition, &delta);
                    Vec3_Normalize(&delta, &delta);
                    direction.set(delta.x, delta.y, delta.z);
                    penetration = PH_F(strings, 0x3FC) * PH_F(self, 0x13C) + PH_F(strings, 0x3FC) - Vec3_Distance(&otherPosition, &previous);
                    car->OnKartHit(KartController_GetRenderObj(Read_U32[PH_I(self, 0x10)]));
                    break;
                }
            }
        }
    }
    if (!hit) return 0;
    void *render = PH_P(self, 8);
    void *effects = PH_P(render, 0x304);
    void *reaction = PH_P(self, 0xC);
    unsigned long long flags = *(unsigned long long *)((char *)effects + 0x10);
    unsigned char immune = 0;
    if ((flags & 0x10000000ULL) != 0) immune = 1;
    if (immune) return 1;
    void *otherEffects = PH_P(PH_P(self, 0x128), 0x304);
    if ((*(unsigned long long *)((char *)otherEffects + 0x10) & 0x80ULL) != 0 || (flags & 0x80ULL) != 0) return 0;
    fn_80057960(reaction, PH_F(self, 0x58), PH_F(self, 0x5C), PH_F(self, 0x60), centerX, centerY, centerZ, lbl_806DA450);
    if (!PH_B(self, 0x138)) {
        direction.x *= lbl_806DA47C;
        direction.y *= lbl_806DA47C;
        direction.z *= lbl_806DA47C;
        PH_F(self, 0xD8) += direction.x;
        PH_F(self, 0xDC) += direction.y;
        PH_F(self, 0xE0) += direction.z;
    }
    {
        PhysicsCollisionVec movement(PH_V(self, 0x4C));
        movement.x -= PH_F(self, 0x58);
        movement.y -= PH_F(self, 0x5C);
        movement.z -= PH_F(self, 0x60);
        movement.x *= lbl_806DA450;
        movement.y *= lbl_806DA450;
        movement.z *= lbl_806DA450;
        PH_F(self, 0x4C) = PH_F(self, 0x58) + movement.x;
        PH_F(self, 0x50) = PH_F(self, 0x5C) + movement.y;
        PH_F(self, 0x54) = PH_F(self, 0x60) + movement.z;
        if (penetration >= lbl_806DA480) {
            float yaw = RelativeHitYaw((float)atan2(PH_F(self, 0x58) - centerX, PH_F(self, 0x60) - centerZ), PH_F(self, 0x84));
            if (yaw > lbl_806DA498 && yaw < lbl_806DA494) KartReaction_Front(render);
            else if (yaw > lbl_806DA42C && yaw < lbl_806DA498) KartReaction_Side(render);
            else KartReaction_Rear(render);
        }
    }
    return 1;
}

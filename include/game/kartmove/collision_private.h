#ifndef KART_COLLISION_PRIVATE_H
#define KART_COLLISION_PRIVATE_H
#include "game/kartmove/speed_private.h"
/* Vec3 is the public storage type. These temporaries have the original
 * nontrivial lifetime, whose empty destructor is also used by terrain code. */
struct CollisionVec {
    float x, y, z;
    CollisionVec() {}
    CollisionVec(float px, float py, float pz) : x(px), y(py), z(pz) {}
    ~CollisionVec() {}
};
struct KartCollisionParams {
    unsigned char pad0[0x90];
    Vec3 probes[4];
};
struct KartCollisionSpeed {
    float unknown0, unknown4, maxSpeed;
    unsigned char padC[0x18-0xC];
};
struct KartCollisionState {
    unsigned char pad0[4];
    KartCollisionParams *params;
    int speedClass;
    float speed;
    unsigned char pad10[0x24-0x10];
    KartCollisionSpeed *speedTable;
    float unknown28;
    float wallDamping;
    unsigned char pad30[0x40-0x30];
    Vec3 pos, prevPos;
    float matrix[16];
    unsigned char pad98[0x17c-0x98];
    Vec3 velocity;
    unsigned char pad188[0x194-0x188];
    Vec3 acceleration;
    unsigned char pad1A0[0x1ac-0x1a0];
    Vec3 angularVelocity;
    unsigned char pad1B8[0x1c4-0x1b8];
    float steering, yaw;
    unsigned char pad1CC[0x1e0-0x1cc];
    float groundSpeed;
    unsigned char pad1E4[0x244-0x1e4];
    unsigned char hit, frontHit, rearHit, unknown247;
    int hitTimer;
    unsigned char pad24C[0x254-0x24c];
    unsigned char grounded[4];
    unsigned char pad258[0x298-0x258];
    Vec3 jumpOrigin;
    float unknown2A4, jumpTimer, unknown2AC;
    Vec3 jumpNormal;
    unsigned char jumping;
    unsigned char pad2BD[0x300-0x2bd];
    float scale;
    Vec3 wallPoint;
};
extern "C" {
unsigned char Terrain_RaycastWall(const void*, const void*, void*, void*);
unsigned char Terrain_GetGroundHeightWithPenetration(const void*, float*, void*, void*, float);
float Saturate_Double(float, float, float);
double cos(double);
double sin(double);
extern const float lbl_806D9700, lbl_806D9704;
extern const float lbl_806D9718, lbl_806D971C, lbl_806D9720, lbl_806D9724;
extern const float lbl_806D9728, lbl_806D972C, lbl_806D9730, lbl_806D9734, lbl_806D9738;
extern const double lbl_806D96F0;
}
#endif

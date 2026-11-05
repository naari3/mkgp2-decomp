#ifndef GAME_KARTITEM_REAR_TARGET_PRIVATE_H
#define GAME_KARTITEM_REAR_TARGET_PRIVATE_H
#include "game/KartMovement.h"
struct RearTargetFlags { char pad[0x10]; unsigned long long bits; };
struct RearTargetKart { char pad[0x304]; RearTargetFlags *flags; };
struct RearTargetOwner { char pad[8]; RearTargetKart *kart; };
struct RearTargetResult { RearTargetKart *kart; float distance; int side; };
extern "C" {
float *KartDriver_GetKartRootMtx(RearTargetKart *);
void KartDriver_GetJointPosition(RearTargetKart *, int, Vec3 *);
float Vec3_Magnitude(Vec3 *);
void Vec3_Normalize(Vec3 *, Vec3 *);
float Vec3_Dot(Vec3 *, Vec3 *);
void SetAnimWallHitA(RearTargetKart *);
void SetAnimWallHitB(RearTargetKart *);
extern const float lbl_806D2F40, lbl_806D2F44, lbl_806D2F48;
}
#endif

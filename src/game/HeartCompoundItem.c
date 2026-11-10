/*
 * HeartCompoundItem @ 0x800F2620..0x800F2D60.
 *
 * Held "heart" compound item. Update drives a three-state machine
 * (spawn / active / release); while active it alternates between the carry
 * phase (item orbits above the holder's kart) and the release phase (glow
 * effects on every other kart holding an item, then the item drifts away).
 * `st` is the per-item state block at self + 0xEC.
 */

#include "game/types/Vec3.h"

typedef float Mtx44[4][4];
typedef float Mtx34[3][4];

extern float BuildOrientationFromYaw(float yaw);
extern char *DrawEffect_SpawnDirect(void (*fn)(char *));
extern void Effect_CompoundRing_PlaceChildren(char *ring, Mtx34 *m, float yaw, float scale, float alpha);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern double sin(double x);
extern void *GetRaceContextPtr(void);
extern void Item_DecayVelocityScalar(char *item, float k);
extern void Item_RenderHandheldByCharacter(char *item, Vec3 ofs, Vec3 rot, int flag, float scale);
extern void ItemObject_DispatchVtable18_GetState(void *kart);
extern void JointByName_GetLocalMatrix4x3(Mtx34 *out, void *slot, const char *name);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern int KartMovement_GetCurrentItemId(void *kart);
extern void Mtx_TransposeToMtx44(Mtx44 *dst, void *src);
extern float Mtx44_GetYawOfPosZ(Mtx44 *m);
extern float Mtx44_GetYawOfPosZ_Padded(void *m);
extern void Mtx44_Inverse_GaussJordan(Mtx44 *dst, Mtx44 *src);
extern void Mtx44_TransformVec3(void *out, Mtx44 m, Vec3 v);
extern int *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void SpriteSlot_Container_Free(char *item);
extern void SpriteSlot_InitNonLoop(void *slot, unsigned char id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void SpriteSlot_SetTransform(void *slot, Vec3 pos, Vec3 rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void Effect_KartAuraCompound_Update(char *self);
extern void Effect_KartGlow_Update(char *self);

extern const char lbl_8032F580[];
extern Vec3 HeartCompoundItem_TickCarryPhase_data_804216F8;
extern Vec3 HeartCompoundItem_TickCarryPhase_data_80421704;
extern int HeartCompoundItem_Update_data_806CF3C8;
extern float HeartCompoundItem_TickCarryPhase_data_806CF3CC;
extern float HeartCompoundItem_TickCarryPhase_data_806CF3D0;
extern float HeartCompoundItem_TickCarryPhase_data_806CF3D4;
extern float HeartCompoundItem_TickCarryPhase_data_806CF3D8;
extern const float lbl_806D6060;
extern const float lbl_806D6064;
extern const float lbl_806D6068;
extern const float lbl_806D606C;
extern const float lbl_806D6070;
extern const float lbl_806D6074;
extern const float lbl_806D6080;
extern const float lbl_806D6084;

extern const double lbl_806D6078;

#pragma exceptions on
#pragma use_lmw_stmw on

void HeartCompoundItem_TickReleasePhase(char *self, char *st) {
    Mtx44 m;
    int i;
    int *slot;
    void *kart;
    char *eff;

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        *(float *)(self + 0xBC) = lbl_806D6060;
        *(float *)(st + 0x14) = lbl_806D6060;
        *(float *)(st + 0x18) = lbl_806D6060;
        *(unsigned int *)(st + 0x4) = 10;
        *(unsigned int *)(st + 0x8) = 20;
        if (*(char **)(st + 0x4C) != 0) {
            *(signed char *)(*(char **)(st + 0x4C) + 0x190) = 1;
        }
        for (i = 0; i < 0x80; i++) {
            slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
            if (slot != 0 && ((unsigned int)slot[0] <= 3 || slot[0] == 6)) {
                kart = *(void **)(slot + 0xB4 / 4);
                if (*(void **)(st + 0x98) != kart && KartMovement_GetCurrentItemId(kart) != -1) {
                    int j;

                    for (j = 0; j < 6; j++) {
                        eff = DrawEffect_SpawnDirect(Effect_KartGlow_Update);
                        *(float *)(eff + 0x150) = lbl_806D6064 * j;
                        *(int *)(eff + 0x180) = 0x28;
                        *(void **)(eff + 0x11C) = kart;
                    }
                }
            }
        }
        (*(signed char *)(self + 0xCA))++;
    case 1:
        if (*(unsigned int *)(st + 0x8) == 0) {
            for (i = 0; i < 0x80; i++) {
                slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
                if (slot != 0 && ((unsigned int)slot[0] <= 3 || slot[0] == 6)) {
                    void *other = *(void **)(slot + 0xB4 / 4);

                    if (*(void **)(st + 0x98) != other && KartMovement_GetCurrentItemId(other) != -1) {
                        ItemObject_DispatchVtable18_GetState(other);
                    }
                }
            }
            (*(signed char *)(self + 0xCA))++;
        }
        break;
    case 2:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(st + 0x98))) {
        *(signed char *)(self + 0x28) = 0;
    } else {
        *(signed char *)(self + 0x28) = 1;
    }
    if (*(unsigned int *)(st + 0x4) == 0) {
        *(float *)(self + 0xBC) += lbl_806D6068;
    }
    *(float *)(st + 0x14) += *(float *)(self + 0xBC);
    *(float *)(st + 0x18) += lbl_806D606C;
    if (*(unsigned int *)(st + 0x8) == 0) {
        *(float *)(self + 0x2C) -= lbl_806D6070;
        if (*(float *)(self + 0x2C) < lbl_806D6060) {
            *(signed char *)(self + 0x28) = 0;
            *(signed char *)(self + 0xC8) = 3;
            *(signed char *)(self + 0xC9) = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(self, lbl_806D6074);
    if (*(void **)(st + 0x98) != 0) {
        Mtx_TransposeToMtx44(&m, KartDriver_GetKartRootMtx(*(void **)(st + 0x98)));
        Mtx44_TransformVec3(self + 0xA0, m, *(Vec3 *)(st + 0x34));
        *(float *)(self + 0xA4) += *(float *)(st + 0x14);
        *(float *)(self + 0xB0) = BuildOrientationFromYaw(*(float *)(st + 0x18) + Mtx44_GetYawOfPosZ(&m));
    }
}

#pragma use_lmw_stmw reset


void HeartCompoundItem_TickCarryPhase(char *self, char *st) {
    Mtx44 m;
    Vec3 rot;
    Vec3 ofs;
    double s;

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(signed char *)(self + 0x28) = 1;
        *(float *)(self + 0x2C) = lbl_806D6060;
        *(float *)(st + 0x14) = lbl_806D6060;
        (*(signed char *)(self + 0xCA))++;
    case 1:
        *(float *)(st + 0x14) = BuildOrientationFromYaw(*(float *)(st + 0x14) + HeartCompoundItem_TickCarryPhase_data_806CF3D0);
        rot.x = HeartCompoundItem_TickCarryPhase_data_80421704.x;
        rot.y = HeartCompoundItem_TickCarryPhase_data_80421704.y;
        rot.z = HeartCompoundItem_TickCarryPhase_data_806CF3D4 * (float)sin(*(float *)(st + 0x14)) + HeartCompoundItem_TickCarryPhase_data_80421704.z;
        ofs.x = HeartCompoundItem_TickCarryPhase_data_804216F8.x;
        s = sin(lbl_806D6080 * *(float *)(st + 0x14));
        ofs.y = HeartCompoundItem_TickCarryPhase_data_804216F8.y + (HeartCompoundItem_TickCarryPhase_data_806CF3D8 * (float)s + HeartCompoundItem_TickCarryPhase_data_806CF3D8);
        ofs.z = HeartCompoundItem_TickCarryPhase_data_804216F8.z;
        Item_RenderHandheldByCharacter(self, ofs, rot, 1, HeartCompoundItem_TickCarryPhase_data_806CF3CC);
        *(float *)(self + 0xB0) = Mtx44_GetYawOfPosZ_Padded(self + 0x48);
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(st + 0x98))) {
            *(signed char *)(self + 0x28) = 0;
        } else {
            *(signed char *)(self + 0x28) = 1;
        }

        switch (*(signed char *)(st + 0xA0)) {
        case 1:
            *(signed char *)(st + 0xA0) = 0;
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
            *(float *)(self + 0x2C) = lbl_806D6084;
            if (*(void **)(st + 0x98) != 0) {
                Mtx_TransposeToMtx44(&m, KartDriver_GetKartRootMtx(*(void **)(st + 0x98)));
                Mtx44_Inverse_GaussJordan(&m, &m);
                Mtx44_TransformVec3(st + 0x34, m, *(Vec3 *)(self + 0xA0));
            }
            (*(signed char *)(self + 0xC9))++;
            *(signed char *)(self + 0xCA) = 0;
            break;
        case 2:
            *(signed char *)(st + 0xA0) = 0;
            *(signed char *)(self + 0x28) = 0;
            *(signed char *)(self + 0xC8) = 3;
            *(signed char *)(self + 0xC9) = 0;
            break;
        }
        break;
    }
}

void HeartCompoundItem_Update(char *self) {
    Mtx34 jm;
    char *st = self + 0xEC;

    switch (*(signed char *)(self + 0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, HeartCompoundItem_Update_data_806CF3C8);
        *(signed char *)(self + 0x14) = 4;
        *(char **)(st + 0x4C) = DrawEffect_SpawnDirect(Effect_KartAuraCompound_Update);
        *(signed char *)(self + 0xC8) = 1;
        *(signed char *)(self + 0xC9) = 0;
        *(signed char *)(self + 0xCA) = 0;
    case 1:
        switch (*(signed char *)(self + 0xC9)) {
        case 0:
            HeartCompoundItem_TickCarryPhase(self, st);
            break;
        case 1:
            HeartCompoundItem_TickReleasePhase(self, st);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        if (*(char **)(st + 0x4C) != 0) {
            *(signed char *)(*(char **)(st + 0x4C) + 0xC9) = 2;
        }
        *(char **)(st + 0x4C) = 0;
        *(signed char *)(*(char **)(st + 0x98) + 0x2B1) = 0;
        SpriteSlot_Container_Free(self);
        return;
    }

    SpriteSlot_SetTransform(self + 0x14, *(Vec3 *)(self + 0xA0), *(Vec3 *)(self + 0xAC),
                            *(float *)(self + 0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    if (*(char **)(st + 0x4C) != 0) {
        JointByName_GetLocalMatrix4x3(&jm, self + 0x14, lbl_8032F580);
        if (*(signed char *)(self + 0x28)) {
            Effect_CompoundRing_PlaceChildren(*(char **)(st + 0x4C), &jm, *(float *)(self + 0xB0),
                                              *(float *)(self + 0xC4), *(float *)(self + 0x2C));
        } else {
            Effect_CompoundRing_PlaceChildren(*(char **)(st + 0x4C), &jm, *(float *)(self + 0xB0),
                                              *(float *)(self + 0xC4), lbl_806D6060);
        }
    }
    if (*(unsigned int *)(st + 0x4) != 0) {
        (*(unsigned int *)(st + 0x4))--;
    }
    if (*(unsigned int *)(st + 0x8) != 0) {
        (*(unsigned int *)(st + 0x8))--;
    }
    if (*(unsigned int *)(st + 0xC) != 0) {
        (*(unsigned int *)(st + 0xC))--;
    }
    if (*(unsigned int *)(st + 0x10) != 0) {
        (*(unsigned int *)(st + 0x10))--;
    }
}

#pragma exceptions reset

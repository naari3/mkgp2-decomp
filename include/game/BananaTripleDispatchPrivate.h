#ifndef GAME_BANANATRIPLEDISPATCH_PRIVATE_H
#define GAME_BANANATRIPLEDISPATCH_PRIVATE_H

#include "game/objview/item_state_private.h"
typedef struct BananaState {
    unsigned char matrixEnabled, pad1[2], variant;
    unsigned int timer, timer8, timerC, timer10;
    float height, lift;
    unsigned char pad1c[0x34-0x1c];
    Vec3 delta;
    unsigned char pad40[12];
    Item *effect;
    unsigned char pad50[0x90-0x50];
    unsigned char active;
} BananaState;
extern unsigned char lbl_806CF3C0[6];
extern char BananaTriple_data_804211B0[][0xC0];
extern char lbl_8032F41C[];
extern void Effect_SparkSprayCompound_Update(void);
extern void *DrawEffect_SpawnDirect(void (*)(void));
extern void SpriteSlot_InitNonLoop(void *, int);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
extern void SpriteSlot_SetJointVisibilityByName(void *, char *, int, int);
extern void BananaTriple_Tick_HeldAndHoming_32to36(Item *, BananaState *);
extern void BananaTriple_StuckOnDriverTick_32to36(Item *, BananaState *);
extern void BananaTriple_OnImpactTick_32to36(Item *, BananaState *);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern int Item_AdvanceTetherToJoint13(Item *, float *, float, float, float);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Item_DecayVelocityScalar(Item *, float);
extern int Item_OrbitAnchorKart(Item *, Vec3 *, unsigned int, float, float);
extern void ItemObject_DecrementCategoryBudget(Item *);
extern void SpriteSlot_Container_Free(Item *);
extern void Matrix4_Identity(float [4][4]);
extern void Mtx44_Scale_Uniform(float [4][4], float [4][4], float);
extern void Matrix4_PreMultiplyRotX(float [4][4], float [4][4], float);
extern void Matrix4_PreMultiplyRotY(float [4][4], float [4][4], float);
extern void Matrix4_PreMultiplyRotZ(float [4][4], float [4][4], float);
#ifdef __MWERKS__
extern void Mtx44_Translate(float [4][4], float [4][4], Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float a0[4][4], float a1[4][4], Vec3 *);
static inline void Mtx44_Translate_ByValue(float a0[4][4], float a1[4][4], Vec3 a2) { Mtx44_Translate(a0, a1, &a2); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void DbgScene_CopyMatrix3x4Transpose(void *, float [4][4]);
extern void SpriteSlot_TickAnim(void *);
extern void JointByName_GetWorldPosition(Vec3 *, void *, char *);
#ifdef __MWERKS__
extern void Effect_SparkSpray_PlaceChildren(Item *, Vec3, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Effect_SparkSpray_PlaceChildren(Item *, Vec3 *, float, float);
static inline void Effect_SparkSpray_PlaceChildren_ByValue(Item *a0, Vec3 a1, float a2, float a3) { Effect_SparkSpray_PlaceChildren(a0, &a1, a2, a3); }
#define Effect_SparkSpray_PlaceChildren Effect_SparkSpray_PlaceChildren_ByValue
#endif

#endif

/* --- owned .data 0x8041A428..0x8041A494 (tools/own_data.py) --- */
#pragma force_active on
extern "C" float Effect_KartJoint12_3Stage_Update_data_8041A428[3][9] = { 0.0f, 2.0f, 4.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 4.0f, 5.5f, 7.0f, 1.0f, 1.5f, 2.0f, 1.0f, 0.5f, 0.0f };
#pragma force_active reset
extern "C" /* Target-observed local views; live Ghidra types were unavailable. */
#include "game/types/JointVec.h"
struct Joint12Effect;
struct Joint12Group {
 char pad00[0x10]; Joint12Effect *children[3]; char pad1C[0x34];
 void *kart; JointVec offset; char pad60[0x24]; float age;
};
struct Joint12Effect {
 char pad00[0x14]; char slot[0x18]; float alpha; char pad30[0x5C];
 JointVec position; char pad98[0x18]; float scale; signed char state;
 char padB5[0x17]; Joint12Group group;
};
extern "C" {
extern const float lbl_806D555C, lbl_806D5570, lbl_806D55D8, lbl_806D5584;
Joint12Effect *DrawEffect_SpawnDirect(void (*)(Joint12Effect *));
void fn_800AF4F8(Joint12Effect *);
void DrawEffect_Free(Joint12Effect *);
void VfxSlot_BindResourceEx(void *, int, int);
void *KartDriver_GetKartRootMtx(void *);
void Mtx_TransposeToMtx44(float (*)[4], const void *);
void Mtx44_TransformVec3(JointVec *, const float (*)[4], JointVec);
void Vec3_Copy(JointVec *, const JointVec *);
void VfxSlot_SetPositionFromVec(void *, JointVec);
void VfxSlot_SetScaleUniform(void *, float);
}
static inline float stageFraction(float start, float end, float age) {
 return (age - start) * (lbl_806D5584 / (end - start));
}
static inline float stageValue(float start, float end, float fraction) {
 return start + fraction * (end - start);
}
static inline void interpolate(Joint12Effect **child, float *row, float age) {
 if (row[0] <= age && age < row[1]) {
  float t = stageFraction(row[0], row[1], age);
  (*child)->scale = stageValue(row[3], row[4], t);
  (*child)->alpha = stageValue(row[6], row[7], t);
 }
}
static inline void updateChild(float *row, Joint12Group *group, Joint12Effect *effect, int i) {
 if (group->children[i]) {
  Vec3_Copy(&group->children[i]->position, &effect->position);
  if (row[0] <= group->age && group->age < row[2]) {
   for (int stage = 0; stage < 2; ++stage) {
    interpolate(&group->children[i], row + stage, group->age);
   }
  } else {
   group->children[i]->scale = lbl_806D555C;
   group->children[i]->alpha = lbl_806D555C;
  }
  VfxSlot_SetPositionFromVec(group->children[i]->slot, group->children[i]->position);
  VfxSlot_SetScaleUniform(group->children[i]->slot, group->children[i]->scale);
 }
}
extern "C" void Effect_KartJoint12_3Stage_Update(Joint12Effect *effect) {
 int i;
 Joint12Group *group = &effect->group;
 switch (effect->state) {
 case 0:
  for (i = 0; i < 3; ++i) {
   group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
   if (group->children[i]) {
    switch (i) {
    case 0: VfxSlot_BindResourceEx(group->children[i]->slot, 0x5C, 0); break;
    case 1: VfxSlot_BindResourceEx(group->children[i]->slot, 0x5D, 0); break;
    case 2: VfxSlot_BindResourceEx(group->children[i]->slot, 0x5E, 0); break;
    }
   }
  }
  group->age = lbl_806D555C;
  ++effect->state;
  break;
 case 1: break;
 }
 group->age += lbl_806D5570;
 if (lbl_806D55D8 < group->age) {
  DrawEffect_Free(group->children[0]); DrawEffect_Free(group->children[1]); DrawEffect_Free(group->children[2]);
  group->children[0] = 0; group->children[1] = 0; group->children[2] = 0;
  DrawEffect_Free(effect); return;
 }
 float matrix[4][4];
 Mtx_TransposeToMtx44(matrix, KartDriver_GetKartRootMtx(group->kart));
 Mtx44_TransformVec3(&effect->position, matrix, group->offset);
 for (i = 0; i < 3; ++i) {
  updateChild(Effect_KartJoint12_3Stage_Update_data_8041A428[i], group, effect, i);
 }
}

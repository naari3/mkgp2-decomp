/* Target-observed local views; live Ghidra types were unavailable. */
struct JointVec { float x, y, z; };
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
extern float lbl_8041A428[3][9];
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
static inline void interpolate(Joint12Effect **child, float *row, float age) {
 if (row[0] <= age && age < row[1]) {
  float t = lbl_806D5584 / (row[1] - row[0]);
  t = (age - row[0]) * t;
  (*child)->scale = row[3] + t * (row[4] - row[3]);
  (*child)->alpha = row[6] + t * (row[7] - row[6]);
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
  float *row = lbl_8041A428[i];
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
}

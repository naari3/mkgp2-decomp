// Three-child smoke ring. Views contain only fields observed in target code.
// Honest native draft: 556B, text 96.97122%; compiler-generated EH/index 100%.
// Remaining difference is the transient child pointer register and copy scheduling.
struct SmokeVec { float v[3]; };
struct SmokeEffect;
struct SmokeGroup {
    unsigned char pad00[0x10];
    SmokeEffect* child[3];
    unsigned char pad1C[0x68];
    float phase;
};
struct SmokeEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x78];
    SmokeVec position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    SmokeGroup group;
};
extern "C" {
extern const SmokeVec lbl_8032A730, lbl_8032A73C;
extern const float lbl_806D5478, lbl_806D5400, lbl_806D5498;
extern const float lbl_806D5450, lbl_806D5480;
void fn_800AF4F8(SmokeEffect*);
SmokeEffect* DrawEffect_SpawnDirect(void (*)(SmokeEffect*));
void DrawEffect_Free(SmokeEffect*);
void VfxSlot_BindResourceEx(void*, int, int);
void VfxSlot_SetScaleUniform(void*, float);
void VfxSlot_SetPositionFromVec(void*, SmokeVec);
float BuildOrientationFromYaw(float);
void GetSpawnPosition(SmokeVec*, float, float, float);
void Vec2_RotateY(SmokeVec*, const SmokeVec*, float);
void Vec2_RotateX(SmokeVec*, const SmokeVec*, float);
void Vec3_Add_DestFirst(SmokeVec*, const SmokeVec*, const SmokeVec*);

void Effect_SmokeRing3_Update(SmokeEffect* effect) {
    SmokeVec angles;
    SmokeVec tilts;
    SmokeGroup* group = &effect->group;
    int i;
    switch (effect->state) {
    case 0:
        for (i = 0; i < 3; ++i) {
            group->child[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->child[i]) {
                VfxSlot_BindResourceEx(group->child[i]->slot, 0x11, 0);
                group->child[i]->scale = lbl_806D5478;
                VfxSlot_SetScaleUniform(group->child[i]->slot, group->child[i]->scale);
            }
        }
        group->phase = lbl_806D5400;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->cleanup) {
        for (i = 0; i < 3; ++i) {
            DrawEffect_Free(group->child[i]);
            group->child[i] = 0;
        }
        DrawEffect_Free(effect);
        return;
    }
    group->phase = BuildOrientationFromYaw(lbl_806D5498 + group->phase);
    for (i = 0; i < 3; ++i) {
        SmokeEffect* child = group->child[i];
        if (child) {
            angles = lbl_8032A730;
            tilts = lbl_8032A73C;
            GetSpawnPosition(&child->position, lbl_806D5400, lbl_806D5400, lbl_806D5450);
            Vec2_RotateY(&group->child[i]->position, &group->child[i]->position, group->phase + angles.v[i]);
            Vec2_RotateX(&group->child[i]->position, &group->child[i]->position, tilts.v[i]);
            Vec3_Add_DestFirst(&group->child[i]->position, &effect->position, &group->child[i]->position);
            group->child[i]->position.v[1] += lbl_806D5480;
            VfxSlot_SetPositionFromVec(group->child[i]->slot, group->child[i]->position);
        }
    }
}
}

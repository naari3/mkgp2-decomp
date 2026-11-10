/* Narrow target-observed views; live Ghidra types were unavailable. */
struct RotateVec { float x, y, z; };
struct RotateChild {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float alpha;
    unsigned char pad30[0x5C];
    RotateVec position;
    unsigned char pad98[8];
    float rotationZ;
    unsigned char padA4[0xC];
    float scale;
};
struct RotateGroup {
    unsigned char pad00[0x10];
    RotateChild *children[2];
    unsigned char pad18[0x6C];
    float alpha;
    float phase;
    unsigned char pad8C[0x38];
    signed char enabled;
};
struct RotateEffect {
    unsigned char pad00[0xCC];
    RotateGroup group;
};
extern "C" {
void Vec3_Copy(RotateVec *, const RotateVec *);
#ifdef __MWERKS__
void VfxSlot_SetPositionFromVec(void *, RotateVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void *, RotateVec *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void *a0, RotateVec a1) { VfxSlot_SetPositionFromVec(a0, &a1); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_TwoChildRotate_FromPhase150(RotateEffect *effect, RotateVec *position, float scale, float alpha) {
    if (effect) {
        RotateGroup *group = &effect->group;
        if (group->enabled) {
            group->alpha += 0.05f;
            if (1.0f < group->alpha) group->alpha = 1.0f;
        } else {
            group->alpha -= 0.05f;
            if (group->alpha < 0.0f) group->alpha = 0.0f;
        }
        group->phase += 0.0033333334f;
        if (1.0f < group->phase) group->phase -= 1.0f;
        for (int i = 0; i < 2; ++i) {
            if (group->children[i]) {
                Vec3_Copy(&group->children[i]->position, position);
                if (i == 0) group->children[i]->rotationZ = -18.849552f * group->phase;
                else group->children[i]->rotationZ = -31.41592f * group->phase;
                group->children[i]->scale = scale;
                group->children[i]->alpha = group->alpha * alpha;
                group->children[i]->visible = 1;
                VfxSlot_SetPositionFromVec(group->children[i]->slot, group->children[i]->position);
                VfxSlot_SetRotationZ(group->children[i]->slot, group->children[i]->rotationZ);
                VfxSlot_SetScaleUniform(group->children[i]->slot, group->children[i]->scale);
            }
        }
    }
}
}


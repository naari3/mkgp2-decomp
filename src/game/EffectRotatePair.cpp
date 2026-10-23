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
};
struct RotateEffect {
    unsigned char pad00[0xCC];
    RotateGroup group;
    unsigned char pad158[0x38];
    signed char enabled;
};
extern "C" {
extern const float lbl_806D5794, lbl_806D5790, lbl_806D5770;
extern const float lbl_806D57CC, lbl_806D57D0, lbl_806D57D4;
void Vec3_Copy(RotateVec *, const RotateVec *);
void VfxSlot_SetPositionFromVec(void *, RotateVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_TwoChildRotate_FromPhase150(RotateEffect *effect, RotateVec *position, float scale, float alpha) {
    if (effect) {
        RotateGroup *group = &effect->group;
        if (effect->enabled) {
            group->alpha += lbl_806D5794;
            if (lbl_806D5790 < group->alpha) group->alpha = lbl_806D5790;
        } else {
            group->alpha -= lbl_806D5794;
            if (group->alpha < lbl_806D5770) group->alpha = lbl_806D5770;
        }
        group->phase += lbl_806D57CC;
        if (lbl_806D5790 < group->phase) group->phase -= lbl_806D5790;
        for (int i = 0; i < 2; ++i) {
            if (group->children[i]) {
                Vec3_Copy(&group->children[i]->position, position);
                if (i == 0) group->children[i]->rotationZ = lbl_806D57D0 * group->phase;
                else group->children[i]->rotationZ = lbl_806D57D4 * group->phase;
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


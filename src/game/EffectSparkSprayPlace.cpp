/* Target-observed local views; no live Ghidra type lookup was performed. */
struct SprayVec { float x, y, z; };
struct SprayEffect;
struct SprayGroup {
    unsigned char pad00[0x10];
    SprayEffect *children[8];
};
struct SprayEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float alpha;
    unsigned char pad30[0x5C];
    SprayVec position;
    unsigned char pad98[8];
    float rotation;
    unsigned char padA4[0xC];
    float scale;
    unsigned char padB4[0x15];
    signed char cleanup;
    unsigned char padCA[2];
    SprayGroup group;
    unsigned char padFC[0x24];
    SprayVec local;
    unsigned char pad12C[0x2C];
    float verticalOffset;
};
extern "C" {
void Vec3_Copy(SprayVec *, const SprayVec *);
void Vec3_Scale(SprayVec *, const SprayVec *, float);
void Vec3_Add_DestFirst(SprayVec *, const SprayVec *, const SprayVec *);
void VfxSlot_SetPositionFromVec(void *, SprayVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);

void Effect_SparkSpray_PlaceChildren(SprayEffect *effect, const SprayVec *position, float scale, float alpha) {
    if (effect) {
        Vec3_Copy(&effect->position, position);
        effect->scale = scale;
        SprayGroup *group = &effect->group;
        SprayEffect *child;
        effect->alpha = alpha;
        for (int i = 0; i < 8; ++i) {
            child = group->children[i];
            if (child) {
                SprayVec offset;
                Vec3_Scale(&offset, &child->local, scale);
                Vec3_Add_DestFirst(&child->position, position, &offset);
                child->position.y += child->verticalOffset;
                VfxSlot_SetPositionFromVec(child->slot, child->position);
                VfxSlot_SetRotationZ(child->slot, child->rotation);
                VfxSlot_SetScaleUniform(child->slot, child->scale);
                child->alpha = alpha;
                if (!group->children[i]->cleanup) child->visible = 1;
            }
        }
    }
}
}

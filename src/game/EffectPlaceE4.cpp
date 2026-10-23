/* Narrow target-observed layout; live Ghidra types unavailable. */
struct PlaceE4Vec { float x, y, z; };
struct PlaceE4Effect;
struct PlaceE4Group {
    char pad00[0x10];
    PlaceE4Effect *children[2];
    PlaceE4Effect *spray;
};
struct PlaceE4Effect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x5C];
    PlaceE4Vec position;
    char pad98[0x18];
    float scale;
    char padB4[0x18];
    PlaceE4Group group;
};
extern "C" {
extern const float lbl_806D57E8;
void Vec3_Copy(PlaceE4Vec *, const PlaceE4Vec *);
void VfxSlot_SetPositionFromVec(void *, PlaceE4Vec);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_SparkSpray_PlaceChildren(PlaceE4Effect *, PlaceE4Vec, float, float);
void Effect_TwoChildPlace_AndForward_E4(PlaceE4Effect *effect, const PlaceE4Vec *position, float scale, float alpha) {
    if (effect) {
        PlaceE4Group *group = &effect->group;
        Vec3_Copy(&effect->position, position);
        effect->scale = lbl_806D57E8 * scale;
        effect->alpha = alpha;
        for (int i = 0; i < 2; ++i) {
            if (group->children[i]) {
                Vec3_Copy(&group->children[i]->position, &effect->position);
                group->children[i]->scale = effect->scale;
                group->children[i]->alpha = effect->alpha;
                VfxSlot_SetPositionFromVec(group->children[i]->slot, group->children[i]->position);
                VfxSlot_SetScaleUniform(group->children[i]->slot, group->children[i]->scale);
                group->children[i]->visible = 1;
            }
        }
        Effect_SparkSpray_PlaceChildren(group->spray, *position, scale, alpha);
    }
}
}

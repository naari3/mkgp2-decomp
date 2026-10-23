/* Narrow target-observed layout; live Ghidra types were unavailable. */
struct Variant77Vec { float x, y, z; };
struct Variant77Effect {
    char pad00[0x10];
    int variant;
    char slot[0x18];
    float alpha;
    char pad30[0x5C];
    Variant77Vec position;
    char pad98[0x18];
    float scale;
    signed char state;
    char padB5[0x14];
    signed char fadeRequested;
    char padCA[0x86];
    float baseScale;
    float growth;
};
struct Variant77View { char pad00[0x80]; Variant77Vec position; char pad8C[0xC]; };
extern "C" {
extern Variant77View lbl_805DF3D0;
extern const float lbl_806D555C, lbl_806D55C0, lbl_806D5584;
extern const float lbl_806D55B4, lbl_806D5560, lbl_806D55C4, lbl_806D556C;
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetUVScroll(void *, float, float);
void Vec3_Subtract_DestFirst(Variant77Vec *, const Variant77Vec *, const Variant77Vec *);
float Vec3_Magnitude_Wrapper(const Variant77Vec *);
void Vec3_Scale(Variant77Vec *, const Variant77Vec *, float);
void Vec3_Add_DestFirst(Variant77Vec *, const Variant77Vec *, const Variant77Vec *);
void DrawEffect_Free(Variant77Effect *);
void VfxSlot_SetPositionFromVec(void *, Variant77Vec);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_Res77or78_Variant_Update(Variant77Effect *effect) {
    Variant77Vec direction;
    switch (effect->state) {
    case 0:
        if (effect->variant == 0) VfxSlot_BindResource(effect->slot, 0x77);
        else VfxSlot_BindResource(effect->slot, 0x78);
        VfxSlot_SetUVScroll(effect->slot, lbl_806D555C, lbl_806D55C0);
        effect->baseScale = effect->scale;
        effect->growth = lbl_806D555C;
        effect->alpha = lbl_806D5584;
        if (effect->variant != 0) {
            Vec3_Subtract_DestFirst(&direction, &lbl_805DF3D0.position, &effect->position);
            Vec3_Scale(&direction, &direction,
                lbl_806D55B4 * (lbl_806D5584 / Vec3_Magnitude_Wrapper(&direction)));
            Vec3_Add_DestFirst(&effect->position, &effect->position, &direction);
        }
        ++effect->state;
        // Initial growth is applied in the same update.
    case 1:
        effect->growth += lbl_806D5560;
        if (lbl_806D5584 < effect->growth) {
            effect->growth = lbl_806D5584;
            if (effect->fadeRequested != 0 || effect->variant != 0) ++effect->state;
        }
        break;
    case 2:
        if (effect->variant == 0) effect->alpha -= lbl_806D55C4;
        else effect->alpha -= lbl_806D55B4;
        if (effect->alpha <= lbl_806D555C) {
            DrawEffect_Free(effect);
            return;
        }
        break;
    }
    effect->scale = lbl_806D556C * (effect->baseScale * effect->growth);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
}
}

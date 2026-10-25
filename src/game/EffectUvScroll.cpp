/* Narrow target-observed layout; live Ghidra types unavailable. */
struct UvVec { float x, y, z; };
struct UvEffect {
    char pad00[0x10];
    int scrollEnabled;
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x5C];
    UvVec position;
    char pad98[0x18];
    float scale;
    char padB4[0x6C];
    UvVec previous;
};
struct UvCamera { char pad00[0x80]; UvVec position; char tail[0xC]; };
extern "C" {
extern UvCamera lbl_805DF3D0;
extern const float lbl_806D57BC, lbl_806D57C0, lbl_806D57C4;
extern const float lbl_806D5770, lbl_806D5790, lbl_806D57C8;
float fn_800D3184(UvVec *, const UvVec *);
void VfxSlot_SetUVScroll(void *, float, float);
void Vec3_Copy(UvVec *, const UvVec *);
void Vec3_Subtract_DestFirst(UvVec *, const UvVec *, const UvVec *);
float Vec3_Magnitude_Wrapper(const UvVec *);
void Vec3_Scale(UvVec *, const UvVec *, float);
void Vec3_Add_DestFirst(UvVec *, const UvVec *, const UvVec *);
void VfxSlot_SetPositionFromVec(void *, UvVec);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_ApplyUvScrollAlong_E4(UvEffect *effect, const UvVec *position, float scale, float alpha) {
    UvVec offset;
    if (!effect) return;
    if (effect->scrollEnabled) {
        float uv = fn_800D3184(&effect->previous, position) / lbl_806D57BC;
        if (0.033333335f < uv) uv = 0.033333335f;
        if (uv < lbl_806D57C4) uv = lbl_806D57C4;
        VfxSlot_SetUVScroll(effect->slot, uv, lbl_806D5770);
        Vec3_Copy(&effect->previous, position);
    }
    effect->scale = scale;
    Vec3_Copy(&effect->position, position);
    Vec3_Subtract_DestFirst(&offset, &lbl_805DF3D0.position, &effect->position);
    float reciprocal = lbl_806D5790 / Vec3_Magnitude_Wrapper(&offset);
    Vec3_Scale(&offset, &offset, (2.0f * scale) * reciprocal);
    Vec3_Add_DestFirst(&effect->position, &effect->position, &offset);
    effect->alpha = alpha;
    effect->visible = 1;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
}
}

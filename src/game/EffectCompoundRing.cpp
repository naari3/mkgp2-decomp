// Compound ring placement, 0x800C3EBC..0x800C4204.
// Layout names describe the accesses in this routine; the effect is otherwise opaque.
// Native reconstruction is NonMatching (99.309525% text; auto EH/index 100%).
// Unsupported mode values deliberately leave orientation/tilt live, as in target.
struct RingVec { float value[3]; };
struct RingPair { float value[2]; };
struct RingEffect;
struct RingChildren {
    unsigned char pad00[0x10];
    RingEffect* child[6];
    unsigned char pad28[0x2c];
    RingVec previous;
    RingVec current;
    unsigned char pad6C[0x18];
    float phase;
    unsigned char pad88[0x3c];
    signed char mode;
};
struct RingEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float opacity;
    unsigned char pad30[0x5c];
    RingVec position;
    unsigned char pad98[4];
    float angle;
    unsigned char padA0[0x10];
    float scale;
    unsigned char padB4[0x18];
    RingChildren children;
};
extern "C" {
extern const RingVec lbl_8032A754, lbl_8032A760;
extern const RingPair lbl_806D53E0;
extern const float lbl_806D5484, lbl_806D544C, lbl_806D5488;
extern const float lbl_806D5464, lbl_806D5410, lbl_806D5400, lbl_806D5404;
extern const float lbl_806D548C, lbl_806D5490;
void Mtx44_GetTranslation_RowMajor(RingVec*, const void*);
void Vec3_Copy(RingVec*, const RingVec*);
float BuildOrientationFromYaw(float);
double sin(double);
void GetSpawnPosition(RingVec*, float, float, float);
void Vec3_Scale(RingVec*, const RingVec*, float);
void Vec2_RotateX(RingVec*, const RingVec*, float);
void Vec2_RotateY(RingVec*, const RingVec*, float);
void Vec3_Add_DestFirst(RingVec*, const RingVec*, const RingVec*);
void VfxSlot_SetPositionFromVec(void*, const RingVec*);
void VfxSlot_SetScaleUniform(void*, float);

void Effect_CompoundRing_PlaceChildren(RingEffect* effect, const void* source,
                                     float angle, float scale, float opacity)
{
    RingVec translation;
    RingVec temp;
    RingVec scales;
    RingVec offsets;
    RingVec slotPosition;
    RingPair signs;
    float orientation;
    float tilt;
    RingChildren* ring;
    int i;
    RingEffect* child;

    Mtx44_GetTranslation_RowMajor(&translation, source);
    scales = lbl_8032A754;
    offsets = lbl_8032A760;
    signs = lbl_806D53E0;
    ring = &effect->children;
    Vec3_Copy(&effect->position, &translation);
    effect->angle = angle;
    effect->scale = scale;
    effect->opacity = opacity;
    ring->phase = BuildOrientationFromYaw(lbl_806D5484 + ring->phase);
    for (i = 0; i < 6; ++i) {
        if (ring->child[i]) {
            switch (ring->mode) {
            case 0:
                tilt = signs.value[i / 3];
                orientation = BuildOrientationFromYaw(tilt * (ring->phase - offsets.value[i % 3]) + effect->angle);
                tilt *= lbl_806D5488 * (float)sin(lbl_806D544C * orientation);
                break;
            case 1:
                tilt = signs.value[i / 3];
                orientation = BuildOrientationFromYaw((lbl_806D5464 * tilt + effect->angle) - lbl_806D5410 * offsets.value[i % 3]);
                tilt *= lbl_806D5488 * (float)sin(lbl_806D544C * orientation);
                break;
            }
            child = ring->child[i];
            GetSpawnPosition(&temp, lbl_806D5400, lbl_806D5400, lbl_806D5404);
            Vec3_Scale(&temp, &temp, effect->scale);
            Vec2_RotateX(&temp, &temp, tilt);
            Vec2_RotateY(&temp, &temp, orientation);
            temp.value[1] += lbl_806D548C * effect->scale;
            Vec3_Copy(&child->children.previous, &child->children.current);
            Vec3_Copy(&child->children.current, &temp);
            Vec3_Add_DestFirst(&temp, &effect->position, &temp);
            Vec3_Copy(&ring->child[i]->position, &temp);
            ring->child[i]->scale = lbl_806D5490 * (effect->scale * scales.value[i % 3]);
            ring->child[i]->opacity = effect->opacity;
            slotPosition = ring->child[i]->position;
            VfxSlot_SetPositionFromVec(ring->child[i]->slot, &slotPosition);
            VfxSlot_SetScaleUniform(ring->child[i]->slot, ring->child[i]->scale);
            ring->child[i]->visible = 1;
        }
    }
}
}

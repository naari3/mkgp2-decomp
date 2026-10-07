/* Dust streamer family. Local views describe only observed fields.
 * Full target and actual callee ABI audited; Ghidra unavailable.
 * Positions remain an external 84-byte aggregate, copied into a local.
 * NonMatching: five growth-clamp instructions retain an f1/f2 web swap.
 */
struct DustVec3 { float x, y, z; };
struct DustPositions { DustVec3 entries[7]; };
struct DustKartState {
    unsigned char pad00[0x10];
    unsigned long long bits;
};
struct DustKart {
    unsigned char pad00[0x238];
    int visible;
    unsigned char pad23c[0xc8];
    DustKartState *state;
};
struct DustEffect {
    unsigned char pad00[0x10];
    int index;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x5c];
    DustVec3 position;
    unsigned char pad98[0xc];
    DustVec3 velocity;
    float scale;
    signed char phase, subphase;
    unsigned char padb6[0x66];
    DustKart *kart;
    unsigned char pad120[0x30];
    float growth, stretch;
    unsigned char pad158[0x28];
    unsigned int delay, triggerDelay, timer2, timer3;
};
extern "C" {
extern DustPositions lbl_8032A65C;
extern float lbl_805DF3D0[16];
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51C8, lbl_806D51D4;
extern const float lbl_806D51EC, lbl_806D51F8, lbl_806D521C, lbl_806D5220;
extern const float lbl_806D5224, lbl_806D5228;
extern const float lbl_806D5290, lbl_806D5294, lbl_806D5298, lbl_806D529C;
extern const float lbl_806D52A0, lbl_806D52A4, lbl_806D52A8;
void VfxSlot_BindResourceEx(void *, int, int);
void Vec3_Copy(DustVec3 *, const DustVec3 *);
float Rand_RangeFloat(float, float);
int Rand_RangeInt(int, int);
void VfxSlot_SetRotationZ(void *, float);
void GetSpawnPosition(DustVec3 *, float, float, float);
void DrawEffect_Free(DustEffect *);
void Vec3_Add_DestFirst(DustVec3 *, const DustVec3 *, const DustVec3 *);
void Mtx44_TransformVec3(DustVec3 *, const float *, DustVec3);
void VfxSlot_SetPositionFromVec(void *, DustVec3);
void VfxSlot_SetScaleVec3(void *, float, float, float);
void VfxSlot_SetScaleUniform(void *, float);

static inline bool Expired(DustEffect *effect, float decay)
{
    float minimum = 0.0f;
    effect->lifetime -= decay;
    if (effect->lifetime < minimum) return true;
    return false;
}

void KartFx_DustStreamerPieceTick(DustEffect *effect)
{
    DustPositions positions = lbl_8032A65C;
    DustVec3 transformed;
    float scale;
    switch (effect->phase) {
    case 0:
        if (effect->index == 0) VfxSlot_BindResourceEx(effect->slot, 0x73, 0);
        else VfxSlot_BindResourceEx(effect->slot, 0x74, 0);
        effect->slot[0] = 1;
        Vec3_Copy(&effect->position, &positions.entries[effect->index]);
        if (effect->index != 0)
            VfxSlot_SetRotationZ(effect->slot, lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224));
        effect->scale = lbl_806D51C4;
        if (effect->index == 0) effect->scale *= lbl_806D5228;
        else effect->scale *= Rand_RangeFloat(lbl_806D51EC, lbl_806D51C4);
        effect->growth = lbl_806D51C0;
        effect->stretch = lbl_806D51C4;
        effect->lifetime = lbl_806D51C4;
        effect->phase = 1;
        effect->subphase = 0;
        /* Initialization continues immediately into the growth state. */
    case 1:
        switch (effect->subphase) {
        case 0:
            effect->delay = 0;
            if (effect->index != 0) effect->delay = Rand_RangeInt(5, 10);
            effect->triggerDelay = 3;
            ++effect->subphase;
        case 1:
            if (effect->delay == 0) {
                effect->growth += lbl_806D51F8;
                if (lbl_806D51C4 < effect->growth) {
                    effect->growth = lbl_806D51C4;
                    effect->delay = 10;
                    ++effect->subphase;
                }
            }
            break;
        case 2:
            if (effect->delay == 0) {
                effect->delay = 0;
                if (effect->index != 0) effect->delay = Rand_RangeInt(10, 30);
                ++effect->subphase;
            }
            break;
        case 3:
            if (effect->delay == 0) {
                if (effect->index == 0) effect->velocity.y -= lbl_806D5290;
                else effect->velocity.y -= lbl_806D5294;
                if (effect->index == 0) effect->stretch += lbl_806D5298;
                if (effect->position.y < lbl_806D529C) {
                    DrawEffect_Free(effect);
                    return;
                }
            }
            break;
        }
        {
            DustKartState *state = effect->kart->state;
            if (effect->triggerDelay == 0 && (state->bits & 0x10000ULL) != 0) {
                effect->phase = 2;
                effect->subphase = 0;
            }
        }
        break;
    case 2:
        switch (effect->subphase) {
        case 0:
            GetSpawnPosition(&effect->velocity, lbl_806D51C0, lbl_806D51C0, lbl_806D51C0);
            ++effect->subphase;
        case 1:
            effect->growth += lbl_806D51D4;
            if (Expired(effect, lbl_806D51C8)) {
                DrawEffect_Free(effect);
                return;
            }
            break;
        }
        break;
    }
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    transformed.x = lbl_806D52A0 * effect->position.x;
    transformed.y = lbl_806D52A4 * effect->position.y;
    transformed.z = lbl_806D52A8 + effect->position.z;
    Mtx44_TransformVec3(&transformed, lbl_805DF3D0, transformed);
    VfxSlot_SetPositionFromVec(effect->slot, transformed);
    scale = effect->scale * effect->growth;
    if (effect->index == 0)
        VfxSlot_SetScaleVec3(effect->slot, scale, scale * effect->stretch, scale);
    else VfxSlot_SetScaleUniform(effect->slot, scale);
    if (effect->kart->visible == 0) effect->visible = 0;
    else effect->visible = 1;
    if (effect->delay != 0) --effect->delay;
    if (effect->triggerDelay != 0) --effect->triggerDelay;
    if (effect->timer2 != 0) --effect->timer2;
    if (effect->timer3 != 0) --effect->timer3;
}

}

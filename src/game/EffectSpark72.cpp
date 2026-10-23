/* Narrow target-observed layout; live Ghidra types were unavailable. */
struct Spark72Vec { float x, y, z; };
struct Spark72Effect {
    char pad00[0x14];
    char slot[0x18];
    float alpha;
    char pad30[0x5C];
    Spark72Vec position;
    char pad98[0xC];
    Spark72Vec velocity;
    float scale;
    signed char state;
    char padB5[0xCB];
    unsigned int timers[4];
};
extern "C" {
extern const float lbl_806D556C, lbl_806D558C, lbl_806D555C;
extern const float lbl_806D5590, lbl_806D5574, lbl_806D5594, lbl_806D5598;
extern const float lbl_806D559C, lbl_806D5584, lbl_806D55A0, lbl_806D55A4;
void VfxSlot_BindResourceEx(void *, int, int);
float Rand_RangeFloat(float, float);
int Rand_RangeInt(int, int);
void GetSpawnPosition(Spark72Vec *, float, float, float);
void Vec2_RotateX(Spark72Vec *, const Spark72Vec *, float);
void Vec2_RotateY(Spark72Vec *, const Spark72Vec *, float);
void Vec3_Scale(Spark72Vec *, const Spark72Vec *, float);
void VfxSlot_SetScaleUniform(void *, float);
void Vec3_Add_DestFirst(Spark72Vec *, const Spark72Vec *, const Spark72Vec *);
void VfxSlot_SetPositionFromVec(void *, Spark72Vec);
void DrawEffect_Free(Spark72Effect *);

void Effect_Spark_Res72_Update(Spark72Effect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x72, 0);
        GetSpawnPosition(&effect->velocity, lbl_806D555C,
            Rand_RangeFloat(lbl_806D556C, lbl_806D558C), lbl_806D555C);
        Vec2_RotateX(&effect->velocity, &effect->velocity,
            lbl_806D5574 * Rand_RangeFloat(lbl_806D555C, lbl_806D5590));
        Vec2_RotateY(&effect->velocity, &effect->velocity,
            lbl_806D5574 * Rand_RangeFloat(lbl_806D5594, lbl_806D5598));
        Vec3_Scale(&effect->velocity, &effect->velocity, effect->scale);
        effect->scale *= Rand_RangeFloat(lbl_806D556C, lbl_806D559C);
        VfxSlot_SetScaleUniform(effect->slot, effect->scale);
        effect->timers[0] = (signed char)Rand_RangeInt(30, 60);
        effect->alpha = lbl_806D5584;
        ++effect->state;
        break;
    case 1:
        break;
    }
    if (!effect->timers[0]) {
        effect->alpha -= lbl_806D55A0;
        if (effect->alpha < lbl_806D555C) {
            DrawEffect_Free(effect);
            return;
        }
    }
    effect->velocity.y -= lbl_806D55A4;
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
}
}

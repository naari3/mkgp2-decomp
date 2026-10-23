/* Narrow target-observed layout; live Ghidra types unavailable. */
struct CompoundVec { float x, y, z; };
struct CompoundEffect {
    char pad00[0x10];
    int variant;
    char pad14[0x78];
    CompoundVec position;
    char pad98[0xC];
    CompoundVec velocity;
    float scale;
    signed char state;
    char padB5[0x14];
    signed char finished;
    char padCA[0x12];
    CompoundEffect *child;
    char padE0[0x40];
    CompoundVec tuning;
    char pad12C[0x64];
    signed char mode, pieceCount, pad192, flag193;
};
extern "C" {
extern const float lbl_806D555C, lbl_806D5584, lbl_806D55C8, lbl_806D558C;
extern const float lbl_806D5574, lbl_806D55CC, lbl_806D55D0, lbl_806D5570;
extern const float lbl_806D55B4, lbl_806D55D4;
void Effect_Res77or78_Variant_Update(CompoundEffect *);
void Effect_DriftExplosion_Res79_Update(CompoundEffect *);
void Effect_DriftExplosion_Res7A_JointChain_Update(CompoundEffect *);
void Effect_Spark_Res72_Update(CompoundEffect *);
void Effect_ExplosionPiece_Update(CompoundEffect *);
CompoundEffect *DrawEffect_SpawnDirect(void (*)(CompoundEffect *));
void DrawEffect_Free(CompoundEffect *);
void Vec3_Copy(CompoundVec *, const CompoundVec *);
void GetSpawnPosition(CompoundVec *, float, float, float);
float Rand_RangeFloat(float, float);
float BuildOrientationFromYaw(float);
void Vec2_RotateY(CompoundVec *, const CompoundVec *, float);
void Vec3_Scale(CompoundVec *, const CompoundVec *, float);
void Vec3_Add_DestFirst(CompoundVec *, const CompoundVec *, const CompoundVec *);
void Effect_Explosion_Compound_Update(CompoundEffect *effect) {
    CompoundEffect *child;
    int i;
    switch (effect->state) {
    case 0:
        for (i = 0; i < 2; ++i) {
            child = DrawEffect_SpawnDirect(Effect_Res77or78_Variant_Update);
            if (child) {
                child->variant = (unsigned char)i;
                Vec3_Copy(&child->position, &effect->position);
                child->scale = effect->scale;
                child->mode = effect->mode;
            }
            if (i == 0) effect->child = child;
        }
        child = DrawEffect_SpawnDirect(Effect_DriftExplosion_Res79_Update);
        if (child) {
            Vec3_Copy(&child->position, &effect->position);
            child->scale = effect->scale;
            child->mode = effect->mode;
        }
        child = DrawEffect_SpawnDirect(Effect_DriftExplosion_Res7A_JointChain_Update);
        if (child) {
            Vec3_Copy(&child->position, &effect->position);
            child->scale = effect->scale;
            child->mode = effect->mode;
        }
        if (!effect->mode) {
            for (i = 0; i < 10; ++i) {
                child = DrawEffect_SpawnDirect(Effect_Spark_Res72_Update);
                if (child) {
                    Vec3_Copy(&child->position, &effect->position);
                    child->scale = effect->scale;
                    child->mode = effect->mode;
                }
            }
        }
        ++effect->state;
    case 1:
        if (effect->finished) {
            if (effect->child) effect->child->finished = 1;
            effect->child = 0;
            float angle = lbl_806D555C;
            for (i = 0; i < 6; ++i) {
                CompoundEffect *piece = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
                if (piece) {
                    CompoundVec offset;
                    GetSpawnPosition(&piece->velocity, lbl_806D555C, lbl_806D555C, lbl_806D5584);
                    Vec2_RotateY(&piece->velocity, &piece->velocity,
                        BuildOrientationFromYaw(angle + lbl_806D5574 * Rand_RangeFloat(lbl_806D55C8, lbl_806D558C)));
                    Vec3_Scale(&offset, &piece->velocity, effect->scale * Rand_RangeFloat(lbl_806D55CC, lbl_806D55D0));
                    Vec3_Add_DestFirst(&piece->position, &effect->position, &offset);
                    Vec3_Scale(&piece->velocity, &piece->velocity, effect->scale * Rand_RangeFloat(lbl_806D5570, lbl_806D5584));
                    if (!effect->mode) piece->pieceCount = 4;
                    else piece->pieceCount = 2;
                    piece->flag193 = 1;
                    GetSpawnPosition(&piece->tuning, lbl_806D55B4, lbl_806D55B4, lbl_806D55B4);
                }
                angle = BuildOrientationFromYaw(lbl_806D55D4 + angle);
            }
            DrawEffect_Free(effect);
        }
        break;
    }
}
}

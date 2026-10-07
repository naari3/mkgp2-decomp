/* ASM-derived partial views; no Ghidra type access was available.
 * Complete NonMatching draft: .text 98.61842%, extab/extabindex 100%.
 * The sole residual is the first velocity setup's scratch FP scheduling:
 * target multiplies the speed then loads zero in f1/copies f1 to f2;
 * CW loads zero in f2 before the multiply/copies f2 to f1.
 * No inline ASM or manually emitted EH is used. */
struct GabyouHitVec { float x, y, z; };
struct GabyouHitItem {
    unsigned char pad00[8]; int type;
    unsigned char pad0C[0x1C]; unsigned char active;
    unsigned char pad29[0x77]; GabyouHitVec position;
    unsigned char padAC[0x1C]; unsigned char state, hitFlag;
    unsigned char padCA[0xB6]; unsigned int owner94, owner98;
    unsigned char pad188[0x54]; signed char mode;
    unsigned char pad1DD[3]; unsigned int modeData;
    unsigned char pad1E4[8];
};
struct GabyouHitContext {
    unsigned char pad00[0x94]; unsigned int owner94, owner98;
    void *driver; unsigned char padA0[0x50]; signed char mode;
    unsigned char padF1[3]; unsigned int modeData;
};
struct GabyouHitEffect {
    unsigned char pad00[0x8C]; GabyouHitVec position;
    unsigned char pad98[0xC]; GabyouHitVec velocity;
    unsigned char padB0[0x6C]; void *owner; GabyouHitVec scale;
    unsigned char pad12C[0x64]; unsigned char flags[4];
};
extern "C" {
GabyouHitItem *ItemObject_SpawnWithAlias(int, int);
GabyouHitEffect *DrawEffect_SpawnDirect(void (*)(GabyouHitEffect *));
void Effect_ExplosionPiece_Update(GabyouHitEffect *);
void Vec3_Copy(GabyouHitVec *, const GabyouHitVec *);
void GetSpawnPosition(GabyouHitVec *, float, float, float);
void Vec2_RotateX(GabyouHitVec *, const GabyouHitVec *, float);
void Vec2_RotateY(GabyouHitVec *, const GabyouHitVec *, float);
float Rand_RangeFloat(float, float);
void SoundMgr_PlaySE_Positional(int, const GabyouHitVec *, int);
int KartItem_QueryEffectStateFromIse(void *);
void ItemHit_Dispatch(GabyouHitItem *, signed char, const GabyouHitVec *, void *);
void *memset(void *, int, unsigned long);
extern const float lbl_806D5D20, lbl_806D5D24, lbl_806D5D2C;
extern const float lbl_806D5D34, lbl_806D5D38, lbl_806D5D3C;
extern const float lbl_806D5D40, lbl_806D5D44, lbl_806D5D48, lbl_806D5D4C;

void GabyouItem_OnHitFlush_2Eto31(GabyouHitItem *item, GabyouHitContext *context)
{
    switch (item->type) {
    case 0x2E: {
        GabyouHitItem *spawn = ItemObject_SpawnWithAlias(0x64, 0xFF);
        if (spawn) {
            Vec3_Copy(&spawn->position, &item->position);
            spawn->owner94 = context->owner94;
            spawn->owner98 = context->owner98;
        }
        break;
    }
    case 0x2F: {
        GabyouHitItem *spawn = ItemObject_SpawnWithAlias(0x63, 0xFF);
        if (spawn) {
            spawn->mode = context->mode;
            spawn->modeData = context->modeData;
            Vec3_Copy(&spawn->position, &item->position);
            spawn->owner94 = context->owner94;
            spawn->owner98 = context->owner98;
        }
        break;
    }
    case 0x30: case 0x31:
        if (context->mode == 0) {
            for (int i = 0; i < 3; ++i) {
                GabyouHitEffect *effect = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
                if (effect) {
                    Vec3_Copy(&effect->position, &item->position);
                    float speed = lbl_806D5D2C * Rand_RangeFloat(lbl_806D5D34, lbl_806D5D38);
                    float zero = lbl_806D5D20;
                    GetSpawnPosition(&effect->velocity, zero, zero, speed);
                    Vec2_RotateX(&effect->velocity, &effect->velocity,
                        lbl_806D5D3C * Rand_RangeFloat(lbl_806D5D40, lbl_806D5D20));
                    Vec2_RotateY(&effect->velocity, &effect->velocity,
                        lbl_806D5D3C * Rand_RangeFloat(lbl_806D5D44, lbl_806D5D48));
                    effect->flags[0] = 1;
                    effect->flags[1] = 1;
                    effect->flags[2] = 1;
                    effect->owner = context->driver;
                    GetSpawnPosition(&effect->scale, lbl_806D5D4C, lbl_806D5D4C, lbl_806D5D24);
                    effect->flags[3] = 1;
                }
            }
            GabyouHitVec position = item->position;
            SoundMgr_PlaySE_Positional(0x87, &position, 0);
        } else {
            GabyouHitItem *spawn = ItemObject_SpawnWithAlias(0x64, 0xFF);
            if (spawn) {
                Vec3_Copy(&spawn->position, &item->position);
                spawn->owner94 = context->owner94;
                spawn->owner98 = context->owner98;
            }
            if (context->driver && KartItem_QueryEffectStateFromIse(context->driver) == 1) {
                GabyouHitItem hit;
                memset(&hit, 0, sizeof(hit));
                hit.type = 0x2E;
                hit.owner98 = context->owner98;
                ItemHit_Dispatch(&hit, 0, &item->position, context->driver);
            }
        }
        break;
    }
    item->active = 0;
    item->state = 3;
    item->hitFlag = 0;
}
}

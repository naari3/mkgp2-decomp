/* Local views, restricted to fields observed in the target callback.
 * Aggregate resources remain external and are copied once per loop iteration.
 * NonMatching: f1/f2 are exchanged in the two growth/clamp blocks.
 * The complete control flow and native EH/index are otherwise exact.
 */
struct StateVec { float x, y, z; };
struct StatePair { signed char value[2]; };
union StateTriple {
    struct { StatePair pair; signed char last; } parts;
    signed char value[3];
};
struct StateKart { unsigned char pad[0x238]; int wingEnabled; };
struct StateEffect {
    unsigned char pad00[0x10];
    unsigned int side;
    unsigned char pad14[0x78];
    StateVec position;
    unsigned char pad98[0xC];
    StateVec offset;
    float growth;
    unsigned char padb4[0x15];
    unsigned char cleanup;
    unsigned char padca[0x12];
    void *owner;
    unsigned char pade0[0x3C];
    StateKart *kart;
    unsigned char pad120[0x30];
    float intensity;
    unsigned char pad154[0x3C];
    unsigned char variant, alternate;
};
struct StatePayload {
    StateKart *kart;
    unsigned char pad04[4];
    signed char state[2];
    unsigned char pad0a[0xE];
    StateVec offset;
    float speed;
    unsigned char pad28[0x14];
    float charge;
    unsigned char pad40[0x54];
    unsigned char smokeCooldown;
    unsigned char pad95[3];
    StateEffect *chain[3][2];
    StateEffect *flamePair;
    unsigned char hitCooldown, mushroomCooldown;
    unsigned char padb6[2];
    StateEffect *starAura;
    unsigned char starCooldown, driftCooldown, driftSide, padbf;
    float driftGrowth;
    StateEffect *trail;
    float exhaustGrowth;
};
struct StateMotion { unsigned char pad00[0x10]; unsigned long long flags; };
extern "C" {
extern StatePair lbl_806D51A0, lbl_806D51A8;
/* These adjacent symbols are copied into a three-byte local aggregate. */
extern StatePair lbl_806D51A4;
extern signed char lbl_806D51A6;
extern const float lbl_806D51BC, lbl_806D51C0, lbl_806D51C4;
extern const float lbl_806D51C8, lbl_806D51D8, lbl_806D51E8;
extern const double lbl_806D5380;
void EffectVfx6D_KartSmokeSpark_Tick(StateEffect *);
void EffectItemChainIndicator_Tick(StateEffect *);
void EffectItem4SpawnSubFlamePair_Tick(StateEffect *);
void EffectVfx134_KartHitBurst_Tick(StateEffect *);
void EffectVfx13_14_84_85_BoostSpark_Tick(StateEffect *);
void EffectVfx13or14_MushroomDust_Tick(StateEffect *);
void EffectVfx15_StarItemAura_Tick(StateEffect *);
void EffectVfx16_StarItemBurst_Tick(StateEffect *);
void EffectVfx9_DriftSpark_Tick(StateEffect *);
void EffectVfx10_KartTrail_Tick(StateEffect *);
void KartFx_BoostExhaustRayTick(StateEffect *);
StateEffect *DrawEffect_SpawnDirect(void (*)(StateEffect *));
const float *KartDriver_GetKartRootMtx(StateKart *);
void Mtx44_GetTranslation_RowMajor(StateVec *, const float *);
void Vec3_Copy(StateVec *, const StateVec *);
int Rand_RangeIntMax(int);

void KartFx_DispatchGroupE_StateByte(void *owner, StatePayload *payload,
                                    StateMotion *motion, int enabled) {
    if (enabled) {
        for (int i = 0; i < 2; ++i) {
            StatePair kinds = lbl_806D51A0;
            if (payload->state[0] == kinds.value[i] &&
                payload->state[1] == kinds.value[i] &&
                payload->charge < lbl_806D51E8 &&
                lbl_806D51BC <= payload->speed && !payload->smokeCooldown) {
                StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx6D_KartSmokeSpark_Tick);
                if (effect) {
                    Mtx44_GetTranslation_RowMajor(&effect->position,
                        KartDriver_GetKartRootMtx(payload->kart));
                    effect->variant = kinds.value[i];
                    if (payload->kart->wingEnabled) effect->kart = payload->kart;
                }
                payload->smokeCooldown = 6;
            }
        }
    }
    if (payload->smokeCooldown) --payload->smokeCooldown;
    for (int kind = 0; kind < 3; ++kind) {
        for (int side = 0; side < 2; ++side) {
            StateTriple kinds;
            kinds.parts.pair = lbl_806D51A4;
            kinds.parts.last = lbl_806D51A6;
            if (payload->state[side] == kinds.value[kind] &&
                payload->kart->wingEnabled &&
                (kind != 0 || lbl_806D51C8 <= payload->charge) &&
                payload->charge < lbl_806D51E8) {
                if (!payload->chain[kind][side]) {
                    payload->chain[kind][side] = DrawEffect_SpawnDirect(EffectItemChainIndicator_Tick);
                    if (payload->chain[kind][side]) {
                        payload->chain[kind][side]->kart = payload->kart;
                        Vec3_Copy(&payload->chain[kind][side]->offset, &payload->offset);
                        payload->chain[kind][side]->side = (unsigned char)side;
                        payload->chain[kind][side]->alternate = payload->state[side];
                    }
                }
            } else if (payload->chain[kind][side]) {
                if (payload->state[side] != kinds.value[kind])
                    payload->chain[kind][side]->cleanup = 1;
                else payload->chain[kind][side]->cleanup = 2;
                payload->chain[kind][side] = 0;
            }
        }
    }
    if (enabled && payload->state[0] == 4 && payload->state[1] == 4 && !payload->flamePair) {
        payload->flamePair = DrawEffect_SpawnDirect(EffectItem4SpawnSubFlamePair_Tick);
        if (payload->flamePair) {
            payload->flamePair->kart = payload->kart;
            payload->flamePair->owner = owner;
        }
    }
    if (enabled && (motion->flags & 0x100000ULL) != 0 &&
        lbl_806D51BC <= payload->speed && !payload->hitCooldown) {
        StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx134_KartHitBurst_Tick);
        if (effect) effect->kart = payload->kart;
        payload->hitCooldown = 5;
    }
    if (payload->hitCooldown) --payload->hitCooldown;
    if (enabled) {
        StatePair state;
        state.value[0] = payload->state[0];
        state.value[1] = payload->state[1];
        if ((motion->flags & 0x100000ULL) != 0) {
            state.value[0] = 4;
            state.value[1] = 4;
        }
        for (int kind = 0; kind < 2; ++kind) {
            for (int side = 0; side < 2; ++side) {
                StatePair kinds = lbl_806D51A8;
                if (state.value[side] == kinds.value[kind] && lbl_806D51BC <= payload->speed) {
                    StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx13_14_84_85_BoostSpark_Tick);
                    if (effect) {
                        effect->kart = payload->kart;
                        Vec3_Copy(&effect->offset, &payload->offset);
                        effect->side = (unsigned char)side;
                        effect->variant = state.value[side];
                        if (kind == 0 && Rand_RangeIntMax(15) % 2 != 0) effect->alternate = 1;
                    }
                }
            }
        }
    }
    if (enabled) {
        for (int side = 0; side < 2; ++side) {
            if (payload->state[side] == 5 && lbl_806D51BC <= payload->speed && !payload->mushroomCooldown) {
                StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx13or14_MushroomDust_Tick);
                if (effect) {
                    effect->side = (unsigned char)side;
                    effect->kart = payload->kart;
                }
                payload->mushroomCooldown = 3;
            }
        }
    }
    if (payload->mushroomCooldown) --payload->mushroomCooldown;
    if (enabled && payload->state[0] == 6 && payload->state[1] == 6 && !payload->starAura) {
        payload->starAura = DrawEffect_SpawnDirect(EffectVfx15_StarItemAura_Tick);
        if (payload->starAura) {
            payload->starAura->kart = payload->kart;
            payload->starAura->owner = owner;
        }
    }
    if (enabled && payload->state[0] == 6 && payload->state[1] == 6 &&
        lbl_806D51BC < payload->speed && !payload->starCooldown) {
        StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx16_StarItemBurst_Tick);
        if (effect) effect->kart = payload->kart;
        payload->starCooldown = 15;
    }
    if (payload->starCooldown) --payload->starCooldown;
    if (lbl_806D51C8 <= payload->charge) {
        float limit = 1.0f;
        payload->driftGrowth += lbl_806D51D8;
        if (limit < payload->driftGrowth) payload->driftGrowth = limit;
    } else payload->driftGrowth = lbl_806D51C0;
    if (enabled && lbl_806D51C8 <= payload->charge && !payload->driftCooldown) {
        StateEffect *effect = DrawEffect_SpawnDirect(EffectVfx9_DriftSpark_Tick);
        if (effect) {
            effect->side = payload->driftSide;
            effect->kart = payload->kart;
            Vec3_Copy(&effect->offset, &payload->offset);
            effect->growth = payload->driftGrowth;
        }
        payload->driftSide ^= 1;
        payload->driftCooldown = 5;
    }
    if (payload->driftCooldown) --payload->driftCooldown;
    if (enabled && lbl_806D51C8 <= payload->charge && !payload->trail) {
        payload->trail = DrawEffect_SpawnDirect(EffectVfx10_KartTrail_Tick);
        if (payload->trail) {
            payload->trail->kart = payload->kart;
            payload->trail->owner = owner;
        }
    }
    if (lbl_806D51E8 <= payload->charge) {
        float limit = 1.0f;
        payload->exhaustGrowth += lbl_806D51D8;
        if (limit < payload->exhaustGrowth) payload->exhaustGrowth = limit;
    } else {
        payload->exhaustGrowth -= lbl_806D51D8;
        if (payload->exhaustGrowth < lbl_806D5380) payload->exhaustGrowth = lbl_806D51C0;
    }
    if (enabled && payload->exhaustGrowth != lbl_806D51C0) {
        for (int side = 0; side < 2; ++side) {
            StateEffect *effect = DrawEffect_SpawnDirect(KartFx_BoostExhaustRayTick);
            if (effect) {
                effect->side = (unsigned char)side;
                effect->kart = payload->kart;
                effect->intensity = payload->exhaustGrowth;
            }
        }
    }
}
}

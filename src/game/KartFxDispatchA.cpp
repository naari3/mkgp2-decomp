/* Dispatch-only ABI views. The flags and latches are independent: callbacks
 * can mutate kart state, so later dispatches deliberately reload their flags.
 */
struct DispatchKart {
    unsigned char pad00[0x238];
    int field238;
};
struct DispatchEffect {
    unsigned char pad00[0x10];
    unsigned int side;
    unsigned char pad14[0x108];
    DispatchKart *kart;
};
struct DispatchMotion {
    unsigned char pad00[0x10];
    unsigned long long flags;
    unsigned char pad18[0x10];
    float horn;
    int boostSide;
};
struct DispatchPayload {
    DispatchKart *kart;
    unsigned char pad04[0x20];
    float wheelSpeed;
    unsigned char pad28[0x10];
    signed char auxAccel;
    unsigned char pad39[0x13];
    DispatchEffect *horn, *drift;
    unsigned char flashDelay, flashIndex, landDelay, boostPrevious[2];
    unsigned char pad59[3];
    DispatchEffect *streak, *spark;
    unsigned char auxDelay;
    unsigned char pad65[3];
    DispatchEffect *wheel;
    unsigned char wheelPrevious, wheelDelay;
    unsigned char pad6e[2];
    DispatchEffect *fire, *status, *matrix, *trail;
};
struct DispatchFlames { unsigned char side[2]; };
extern "C" {
extern const DispatchFlames lbl_806DCF30;
extern const float lbl_806D51C0, lbl_806D51BC;
double FAbs_FloatAsDouble(float);
DispatchEffect *DrawEffect_SpawnDirect(void (*)(DispatchEffect *));
void KartFx_HornBlastTick(DispatchEffect *);
void KartFx_DriftPuffTick(DispatchEffect *);
void KartFx_FlashOrbitTick(DispatchEffect *);
void KartFx_JumpLandPuffTick(DispatchEffect *);
void KartFx_Slot57_BoostFlameTick(DispatchEffect *);
void KartFx_Slot5C_TripleStreakTick(DispatchEffect *);
void KartFx_Slot50_RingExplodeTick(DispatchEffect *);
void KartFx_Slot68_JumpDustSpawner(DispatchEffect *);
void KartFx_DustStreamerSpawnerTick(DispatchEffect *);
void KartFx_Slot60_DriftSparkTick(DispatchEffect *);
void KartFx_Slot4C_AuxAccelBurstTick(DispatchEffect *);
void DrawEffect_Cb_KartWheel_DualSpawn(DispatchEffect *);
void DrawEffect_Cb_DualBurstSpawner_2x4(DispatchEffect *);
void DrawEffect_Cb_WheelSpark_Bind4D(DispatchEffect *);
void DrawEffect_Cb_KartFire_WithSE99(DispatchEffect *);
void DrawEffect_Cb_KartItemStatus_Bind0C(DispatchEffect *);
void DrawEffect_Cb_MatrixSourced_Bind63(DispatchEffect *);
void DrawEffect_Cb_KartTrail_Bind3E(DispatchEffect *);
void DrawEffect_Cb_BurstSpawner_30Frame(DispatchEffect *);
}

static inline unsigned char Flag(DispatchMotion *motion, unsigned long long mask) {
    unsigned char result;
    if ((motion->flags & mask) == 0) result = 0;
    else result = 1;
    return result;
}

extern "C" void KartFx_DispatchGroupA(void *, DispatchPayload *payload,
                                      DispatchMotion *motion, int enabled) {
    if (enabled) {
        /* Keep the double result named: this also preserves compare direction. */
        double magnitude = FAbs_FloatAsDouble(motion->horn);
        if (magnitude != lbl_806D51C0 && !payload->horn) {
            payload->horn = DrawEffect_SpawnDirect(KartFx_HornBlastTick);
            if (payload->horn) payload->horn->kart = payload->kart;
        }
    }
    if (enabled && (Flag(motion, 0x20000ULL) ||
                    (motion->flags & 0x4000000000000000ULL) != 0) && !payload->drift) {
        payload->drift = DrawEffect_SpawnDirect(KartFx_DriftPuffTick);
        if (payload->drift) payload->drift->kart = payload->kart;
    }
    if (enabled && (motion->flags & 0x80000ULL) != 0 && payload->flashDelay == 0) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_FlashOrbitTick);
        if (effect) {
            effect->kart = payload->kart;
            effect->side = payload->flashIndex;
            payload->flashIndex = (payload->flashIndex + 1) % 4;
        }
        payload->flashDelay = 10;
    }
    if (payload->flashDelay) --payload->flashDelay;
    if ((motion->flags & 0x80000ULL) != 0) payload->landDelay = 30;
    else if (payload->landDelay && enabled && payload->kart->field238) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_JumpLandPuffTick);
        if (effect) effect->kart = payload->kart;
    }
    if (payload->landDelay) --payload->landDelay;
    if (enabled) {
        DispatchFlames flames = lbl_806DCF30;
        if ((motion->flags & 0x20ULL) != 0) {
            switch (motion->boostSide) {
            case 0: flames.side[0] = 1; flames.side[1] = 1; break;
            case 1: flames.side[0] = 1; break;
            case 2: flames.side[1] = 1; break;
            }
        }
        for (int i = 0; i < 2; ++i) {
            if (payload->boostPrevious[i] == 0 && flames.side[i] != 0) {
                DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_Slot57_BoostFlameTick);
                if (effect) {
                    effect->kart = payload->kart;
                    effect->side = i;
                }
            }
        }
        payload->boostPrevious[0] = flames.side[0];
        payload->boostPrevious[1] = flames.side[1];
    }
    if (enabled && (motion->flags & 0x0200000000000000ULL) != 0 && !payload->streak) {
        payload->streak = DrawEffect_SpawnDirect(KartFx_Slot5C_TripleStreakTick);
        if (payload->streak) payload->streak->kart = payload->kart;
    }
    if (enabled && (motion->flags & 0x2000ULL) != 0) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_Slot50_RingExplodeTick);
        if (effect) effect->kart = payload->kart;
    }
    if ((motion->flags & 0x2000ULL) != 0 && payload->kart->field238) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_Slot68_JumpDustSpawner);
        if (effect) effect->kart = payload->kart;
    }
    if ((motion->flags & 0x200ULL) != 0 && payload->kart->field238) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_DustStreamerSpawnerTick);
        if (effect) effect->kart = payload->kart;
    }
    if ((Flag(motion, 0x800ULL) || (motion->flags & 0x200000000ULL) != 0 ||
         (motion->flags & 0x4000000000ULL) != 0) && payload->kart->field238 && !payload->spark) {
        payload->spark = DrawEffect_SpawnDirect(KartFx_Slot60_DriftSparkTick);
        if (payload->spark) {
            payload->spark->kart = payload->kart;
            KartFx_Slot60_DriftSparkTick(payload->spark);
        }
    }
    if (enabled && payload->auxAccel && payload->auxDelay == 0) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(KartFx_Slot4C_AuxAccelBurstTick);
        if (effect) effect->kart = payload->kart;
        payload->auxDelay = 15;
    }
    if (payload->auxDelay) --payload->auxDelay;
    if (enabled && (Flag(motion, 8ULL) || (motion->flags & 0x10ULL) != 0) && !payload->wheel) {
        payload->wheel = DrawEffect_SpawnDirect(DrawEffect_Cb_KartWheel_DualSpawn);
        if (payload->wheel) payload->wheel->kart = payload->kart;
    }
    if (enabled) {
        signed char edge = 0;
        if (Flag(motion, 8ULL) || (motion->flags & 0x10ULL) != 0) edge = 1;
        if (payload->wheelPrevious == 0 && edge) {
            DispatchEffect *effect = DrawEffect_SpawnDirect(DrawEffect_Cb_DualBurstSpawner_2x4);
            if (effect) effect->kart = payload->kart;
        }
        payload->wheelPrevious = edge;
    }
    if (enabled && (motion->flags & 0x40000ULL) != 0 &&
        lbl_806D51BC <= payload->wheelSpeed && payload->wheelDelay == 0) {
        for (int i = 0; i < 2; ++i) {
            DispatchEffect *effect = DrawEffect_SpawnDirect(DrawEffect_Cb_WheelSpark_Bind4D);
            if (effect) {
                effect->side = (unsigned char)i;
                effect->kart = payload->kart;
            }
            payload->wheelDelay = 3;
        }
    }
    if (payload->wheelDelay) --payload->wheelDelay;
    if ((motion->flags & 0x1000000000000000ULL) != 0 && !payload->fire) {
        payload->fire = DrawEffect_SpawnDirect(DrawEffect_Cb_KartFire_WithSE99);
        if (payload->fire) payload->fire->kart = payload->kart;
    }
    if ((motion->flags & 0x400000ULL) != 0 && !payload->status) {
        payload->status = DrawEffect_SpawnDirect(DrawEffect_Cb_KartItemStatus_Bind0C);
        if (payload->status) payload->status->kart = payload->kart;
    }
    if (enabled && (motion->flags & 0x40000000ULL) != 0 && !payload->matrix) {
        payload->matrix = DrawEffect_SpawnDirect(DrawEffect_Cb_MatrixSourced_Bind63);
        if (payload->matrix) payload->matrix->kart = payload->kart;
    }
    if ((motion->flags & 0x2000000ULL) != 0 && !payload->trail) {
        payload->trail = DrawEffect_SpawnDirect(DrawEffect_Cb_KartTrail_Bind3E);
        if (payload->trail) payload->trail->kart = payload->kart;
    }
    if ((Flag(motion, 0x800ULL) || (motion->flags & 0x200000000ULL) != 0 ||
         (motion->flags & 0x2000000000ULL) != 0) && payload->kart->field238 == 0) {
        DispatchEffect *effect = DrawEffect_SpawnDirect(DrawEffect_Cb_BurstSpawner_30Frame);
        if (effect) {
            effect->kart = payload->kart;
            if (Flag(motion, 0x800ULL)) effect->side = 0;
            else if ((motion->flags & 0x200000000ULL) != 0) effect->side = 1;
            else effect->side = 2;
        }
    }
}

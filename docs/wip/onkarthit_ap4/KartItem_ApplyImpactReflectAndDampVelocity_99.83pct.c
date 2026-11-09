static inline float KartItem_sqrtf_r(float x) {
    volatile float y;
    if (x > lbl_806D26EC) {
        double guess = __frsqrte(x);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        y = (float)(x * guess);
        x = y;
    }
    return x;
}

static inline unsigned char KartItem_IsReflectItem(ItemSecondaryLane *sec) {
    const unsigned int *t = lbl_802ED9E4;
    int i;
    for (i = 0; i < 4; i++) {
        if (sec->itemId == (int)t[i]) return 0;
    }
    return 1;
}

#pragma exceptions off
int KartItem_ApplyImpactReflectAndDampVelocity(KartItemOpsView *self, float *ox, float *oy, float *oz) { /* 0x8004B140 size:0x254 */
    KartMovementSpeedView *mv;
    void *stats;
    float sq;
    if (self->ownerDriver->deathState2b8 == 1) {
        return 0;
    }
    if ((unsigned char)KartItem_IsReflectItem(self->secondary) == 0) {
        return 0;
    }
    if (self->strPcbGate20 != 0) {
        SoundObj_PlaySE_Direct(self->soundCtrl, 0x4c);
    }
    mv = self->movement;
    sq = mv->velX * mv->velX + mv->velY * mv->velY + mv->velZ * mv->velZ;
    if (sq > lbl_806D26EC) {
        volatile float y;
        double guess = __frsqrte(sq);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        y = (float)(sq * guess);
        sq = y;
    }
    if (sq > lbl_806D26EC) {
        float k = lbl_806D2714;
        *ox = k * (lbl_806D2730 * mv->velX);
        *oy = k * (lbl_806D2730 * mv->velY);
        *oz = k * (lbl_806D2730 * mv->velZ);
    } else {
        KartMovementSpeedView *rest = self->movement;
        *ox = rest->restVelX;
        *oy = rest->restVelY;
        *oz = rest->restVelZ;
    }
    if ((stats = lbl_806D10A0) == 0) {
        stats = 0;
    }
    if (stats != 0) {
        TitleStats_SetEventFlag_806d1420(stats, self->raceScore10);
    }
    if (KartMovement_GetCurrentItemId(self->ownerDriver) >= 0) {
        return 1;
    }
    if (self->itemSelect104 != 0 && ItemSelect_StartRouletteSpin(self->itemSelect104, self->ownerDriver, 1, 0) >= 0) {
        if ((stats = lbl_806D10A0) == 0) {
            stats = 0;
        }
        if (stats != 0) {
            TitleStats_IncCurrentRaceScore(stats, self->raceScore10, 0);
        }
    }
    fn_801B5B60(GetKartStartSlot(self->raceScore10));
    return 1;
}
#pragma exceptions reset


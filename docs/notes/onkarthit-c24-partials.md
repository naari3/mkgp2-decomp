# onkarthit-c24-partials

Source: Codex worker c24_a26_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

Reflect best partial (99.832214) remains existing ap4 algorithm with compiler EH enabled and SINGLETON_INSTANCE substitutions. sec/return swapped unchanged by nested-getter or whole-check wrapper; stop after3 approaches. Paste-ready helper+function follows:
static inline unsigned char KartItem_IsReflectItem(ItemSecondaryLane *sec) {
    const unsigned int *t = KartItem_ApplyImpactReflectAndDampVelocity_rodata_802ED9E4;
    int i;
    for (i = 0; i < 4; i++) {
        if (sec->itemId == (int)t[i]) return 0;
    }
    return 1;
}

#pragma exceptions on
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
    stats = SINGLETON_INSTANCE(lbl_806D10A0);
    if (stats != 0) {
        TitleStats_SetEventFlag_806d1420(stats, self->raceScore10);
    }
    if (KartMovement_GetCurrentItemId(self->ownerDriver) >= 0) {
        return 1;
    }
    if (self->itemSelect104 != 0 && ItemSelect_StartRouletteSpin(self->itemSelect104, self->ownerDriver, 1, 0) >= 0) {
        stats = SINGLETON_INSTANCE(lbl_806D10A0);
        if (stats != 0) {
            TitleStats_IncCurrentRaceScore(stats, self->raceScore10, 0);
        }
    }
    fn_801B5B60(GetKartStartSlot(self->raceScore10));
    return 1;
}
#pragma exceptions reset


Projectile best partial98.945206 is unchanged existing ap4 98.9 source below; diagnostic only, raw aggregates do not produce its required destructor EH. In-place reference root with genuine Vec3c locals98.061646 still f4 vs targetf7; returned vector/by-value magnitude66.678085. Original asm retained.
#pragma exceptions off
typedef struct ProjScratch { float w[3]; float w2[3]; } ProjScratch;
void ItemEffect_Projectile(ItemStateBlock *self, int idx, void *arg) { /* 0x80051A70 size:0x248 */
    const ItemObjectPosView *obj = (const ItemObjectPosView *)arg;
    float mag2;
    float mag;
    struct { float x, y, z, pad; } d;
    float w2[3];
    float w[3];
    float vy;
    float vx;
    KartMovementSpeedView *mv;
    float vz;

    vx = obj->velX;
    vy = obj->velY;
    vz = obj->velZ;
    d.x = vx;
    d.y = vy;
    d.z = vz;
    vx = d.z * d.z + (d.x * d.x + d.y * d.y); mag = ItemEffect_sqrtf(vx);
    {
        float *dp = &d.x;
        if (mag <= lbl_806D26EC) {
            dp[0] = dp[1] = dp[2] = lbl_806D26EC;
        } else {
            float inv = lbl_806D26FC / mag;
            dp[0] = dp[0] * inv;
            dp[1] = dp[1] * inv;
            dp[2] = dp[2] * inv;
        }
    }
    mv = self->owner->movement;
    {
        float *vel = &mv->velX;
        float *p;
        vx = vel[0]; vy = vel[1]; vz = vel[2]; w[0] = vx; w[1] = vy; w[2] = vz;
        { float *q = w; w2[0] = q[0]; w2[1] = q[1]; w2[2] = q[2]; }
        p = w2;
        mag2 = ItemEffect_sqrtf(p[2] * p[2] + (p[0] * p[0] + p[1] * p[1]));
    }
    d.x = d.x * mag2;
    d.y = d.y * mag2;
    d.z = d.z * mag2;
    d.x = d.x * lbl_806D2730;
    d.y = d.y * lbl_806D2730;
    d.z = d.z * lbl_806D2730;
    d.x = d.x * ItemEffect_Projectile_rodata_802ED5B4[idx].scaleA;
    d.y = d.y * ItemEffect_Projectile_rodata_802ED5B4[idx].scaleA;
    d.z = d.z * ItemEffect_Projectile_rodata_802ED5B4[idx].scaleA;
    ItemEffectImpact_TryArm(self->guard, &d.x, self->owner->movement->transform, ItemEffect_Projectile_rodata_802ED5B4[idx].mode8);
    {
        typedef struct { int a, b; } ProjPair;
        *(ProjPair *)&self->activeId = *(const ProjPair *)&ItemEffect_Projectile_rodata_802ED5B4[idx].valC;
    }
}
#pragma exceptions reset


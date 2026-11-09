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
    d.x = d.x * lbl_802ED5B4[idx].scaleA;
    d.y = d.y * lbl_802ED5B4[idx].scaleA;
    d.z = d.z * lbl_802ED5B4[idx].scaleA;
    ItemEffectImpact_TryArm(self->guard, &d.x, self->owner->movement->transform, lbl_802ED5B4[idx].mode8);
    {
        typedef struct { int a, b; } ProjPair;
        *(ProjPair *)&self->activeId = *(const ProjPair *)&lbl_802ED5B4[idx].valC;
    }
}
#pragma exceptions reset

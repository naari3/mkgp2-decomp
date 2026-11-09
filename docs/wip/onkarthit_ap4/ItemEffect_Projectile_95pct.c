#pragma exceptions off
typedef struct ProjScratch { float w[3]; float w2[3]; } ProjScratch;
void ItemEffect_Projectile(ItemStateBlock *self, int idx, void *arg) { /* 0x80051A70 size:0x248 */
    const ItemObjectPosView *obj = (const ItemObjectPosView *)arg;
    Vec3 d; /* sp+0x28 */
    ProjScratch s; /* sp+0x10 */
    float vx, vy, vz, mag, mag2;
    KartMovementSpeedView *mv;

    vx = obj->velX;
    vy = obj->velY;
    vz = obj->velZ;
    d.x = vx;
    d.y = vy;
    d.z = vz;
    mag = ItemEffect_sqrtf(d.z * d.z + (d.x * d.x + d.y * d.y));
    if (mag <= lbl_806D26EC) {
        d.x = d.y = d.z = lbl_806D26EC;
    } else {
        float inv = lbl_806D26FC / mag;
        d.x = d.x * inv;
        d.y = d.y * inv;
        d.z = d.z * inv;
    }
    mv = self->owner->movement;
    {
        float *vel = &mv->velX;
        float *p;
        s.w[0] = vel[0]; s.w[1] = vel[1]; s.w[2] = vel[2];
        s.w2[0] = s.w[0]; s.w2[1] = s.w[1]; s.w2[2] = s.w[2];
        p = s.w2;
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
    self->activeId = lbl_802ED5B4[idx].valC;
    self->activeFlag = lbl_802ED5B4[idx].valD;
}
#pragma exceptions reset

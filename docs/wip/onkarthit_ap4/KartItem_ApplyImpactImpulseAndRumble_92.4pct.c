static inline float KartItem_sqrtf(float x) {
    volatile float y;
    if (x > lbl_806D26EC) {
        double guess = __frsqrte(x);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline void KartItem_AddImpactClamped(KartMovementSpeedView *mv, const float *v) {
    float len;
    mv->impact1ac += v[0];
    mv->impact1b0 += v[1];
    mv->impact1b4 += v[2];
    len = KartItem_sqrtf(mv->impact1ac * mv->impact1ac + mv->impact1b0 * mv->impact1b0 + mv->impact1b4 * mv->impact1b4);
    if (len > mv->impactCap1b8) {
        float k = mv->impactCap1b8 / len;
        mv->impact1ac *= k;
        mv->impact1b0 *= k;
        mv->impact1b4 *= k;
    }
}

static inline unsigned char KartItem_HasBusFlag(KartItemOpsView *self) {
    unsigned char ret = 0;
    if (self->ownerDriver->itemBus->flags & 0x10000000ULL) ret = 1;
    return ret;
}

#pragma exceptions off
void KartItem_ApplyImpactImpulseAndRumble(KartItemOpsView *self, int mode, float x, float y, float z) { /* 0x8004B49C size:0x520 */
    float mtx[16];
    float d[3];
    float r[3];
    float w[3];
    float len;
    float *t = self->movement->transform;
    int i;
    for (i = 0; i < 16; i++) mtx[i] = t[i];
    {
        float *q = mtx;
        float *pd = d;
        float dx = x - q[12];
        float dy = y - q[13];
        float dz = z - q[14];
        pd[0] = dx; pd[1] = dy; pd[2] = dz;
        {
            float t0 = dx * dx;
            float t1 = dy * dy;
            float sum = t0 + t1;
            float t2 = dz * dz;
            len = KartItem_sqrtf(t2 + sum);
        }
    }
    if (!EffectState_HasContent(self->effectState44)) {
        float dot = d[0] * mtx[0] + d[1] * mtx[1] + d[2] * mtx[2];
        if (self->strPcbGate20 == 1) {
            float tm;
            if (dot > lbl_806D26EC) {
                tm = lbl_806D2734;
            } else {
                tm = lbl_806D2738;
            }
            StrPcb_SetTimer3c40(StrPcb_GetInstance(), tm, 0xc);
        }
    }
    {
        float inv = -(lbl_806D26FC / len);
        d[0] *= inv;
        d[1] *= inv;
        d[2] *= inv;
    }
    if (!(self->ownerDriver->itemBus->flags & 0x10000000ULL) || !(unsigned char)mode) {
        float s = lbl_806D273C * len;
        d[0] *= s;
        d[1] *= s;
        d[2] *= s;
        KartItem_AddImpactClamped(self->movement, d);
        len = lbl_806D2740 - len;
        if (len < lbl_806D26EC) len = 1.0f;
        len *= lbl_806D273C;
    } else if (KartItem_HasBusFlag(self) == 1) {
        len = lbl_806D2740 - len;
        if (len < lbl_806D26EC) len = 1.0f;
        len *= lbl_806D273C;
    }
    {
        float proj;
        float k;
        float *pr = r;
        float *pw = w;
        {
            float *pd = d;
            float *q = mtx;
            float t0 = q[8] * pd[0];
            float t1 = q[9] * pd[1];
            float sum = t0 + t1;
            float t2 = q[10] * pd[2];
            proj = -(t2 + sum);
        }
        pr[0] = d[0] * len;
        pr[1] = d[1] * len;
        pr[2] = d[2] * len;
        self->movement->rumbleX310 = pr[0];
        self->movement->rumbleY314 = pr[1];
        self->movement->rumbleZ318 = pr[2];
        k = lbl_806D2744 * proj;
        pw[0] = mtx[8];
        pw[1] = mtx[9];
        pw[2] = mtx[10];
        pw[0] *= k;
        pw[1] *= k;
        pw[2] *= k;
        d[0] += pw[0];
        d[1] += pw[1];
        d[2] += pw[2];
        KartItem_AddImpactClamped(self->movement, d);
    }
}
#pragma exceptions reset

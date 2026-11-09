#pragma exceptions off
typedef struct TrapScratch { float dir[3]; float d[3]; float mtx[16]; } TrapScratch;
typedef struct TrapVScratch { float w[3]; float v[3]; } TrapVScratch;
void ItemEffect_Trap(ItemStateBlock *self, int idx, void *arg) { /* 0x80051834 size:0x23C */
    float scale = lbl_806D26FC;
    int i;
    if (arg != 0) {
        ItemObjectPosView *o = (ItemObjectPosView *)arg;
        float mtx[16];
        float d[3];
        float dir[3];
        float *t = self->owner->movement->transform;
        for (i = 0; i < 16; i++) mtx[i] = t[i];
        {
            float *q = mtx;
            float *pd = d;
            float *pr = dir;
            {
                float dy = o->posY - q[13];
                float dx = o->posX - q[12];
                float dz = o->posZ - q[14];
                pd[0] = dx; pd[1] = dy; pd[2] = dz;
            }
            pr[0] = q[0]; pr[1] = q[1]; pr[2] = q[2];
            {
                float t0 = pr[0] * pd[0];
                float t1 = pr[1] * pd[1];
                float sum = t0 + t1;
                float t2 = pr[2] * pd[2];
                if (t2 + sum < lbl_806D26EC) scale = lbl_806D26E4;
            }
        }
        scale *= lbl_802ED7BC[idx].scaleB;
    }
    {
        KartMovementSpeedView *mv = self->owner->movement;
        float v[3];
        float w[3];
        float *vel = &mv->velX;
        w[0] = vel[0]; w[1] = vel[1]; w[2] = vel[2];
        { float *q = w; v[0] = q[0]; v[1] = q[1]; v[2] = q[2]; }
        {
            float k = lbl_806D2730; float *p = v;
            p[0] = p[0] * k; p[1] = p[1] * k; p[2] = p[2] * k;
        }
        {
            float k = lbl_802ED7BC[idx].scaleA; float *p = v;
            p[0] = p[0] * k; p[1] = p[1] * k; p[2] = p[2] * k;
        }
        ItemEffectDamp_TryArm(self->guard, v, lbl_802ED7BC[idx].mode, mv->accel1c8, scale);
    }
    {
        int a = lbl_802ED7BC[idx].valC;
        int b = lbl_802ED7BC[idx].valD;
        *(float *)((char *)self->owner->ownerDriver->itemBus + 0x28) = scale;
        self->activeId = a;
        self->activeFlag = b;
    }
}
#pragma exceptions reset

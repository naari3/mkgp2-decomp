#pragma exceptions off
typedef struct TrapScratch { float dir[3]; float d[3]; float mtx[16]; } TrapScratch;
typedef struct TrapVScratch { float w[3]; float v[3]; } TrapVScratch;
void ItemEffect_Trap(ItemStateBlock *self, int idx, void *arg) { /* 0x80051834 size:0x23C */
    float scale = lbl_806D26FC;
    int i;
    if (arg != 0) {
        ItemObjectPosView *o = (ItemObjectPosView *)arg;
        TrapScratch s;
        float *t = self->owner->movement->transform;
        for (i = 0; i < 16; i++) s.mtx[i] = t[i];
        {
            float dir0 = s.mtx[0];
            float dir1 = s.mtx[1];
            float dir2 = s.mtx[2];
            float dx, dy, dz;
            float t0, t1, sum, t2, dot;
            dy = o->posY - s.mtx[13];
            dx = o->posX - s.mtx[12];
            dz = o->posZ - s.mtx[14];
            s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
            s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
            t0 = dir0 * dx;
            t1 = dir1 * dy;
            sum = t0 + t1;
            t2 = dir2 * dz;
            dot = t2 + sum;
            if (dot < lbl_806D26EC) scale = lbl_806D26E4;
        }
        scale *= lbl_802ED7BC[idx].scaleB;
    }
    {
        KartMovementSpeedView *mv = self->owner->movement;
        TrapFxEntry *e = &lbl_802ED7BC[idx];
        TrapVScratch s;
        float *vel = &mv->velX;
        s.w[0] = vel[0]; s.w[1] = vel[1]; s.w[2] = vel[2];
        s.v[0] = s.w[0]; s.v[1] = s.w[1]; s.v[2] = s.w[2];
        {
            float k = lbl_806D2730; float *p = s.v;
            p[0] = p[0] * k; p[1] = p[1] * k; p[2] = p[2] * k;
        }
        {
            float k = e->scaleA; float *p = s.v;
            p[0] = p[0] * k; p[1] = p[1] * k; p[2] = p[2] * k;
        }
        ItemEffectDamp_TryArm(self->guard, s.v, e->mode, mv->accel1c8, scale);
    }
    *(float *)((char *)self->owner->ownerDriver->itemBus + 0x28) = scale;
    self->activeId = lbl_802ED7BC[idx].valC;
    self->activeFlag = lbl_802ED7BC[idx].valD;
}
#pragma exceptions reset

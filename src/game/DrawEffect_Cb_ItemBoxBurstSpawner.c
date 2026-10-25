typedef struct BurstEffect {
    unsigned char pad000[0x8C];
    float pos[3];                /* 0x08C */
    unsigned char pad098[4];
    float yaw;                   /* 0x09C */
} BurstEffect;

extern BurstEffect *DrawEffect_SpawnDirect(void (*callback)(BurstEffect *));
extern void DrawEffect_Cb_ItemBoxBurstFlash_Tick(BurstEffect *);
extern void DrawEffect_Cb_CircleFlare_Tick(BurstEffect *);
extern void DrawEffect_Free(void *);
extern void Vec3_Copy(float *dst, const float *src);
extern float BuildOrientationFromYaw(float angle);

void DrawEffect_Cb_ItemBoxBurstSpawner(BurstEffect *self)
{
    BurstEffect *e;
    float yaw;
    float step;
    int i;

    e = DrawEffect_SpawnDirect(DrawEffect_Cb_ItemBoxBurstFlash_Tick);
    if (e != 0) {
        Vec3_Copy(e->pos, self->pos);
    }
    yaw = 0.0f;
    step = 0.785398f;
    for (i = 0; i < 8; i++) {
        e = DrawEffect_SpawnDirect(DrawEffect_Cb_CircleFlare_Tick);
        if (e != 0) {
            Vec3_Copy(e->pos, self->pos);
            e->yaw = yaw;
        }
        yaw = BuildOrientationFromYaw(step + yaw);
    }
    DrawEffect_Free(self);
}

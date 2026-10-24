typedef struct RalySmokeEffect {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char pad014[0x8C - 0x14];
    float pos[3];                /* 0x08C */
    unsigned char pad098[0xB0 - 0x98];
    float scale;                 /* 0x0B0 */
    unsigned char pad0b4[0x11C - 0xB4];
    int owner;                   /* 0x11C */
} RalySmokeEffect;

extern RalySmokeEffect *DrawEffect_SpawnDirect(void (*callback)(RalySmokeEffect *));
extern void DrawEffect_Cb_RalySmokeVariant_Tick(RalySmokeEffect *);
extern void DrawEffect_Free(void *);
extern void Vec3_Copy(float *dst, const float *src);

void DrawEffect_Cb_RalySmokeSpawner_4Wheel(RalySmokeEffect *self)
{
    int i;

    for (i = 0; i < 4; i++) {
        RalySmokeEffect *e = DrawEffect_SpawnDirect(DrawEffect_Cb_RalySmokeVariant_Tick);
        if (e != 0) {
            e->variant = (signed char)i;
            Vec3_Copy(e->pos, self->pos);
            e->scale = self->scale;
            e->owner = self->owner;
        }
    }
    DrawEffect_Free(self);
}

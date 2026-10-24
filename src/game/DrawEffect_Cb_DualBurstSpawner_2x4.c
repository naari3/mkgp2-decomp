typedef struct DualBurstEffect {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char pad014[0x11C - 0x14];
    int owner;                   /* 0x11C */
} DualBurstEffect;

extern DualBurstEffect *DrawEffect_SpawnDirect(void (*callback)(DualBurstEffect *));
extern void DrawEffect_Cb_KartItem_Bind6E_3Phase(DualBurstEffect *);
extern void DrawEffect_Free(void *);

void DrawEffect_Cb_DualBurstSpawner_2x4(DualBurstEffect *self)
{
    int side;
    int i;

    for (side = 0; side < 2; side++) {
        for (i = 0; i < 4; i++) {
            DualBurstEffect *e = DrawEffect_SpawnDirect(DrawEffect_Cb_KartItem_Bind6E_3Phase);
            if (e != 0) {
                e->variant = (unsigned char)side;
                e->owner = self->owner;
            }
        }
    }
    DrawEffect_Free(self);
}

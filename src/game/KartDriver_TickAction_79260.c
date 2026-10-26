/* Forward to the kart's tire FX (KartTireFX_SetYaw) once the kart model is loaded. */
typedef struct KartDriver {
    void *model;           /* 0x000 */
    unsigned char pad004[0x8];
    void *loaded;          /* 0x00C */
    unsigned char pad010[0x2fc];
    void *tireFX;          /* 0x30C */
} KartDriver;

extern void KartTireFX_SetYaw(void *tireFX, float value);

int KartDriver_TickAction_79260(KartDriver *self, float value)
{
    if (self->model == 0 || self->loaded == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_SetYaw(self->tireFX, value);
    }
    return 1;
}

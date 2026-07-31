typedef struct KartEffectFadeTransit {
    unsigned char active;
    unsigned char pad[3];
    void *owner;
    void *effect;
    void *camera;
    float value;
    float target;
    unsigned int timer;
} KartEffectFadeTransit;

unsigned int KartEffectFadeTransit_GetActiveValue(KartEffectFadeTransit *self)
{
    return self->timer;
}

unsigned char KartEffectFadeTransit_IsActive(KartEffectFadeTransit *self)
{
    return self->timer != 0;
}

typedef struct EffectActor {
    unsigned char _pad[0xEC];
    void* kart;
    void* target;
} EffectActor;

void EffectActor_BindKartTargetPair(EffectActor* self, void* kart, void* target)
{
    self->kart = kart;
    self->target = target;
}

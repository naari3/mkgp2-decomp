class EffectResource {
public:
    virtual void v0();
    virtual void Release();
    virtual void Update();
};

struct EffectKart {
    unsigned char pad[0x9C];
    float baseSpeed;
};

struct EffectSpeed {
    EffectKart *kart;
    unsigned char pad_04[8];
    int target;
    int current;
    int step;
    unsigned char ramping;
    unsigned char pad_19[3];
    int handle;
    EffectResource *resource;
    unsigned char pad_24[0x20];
    float speed;
};

static inline unsigned char ramp(EffectSpeed *effect) {
    if (effect->ramping == 0) {
        return 0;
    }
    effect->current += effect->step;
    if (effect->step > 0) {
        if (effect->target < effect->current) {
            effect->ramping = 0;
            effect->current = effect->target;
        }
    } else {
        if (effect->target > effect->current) {
            effect->ramping = 0;
            effect->current = effect->target;
        }
    }
    return effect->ramping;
}

extern "C" float EffectSpeed_TickAndGet(EffectSpeed *effect) {
    if (effect->handle == 0) {
        return effect->kart->baseSpeed;
    }
    effect->resource->Update();
    if (!ramp(effect)) {
        if (effect->resource != 0) {
            effect->resource->Release();
        }
        effect->resource = 0;
        effect->handle = 0;
        return effect->kart->baseSpeed;
    }
    return effect->speed;
}

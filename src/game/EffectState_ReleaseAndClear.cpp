class EffectResource {
public:
    virtual void v0();
    virtual void Release();
};

struct EffectState {
    unsigned char pad[0x1C];
    int handle;
    EffectResource *resource;
};

extern "C" void EffectState_ReleaseAndClear(EffectState *state) {
    if (state->resource != 0) {
        state->resource->Release();
    }
    state->resource = 0;
    state->handle = 0;
}

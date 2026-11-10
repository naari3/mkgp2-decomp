class EffectResource {
public:
    virtual void v0();
    virtual void Release();
};

#include "game/types/EffectState.h"

extern "C" void EffectState_ReleaseAndClear(EffectState *state) {
    if (state->resource != 0) {
        state->resource->Release();
    }
    state->resource = 0;
    state->content = 0;
}

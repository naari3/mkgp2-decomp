#ifndef TRANSITION_EFFECT_PRIVATE_H
#define TRANSITION_EFFECT_PRIVATE_H

struct TransitionFade { float remaining, delay; };
struct TransitionIris {
    unsigned char closing;
    float remaining, radius, step;
    unsigned int unused, alpha;
};
struct TransitionFlash { float remaining; unsigned char active; float r, g, b, alpha; };
struct TransitionQuad { unsigned char active; float r, g, b, alpha; };
struct TransitionOverlayObject {
    void *object;
    ~TransitionOverlayObject() throw();
};
struct TransitionRoulette {
    TransitionOverlayObject holder;
    float remaining, speed, fade;
    int phase;
    float elapsed;
    unsigned char active;
};
struct TransitionEffectView {
    void **vtable;
    TransitionFade *fade;
    TransitionIris *iris;
    float *shake;
    TransitionFlash *flash;
    TransitionQuad *quad;
    TransitionRoulette *roulette;
    int mode;
    float duration;
    unsigned char active;
    unsigned char rest[0x4F];
};

#endif

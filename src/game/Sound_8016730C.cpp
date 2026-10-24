/*
 * 0x8016730C..0x801674AC: small sound-handle wrappers (stop / restart with
 * fixed fade parameters).
 */

struct SndHandle {
    virtual ~SndHandle();
    virtual void Stop();
};

typedef struct SndVoice {
    char pad00[0x1C];
    float fadeIn;
    float fadeOut;
    float vol24;
    float vol28;
} SndVoice;

typedef struct SndSlot8 {
    int id;
    SndHandle *handle;
    SndVoice *voice;
} SndSlot8;

typedef struct SndSlot4 {
    int id;
    SndVoice *voice;
} SndSlot4;

static inline void SndVoice_SetVol(SndVoice *v, float a, float b) {
    v->vol24 = a;
    v->vol28 = b;
}

static inline void SndVoice_SetFade(SndVoice *v, float a, float b) {
    v->fadeIn = a;
    v->fadeOut = b;
}

extern "C" {
extern void fn_80201148(SndVoice *);
extern SndVoice *fn_802011D0(int, int);
extern void fn_801FFFF4(SndVoice *);
extern SndVoice *fn_8020007C(int, int, int);

#pragma exceptions on

void fn_8016730C(void) {
}

void fn_80167310(SndSlot8 *self) {
    if (self->voice) {
        fn_80201148(self->voice);
    }
}

void fn_8016733C(SndSlot8 *self) {
    if (self->voice) {
        self->handle->Stop();
    }
    self->voice = fn_802011D0(self->id, 0);
    SndVoice_SetVol(self->voice, 89.0f, 458.0f);
}

void fn_801673A8(SndSlot4 *self) {
    if (self->voice) {
        fn_801FFFF4(self->voice);
    }
}

void fn_801673D4(SndSlot4 *self) {
    if (self->voice) {
        ((SndHandle *)self->voice)->Stop();
    }
    self->voice = fn_8020007C(0, self->id, 0);
    SndVoice_SetFade(self->voice, 315.0f, 457.0f);
}

void fn_80167440(SndSlot4 *self) {
    if (self->voice) {
        ((SndHandle *)self->voice)->Stop();
    }
    self->voice = fn_8020007C(1, self->id, 0);
    SndVoice_SetFade(self->voice, 315.0f, 457.0f);
}

#pragma exceptions reset
}

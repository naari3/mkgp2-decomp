/*
 * 0x801674AC..0x80167744: two-voice ambient player (tick / update /
 * deleting destructor / init).
 */

struct AmbVoice {
    virtual ~AmbVoice();
    virtual void Release();
    virtual void Start();
    virtual void Play();

    int id;
    int delay;
    int state;

    bool Tick() {
        if (delay > 0) {
            delay--;
            return 0;
        }
        if (state == 1) {
            state = 2;
        }
        return state <= 0;
    }

    bool IsIdle() {
        if (delay > 0) {
            return 0;
        }
        return state <= 0;
    }
};

struct AmbPair {
    int id;
    AmbVoice *a;
    AmbVoice *b;
};

extern "C" {
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

void fn_801674AC(AmbPair *self) {
    if (self->a) {
        if (self->a->Tick()) {
            self->a->Play();
        }
    }
    if (self->b) {
        if (self->b->Tick()) {
            self->b->Play();
        }
    }
}

void fn_801675A4(AmbPair *self) {
    if (self->a) {
        if (self->a->IsIdle()) {
            self->a->Start();
        }
        if (self->a->state >= 2) {
            self->a->Release();
            self->a = 0;
        }
    }
    if (self->b) {
        if (self->b->IsIdle()) {
            self->b->Start();
        }
        if (self->b->state >= 2) {
            self->b->Release();
            self->b = 0;
        }
    }
}

AmbPair *fn_801676AC(AmbPair *self, short flag) {
    if (self) {
        if (self->a) {
            self->a->Release();
        }
        if (self->b) {
            self->b->Release();
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_80167730(AmbPair *self, int id) {
    self->id = id;
    self->a = 0;
    self->b = 0;
}

#pragma exceptions reset
}

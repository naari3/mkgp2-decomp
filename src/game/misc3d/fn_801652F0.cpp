struct Disp {
    virtual ~Disp();
    virtual void Release();
    virtual void Start();
    virtual void Play();

    int id;
    int wait;
    int state;

    bool IsIdle() {
        if (wait > 0) {
            return 0;
        }
        return state <= 0;
    }
};

struct DispImpl : Disp {
    DispImpl(int a, int b);
    unsigned char pad[0x7c - 0x10];
};

struct Scene801652F0 {
    int pad0;
    unsigned char hidden;
    unsigned char pad5[3];
    unsigned char ready;
    unsigned char pad9[3];
    unsigned int mode;
    Disp *disp;
};

extern "C" {
void fn_80121210(void);
}

extern "C" void fn_801652F0(Scene801652F0 *s) {
    if (s->hidden != 0) return;
    if (s->ready == 0) s->ready = 1;
    if (s->mode == 11) {
        if (s->disp == 0) s->disp = new DispImpl(0, 0);
        if (s->disp == 0) return;
        if (s->disp->state >= 2) {
            s->disp->Release();
            s->disp = 0;
            fn_80121210();
            return;
        }
        if (s->disp->IsIdle()) s->disp->Start();
    } else {
        if (s->disp == 0) {
            s->hidden = 1;
            return;
        }
        if (s->disp->state >= 2) {
            s->hidden = 1;
            return;
        }
        if (s->disp->IsIdle()) s->disp->Start();
    }
}

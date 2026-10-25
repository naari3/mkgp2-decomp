struct Disp {
    virtual ~Disp();
    virtual void Release();
    virtual void Start();
    virtual void Play();

    int id;
    int wait;
    int state;

    bool Tick() {
        if (wait > 0) {
            wait--;
            return 0;
        }
        if (state == 1) {
            state = 2;
        }
        return state <= 0;
    }
};

struct Scene8016504C {
    int pad0;
    unsigned char hidden;
    unsigned char pad5[3];
    unsigned char ready;
    unsigned char pad9[3];
    unsigned int mode;
    Disp *disp;
};

extern "C" {
void fn_8011F994(int on);
void fn_801493B0(Disp *d);
void fn_8013DA00(void);
void fn_8011FAB8(void);
void HSD_StateInvalidate(int state);
}

extern "C" void fn_8016504C(Scene8016504C *s) {
    if (s->hidden != 0) return;
    if (s->ready == 0) return;
    switch (s->mode) {
    case 0:
        if (s->disp->Tick()) {
            s->disp->Play();
            fn_8011F994(0);
            fn_801493B0(s->disp);
            fn_8011F994(1);
        }
        break;
    case 2:
        if (s->disp->Tick()) {
            s->disp->Play();
            fn_8011F994(0);
            fn_8011F994(1);
        }
        break;
    case 5:
        if (s->disp->Tick()) {
            s->disp->Play();
            fn_8011F994(0);
            fn_8013DA00();
            fn_8011F994(1);
        }
        break;
    case 11:
        if (s->disp != 0 && s->disp->Tick()) {
            s->disp->Play();
        }
        break;
    default:
        if (s->disp->Tick()) {
            s->disp->Play();
        }
        break;
    }
    fn_8011FAB8();
    HSD_StateInvalidate(-1);
}

/* Card flow tick: forwards to the handler for the current sub-state. */
class CardHandler {
public:
    virtual void v8();
    virtual void vC();
    virtual void Update();
};

struct CardSprites {
    void *anim0;
    void *anim1;
    unsigned char visible;
};

struct CardFlow {
    void *vt;
    char pad_4[4];
    CardSprites *sprites;
    void *state0;
    void *state1;
    void *state2;
    CardHandler *state3;
    int state;
    void *state4;
    void *state5;
};

extern "C" {
extern char lbl_8039A2E8[];
void fn_801A0004(void *anim);
void fn_801BB474(void *table, int a, int b);
void fn_801C0A0C(void *p);
void fn_801C0060(void *p);
void fn_801BDB60(void *p);
void fn_801BCDAC(void *p);
void fn_801BB6D4(void *p);
}

extern "C" void fn_801BA9A0(CardFlow *self) {
    CardSprites *sprites = self->sprites;

    if (sprites->visible) {
        fn_801A0004(sprites->anim0);
        fn_801A0004(sprites->anim1);
        fn_801BB474(lbl_8039A2E8, 2, 5);
    }
    if (self->state == 0) {
        fn_801C0A0C(self->state0);
    } else if (self->state == 1) {
        fn_801C0060(self->state1);
    } else if (self->state == 2) {
        fn_801BDB60(self->state2);
    } else if (self->state == 3) {
        self->state3->Update();
    } else if (self->state == 4) {
        fn_801BCDAC(self->state4);
    } else if (self->state == 5) {
        fn_801BB6D4(self->state5);
    }
}

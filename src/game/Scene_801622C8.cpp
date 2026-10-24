/* 0x801622C8..0x8016234C: per-frame hook of a scene with an 8-slot table. */

struct VObjPad {
    char pad[0x14];
};

struct Model : VObjPad {
    virtual ~Model();
    virtual void M1();
    virtual void M2();
    virtual void M3();
    virtual void M4();
    virtual void Draw();
};

struct Scene801622C8 {
    void *vtable;
    unsigned char disabled;
    char pad05[3];
    Model *model;
    char pad0C[4];
    unsigned char active;
};

extern "C" {
extern void fn_8011F994(int);
extern void fn_802C14B8(int);

#pragma exceptions on

void fn_801622C8(Scene801622C8 *self) {
    int i;
    if (!self->disabled && self->active == 1) {
        for (i = 0; i < 8; i++) {
            fn_8011F994(i);
        }
        if (self->model) {
            self->model->Draw();
        }
        fn_802C14B8(-1);
    }
}

#pragma exceptions reset
}

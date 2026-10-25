extern void fn_801A0004(void *obj);
extern void *fn_801A1174(int id, int a, int b, int c, int d);
extern void *fn_801A1128(void *obj, float x, float y);
extern void fn_801A0DF0(void *obj);

extern const float lbl_806DA210;
extern const float lbl_806DA214;
extern const float lbl_806DA218;
extern const float lbl_806DA21C;
extern const float lbl_806DA220;
extern const float lbl_806DA224;

typedef struct ItemFx {
    char pad0[0x8];
    float timer;
    char padC[0x14];
    void *fx20;
    void *fx24;
    void *fx28;
    void *fx2C;
    void *fx30;
} ItemFx;

void fn_801DA46C(ItemFx *self) {
    if (self->fx20 != 0) {
        fn_801A0004(self->fx20);
    }
    if (self->fx2C != 0) {
        fn_801A0004(self->fx2C);
    } else {
        fn_801A0DF0(fn_801A1128(fn_801A1174(0x1E86, 4, 0, 0, 0), lbl_806DA210, lbl_806DA214));
        fn_801A0DF0(fn_801A1128(fn_801A1174(0x1B4C, 4, 0, 0, 0), lbl_806DA210, lbl_806DA218));
        if (self->fx30 != 0) {
            fn_801A0DF0(fn_801A1128(fn_801A1174(0x1597, 4, 0, 0, 0), lbl_806DA21C, lbl_806DA220));
            fn_801A0004(self->fx30);
        }
    }
    if (self->fx24 != 0) {
        fn_801A0004(self->fx24);
    }
    if (self->timer < lbl_806DA224 && self->fx28 != 0) {
        fn_801A0004(self->fx28);
    }
}

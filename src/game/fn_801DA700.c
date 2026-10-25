typedef struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
} InputView;

typedef struct AttractFlow {
    void *vt;
    char pad_4;
    signed char kind;
    char pad_6[0x1A];
    void *sprites[5];
} AttractFlow;

extern InputView *g_pInputState;
extern void *lbl_8049BC08[];
extern int lbl_8049BBE8[];
extern const float lbl_806DA234;
extern void MemoryManager_TimedFree(void *p);
extern void SetScreenBrightness(float level);
extern void Sprite_Destroy(void *sprite, int flag);
extern void Sprite_SetAnimParam(void *sprite, short id, int value);
extern void dtor_801BA14C(void *self, int flag);
extern void fn_80120A08(int id);
extern void fn_801699D8(int a, int b);
extern void fn_80169C44(void);

static inline InputView *input_state(void) {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

AttractFlow *fn_801DA700(AttractFlow *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8049BC08;
        if (input_state()) {
            InputView *input = input_state();
            input->enabled = 0;
            input->held = 0;
            input->edge = 0;
        }
        fn_801699D8(0, 0);
        fn_801699D8(1, 0);
        fn_80169C44();
        fn_80120A08(0x1B4C);
        fn_80120A08(0x1E86);
        Sprite_SetAnimParam(self->sprites[1], lbl_8049BBE8[self->kind], 0x1B18);
        Sprite_Destroy(self->sprites[0], 1);
        Sprite_Destroy(self->sprites[1], 1);
        Sprite_Destroy(self->sprites[2], 1);
        Sprite_Destroy(self->sprites[3], 1);
        Sprite_Destroy(self->sprites[4], 1);
        SetScreenBrightness(lbl_806DA234);
        dtor_801BA14C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

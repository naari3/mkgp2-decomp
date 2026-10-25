typedef struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
} InputView;

typedef struct EntryFlow {
    void *vt;
    char pad_4[4];
    int kind;
    char pad_C[8];
    void *sprite14;
    void *sprite18;
    void *anim1C;
} EntryFlow;

extern InputView *g_pInputState;
extern void *lbl_8049A878[];
extern int lbl_8049A858[];
extern const float lbl_806D9980;
extern void MemoryManager_TimedFree(void *p);
extern void SetScreenBrightness(float level);
extern void Sprite_Destroy(void *sprite, int flag);
extern void Sprite_SetAnimParam(void *sprite, short id, int value);
extern void dtor_801BA14C(void *self, int flag);
extern void fn_80161F28(void *anim, int flag);
extern void fn_801699D8(int a, int b);
extern void fn_80169C44(void);

static inline InputView *input_state(void) {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

EntryFlow *fn_801BA6A4(EntryFlow *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8049A878;
        fn_801699D8(0, 0);
        fn_801699D8(1, 0);
        fn_80169C44();
        if (input_state()) {
            InputView *input = input_state();
            input->enabled = 0;
            input->held = 0;
            input->edge = 0;
        }
        if (self->sprite14 != 0) {
            Sprite_SetAnimParam(self->sprite14, lbl_8049A858[self->kind], 0x1B18);
        }
        fn_80161F28(self->anim1C, 1);
        Sprite_Destroy(self->sprite14, 1);
        Sprite_Destroy(self->sprite18, 1);
        SetScreenBrightness(lbl_806D9980);
        dtor_801BA14C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

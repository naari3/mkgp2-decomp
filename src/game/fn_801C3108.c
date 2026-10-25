typedef struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
} InputView;

typedef struct ClassFlow {
    void *vt;
    char pad_4[0x28];
    void *sprites[4];
} ClassFlow;

extern InputView *g_pInputState;
extern int g_ccClass;
extern int g_gameMode;
extern void *lbl_8049AA0C[];
extern const float lbl_806D9AF8;
extern void MemoryManager_TimedFree(void *p);
extern void SetScreenBrightness(float level);
extern void Sprite_Destroy(void *sprite, int flag);
extern unsigned char *SyncSlot_GetRecv(void);
extern void dtor_801BA14C(void *self, int flag);
extern void fn_80120A08(int id);
extern void fn_80169C44(void);
extern void fn_801A1678(void);
extern void fn_801B7B04(int arg);

static inline InputView *input_state(void) {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

ClassFlow *fn_801C3108(ClassFlow *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8049AA0C;
        fn_801B7B04(1);
        if (input_state()) {
            InputView *input = input_state();
            input->enabled = 0;
            input->held = 0;
            input->edge = 0;
        }
        SetScreenBrightness(lbl_806D9AF8);
        fn_80169C44();
        fn_80120A08(0x166F);
        fn_80120A08(0x1AE0);
        fn_80120A08(0x1ADF);
        fn_80120A08(0x1ADE);
        fn_80120A08(0x1666);
        fn_80120A08(0x1B12);
        fn_80120A08(0x1B13);
        Sprite_Destroy(self->sprites[3], 1);
        Sprite_Destroy(self->sprites[2], 1);
        Sprite_Destroy(self->sprites[1], 1);
        Sprite_Destroy(self->sprites[0], 1);
        fn_801A1678();
        if (g_gameMode == 2) {
            g_ccClass = (SyncSlot_GetRecv()[1] >> 1) & 3;
        }
        dtor_801BA14C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

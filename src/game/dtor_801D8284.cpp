class Deletable {
public:
    virtual ~Deletable();
};

struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0x13];
    int value18;
    int value1C;
};

struct SceneObject {
    void *vtbl;
    unsigned char pad_04[0x18];
    Deletable *child;
    void *lobjList;
    void *driverA;
    void *driverB;
    unsigned char pad_2C[0x3C];
    void *sprites[3];
    void *sprites2[3];
    void *buffer;
};

extern "C" {
extern char lbl_8049BBD0[];
extern InputState *g_pInputState;
void fn_80169C44(void);
void SetScreenBrightness(float);
void Sprite_Destroy(void *, int);
void KartDriver_Dtor(void *, int);
void LObjList_Destroy(void *, int);
void MemoryManager_TimedFree(void *);
void fn_80120A08(int);
void dtor_801BA14C(void *, int);
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

extern "C" SceneObject *dtor(SceneObject *self, short flags) {
    if (self != 0) {
        self->vtbl = lbl_8049BBD0;
        fn_80169C44();
        if (input_state() != 0) {
            InputState *state = input_state();

            state->active = 0;
            state->value18 = 0;
            state->value1C = 0;
        }
        SetScreenBrightness(-1.0f);
        Sprite_Destroy(self->sprites[0], 1);
        Sprite_Destroy(self->sprites[1], 1);
        Sprite_Destroy(self->sprites[2], 1);
        KartDriver_Dtor(self->driverA, 1);
        KartDriver_Dtor(self->driverB, 1);
        delete self->child;
        LObjList_Destroy(self->lobjList, 1);
        Sprite_Destroy(self->sprites2[0], 1);
        Sprite_Destroy(self->sprites2[1], 1);
        Sprite_Destroy(self->sprites2[2], 1);
        if (self->buffer != 0) {
            MemoryManager_TimedFree(self->buffer);
        }
        fn_80120A08(0x167F);
        dtor_801BA14C(self, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

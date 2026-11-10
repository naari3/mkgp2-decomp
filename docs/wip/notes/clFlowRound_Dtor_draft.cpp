struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0x13];
    int value18;
    int value1C;
};

struct RoundSlot {
    void *sprite;
    int pad[4];
};

struct RoundOwned {
    void *sprite;
};

struct clFlowRound {
    void *vtbl;
    unsigned char pad_04[0x24];
    void *sprite28;
    unsigned char pad_2C[0x10];
    RoundSlot slots[4];
    unsigned char pad_8C[0x60];
    void *spriteEC;
    void *spriteF0;
    unsigned char pad_F4[0x68];
    void *sprite15C;
    void *sprite160;
    unsigned char pad_164[4];
    RoundOwned *owned;
};

struct RoundTable {
    unsigned char pad_000[0x11C];
    short cupSlot[10];
    short bgmIds[14];
    unsigned char vtbl[4];
};

extern "C" {
extern RoundTable clFlowRound_data_8049AE70;
extern short clFlowRound_data_806CFDF0;
extern const float lbl_806D9D48;
extern InputState *g_pInputState;
extern int g_cupId;
void fn_80169C44(void);
void SetScreenBrightness(float);
void Sprite_Destroy(void *, int);
void MemoryManager_TimedFree(void *);
void fn_80120A08(int);
void fn_801A1678(void);
void dtor_801BA14C(void *, int);
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

extern "C" clFlowRound *clFlowRound_Dtor(clFlowRound *self, short flags) {
    RoundTable *tbl = &clFlowRound_data_8049AE70;
    RoundOwned *owned;
    int i;

    if (self != 0) {
        self->vtbl = tbl->vtbl;
        fn_80169C44();
        if (input_state() != 0) {
            InputState *state = input_state();

            state->active = 0;
            state->value18 = 0;
            state->value1C = 0;
        }
        SetScreenBrightness(lbl_806D9D48);
        fn_80120A08(tbl->bgmIds[tbl->cupSlot[g_cupId]]);
        fn_80120A08(clFlowRound_data_806CFDF0);
        Sprite_Destroy(self->sprite160, 1);
        Sprite_Destroy(self->sprite15C, 1);
        Sprite_Destroy(self->spriteEC, 1);
        Sprite_Destroy(*(void **)((char *)self + 0x88), 1);
        Sprite_Destroy(self->sprite28, 1);
        Sprite_Destroy(self->spriteF0, 1);
        {
            owned = self->owned;

            if (owned != 0) {
                Sprite_Destroy(owned->sprite, 1);
                MemoryManager_TimedFree(owned);
            }
        }
        for (i = 0; i < 4; i++) {
            Sprite_Destroy(self->slots[i].sprite, 1);
        }
        fn_801A1678();
        dtor_801BA14C(self, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

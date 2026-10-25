extern void SetAnimSpin(int obj);
extern const float lbl_806DA42C;
extern const float lbl_806DA46C;

typedef struct SpinState {
    char pad_0[8];
    int animObj;
    char pad_C[0x98];
    unsigned char enabled;
    unsigned char spinning;
    char pad_A6[6];
    float spinTime;
    float unkB0;
    float vel[3];
    int hitTimer;
} SpinState;

void fn_801ECB04(SpinState *self) {
    unsigned char busy;

    if (self->enabled) {
        busy = 0;
        if (self->spinning || self->hitTimer > 0) {
            busy = 1;
        }
        if (!busy) {
            self->spinning = 1;
            SetAnimSpin(self->animObj);
            self->spinTime = lbl_806DA46C;
            self->vel[0] = lbl_806DA42C;
            self->vel[1] = lbl_806DA42C;
            self->vel[2] = lbl_806DA42C;
        }
    }
}

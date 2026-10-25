typedef struct WpPair {
    int a;
    int b;
} WpPair;

typedef struct DriveState {
    char pad00[8];
    int pendingA;
    int pendingB;
    int boost;
    char pad14[4];
    float speedScale;
    float accel;
    char pad20[4];
    float steer;
    char pad28[0x48];
    char queue[1];
} DriveState;

extern void *fn_801DB8F0(void);
extern int fn_801DB830(void *self, int idx);
extern int fn_801DB8A4(void *self, int idx);
extern int fn_801DB890(void *self, int idx);
extern void fn_801E2DF0(void *queue);
extern void fn_801E2FD4(void *queue, WpPair *pair);
extern const int lbl_803BD0FC[];
extern float lbl_806D18F4;
extern float lbl_806D18F8;
extern const float lbl_806D18FC;

void fn_801DEAF4(DriveState *self, int wp) {
    WpPair q;
    WpPair p;

    if (self->pendingA != 0) {
        self->pendingB = 0;
        self->pendingA = 0;
        fn_801E2DF0(self->queue);
    }
    if (self->pendingB <= 0 && self->pendingA == 0) {
        switch (fn_801DB830(fn_801DB8F0(), wp)) {
        case 3:
        case 4:
            self->boost = 1;
            self->speedScale = 0.0f;
            self->accel = lbl_806D18FC;
            break;
        case 5:
            self->speedScale = lbl_806D18F4;
            break;
        case 6:
            self->speedScale = lbl_806D18F8;
            break;
        case 11:
            self->steer = 0.0f;
            break;
        case 10:
            break;
        }
        p.b = fn_801DB8A4(fn_801DB8F0(), wp);
        p.a = wp;
        fn_801E2FD4(self->queue, &p);
        q.b = lbl_803BD0FC[fn_801DB890(fn_801DB8F0(), wp)];
        q.a = 0;
        fn_801E2FD4(self->queue, &q);
        self->pendingB = q.b;
        self->pendingA = q.a;
    }
}

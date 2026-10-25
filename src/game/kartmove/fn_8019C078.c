typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SuspParam {
    float pad0;
    float target;
    float rateUp;
    float rateDown;
    unsigned char pad10[8];
} SuspParam;

typedef struct Car {
    unsigned char pad0[0x6c];
    float speed;
    unsigned char pad70[0x254 - 0x70];
    unsigned char active[4];
    Vec3 corner[4];
    float susp[4];
} Car;

extern SuspParam lbl_804963F8[];
extern const float lbl_806D96D0;
extern const float lbl_806D9740;
extern double __fabs(double);

void fn_8019C078(Car *car) {
    int i;
    if (car->speed < lbl_806D96D0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        float v = car->susp[i];
        if (car->active[i] == 1) {
            SuspParam *p = &lbl_804963F8[i >> 1];
            float *tgt = &p->target;
            float d = *tgt - v;
            if (d < lbl_806D96D0) {
                v = d * p->rateDown + v;
                if (v < *tgt || (float)__fabs(v - *tgt) < lbl_806D9740) {
                    v = *tgt;
                }
            } else {
                v = d * p->rateUp + v;
                if (v > *tgt || (float)__fabs(v - *tgt) < lbl_806D9740) {
                    v = *tgt;
                }
            }
            car->susp[i] = v;
            car->corner[i].y += v;
        }
    }
}

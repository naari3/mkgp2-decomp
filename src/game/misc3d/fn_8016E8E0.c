typedef struct { float x, y, z; } Vec3;
typedef float Mtx[3][4];

typedef struct Kart {
    char pad[0x1f8];
    int kind;
} Kart;

typedef struct Gate {
    int pad0;
    int state;
    Vec3 *pos;
    float t;
} Gate;

extern Kart *GetKartSlotKartVariant(int slot);
extern Mtx *KartDriver_GetKartRootMtx(Kart *k);
extern void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern float PSVECSquareMag(const Vec3 *v);
extern const float lbl_806D8BA8;
extern const float lbl_806D8BAC;
extern const float lbl_806D8BB0;
extern const float lbl_806D8BB4;
extern const float lbl_806D8BB8;
extern const float lbl_806D8BBC;
extern const float lbl_806D8BC0;
extern const float lbl_806D8BC4;
extern const float lbl_806D8BC8;
extern const float lbl_806D8BCC;

void fn_8016E8E0(Gate *g) {
    Kart *k;
    unsigned char near = 0;
    int i;
    Vec3 v;
    float nt;
    for (i = 0; i < 8; i++) {
        k = GetKartSlotKartVariant(i);
        if (k != 0 && k->kind == 4) {
            v.x = (*KartDriver_GetKartRootMtx(k))[0][3];
            v.y = (*KartDriver_GetKartRootMtx(k))[1][3];
            v.z = (*KartDriver_GetKartRootMtx(k))[2][3];
            Vec3_Subtract(&v, g->pos, &v);
            if (PSVECSquareMag(&v) < lbl_806D8BB4) near = 1;
            break;
        }
    }
    switch (g->state) {
    case 0:
        if (near) {
            g->state = 1;
            g->t = lbl_806D8BB8;
        } else {
            nt = g->t + lbl_806D8BAC; g->t = nt;
            if (nt > lbl_806D8BBC) g->t = lbl_806D8BA8;
        }
        break;
    case 1:
        nt = g->t + lbl_806D8BAC; g->t = nt;
        if (nt > lbl_806D8BB0) {
            g->state = 2;
            g->t = lbl_806D8BC0;
        }
        break;
    case 2:
        if (!near) {
            g->state = 3;
            g->t = lbl_806D8BC4;
        } else {
            nt = g->t + lbl_806D8BAC; g->t = nt;
            if (nt > lbl_806D8BC8) g->t = lbl_806D8BC0;
        }
        break;
    case 3:
        nt = g->t + lbl_806D8BAC; g->t = nt;
        if (nt > lbl_806D8BCC) {
            g->state = 0;
            g->t = lbl_806D8BA8;
        }
        break;
    default:
        g->state = 0;
        g->t = lbl_806D8BA8;
        break;
    }
}

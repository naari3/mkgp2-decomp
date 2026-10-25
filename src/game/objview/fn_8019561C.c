typedef struct Inner {
    struct Inner *next;
} Inner;

typedef struct Outer {
    struct Outer *next;
    unsigned char pad[4];
    Inner *list;
} Outer;

typedef struct Area {
    void *vt;
    Outer *groups;
    int mode;
    unsigned char inside;
} Area;

extern void *g_playerRenderObj;
extern const float lbl_8037D800[4];
extern unsigned char IsRaceStarted(void);
extern float (*KartDriver_GetKartRootMtx(void *kart))[4];

void fn_8019561C(Area *a) {
    void *kart;
    float (*m)[4];
    Outer *g;
    Inner *e;

    if (a->mode == 8) {
        if ((kart = g_playerRenderObj) != 0 && IsRaceStarted() == 1) {
            m = KartDriver_GetKartRootMtx(kart);
            a->inside = 1;
            if (m[0][3] < lbl_8037D800[0]) return;
            if (m[0][3] > lbl_8037D800[1]) return;
            if (m[2][3] < lbl_8037D800[2]) return;
            if (m[2][3] > lbl_8037D800[3]) return;
        }
        a->inside = 0;
        for (g = a->groups; g != 0; g = g->next) {
            for (e = g->list; e != 0; e = e->next) {
            }
        }
    } else {
        Inner *e2;
        Outer *g2;
        for (g2 = a->groups; g2 != 0; g2 = g2->next) {
            for (e2 = g2->list; e2 != 0; e2 = e2->next) {
            }
        }
    }
}

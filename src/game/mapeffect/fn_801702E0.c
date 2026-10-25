typedef struct Spark {
    unsigned char active;
    unsigned char pad[3];
    int timer;
    int value;
} Spark;

typedef struct SparkGen {
    int pad0[2];
    int range;
    int padc;
    void *model;
    int pad14[4];
    Spark sparks[5];
    int cooldown;
    int idx;
} SparkGen;

extern const float lbl_80495994[64];
extern const float lbl_806D8CD0;

void fn_801702E0(SparkGen *g) {
    int i;
    int j;
    int v;
    unsigned char found;
    Spark *s;
    if (g->model == 0) return;
    for (i = 0; i < 5; i++) {
        s = &g->sparks[i];
        if (s->active) {
            if (++s->timer > 0x50) s->active = 0;
        } else if (g->cooldown == 0) {
            v = (int)((float)g->range * lbl_80495994[g->idx]);
            found = 0;
            for (j = 0; j < 5; j++) {
                if (g->sparks[j].active && g->sparks[j].value == v) found = 1;
            }
            if (!found) {
                s->active = 1;
                s->timer = 0;
                s->value = v;
                g->cooldown = 5;
                g->cooldown = (int)(lbl_806D8CD0 * lbl_80495994[g->idx]);
            }
        }
    }
    g->idx++;
    if (g->idx >= 0x40) g->idx = 0;
    if (g->cooldown > 0) g->cooldown--;
}

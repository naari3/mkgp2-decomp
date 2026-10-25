typedef struct SpeedPt {
    float key;
    float speed;
} SpeedPt;

typedef struct SpeedTable {
    SpeedPt *pts;
    int count;
    float ref;
    unsigned char pad[0xc];
} SpeedTable;

typedef struct KartMove {
    unsigned char pad0[8];
    int table;
    unsigned char padc[0x22 - 0xc];
    unsigned char limited;
    unsigned char pad23;
    SpeedTable *tables;
} KartMove;

extern const float lbl_806D96D0;
extern const float lbl_806D96D4;
extern const float lbl_806D96D8;
extern const float lbl_806D96DC;
extern double __fabs(double);

static inline float LookupSpeed(KartMove *k) {
    int i;
    float s = lbl_806D96D0;
    for (i = 0; i < k->tables[k->table].count; i++) {
        SpeedTable *t = &k->tables[k->table];
        if ((float)__fabs(t->pts[i].key - t->ref) < lbl_806D96D4) {
            s = k->tables[k->table].pts[i].speed;
            break;
        }
    }
    if (k->limited == 1 && s >= lbl_806D96D8) {
        s = lbl_806D96D8;
    }
    return s;
}

float KartMovement_CalcMaxSpeed(KartMove *k) {
    return lbl_806D96DC * LookupSpeed(k);
}

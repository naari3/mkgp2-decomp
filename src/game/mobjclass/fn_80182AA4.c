typedef struct TObjView {
    unsigned char pad[0x74];
    float mtx[3][4];
} TObjView;

typedef struct DObjView {
    void *parent;
    struct DObjView *next;
    void *mobj;
} DObjView;

extern const float lbl_806D927C;
extern void PSMTXTrans(float m[3][4], float x, float y, float z);
extern void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);
extern TObjView *HSD_MObjGetTObj(void *mobj);

static inline void *DObjGetMObj(DObjView *dobj) {
    return dobj ? dobj->mobj : 0;
}

static inline void TObjTranslate(TObjView *tobj, float x, float y) {
    float m[3][4];
    if (tobj != 0) {
        PSMTXTrans(m, x, y, lbl_806D927C);
        PSMTXConcat(m, tobj->mtx, tobj->mtx);
    }
}

void fn_80182AA4(DObjView *dobj, float x, float y) {
    for (; dobj != 0; dobj = dobj->next) {
        TObjTranslate(HSD_MObjGetTObj(DObjGetMObj(dobj)), x, y);
    }
}

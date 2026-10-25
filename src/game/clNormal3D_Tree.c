/* JObj tree walkers for clNormal3D, 0x80030D48..0x80031408: texture matrix
 * offset and recursive render-mode flag set. */
typedef float Mtx[3][4];

typedef struct TObjView {
    unsigned char pad00[0x4C];
    unsigned int flags; /* 0x4C */
    unsigned char pad50[0x24];
    Mtx mtx; /* 0x74 */
} TObjView;

typedef struct MObjView {
    unsigned char pad00[4];
    unsigned int rendermode; /* 0x04 */
} MObjView;

typedef struct DObjView {
    unsigned char pad00[4];
    struct DObjView *next; /* 0x04 */
    MObjView *mobj; /* 0x08 */
} DObjView;

typedef struct JObjView {
    unsigned char pad00[8];
    struct JObjView *next; /* 0x08 */
    unsigned char pad0C[4];
    struct JObjView *child; /* 0x10 */
} JObjView;

typedef struct clNormal3DTree {
    unsigned char pad00[0x2C];
    JObjView *root; /* 0x2C */
    unsigned char pad30[0x10];
    JObjView **parts; /* 0x40 */
    int numParts; /* 0x44 */
    unsigned char enabled; /* 0x48 */
} clNormal3DTree;

extern const float lbl_806D2340;

DObjView *HSD_JObjGetDObj(JObjView *jobj);
unsigned int HSD_JObjGetFlags(JObjView *jobj);
TObjView *HSD_MObjGetTObj(MObjView *mobj);
TObjView *HSD_TObjGetNext(TObjView *tobj);
void PSMTXTrans(Mtx m, float x, float y, float z);
void PSMTXConcat(Mtx a, Mtx b, Mtx ab);
JObjView *JObj_GetNext(JObjView *jobj);
JObjView *JObj_GetChild(JObjView *jobj);
DObjView *DObj_GetNext(DObjView *dobj);

static inline JObjView *jobj_next(JObjView *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline JObjView *jobj_child(JObjView *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline DObjView *dobj_next(DObjView *dobj) {
    DObjView *n;
    if (dobj != 0) {
        n = dobj->next;
    } else {
        n = 0;
    }
    return n;
}

static inline MObjView *dobj_mobj(DObjView *dobj) {
    if (dobj != 0) {
        return dobj->mobj;
    }
    return 0;
}

#pragma exceptions on

void JObjTree_TranslateAndMul(clNormal3DTree *self, float x, float y, JObjView *jobj)
{
    if (!self->enabled) {
        return;
    }
    if (jobj != 0) {
        Mtx m;
        DObjView *dobj = HSD_JObjGetDObj(jobj);

        PSMTXTrans(m, x, y, lbl_806D2340);
        for (; dobj != 0; dobj = dobj_next(dobj)) {
            MObjView *mobj = dobj_mobj(dobj);
            if (mobj != 0) {
                TObjView *tobj;
                for (tobj = HSD_MObjGetTObj(mobj); tobj != 0; tobj = HSD_TObjGetNext(tobj)) {
                    if ((tobj->flags & 0xF) == 0) {
                        PSMTXConcat(m, tobj->mtx, tobj->mtx);
                    }
                }
            }
        }
        if (!(HSD_JObjGetFlags(jobj) & 0x1000) && jobj_child(jobj) != 0) {
            JObjTree_TranslateAndMul(self, x, y, jobj_child(jobj));
        }
        if (jobj_next(jobj) != 0) {
            JObjTree_TranslateAndMul(self, x, y, jobj_next(jobj));
        }
    } else {
        int i;
        for (i = 0; i < self->numParts; i++) {
            Mtx m;
            DObjView *dobj = HSD_JObjGetDObj(self->parts[i]);

            PSMTXTrans(m, x, y, lbl_806D2340);
            for (; dobj != 0; dobj = dobj_next(dobj)) {
                MObjView *mobj = dobj_mobj(dobj);
                if (mobj != 0) {
                    TObjView *tobj;
                    for (tobj = HSD_MObjGetTObj(mobj); tobj != 0; tobj = HSD_TObjGetNext(tobj)) {
                        if ((tobj->flags & 0xF) == 0) {
                            PSMTXConcat(m, tobj->mtx, tobj->mtx);
                        }
                    }
                }
            }
        }
    }
}

void clNormal3D_SetFlags(clNormal3DTree *self, unsigned int flags, JObjView *jobj);

/* Third level: the target calls the out-of-line accessors here. */
static inline void SetFlags_L3(clNormal3DTree *self, unsigned int flags, JObjView *jobj)
{
    DObjView *dobj;

    if (jobj == 0) {
        jobj = self->root;
    }
    for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = DObj_GetNext(dobj)) {
        dobj->mobj->rendermode |= flags;
    }
    if (!(HSD_JObjGetFlags(jobj) & 0x1000) && JObj_GetChild(jobj) != 0) {
        clNormal3D_SetFlags(self, flags, JObj_GetChild(jobj));
    }
    if (JObj_GetNext(jobj) != 0) {
        clNormal3D_SetFlags(self, flags, JObj_GetNext(jobj));
    }
}

static inline void SetFlags_L2(clNormal3DTree *self, unsigned int flags, JObjView *jobj)
{
    DObjView *dobj;

    if (jobj == 0) {
        jobj = self->root;
    }
    for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = dobj_next(dobj)) {
        dobj->mobj->rendermode |= flags;
    }
    if (!(HSD_JObjGetFlags(jobj) & 0x1000) && jobj_child(jobj) != 0) {
        SetFlags_L3(self, flags, JObj_GetChild(jobj));
    }
    if (jobj_next(jobj) != 0) {
        SetFlags_L3(self, flags, JObj_GetNext(jobj));
    }
}

void clNormal3D_SetFlags(clNormal3DTree *self, unsigned int flags, JObjView *jobj)
{
    DObjView *dobj;

    if (jobj == 0) {
        jobj = self->root;
    }
    for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = dobj_next(dobj)) {
        dobj->mobj->rendermode |= flags;
    }
    if (!(HSD_JObjGetFlags(jobj) & 0x1000) && jobj_child(jobj) != 0) {
        SetFlags_L2(self, flags, jobj_child(jobj));
    }
    if (jobj_next(jobj) != 0) {
        SetFlags_L2(self, flags, jobj_next(jobj));
    }
}

#pragma exceptions reset

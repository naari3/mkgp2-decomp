struct HSD_TObj {
    unsigned char pad[0x74];
    float mtx[3][4];
};

struct HSD_DObj {
    void *parent;
    HSD_DObj *next;
    void *mobj;
};

struct HSD_JObj {
    unsigned char pad[0x8];
    HSD_JObj *next;
    HSD_JObj *parent;
    HSD_JObj *child;
    unsigned int flags;
};

extern "C" {
extern const float lbl_806D927C;
void PSMTXTrans(float m[3][4], float x, float y, float z);
void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);
HSD_TObj *HSD_MObjGetTObj(void *mobj);
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
}

inline void *DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}

inline void TObjTranslate(HSD_TObj *tobj, float x, float y) {
    float m[3][4];
    if (tobj != 0) {
        PSMTXTrans(m, x, y, lbl_806D927C);
        PSMTXConcat(m, tobj->mtx, tobj->mtx);
    }
}

inline void DObjsTranslate(HSD_DObj *dobj, float x, float y) {
    for (; dobj != 0; dobj = dobj->next) {
        TObjTranslate(HSD_MObjGetTObj(DObjGetMObj(dobj)), x, y);
    }
}

inline void JObjTranslateDObjs(HSD_JObj *jobj, float x, float y) {
    if (jobj != 0) {
        DObjsTranslate(HSD_JObjGetDObj(jobj), x, y);
    }
}

extern "C" void fn_80182B50(HSD_JObj *jobj, float x, float y) {
    if (jobj == 0) {
        return;
    }
    JObjTranslateDObjs(jobj, x, y);
    if (!(jobj->flags & 0x1000)) {
        for (jobj = jobj->child; jobj != 0; jobj = jobj->next) {
            fn_80182B50(jobj, x, y);
        }
    }
}

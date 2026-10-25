struct HSD_MObj {
    unsigned char pad[0x23];
    unsigned char x23;
};

struct HSD_DObj {
    void *parent;
    HSD_DObj *next;
    HSD_MObj *mobj;
};

struct HSD_JObj {
    unsigned char pad[0x8];
    HSD_JObj *next;
    HSD_JObj *parent;
    HSD_JObj *child;
    unsigned int flags;
};

extern "C" {
extern unsigned char lbl_80495B58[];
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
int hsdObjIsDescendantOf(void *obj, void *info);
}

inline HSD_DObj *DObjGetNext(HSD_DObj *dobj) {
    return dobj ? dobj->next : 0;
}

inline HSD_MObj *DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}

inline void SetMObjFlag(HSD_MObj *mobj, unsigned char v) {
    if (hsdObjIsDescendantOf(mobj, lbl_80495B58)) {
        mobj->x23 = v;
    }
}

inline void SetJObjDObjsFlag(HSD_JObj *jobj, unsigned char v) {
    HSD_DObj *dobj;
    for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = DObjGetNext(dobj)) {
        SetMObjFlag(DObjGetMObj(dobj), v);
    }
}

extern "C" void fn_80182204(HSD_JObj *jobj, unsigned char v) {
    if (jobj == 0) {
        return;
    }
    SetJObjDObjsFlag(jobj, v);
    if (!(jobj->flags & 0x1000)) {
        for (jobj = jobj->child; jobj != 0; jobj = jobj->next) {
            fn_80182204(jobj, v);
        }
    }
}

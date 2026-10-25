struct HSD_JObj;
struct HSD_MObj;
struct HSD_TObj {
    unsigned char pad[0x40];
    int wrap_s;
    int wrap_t;
    unsigned char repeat_s;
    unsigned char repeat_t;
};
struct HSD_DObj {
    void *parent;
    HSD_DObj *next;
    HSD_MObj *mobj;
};

struct clNormal3D {
    unsigned char data[0x5c];
    clNormal3D(const char *name, int arg);
};

struct TexWrap {
    int pad0;
    unsigned char s;
    unsigned char t;
    unsigned char pad6[0xa];
};

extern "C" {
extern const char lbl_80377F60[];
extern TexWrap lbl_80495E30[];
HSD_JObj *Archive_GetRootJObj(clNormal3D *model);
void HSD_JObjSetFlags(HSD_JObj *jobj, unsigned int flags);
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
void fn_80182644(HSD_MObj *mobj, unsigned int flags);
HSD_TObj *HSD_MObjGetTObj(HSD_MObj *mobj);
void HSD_DObjSetFlags(HSD_DObj *dobj, unsigned int flags);
}

static inline HSD_MObj *HSD_DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}

static inline HSD_DObj *HSD_DObjGetNext(HSD_DObj *dobj) {
    return dobj ? dobj->next : 0;
}

struct Obj8018D82C {
    clNormal3D *model;
    int pad4[4];
    HSD_DObj *dobjs[1];
    unsigned char flag;
    Obj8018D82C();
};

Obj8018D82C::Obj8018D82C() {
    HSD_JObj *jobj;
    HSD_DObj *dobj;
    int i;
    model = 0;
    dobjs[0] = 0;
    flag = 0;
    clNormal3D *m = new clNormal3D(lbl_80377F60, 0);
    model = m;
    if (m != 0) {
        jobj = Archive_GetRootJObj(model);
        i = 0;
        HSD_JObjSetFlags(jobj, 0x200);
        for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = HSD_DObjGetNext(dobj)) {
            if (i < 1) {
                HSD_TObj *tobj;
                fn_80182644(HSD_DObjGetMObj(dobj), 0x20000000);
                tobj = HSD_MObjGetTObj(HSD_DObjGetMObj(dobj));
                if (tobj != 0) {
                    tobj->wrap_s = 1;
                    tobj->wrap_t = 1;
                    tobj->repeat_s = lbl_80495E30[i].s;
                    tobj->repeat_t = lbl_80495E30[i].t;
                }
                dobjs[i] = dobj;
                i++;
            } else {
                HSD_DObjSetFlags(dobj, 1);
            }
        }
    }
}

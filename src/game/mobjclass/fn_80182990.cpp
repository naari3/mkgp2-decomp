struct HSD_MObj {
    unsigned char pad[0x10];
    void *buf;
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
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
void *hsdAllocMemPiece(unsigned int size);
void *memcpy(void *dst, const void *src, unsigned long n);
}

inline HSD_DObj *DObjGetNext(HSD_DObj *dobj) {
    return dobj ? dobj->next : 0;
}

inline HSD_MObj *DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}

inline void SetMObjBuf(HSD_MObj *mobj, void *src) {
    if (mobj != 0 && src != 0) {
        if (mobj->buf == 0) {
            mobj->buf = hsdAllocMemPiece(0xc);
            if (mobj->buf == 0) {
                return;
            }
        }
        memcpy(mobj->buf, src, 0xc);
    }
}

extern "C" void fn_80182990(HSD_JObj *jobj, void *src) {
    HSD_DObj *dobj;
    if (jobj != 0 && src != 0) {
        for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = DObjGetNext(dobj)) {
            SetMObjBuf(DObjGetMObj(dobj), src);
        }
    }
}

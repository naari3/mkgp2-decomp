typedef struct HsdHandle {
    char pad[8];
    int x8;
} HsdHandle;

typedef struct Child8018FDA4 {
    char pad[0x24];
    HsdHandle *h;
    void *buf28;
    int x2c;
    int pad30;
    int x34;
    void *buf38;
    void *buf3c;
} Child8018FDA4;

typedef struct Obj8018FDA4 {
    void *vt;
    void *obj;
    Child8018FDA4 *child;
} Obj8018FDA4;

extern char lbl_80495F04[];
extern char lbl_80490FE0[];
extern char lbl_803785C0[];
extern void fn_801831F8(HsdHandle *h, int id, void *buf, int x);
extern void HSD_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void Object_DtorWithGXSync(void *p, int flag);
extern void DebugPrintf(const char *fmt, ...);

static inline void ChildDtor(Child8018FDA4 *c) {
    if (c != 0) {
        if (c->h != 0) {
            fn_801831F8(c->h, 0xd, c->buf38, c->x34);
            c->h->x8 = c->x2c;
        }
        if (c->buf28 != 0) HSD_Free(c->buf28);
        if (c->buf38 != 0) HSD_Free(c->buf38);
        if (c->buf3c != 0) HSD_Free(c->buf3c);
        MemoryManager_TimedFree(c);
    }
}

Obj8018FDA4 *fn_8018FDA4(Obj8018FDA4 *p, short flag) {
    if (p != 0) {
        p->vt = lbl_80495F04;
        if (p->child != 0) ChildDtor(p->child);
        if (p->obj != 0) Object_DtorWithGXSync(p->obj, 1);
        DebugPrintf(lbl_803785C0);
        if (p != 0) p->vt = lbl_80490FE0;
        if (flag > 0) MemoryManager_TimedFree(p);
    }
    return p;
}

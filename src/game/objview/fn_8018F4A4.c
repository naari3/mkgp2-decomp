typedef struct HsdHandle {
    char pad[8];
    int x8;
    void *xc;
} HsdHandle;

typedef struct Layer {
    HsdHandle *h;
    char pad[4];
    int saved;
    char padc[4];
    void *buf10;
    char pad14[0xc];
    void *buf20;
    char pad24[4];
    void *buf28;
} Layer;

typedef struct Node {
    struct Node *next;
    HsdHandle *h[2];
    int saved[2];
    void *buf14[2];
    int x1c[2];
    void *buf24[2];
    void *buf2c[2];
    int x34;
} Node;

typedef struct Obj8018F4A4 {
    void *vt;
    void *obj;
    int pad8;
    Node *list;
} Obj8018F4A4;

extern char lbl_80495EDC[];
extern char lbl_80490FE0[];
extern char lbl_803784E4[];
extern void fn_801831F8(void *h, int id, void *buf, int x);
extern void HSD_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void Object_DtorWithGXSync(void *p, int flag);
extern void DebugPrintf(const char *fmt, ...);

static inline void *GetXC(HsdHandle *h) {
    return h ? h->xc : 0;
}

static inline void FreeNode(Node *cur) {
    HsdHandle *t;
    int i;
    if (cur != 0) {
        for (i = 0; i < 2; i++) {
            if (cur->h[i] != 0) {
                t = GetXC(cur->h[i]);
                fn_801831F8(t, 9, cur->buf24[i], cur->x34);
                ((HsdHandle *)t)->x8 = cur->saved[i];
            }
            if (cur->buf14[i] != 0) HSD_Free(cur->buf14[i]);
            if (cur->buf24[i] != 0) HSD_Free(cur->buf24[i]);
            if (cur->buf2c[i] != 0) HSD_Free(cur->buf2c[i]);
        }
        cur->h[0] = 0;
        cur->saved[0] = 0;
        cur->buf14[0] = 0;
        cur->x1c[0] = 0;
        cur->buf2c[0] = 0;
        cur->buf24[0] = 0;
        cur->h[1] = 0;
        cur->saved[1] = 0;
        cur->buf14[1] = 0;
        cur->x1c[1] = 0;
        cur->buf2c[1] = 0;
        cur->buf24[1] = 0;
        cur->x34 = 0;
        MemoryManager_TimedFree(cur);
    }
}

Obj8018F4A4 *fn_8018F4A4(Obj8018F4A4 *p, short flag) {
    Node *n;
    Node *cur;
    if (p != 0) {
        p->vt = lbl_80495EDC;
        n = p->list;
        while (n != 0) {
            cur = n;
            n = n->next;
            FreeNode(cur);
        }
        if (p->obj != 0) Object_DtorWithGXSync(p->obj, 1);
        p->obj = 0;
        p->list = 0;
        DebugPrintf(lbl_803784E4);
        if (p != 0) p->vt = lbl_80490FE0;
        if (flag > 0) MemoryManager_TimedFree(p);
    }
    return p;
}

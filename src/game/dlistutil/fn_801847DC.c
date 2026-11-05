typedef struct JObj {
    char pad[8];
    struct JObj *next, *parent, *child;
} JObj;
typedef struct DObj {
    void *parent;
    struct DObj *next;
} DObj;
extern unsigned int HSD_JObjGetFlags(JObj *);
extern DObj *HSD_JObjGetDObj(JObj *);
extern int fn_80184374(JObj *, DObj *, void *, void *);
static inline JObj *GetChild(JObj *p) { if (!p) return 0; return p->child; }
static inline JObj *GetNext(JObj *p) { if (!p) return 0; return p->next; }
static inline JObj *GetParent(JObj *p) { if (!p) return 0; return p->parent; }
static inline DObj *DNext(DObj *p) { return p ? p->next : 0; }
int fn_801847DC(JObj *root, void *min, void *max) {
    JObj *jobj;
    DObj *dobj;
    int depth;
    JObj *next;
    if (!root) return 0;
    jobj = root;
    depth = 0;
    while (jobj) {
        if (!(HSD_JObjGetFlags(jobj) & 0x10)) {
            for (dobj=HSD_JObjGetDObj(jobj); dobj; dobj=DNext(dobj))
                fn_80184374(jobj,dobj,min,max);
            if (!(HSD_JObjGetFlags(jobj) & 0x1000)) {
                next=GetChild(jobj);
                if (next) { ++depth; goto advance; }
            }
        }
        if (depth > 0) {
            next=GetNext(jobj);
            if (next) goto advance;
        }
        do {
            next=GetParent(jobj);
            --depth;
            if (!next) break;
            jobj=next;
            next=GetNext(jobj);
        } while (!next);
        if (depth <= 0) break;
advance:
        jobj=next;
    }
    return 1;
}

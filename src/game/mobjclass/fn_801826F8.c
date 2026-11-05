typedef struct MObj {
    unsigned char pad[0x10];
    void *buf;
} MObj;
typedef struct DObj {
    void *parent;
    struct DObj *next;
    MObj *mobj;
} DObj;
typedef struct JObj {
    unsigned char pad[8];
    struct JObj *next, *parent, *child;
    unsigned int flags;
} JObj;
extern DObj *HSD_JObjGetDObj(JObj *);
extern void *hsdAllocMemPiece(unsigned int);
extern void *memcpy(void *, const void *, unsigned long);
extern DObj *fn_801869C8(DObj *);
extern MObj *fn_801869E0(DObj *);
extern void fn_80182684(MObj *, void *);
extern void fn_80182990(JObj *, void *);
static inline DObj *Next(DObj *d) { return d ? d->next : 0; }
static inline MObj *Material(DObj *d) { return d ? d->mobj : 0; }
static inline void SetBuffer(MObj *m, void *src) {
    if (m && src) {
        if (!m->buf) {
            m->buf=hsdAllocMemPiece(12);
            if (!m->buf) return;
        }
        memcpy(m->buf,src,12);
    }
}
void fn_801826F8(JObj *root, void *src) {
    DObj *d;
    JObj *a, *b, *c, *e;
    if (root && src) {
        if (root && src) {
            for (d=HSD_JObjGetDObj(root);d;d=Next(d)) SetBuffer(Material(d),src);
        }
        if (!(root->flags & 0x1000)) {
            for (a=root->child;a;a=a->next) {
                if (a && src) {
                    if (a && src) {
                        for (d=HSD_JObjGetDObj(a);d;d=Next(d)) SetBuffer(fn_801869E0(d),src);
                    }
                    if (!(a->flags & 0x1000)) {
                        for (b=a->child;b;b=b->next) {
                            if (b && src) {
                                if (b && src) {
                                    for (d=HSD_JObjGetDObj(b);d;d=fn_801869C8(d)) fn_80182684(fn_801869E0(d),src);
                                }
                                if (!(b->flags & 0x1000)) {
                                    for (c=b->child;c;c=c->next) {
                                        if (c && src) {
                                            fn_80182990(c,src);
                                            if (!(c->flags & 0x1000)) {
                                                for (e=c->child;e;e=e->next) fn_801826F8(e,src);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

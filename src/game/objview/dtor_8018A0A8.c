typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct OctNode {
    float f0, f4, f8, fc, f10, f14;
    char pad18[0xc];
    float f24;
    char pad28[8];
    struct OctNode *c0;
    struct OctNode *c1;
    ListNode *list;
} OctNode;

extern const float lbl_806D935C;
extern int lbl_806D1690;
extern int lbl_806D1694;
extern void fn_80189950(OctNode *n);
extern void MemoryManager_TimedFree(void *p);
extern OctNode *dtor_8018A0A8(OctNode *n, short flag);

static inline void Base_Dtor(OctNode *n) {
    n->f0 = lbl_806D935C;
    n->f4 = lbl_806D935C;
    n->f8 = lbl_806D935C;
    n->fc = lbl_806D935C;
    n->f10 = lbl_806D935C;
    n->f14 = lbl_806D935C;
    n->f24 = lbl_806D935C;
    lbl_806D1694--;
}

static inline void Inner_Delete(OctNode *c) {
    if (c != 0) {
        if (c->c0 != 0) {
            dtor_8018A0A8(c->c0, 1);
            c->c0 = 0;
        }
        if (c->c1 != 0) {
            dtor_8018A0A8(c->c1, 1);
            c->c1 = 0;
        }
        fn_80189950(c);
        Base_Dtor(c);
        MemoryManager_TimedFree(c);
    }
}

#pragma auto_inline off
OctNode *dtor_8018A0A8(OctNode *n, short flag) {
    ListNode *l;
    ListNode *next;
    if (n != 0) {
        if (n->c0 != 0) {
            Inner_Delete(n->c0);
            n->c0 = 0;
        }
        if (n->c1 != 0) {
            Inner_Delete(n->c1);
            n->c1 = 0;
        }
        l = n->list;
        while (l != 0) {
            next = l->next;
            if (l != 0) {
                lbl_806D1690--;
                MemoryManager_TimedFree(l);
            }
            l = next;
        }
        n->list = 0;
        Base_Dtor(n);
        if (flag > 0) MemoryManager_TimedFree(n);
    }
    return n;
}
#pragma auto_inline reset

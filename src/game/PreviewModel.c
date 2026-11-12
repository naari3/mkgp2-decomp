/* clCSModel and the eight preview layers (0x8013D4B0..0x8013DD38).
 * Nondeferred generation: the base table precedes the derived base list.
 * Single-declaration C++ linkage specifications keep the member definitions
 * on the same no-cleanup parser path as the C entry points. The ordinary
 * fn_8013DBF8 definition flushes the pending base destructor after its code.
 * PreviewList's inline constructor is defined last so its address-only copy
 * follows the base Draw method. See the RTTI working notes for the rule.
 */
#include "game/types/size_t.h"
#pragma cplusplus on

struct Normal3D {
    unsigned char opaque[0x5C];
    Normal3D(void *resource, unsigned char mode);
    ~Normal3D();
};

extern "C" {
extern void *Alloc(unsigned long size);
extern void MemoryManager_TimedFree(void *p);
extern void Object_SetColorRGBA(Normal3D *obj, int, float r, float g, float b, float a);
extern void Object_SetJObjRotationX(Normal3D *obj, float r);
extern void Object_SetJObjRotationY(Normal3D *obj, float r);
extern void Object_SetJObjRotationZ(Normal3D *obj, float r);
extern void Object_SetJObjScaleXYZ(Normal3D *obj, float x, float y, float z);
extern void Object_SetJObjPositionXYZ(Normal3D *obj, float x, float y, float z);
extern void Object_RenderJObjTree(Normal3D *obj, int flags);
extern int clNormal3D_Exec(Normal3D *obj);
extern int clNormal3D_SetScale(Normal3D *obj, int, float, float, float, float);
extern void clNormal3D_SetFlags(Normal3D *obj, unsigned int set, unsigned int clear);
extern void *fn_8013BC98(void);
extern void fn_8013BB1C(void *cam, float x, float y);
extern unsigned char fn_8013BC38(void *cam);
extern void fn_8013BBFC(void *cam);
extern void fn_8013BB9C(void *cam);
extern int fn_8013BD7C(void);
extern void fn_8013BCA0(void);
extern void *fn_8013C3B8(void);
extern void fn_8013C34C(void *rt);
extern void fn_8013C334(void *rt);
extern int fn_8013C428(void);
extern void fn_8013C3C0(void);
}

void *operator new(size_t size);
void operator delete(void *p);

#include "game/types/clCSModelInterface.h"

struct clCSModel : clCSModelInterface {
    Normal3D *model;
    float x, y;
    float r, g, b, a;
    clCSModel(void *resource, unsigned char flag);
    virtual ~clCSModel();
    virtual void Draw();
};

extern "C" {
extern void DoublyLinkedList_EraseRange();
extern void clNormal3D_Construct();
extern const float lbl_806D76E0;
extern const float lbl_806D76E4;

void fn_8013D940(int layer);
void fn_8013DA00(void);
}

struct ListNodeBase {
    ListNodeBase *prev;
    ListNodeBase *next;
};

struct ListNode : ListNodeBase {
    clCSModel *data;
};

struct ListBase {
    struct iterator {
        ListNodeBase *node;
        iterator(ListNodeBase *n) : node(n) {}
        iterator(const iterator &o) : node(o.node) {}
        clCSModel *&operator*() const { return ((ListNode *)node)->data; }
        iterator &operator++() {
            node = node->next;
            return *this;
        }
        bool operator!=(const iterator &o) const { return node != o.node; }
    };
    unsigned long count;
    ListNodeBase end_;
    ListBase();
    ~ListBase() { clear(); }
    iterator begin() { return iterator(end_.next); }
    iterator end() { return iterator(&end_); }
    bool empty() const { return count == 0; }
    iterator erase(iterator first, iterator last);
    iterator insert(iterator pos, clCSModel *const &value);
    void clear() { erase(begin(), end()); }
    void push_back(clCSModel *const &value) { insert(end(), value); }
};

struct ListMid : ListBase {
    ~ListMid() {}
};

struct PreviewList : ListMid {
    PreviewList();
    ~PreviewList();
};

struct CBase {
    ListNodeBase *node;
    CBase(ListNodeBase *n) : node(n) {}
    CBase &operator++() {
        node = node->next;
        return *this;
    }
};

struct CIter : CBase {
    CIter(const ListBase::iterator &o) : CBase(o.node) {}
    clCSModel *operator*() const { return ((ListNode *)node)->data; }
    bool operator!=(const ListBase::iterator &o) const { return node != o.node; }
};

struct PreviewLists {
    PreviewList lists[8];
    PreviewLists() {
        for (int i = 0; i < 8; i++) {
            lists[i].clear();
        }
    }
    ~PreviewLists() {}
    void clearAll() {
        for (int i = 0; i < 8; i++) {
            lists[i].clear();
        }
    }
};

extern "C" PreviewLists *PreviewModel_bss_806D1560;

extern "C" int fn_8013DBF8(void);

static inline void RenderRange(CIter first, const ListBase::iterator &last) {
    for (; first != last; ++first) {
        (*first)->Draw();
    }
}

static inline void EraseFrom(ListBase &l, ListNodeBase *e) {
    l.erase(ListBase::iterator(e->next), ListBase::iterator(e));
}

static inline void RenderAll(PreviewLists *p) {
    for (int i = 0; i < 8; i++) {
        PreviewList &l = p->lists[i];
        if (!l.empty()) {
            RenderRange(l.begin(), l.end());
            l.clear();
        }
    }
}
extern "C" void fn_8013D4B0(clCSModel *p, float a) {
    Object_SetColorRGBA(p->model, 0, p->r, p->g, p->b, a);
    p->a = a;
}

extern "C" void fn_8013D50C(clCSModel *p, float r, float g, float b, float a) {
    Object_SetColorRGBA(p->model, 0, r, g, b, a);
    p->r = r;
    p->g = g;
    p->b = b;
    p->a = a;
}

extern "C" void fn_8013D570(clCSModel *p, float ry) {
    if (p->model) {
        Object_SetJObjRotationY(p->model, ry);
    }
}

extern "C" void fn_8013D59C(clCSModel *p, float rx, float ry, float rz) {
    if (p->model) {
        Object_SetJObjRotationZ(p->model, rz);
        Object_SetJObjRotationX(p->model, rx);
        Object_SetJObjRotationY(p->model, ry);
    }
}

extern "C" void fn_8013D608(clCSModel *p, float x, float y, float z) {
    if (p->model) {
        Object_SetJObjScaleXYZ(p->model, x, y, z);
    }
}

extern "C" void fn_8013D634(clCSModel *p, float x, float y, float z) {
    if (p->model) {
        Object_SetJObjPositionXYZ(p->model, x, y, z);
    }
}

extern "C" void fn_8013D660(clCSModel *p, float x, float y) {
    p->x = x;
    p->y = y;
}

void clCSModel::Draw() {
    clCSModel *p = this;
    if (p->model && fn_8013BC98() && fn_8013C3B8()) {
        fn_8013BB1C(fn_8013BC98(), p->x, p->y);
        if (fn_8013BC38(fn_8013BC98())) {
            fn_8013C34C(fn_8013C3B8());
            fn_8013BBFC(fn_8013BC98());
            Object_RenderJObjTree(p->model, 7);
            fn_8013BB9C(fn_8013BC98());
            fn_8013C334(fn_8013C3B8());
        }
    }
}

extern "C" int fn_8013D704(clCSModel *p) {
    int ret;
    if (p->model == 0) {
        ret = 0;
    } else {
        ret = clNormal3D_Exec(p->model);
    }
    return ret;
}

extern "C" int fn_8013D738(clCSModel *p, float sx, float sy) {
    if (p->model == 0) {
        return 0;
    } else {
        return clNormal3D_SetScale(p->model, 0, sx, sy, 0.0f, 0.0f);
    }
}

clCSModel::~clCSModel() {
    if (model) {
        delete model;
    }
    fn_8013BCA0();
    fn_8013C3C0();
}

extern "C++" clCSModel::clCSModel(void *resource, unsigned char flag) {
    fn_8013BD7C();
    fn_8013C428();
    model = 0;
    x = lbl_806D76E0;
    y = lbl_806D76E0;
    r = lbl_806D76E4;
    g = lbl_806D76E4;
    b = lbl_806D76E4;
    model = new Normal3D(resource, flag);
    if (flag) {
        clNormal3D_SetFlags(model, 0x40000000, 0);
    }
}

extern "C++" PreviewList::~PreviewList() {}

extern "C" void fn_8013D940(int layer) {
    if (PreviewModel_bss_806D1560 && layer >= 0 && layer < 8) {
        PreviewList &l = PreviewModel_bss_806D1560->lists[layer];
        if (!l.empty()) {
            ListNodeBase *e = &l.end_;
            CIter b = ListBase::iterator(e->next);
            RenderRange(b, ListBase::iterator(e));
            EraseFrom(l, e);
        }
    }
}

extern "C" void fn_8013DA00(void) {
    if (PreviewModel_bss_806D1560) RenderAll(PreviewModel_bss_806D1560);
}

extern "C" void fn_8013DAC8(clCSModel *m, int layer) {
    if (PreviewModel_bss_806D1560) {
        clCSModel *v = m;
        if (v && layer >= 0 && layer < 8) {
            PreviewModel_bss_806D1560->lists[layer].push_back(v);
        }
    }
}

extern "C" void fn_8013DB2C(void) {
    PreviewLists *p = PreviewModel_bss_806D1560;
    if (p) {
        p->clearAll();
    }
}

extern "C" void fn_8013DB9C(void) {
    if (PreviewModel_bss_806D1560) {
        delete PreviewModel_bss_806D1560;
        PreviewModel_bss_806D1560 = 0;
    }
}

int fn_8013DBF8(void) {
    if (!PreviewModel_bss_806D1560) {
        PreviewModel_bss_806D1560 = new PreviewLists;
    }
    if (!PreviewModel_bss_806D1560) {
        return 0;
    }
    return 1;
}

void clCSModelInterface::Draw() {}

inline PreviewList::PreviewList() {}

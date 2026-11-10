/*
 * 3D preview models drawn through the orthographic camera into the shared
 * render target, plus eight per-layer lists of them.
 *
 * The vtables (clCSModelInterface_vtable_8048EAE8 base, PreviewModel_data_8048EB04 model) stay in data, so the
 * vptr stores and the virtual Render call are spelled out by hand.
 *
 * The base dtor (dtor_8013DCBC) is written as a plain deleting-dtor
 * function: as a real inline ~PreviewBase, CW would emit its weak copy right
 * after the model ctor instead of at the end of the unit.
 *
 * Still asm: the model ctor (a real C++ ctor matches except that weak-copy
 * placement; an extern "C" version with `new` matches the code but gets an
 * auto extab without the DESTROYBASE action), and the two render-and-clear
 * loops, which keep their list iterator in a stack slot that no C++ form
 * tried here does.
 */
#pragma cplusplus on

struct Normal3D {
    unsigned char opaque[0x5C];
    Normal3D(void *resource, unsigned char mode);
    ~Normal3D();
};

extern "C" {
extern char clCSModelInterface_vtable_8048EAE8[];
extern char PreviewModel_data_8048EB04[];
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

void *operator new(unsigned long size);
void operator delete(void *p);

struct PreviewBase {
    void *vptr;
    PreviewBase() { vptr = clCSModelInterface_vtable_8048EAE8; }
    ~PreviewBase() { vptr = clCSModelInterface_vtable_8048EAE8; }
};

struct PreviewModel : PreviewBase {
    Normal3D *model;
    float x, y;
    float r, g, b, a;
    PreviewModel(void *resource, unsigned char flag);
    ~PreviewModel();
};

extern "C" {
extern void DoublyLinkedList_EraseRange();
extern void clNormal3D_Construct();
extern const float lbl_806D76E0;
extern const float lbl_806D76E4;

void fn_8013D940(int layer);
void fn_8013DA00(void);
struct PreviewBase;
PreviewBase *dtor_8013DCBC(PreviewBase *self, short flag);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_fn_8013D940[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8013DA00[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_dtor_8013DCBC[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013D940 = {
    (void *)&fn_8013D940, 0x000000C0, (void *)extab_fn_8013D940
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013DA00 = {
    (void *)&fn_8013DA00, 0x000000C8, (void *)extab_fn_8013DA00
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_8013DCBC = {
    (void *)&dtor_8013DCBC, 0x00000048, (void *)extab_dtor_8013DCBC
};

}

extern "C" void fn_8013D4B0(PreviewModel *p, float a) {
    Object_SetColorRGBA(p->model, 0, p->r, p->g, p->b, a);
    p->a = a;
}

extern "C" void fn_8013D50C(PreviewModel *p, float r, float g, float b, float a) {
    Object_SetColorRGBA(p->model, 0, r, g, b, a);
    p->r = r;
    p->g = g;
    p->b = b;
    p->a = a;
}

extern "C" void fn_8013D570(PreviewModel *p, float ry) {
    if (p->model) {
        Object_SetJObjRotationY(p->model, ry);
    }
}

extern "C" void fn_8013D59C(PreviewModel *p, float rx, float ry, float rz) {
    if (p->model) {
        Object_SetJObjRotationZ(p->model, rz);
        Object_SetJObjRotationX(p->model, rx);
        Object_SetJObjRotationY(p->model, ry);
    }
}

extern "C" void fn_8013D608(PreviewModel *p, float x, float y, float z) {
    if (p->model) {
        Object_SetJObjScaleXYZ(p->model, x, y, z);
    }
}

extern "C" void fn_8013D634(PreviewModel *p, float x, float y, float z) {
    if (p->model) {
        Object_SetJObjPositionXYZ(p->model, x, y, z);
    }
}

extern "C" void fn_8013D660(PreviewModel *p, float x, float y) {
    p->x = x;
    p->y = y;
}

extern "C" void fn_8013D66C(PreviewModel *p) {
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

extern "C" int fn_8013D704(PreviewModel *p) {
    int ret;
    if (p->model == 0) {
        ret = 0;
    } else {
        ret = clNormal3D_Exec(p->model);
    }
    return ret;
}

extern "C" int fn_8013D738(PreviewModel *p, float sx, float sy) {
    if (p->model == 0) {
        return 0;
    } else {
        return clNormal3D_SetScale(p->model, 0, sx, sy, 0.0f, 0.0f);
    }
}

PreviewModel::~PreviewModel() {
    vptr = PreviewModel_data_8048EB04;
    if (model) {
        delete model;
    }
    fn_8013BCA0();
    fn_8013C3C0();
}

/* fakematch (class view): the ctor is built on a second view of the base
 * whose dtor is only declared, so the DESTROYBASE cleanup names the
 * out-of-line dtor_8013DCBC instead of emitting a weak copy of the inline
 * base dtor right after this function. Natural code: the same ctor on
 * PreviewModel/PreviewBase. */
struct PreviewBaseOOL {
    void *vptr;
    PreviewBaseOOL() { vptr = clCSModelInterface_vtable_8048EAE8; }
    ~PreviewBaseOOL();
};

struct PreviewModelCtor : PreviewBaseOOL {
    Normal3D *model;
    float x, y;
    float r, g, b, a;
    PreviewModelCtor(void *resource, unsigned char flag);
};

PreviewModelCtor::PreviewModelCtor(void *resource, unsigned char flag) {
    vptr = PreviewModel_data_8048EB04;
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

struct ListNodeBase {
    ListNodeBase *prev;
    ListNodeBase *next;
};

struct ListNode : ListNodeBase {
    PreviewModel *data;
};

struct ListBase {
    struct iterator {
        ListNodeBase *node;
        iterator(ListNodeBase *n) : node(n) {}
        iterator(const iterator &o) : node(o.node) {}
        PreviewModel *&operator*() const { return ((ListNode *)node)->data; }
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
    iterator insert(iterator pos, PreviewModel *const &value);
    void clear() { erase(begin(), end()); }
    void push_back(PreviewModel *const &value) { insert(end(), value); }
};

struct ListMid : ListBase {
    ~ListMid() {}
};

struct PreviewList : ListMid {
    PreviewList() {}
    ~PreviewList();
};

static inline void RenderModel(PreviewModel *m) {
    ((void (**)(PreviewModel *))m->vptr)[3](m);
}

PreviewList::~PreviewList() {
}

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

struct RenderIface {
    virtual void Slot0();
    virtual void Render();
};
static inline void RenderModelV(PreviewModel *m) { ((RenderIface *)m)->Render(); }
#pragma push
#pragma global_optimizer off
extern "C" void fn_8013D940(int layer) {
    if (PreviewModel_bss_806D1560 && layer >= 0 && layer < 8) {
        PreviewList *l = &PreviewModel_bss_806D1560->lists[layer];
        if (!l->empty()) {
            ListNodeBase *e = &l->end_;
            ListBase::iterator it = ListBase::iterator(e->next);
            for (; it.node != e; ++it) {
                RenderModelV(*it);
            }
            l->clear();
        }
    }
}

#pragma pop
extern "C" void fn_8013DA00(void) {
    PreviewLists *p = PreviewModel_bss_806D1560;
    if (p) {
        for (int i = 0; i < 8; i++) {
            PreviewList *l = &p->lists[i];
            if (!l->empty()) {
                for (ListBase::iterator it = l->begin(); it != l->end(); ++it) {
                    RenderModel(*it);
                }
                l->clear();
            }
        }
    }
}

extern "C" void fn_8013DAC8(PreviewModel *m, int layer) {
    if (PreviewModel_bss_806D1560) {
        PreviewModel *v = m;
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

extern "C" int fn_8013DBF8(void) {
    if (!PreviewModel_bss_806D1560) {
        PreviewModel_bss_806D1560 = new PreviewLists;
    }
    if (!PreviewModel_bss_806D1560) {
        return 0;
    }
    return 1;
}

#pragma exceptions off
extern "C" PreviewBase *dtor_8013DCBC(PreviewBase *self, short flag) {
    if (self != 0) {
        self->vptr = clCSModelInterface_vtable_8048EAE8;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset

extern "C" void fn_8013DD04(void) {
}

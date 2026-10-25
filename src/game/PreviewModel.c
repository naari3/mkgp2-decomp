/*
 * 3D preview models drawn through the orthographic camera into the shared
 * render target, plus eight per-layer lists of them.
 *
 * The vtables (lbl_8048EAE8 base, lbl_8048EB04 model) stay in data, so the
 * vptr stores and the virtual Render call are spelled out by hand.
 *
 * Still asm: the model ctor (the out-of-line base dtor it names in its
 * cleanup actions would be emitted right after it instead of at the end of
 * the unit), the base dtor itself, and the two render-and-clear loops, which
 * keep their list iterator in a stack slot that no C++ form tried here does.
 */
#pragma cplusplus on

struct Normal3D {
    unsigned char opaque[0x5C];
    Normal3D(void *resource, unsigned char mode);
    ~Normal3D();
};

extern "C" {
extern char lbl_8048EAE8[];
extern char lbl_8048EB04[];
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
    PreviewBase() { vptr = lbl_8048EAE8; }
    ~PreviewBase() { vptr = lbl_8048EAE8; }
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
extern float lbl_806D76E0;
extern float lbl_806D76E4;
asm void fn_8013D800(void);
asm void fn_8013D940(void);
asm void fn_8013DA00(void);
asm void dtor_8013DCBC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; unsigned int f11; void *f12; } extab_fn_8013D800 = { 0x200A0000, 0x00000044, 0x000C0028, 0x00000088, 0x00000020, 0x000000A4, 0x00000028, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001D, 0x00000000, (void *)&dtor_8013DCBC };

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
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013D800 = {
    (void *)&fn_8013D800, 0x000000C8, (void *)&extab_fn_8013D800
};

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
    vptr = lbl_8048EB04;
    if (model) {
        delete model;
    }
    fn_8013BCA0();
    fn_8013C3C0();
}

extern "C" asm void fn_8013D800(void) { /* 0x8013D800 size:0xC8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r7, lbl_8048EAE8@ha
    lis r6, lbl_8048EB04@ha
    stw r0, 0x24(r1)
    addi r0, r6, lbl_8048EB04@l
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    addi r3, r7, lbl_8048EAE8@l
    stw r28, 0x10(r1)
    stw r3, 0x0(r29)
    stw r0, 0x0(r29)
    bl fn_8013BD7C
    bl fn_8013C428
    li r0, 0x0
    lfs f1, lbl_806D76E0(r2)
    stw r0, 0x4(r29)
    li r3, 0x5c
    lfs f0, lbl_806D76E4(r2)
    stfs f1, 0x8(r29)
    stfs f1, 0xc(r29)
    stfs f0, 0x10(r29)
    stfs f0, 0x14(r29)
    stfs f0, 0x18(r29)
    bl Alloc
    mr. r28, r3
    beq fn_8013D800_L_8013D888
    mr r4, r30
    mr r5, r31
    bl clNormal3D_Construct
    fn_8013D800_L_8013D888:
    clrlwi. r0, r31, 24
    stw r28, 0x4(r29)
    beq fn_8013D800_L_8013D8A4
    lwz r3, 0x4(r29)
    lis r4, 0x4000
    li r5, 0x0
    bl clNormal3D_SetFlags
    fn_8013D800_L_8013D8A4:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
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

extern "C" PreviewLists *lbl_806D1560;

extern "C" asm void fn_8013D940(void) { /* 0x8013D940 size:0xC0 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    lwz r4, lbl_806D1560(r13)
    cmplwi r4, 0x0
    beq fn_8013D940_L_8013D9E8
    cmpwi r3, 0x0
    blt fn_8013D940_L_8013D9E8
    cmpwi r3, 0x8
    bge fn_8013D940_L_8013D9E8
    mulli r0, r3, 0xc
    add r31, r4, r0
    lwz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq fn_8013D940_L_8013D9E8
    addi r30, r31, 0x4
    lwz r0, 0x8(r31)
    stw r0, 0x18(r1)
    stw r0, 0x14(r1)
    b fn_8013D940_L_8013D9BC
    fn_8013D940_L_8013D998:
    lwz r3, 0x14(r1)
    lwz r3, 0x8(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x14(r1)
    lwz r0, 0x4(r3)
    stw r0, 0x14(r1)
    fn_8013D940_L_8013D9BC:
    lwz r0, 0x14(r1)
    cmplw r0, r30
    bne fn_8013D940_L_8013D998
    stw r30, 0x10(r1)
    mr r4, r31
    addi r3, r1, 0x8
    addi r5, r1, 0xc
    lwz r0, 0x4(r30)
    addi r6, r1, 0x10
    stw r0, 0xc(r1)
    bl DoublyLinkedList_EraseRange
    fn_8013D940_L_8013D9E8:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_8013DA00(void) { /* 0x8013DA00 size:0xC8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    lwz r29, lbl_806D1560(r13)
    cmplwi r29, 0x0
    beq fn_8013DA00_L_8013DAAC
    li r31, 0x0
    fn_8013DA00_L_8013DA28:
    lwz r0, 0x0(r29)
    cmplwi r0, 0x0
    beq fn_8013DA00_L_8013DA9C
    lwz r0, 0x8(r29)
    addi r30, r29, 0x4
    stw r0, 0x18(r1)
    stw r0, 0x14(r1)
    b fn_8013DA00_L_8013DA6C
    fn_8013DA00_L_8013DA48:
    lwz r3, 0x14(r1)
    lwz r3, 0x8(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x14(r1)
    lwz r0, 0x4(r3)
    stw r0, 0x14(r1)
    fn_8013DA00_L_8013DA6C:
    lwz r0, 0x14(r1)
    cmplw r0, r30
    bne fn_8013DA00_L_8013DA48
    addi r0, r29, 0x4
    mr r4, r29
    stw r0, 0x10(r1)
    addi r3, r1, 0x8
    addi r5, r1, 0xc
    addi r6, r1, 0x10
    lwz r0, 0x8(r29)
    stw r0, 0xc(r1)
    bl DoublyLinkedList_EraseRange
    fn_8013DA00_L_8013DA9C:
    addi r31, r31, 0x1
    addi r29, r29, 0xc
    cmpwi r31, 0x8
    blt fn_8013DA00_L_8013DA28
    fn_8013DA00_L_8013DAAC:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" void fn_8013DAC8(PreviewModel *m, int layer) {
    if (lbl_806D1560) {
        PreviewModel *v = m;
        if (v && layer >= 0 && layer < 8) {
            lbl_806D1560->lists[layer].push_back(v);
        }
    }
}

extern "C" void fn_8013DB2C(void) {
    PreviewLists *p = lbl_806D1560;
    if (p) {
        p->clearAll();
    }
}

extern "C" void fn_8013DB9C(void) {
    if (lbl_806D1560) {
        delete lbl_806D1560;
        lbl_806D1560 = 0;
    }
}

extern "C" int fn_8013DBF8(void) {
    if (!lbl_806D1560) {
        lbl_806D1560 = new PreviewLists;
    }
    if (!lbl_806D1560) {
        return 0;
    }
    return 1;
}

extern "C" asm void dtor_8013DCBC(void) { /* 0x8013DCBC size:0x48 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq dtor_8013DCBC_L_8013DCEC
    lis r5, lbl_8048EAE8@ha
    extsh. r0, r4
    addi r0, r5, lbl_8048EAE8@l
    stw r0, 0x0(r31)
    ble dtor_8013DCBC_L_8013DCEC
    bl MemoryManager_TimedFree
    dtor_8013DCBC_L_8013DCEC:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void fn_8013DD04(void) {
}

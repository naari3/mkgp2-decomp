/* Result-scene objects, .text 0x8015C41C..0x8016219C.
 * This span's extabindex is not in ascending order, so dtk can't split it
 * further; it stays one NonMatching TU and gains functions as they match. */

struct VObj {
    virtual ~VObj();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
};

extern "C" {
extern void *Alloc(unsigned long size);
extern void HSD_StateInvalidate(int state);
}

struct SceneBase {
    SceneBase() { done = 0; }
    virtual ~SceneBase() {}
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    unsigned char done;
};

struct ResultSub {
    ResultSub(int a, int b);
    virtual ~ResultSub();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    char pad4[0x10];
    int state;
    char pad18[0x60 - 0x18];
};

struct ResultSceneA : SceneBase {
    ResultSceneA() {
        started = 0;
        sub = new ResultSub(0, 0);
    }
    virtual ~ResultSceneA() {
        if (sub) sub->Destroy();
    }
    virtual void Destroy() { delete this; }
    virtual void Update() {
        if (!started) started = 1;
        sub->Update();
        if (sub->state == 99) done = 1;
    }
    virtual void Draw() {
        if (started) {
            sub->Draw();
            HSD_StateInvalidate(-1);
        }
    }
    unsigned char started;
    ResultSub *sub;
};

extern "C" {

extern void MemoryManager_TimedFree(void *p);
extern void fn_8011FAFC(void *p, int n);
extern void fn_801A0004(void *p);
extern void fn_80160588(void *self, int n);
extern void fn_80161720(void *self);
extern char lbl_80490A58[];
extern const float lbl_806D86A4;
extern const float lbl_806D86D8;

void fn_8015CB24(VObj *p) {
    delete p;
}

typedef struct {
    char pad0[0x10];
    float a;
    char pad14[0x28 - 0x14];
    float b;
} Obj8015CD40;

int fn_8015CD40(Obj8015CD40 *o) {
    if (o->a > lbl_806D86D8 || o->b >= lbl_806D86A4) return 1;
    return 0;
}

typedef struct {
    char pad0[0x10];
    int state;
} Obj8015E1D4;

unsigned char fn_8015E1D4(Obj8015E1D4 *o) {
    return o->state == 6;
}

typedef struct {
    char pad0[0x10];
    unsigned char mode;
    char pad11[3];
    char sub[0x6c - 0x14];
    void *p6c;
} Obj8015E804;

void fn_8015E804(Obj8015E804 *o) {
    if (o->mode != 1) {
        fn_8011FAFC(o->sub, 3);
        fn_801A0004(o->p6c);
    }
}

unsigned char fn_8015E84C(Obj8015E804 *o) {
    return o->mode;
}

void fn_8015E854(void) {
}

void fn_8015E858(void) {
}

int fn_8015E85C(void) {
    return 1;
}

typedef struct {
    void *vt;
} ObjBase8015E864;

ObjBase8015E864 *dtor_8015E864(ObjBase8015E864 *p, short flag) {
    if (p) {
        p->vt = (void *)lbl_80490A58;
        if (flag > 0) MemoryManager_TimedFree(p);
    }
    return p;
}

void fn_80160364(VObj *p) {
    delete p;
}

typedef struct {
    unsigned char active;
    char pad1[0x10 - 1];
    int ready;
    int cur;
    int next;
} Obj80161888;

int fn_801618CC(Obj80161888 *o, int v, int unused);

void fn_80161888(Obj80161888 *o) {
    o->active = 1;
    fn_801618CC(o, o->next, 1);
    fn_80161720(o);
}

int fn_801618CC(Obj80161888 *o, int v, int unused) {
    if (o->ready == 0) return 0;
    o->next = v;
    o->cur = -1;
    fn_80160588(o, 0);
    return 1;
}

SceneBase *fn_80160238(void) {
    return new ResultSceneA;
}

}

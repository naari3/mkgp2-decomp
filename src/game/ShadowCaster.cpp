/*
 * 0x801746A8..0x80174D94: a shadow caster bound to a model's joint tree.
 * Setup walks the tree once to optionally swap flagged joints for proxy
 * copies (restored by the proxy destructor), measures the model's bounds,
 * and registers every display object with the shadow set; draw, reset,
 * destructor and constructor follow. The tree free/clone helpers after it
 * (0x80174D94..0x801752C0) are still asm.
 * Real C++ for the proxy ctor/dtor; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

struct DObj {
    char pad00[0x4];
    DObj *next;
};

struct JObj {
    char pad00[0x8];
    JObj *next;
    JObj *parent;
    JObj *child;
    unsigned int flags;
};

struct ShadowSet;

struct Vec3f {
    float x, y, z;
};

extern "C" {
unsigned int fn_802D07BC(JObj *);
DObj *fn_802D0758(JObj *);
unsigned char fn_80183CC4(JObj *, DObj *, Vec3f *, float *);
void fn_801899B8(ShadowSet *, JObj *, DObj *, Vec3f *, float);
void fn_801893BC(ShadowSet *);
void fn_802D0B48(JObj *, unsigned int);
JObj *fn_802D0EF4(void);
void fn_80175048(JObj *, JObj *, JObj *, unsigned char);
extern int lbl_806D15E8;
}

struct Proxy {
    ~Proxy();
    Proxy *next;
    JObj *jobj;
    JObj *orig;
    unsigned int origFlags;

    Proxy(JObj *jobj) {
        next = 0;
        this->jobj = jobj;
        orig = 0;
        if (this->jobj) {
            orig = this->jobj->child;
            origFlags = this->jobj->flags;
            fn_802D0B48(this->jobj, 0x1000);
            if (this->jobj->flags & 0x40000) {
                this->jobj->flags |= 0x10000000;
                this->jobj->flags &= ~0x40000;
            }
            if (this->jobj->flags & 0x80000) {
                this->jobj->flags |= 0x20000000;
                this->jobj->flags &= ~0x80000;
            }
            if (this->jobj->flags & 0x100000) {
                this->jobj->flags |= 0x40000000;
                this->jobj->flags &= ~0x100000;
            }
            this->jobj->child = fn_802D0EF4();
            lbl_806D15E8++;
            fn_80175048(orig, this->jobj->child, this->jobj, 1);
        }
    }
};


static inline DObj *DObjNext(DObj *d) {
    if (d) {
        return d->next;
    }
    return 0;
}

static inline JObj *JObjChild(JObj *j) {
    return j == 0 ? 0 : j->child;
}

static inline JObj *JObjNext(JObj *j) {
    return j == 0 ? 0 : j->next;
}

static inline JObj *JObjParent(JObj *j) {
    return j == 0 ? 0 : j->parent;
}

struct ShadowSet {
    ShadowSet();
    ~ShadowSet();
    char pad00[0x40];
};

struct Caster {
    JObj *root;
    ShadowSet sub;
    Proxy *proxies;

    Caster(JObj *root, unsigned char proxy);
    ~Caster();
};

extern "C" {
extern const Vec3f lbl_80370858;
extern const Vec3f lbl_80370864;
void fn_80189C10(ShadowSet *);
unsigned char fn_801847DC(JObj *, Vec3f *, Vec3f *);
void fn_80189FD8(ShadowSet *, Vec3f *, Vec3f *);
void fn_80174D94(JObj *, unsigned char);
void fn_802D041C(JObj *);
}

#pragma auto_inline off

extern "C" {

void fn_801746A8(Caster *self) {
    fn_801893BC(&self->sub);
}

void fn_801746CC(Caster *self) {
    if (self->root) {
        DObj *dobj;
        JObj *jobj = self->root;
        int depth = 0;
        JObj *next;

        while (jobj) {
            if (!(fn_802D07BC(jobj) & 0x10)) {
                if (fn_802D0758(jobj)) {
                    for (dobj = fn_802D0758(jobj); dobj; dobj = DObjNext(dobj)) {
                        Vec3f pos;
                        float r;

                        if (fn_80183CC4(jobj, dobj, &pos, &r)) {
                            fn_801899B8(&self->sub, jobj, dobj, &pos, r);
                        }
                    }
                }
                if (!(fn_802D07BC(jobj) & 0x1000) && (next = JObjChild(jobj))) {
                    depth++;
                    goto advance;
                }
            }
            if (depth <= 0 || !(next = JObjNext(jobj))) {
                do {
                    next = JObjParent(jobj);
                    depth--;
                    if (!next) {
                        break;
                    }
                    jobj = next;
                } while (!(next = JObjNext(jobj)));
                if (depth <= 0) {
                    break;
                }
            }
        advance:
            jobj = next;
        }
    }
}

void fn_80174850(Caster *self) {
    Proxy *prev = 0;
    Proxy *p = self->proxies;

    while (p) {
        while (p->next) {
            prev = p;
            p = p->next;
        }
        delete p;
        if (!prev) {
            break;
        }
        prev->next = 0;
        prev = 0;
        p = self->proxies;
    }
    self->proxies = 0;
}

void fn_801748DC(Caster *self) {
    if (self->root) {
        JObj *jobj = self->root;
        int depth = 0;
        JObj *next;

        while (jobj) {
            if (depth < 0) {
                break;
            }
            if (!(fn_802D07BC(jobj) & 0x10)) {
                if (fn_802D07BC(jobj) & 0x1000) {
                    Proxy *proxy = new Proxy(jobj);
                    Proxy *p = self->proxies;

                    if (!p) {
                        self->proxies = proxy;
                    } else {
                        while (p->next) {
                            p = p->next;
                        }
                        p->next = proxy;
                    }
                }
                if (!(fn_802D07BC(jobj) & 0x1000) && (next = JObjChild(jobj))) {
                    depth++;
                    goto advance;
                }
            }
            if (!(next = JObjNext(jobj))) {
                do {
                    next = JObjParent(jobj);
                    if (!next) {
                        break;
                    }
                    jobj = next;
                    depth--;
                } while (!(next = JObjNext(jobj)));
            }
        advance:
            jobj = next;
        }
    }
}

void fn_80174B14(Caster *self) {
    fn_80189C10(&self->sub);
    fn_80174850(self);
    self->root = 0;
}

int fn_80174B54(Caster *self, JObj *root, unsigned char proxy) {
    fn_80174B14(self);
    if (!root) {
        return 0;
    }
    self->root = root;
    if (proxy) {
        fn_801748DC(self);
    }
    {
        Vec3f min = lbl_80370858;
        Vec3f max = lbl_80370864;

        if (fn_801847DC(self->root, &min, &max)) {
            fn_80189FD8(&self->sub, &min, &max);
        }
    }
    fn_801746CC(self);
    return 1;
}

}

#pragma exceptions on

Caster::~Caster() {
    fn_80174B14(this);
}

Caster::Caster(JObj *root, unsigned char proxy) {
    this->root = 0;
    proxies = 0;
    fn_80174B54(this, root, proxy);
}

Proxy::~Proxy() {
    if (orig) {
        fn_80174D94(jobj->child, 1);
        fn_802D041C(jobj->child);
        lbl_806D15E8--;
        jobj->child = orig;
        jobj->flags = origFlags;
        orig = 0;
    }
}

#pragma exceptions reset

#pragma auto_inline reset

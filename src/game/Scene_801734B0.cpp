/*
 * 0x801734B0..0x801737CC: small course-effect helpers (cached position
 * update, handle reset and arm) and the destructor and constructor of a
 * handle that holds a reference on a shared effect resource (created by its
 * first user and freed with its last).
 * Real C++ for the inlined deletes; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

struct Vec3f {
    float x, y, z;
};

struct PosCache {
    char pad00[0x4];
    Vec3f pos;
    char pad10[0xC];
    float dirty;
};

struct HandleState {
    int id;
    float t;
    unsigned char active;
};

struct Handle {
    HandleState *state;
    char pad04[0x18];
    float rate;
};

struct EffectObj {
    EffectObj(const char *name);
    ~EffectObj();
    char pad00[0x4];
};

struct EffectSlot {
    EffectSlot();
    ~EffectSlot();
    char pad00[0x94];
};

struct SlotDesc {
    float params[4];
    int obj;
};

extern "C" {
extern const SlotDesc lbl_8036E8D4[4];
extern const char *lbl_806CFAC8[2];
void fn_801F7344(EffectObj *, EffectSlot *);
void fn_801F7198(EffectObj *, EffectSlot *, int);
void fn_801F6D58(EffectSlot *, const SlotDesc *, int, int);
}

struct SharedEffect {
    EffectObj *objs[2];
    EffectSlot slots[4];

    SharedEffect() {
        int i;

        for (i = 0; i < 2; i++) {
            objs[i] = new EffectObj(lbl_806CFAC8[i]);
        }
        for (i = 0; i < 4; i++) {
            int obj = lbl_8036E8D4[i].obj;

            if (objs[obj]) {
                fn_801F7344(objs[obj], &slots[i]);
                fn_801F7198(objs[obj], &slots[i], 0);
                fn_801F6D58(&slots[i], &lbl_8036E8D4[i], 0, 0);
            }
        }
    }

    ~SharedEffect() {
        int i;

        for (i = 0; i < 2; i++) {
            if (objs[i]) {
                delete objs[i];
            }
        }
    }
};

extern "C" {
extern SharedEffect *lbl_806D15E0;
extern int lbl_806D15E4;
}

struct RefSub {
    unsigned char on;
    char pad01[0x1F];
};

struct SharedRef {
    int id;
    float t;
    unsigned char active;
    float a;
    float b;
    float c;
    RefSub subs[5];

    SharedRef() {
        int i;

        if (lbl_806D15E0 == 0) {
            lbl_806D15E0 = new SharedEffect();
        }
        lbl_806D15E4++;
        id = -1;
        t = 0.0f;
        active = 0;
        a = 0.0f;
        b = 0.0f;
        c = 0.0f;
        for (i = 0; i < 5; i++) {
            subs[i].on = 0;
        }
    }

    ~SharedRef() {
        if (lbl_806D15E4 > 0) {
            lbl_806D15E4--;
        }
        if (lbl_806D15E4 <= 0 && lbl_806D15E0) {
            delete lbl_806D15E0;
            lbl_806D15E0 = 0;
            lbl_806D15E4 = 0;
        }
    }
};

struct EffectHandle {
    SharedRef *ref;
    float f[7];

    EffectHandle();
    ~EffectHandle();
};

extern "C" {

void fn_801734B0(PosCache *self, Vec3f *pos) {
    if (self->pos.x != pos->x || self->pos.y != pos->y || self->pos.z != pos->z) {
        self->pos.x = pos->x;
        self->pos.y = pos->y;
        self->pos.z = pos->z;
        self->dirty = 0.0f;
    }
}

void fn_80173500(Handle *self) {
    if (self->state->id != -1) {
        self->state->id = -1;
    }
}

int fn_8017351C(Handle *self) {
    HandleState *st = self->state;

    if (st->id == -1) {
        st->id = 0;
        st->t = 0.0f;
        st->active = 0;
    }
    self->rate = 1.0f;
    return 1;
}

}

#pragma exceptions on

EffectHandle::~EffectHandle() {
    if (ref) {
        delete ref;
        ref = 0;
    }
}

EffectHandle::EffectHandle() {
    ref = new SharedRef();
    f[0] = 0.0f;
    f[1] = 0.0f;
    f[2] = 0.0f;
    f[3] = 0.0f;
    f[4] = 0.0f;
    f[5] = 0.0f;
    f[6] = 0.0f;
}

#pragma exceptions reset

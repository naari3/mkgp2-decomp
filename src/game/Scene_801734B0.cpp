/*
 * 0x801734B0..0x80173F5C: homing target markers. Small helpers (cached
 * position update, handle reset and arm), the destructor and constructor of
 * a handle that holds a reference on a shared effect resource (created by
 * its first user and freed with its last), its draw, and the lock-on marker
 * that tracks a kart on screen: update, target set, state queries, stop,
 * start, destructor and constructor.
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
    Vec3f pos;
    RefSub subs[5];

    void SetActive(unsigned char on) {
        if (active != on) {
            active = on;
            if (active == 0 && (id == 2 || id == 3)) {
                id = 4;
                t = 0.0f;
            }
        }
    }

    void SetPos(float x, float y, float z) {
        pos.x = x;
        pos.y = y;
        pos.z = z;
    }

    void Arm() {
        if (id == -1) {
            id = 0;
            t = 0.0f;
            active = 0;
        }
    }

    SharedRef() {
        int i;

        if (lbl_806D15E0 == 0) {
            lbl_806D15E0 = new SharedEffect();
        }
        lbl_806D15E4++;
        id = -1;
        t = 0.0f;
        active = 0;
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
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

struct Vec2f {
    float x, y;
};

struct Driver {
    char pad000[0x2D0];
    unsigned char sound;
};

struct HomingMarker {
    SharedRef *ref;
    Driver *driver;
    void *kart;
    Vec3f target;
    Vec3f cur;
    float phase;
    unsigned int wobble;
    float blend;

    HomingMarker(Driver *driver);
    ~HomingMarker();
};

extern "C" {
extern const Vec2f lbl_8036E954[];
void fn_801721B0(SharedRef *);
void fn_80172948(SharedRef *);
void *GetCourseScene3D(void);
float *KartDriver_GetKartRootMtx(void *);
void CObj_ProjectPoint(void *, float *, float *, float *, float *, float, float, float);
float LUT_Sin12Bit(float);
unsigned char fn_8016C360(int);
void fn_8016C394(int);
void SoundMgr_PlaySE(int);
}

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

extern "C" {

void fn_801737CC(EffectHandle *self) {
    fn_801721B0(self->ref);
}

void fn_801737F0(HomingMarker *self) {
    void *scene;
    int state;
    float depth;

    scene = GetCourseScene3D();
    if (scene && self->kart) {
        float *m = KartDriver_GetKartRootMtx(self->kart);

        self->target.x = m[3];
        self->target.y = m[7];
        self->target.z = m[11];
        self->target.x = 5.0f * m[1] + self->target.x;
        self->target.y = 5.0f * m[5] + self->target.y;
        self->target.z = 5.0f * m[9] + self->target.z;
        CObj_ProjectPoint(scene, &self->target.x, &self->target.y, &self->target.z, &depth,
                          self->target.x, self->target.y, self->target.z);
    }
    state = self->ref->id;
    switch (state) {
    case 0:
        self->cur.x = 320.0f;
        self->cur.y = 220.0f;
        self->cur.z = 0.0f;
        break;
    case 1:
        if (self->kart) {
            self->blend += 0.033333335f;
            if (self->blend > 1.0f) {
                self->blend = 1.0f;
                self->ref->SetActive(1);
            }
            self->cur.x += self->blend * (self->target.x - self->cur.x);
            self->cur.y += self->blend * (self->target.y - self->cur.y);
            self->cur.z += self->blend * (self->target.z - self->cur.z);
        } else {
            if (self->blend < 1.0f) {
                self->blend += 0.016666668f;
                if (self->blend > 1.0f) {
                    self->blend = 1.0f;
                }
                self->cur.x += (320.0f - self->cur.x) * self->blend;
                self->cur.y += (220.0f - self->cur.y) * self->blend;
                self->cur.z += -self->cur.z * self->blend;
            } else {
                self->cur.x = 320.0f;
                self->cur.y = 220.0f;
                self->cur.z = 0.0f;
            }
            if ((self->phase += 1.0f) >= 60.0f) {
                self->phase = 0.0f;
                if (++self->wobble >= 3) {
                    self->wobble = 0;
                }
            }
            self->cur.x = lbl_8036E954[self->wobble].x * LUT_Sin12Bit(6.0f * self->phase) + self->cur.x;
            self->cur.y = lbl_8036E954[self->wobble].y * LUT_Sin12Bit(6.0f * self->phase) + self->cur.y;
        }
        break;
    case 2:
    case 3:
        self->cur.x = self->target.x;
        self->cur.y = self->target.y;
        self->cur.z = self->target.z;
        break;
    }
    self->ref->SetPos(self->cur.x, self->cur.y, self->cur.z);
    fn_80172948(self->ref);
    if (self->driver->sound) {
        if (state == 3) {
            if (!fn_8016C360(0x6B)) {
                SoundMgr_PlaySE(0x6B);
            }
        } else {
            fn_8016C394(0x6B);
        }
    }
}

void fn_80173B68(HomingMarker *self, void *kart) {
    if (self->kart != kart) {
        self->kart = kart;
        self->phase = 0.0f;
        self->blend = 0.0f;
        self->ref->SetActive(0);
    }
}

int fn_80173BD0(HomingMarker *self) {
    return self->ref->id == 3;
}

void fn_80173BE8(HomingMarker *self) {
    if (self->ref->id != -1) {
        self->ref->id = -1;
    }
    if (self->driver->sound) {
        fn_8016C394(0x6B);
    }
}

int fn_80173C34(HomingMarker *self) {
    if (self->ref->id == -1) {
        self->phase = 0.0f;
        self->blend = 0.0f;
        self->ref->SetActive(0);
        self->ref->Arm();
    }
    return 1;
}

}

#pragma exceptions on

HomingMarker::~HomingMarker() {
    delete ref;
    ref = 0;
    fn_8016C394(0x6B);
}

HomingMarker::HomingMarker(Driver *driver) {
    ref = new SharedRef();
    this->driver = driver;
    kart = 0;
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    cur.x = 0.0f;
    cur.y = 0.0f;
    cur.z = 0.0f;
    wobble = 0;
    phase = 0.0f;
    blend = 0.0f;
}

#pragma exceptions reset

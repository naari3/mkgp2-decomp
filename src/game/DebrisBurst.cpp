/*
 * 0x8016DA30..0x8016E1C0: debris burst effect (four spawn groups of JObj
 * particles that fall and despawn below the course): draw, update, spawn,
 * group queries, destructor and constructor. The TU owns .rodata
 * 0x8036D690..0x8036D728 (spawn table and names), which CW addresses
 * through one hoisted base.
 */

struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x20];
    Vec3f translate;
};

struct Debris {
    HSD_JObj *jobj;
    unsigned char alive;
    char pad05[0x3];
    Vec3f vel;
    char pad14[0xC];
};

struct DebrisGroup {
    HSD_JObj *root;
    unsigned char active;
    char pad05[0x3];
    Debris *items;
};

struct DebrisSpawn {
    int count;
    Vec3f pos;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
};

struct SoundEmitter {
    SoundEmitter();
    virtual ~SoundEmitter();
    virtual void Update();
    virtual void Draw();
    char pad04[0x2970];
};

struct DebrisBurst {
    void *model;
    DebrisGroup *groups;
    SoundEmitter *sound;
    int randIdx;

    DebrisBurst();
};

extern "C" {
extern float lbl_80495994[64];
extern char lbl_806D8B70[7];
extern char lbl_806D8B78[5];
void __assert(char *, int, char *);
void Object_RenderJObjTree(void *, int);
void PSVECAdd(Vec3f *, Vec3f *, Vec3f *);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void fn_801712E4(SoundEmitter *, float, float, float, float);
void HSD_JObjSetFlags(HSD_JObj *, int);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void Object_DtorWithGXSync(void *, int);
void *FUN_8003b120(int);
int sprintf(char *, const char *, ...);
HSD_JObj *ResolveJointByName(void *, char *);
void HSD_JObjSetFlagsAll(HSD_JObj *, int);
void HSD_JObjClearFlags(HSD_JObj *, int);
void Vec3_Subtract(Vec3f *, const Vec3f *, Vec3f *);
float PSVECSquareMag(Vec3f *);
float LUT_Sin12Bit(float);
float fn_80186960(float);
}

static const DebrisSpawn sDebrisSpawn[4] = {
    {13, {-43.5f, -55.0f, -4.0f}},
    {11, {40.0f, -55.0f, -5.5f}},
    {10, {68.5f, -55.0f, 72.0f}},
    {9, {-70.5f, -55.0f, 70.5f}},
};
static const char sDebrisModel[0x18] = "KP_challenge_ashi.dat";
static const char sDebrisGroupJoint[0x1C] = "KP_castle_hontai%02d_joint";
static const char sDebrisItemJoint[0x24] = "KP_castle_hahen_%02d_%02d_joint";

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *out) {
    if (jobj == 0) {
        __assert(lbl_806D8B70, 0x3E4, lbl_806D8B78);
    }
    out->x = jobj->translate.x;
    out->y = jobj->translate.y;
    out->z = jobj->translate.z;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D8B70, 0x25D, lbl_806D8B78);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (!clean) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetTranslate(HSD_JObj *jobj, Vec3f *t) {
    if (jobj == 0) {
        __assert(lbl_806D8B70, 0x3A9, lbl_806D8B78);
    }
    jobj->translate.x = t->x;
    jobj->translate.y = t->y;
    jobj->translate.z = t->z;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline float DebrisBurst_Rand(DebrisBurst *self) {
    if (++self->randIdx >= 64) {
        self->randIdx = 0;
    }
    return lbl_80495994[self->randIdx];
}

extern "C" {

void fn_8016DA30(DebrisBurst *self) {
    Object_RenderJObjTree(self->model, 7);
    self->sound->Draw();
}

void fn_8016DA78(DebrisBurst *self) {
    unsigned int g;
    int i;
    Vec3f pos;

    for (g = 0; g < 4; g++) {
        if (self->groups[g].active) {
            for (i = 0; i < sDebrisSpawn[g].count; i++) {
                if (self->groups[g].items[i].alive) {
                    HSD_JObjGetTranslation(self->groups[g].items[i].jobj, &pos);
                    if (self->groups[g].items[i].vel.y > -10.0f) {
                        self->groups[g].items[i].vel.y -= 0.2f;
                    }
                    PSVECAdd(&pos, &self->groups[g].items[i].vel, &pos);
                    HSD_JObjSetTranslate(self->groups[g].items[i].jobj, &pos);
                    if (pos.y < -110.0f) {
                        fn_801712E4(self->sound, pos.x, pos.y, pos.z, 2.5f);
                        HSD_JObjSetFlags(self->groups[g].items[i].jobj, 0x10);
                        self->groups[g].items[i].alive = 0;
                    }
                }
            }
        }
    }
    self->sound->Update();
}

int fn_8016DC90(DebrisBurst *self, Vec3f *at, float radius) {
    unsigned int g;
    int i;
    float range;
    Vec3f d;

    range = 10.0f + radius;
    range = range * range;
    for (g = 0; g < 4; g++) {
        if (!self->groups[g].active) {
            Vec3_Subtract(at, &sDebrisSpawn[g].pos, &d);
            d.y = 0.0f;
            if (PSVECSquareMag(&d) < range) {
                HSD_JObjSetFlagsAll(self->groups[g].root, 0x10);
                for (i = 0; i < sDebrisSpawn[g].count; i++) {
                    HSD_JObjClearFlags(self->groups[g].items[i].jobj, 0x10);
                    self->groups[g].items[i].alive = 1;
                    float angle = 360.0f * DebrisBurst_Rand(self);
                    float speed = 5.0f * DebrisBurst_Rand(self);
                    self->groups[g].items[i].vel.x = speed * LUT_Sin12Bit(angle);
                    self->groups[g].items[i].vel.y = speed * LUT_Sin12Bit(90.0f * DebrisBurst_Rand(self));
                    self->groups[g].items[i].vel.z = speed * fn_80186960(angle);
                }
                self->groups[g].active = 1;
                return g;
            }
        }
    }
    return -1;
}

int fn_8016DEF4(DebrisBurst *self) {
    int n = 0;
    unsigned int g;

    for (g = 0; g < 4; g++) {
        if (self->groups[g].active == 1) {
            n++;
        }
    }
    return n;
}

int fn_8016DF50(DebrisBurst *self) {
    unsigned int g;

    for (g = 0; g < 4; g++) {
        if (self->groups[g].active == 0) {
            return 0;
        }
    }
    return 1;
}

DebrisBurst *fn_8016DFAC(DebrisBurst *self, short flag) {
    unsigned int g;

    if (self) {
        for (g = 0; g < 4; g++) {
            MemoryManager_Free(self->groups[g].items);
        }
        MemoryManager_Free(self->groups);
        Object_DtorWithGXSync(self->model, 1);
        delete self->sound;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}

DebrisBurst::DebrisBurst() {
    unsigned int g;
    int i;
    char name[0x100];

    model = new clNormal3D(sDebrisModel, 0);
    groups = (DebrisGroup *)FUN_8003b120(sizeof(DebrisGroup) * 4);
    for (g = 0; g < 4; g++) {
        sprintf(name, sDebrisGroupJoint, g + 1);
        groups[g].root = ResolveJointByName(model, name);
        groups[g].active = 0;
        groups[g].items = (Debris *)FUN_8003b120(sDebrisSpawn[g].count * sizeof(Debris));
        for (i = 0; i < sDebrisSpawn[g].count; i++) {
            sprintf(name, sDebrisItemJoint, g + 1, i);
            groups[g].items[i].jobj = ResolveJointByName(model, name);
            HSD_JObjSetFlags(groups[g].items[i].jobj, 0x10);
        }
    }
    sound = new SoundEmitter();
    randIdx = 0;
}

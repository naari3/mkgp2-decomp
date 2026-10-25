/*
 * 0x8016DA30..0x8016DC90: debris burst effect (four spawn groups of JObj
 * particles that fall and despawn below the course).
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

struct SoundEmitter {
    virtual ~SoundEmitter();
    virtual void Update();
    virtual void Draw();
};

struct DebrisBurst {
    void *model;
    DebrisGroup *groups;
    SoundEmitter *sound;
    int randIdx;
};

extern "C" {
extern const DebrisSpawn lbl_8036D690[4];
extern char lbl_806D8B70[7];
extern char lbl_806D8B78[5];
void __assert(char *, int, char *);
void Object_RenderJObjTree(void *, int);
void fn_8025E264(Vec3f *, Vec3f *, Vec3f *);
void fn_802D20AC(HSD_JObj *);
void fn_801712E4(SoundEmitter *, float, float, float, float);
void fn_802D07D4(HSD_JObj *, int);
}

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
        fn_802D20AC(jobj);
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
            for (i = 0; i < lbl_8036D690[g].count; i++) {
                if (self->groups[g].items[i].alive) {
                    HSD_JObjGetTranslation(self->groups[g].items[i].jobj, &pos);
                    if (self->groups[g].items[i].vel.y > -10.0f) {
                        self->groups[g].items[i].vel.y -= 0.2f;
                    }
                    fn_8025E264(&pos, &self->groups[g].items[i].vel, &pos);
                    HSD_JObjSetTranslate(self->groups[g].items[i].jobj, &pos);
                    if (pos.y < -110.0f) {
                        fn_801712E4(self->sound, pos.x, pos.y, pos.z, 2.5f);
                        fn_802D07D4(self->groups[g].items[i].jobj, 0x10);
                        self->groups[g].items[i].alive = 0;
                    }
                }
            }
        }
    }
    self->sound->Update();
}

}

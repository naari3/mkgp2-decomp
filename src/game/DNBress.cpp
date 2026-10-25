/*
 * 0x80226954..0x80227FA4: clDNBress (dnBress.cpp), the ice dinosaur's breath
 * on Dino Dino Jungle. When a kart comes close, the dinosaur animation plays,
 * a breath sound starts and fire/frost particles (two variants, picked by the
 * reverse-course flag) are spawned through pointer-to-member tables. Four
 * smoke puffs rise over the lake. The class data (spawn ranges, member
 * function tables, vtable) lives in lbl_804EDF80 and is addressed off one
 * base; the static initializer (fn_80227FA4) stays in asm.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x38 - 0x18];
    Vec3f translate;
    Mtx mtx;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
    ~clNormal3D();
};

struct AnimCtrl {
    char _opaque[0x180];
    AnimCtrl();
    ~AnimCtrl();
};

struct KartRender {
    char pad000[0x23C];
    int x23c;
};

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

struct Particle {
    unsigned char active;
    Vec3f v;
    Vec3f pos;
    float scale;
    float alpha;
    float c[3];
    float speed;
    float grow;
    float dvx;
    float dvy;
    float dvz;
    int delay;
};

struct clMapEffectParts {
    virtual ~clMapEffectParts() {}
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    clMapEffectParts() {}
};

struct clDNBress;
typedef void (clDNBress::*SpawnFn)();
typedef void (clDNBress::*UpdFn)(Particle *p);

struct FireFuncs {
    SpawnFn spawn;
    UpdFn upd;
};

struct clDNBress : clMapEffectParts {
    clNormal3D *model;
    int type;
    unsigned char xc;
    AnimCtrl *anim;
    clNormal3D *x14;
    clNormal3D *fx;
    HSD_JObj *joint;
    float x20;
    Vec3f pos;
    Vec3f dir;
    int randIdx;
    unsigned char sePlaying;
    int cooldown;
    int state;
    int x4c;
    int timer;
    float x54;
    Vec3f x58;
    unsigned char hidden;
    int x68;
    Particle parts[20];
    Particle smoke[4];
    Particle *freeSlot;
    SpawnFn spawn;
    UpdFn upd;

    clDNBress();
    virtual void Enable(int on);
    virtual ~clDNBress();
    virtual void Update();
    virtual void Draw();
    void Tick();
    void UpdFire1(Particle *p);
    void SpawnFire1();
    void UpdFire2(Particle *p);
    void SpawnFire2();
    void Breathe();
};

extern "C" {
extern int g_gameMode;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern KartRender *g_playerRenderObj;
extern const char lbl_806DB3F0[7];
extern const char lbl_806DB3F8[5];
extern const int lbl_806DB3E8[2];
extern float lbl_806D0548[2];
extern float lbl_806D0580;
extern float lbl_806D0584;
extern float lbl_806D0588;
extern const int lbl_803D0240[4][2];
extern const float lbl_803D0260[3];
extern const float lbl_803D026C[3];
extern const float lbl_803D0278[4];
extern const Vec3f lbl_803D02A0[2];
extern float lbl_804EDF80[2][3];
extern FireFuncs lbl_804EDF98[2];
extern float lbl_80495A94[48];
extern const char lbl_803D01BC[];
extern const char lbl_803D01CC[];
extern const char *lbl_803D01DC[];
extern const char lbl_803D0300[];
extern const char lbl_803D0320[];
extern const char lbl_803D0340[];
extern const char lbl_803D0354[];
extern const char lbl_803D037C[];
extern const float lbl_806DB400;
extern const float lbl_806DB404;
extern const float lbl_806DB408;
extern const float lbl_806DB40C;
extern const float lbl_806DB410;
extern const float lbl_806DB414;
extern const float lbl_806DB418;
extern const float lbl_806DB41C;
extern const float lbl_806DB420;
extern const float lbl_806DB424;
extern const float lbl_806DB428;
extern const float lbl_806DB42C;
extern const float lbl_806DB430;
extern const float lbl_806DB434;
extern const float lbl_806DB438;
extern const float lbl_806DB43C;
extern const float lbl_806DB440;
extern const float lbl_806DB444;
extern const float lbl_806DB448;
extern const float lbl_806DB44C;
extern const float lbl_806DB450;
extern const float lbl_806DB454;
extern const float lbl_806DB458;
extern const float lbl_806DB45C;
extern const float lbl_806DB460;
extern const float lbl_806DB464;
extern const float lbl_806DB468;
extern const float lbl_806DB46C;
extern const float lbl_806DB470;
extern const float lbl_806DB474;
extern const float lbl_806DB478;
extern const float lbl_806DB47C;
extern const float lbl_806DB480;
extern const float lbl_806DB484;
void __assert(const char *file, int line, const char *cond);
HSD_JObj *LinkedNode_GetField10_OrFallback(clNormal3D *m, int idx);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void Object_RenderJObjTree(clNormal3D *m, int mask);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXMultVecSR(Mtx m, Vec3f *src, Vec3f *dst);
float PSVECSquareMag(Vec3f *v);
void Object_SetColorRGBA(clNormal3D *m, int idx, float r, float g, float b, float a);
void Object_DriveAnimMatrix(clNormal3D *m);
void clNormal3D_SetScale(clNormal3D *m, int idx, float x, float y, float z, float w);
KartRender *GetKartSlotKartVariant(int slot);
void *GetPlayerCarObject(void);
KartRender *CarObject_GetRenderObj(void *car);
const float *KartDriver_GetKartRootMtx(KartRender *k);
void fn_80240014(AnimCtrl *a);
void fn_8023FE74(AnimCtrl *a, int b, int frame);
void fn_80240378(AnimCtrl *a, const char *file, int b, clNormal3D *m, const char **names);
void SoundMgr_PlaySE(int id);
void fn_8016C288(int id, Vec3f *pos);
void fn_8016C1F8(int id, float vol);
void fn_8016C394(int id);
float LUT_Cosine(float a);
float LUT_Sine(float a);
void DebugPrintf(const char *fmt, ...);
HSD_JObj *ResolveJointByName(clNormal3D *m, const char *name);
void JObj_Hide(clNormal3D *m, HSD_JObj *jobj, int flags);
void fn_80182954(HSD_JObj *jobj, int on);
}

static inline HSD_JObj *GetJObj(clNormal3D *m) {
    HSD_JObj *jobj = LinkedNode_GetField10_OrFallback(m, 0);
    if (jobj == 0) {
        __assert(lbl_806DB3F0, 0x3E4, lbl_806DB3F8);
    }
    return jobj;
}

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB3F0, 0x47C, lbl_806DB3F8);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806DB3F0, 0x25D, lbl_806DB3F8);
        }
        unsigned int flags = jobj->flags;
        unsigned char dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline bool InRect(float x, float z, const float *r) {
    if (x < r[0]) {
        return 0;
    }
    if (x > r[2]) {
        return 0;
    }
    if (z < r[1]) {
        return 0;
    }
    if (z > r[3]) {
        return 0;
    }
    return 1;
}

void clDNBress::Draw() {
    Mtx m;

    if (model == 0) {
        return;
    }
    if (hidden == 1) {
        return;
    }
    GetJObj(model);
    Object_RenderJObjTree(model, 7);
    if (fx == 0) {
        return;
    }
    GXChannel ch(Archive_GetRootJObj(fx), HSD_JObjGetDObj(Archive_GetRootJObj(fx)), 0x40000000, 1);
    for (int i = 0; i < 20; i++) {
        if (parts[i].active) {
            PSMTXScale(m, parts[i].scale, parts[i].scale, parts[i].scale);
            m[0][3] = parts[i].pos.x;
            m[1][3] = parts[i].pos.y;
            m[2][3] = parts[i].pos.z;
            Object_SetColorRGBA(fx, 0, parts[i].c[0], parts[i].c[1], parts[i].c[2], parts[i].alpha);
            ch.PushTransform(m);
        }
    }
    if (g_gameMode == 2) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (smoke[i].active == 1) {
            PSMTXScale(m, smoke[i].scale, smoke[i].scale, smoke[i].scale);
            m[0][3] = smoke[i].pos.x;
            m[1][3] = smoke[i].pos.y;
            m[2][3] = smoke[i].pos.z;
            Object_SetColorRGBA(fx, 0, smoke[i].c[0], smoke[i].c[1], smoke[i].c[2], smoke[i].alpha);
            ch.PushTransform(m);
        }
    }
}

void clDNBress::Update() {
    if (model == 0 || fx == 0) {
        return;
    }
    switch (state) {
    case 0: {
        KartRender *kart = 0;
        for (int i = 0; i < 8; i++) {
            KartRender *k = GetKartSlotKartVariant(i);
            if (k && k->x23c == 0) {
                kart = k;
                break;
            }
        }
        if (kart == 0 && GetPlayerCarObject()) {
            kart = CarObject_GetRenderObj(GetPlayerCarObject());
        }
        if (kart) {
            HSD_JObj *jobj = GetJObj(model);
            Vec3f d;
            d.x = jobj->translate.x;
            d.y = jobj->translate.y;
            d.z = jobj->translate.z;
            d.x = KartDriver_GetKartRootMtx(kart)[3] - d.x;
            d.y = lbl_806DB400;
            d.z = KartDriver_GetKartRootMtx(kart)[11] - d.z;
            if (PSVECSquareMag(&d) < lbl_806D0548[type]) {
                state = 1;
            }
        }
        break;
    }
    case 1:
        fn_80240014(anim);
        Tick();
        if (timer == 0) {
            timer = 0;
            x4c = 0;
            clNormal3D_SetScale(model, 0, lbl_806DB400, lbl_806DB404, lbl_806DB400, lbl_806DB400);
            fn_8023FE74(anim, 0, 0);
        } else if (timer == lbl_806DB3E8[type]) {
            HSD_JObj *jobj = joint;
            SetupJointMatrix(jobj);
            pos.x = jobj->mtx[0][3];
            pos.y = jobj->mtx[1][3];
            pos.z = jobj->mtx[2][3];
            if (g_gameMode != 2) {
                SoundMgr_PlaySE(0x3D);
                fn_8016C288(0x3D, &pos);
                fn_8016C1F8(0x3D, lbl_806DB408);
            }
        } else if (timer >= lbl_803D0240[0][type]) {
            state = 2;
            x4c = 1;
            timer = 0;
            fn_8023FE74(anim, 0, lbl_803D0240[0][type]);
            break;
        }
        timer++;
        break;
    case 2:
        Breathe();
        break;
    case 3:
        fn_80240014(anim);
        Tick();
        if (timer == 0) {
            x4c = 2;
        } else if (timer >= lbl_803D0240[2][type]) {
            state = 4;
            timer = 0;
            break;
        }
        timer++;
        break;
    case 4:
        Tick();
        if (timer != 0 && timer >= lbl_803D0240[3][type]) {
            state = 1;
            timer = 0;
            break;
        }
        timer++;
        break;
    case 5:
        break;
    }
    Object_DriveAnimMatrix(model);
}

void clDNBress::Tick() {
    for (int i = 0; i < 20; i++) {
        if (!parts[i].active) {
            freeSlot = &parts[i];
        } else {
            (this->*upd)(&parts[i]);
            if (parts[i].alpha <= lbl_806DB400) {
                parts[i].active = 0;
            }
        }
    }
    if (g_gameMode == 2) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        Particle *p = &smoke[i];
        if (p->active == 1) {
            p->pos.y = p->v.y * p->speed + p->pos.y;
            p->scale += p->grow;
            p->speed -= lbl_806DB40C;
            p->alpha -= lbl_806DB40C;
            p->c[1] = p->c[2] += lbl_806DB40C;
            if (p->alpha < lbl_806DB400) {
                p->active = 0;
            }
        } else if (p->delay > 0) {
            p->delay--;
        } else {
            p->v.y = lbl_806DB414 * lbl_80495A94[randIdx] + lbl_806DB410;
            p->pos.x = lbl_804EDF80[type][0] * lbl_80495A94[randIdx] + lbl_803D02A0[type].x;
            if (++randIdx >= 48) {
                randIdx = 0;
            }
            p->pos.y = lbl_803D02A0[type].y;
            p->pos.z = lbl_804EDF80[type][2] * lbl_80495A94[randIdx] + lbl_803D02A0[type].z;
            p->scale = lbl_806DB418;
            p->alpha = lbl_806DB41C;
            p->speed = lbl_806DB41C * lbl_80495A94[randIdx] + lbl_806DB404;
            p->grow = lbl_806DB424 * lbl_80495A94[randIdx] + lbl_806DB420;
            p->active = 1;
            p->c[0] = lbl_803D0260[0];
            p->c[1] = lbl_803D0260[1];
            p->c[2] = lbl_803D0260[2];
            if (++randIdx >= 48) {
                randIdx = 0;
            }
        }
    }
}

void clDNBress::UpdFire1(Particle *p) {
    if (p == 0) {
        return;
    }
    p->pos.x = p->v.x * p->speed + p->pos.x;
    p->pos.y = p->v.y * p->speed + p->pos.y;
    p->pos.z = p->v.z * p->speed + p->pos.z;
    p->scale += p->grow;
    p->v.y += p->dvy;
    if (p->v.y > lbl_806DB424) {
        p->v.x *= lbl_806DB428;
        p->v.z *= lbl_806DB428;
        p->v.y += lbl_806DB42C;
        p->c[1] = p->c[2] -= lbl_806DB430;
    } else if (p->v.y > lbl_806DB434) {
        p->v.x *= lbl_806DB438;
        p->v.z *= lbl_806DB438;
        p->c[1] = p->c[2] -= lbl_806DB43C;
        p->dvy *= lbl_806DB440;
    }
    p->v.x += p->dvx;
    p->v.z += p->dvz;
    p->c[1] = p->c[2] -= lbl_806DB444;
    p->speed -= lbl_806DB448;
    if (p->speed <= lbl_806DB424) {
        p->speed = lbl_806DB424;
    }
    p->alpha -= lbl_806DB43C;
}

void clDNBress::SpawnFire1() {
    Particle *p = freeSlot;
    if (p == 0) {
        return;
    }
    p->v.x = dir.x;
    freeSlot->v.y = lbl_806DB44C * dir.y;
    freeSlot->v.z = dir.z;
    freeSlot->pos.x = pos.x;
    freeSlot->pos.y = pos.y;
    freeSlot->pos.z = pos.z;
    freeSlot->scale = lbl_806DB450;
    freeSlot->alpha = lbl_806DB404;
    freeSlot->speed = lbl_806DB414 * lbl_80495A94[randIdx] + lbl_806DB454;
    freeSlot->grow = lbl_806DB424 * lbl_80495A94[randIdx] + lbl_806DB424;
    freeSlot->active = 1;
    freeSlot->c[0] = lbl_803D026C[0];
    freeSlot->c[1] = lbl_803D026C[1];
    freeSlot->c[2] = lbl_803D026C[2];
    freeSlot->dvx = dir.x * lbl_80495A94[randIdx];
    if (++randIdx >= 48) {
        randIdx = 0;
    }
    freeSlot->dvz = dir.z * lbl_80495A94[randIdx];
    freeSlot->dvy = lbl_806DB458;
    if (++randIdx >= 48) {
        randIdx = 0;
    }
    cooldown = 4;
    freeSlot = 0;
}

void clDNBress::UpdFire2(Particle *p) {
    if (p == 0) {
        return;
    }
    p->pos.x = p->v.x * p->speed + p->pos.x;
    p->pos.y = p->v.y * p->speed + p->pos.y;
    p->pos.z = p->v.z * p->speed + p->pos.z;
    p->scale += p->grow;
    p->v.y += p->dvy;
    if (p->v.y > lbl_806DB448) {
        p->dvy = lbl_806DB400;
    } else if (p->v.y > lbl_806DB45C) {
        p->speed -= lbl_806DB460;
        p->v.x *= lbl_806DB464;
        p->v.z *= lbl_806DB464;
        p->c[1] = p->c[2] -= lbl_806DB430;
    } else if (p->v.y > lbl_806DB468) {
        p->v.x *= lbl_806DB464;
        p->v.z *= lbl_806DB464;
        p->c[1] = p->c[2] -= lbl_806DB43C;
    }
    p->v.x += p->dvx;
    p->v.z += p->dvz;
    p->c[1] = p->c[2] -= lbl_806DB46C;
    p->speed -= lbl_806DB470;
    if (p->speed <= lbl_806DB424) {
        p->speed = lbl_806DB424;
    }
    p->alpha -= lbl_806DB43C;
}

void clDNBress::SpawnFire2() {
    Particle *p = freeSlot;
    if (p == 0) {
        return;
    }
    p->v.x = dir.x;
    freeSlot->v.y = lbl_806DB418 * dir.y;
    freeSlot->v.z = dir.z;
    freeSlot->pos.x = pos.x;
    freeSlot->pos.y = pos.y;
    freeSlot->pos.z = pos.z;
    freeSlot->scale = lbl_806DB418;
    freeSlot->alpha = lbl_806DB404;
    freeSlot->speed = lbl_806DB414 * lbl_80495A94[randIdx] + lbl_806DB474;
    freeSlot->grow = lbl_806DB424 * lbl_80495A94[randIdx] + lbl_806DB424;
    freeSlot->active = 1;
    freeSlot->c[0] = lbl_803D026C[0];
    freeSlot->c[1] = lbl_803D026C[1];
    freeSlot->c[2] = lbl_803D026C[2];
    float a = lbl_806DB478 * lbl_80495A94[randIdx] - lbl_806DB47C;
    freeSlot->dvx = dir.x * LUT_Cosine(a);
    freeSlot->dvz = dir.z * LUT_Sine(a);
    freeSlot->dvy = lbl_806DB480;
    if (++randIdx >= 48) {
        randIdx = 0;
    }
    cooldown = 4;
    freeSlot = 0;
}

void clDNBress::Breathe() {
    fn_80240014(anim);
    hidden = 1;
    KartRender *k;
    if ((k = g_playerRenderObj) != 0) {
        float x = KartDriver_GetKartRootMtx(k)[3];
        float z = KartDriver_GetKartRootMtx(k)[11];
        if (InRect(x, z, lbl_803D0278) == 1) {
            hidden = 0;
            if (!sePlaying) {
                if (g_gameMode != 2) {
                    SoundMgr_PlaySE(0x44);
                }
                sePlaying = 1;
            }
        } else if (sePlaying) {
            fn_8016C394(0x44);
            sePlaying = 0;
        }
    }
    if (x68 < 0) {
        fn_8016C394(0x44);
        sePlaying = 0;
    }
    if (sePlaying == 1) {
        dir.x = lbl_806D0580;
        dir.y = lbl_806D0584;
        dir.z = lbl_806D0588;
        HSD_JObj *jobj = joint;
        SetupJointMatrix(jobj);
        float(*m)[4] = jobj->mtx;
        PSMTXMultVecSR(m, &dir, &dir);
        pos.x = m[0][3];
        pos.y = m[1][3];
        pos.z = m[2][3];
        fn_8016C288(0x44, &pos);
    }
    Tick();
    if (cooldown == 0 && sePlaying == 1) {
        (this->*spawn)();
    }
    if (cooldown != 0) {
        cooldown--;
    }
    if (++x68 >= lbl_803D0240[1][type]) {
        fn_8023FE74(anim, 0, lbl_803D0240[0][type]);
        x68 = 0;
    }
    if (++timer >= lbl_803D0240[1][type] * 4) {
        x20 = lbl_806DB400;
        x68 = 0;
        timer = 0;
        sePlaying = 0;
        state = 3;
        fn_8023FE74(anim, 0, lbl_803D0240[1][type] + lbl_803D0240[0][type]);
        fn_8016C394(0x44);
    }
}

clDNBress::~clDNBress() {
    fn_8016C394(0x44);
    if (anim) {
        delete anim;
        anim = 0;
    }
    if (model) {
        delete model;
        model = 0;
    }
    if (x14) {
        delete x14;
        x14 = 0;
    }
    if (fx) {
        delete fx;
        fx = 0;
    }
    DebugPrintf(lbl_803D0300);
}

clDNBress::clDNBress() {
    type = 0;
    xc = 0;
    anim = 0;
    x14 = 0;
    fx = 0;
    joint = 0;
    x20 = lbl_806DB400;
    randIdx = 0;
    sePlaying = 0;
    cooldown = 0;
    state = 0;
    x4c = 0;
    timer = 0;
    x54 = lbl_806DB400;
    hidden = 0;
    x68 = 0;
    freeSlot = 0;
    DebugPrintf(lbl_803D0320);
    model = 0;
    if (g_longRoundFlag == 0) {
        return;
    }
    if (g_reverseRoundFlag == 1) {
        type++;
    }
    anim = new AnimCtrl;
    if (type == 0) {
        model = new clNormal3D(lbl_803D01BC, 0);
        fn_80240378(anim, lbl_803D01BC, 0, model, lbl_803D01DC);
    } else {
        model = new clNormal3D(lbl_803D01CC, 0);
        fn_80240378(anim, lbl_803D01CC, 0, model, lbl_803D01DC);
    }
    if (model) {
        clNormal3D_SetScale(model, 0, lbl_806DB400, lbl_806DB404, lbl_806DB400, lbl_806DB400);
    }
    if (model) {
        if (type == 0) {
            joint = ResolveJointByName(model, lbl_803D0340);
        } else {
            joint = ResolveJointByName(model, lbl_803D0340);
        }
    }
    if (joint == 0) {
        DebugPrintf(lbl_803D0354);
        return;
    }
    fx = new clNormal3D(lbl_803D037C, 1);
    if (fx) {
        JObj_Hide(fx, Archive_GetRootJObj(fx), 4);
        fn_80182954(Archive_GetRootJObj(fx), 1);
        HSD_JObjSetFlags(Archive_GetRootJObj(fx), 0x200);
    }
    for (int i = 0; i < 20; i++) {
        parts[i].active = 0;
        parts[i].c[0] = parts[i].c[1] = parts[i].c[2] = lbl_806DB404;
    }
    for (int i = 0; i < 4; i++) {
        smoke[i].active = 0;
        smoke[i].delay = i * 12 + 45;
        smoke[i].c[0] = lbl_806DB404;
        smoke[i].c[1] = smoke[i].c[2] = lbl_806DB484;
    }
    pos.x = pos.y = pos.z = lbl_806DB400;
    dir.x = dir.y = dir.z = lbl_806DB400;
    x58.x = x58.y = x58.z = lbl_806DB400;
    if (type == 1) {
        spawn = lbl_804EDF98[0].spawn;
        upd = lbl_804EDF98[0].upd;
    } else {
        spawn = lbl_804EDF98[1].spawn;
        upd = lbl_804EDF98[1].upd;
    }
}

#include "game/objview/emitter_private.h"
#include "game/types/clMapEffectParts.h"

class clRBShootingStar : public clMapEffectParts {
public:
    virtual ~clRBShootingStar();
    virtual void Update();
    virtual void Draw();
    clRBShootingStar(clNormal3D *);
    clNormal3D *model, *billboard;
    int count;
    ViewMatrixParticle *matrices;
    ViewBillboardParticle *particles;
    int delay, randomIndex, variationIndex;
};
extern "C" {
void MemoryManager_Free(void *);
void Object_DtorWithGXSync(void *, int);
void *FUN_8003b120(unsigned long);
}
const char lbl_803780C8[]  = "shooting_star.dat";
const char lbl_803780DC[] = "star_dust.dat";
const Vec3f lbl_803780EC[12] = {
    { -112.0f, -112.0f, 0.0f },
    { -188.0f, -194.0f, 0.0f },
    { -258.0f, -268.0f, 0.0f },
    { -320.0f, -336.0f, 0.0f },
    { -380.0f, -400.0f, 0.0f },
    { -433.0f, -460.0f, 0.0f },
    { -484.0f, -520.0f, 0.0f },
    { -530.0f, -574.0f, 0.0f },
    { -570.0f, -622.0f, 0.0f },
    { -608.0f, -670.0f, 0.0f },
    { -632.0f, -704.0f, 0.0f },
    { -650.0f, -724.0f, 0.0f }
};

extern "C" { const void *lbl_806CFC40 = lbl_803780C8; const void *lbl_806CFC44 = lbl_803780DC; }
static inline ViewJoint *child(ViewJoint *p) { if (p == 0) return 0; return p->child; }
static inline ViewJoint *next(ViewJoint *p) { if (p == 0) return 0; return p->next; }
clRBShootingStar::clRBShootingStar(clNormal3D *root) {
    DebugPrintf(" CreateMapEffect : clRBShootingStar\n");
    model = 0; billboard = 0; count = 0; matrices = 0; particles = 0;
    delay = 0; randomIndex = 0; variationIndex = 0;
    ViewJoint *joint = (ViewJoint *)ResolveJointByName(root, "RB_road_rb_star_joint");
    count = 0;
    ViewJoint *j;
    for (j = child(joint); j; j = next(j)) count++;
    if (count == 0) return;
    model = new clNormal3D(lbl_806CFC40, 0);
    clNormal3D_SetScale(model, 0, lbl_806D9440, lbl_806D9460, lbl_806D9440, lbl_806D9440);
    billboard = new clNormal3D(lbl_806CFC44, 1);
    matrices = (ViewMatrixParticle *)FUN_8003b120(count * sizeof(ViewMatrixParticle));
    int i;
    for (i = 0, j = child(joint); i < count && j; i++, j = next(j)) {
        matrices[i].age = lbl_806D944C;
        matrices[i].joint = j;
    }
    for (i = 0; i < count; i++) matrices[i].age = lbl_806D944C;
    particles = (ViewBillboardParticle *)FUN_8003b120(60 * sizeof(ViewBillboardParticle));
    for (i = 0; i < 60; i++) particles[i].age = lbl_806D944C;
}

clRBShootingStar::~clRBShootingStar() {
    if (model) Object_DtorWithGXSync(model, 1);
    if (billboard) Object_DtorWithGXSync(billboard, 1);
    if (matrices) MemoryManager_Free(matrices);
    if (particles) MemoryManager_Free(particles);
    DebugPrintf(" DeleteMapEffect : clRBShootingStar\n");
}


extern "C" {
extern float lbl_80495994[], lbl_80495A94[];
extern const Vec3f lbl_803780EC[12];
extern const float lbl_806D9464, lbl_806D9468, lbl_806D946C;
extern const float lbl_806D9470, lbl_806D9474, lbl_806D9478, lbl_806D947C;
extern char lbl_806D9450[8], lbl_806D9458[8];
void HSD_JObjSetupMatrixSub(ViewJoint *);
}
static inline float variation(clRBShootingStar *o) {
    if (o->variationIndex >= 48) o->variationIndex = 0;
    return lbl_80495A94[o->variationIndex++];
}
static inline void setup(ViewJoint *j) {
    if (!j) __assert(lbl_806D9450, 0x47c, lbl_806D9458);
    if (j) {
        if (!j) __assert(lbl_806D9450, 0x25d, lbl_806D9458);
        unsigned char dirty = 0;
        if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty = 1;
        if (dirty) HSD_JObjSetupMatrixSub(j);
    }
}
static inline void freeParticle(clRBShootingStar *o, ViewBillboardParticle *&out) {
    for (int i = 0; i < 60; i++) {
        if (o->particles[i].age < 0.0f) { out = &o->particles[i]; return; }
    }
    out = 0;
}
static inline void updateParticle(ViewBillboardParticle *q) {
    if (q->age < 0.0f) return;
    q->scale += q->speed;
    if (q->age < 10.0f) q->alpha = q->maxAlpha * (q->age / 10.0f);
    else q->alpha = q->maxAlpha - q->maxAlpha * ((q->age - 10.0f) / 30.0f);
    if ((q->age += 1.0f) > 40.0f) q->age = -1.0f;
}
static inline void initializeMatrix(clRBShootingStar *o, void *scene, int index) {
    ViewJoint *joint;
    o->matrices[index].age = 0.0f;
    joint = o->matrices[index].joint;
    setup(joint);
    PSMTXScale(o->matrices[index].matrix, 1.0f + variation(o), 1.0f, 1.0f);
    PSMTXConcat(o->matrices[index].matrix, *CObj_GetProjMatrix_Cached(scene), o->matrices[index].matrix);
    o->matrices[index].matrix[0][3] = joint->matrix[0][3];
    o->matrices[index].matrix[1][3] = joint->matrix[1][3];
    o->matrices[index].matrix[2][3] = joint->matrix[2][3];
    o->delay = (int)(30.0f + 30.0f * variation(o));
}
static inline void updateMatrices(clRBShootingStar *o, int &i, unsigned int &matrixOffset) {
    unsigned int point;
    ViewMatrixParticle *p;
    ViewBillboardParticle *q;
    for (i = 0, matrixOffset = 0; i < o->count; matrixOffset += sizeof(ViewMatrixParticle), i++) {
        p = (ViewMatrixParticle *)((char *)o->matrices + matrixOffset);
        if (p->age < 0.0f) continue;
        if ((p->age += 1.0f) >= 89.0f) { p->age = -1.0f; continue; }
        if (p->age >= 20.0f) {
            point = ((int)(p->age - 20.0f)) >> 1;
            if (point < 12) {
                freeParticle(o, q);
                if (q) {
                    q->age = 0.0f;
                    q->scale = 0.0f;
                    q->alpha = 0.0f;
                    q->speed = 0.025f + 0.05f * variation(o);
                    q->maxAlpha = 0.5f + 0.5f * variation(o);
                    PSMTXMultVec(p->matrix, &lbl_803780EC[point], &q->pos);
                }
            }
        }
    }
}
static inline void updateBillboards(clRBShootingStar *o) {
    int k;
    ViewBillboardParticle *q;
    unsigned int particleOffset;
    for (k = 0, particleOffset = 0; k < 60; particleOffset += sizeof(ViewBillboardParticle), k++) {
        q = (ViewBillboardParticle *)((char *)o->particles + particleOffset);
        updateParticle(q);
    }
}
void clRBShootingStar::Update() {
    clRBShootingStar *o = this;
    int index;
    int matrixIndex;
    unsigned int matrixOffset;
    void *scene;
    if (o->count == 0) return;
    if (o->delay > 0) o->delay--;
    else {
        if (o->randomIndex >= 64) o->randomIndex = 0;
        float random = lbl_80495994[o->randomIndex++];
        index = (int)(o->count * random);
        if (-1.0f == o->matrices[index].age) {
            scene = GetCourseScene3D();
            initializeMatrix(o, scene, index);
        }
    }
    updateMatrices(o, matrixIndex, matrixOffset);
    updateBillboards(o);
}



void clRBShootingStar::Draw() {
    clRBShootingStar *o = this;
    int i;
    ViewMatrixParticle *p;
    ViewBillboardParticle *q;
    Mtx *view;
    Vec3f pos;
    if (o->count == 0) return;
    view = CObj_GetProjMatrix_Cached(GetCourseScene3D());
    for (i = 0; i < o->count; i++) {
        p = &o->matrices[i];
        if (!(p->age < lbl_806D9440)) {
            pos.x = p->matrix[0][3];
            pos.y = p->matrix[1][3];
            pos.z = p->matrix[2][3];
            if (fn_801379F0(&pos, lbl_806D9444)) {
                Object_SetField8_AndDirty(o->model, p->age);
                Object_SetAnimBinding(o->model, p->matrix, 0);
                clNormal3D_Exec(o->model);
                Object_DriveAnimMatrix(o->model);
                Object_RenderJObjTree(o->model, 7);
            }
        }
    }
    GXChannel ch(Archive_GetRootJObj(o->billboard), HSD_JObjGetDObj(Archive_GetRootJObj(o->billboard)), 0x40000000, 1);
    Mtx m;
    for (i = 0; i < 60; i++) {
        q = &o->particles[i];
        /* regalloc_patterns 73: the age test spells the element out again, so
         * the address becomes a CSE temp that is coloured before the split
         * temp of the shared counter (q r30, i r29). */
        if (!(o->particles[i].age < lbl_806D9440) && fn_801379F0(&q->pos, lbl_806D9448)) {
            PSMTXScale(m, q->scale, q->scale, q->scale);
            PSMTXConcat(m, *view, m);
            m[0][3] = q->pos.x;
            m[1][3] = q->pos.y;
            m[2][3] = q->pos.z;
            Object_SetColorAlphaOnly(o->billboard, 0, q->alpha);
            GXChannel_PushTransform(&ch, m);
        }
    }
}



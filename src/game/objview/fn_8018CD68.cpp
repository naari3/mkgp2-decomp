/* clPCFruit: animated fruit joints in Pac-Man Stadium. */
#include "game/types/Vec3.h"
#include "game/types/HSD_JObj.h"
#include "game/types/clMapEffectParts.h"
#include "game/types/clNormal3D.h"
extern "C" {
extern char lbl_806D93A8[7], lbl_806D93B0[5];
extern const float lbl_806D93B8, lbl_806D93BC;
void __assert(const char *, int, const char *);
unsigned char fn_801379F0(Vec3 *, float);
void Object_RenderJObjEx(void *, HSD_JObj *, int);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void Object_DtorWithGXSync(void *, int);
void DebugPrintf(const char *, ...);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
}
struct clPCFruit : clMapEffectParts {
    clNormal3D *model;
    HSD_JObj *joint;
    clPCFruit();
    virtual ~clPCFruit();
    virtual void Update();
    virtual void Draw();
};
static inline HSD_JObj *JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj *JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline void JObjGetTranslation(HSD_JObj *jobj, Vec3 *t) {
    if (!jobj) {
        __assert(lbl_806D93A8, 0x3e4, lbl_806D93B0);
    }
    t->x = jobj->translate.x;
    t->y = jobj->translate.y;
    t->z = jobj->translate.z;
}

static inline unsigned char JObjMtxIsDirty(HSD_JObj *jobj) {
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D93A8, 0x25d, lbl_806D93B0);
    }
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void JObjAddRotationZ(HSD_JObj *jobj, float z) {
    if (!jobj) {
        __assert(lbl_806D93A8, 0x41d, lbl_806D93B0);
    }
    jobj->rotate.y += z;
    if (!(jobj->flags & 0x2000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}


clPCFruit::clPCFruit() {
    DebugPrintf(" CreateMapEffect : clPCFruit\n");
    model = 0;
    joint = 0;
    model = new clNormal3D("PCA_anim_fruits.dat", 0);
    joint = ResolveJointByName(model, "PC_land_anim_fruits_joint");
}
clPCFruit::~clPCFruit() {
    if (model != 0) delete model;
    DebugPrintf(" DeleteMapEffect : clPCFruit\n");
}
void clPCFruit::Update() {
    HSD_JObj *jobj;

    if (model == 0 || joint == 0) {
        return;
    }
    for (jobj = JObjGetChild(joint); jobj != 0; jobj = JObjGetNext(jobj)) {
        JObjAddRotationZ(jobj, lbl_806D93BC);
    }
}
void clPCFruit::Draw() {
    HSD_JObj *jobj;
    Vec3 v;

    if (model == 0 || joint == 0) {
        return;
    }
    for (jobj = JObjGetChild(joint); jobj != 0; jobj = JObjGetNext(jobj)) {
        JObjGetTranslation(jobj, &v);
        if (fn_801379F0(&v, lbl_806D93B8)) {
            Object_RenderJObjEx(model, jobj, 7);
        }
    }
}

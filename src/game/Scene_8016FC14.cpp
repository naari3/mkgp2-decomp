/* clKPSekizou: placed stone statue map effect. */
#include "game/types/HSD_JObj.h"

#include "game/types/clNormal3D.h"
#include "game/types/clMapEffectParts.h"
#include "game/types/Vec3f.h"

extern "C" {
extern char lbl_806D8C7C[7];
extern char lbl_806D8C84[5];
extern int g_reverseRoundFlag;
void DebugPrintf(const char *, ...);
int fn_8016C394(int);
void Object_GetJObjPositionVec(void *, Vec3f *);
unsigned char fn_801379F0(Vec3f *, float);
void Object_RenderJObjTree(void *, int);
void __assert(char *, int, char *);
void Object_SetJObjPositionX(clNormal3D *, float);
void Object_SetJObjPositionY(clNormal3D *, float);
void Object_SetJObjField40(clNormal3D *, float);
void Object_SetJObjRotationY(clNormal3D *, float);
}

static inline float HSD_JObjGetTranslationX(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D8C7C, 0x3F1, lbl_806D8C84);
    }
    return jobj->translate.x;
}

static inline float HSD_JObjGetTranslationY(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D8C7C, 0x3FD, lbl_806D8C84);
    }
    return jobj->translate.y;
}

static inline float HSD_JObjGetTranslationZ(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D8C7C, 0x409, lbl_806D8C84);
    }
    return jobj->translate.z;
}



struct clKPSekizou : clMapEffectParts {
    clNormal3D *model;

    clKPSekizou(HSD_JObj *at);
    virtual ~clKPSekizou();
    virtual void Update();
    virtual void Draw();
};


clKPSekizou::clKPSekizou(HSD_JObj *at) {
    DebugPrintf(" CreateMapEffect : clKPSekizou\n");
    model = 0;
    model = new clNormal3D("KP_sekizou.dat", 0);
    if (model) {
        if (at) {
            Object_SetJObjPositionX(model, HSD_JObjGetTranslationX(at));
            Object_SetJObjPositionY(model, HSD_JObjGetTranslationY(at));
            Object_SetJObjField40(model, HSD_JObjGetTranslationZ(at));
        }
        if (g_reverseRoundFlag == 0) {
            Object_SetJObjRotationY(model, -0.785398f);
        } else {
            Object_SetJObjRotationY(model, 1.570796f);
        }
    }
}



clKPSekizou::~clKPSekizou() {
    fn_8016C394(0x34);
    if (model) {
        delete model;
    }
    DebugPrintf(" DeleteMapEffect : clKPSekizou\n");
}

void clKPSekizou::Update() {}

void clKPSekizou::Draw() {
    Vec3f pos;
    if (model) {
        Object_GetJObjPositionVec(model, &pos);
        if (fn_801379F0(&pos, 450.0f)) {
            Object_RenderJObjTree(model, 7);
        }
    }
}

/*
 * 0x8016FD0C..0x8016FE44: constructor of a single placed course model
 * (vtable lbl_8049123C, base vtable lbl_80490FE0). Real C++ for its EH
 * actions; mangled names are bridged in tools/extab_user_renames.json.
 */

struct HSD_JObj {
    char pad00[0x38];
    float tx;
    float ty;
    float tz;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(void *res, int flags);
};

extern "C" {
extern char lbl_8036E0E8[];
extern char lbl_8036E108[];
extern char lbl_806D8C7C[7];
extern char lbl_806D8C84[5];
extern int g_reverseRoundFlag;
void DebugPrintf(const char *, ...);
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
    return jobj->tx;
}

static inline float HSD_JObjGetTranslationY(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D8C7C, 0x3FD, lbl_806D8C84);
    }
    return jobj->ty;
}

static inline float HSD_JObjGetTranslationZ(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D8C7C, 0x409, lbl_806D8C84);
    }
    return jobj->tz;
}

struct CourseMarkerBase {
    virtual void vKeyFunction();
    virtual ~CourseMarkerBase();
    CourseMarkerBase() {}
};

struct CourseModel : CourseMarkerBase {
    clNormal3D *model;

    CourseModel(HSD_JObj *at);
    virtual void vKeyFunction3();
};

#pragma exceptions on

CourseModel::CourseModel(HSD_JObj *at) {
    DebugPrintf(lbl_8036E0E8);
    model = 0;
    model = new clNormal3D(lbl_8036E108, 0);
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

#pragma exceptions reset

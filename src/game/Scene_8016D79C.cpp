/* clKPCandle: course candle markers, 0x8016D79C..0x8016DA30.
 * Deferred generation puts the definitions in reverse address order.
 * RTTI, the base list and the virtual table are compiler generated.
 */
#include "game/types/Vec3f.h"
#include "game/types/HSD_JObj.h"
#include "game/types/clNormal3D.h"
#include "game/types/clMapEffectParts.h"

struct MarkerSource {
    char pad00[0x10];
    HSD_JObj *chain;
};

struct clKPCandle : clMapEffectParts {
    virtual ~clKPCandle();
    virtual void Update();
    virtual void Draw();
    clNormal3D *model;
    HSD_JObj *chain;
    clKPCandle(MarkerSource *src);
};

extern "C" {
extern char lbl_806D8B48[7];
extern char lbl_806D8B50[5];
void __assert(char *, int, char *);
unsigned char fn_801379F0(Vec3f *, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_RenderJObjTree(void *, int);
void clNormal3D_Exec(void *);
void DebugPrintf(const char *, ...);
HSD_JObj *Archive_GetRootJObj(clNormal3D *);
void HSD_JObjClearFlagsAll(HSD_JObj *, int);
void HSD_JObjSetFlagsAll(HSD_JObj *, int);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
void Object_SetJObjScaleXYZ(clNormal3D *, float, float, float);
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *out) {
    if (jobj == 0) {
        __assert(lbl_806D8B48, 0x3E4, lbl_806D8B50);
    }
    out->x = jobj->translate.x;
    out->y = jobj->translate.y;
    out->z = jobj->translate.z;
}

clKPCandle::clKPCandle(MarkerSource *src) {
    DebugPrintf(" CreateMapEffect : clKPCandle\n");
    model = 0;
    chain = 0;
    model = new clNormal3D("candlefire.dat", 0);
    if (model == 0) {
        return;
    }
    HSD_JObjClearFlagsAll(Archive_GetRootJObj(model), 0xE00);
    HSD_JObjSetFlagsAll(Archive_GetRootJObj(model), 0x400);
    clNormal3D_SetScale(model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjScaleXYZ(model, 1.5f, 1.5f, 1.5f);
    chain = src == 0 ? 0 : src->chain;
}


clKPCandle::~clKPCandle() {
    if (model) {
        delete model;
    }
    DebugPrintf(" DeleteMapEffect : clKPCandle\n");
}

void clKPCandle::Update() {
    if (model) {
        clNormal3D_Exec(model);
    }
}

void clKPCandle::Draw() {
    HSD_JObj *jobj;
    Vec3f pos;

    if (model == 0) {
        return;
    }
    for (jobj = chain; jobj != 0; jobj = jobj->next) {
        HSD_JObjGetTranslation(jobj, &pos);
        pos.y += 8.0f;
        if (fn_801379F0(&pos, 10.0f)) {
            Object_SetJObjPositionVec(model, &pos);
            Object_RenderJObjTree(model, 7);
        }
    }
}

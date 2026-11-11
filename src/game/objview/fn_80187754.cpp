#include "game/types/clMapEffectParts.h"
#include "game/types/clNormal3D.h"

extern "C" {
void DebugPrintf(const char *fmt, ...);
void Object_SetJObjPositionXYZ(void *, float, float, float);
void Object_SetJObjRotationY(void *, float);
void Object_RenderJObjTree(void *, int);
}

struct clMRLightHouse : clMapEffectParts {
    clNormal3D *jobj;
    float rot;
    clMRLightHouse();
    virtual ~clMRLightHouse();
    virtual void Update();
    virtual void Draw();
};

clMRLightHouse::clMRLightHouse() {
    DebugPrintf(" CreateMapEffect : clMRLightHouse\n");
    jobj = 0;
    rot = 0.0f;
    jobj = new clNormal3D("MRA_lighthouse_C.dat", 0);
    Object_SetJObjPositionXYZ(jobj, -1258.0f, 458.0f, -4584.0f);
}

clMRLightHouse::~clMRLightHouse() {
    if (jobj) {
        delete jobj;
    }
    DebugPrintf(" DeleteMapEffect : clMRLightHouse\n");
}

void clMRLightHouse::Update() {
    if (jobj) {
        rot += 0.006283186f;
        if (rot >= 6.2831855f) {
            rot -= 6.2831855f;
        }
        Object_SetJObjRotationY(jobj, rot);
    }
}

void clMRLightHouse::Draw() {
    if (jobj) {
        Object_RenderJObjTree(jobj, 7);
    }
}

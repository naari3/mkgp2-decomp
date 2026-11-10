#ifndef MAPOBJECT17B_PRIVATE_H
#define MAPOBJECT17B_PRIVATE_H

typedef float Mtx[3][4];

#include "game/types/Vec3f.h"

#include "game/types/ModelPath.h"

#include "game/types/ModelDef.h"

#include "game/types/ModelEntry.h"

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x4];
    float rotX;
    float rotY;
    float rotZ;
    char pad28[0x10];
    Vec3f translate;
};

class clNormal3D {
public:
    clNormal3D(const void *desc, int flags);
    char pad[0x5C];
};

extern "C" {
extern const char lbl_80376138[];
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
HSD_JObj *Archive_GetRootJObj(clNormal3D *);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
void DebugPrintf(const char *fmt, ...);
void PSMTXRotRad(Mtx m, char axis, float rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
void fn_80181EA4(const Vec3f *p0, const Vec3f *p1, const Vec3f *p2, Vec3f *out, float t);
double atan2(double y, double x);
extern char lbl_806D8EA8[7];
extern char lbl_806D8EB0[5];
extern char lbl_803761A0[];
extern char lbl_803761AC[];
extern float lbl_806D15F0;
void __assert(char *, int, char *);
void HSD_JObjReqAnimAll(HSD_JObj *, float);
void HSD_JObjAnimAll(HSD_JObj *);
void HSD_JObjDispAll(HSD_JObj *, int, int, int);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void PSVECAdd(const Vec3f *, const Vec3f *, Vec3f *);
unsigned char fn_80137718(Vec3f *pos, Vec3f *view, float radius);
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *translate) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x3E4, lbl_806D8EB0);
    }
    *translate = jobj->translate;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x25D, lbl_806D8EB0);
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

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, float x) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2A4, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2A5, lbl_803761AC);
    }
    jobj->rotX = x;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2B8, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2B9, lbl_803761AC);
    }
    jobj->rotY = y;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, float z) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x2CC, lbl_806D8EB0);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D8EA8, 0x2CD, lbl_803761AC);
    }
    jobj->rotZ = z;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslate(HSD_JObj *jobj, const Vec3f *translate) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x3A9, lbl_806D8EB0);
    }
    if (translate == 0) {
        __assert(lbl_806D8EA8, 0x3AA, lbl_803761A0);
    }
    jobj->translate = *translate;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

class clModel {
public:
    clModel *next;
    ModelDef *def;
    HSD_JObj *jobj;
    float frame;
    Vec3f offset;
    virtual void Update();
    virtual void Draw();

    clModel(clNormal3D *obj, ModelDef *d) {
        next = 0;
        def = d;
        jobj = 0;
        frame = 0.0f;
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
        if (obj != 0 && def != 0) {
            if (def->flags & 4) {
                jobj = Archive_GetRootJObj(obj);
            } else {
                jobj = ResolveJointByName(obj, def->name);
                if (jobj == 0) {
                    DebugPrintf(lbl_80376138, def->name);
                }
            }
            if (def->flags & 8) {
                offset.y = def->height;
            }
            if (def->flags & 0x10) {
                offset.y = 0.5f * def->height;
            }
        }
    }
    ~clModel();
    void Append(clModel *m);
    inline void UpdateFrame();
};

inline void clModel::UpdateFrame() {
    if (def->flags & 1) {
        if ((frame += 1.0f) > def->frameEnd) {
            frame = 0.0f;
        }
    }
}

#include "game/types/clModelP.h"

#include "game/types/ModelParam.h"

#include "game/types/clModelPR.h"

class clModelM : public clModel {
public:
    ModelPath *path;
    Vec3f p0;
    Vec3f p1;
    Vec3f p2;
    int index;
    float t;
    Vec3f pos;
    Vec3f prevPos;
    float heading;

    clModelM(clNormal3D *obj, ModelDef *d);
    virtual void Update();
    virtual void Draw();

    Vec3f &Point(int i) {
        int n = path->count;
        if (i >= n) {
            i -= n;
        }
        return path->points[i];
    }
    void LoadSegment() {
        p0 = Point(index);
        p1 = Point(index + 1);
        p2 = Point(index + 2);
        p0.x = 0.5f * (p0.x + p1.x);
        p0.y = 0.5f * (p0.y + p1.y);
        p0.z = 0.5f * (p0.z + p1.z);
        p2.x = 0.5f * (p1.x + p2.x);
        p2.y = 0.5f * (p1.y + p2.y);
        p2.z = 0.5f * (p1.z + p2.z);
    }
};

#include "game/types/clModelGroup.h"

#endif

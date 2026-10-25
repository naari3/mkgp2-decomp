#ifndef MAPOBJECT_H
#define MAPOBJECT_H

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct ModelPath {
    Vec3f *points;
    int count;
    float speed;
};

struct ModelDef {
    const char *name;
    int type;
    float height;
    float frameEnd;
    unsigned int flags;
    void *param;
    char pad18[0x4];
};

struct ModelEntry {
    const void *desc;
    ModelDef *defs;
};

class clNormal3D {
public:
    clNormal3D(const void *desc, int flags);
    char pad[0x5C];
};

extern "C" {
extern const char lbl_80376138[];
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
void *Archive_GetRootJObj(clNormal3D *);
void *ResolveJointByName(clNormal3D *, const char *);
void DebugPrintf(const char *fmt, ...);
void PSMTXRotRad(Mtx m, char axis, float rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
void fn_80181EA4(const Vec3f *p0, const Vec3f *p1, const Vec3f *p2, Vec3f *out, float t);
double atan2(double y, double x);
}

class clModel {
public:
    clModel *next;
    ModelDef *def;
    void *jobj;
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

#endif

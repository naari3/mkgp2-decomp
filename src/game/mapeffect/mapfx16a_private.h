#ifndef MAPFX16A_PRIVATE_H
#define MAPFX16A_PRIVATE_H
#include "game/mapobject/mapobject.h"

struct MapPart16A {
    MapPart16A() {}
    virtual ~MapPart16A();
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int);
};
struct Zone16A {
    void *data;
    Zone16A(const void *, int);
};
struct Motion16A {
    HSD_JObj *joint;
    int state;
    float unused, frame;
    Vec3f pos;
    float rot;
};
struct Desc16A {
    const char *name;
    Vec3f start;
    float rot;
    Vec3f end;
    float unused;
};
struct Desc16ARaw {
    const char *name;
    unsigned int w[8];
};
struct Jungle16A : MapPart16A {
    clNormal3D *model;
    Zone16A *zone;
    Motion16A *motions;
    Jungle16A();
    virtual ~Jungle16A();
};
struct DObj16A {
    void *parent;
    DObj16A *next;
    void *material;
};
struct TObj16A { char pad[0x48]; unsigned char s, t; };
struct Obj16A { char pad[0x18]; unsigned char flag; char tail[3]; Obj16A(); };
struct Cave16A : MapPart16A {
    Obj16A *model;
    Zone16A *zone;
    unsigned char hit;
    clNormal3D *archive;
    float alpha;
    Cave16A();
    virtual ~Cave16A();
};
extern "C" {
extern const char Jungle16ACtor_rodata_8036CA00[];
extern const Desc16ARaw Jungle16AUpdate_rodata_8036CE88[];
extern const float lbl_806D8A40, lbl_806D8A54, lbl_806D8A58, lbl_806D8A5C;
extern const float lbl_806D8A60, lbl_806D8A64, lbl_806D8A68, lbl_806D8A70;
extern char lbl_806D8A44[7], lbl_806D8A4C[5];
extern const char lbl_8036CEF0[], lbl_8036CEFC[];
extern void *Jungle16ACtor_data_806CFA00;
extern int g_longRoundFlag;
void *FUN_8003b120(unsigned long);
DObj16A *HSD_JObjGetDObj(HSD_JObj *);
TObj16A *HSD_MObjGetTObj(void *);
void Object_RenderJObjEx(clNormal3D *, HSD_JObj *, int);
void *GetKartSlotKartVariant(int);
float *KartDriver_GetKartRootMtx(void *);
unsigned char fn_80123480(Zone16A *, Vec3f *);
float fn_80186960(float);
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
float *CObj_GetViewMatrix_Cached(void *);
float Vec3_Dot(const Vec3f *, const Vec3f *);
}
static inline unsigned char Dirty16A(HSD_JObj *j) {
    if (!j) __assert(lbl_806D8A44, 0x25d, lbl_806D8A4C);
    unsigned char ret = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) ret = 1;
    return ret;
}
static inline void SetDirty16A(HSD_JObj *j) {
    if (j && !Dirty16A(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline void Translate16A(HSD_JObj *j, const Vec3f *p) {
    if (!j) __assert(lbl_806D8A44, 0x3a9, lbl_806D8A4C);
    if (!p) __assert(lbl_806D8A44, 0x3aa, (char *)lbl_8036CEF0);
    j->translate.x = p->x; j->translate.y = p->y; j->translate.z = p->z;
    if (!(j->flags & 0x2000000)) SetDirty16A(j);
}
static inline void Rotate16A(HSD_JObj *j, float y) {
    if (!j) __assert(lbl_806D8A44, 0x2b8, lbl_806D8A4C);
    if (j->flags & 0x20000) __assert(lbl_806D8A44, 0x2b9, (char *)lbl_8036CEFC);
    j->rotY = y;
    if (!(j->flags & 0x2000000)) SetDirty16A(j);
}
#endif

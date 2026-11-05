#include "game/mapobject/mapobject.h"

void *operator new(unsigned long);
void operator delete(void *) throw();

struct Obj987Base {
    Obj987Base() {}
    virtual ~Obj987Base();
};
struct Obj987Entry {
    clNormal3D *model;
    HSD_JObj *joint1;
    HSD_JObj *joint2;
    int state;
};
struct Obj987Position { Vec3f pos; float yaw; };
struct Obj987Particle { float x, y, z; char rest[0x48 - 12]; };
struct Obj987 : Obj987Base {
    Obj987Entry *items;
    int count;
    clNormal3D *child;
    Obj987Particle *particles;
    int x14, x18, x1c;
    Obj987();
    virtual ~Obj987();
};
extern "C" {
extern const char lbl_8037DB78[];
extern int g_longRoundFlag, g_courseVariantIdx;
void *FUN_8003b120(unsigned long);
void Object_SetJObjPositionVec(clNormal3D *, const Vec3f *);
void Object_SetJObjRotationY(clNormal3D *, float);
}

Obj987::Obj987() {
    const char *resource;
    const Obj987Position *positions;
    int i;
    const Obj987Position *walker;
    const char *data = lbl_8037DB78;
    DebugPrintf(data + 0xac);
    items = 0;
    count = 0;
    child = 0;
    particles = 0;
    x14 = 0;
    x18 = 0;
    x1c = 0;
    resource = 0;
    if (g_longRoundFlag == 0) {
        switch (g_courseVariantIdx) {
        case 0: resource = data + 0xcc; break;
        case 1: resource = data + 0xec; break;
        case 2: resource = data + 0x10c; break;
        }
        positions = (const Obj987Position *)data;
        count = 2;
    } else {
        switch (g_courseVariantIdx) {
        case 0: resource = data + 0x12c; break;
        case 1: resource = data + 0x14c; break;
        case 2: resource = data + 0x16c; break;
        }
        positions = (const Obj987Position *)(data + 0x20);
        count = 4;
    }
    if (resource == 0 || positions == 0 || count <= 0) return;
    items = (Obj987Entry *)FUN_8003b120(count * sizeof(Obj987Entry));
    walker = positions;
    for (i = 0; i < count; i++, walker++) {
        items[i].model = new clNormal3D(resource, 0);
        clNormal3D_SetScale(items[i].model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Object_SetJObjPositionVec(items[i].model, &walker->pos);
        Object_SetJObjRotationY(items[i].model, walker->yaw);
        items[i].joint1 = ResolveJointByName(items[i].model, data + 0x18c);
        items[i].joint2 = ResolveJointByName(items[i].model, data + 0x1a8);
        items[i].state = 0;
    }
    child = new clNormal3D(data + 0x1c0, 1);
    particles = (Obj987Particle *)FUN_8003b120(60 * sizeof(Obj987Particle));
    for (i = 0; i < 60; i++) particles[i].z = -1.0f;
}

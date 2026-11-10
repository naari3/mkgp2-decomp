#include "game/types/size_t.h"
#include "game/mapobject/mapobject.h"

void *operator new(size_t);
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
// Original shared pool: short/long placements, origin, type names and resources.
extern "C" const Obj987Position lbl_8037DB78[2] = {
    {{973.456787109375f, 447.79998779296875f, -2931.159912109375f}, -0.5060005784034729f},
    {{1366.4639892578125f, 447.79998779296875f, -2712.1298828125f}, -0.5060005784034729f},
};
extern "C" const Obj987Position lbl_8037DB98[4] = {
    {{928.9713134765625f, 463.651611328125f, -2973.179931640625f}, -0.5152333974838257f},
    {{2680.0f, 295.0f, -3675.0f}, -9.155996322631836f},
    {{3530.0f, 190.0f, -3650.0f}, -9.805992126464844f},
    {{3750.0f, 63.0f, -2830.179931640625f}, 0.9075711965560913f},
};
// Shared origin used by the nearest-particle calculation in fn_801980C8.
extern "C" const Vec3f lbl_8037DBD8 = {0.0f, 0.0f, 0.0f};
extern "C" const char lbl_8037DBE4[12] = "clWCYukinko";
extern "C" const char lbl_8037DBF0[17] = "clMapEffectParts";
extern "C" const char lbl_8037DC04[32] = " DeleteMapEffect : clWCYukinko\n";
extern "C" const char lbl_8037DC24[32] = " CreateMapEffect : clWCYukinko\n";
extern "C" const char lbl_8037DC44[30] = "map_chara_yukinko_short_A.dat";
extern "C" const char lbl_8037DC64[30] = "map_chara_yukinko_short_B.dat";
extern "C" const char lbl_8037DC84[30] = "map_chara_yukinko_short_C.dat";
extern "C" const char lbl_8037DCA4[29] = "map_chara_yukinko_long_A.dat";
extern "C" const char lbl_8037DCC4[29] = "map_chara_yukinko_long_B.dat";
extern "C" const char lbl_8037DCE4[29] = "map_chara_yukinko_long_C.dat";
extern "C" const char lbl_8037DD04[26] = "map_chara_uv_effect_joint";
extern "C" const char lbl_8037DD20[22] = "map_chara_mouth_joint";
extern "C" const char lbl_8037DD38[16] = "ef_snowmark.dat";
extern "C" {
extern int g_longRoundFlag, g_courseVariantIdx;
void *FUN_8003b120(unsigned long);
void Object_SetJObjPositionVec(clNormal3D *, const Vec3f *);
void Object_SetJObjRotationY(clNormal3D *, float);
}

Obj987::Obj987() {
    int i;
    const char *resource;
    const Obj987Position *positions;
    DebugPrintf(lbl_8037DC24);
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
        case 0: resource = lbl_8037DC44; break;
        case 1: resource = lbl_8037DC64; break;
        case 2: resource = lbl_8037DC84; break;
        }
        positions = lbl_8037DB78;
        count = 2;
    } else {
        switch (g_courseVariantIdx) {
        case 0: resource = lbl_8037DCA4; break;
        case 1: resource = lbl_8037DCC4; break;
        case 2: resource = lbl_8037DCE4; break;
        }
        positions = lbl_8037DB98;
        count = 4;
    }
    if (resource == 0 || positions == 0 || count <= 0) return;
    items = (Obj987Entry *)FUN_8003b120(count * sizeof(Obj987Entry));
    for (i = 0; i < count; i++) {
        items[i].model = new clNormal3D(resource, 0);
        clNormal3D_SetScale(items[i].model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Object_SetJObjPositionVec(items[i].model, &positions[i].pos);
        Object_SetJObjRotationY(items[i].model, positions[i].yaw);
        items[i].joint1 = ResolveJointByName(items[i].model, lbl_8037DD04);
        items[i].joint2 = ResolveJointByName(items[i].model, lbl_8037DD20);
        items[i].state = 0;
    }
    child = new clNormal3D(lbl_8037DD38, 1);
    particles = (Obj987Particle *)FUN_8003b120(60 * sizeof(Obj987Particle));
    for (i = 0; i < 60; i++) particles[i].z = -1.0f;
}

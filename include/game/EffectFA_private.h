#ifndef EFFECT_FA_PRIVATE_H
#define EFFECT_FA_PRIVATE_H
#include "game/mapobject/mapobject.h"

struct MapEffectPart {
    HSD_JObj *joint;
    int frame;
    float time, x, scale, y;
};
struct MapEffectFA {
    Vec3f position;
    float radius;
    unsigned char active, released;
    char pad12[2];
    int state;
    float timer, phase, alpha, yaw;
    unsigned char soundPlayed;
    char pad29[3];
    MapEffectPart parts[6];
    MapEffectFA();
};
struct MapEffectDef {
    int model;
    const char *joint;
    void *animation;
};
extern "C" {
extern int lbl_806D15D8;
extern clNormal3D *lbl_806D15D0;
extern HSD_JObj *lbl_806D15D4;
extern clNormal3D *lbl_80491224[3];
extern const char *EffectFA_Ctor_data_80491218[3];
extern const char EffectFA_Ctor_rodata_8036D960[];
extern char lbl_80495988[];
extern const float lbl_806D8C28, lbl_806D8C30, lbl_806D8C74;
void HSD_JObjSetFlagsAll(HSD_JObj *, unsigned int);
void fn_801825FC();
void fn_801825C8();
void fn_801826F8(HSD_JObj *, void *);
}


#endif

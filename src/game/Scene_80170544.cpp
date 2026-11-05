/* clKPThunder constructor, 0x80170544..0x801706C8.
 * Native string pool 0x8036E118..0x8036E21C also supplies the existing
 * destructor/RTTI users. The following four alignment bytes remain in fallback.
 */
#include "game/Scene_80170544_private.h"

extern "C" {
extern const char lbl_8036E118[0xC] = "clKPThunder";
extern const char lbl_8036E124[0x14] = "clMapEffectParts";
extern const char lbl_8036E138[0x20] = " DeleteMapEffect : clKPThunder\n";
extern const char lbl_8036E158[0x20] = " CreateMapEffect : clKPThunder\n";
extern const char lbl_8036E178[0x10] = "skythunder.dat";
extern const char lbl_8036E188[0x14] = "KP_sky_kasan.dat";
extern const char lbl_8036E19C[0x20] = "ef_sky_thunder_thunder1_joint";
extern const char lbl_8036E1BC[0x20] = "ef_sky_thunder_thunder2_joint";
extern const char lbl_8036E1DC[0x20] = "ef_sky_thunder_thunder3_joint";
extern const char lbl_8036E1FC[0x20] = "ef_sky_thunder_thunder4_joint";
extern const float lbl_806D8CD4;
void DebugPrintf(const char *, ...);
void fn_801825FC();
void fn_801825C8();
void Object_SetJObjScaleXYZ(clNormal3D *, float, float, float);
void *ResolveJointByName(clNormal3D *, const char *);
}

static inline SparkJoint *GetChild(SparkJoint *j) {
    if (j == 0) return 0;
    return j->child;
}

SparkModels::SparkModels(SparkJoint *at) {
    DebugPrintf(lbl_8036E158);
    modelA = 0;
    modelB = 0;
    sparks[0].active = 0;
    sparks[1].active = 0;
    sparks[2].active = 0;
    sparks[3].active = 0;
    sparks[4].active = 0;
    joints[0] = 0;
    joints[1] = 0;
    joints[2] = 0;
    joints[3] = 0;
    cooldown = 0;
    randomIndex = 0;
    root = at;
    count = 0;
    for (SparkJoint *j = GetChild(root); j; j = j->next) {
        count++;
    }
    fn_801825FC();
    modelB = new clNormal3D((void *)lbl_8036E178, 0);
    fn_801825C8();
    modelA = new clNormal3D((void *)lbl_8036E188, 1);
    if (modelB) {
        Object_SetJObjScaleXYZ(modelB, lbl_806D8CD4, lbl_806D8CD4, lbl_806D8CD4);
        joints[0] = ResolveJointByName(modelB, lbl_8036E19C);
        joints[1] = ResolveJointByName(modelB, lbl_8036E1BC);
        joints[2] = ResolveJointByName(modelB, lbl_8036E1DC);
        joints[3] = ResolveJointByName(modelB, lbl_8036E1FC);
    }
}

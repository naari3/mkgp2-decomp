#ifndef SCENE_ROLE_VARIANT_C_PRIVATE_H
#define SCENE_ROLE_VARIANT_C_PRIVATE_H
#include "game/FlowScene.h"

/* Local ABI views observed in target ASM; no live Ghidra type lookup. */
struct SceneRoleVariantCRoot {
    virtual void ExternalKey();
    unsigned char done;
    unsigned char padding[3];
    SceneRoleVariantCRoot() : done(0) {}
    ~SceneRoleVariantCRoot() {}
};
struct SceneRoleVariantCChild : SceneRoleVariantCRoot {
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};
struct SceneRoleVariantCBase : SceneRoleVariantCRoot {
    SceneRoleVariantCChild *child;
    int route;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    SceneRoleVariantCBase();
    ~SceneRoleVariantCBase();
    virtual void SlotC();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Start(int);
    virtual void Finish(int);
};
struct SceneRoleVariantC : SceneRoleVariantCBase {
    SceneRoleVariantC();
    ~SceneRoleVariantC();
    virtual void ExternalKey();
};
struct SceneRoleVariantCContext {
    char pad[12];
    float value;
};
extern "C" {
extern SceneRoleVariantCContext *lbl_806D1A60;
extern const float lbl_806DBFC8, lbl_806DBFCC, lbl_806DBFD0;
extern const float lbl_806DBFD4, lbl_806DBFD8, lbl_806DBFDC;
void *ItemDisplay_GetOrCreate();
void fn_8020AAD4(void *);
void fn_80120A08(int);
}
#endif

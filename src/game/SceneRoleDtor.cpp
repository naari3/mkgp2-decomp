/* Target-observed owner view; canonical list and owning member reused.
 * No live Ghidra type lookup was performed. */
#include "game/FlowScene.h"

extern "C" {
void *ItemDisplay_GetOrCreate();
void fn_8020AAD4(void *);
}

struct SceneRoleBase {
    virtual void ExternalKey();
    unsigned char flags[4];
    ~SceneRoleBase() {}
};

struct SceneRoleOwner : SceneRoleBase {
    VHolder<FlowSceneList> list;
    int value;
    unsigned char tail[4];
    virtual void ExternalKey();
    ~SceneRoleOwner();
};

SceneRoleOwner::~SceneRoleOwner()
{
    fn_801F4D3C(list.p);
    fn_8020AAD4(ItemDisplay_GetOrCreate());
}

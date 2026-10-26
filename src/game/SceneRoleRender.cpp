#include "game/FlowScene.h"

/* Target-observed owner view; no live Ghidra type lookup was performed. */
struct SceneRoleRender {
    void *vtable;
    unsigned char finished;
    unsigned char pad05[3];
    FlowSceneList *scene;
};

extern "C" void HSD_StateInvalidate(unsigned int mask);

extern "C" void fn_8024CFE8(SceneRoleRender *self)
{
    if (!self->finished) {
        self->scene->Draw();
        HSD_StateInvalidate(~0U);
    }
}

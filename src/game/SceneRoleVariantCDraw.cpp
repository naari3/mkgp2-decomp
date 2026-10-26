#include "game/SceneRoleVariantCPrivate.h"
extern "C" void HSD_StateInvalidate(unsigned int);
extern "C" void fn_8024CCE8(SceneRoleVariantC *self)
{
    if (!self->done) {
        self->list.p->Draw();
        if (self->child)
            self->child->Draw();
        HSD_StateInvalidate(~0U);
    }
}

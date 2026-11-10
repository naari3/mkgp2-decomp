#include "game/singleton.h"
#include "game/RaceHudMethodsPrivate.h"
extern "C" void fn_80249130(HudMethodScene *self) {
    if(GetInput()) { InputState *in=g_pInputState; CGameCoin_ProcessInput(SINGLETON_INSTANCE(in)); }
    if(!self->done) {
        fn_8021A1C4(lbl_806D1A60);
        ItemDisplay_Update(ItemDisplay_GetOrCreate());
        if(!self->child) {
            if(self->position == -1) self->done=1;
            else self->Enter(self->position);
        }
        if(self->child) {
            if(!self->child->done) self->child->Update();
            else self->Leave(self->position);
        }
        if(fn_801FD924(&self->host)) {
            if(self->child) self->Leave(self->position);
            self->position=7;
        }
        fn_801FD830(&self->host);
        fn_801DABFC(fn_801DAEC0());
    }
}

#include "game/RaceHudMethodsPrivate.h"
extern "C" HudMethodScene *dtor_80249274(HudMethodScene *self, short flag) {
    if(self) {
        *(void ***)self=RaceHudScene_vtable_804EECA4; self->host=RaceHudScene_vtable_804EECA4+6;
        if(lbl_806D1A88) { fn_80232550(lbl_806D1A88,1); lbl_806D1A88=0; }
        fn_8011F86C(); fn_801DAEC0()->SetOther(0);
        fn_801DAE54(); fn_8021A2B4(); ItemDisplay_Destroy();
        dtor_801FD958(&self->host,0);
        if(self) *(void ***)self=lbl_803FE0C8;
        if(flag>0) MemoryManager_TimedFree(self);
    }
    return self;
}

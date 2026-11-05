#include "game/RaceHudTransitionPrivate.h"

extern "C" void fn_80248028(RaceHudTransition *self) {
    if (self->scene) {
        if (!self->scene->done) self->scene->Draw();
        fn_80218B5C(self->display);
        fn_8011F994(7);
    }
}

extern "C" int fn_80248088(RaceHudTransition *self) {
    fn_801A1280();
    if (self->scene->done) {
        if (self->scene) {
            if (self->scene) {
                self->scene->Destroy();
                self->scene=0;
            }
        }
        fn_80121210();
        fn_8012094C();
        clRom_PurgeAll();
        fn_801A0B70(1);
        fn_801F8E54();
        if (fn_8024F588()->flag) {
            g_cupId+=8;
            return 4;
        }
        fn_8024F530();
        return 3;
    }
    self->scene->Update();
    fn_8020F290();
    fn_80218B80(self->display);
    return -2;
}

#include "game/anon_8020314C_private.h"

extern "C" void fn_8020314C(MsgPopup *self) {
    if (self->state < 6) {
        int msg = self->msgId;
        if (msg != 0 && msg != 1) {
            fn_8011FAFC(&self->ctrls[0], self->layer);
        }
        if (self->state < 5) {
            int i;
            fn_8011FAFC(&self->ctrls[1], self->layer);
            fn_8011FAFC(&self->ctrls[2], self->layer);
            if (self->badge != 0) {
                fn_8011FAFC(&self->ctrls[3], self->layer);
            }
            for (i = 0; i < 4; i++) {
                fn_801F8A34(fn_801F8E58(), &self->texts[i], self->layer);
            }
        }
    }
}

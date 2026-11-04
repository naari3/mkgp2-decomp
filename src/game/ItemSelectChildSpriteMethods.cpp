#include "game/ItemSelectChildSprite.h"

extern "C" void fn_8023E154(ItemSelectChildSprite *self) {
    self->countdown = 30;
    float value = fn_8020A6CC(self->fade);
    fn_8020A734(self->fade, 10, value, 0.0f);
}
extern "C" void fn_8023E19C(ItemSelectChildSprite *self) {
    self->countdown = 10;
    float value = fn_8020A6CC(self->fade);
    fn_8020A734(self->fade, 5, value, 0.8f);
}
extern "C" void fn_8023E1E4(ItemSelectChildSprite *self, int item, unsigned char changed) {
    if (!((item > 0 && item < 0x115) || (item > 0x115 && item < 0x130))) {
        ItemSelectChildEffect *effect = self->effect;
        if (effect->active) {
            float value = fn_8020A6CC(effect->fade.p);
            if (1.0f == value || 0.0f == value)
                fn_8020A734(effect->fade.p, 5, 0.0f, 1.0f);
        }
    } else {
        if (changed) {
            self->phase = 1;
            fn_8020A7CC(self->timer.p, 0, 25, 25);
        }
        ItemSelectChildEffect *effect = self->effect;
        if (effect->active != 1) {
            float value = fn_8020A6CC(effect->fade.p);
            if (1.0f == value || 0.0f == value)
                fn_8020A734(effect->fade.p, 5, 1.0f, 0.0f);
        }
        fn_8023D458(self->item, item);
    }
}
extern "C" void fn_8023E2F8(ItemSelectChildSprite *self) {
    fn_8023D2B4(self->item);
    fn_8011F994(3);
}

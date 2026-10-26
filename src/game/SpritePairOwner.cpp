#include "game/SpritePairOwner.h"
extern "C" {
void fn_8023CC74(SpritePairOwner *self, int on) {
    if (self->handles[0] >= 0) SpriteHandle_SetActiveFlag(self->handles[0], on);
}
void fn_8023CCA0(SpritePairOwner *self, int on) {
    if (self->handles[1] >= 0) SpriteHandle_SetActiveFlag(self->handles[1], on);
}
void fn_8023CCCC(SpritePairOwner *self, float x, float y) {
    if (self->handles[0] >= 0) fn_8011F804(self->handles[0], x, y);
}
void fn_8023CCF8(SpritePairOwner *self, float x, float y) {
    if (self->handles[1] >= 0) fn_8011F804(self->handles[1], x, y);
}
void fn_8023CD24(SpritePairOwner *self, float x, float y) {
    Sprite *sprite=self->sprites[0];
    if (sprite) { sprite->x=x; sprite->y=y; }
}
void fn_8023CD3C(SpritePairOwner *self, float x, float y) {
    Sprite *sprite=self->sprites[1];
    if (sprite) { sprite->x=x; sprite->y=y; }
}
void fn_8023CD54(SpritePairOwner *self) {
    for (int i=0; i<2; ++i) if (self->sprites[i]) fn_801A0004(self->sprites[i]);
}
}

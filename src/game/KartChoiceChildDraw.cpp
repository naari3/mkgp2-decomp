#include "game/KartChoiceOwnerPrivate.h"
extern "C" void fn_8023BEF0(ChoiceChild *self) {
    if (self->hidden == 1) return;
    float sy;
    float sx;
    sx = self->scale * (lbl_806DB990 * lbl_806D6DE4);
    sy = self->scale * (lbl_806DB990 * lbl_806D6DE8);
    int active = 0;
    if (self->alias != -1) {
        fn_8011F804(self->sprites[0], self->x, self->y);
        fn_8011F744(self->sprites[0], sx, sy);
        SpriteHandle_SetCornerAlpha(self->sprites[0], 255);
        active = 1;
    }
    SpriteHandle_SetActiveFlag(self->sprites[0], active);
    SpriteHandle_RecomputeCull(self->sprites[0]);
    float width = lbl_806DB994 * self->scale;
    float scale = self->scale;
    fn_8011F804(self->sprites[2], self->x, self->y);
    fn_8011F744(self->sprites[2], width, lbl_806DB998 * scale);
    SpriteHandle_SetActiveFlag(self->sprites[2], 1);
    SpriteHandle_RecomputeCull(self->sprites[2]);
    int offset = 0;
    float size = self->scale;
    if (self->alias < 0) size *= lbl_806DB990;
    else if (self->value == 0) offset = -10;
    fn_8011F804(self->sprites[1], self->x, self->y + offset);
    fn_8011F744(self->sprites[1], size, size);
    SpriteHandle_SetActiveFlag(self->sprites[1], 1);
    SpriteHandle_RecomputeCull(self->sprites[1]);
    active = 0;
    if (g_gameMode != 1 && self->render->unavailable == 0) {
        fn_8011F804(self->sprites[3], self->x, self->y - lbl_806DB99C);
        fn_8011F744(self->sprites[3], self->scale, self->scale);
        active = 1;
    }
    SpriteHandle_SetActiveFlag(self->sprites[3], active);
    SpriteHandle_RecomputeCull(self->sprites[3]);
}

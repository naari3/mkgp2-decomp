#include "game/ItemSelectChildSprite.h"
struct ItemSelectChildLayout {
    char pad000[0x3fc];
    float origin[4][2];
    float pair[2][2];
    float offsets[4];
    char tail[0x34];
};
extern "C" {
extern const ItemSelectChildLayout lbl_803E5878;
void fn_8023D2B8(ItemAliasSprite *);
int fn_8020A788(FlowFader *);
}
static inline void DrawEffect(ItemSelectChildEffect *effect, int active, const float pair[2][2]) {
    float sx = effect->scale;
    float sy = effect->scale * fn_8020A6CC(effect->fade.p);
    float shift = effect->scale * (1.0f - fn_8020A6CC(effect->fade.p));
    for (int i = 0; i < 2; ++i) {
        fn_8011F804(effect->handles[i],
            effect->scale * pair[i][0] + effect->x,
            shift * pair[i][1] +
                (effect->scale * pair[i][1] + effect->y));
        fn_8011F744(effect->handles[i], sx, sy);
        SpriteHandle_SetActiveFlag(effect->handles[i], active);
        SpriteHandle_RecomputeCull(effect->handles[i]);
    }
    effect->fade.p->Step();
    if (1.0f == fn_8020A6CC(effect->fade.p)) effect->active = 0;
    else effect->active = 1;
}
static inline void DrawOverlay(ItemSelectChildOverlay *overlay, int active) {
    float scale = overlay->scale * fn_8020A6CC(overlay->fade.p);
    fn_8011F804(overlay->handles[0], overlay->x, overlay->y);
    fn_8011F744(overlay->handles[0], scale, scale);
    SpriteHandle_SetCornerAlpha(overlay->handles[0], (unsigned char)fn_8020A788(overlay->alpha.p));
    SpriteHandle_SetActiveFlag(overlay->handles[0], active);
    SpriteHandle_RecomputeCull(overlay->handles[0]);
    int pulse = 0;
    if (1.0f == fn_8020A6CC(overlay->fade.p)) pulse = active;
    fn_8011F804(overlay->handles[1], overlay->x, overlay->y);
    fn_8011F744(overlay->handles[1], scale, scale);
    SpriteHandle_SetCornerAlpha(overlay->handles[1], (unsigned char)fn_8020A788(overlay->pulse.p));
    SpriteHandle_SetActiveFlag(overlay->handles[1], pulse);
    SpriteHandle_RecomputeCull(overlay->handles[1]);
    overlay->fade.p->Step();
    overlay->alpha.p->Step();
    overlay->pulse.p->Step();
    if (overlay->pulse.p->Done()) {
        if (fn_8020A788(overlay->pulse.p) == 255) fn_8020A7CC(overlay->pulse.p, 255, 0, 5);
        else fn_8020A7CC(overlay->pulse.p, 0, 255, 5);
    }
}
static inline void SetItemPos(ItemAliasSprite *item, float x, float y) { item->x=x; item->y=y; }
static inline void SetItemScale(ItemAliasSprite *item, float scale) { item->scaleX=scale; item->scaleY=scale; }
template <class T> static inline void SetPartPos(T *part, float x, float y) { part->x=x; part->y=y; }
extern "C" void fn_8023DCEC(ItemSelectChildSprite *self, int active) {
    const ItemSelectChildLayout *layout = &lbl_803E5878;
    ResCtrl rc;
    float scale;
    float x;
    float y;
    y = self->baseY - self->y;
    scale = self->scale;
    x = self->x;
    scale += fn_8020A6CC(self->fade);
    SetItemPos(self->item, x + (layout->offsets[2] + layout->origin[self->variant][0]),
        y + (layout->offsets[3] + layout->origin[self->variant][1]));
    SetItemScale(self->item, scale);
    self->item->color = self->color;
    self->item->active = active;
    if (active) fn_8023D2B8(self->item);
    SetPartPos(self->effect, x + (layout->offsets[0] + layout->origin[self->variant][0]),
        y + (layout->offsets[1] + layout->origin[self->variant][1]));
    self->effect->scale = scale;
    DrawEffect(self->effect, active, layout->pair);
    fn_8011F804(self->handle,
        x + (layout->offsets[0] + layout->origin[self->variant][0]),
        y + (layout->offsets[1] + layout->origin[self->variant][1]));
    fn_8011F744(self->handle, scale, scale);
    SpriteHandle_SetActiveFlag(self->handle, active);
    SpriteHandle_RecomputeCull(self->handle);
    SetPartPos(self->overlay, x + (layout->offsets[0] + layout->origin[self->variant][0]),
        y + (layout->offsets[1] + layout->origin[self->variant][1]));
    self->overlay->scale = scale;
    DrawOverlay(self->overlay, active);
}

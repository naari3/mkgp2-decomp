#include "game/ItemSelectChildSprite.h"
/* Original shared animation curves and child layout pool at 0x803E5878. */
#pragma force_active on
extern const float childScales[3] = {1.0f, 0.7f, 0.9f};
extern const float childCurves[18][7][2] = {
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 66.66667175292969f}, {1000.0f, 66.66667175292969f}, {2000.0f, 66.66667175292969f}, {3000.0f, 66.66667175292969f}, {4000.0f, 66.66667175292969f}, {5000.0f, 66.66667175292969f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}},
    {{0.0f, 0.0f}, {500.0f, 83.33333587646484f}, {1000.0f, 83.33333587646484f}, {2000.0f, 83.33333587646484f}, {3000.0f, 83.33333587646484f}, {4000.0f, 83.33333587646484f}, {5000.0f, 83.33333587646484f}}
};
extern const float childOrigins[4][2] = {{162.0f, 40.0f}, {260.0f, 40.0f}, {162.0f, 40.0f}, {147.0f, 40.0f}};
extern const float childEffectPositions[2][2] = {{0.0f, -8.5f}, {0.0f, 11.5f}};
extern const float childOffsets[4] = {0.0f, 0.0f, 0.0f, 0.0f};
extern const char childIntCounterName[] = "clIntCounter";
extern const char childCounterInterfaceName[] = "clCounterInterface";
extern const char childFloatCounterName[] = "clFloatCounter";
#pragma force_active reset
extern "C" {
void fn_8023D2B8(ItemAliasSprite *);
int fn_8020A788(FlowFader *);
}
static inline void DrawEffect(ItemSelectChildSprite *self, int active) {
    ItemSelectChildEffect *effect = self->effect;
    float sx = effect->scale;
    float sy = effect->scale * fn_8020A6CC(effect->fade.p);
    float shift = effect->scale * (lbl_806DBDA8 - fn_8020A6CC(effect->fade.p));
    for (int i = 0; i < 2; ++i) {
        fn_8011F804(effect->handles[i],
            effect->scale * childEffectPositions[i][0] + effect->x,
            shift * childEffectPositions[i][1] +
                (effect->scale * childEffectPositions[i][1] + effect->y));
        fn_8011F744(effect->handles[i], sx, sy);
        SpriteHandle_SetActiveFlag(effect->handles[i], active);
        SpriteHandle_RecomputeCull(effect->handles[i]);
    }
    effect->fade.p->Step();
    if (lbl_806DBDA8 == fn_8020A6CC(effect->fade.p)) effect->active = 0;
    else effect->active = 1;
}
static inline void DrawOverlay(ItemSelectChildSprite *self, int active) {
    ItemSelectChildOverlay *overlay;
    int pulse;
    overlay = self->overlay;
    float scale = overlay->scale * fn_8020A6CC(overlay->fade.p);
    fn_8011F804(overlay->handles[0], overlay->x, overlay->y);
    fn_8011F744(overlay->handles[0], scale, scale);
    SpriteHandle_SetCornerAlpha(overlay->handles[0], (unsigned char)fn_8020A788(overlay->alpha.p));
    SpriteHandle_SetActiveFlag(overlay->handles[0], active);
    SpriteHandle_RecomputeCull(overlay->handles[0]);
    pulse = 0;
    if (lbl_806DBDA8 == fn_8020A6CC(overlay->fade.p)) pulse = active;
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
static inline void SetItemPos(ItemAliasSprite *item, float y, float x) {
    float px; float py;
    px = x; py = y;
    item->x=px; item->y=py;
}
static inline void SetItemScale(ItemAliasSprite *item, float scale) { item->scaleX=scale; item->scaleY=scale; }
template <class T> static inline void SetPartPos(T *part, float y, float x) {
    float px; float py;
    px = x; py = y;
    part->x=px; part->y=py;
}
extern "C" void fn_8023DCEC(ItemSelectChildSprite *self, int active) {
    ResCtrl rc;
    float scale;
    float x;
    float y;
    y = self->baseY - self->y;
    scale = self->scale;
    x = self->x;
    scale += fn_8020A6CC(self->fade);
    SetItemPos(self->item, y + (childOffsets[3] + childOrigins[self->variant][1]),
        x + (childOffsets[2] + childOrigins[self->variant][0]));
    SetItemScale(self->item, scale);
    self->item->color = self->color;
    self->item->active = active;
    if ((unsigned char)active) fn_8023D2B8(self->item);
    SetPartPos(self->effect, y + (childOffsets[1] + childOrigins[self->variant][1]),
        x + (childOffsets[0] + childOrigins[self->variant][0]));
    self->effect->scale = scale;
    DrawEffect(self, active);
    fn_8011F804(self->handle,
        x + (childOffsets[0] + childOrigins[self->variant][0]),
        y + (childOffsets[1] + childOrigins[self->variant][1]));
    fn_8011F744(self->handle, scale, scale);
    SpriteHandle_SetActiveFlag(self->handle, active);
    SpriteHandle_RecomputeCull(self->handle);
    SetPartPos(self->overlay, y + (childOffsets[1] + childOrigins[self->variant][1]),
        x + (childOffsets[0] + childOrigins[self->variant][0]));
    self->overlay->scale = scale;
    DrawOverlay(self, active);
}


#ifndef HUD_SPRITE2454_PRIVATE_H
#define HUD_SPRITE2454_PRIVATE_H
#include "game/FlowScene.h"
struct HudTween {
    virtual ~HudTween();
    short limit, frame;
};
struct HudByteTween {
    virtual ~HudByteTween();
    short limit, frame;
};
struct HudSprite2454 {
    void *vtable;
    int layer;
    float x, y, scale;
    HudTween *size, *rotation;
    HudByteTween *color;
};
struct HudSprite2457 {
    void *vtable;
    unsigned char visible;
    char pad[3];
    float x,y;
};
extern "C" {
void fn_8011FAFC(ResCtrl *, int);
void fn_80121E10(ResCtrl *);
void fn_80120A08(int);
float fn_8020A6CC(HudTween *);
int fn_8020A788(HudByteTween *);
#include "game/types/tween_set_order.h"
void fn_8020A734(HudTween *, int, float, float);
void fn_8020A7CC(HudByteTween *, int, int, int);
void MemoryManager_TimedFree(void *);
extern float lbl_806DBE90, lbl_806DBE64, lbl_806DBED8;
}
inline void HudTweenTick(HudTween *t) {
    t->frame++;
    short limit=t->limit;
    if (t->frame >= limit) t->frame=limit;
}
inline void HudTweenTick(HudByteTween *t) {
    t->frame++;
    short limit=t->limit;
    if(t->frame>=limit) t->frame=limit;
}
#endif

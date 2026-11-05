#ifndef ITEM_SELECT_PENDING_PRIVATE_H
#define ITEM_SELECT_PENDING_PRIVATE_H
#include "game/FlowScene.h"
struct SelectSprite { char pad0[0xC]; float x,y,z,w,unused1C,scale; };
struct SelectTween {
    unsigned char enabled; char pad1[3];
    float from,to,step,t,value;
    SelectTween();
};
struct SelectEntry {
    virtual void Key();
    virtual void Apply();
    virtual void Update();
    SelectSprite *sprite;
    int delay;
    SelectTween tween[5];
    unsigned char active,mode; char pad86[2];
};
struct SelectNode { SelectNode *prev,*next; SelectEntry *entry; };
struct SelectOwner {
    void *vt; int count; SelectNode *last,*first;
    int timer; unsigned char closing; char pad15[3]; int result;
};
extern "C" {
extern const float lbl_806D9E20,lbl_806D9E24,lbl_806D9E28,lbl_806D9E2C;
void Sprite_AdvanceAnim(SelectSprite *,float);
int fn_801CCAAC(SelectOwner *);
}
#endif

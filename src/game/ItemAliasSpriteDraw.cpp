#include "game/ItemAliasSprite.h"
void ItemAliasSprite::Draw() {
    ItemAliasSprite *self=this;
    SpriteLayer_SetResource(self->handles[0],self->resource);
    fn_8011F804(self->handles[0],self->x,self->y);
    fn_8011F744(self->handles[0],self->scaleX,self->scaleY);
    unsigned int color=self->color;
    fn_8011F610(self->handles[0],color>>24,(color>>16)&255,(color>>8)&255);
    SpriteHandle_SetCornerAlpha(self->handles[0],color&255);
    SpriteHandle_SetActiveFlag(self->handles[0],self->active);
    SpriteHandle_RecomputeCull(self->handles[0]);
    unsigned char show=0;
    if (self->alias) {
        int resource;
        float x,y;
        show=1;
        if (self->style==0) {
            resource=0x7C5;
            x=lbl_806DBD8C*self->scaleX+self->x;
            y=lbl_806DBD90*self->scaleY+self->y;
        } else {
            resource=0xB69;
            x=lbl_806DBD94*self->scaleX+self->x;
            y=lbl_806DBD98*self->scaleY+self->y;
        }
        SpriteLayer_SetResource(self->handles[1],resource);
        fn_8011F804(self->handles[1],x,y);
        fn_8011F744(self->handles[1],self->scaleX,self->scaleY);
        color=self->color;
        fn_8011F610(self->handles[1],color>>24,(color>>16)&255,(color>>8)&255);
        SpriteHandle_SetCornerAlpha(self->handles[1],color&255);
    }
    int on=0;
    if (self->active && show) on=1;
    SpriteHandle_SetActiveFlag(self->handles[1],on);
    SpriteHandle_RecomputeCull(self->handles[1]);
}

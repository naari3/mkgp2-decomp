#include "game/ItemAliasSprite.h"
static inline int ResolveItem(int item, signed char *alias) {
    if (alias) *alias=0;
    unsigned int index;
    unsigned char scratch;
    if (item<0 || item>=0x147) index=0x146;
    else {
        int source=ItemAlias_DestToSource((unsigned char)item,&scratch);
        if (alias && item!=0) *alias=scratch;
        index=g_itemIdToIndexTable[source];
    }
    return lbl_803DC530[index].resource;
}
extern "C" void fn_8023D458(ItemAliasSprite *self,int item) {
    self->item=item;
    if (!((item>0 && item<0x115) || (item>0x115 && item<0x137))) self->item=0;
    if (item>0x115 && item<0x137) {
        self->resource=lbl_803E57E8[item-0x115];
        self->alias=0;
    } else self->resource=ResolveItem(self->item,&self->alias);
}
ItemAliasSprite::~ItemAliasSprite() {
    for(int i=0;i<2;++i) SpriteHandle_Destroy(handles[i]);
}
ItemAliasSprite::ItemAliasSprite(int style_,int layer_) {
    style=style_; layer=layer_;
    x=lbl_806DBD9C; y=lbl_806DBD9C;
    scaleX=lbl_806DBDA0; scaleY=lbl_806DBDA0;
    color=0xFFFFFFFF; active=1; item=0;
    resource=ResolveItem(0,&alias);
    ResCtrl rc;
    fn_80121E10(&rc);
    rc.resId=0x1422;
    for (int i=0;i<2;++i) {
        handles[i]=SpriteHandle_CreateDefault(&rc,layer);
        SpriteHandle_SetActiveFlag(handles[i],0);
    }
}

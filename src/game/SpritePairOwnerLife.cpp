#include "game/SpritePairOwner.h"
#pragma use_lmw_stmw on
SpritePairOwner::~SpritePairOwner() {
    for (int i=0; i<2; ++i) {
        if (sprites[i]) { delete sprites[i]; sprites[i]=0; }
    }
    for (int i=0; i<2; ++i) if (handles[i]>=0) SpriteHandle_Destroy(handles[i]);
}
SpritePairOwner::SpritePairOwner(int back, int front, int backHandle, int frontHandle, int layer) {
    alpha=lbl_806DB9D8;
    speed=lbl_806DB9DC;
    sprites[0]=0; sprites[1]=0;
    handles[0]=-1; handles[1]=-1;
    if (back>=0) {
        sprites[1]=new Sprite(back,1,0);
        fn_8019FF6C(sprites[1],1);
        sprites[1]->layer=layer;
    }
    if (front>=0) {
        sprites[0]=new Sprite(front,1,0);
        fn_8019FF6C(sprites[0],1);
        sprites[0]->layer=layer;
    }
    ResCtrl rc;
    if (backHandle>=0) {
        rc.resId=backHandle;
        handles[1]=SpriteHandle_CreateDefault(&rc,layer);
        resources[1]=backHandle;
    }
    fn_80121E10(&rc);
    if (frontHandle>=0) {
        rc.resId=frontHandle;
        handles[0]=SpriteHandle_CreateDefault(&rc,layer);
        resources[0]=frontHandle;
    }
}
#pragma use_lmw_stmw reset

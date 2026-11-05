#include "game/ItemGridInitPrivate.h"
#pragma use_lmw_stmw on
static inline unsigned char GridContains(int *ids, int value) {
    unsigned char found=0;
    for (int i=0;i<3;++i) if(value==ids[i]) {found=1;break;}
    return found;
}
extern "C" GridInitState *ItemGridState_Init(GridInitState *self) {
    self->selected=0;
    self->phase=0;
    self->done=0;
    self->automatic=0;
    self->groups[0]=0; self->groups[1]=0; self->groups[2]=0;
    self->groups[3]=0; self->groups[4]=0; self->groups[5]=0; self->groups[6]=0;
    PreloadResource(0x192a); PreloadResource(0x192c);
    ResCtrl resource;
    resource.resId=0x192a;
    resource.flag=1;
    resource.x=lbl_806DB8DC; resource.y=lbl_806DB940; resource.z=lbl_806DB8CC;
    self->handle=SpriteHandle_CreateDefault(&resource,6);
    SpriteHandle_SetActiveFlag(self->handle,0);
    SpriteHandle_RecomputeCull(self->handle);
    GridInitState *rowBase=self;
    int row;
    int col;
    for(row=0;row<3;++row, rowBase=(GridInitState *)((char *)rowBase+0x10)) {
        GridInitState *cursor=rowBase;
        for(col=0;col<4;++col, cursor=(GridInitState *)((char *)cursor+4)) {
            cursor->texts[0][0]=new TextManager;
            TexMgr_SetTexture(cursor->texts[0][0],lbl_806DB8F8);
            cursor->texts[0][0]->scale=lbl_806DB8A0;
        }
    }
    int ids[3];
    unsigned char *player=g_playerData;
    ids[0]=*(int *)(player+0x18c); ids[1]=*(int *)(player+0x190); ids[2]=*(int *)(player+0x194);
    for(int i=0;i<3;++i) {
        int id;
        if(fn_8023D860(*(int *)(player+0x18c+i*4))==1) {
            int character=g_characterId;
            id=fn_8023D844(character,fn_8023D7A8(*(int *)(player+0x18c+i*4)));
            if(player[id+0xa8]==0) {
                for(int j=0;j<3;++j) {
                    if(!GridContains(ids,lbl_803DC174[j])) {id=lbl_803DC174[j];break;}
                }
            }
        } else id=*(int *)(player+0x18c+i*4);
        ids[i]=id;
        self->itemIndices[i]=id;
        self->resources[i]=Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,id),0);
    }
    return self;
}
#pragma use_lmw_stmw reset

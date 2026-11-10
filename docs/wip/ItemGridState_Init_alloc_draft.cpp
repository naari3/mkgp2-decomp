#include "game/ItemGridInitPrivate.h"
#pragma use_lmw_stmw on
extern "C" void *Alloc(unsigned long);
extern "C" void TexMgr_Init(void *);
static inline int GridFallbackCandidate(int index) {
    return ItemGridState_Init_rodata_803DC174[index];
}
static inline void CreateGridTexts(GridInitState *self) {
    int col, row;
    for (row=0;row<3;++row) {
        for (col=0;col<4;++col) {
            TextManager *t = (TextManager *)Alloc(0x230);
            if (t) TexMgr_Init(t);
            self->texts[row][col]=t;
            TexMgr_SetTexture(self->texts[row][col],lbl_806DB8F8);
            self->texts[row][col]->scale=lbl_806DB8A0;
        }
    }
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
    CreateGridTexts(self);
    int ids[3];
    int i;
    unsigned char *player=g_playerData;
    ids[0]=*(int *)(player+0x18c); ids[1]=*(int *)(player+0x190); ids[2]=*(int *)(player+0x194);
    for(i=0;i<3;++i) {
        int id;
        if(fn_8023D860(*(int *)(player+0x18c+i*4))==1) {
            int character=g_characterId;
            id=fn_8023D844(character,fn_8023D7A8(*(int *)(player+0x18c+i*4)));
            if(player[id+0xa8]==0) {
                for(int j=0;j<3;++j) {
                    int candidate=GridFallbackCandidate(j);
                    unsigned char found=0;
                    for (int k=0;k<3;++k) {
                        if (candidate==ids[k]) { found=1; break; }
                    }
                    if (!found) {id=GridFallbackCandidate(j);break;}
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

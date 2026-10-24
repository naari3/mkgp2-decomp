#include "game/ItemSelectState.h"
extern "C" {
struct PlayerData { unsigned char pad[0x18c]; int selected[3]; };
extern PlayerData g_playerData;
extern unsigned char lbl_806D1264[3];
extern int g_characterId;
extern unsigned int lbl_803DC180[6][10];
int PlayerData_ResolveUnlockedIdByIndex(void *,int);
void SpriteHandle_Destroy(unsigned int);
int fn_8023D844(int,int);
int Item_GetDescriptorField0(int,void *);
void fn_80120A08(int);
}
static inline int characterId() {
 int id=g_characterId; if(id<0) id=0; if(id>=13) id=0; return id;
}
ItemSelectState::~ItemSelectState() {
    PlayerData *player=&g_playerData;
    g_playerData.selected[0]=selectedItemId0;
    g_playerData.selected[1]=selectedItemId1;
    g_playerData.selected[2]=selectedItemId2;
    lbl_806D1264[0]=PlayerData_ResolveUnlockedIdByIndex(&g_playerData,selectedItemId0);
    lbl_806D1264[1]=PlayerData_ResolveUnlockedIdByIndex(&g_playerData,selectedItemId1);
    lbl_806D1264[2]=PlayerData_ResolveUnlockedIdByIndex(&g_playerData,selectedItemId2);
    if(iconArray) {delete iconArray;iconArray=0;}
    if(auxBuffer) {delete auxBuffer;auxBuffer=0;}
    for(int i=0;i<9;i++) if(groups[i]) {SpriteAnimHandle_Destroy(groups[i],1);groups[i]=0;}
    for(int i=0;i<66;i++) {
        SpriteHandle_Destroy(itemSprites[i]);
        int character=characterId();
        int index;
        if(i%11>=10) index=fn_8023D844(character,i/11);
        else index=lbl_803DC180[i/11][i%11];
        fn_80120A08(Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,index),0));
    }
    for(int i=0;i<5;i++) SpriteHandle_Destroy(sprites[i]);
    fn_80120A08(0x17bb);fn_80120A08(0x1d23);fn_80120A08(0x17ed);fn_80120A08(0x1e3d);
}


#include "game/ItemSelectState.h"
struct ResCtrl {
 int resId; int field4,mode,fieldc; unsigned char flag,pad11[3];
 float x,y,z,width,height,field28,scaleX,scaleY;
 unsigned int colors[4]; int tail[5];
 ResCtrl(); ~ResCtrl() {}
};
extern "C" {
void PreloadResource(int);void fn_80121E10(ResCtrl *);
unsigned int SpriteHandle_CreateDefault(ResCtrl *,int);
void SpriteHandle_SetActiveFlag(unsigned int,int);void SpriteHandle_RecomputeCull(unsigned int);
int isJapanese();void TexMgr_SetTexture(TextManager *,const char *);
void fn_801F93EC(float,float,TextManager *);void fn_801F8E90(TextManager *);
int fn_8023D844(int,int);int PlayerData_ResolveUnlockedIdByIndex(void *,int);
int Item_GetDescriptorField0(int,void *);
extern int g_characterId;
extern unsigned char g_playerData[];
extern unsigned int lbl_803DC180[6][10];
extern float lbl_803DC29C[];
extern char lbl_803DC0C0[];
extern const float lbl_806DB88C,lbl_806DB890,lbl_806DB8CC,lbl_806DB900,lbl_806DB924;
extern const float lbl_806DB928,lbl_806DB92C,lbl_806DB930,lbl_806DB8F0,lbl_806DB910;
extern const float lbl_806DB8DC,lbl_806DB934,lbl_806DB938,lbl_806DB93C;
extern const float lbl_806DB8D4,lbl_806DB8D8,lbl_806DB8E0;
}
static inline int portraitIndex() {
 if(g_characterId==0)return 0;
 else if(g_characterId==1)return 1;
 else if(g_characterId==8)return 2;
 else if(g_characterId==11)return 3;
 else if(g_characterId==3)return 4;
 else if(g_characterId==7)return 5;
 else if(g_characterId==10)return 6;
 else if(g_characterId==12)return 7;
 else if(g_characterId==9)return 8;
 else if(g_characterId==5)return 9;
 else if(g_characterId==2)return 10;
 else if(g_characterId==6)return 11;
 else if(g_characterId==4)return 12;
 else return 0;
}
ItemSelectState::ItemSelectState() {
 char *data=lbl_803DC0C0;
 iconArray=0;auxBuffer=0;field148=0;field14c=0;resultCode=0;phase=0;doneFlag=0;shownFlag=0;
 for(int i=0;i<9;i++)groups[i]=0;
 for(int i=0;i<66;i++)itemSprites[i]=-1;
 for(int i=0;i<5;i++)sprites[i]=-1;
 selectedItemId0=-1;selectedItemId1=-1;selectedItemId2=-1;
 PreloadResource(0x17bb);PreloadResource(0x1d23);PreloadResource(0x17ed);PreloadResource(0x1e3d);
 ResCtrl res;
 res.resId=0x17bb;res.flag=1;res.x=lbl_806DB88C;res.y=lbl_806DB890;res.z=lbl_806DB8CC;
 sprites[0]=SpriteHandle_CreateDefault(&res,5);
 fn_80121E10(&res);
 res.resId=portraitIndex();
 res.resId+=0x1d23;res.flag=1;res.x=lbl_806DB900;res.y=lbl_806DB924;res.z=lbl_806DB8CC;
 sprites[1]=SpriteHandle_CreateDefault(&res,6);
 for(int i=0;i<5;i++){SpriteHandle_SetActiveFlag(sprites[i],0);SpriteHandle_RecomputeCull(sprites[i]);}
 auxBuffer=new TextManager;
 if(!isJapanese())TexMgr_SetTexture(auxBuffer,data+0x21c);
 else {*(float *)(auxBuffer->data+0x22c)=lbl_806DB928;TexMgr_SetTexture(auxBuffer,data+0x238);}
 *(int *)(auxBuffer->data+0x18)=1;
 fn_801F93EC(lbl_806DB92C,lbl_806DB930,auxBuffer);fn_801F8E90(auxBuffer);
 *(unsigned int *)(auxBuffer->data+0x20)=0xffffff00;
 unsigned int *table=(unsigned int *)(data+0xc0);
 float *ys=(float *)(data+0x1dc);
 int total=0;
 for(int row=0;row<6;row++,table+=10,ys++,total+=11) {
 unsigned int *entry=table;
 unsigned int *out=&itemSprites[total];
 for(int col=0;col<11;col++,entry++,out++){
   unsigned int resource=0x1422;
   int character=g_characterId;
   if(character<0)character=0;if(character>=13)character=0;
   int index;
   if(col<10)index=*entry;else index=fn_8023D844(character,row);
   if(g_playerData[0xa8+index]==1)resource=Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(g_playerData,index),0);
   ResCtrl cell;
   cell.y=*ys;cell.flag=1;cell.x=lbl_806DB8F0;cell.z=lbl_806DB8CC;
   cell.colors[0]=cell.colors[1]=cell.colors[2]=cell.colors[3]=0xc3cdf0ff;
   cell.scaleX=cell.scaleY=lbl_806DB910;cell.resId=resource;
   *out=SpriteHandle_CreateDefault(&cell,6);
 }
 }
 fn_80121E10(&res);
 res.tail[1]=res.tail[2]=res.tail[3]=1;
 res.resId=0x1e3d;res.flag=1;res.x=lbl_806DB8DC;res.y=lbl_806DB934;res.z=lbl_806DB8CC;
 res.scaleX=lbl_806DB938;res.scaleY=lbl_806DB8CC;
 sprites[3]=SpriteHandle_CreateDefault(&res,6);
 fn_80121E10(&res);
 res.resId=0x17ed;res.flag=1;res.x=lbl_806DB900;res.y=lbl_806DB93C;res.z=lbl_806DB8CC;
 sprites[2]=SpriteHandle_CreateDefault(&res,6);
 ResCtrl last;
 last.mode=2;last.width=lbl_806DB8D4;last.height=lbl_806DB8D8;last.flag=1;
 last.x=lbl_806DB8DC;last.y=lbl_806DB8E0;last.z=lbl_806DB8CC;
 last.colors[0]=last.colors[1]=last.colors[2]=last.colors[3]=0;
 sprites[4]=SpriteHandle_CreateDefault(&last,6);
 SpriteHandle_SetActiveFlag(sprites[4],0);SpriteHandle_RecomputeCull(sprites[4]);
 iconArray=new IconPack;
}



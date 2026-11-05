#include "game/Scene_8015AFCC_private.h"
extern "C" {
extern PlayerDataRecord g_playerData;
extern const float lbl_806D8394,lbl_806D8398,lbl_806D839C;
extern const float lbl_806D85D0,lbl_806D85D4,lbl_806D85D8,lbl_806D85DC,lbl_806D85E0;
void fn_80121210(); void fn_8013DBF8();
void *fn_801FF00C(int,int); void fn_801FEF34(void *,float,float);
SelectPanel *fn_8020007C(int,int,int);
void InitRumbleController(int); void fn_801699D8(int,int); void SetRumbleMode(int,int,int);
void PreloadResource(int); int Item_GetDescriptorField0(int,int); int Item_GetDescriptorFieldC(int);
unsigned char PlayerData_GetUnlockedItemIdByIndex_U8(int);
unsigned char fn_8019083C(int); int WeatherSystem_PickVariant(int); int fn_801932F8();
void clStream_setVolume(int,int);
}
#pragma exceptions on
Scene8015AFCC::Scene8015AFCC() {
    int itemId; int i; int j; int extra; int t;
    fn_80121210(); fn_8013DBF8();
    active = 0; state = 0; timer = lbl_806D8394; mode = 0;
    driver = 0; player = &g_playerData; flag1c = 0; flag1d = 0; resource = 0x708;
    panel = fn_801FF00C(0,0);
    fn_801FEF34(panel,lbl_806D85D0,lbl_806D85D4);
    panel2 = fn_8020007C(2,0,0);
    panel2->SetPos(lbl_806D85D8,lbl_806D85DC);
    badge = new SelectBadge;
    badge->mode = 0; badge->SetPos(lbl_806D85E0,lbl_806D85DC);
    prompt = new SelectPrompt;
    item = new SelectItem(0);
    character = (signed char)player->variant;
    card = ((unsigned char *)player)[0x19d];
    track = player->prefix[0xc];
    if (character >= 13) character = 0;
    if (character < 0) character = 0;
    driver = new SelectDriver(character,1);
    extraItem = new SelectItem(1);
    kind = player->prefix[0xd];
    valueA = *(unsigned short *)&player->prefix[0xe];
    valueB = *(unsigned short *)&player->prefix[0x10];
    hundredsA = (int)valueA / 100;
    tensA = ((int)valueA - hundredsA*100)/10;
    onesA = (int)valueA - (unsigned char)hundredsA*100 - (unsigned char)tensA*10;
    hundredsB = (int)valueB / 100;
    tensB = ((int)valueB - hundredsB*100)/10;
    onesB = (int)valueB - (unsigned char)hundredsB*100 - (unsigned char)tensB*10;
    for (int i=0;i<4;++i) {
        values[i] = lbl_806D8394;
        arrayA[i] = 0; arrayB[i] = 0; arrayC[i] = 0; arrayD[i] = 0;
    }
    InitRumbleController(1);
    fn_801699D8(0,1); fn_801699D8(1,1); SetRumbleMode(1,2,-1);
    PreloadResource(0x63f); PreloadResource(0x640); PreloadResource(0x642);
    for(i=0;i<5;++i) { PreloadResource(i+0x676); PreloadResource(i+0x671); }
    PreloadResource(0x67f); PreloadResource(0x7cf);
    PreloadResource(Item_GetDescriptorField0(0,0)); PreloadResource(0x7c5);
    for(i=0;i<60;++i) {
        itemId = PlayerData_GetUnlockedItemIdByIndex_U8(i);
        extra = Item_GetDescriptorFieldC(itemId);
        PreloadResource(Item_GetDescriptorField0(itemId,0));
        if (extra >= 0) PreloadResource(extra+0x4f3);
    }
    PreloadResource(0x641); PreloadResource(0x665); PreloadResource(0x666);
    PreloadResource(0x667); PreloadResource(0x668);
    for(j=0;j<7;++j) PreloadResource(j+0x669);
    PreloadResource(0x670);
    for(j=0;j<5;++j) { PreloadResource(j+0x65f); PreloadResource(j+0x65a); }
    PreloadResource(0x664);
    for(j=0;j<10;++j) PreloadResource(j+0x3f7);
    PreloadResource(0x645); PreloadResource(0x644); PreloadResource(0x7db);
    PreloadResource(0x7dc); PreloadResource(0x7f0);
    for(j=0;j<6;++j) PreloadResource(j+0x7dd);
    for(j=0;j<6;++j) PreloadResource(j+0x76c);
    for(j=0;j<12;++j) PreloadResource(j+0x7e4);
    switch(mode) {
    case 0:
        f44 = lbl_806D8394; f50 = lbl_806D8398; f54 = lbl_806D839C;
        { t = track; if(fn_8019083C(1)) clStream_setVolume(1,WeatherSystem_PickVariant(t)); }
        break;
    case 1:
        i=0; f5c=lbl_806D8394; first=i; count=i;
        for(;i<60;++i) {
            if(player->unlockFlags[i]) { ++count; if(first<0) first=i; }
        }
        if(fn_8019083C(1)) clStream_setVolume(1,fn_801932F8());
        break;
    case 3: index=-1; other=0; break;
    case 2: case 4: break;
    }
}
#pragma exceptions reset

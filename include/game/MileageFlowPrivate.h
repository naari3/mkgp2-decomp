#ifndef GAME_MILEAGEFLOWPRIVATE_H
#define GAME_MILEAGEFLOWPRIVATE_H
#include "game/FigureSlotPrivate.h"
#include "game/FlowScene.h"
struct MileageBase { void* vt; MileageBase(); ~MileageBase(); };
struct MileageTableEntry { int miles; short label,title; };
struct MileageTables { short character[13][2]; MileageTableEntry entries[10]; };
extern "C" {
extern MileageTables clFlowFigure_Init_data_8049ACB0;
extern unsigned char g_playerData[];
extern int g_characterId,g_gameMode;
extern unsigned char g_confirmFlag;
extern const float FLOAT_TITLE_STEP_X,FLOAT_TITLE_BASE_X,FLOAT_TITLE_POS_Y,lbl_806D9C20,lbl_806D9C60;
extern const float FLOAT_UNFOCUSED_ALPHA,FLOAT_UNFOCUSED_SCALE,lbl_806D9C38,lbl_806D9C64,FLOAT_ANIM_RESET;
int GetCoinMilage(void*); int rand(); unsigned char IsCardValid();
void SetSyncTarget(int); void PreloadResource(int);
void* FUN_8003b120(int);
unsigned char GetVBlankFlag(); unsigned char VBlankValue_Get();
void NamCam_End(); void NamCam_Init(); void SetupBgSprites(int);
void PlaySoundDSP(int); void InitRumbleController(int); void fn_801699D8(int,int); void fn_801B7B04(int);
}
struct MileageCamera {
    unsigned char active,pending; void* buffer;
    MileageCamera() { active=0; pending=0; buffer=0; buffer=FUN_8003b120(0x4b000); }
    void Start() {
        if(GetVBlankFlag()) {
            if(active == 1) { if(GetVBlankFlag() && active) { active=0; NamCam_End(); } }
            active=1; pending=0; NamCam_Init();
        }
    }
};
struct MileageFlow : MileageBase {
    int selection,count;
    unsigned char complete,available[11],skip,pending;
    char pad1a[2];
    int field1c,field20,ticks,field28,next;
    FigureSprite *s30,*s34,*s38,*s3c,*s40,*s44,*s48,*s4c;
    FigureSprite *icons[11],*titles[11],*prompt;
    MileageCamera* camera;
    MileageFlow();
};
#endif

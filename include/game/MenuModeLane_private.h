#ifndef MENU_MODE_LANE_PRIVATE_H
#define MENU_MODE_LANE_PRIVATE_H
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *) throw();
#include "game/types/SceneBase.h"
struct MenuModeBase : SceneBase {
    virtual void _key();
    int cup, course, variant, round, startAnim, timer, itemCount, randomItem;
    int role, modeFlag, items[3], character, kart, mode, roundIndex, cc, gate;
    void *input;
    int selection;
    MenuModeBase();
    ~MenuModeBase();
};
struct MenuWidget {
    char pad[0x3c]; float x, y;
    MenuWidget(int);
    void SetPosition(float a, float b) { x=a; y=b; }
};
struct MenuScene : MenuModeBase {
    virtual void _key();
    ~MenuScene();
    int state, state2;
    MenuWidget *widgets[3];
    MenuScene();
};
struct GameModeBase {
    void *vt;
    GameModeBase();
    ~GameModeBase();
};
struct MenuDisplay {
    char opaque[0x1c];
    MenuDisplay(int);
};
struct MenuMode : GameModeBase {
    MenuMode();
    MenuModeBase *scene;
    int cup, course, variant, round, startAnim, timer, itemCount, randomItem;
    int role, modeFlag, character, kart, menuId, mode, roundIndex, gate, selection;
    MenuDisplay *display;
};
extern "C" {
extern int g_cupId, g_localPcbRole, g_characterId, g_gameMode, g_roundIndex;
extern int g_ccClass, g_kartVariant, g_humanPlayerCount;
extern unsigned char g_rendererGateFlag, g_lakituStartAnimDone, g_namCamFlag;
extern unsigned char MenuModeLane_data_806D0050, lbl_806D0051, lbl_806D1290;
extern unsigned char lbl_806D1264[3];
extern int lbl_806CF110;
extern volatile int lbl_806D12C0;
extern int DebugOverlay_RaceConfig_data_804E53B0[3];
extern char lbl_806D005C[8], lbl_806D0054[8];
extern char g_playerData[0x2000];
extern void *MenuScene_vtable_804E5444[], *MenuModeBase_vtable_804E549C[], *lbl_803FE0C8[], *MenuModeLane_data_804E54D8[];
extern const float lbl_806DA690, lbl_806DA694, lbl_806DA698, lbl_806DA69C;
void fn_8023E808(MenuWidget *, int);
void fn_80209FA4(); void fn_801F9888();
void InputCmd_SetGlobalConfig(void *); void *InputCmd_GetGlobalConfig();
void fn_801F6494(); int fn_801DC868();
SceneBase *fn_8020CEAC();
MenuModeBase *fn_80271340(SceneBase *, int, char *, char *, int);
void fn_801F98CC(); void fn_80209FE8();
void fn_80218B5C(MenuDisplay *); void fn_80218B80(MenuDisplay *);
void fn_80218D98(MenuDisplay *, int);
void SetTimerModeEnabled(int); void SetCourseParams(int,int,int,int);
int VSMode_SeedRandomItemSequence(int,int,int);
int GetDisplayBufferIndex();
int RaceSlot_InitSlot(int, int, int, int, int);
int RaceSlot_SetItemSlotByte(int, int, unsigned char);
void SetKartVariant(int); void fn_801DC870(int);
void fn_80121210(); void clRom_PurgeAll();
void MemoryManager_TimedFree(void *);
void dtor_8002CDF4(void *, int);
}
#endif

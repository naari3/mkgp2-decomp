#ifndef GAME_MENU_DISPATCH_PRIVATE_H
#define GAME_MENU_DISPATCH_PRIVATE_H
#include "game/MenuDraw_private.h"
struct MenuEntryScene : MenuChildView { char state[0x14 - 4]; MenuEntryScene(); };
struct MenuTitleScene : MenuChildView { char state[0x20 - 4]; MenuTitleScene(); };
struct MenuAttractScene : MenuChildView { char state[0x38 - 4]; MenuAttractScene(); };
struct MenuUnknown8020E0E0Scene : MenuChildView { char state[0x28 - 4]; MenuUnknown8020E0E0Scene(); };
struct MenuUnknown8020D850Scene : MenuChildView { char state[0x38 - 4]; MenuUnknown8020D850Scene(); };
struct MenuCardScene : MenuChildView { char state[0x2c - 4]; MenuCardScene(); };
struct MenuClassScene : MenuChildView { char state[0x58 - 4]; MenuClassScene(); };
struct MenuFrameSelectionScene : MenuChildView { char state[0x1d8 - 4]; MenuFrameSelectionScene(); };
struct MenuKartScene : MenuChildView { char state[0xdc - 4]; MenuKartScene(); };
struct MenuFigureScene : MenuChildView { char state[0xb0 - 4]; MenuFigureScene(); };
struct MenuCupScene : MenuChildView { char state[0x158 - 4]; MenuCupScene(); };
struct MenuRoundScene : MenuChildView { char state[0x16c - 4]; MenuRoundScene(); };
struct MenuCourseScene : MenuChildView { char state[0x160 - 4]; MenuCourseScene(); };
struct MenuItemSelectScene : MenuChildView { char state[0xec - 4]; MenuItemSelectScene(); };
struct MenuItemScene : MenuChildView { char state[0x34 - 4]; MenuItemScene(); };
struct MenuGpPleaseScene : MenuChildView { char state[0x1c - 4]; MenuGpPleaseScene(); };
struct MenuTaPleaseScene : MenuChildView { char state[0x3c - 4]; MenuTaPleaseScene(); };
struct Menuranking_displayScene : MenuChildView { char state[0x3c - 4]; Menuranking_displayScene(); };

extern "C" {
void CGameCoin_ProcessInput(InputState *);
void fn_801A1280(); void fn_8020F290(); void fn_801DAEC0(); void fn_801DABFC();
void GXDrawDone(); void fn_80121210(); void clRom_PurgeAll();
void Sprite_SetupAnim(Sprite *, int, int, int);
void Sprite_SetAnimParam(Sprite *, int, short);
void fn_801A0550(Sprite *); void Sprite_Destroy(Sprite *, int);
int fn_801B7EF8();
int CreditMgr_GetCoinsPerCredit(int);
extern int lbl_806CFD60, lbl_806D1804, lbl_806D1808, lbl_806D1810, lbl_806D1814, lbl_806D1824;
extern signed char lbl_806D1818, lbl_806D184C;
extern unsigned char lbl_806D1819;
extern short lbl_806D181A;
extern short *lbl_806D1828, *lbl_806D182C, *lbl_806D1830, *lbl_806D1834;
extern const float lbl_806D9890, lbl_806D98E0, lbl_806D98E8, lbl_806D98EC, lbl_806D98F8, lbl_806D98FC;
extern const float lbl_806D9924, lbl_806D9928, lbl_806D992C, lbl_806D9930, lbl_806D9934;
extern const double lbl_806D9938, lbl_806D9940;
}
#endif

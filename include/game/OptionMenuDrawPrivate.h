#ifndef GAME_OPTION_MENU_DRAW_PRIVATE_H
#define GAME_OPTION_MENU_DRAW_PRIVATE_H
#include "game/types/OptionDrawPrefix.h"
#include "game/types/OptionDrawPanel.h"
#include "game/types/OptionDrawTarget.h"
#include "game/types/OptionDrawScene.h"
struct RankLog;
extern "C" {
int isJapanese();
extern RankLog *lbl_806D10A0;
const char *get_title_name_global(RankLog *log);
const char *GetTextureByIdAndLang(int,int);
const char *fn_8013C26C(int,int);
void fn_80168798(int,const char *,float,float,float,...);
void fn_80168D84(int,const char *,float,float,float,...);
void fn_80167C60(int,const void *,float,float,float,...);
void fn_80168404(int,const char *,float,float,float,float,float,...);
void fn_80168B90(int,const char *,float,float,float,float,float,float,...);
void fn_801695E0(int,int,int,float,float,float);
void fn_80169334(int,int,int,float,float,float,float,float);
void fn_8013C7B0(void *,float,float);
void fn_8013C5FC(void *,float);
void fn_8013C674(void *,float);
void fn_8013C6EC(void *,float,float,float);
void fn_8013C4A4(void *,float);
void fn_8013C91C(void *);
void fn_8013DAC8(void *,int);
extern const float lbl_806D8394;
extern const float lbl_806D8398;
extern const float lbl_806D839C;
extern const float lbl_806D83B0;
extern const float lbl_806D83B4;
extern const float lbl_806D83B8;
extern const float lbl_806D83CC;
extern const float lbl_806D83D0;
extern const float lbl_806D83D4;
extern const float lbl_806D83DC;
extern const float lbl_806D83E0;
extern const float lbl_806D83EC;
extern const float lbl_806D8410;
extern const float lbl_806D8414;
extern const float lbl_806D8418;
extern const float lbl_806D8428;
extern const float lbl_806D8454;
extern const float lbl_806D84E8;
extern const float lbl_806D8504;
extern const float lbl_806D855C;
extern const float lbl_806D8578;
extern const float lbl_806D857C;
extern const float lbl_806D8580;
extern const float lbl_806D8584;
extern const float lbl_806D8588;
extern const float lbl_806D858C;
extern const float lbl_806D8590;
extern const float lbl_806D8594;
extern const float lbl_806D8598;
extern const float lbl_806D85A0;
extern const float lbl_806D85A4;
extern const float lbl_806D85A8;
extern const float lbl_806D85AC;
extern const float lbl_806D85B0;
extern const float lbl_806D85B4;
extern const float lbl_806D85B8;
extern const float lbl_806D85BC;
extern const float lbl_806D85C0;
extern const float lbl_806D85C4;
extern const float lbl_806D85C8;
extern const float lbl_806D85CC;
extern const char lbl_806D83E4[4];
extern const char lbl_806D83F0[8];
extern const char lbl_806D8574[4];
extern const char lbl_806D859C[4];
}
#endif

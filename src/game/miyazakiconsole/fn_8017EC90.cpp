#include "game/miyazakiconsole/miyazakiconsole.h"
#include "game/miyazakiconsole/fn_8017EC90_private.h"
extern "C" {
extern const char lbl_806D91D4[4];
extern unsigned int lbl_806CFB70;
extern unsigned char lbl_806CFB78, lbl_806D160C;
extern unsigned short lbl_806CFB7A;
extern int lbl_806D1610, lbl_806D1608;
extern int lbl_806D166C, lbl_806D1670;
extern Menu *lbl_806D165C;
void fn_80192348(unsigned int);
void SoundMgr_Play(unsigned int);
void fn_8019190C(unsigned int, unsigned char);
void fn_801915F4(unsigned int, unsigned short);
unsigned int fn_801915DC(unsigned int);
void fn_801814C8();
void fn_801920D4();
void fn_8017FF10(int, int, const char *, ...);
}
// Console parameter tables and menu labels share the original section base.
// Integer sound ID tables and float curves are data, with no layout fillers.

extern "C" const ConsoleParameters lbl_80376220 = {
    {96, 255, 0, 200, 64, 0, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255, 0, 96, 255},
    {
        1.0f, 0.699999988079071f, 0.8999999761581421f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
        1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
        66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
        1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
        83.33333587646484f, 5000.0f, 83.33333587646484f,
    }
};
extern "C" const char lbl_803766C4[10] = "SOUNDTEST";
extern "C" const char lbl_803766D0[10] = "CHARACTOR";
extern "C" const char lbl_803766DC[10] = "MINI GAME";
static const unsigned int consoleData_4C8[18] = {0, 0, 1, 24, 28, 33, 36, 58, 69, 79, 80, 107, 115, 126, 128, 203, 213, 214};
extern "C" const char lbl_80376730[10] = "JUMPDRIFT";
extern "C" const char lbl_8037673C[10] = "WHEELSPIN";
extern "C" const char lbl_80376748[10] = "STARTDASH";
extern "C" const char lbl_80376754[12] = "ITEMRECEIVE";
extern "C" const char lbl_80376760[9] = "DAMAGE01";
extern "C" const char lbl_8037676C[9] = "DAMAGE02";
extern "C" const char lbl_80376778[9] = "DAMAGE03";
extern "C" const char lbl_80376784[9] = "DAMAGE04";
extern "C" const char lbl_80376790[9] = "DAMAGE05";
static const unsigned int consoleData_57C[13] = {215, 236, 257, 278, 299, 321, 342, 363, 384, 405, 426, 448, 469};
extern "C" const char lbl_803767D0[11] = "clMiyazaki";
extern "C" const char lbl_803767DC[12] = "clJobRunner";
static const char consoleData_5C8[14] = "Ending Select";
static const char consoleData_5D8[12] = "Type Select";
static const char consoleData_5E4[13] = "Stage Select";
static const char consoleData_5F4[13] = "Parts Select";
static const char consoleData_604[10] = "Result GP";
static const char consoleData_610[10] = "Result TA";
static const char consoleData_61C[17] = "Result Challenge";
static const char consoleData_630[11] = "SpriteTest";
static const char consoleData_63C[10] = "TitleTest";
static const char consoleData_648[12] = "GetItemTest";
static const char consoleData_654[14] = "NextChallenge";
static const char consoleData_664[9] = "YNWindow";
static const char consoleData_670[10] = "MsgWindow";
static const char consoleData_67C[10] = "TARanking";
static const char consoleData_688[11] = "ModeSelect";
static const char consoleData_694[16] = "TimeZone Select";
static const char consoleData_6A4[9] = "MIDNIGHT";
static const char consoleData_6B0[11] = "Dir Select";
static const char consoleData_6BC[9] = "Straight";
static const char consoleData_6C8[13] = "Select State";
static const char consoleData_6D8[15] = "Success Cups:1";
static const char consoleData_6E8[15] = "Success Cups:2";
static const char consoleData_6F8[15] = "Success Cups:3";
static const char consoleData_708[15] = "Success Cups:4";
static const char consoleData_718[15] = "Success Cups:5";
static const char consoleData_728[15] = "Success Cups:6";
static const char consoleData_738[9] = "Accolade";
static const char consoleData_744[11] = "CardBrowse";
static const char consoleData_750[9] = "PlayDemo";
static const char consoleData_75C[9] = "GetTitle";
static const char consoleData_768[9] = "NextRace";
static const char consoleData_774[10] = "CourceAdj";
static const char consoleData_780[11] = "BattleWait";
static const char consoleData_78C[10] = "PartsTest";
static const char consoleData_798[14] = "Symbol Select";
static const char consoleData_7A8[10] = "AllSymbol";
static const char consoleData_7B4[11] = "scene_data";
static const char consoleData_7C0[14] = "Filter Select";
static const char consoleData_7D0[12] = "ModelViewer";
static const char consoleData_7DC[22] = " START  : Switch Mode";
static const char consoleData_7F4[29] = "  X     : Draw Symbol Select";
static const char consoleData_814[33] = "  Y     : FileList Filter Select";
static const char consoleData_838[22] = "  R     : Load Model ";
static const char consoleData_850[27] = "  B     : Exit ModelViewer";
static const char consoleData_86C[14] = "  %4.4f %4.4f";
static const char consoleData_87C[35] = "  Y     : Animetion Enable/Disable";
static const char consoleData_8A0[15] = "  AX/Y  : Move";
static const char consoleData_8B0[15] = "  L/R   : Zoom";
static const char consoleData_8C0[53] = "//=================================================\n";
static const char consoleData_8F8[36] = "static const stAreaData Area[] = {\n";
static const char consoleData_91C[24] = "    { %ff, %ff, %ff },\n";
static const char consoleData_934[33] = "    AREA_FLAG_EXACT, 0.0f, 0.0f\n";
extern "C" const char lbl_80376B78[15] = "%s SymbolList\n";
extern "C" const char lbl_80376B88[14] = "Accel  : Play";
static const char consoleData_978[14] = "Stream player";
static const char consoleData_988[23] = "+--------------------+";
static const char consoleData_9A0[23] = "|                    |";
static const char consoleData_9B8[11] = " Volume:%d";
static const char consoleData_9C4[11] = " Pitch :%d";
static const char consoleData_9D0[26] = "Handle : Change Parameter";
static const char consoleData_9EC[21] = "Voice player : MARIO";
static const char consoleData_A04[21] = "Voice player : LUIGI";
static const char consoleData_A1C[21] = "Voice player : WARIO";
static const char consoleData_A34[21] = "Voice player : PEACH";
static const char consoleData_A4C[21] = "Voice player : KOOPA";
static const char consoleData_A64[23] = "Voice player : KINOPIO";
static const char consoleData_A7C[22] = "Voice player : DONKEY";
static const char consoleData_A94[21] = "Voice player : YOSHI";
static const char consoleData_AAC[22] = "Voice player : PACMAN";
static const char consoleData_AC4[24] = "Voice player : MSPACMAN";
static const char consoleData_ADC[23] = "Voice player : MONSTER";
static const char consoleData_AF4[23] = "Voice player : WALUIGI";
static const char consoleData_B0C[23] = "Voice player : MAMETCH";
static const char consoleData_B24[9] = "LAUGHING";
static const char consoleData_B30[15] = "FX player : %s";
static const char consoleData_B40[13] = "Chara Select";
static const char consoleData_B50[9] = "MSPACMAN";
static const char consoleData_B5C[12] = "Camera Type";
static const char consoleData_B68[10] = "Main Menu";
static const char consoleData_B74[13] = "SoundTest:FX";
static const char consoleData_B84[16] = "SoundTest:Voice";
static const char consoleData_B94[17] = "SoundTest:Stream";
static const char consoleData_BA8[12] = "ConsoleTest";
static const char consoleData_BB4[25] = "teSingleton<clMenuInput>";
static const char consoleData_BD0[12] = "clMenuInput";
static const char consoleData_BDC[17] = "clSceneInterface";

static inline int MenuBottom(Menu *m) {
    if (m==0) return 0;
    if (m->count<9) return m->count+3;
    return 12;
}
static inline void SoundMenuDraw() {
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+2,consoleData_988);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+3,consoleData_9A0);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+4,consoleData_9A0);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+5,consoleData_988);
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+3,consoleData_9B8,lbl_806CFB78);
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+4,consoleData_9C4,lbl_806CFB7A);
    {
        int line=lbl_806D160C;
        int y=lbl_806D1670;
        int x=lbl_806D166C;
        fn_8017FF10(x+16,(y+line)+3,lbl_806D91D4);
    }
    {
        Menu *m=lbl_806D165C;
        int x=lbl_806D166C;
        int y=lbl_806D1670;
        int bottom=MenuBottom(m);
        fn_8017FF10(x,y+bottom,lbl_80376B88);
    }
    {
        Menu *m=lbl_806D165C;
        int x=lbl_806D166C;
        int y=lbl_806D1670;
        int bottom=MenuBottom(m);
        fn_8017FF10(x,y+(bottom+1),consoleData_9D0);
    }
}


extern "C" int fn_8017EC90(int msg, void *, int arg, int, unsigned int sub) {
    switch (msg) {
    case 0:
        switch (sub) {
        case 9:
            if (lbl_806CFB70 != 0xffffffff) {
                fn_80192348(lbl_806CFB70);
                lbl_806CFB70=-1;
            }
            arg += consoleData_57C[lbl_806D1610];
            SoundMgr_Play(arg);
            lbl_806CFB70=arg;
            fn_8019190C(arg,lbl_806CFB78);
            fn_801915F4(lbl_806CFB70,lbl_806CFB7A);
            break;
        case 1:
            if (++lbl_806D160C > 1) lbl_806D160C=0;
            break;
        case 11:
            fn_801814C8();
            break;
        case 5:
            switch(lbl_806D160C) {
            case 0: lbl_806CFB78=(lbl_806CFB78-1)&0x7f; break;
            case 1: lbl_806CFB7A=(lbl_806CFB7A-0x40)&0xff; break;
            }
            break;
        case 6:
            switch(lbl_806D160C) {
            case 0: lbl_806CFB78=(lbl_806CFB78+1)&0x7f; break;
            case 1: lbl_806CFB7A=(lbl_806CFB7A+0x40)&0xff; break;
            }
            break;
        case 7:
        case 8:
            if (lbl_806CFB70 != 0xffffffff) {
                fn_80192348(lbl_806CFB70);
                lbl_806CFB70=-1;
            }
            lbl_806CFB78=(fn_801915DC(arg+consoleData_57C[lbl_806D1610])>>1)&0x7f;
            lbl_806CFB7A=0x2000;
            break;
        }
        return 0;
    case 1: return 0;
    case 3: return 0;
    case 4:
        SoundMenuDraw();
        return 0;
    case 2:
        fn_801920D4();
        lbl_806CFB70=-1;
        return 0;
    }
    return 0;
}

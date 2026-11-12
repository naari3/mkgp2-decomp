/* Original console TU: 0x8017CE1C..0x8017FF10.
 * Deferred generation uses reverse source order. The namespaces retain the
 * existing external type views; per-TU ABI bridges keep the public symbols.
 * clMiyazaki owns its compiler-emitted vtable, base list and RTTI records.
 */
#include "game/FlowScene.h"
#include "game/mapobject/mapobject17b_debug_private.h"
#include "dolphin/dvd.h"

#include "game/types/Vec3f.h"
#define strlen MiyazakiStringLength
#include "game/miyazakiconsole/miyazakiconsole.h"
#undef strlen
#include "game/miyazakiconsole/fn_8017EC90_private.h"

#include "game/miyazakiconsole/console_update_private.h"
#include "game/types/clJobRunner.h"

struct clMiyazaki : clJobRunner {
    int unused;
    inline clMiyazaki(const char *);
    virtual int Update();
    virtual void Draw();
    virtual ~clMiyazaki();
    void PrintPool(const char *format);
};
namespace create_view {
struct ConsoleDisplay {
    unsigned char active;
    void Enable() { active=1; }
};
extern "C++" {
extern const char lbl_80376220[];
extern const char lbl_806D923C[4];
extern void *lbl_803FDF28[], *lbl_803FDF40[];
extern int lbl_806D15F8, lbl_806D1600, lbl_806D166C, lbl_806D1670;
extern VObject *lbl_806D15FC;
void fn_80180170();
Menu *fn_801816AC(const char *);
void fn_801805AC(Menu *, void *);
void fn_801804CC(Menu *, const char *);
void fn_8017F538();
ConsoleDisplay *fn_801DAEC0();
}
struct ConsoleInputData {
    void *vt;
    unsigned char enabled, flag5, flag6;
    int fields[8];
    ConsoleInputData() {
        vt=lbl_803FDF28;
        g_pInputState=(InputState *)this;
        vt=lbl_803FDF40;
        enabled=0;
        flag5=1;
        flag6=1;
        for (int i=0;i<8;i++) fields[i]=0;
    }
};

}
extern "C++" clMiyazaki *fn_8017FD68() {
    const char *s=create_view::lbl_80376220;
    return new clMiyazaki(s);
}
clMiyazaki::clMiyazaki(const char *s) {
        using namespace create_view;
        create_view::lbl_806D15F8=0;
        create_view::lbl_806D15FC=0;
        create_view::lbl_806D1600=0;
        create_view::fn_80180170();
        create_view::lbl_806D166C=0;
        create_view::lbl_806D1670=5;
        Menu *menu=create_view::fn_801816AC(s+0xb68);
        create_view::fn_801805AC(menu,(void *)create_view::fn_8017F538);
        create_view::fn_801804CC(menu,s+0xb74);
        create_view::fn_801804CC(menu,s+0xb84);
        create_view::fn_801804CC(menu,s+0xb94);
        create_view::fn_801804CC(menu,s+0x7d0);
        create_view::fn_801804CC(menu,s+0xba8);
        create_view::fn_801804CC(menu,create_view::lbl_806D923C);
        if (GetInput()==0) new ConsoleInputData;
        if (GetInput()!=0) {
            InputState *in=GetInput();
            in->enabled=1;
            in->held=0;
            in->edge=0;
        }
        create_view::fn_801DAEC0()->Enable();
    }

namespace view11 {
extern "C++" {
extern char MiyazakiMode_vtable_80491880[];
void fn_801DAE54(void);
void fn_8018137C(void);
void fn_8018013C(void);

void MemoryManager_TimedFree(void *p);
}

struct VRel {
    virtual void v0();
    virtual void Release();
};

struct VDel {
    virtual ~VDel();
};

extern VRel *lbl_806D15FC;



}
clMiyazaki::~clMiyazaki() {
    using namespace view11;
    view11::fn_801DAE54();
    if (view11::lbl_806D15FC != 0) {
        view11::lbl_806D15FC->Release();
        view11::lbl_806D15FC = 0;
    }
    view11::fn_8018137C();
    view11::fn_8018013C();
    delete (view11::VDel *)g_pInputState;
    g_pInputState = 0;
}

namespace view10 {

extern "C++" {
void fn_80180100();
void CGameCoin_ProcessInput(InputState *);
void *GetInputManager();
ConsoleInput *InputMgr_GetPlayer(void *, int);
extern ConsolePage *lbl_806D15FC;
extern int lbl_806D1600;
extern int lbl_806D15F8;
extern unsigned char lbl_806CFBA1;
void fn_80202BCC();
void fn_80202A24();
void *fn_801DAEC0();
void fn_801DABFC(void *);
void fn_8014F5E0();
void fn_80181144();
}

}
int clMiyazaki::Update() {
 using namespace view10;

    view10::fn_80180100();
    if (GetInput() != 0) view10::CGameCoin_ProcessInput(GetInput());
    if (view10::lbl_806D15FC != 0) {
        unsigned char close = 0;
        if (view10::InputMgr_GetPlayer(view10::GetInputManager(), 0)->IsHeld(0x400)) {
            if (++view10::lbl_806D1600 >= 60) close = 1;
        } else {
            view10::lbl_806D1600 = 0;
        }
        if (view10::lbl_806D15FC->closed != 0 || close) {
            view10::lbl_806D15FC->Release();
            view10::lbl_806D15FC = 0;
            view10::fn_80202BCC();
            if (view10::lbl_806CFBA1 != 1) view10::lbl_806CFBA1 = 1;
        } else {
            view10::fn_80202A24();
            view10::lbl_806D15FC->Update();
            view10::fn_801DABFC(view10::fn_801DAEC0());
        }
        view10::fn_8014F5E0();
    } else {
        view10::fn_80181144();
    }
    if (view10::lbl_806D15F8 != 0) {
        switch (view10::lbl_806D15F8) {
        case 1:
            return -4;
        }
    }
    return -2;
}
namespace view9 {
class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void Draw();
};

extern "C++" {
extern Obj *lbl_806D15FC;
void fn_802029EC(void);
void fn_8011FAB8(void);
void fn_80180B34(void);
void fn_8018005C(void);
void HSD_StateInvalidate(int);
}


}
void clMiyazaki::Draw() {
 using namespace view9;

    if (view9::lbl_806D15FC != 0) {
        view9::fn_802029EC();
        view9::lbl_806D15FC->Draw();
    }
    view9::fn_8011FAB8();
    view9::fn_80180B34();
    if (view9::lbl_806D15FC == 0) {
        view9::fn_8018005C();
    }
    HSD_StateInvalidate(0x7F);
}
namespace view8 {
extern "C++" {
extern const char lbl_80376220[];
extern const char *lbl_80491768[9];
extern const char lbl_806D91E0[8],lbl_806D91E8[8],lbl_806D91F0[8],lbl_806D91F8[8],lbl_806D9200[8],lbl_806D9208[8],lbl_806D9210[8],lbl_806D9218[8],lbl_806D9220[8],lbl_806D9228[8],lbl_806D9230[8],lbl_806D9238[4];
extern const char lbl_806D91CC[8],lbl_806D91D8[4],lbl_806D9154[8],lbl_806D915C[8],lbl_806D9164[8],lbl_806D916C[8],lbl_806D9174[8],lbl_806D917C[4],lbl_806D9180[4];
extern int lbl_806D15F8,lbl_806D1608,lbl_806D1604,lbl_806D1614,lbl_806D1628,lbl_806D1630,lbl_806D1634,lbl_806D1638;
extern unsigned char lbl_806CFB78,lbl_806D160C,lbl_806CFB84,lbl_806CFB85;
extern unsigned short lbl_806CFB7A;
extern float lbl_806D1624;
extern const float lbl_806D91B0;
extern int g_characterId;
extern char g_playerData[];
int sprintf(char *, const char *, ...);
char *strstr(const char *,const char *);
Menu *fn_80180670(const char *,unsigned char);
Menu *fn_801816AC(const char *);
void fn_801804CC(Menu *,const char *);
void fn_80180458(Menu *);
void fn_801805AC(Menu *,void *);
void fn_8017EB58();
void fn_8017F1E8();
void fn_8017D660();
void fn_8017CE1C();
void fn_8017EFFC(unsigned int);
void DMAChannelManager_Init();
void fn_801D7610(void *,int);
}
/* The three sub-menu builders are inline helpers with their own Menu*
 * locals: as caller locals (one shared `menu`) the allocator numbered them
 * below the loop temps and swapped r29/r30/r31 (regfix diag, 11-09). */
static inline void CreateNumberMenu(const char *name) {
    Menu *m=fn_801816AC(name);
    fn_801805AC(m,(void *)fn_8017EB58);
    char text[16];
    for (int i=0;i<21;i++) {
        sprintf(text,lbl_806D91CC,i);
        fn_801804CC(m,text);
    }
}
static inline void CreateBankMenu(const char *name) {
    Menu *m=fn_80180670(name,1);
    if (m!=0) {
        for (int i=0;i<9;i++) fn_801804CC(m,lbl_80491768[i]);
    }
}
static inline void AddSoundKinds(Menu *m,const char *s) {
    fn_801804CC(m,lbl_806D91E0);
    fn_801804CC(m,lbl_806D91E8);
    fn_801804CC(m,lbl_806D91F0);
    fn_801804CC(m,lbl_806D91F8);
    fn_801804CC(m,lbl_806D9200);
    fn_801804CC(m,lbl_806D9208);
    fn_801804CC(m,lbl_806D9210);
    fn_801804CC(m,lbl_806D9218);
    fn_801804CC(m,lbl_806D9220);
    fn_801804CC(m,s+0xb50);
    fn_801804CC(m,lbl_806D9228);
}
static inline void CreateSoundKindMenu(const char *s) {
    Menu *m=fn_80180670(s+0xb40,1);
    if (m!=0) AddSoundKinds(m,s);
}
static inline bool ListStreamFiles(Menu *&m,const char *s) {
    m=fn_801816AC(s+0x7d0);
    if (m==0) return false;
    fn_801805AC(m,(void *)fn_8017D660);
    fn_80180458(m);
    DVDDir dir;
    DVDDirEntry entry;
    if (DVDOpenDir(lbl_806D917C,&dir)!=1) return true;
    while (DVDReadDir(&dir,&entry)!=0) {
        if (entry.isDir==0) {
            int filter=lbl_806D1630;
            if (filter!=0) {
                if (filter<=26) {
                    signed char upper=(signed char)(filter+64);
                    signed char lower=(signed char)(filter+96);
                    signed char first=entry.name[0];
                    if (first!=upper && first!=lower) continue;
                } else if (filter<=36) {
                    if (entry.name[0]!=(signed char)(filter+21)) continue;
                }
            }
            if (strstr(entry.name,lbl_806D9180)!=0) fn_801804CC(m,entry.name);
        }
    }
    DVDCloseDir(&dir);
    return true;
}
extern "C++" int fn_8017F538(unsigned int msg,void *,int cursor,int,unsigned int sub) {
    const char *s=lbl_80376220;
    unsigned int id;
    Menu *menu;
    switch(msg) {
    case 0:
        switch(sub) {
        case 1:
            switch(cursor) {
            case 0: {
                CreateBankMenu(s+0x5d8);
                break;
            }
            case 1: {
                CreateSoundKindMenu(s);
                break;
            }
            case 2: {
                CreateNumberMenu(s+0x978);
                break;
            }
            case 3: {
                Menu *m=fn_80180670(s+0xb5c,1);
                if (m!=0) {
                    fn_801804CC(m,lbl_806D9230);
                    fn_801804CC(m,lbl_806D9238);
                }
                break;
            }
            case 4: {
                CreateSoundKindMenu(s);
                break;
            }
            default: lbl_806D15F8=1; break;
            }
            break;
        }
        return 0;
    case 11:
        lbl_806D15F8=1;
        return 0;
    case 1:
        switch(cursor) {
        case 0:
            if (sub<9) {
                char title[48];
                lbl_806D1608=sub;
                lbl_806D1604=0;
                sprintf(title,s+0xb30,lbl_80491768[sub]);
                menu=fn_801816AC(title);
                fn_801805AC(menu,(void *)fn_8017F1E8);
                if (menu!=0) {
                    const unsigned int *range=(const unsigned int *)(s+0x4c8);
                    for (id=range[lbl_806D1608*2];id<=range[lbl_806D1608*2+1];id++) {
                        sprintf(title,lbl_806D91D8,id);
                        fn_801804CC(menu,title);
                        lbl_806D1604++;
                    }
                }
                lbl_806CFB78=0x7f;
                lbl_806CFB7A=0x2000;
                lbl_806D160C=0;
            }
            break;
        case 1:
            fn_8017EFFC(sub);
            break;
        case 3:
            lbl_806D1614=sub;
            lbl_806D1624=lbl_806D91B0;
            lbl_806CFB84=1;
            lbl_806D1628=0;
            lbl_806CFB85=1;
            lbl_806D1630=0;
            lbl_806D1634=0;
            lbl_806D1638=0;
            {
                Menu *streamMenu;
                if (ListStreamFiles(streamMenu,s)) DMAChannelManager_Init();
            }
            break;
        case 4: {
            g_characterId=sub;
            Menu *m=fn_801816AC(lbl_806D9154);
            fn_801805AC(m,(void *)fn_8017CE1C);
            fn_801804CC(m,s+0x738);
            fn_801804CC(m,s+0x744);
            fn_801804CC(m,lbl_806D915C);
            fn_801804CC(m,lbl_806D9164);
            fn_801804CC(m,s+0x750);
            fn_801804CC(m,s+0x75c);
            fn_801804CC(m,s+0x768);
            fn_801804CC(m,s+0x774);
            fn_801804CC(m,lbl_806D916C);
            fn_801804CC(m,lbl_806D9174);
            fn_801804CC(m,s+0x780);
            fn_801804CC(m,s+0x78c);
            fn_801D7610(g_playerData,1);
            break;
        }
        }
        return 0;
    case 3: return 0;
    case 4: return 0;
    case 2: return 0;
    }
    return 0;
}

}

namespace view7 {
extern "C++" int fn_8017EC90(int, void *, int, int, unsigned int);
extern "C++" {
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
unsigned char fn_801915DC(int);
void fn_801814C8();
void fn_801920D4();
void fn_8017FF10(int, int, const char *, ...);
}
// Console parameter tables and menu labels share the original section base.
// Integer sound ID tables and float curves are data, with no layout fillers.

extern "C++" const ConsoleParameters lbl_80376220 = {
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
extern "C++" const char lbl_803766C4[10] = "SOUNDTEST";
extern "C++" const char lbl_803766D0[10] = "CHARACTOR";
extern "C++" const char lbl_803766DC[10] = "MINI GAME";
static const unsigned int consoleData_4C8[18] = {0, 0, 1, 24, 28, 33, 36, 58, 69, 79, 80, 107, 115, 126, 128, 203, 213, 214};
extern "C++" const char lbl_80376730[10] = "JUMPDRIFT";
extern "C++" const char lbl_8037673C[10] = "WHEELSPIN";
extern "C++" const char lbl_80376748[10] = "STARTDASH";
extern "C++" const char lbl_80376754[12] = "ITEMRECEIVE";
extern "C++" const char lbl_80376760[9] = "DAMAGE01";
extern "C++" const char lbl_8037676C[9] = "DAMAGE02";
extern "C++" const char lbl_80376778[9] = "DAMAGE03";
extern "C++" const char lbl_80376784[9] = "DAMAGE04";
extern "C++" const char lbl_80376790[9] = "DAMAGE05";
static const unsigned int consoleData_57C[13] = {215, 236, 257, 278, 299, 321, 342, 363, 384, 405, 426, 448, 469};
static inline int MenuBottom(Menu *m) {
    if (m==0) return 0;
    if (m->count<9) return m->count+3;
    return 12;
}
static inline void SoundMenuDraw() {
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+2,"+--------------------+");
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+3,"|                    |");
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+4,"|                    |");
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+5,"+--------------------+");
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+3," Volume:%d",lbl_806CFB78);
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+4," Pitch :%d",lbl_806CFB7A);
    {
        int line=lbl_806D160C;
        int y=lbl_806D1670;
        int x=lbl_806D166C;
        fn_8017FF10(x+16,line+(y+3),lbl_806D91D4);
    }
    {
        Menu *m=lbl_806D165C;
        int x=lbl_806D166C;
        int y=lbl_806D1670;
        int bottom=MenuBottom(m);
        fn_8017FF10(x,y+bottom,"Accel  : Play");
    }
    {
        Menu *m=lbl_806D165C;
        int x=lbl_806D166C;
        int y=lbl_806D1670;
        int bottom=MenuBottom(m);
        fn_8017FF10(x,y+bottom+1,"Handle : Change Parameter");
    }
}


/* ---- fn_8017EFFC: voice player menu (was miyazakiconsole/fn_8017EFFC.cpp) ---- */
extern "C++" {
extern const char *lbl_8049178C[21];
int sprintf(char *, const char *, ...);
Menu *fn_801816AC(const char *);
void fn_801805AC(Menu *, void *);
void fn_801804CC(Menu *, const char *);
}

/* ---- fn_8017F1E8: FX player menu (was miyazakiconsole/fn_8017F1E8.cpp) ---- */
extern "C++" int fn_8017F1E8(int msg, void *, int arg, int, unsigned int sub) {
    arg += consoleData_4C8[lbl_806D1608*2];
    switch (msg) {
    case 0:
        switch (sub) {
        case 9:
            if (lbl_806CFB70 != 0xffffffff) {
                fn_80192348(lbl_806CFB70);
                lbl_806CFB70=-1;
            }
            SoundMgr_Play(arg);
            fn_8019190C(arg,lbl_806CFB78);
            fn_801915F4(arg,lbl_806CFB7A);
            lbl_806CFB70=arg;
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
            lbl_806CFB78=0x7f;
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

extern "C++" void fn_8017EFFC(unsigned int kind) {
    char title[64];
    lbl_806D1610 = kind;
    switch(kind) {
    case 0: sprintf(title, "Voice player : MARIO"); break;
    case 1: sprintf(title, "Voice player : LUIGI"); break;
    case 2: sprintf(title, "Voice player : WARIO"); break;
    case 3: sprintf(title, "Voice player : PEACH"); break;
    case 4: sprintf(title, "Voice player : KOOPA"); break;
    case 5: sprintf(title, "Voice player : KINOPIO"); break;
    case 6: sprintf(title, "Voice player : DONKEY"); break;
    case 7: sprintf(title, "Voice player : YOSHI"); break;
    case 8: sprintf(title, "Voice player : PACMAN"); break;
    case 9: sprintf(title, "Voice player : MSPACMAN"); break;
    case 10: sprintf(title, "Voice player : MONSTER"); break;
    case 11: sprintf(title, "Voice player : WALUIGI"); break;
    case 12: sprintf(title, "Voice player : MAMETCH"); break;
    }
    Menu *menu = fn_801816AC(title);
    fn_801805AC(menu, (void *)fn_8017EC90);
    for (unsigned int i=0; i<21; i++) fn_801804CC(menu, lbl_8049178C[i]);
    if (lbl_806D1610==4) fn_801804CC(menu, "LAUGHING");
    lbl_806CFB78 = (fn_801915DC(consoleData_57C[lbl_806D1610]) >> 1) & 0x7f;
    lbl_806CFB7A = 0x2000;
    lbl_806D160C = 0;
}


extern "C++" int fn_8017EC90(int msg, void *, int arg, int, unsigned int sub) {
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


}

namespace view6 {
extern "C++" {
typedef struct Node {
    char pad[0x38];
    unsigned int idx;
} Node;

extern unsigned int lbl_806CFB74;
extern unsigned char lbl_806CFB78;
extern Node *lbl_806D165C;
extern void *lbl_806D166C;
extern char *lbl_806D1670;
extern const char lbl_80376B88[];
extern void fn_801909A4(int);
extern void fn_801908F0(void);
extern void ClSound_PlayBgmStream(int slot, int id);
extern void clStream_setVolume(int slot, int vol);
extern void fn_801814C8(void);
extern void fn_8017FF10(void *, char *, const char *, ...);

int fn_8017EB58(int msg, int a1, int arg, int a3, int sub) {
    int ofs;
    Node *node;
    void *dst;
    char *buf;
    switch (msg) {
    case 0:
        switch (sub) {
        case 9:
            if (lbl_806CFB74 != 0xFFFFFFFF) {
                fn_801909A4(lbl_806CFB74);
                lbl_806CFB74 = -1;
            }
            ClSound_PlayBgmStream(arg, 0);
            clStream_setVolume(arg, lbl_806CFB78);
            lbl_806CFB74 = arg;
            break;
        case 10:
            break;
        case 11:
            fn_801814C8();
            break;
        }
        return 0;
    case 1:
        return 0;
    case 3:
        return 0;
    case 4:
        node = lbl_806D165C;
        dst = lbl_806D166C;
        buf = lbl_806D1670;
        if (node == 0) {
            ofs = 0;
        } else if (node->idx < 9) {
            ofs = node->idx + 3;
        } else {
            ofs = 12;
        }
        fn_8017FF10(dst, buf + ofs, lbl_80376B88, ofs);
        return 0;
    case 2:
        fn_801908F0();
        lbl_806CFB74 = -1;
        return 0;
    }
    return 0;
}

}

}

namespace view5 {

struct HSD_CObj;

class Scene3D {
public:
    virtual ~Scene3D();
    HSD_CObj *cobj;
    char pad08[0x307C];
    Scene3D(const char *name);
};

class clNormal3D {
public:
    char pad00[0x24];
    void *archive;
    char pad28[0x34];
    clNormal3D(const char *desc, int flags);
    ~clNormal3D();
};

struct clPathNode {
    char pad[0x34];
    clPathNode *next;
    ~clPathNode() {}
};

extern "C++" {
extern clPathNode *lbl_806D163C;
extern clPathNode *lbl_806D1640;
extern unsigned int lbl_806D1614;
extern Scene3D *lbl_806D1618;
extern float lbl_806D161C;
extern clNormal3D *lbl_806D1620;
extern float lbl_806D1624;
extern int lbl_806CFB7C;
extern float lbl_806CFB80;
extern unsigned char lbl_806CFB84;
extern Vec3f lbl_80677D00;
extern Vec3f lbl_80677D0C;
extern const char lbl_80376B78[];
extern char lbl_806D91C0[5];
extern char lbl_806D91C8[2];
void GXDrawDone(void);
void SetCourseScene3D(Scene3D *scene);
void TransparentDraw_RemoveByOwner(int owner);
void clNormal3D_SetFlags(clNormal3D *obj, unsigned int flags, int arg);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
int SceneDrawList_RegisterArchive(void *archive, int layer);
void HSD_CObjSetEyePosition(HSD_CObj *cobj, Vec3f *pos);
void HSD_CObjSetInterest(HSD_CObj *cobj, Vec3f *pos);
void HSD_CObjSetRoll(HSD_CObj *cobj, float roll);
void *Archive_GetCurrent(void *archive);
const char *HSD_ArchiveGetPublicName(void *archive, int index);
void DebugPrintf(const char *fmt, ...);
}

static inline void RemoveNode(clPathNode *n) {
    clPathNode *p;
    clPathNode *q;
    if (n == 0) {
        return;
    }
    p = lbl_806D163C;
    if (n == p) {
        lbl_806D163C = n->next;
        delete n;
        lbl_806D1640 = lbl_806D163C;
        return;
    }
    for (; (q = p->next) != 0; p = q) {
        if (q == n) {
            clPathNode *next = q->next;
            delete q;
            p->next = next;
            lbl_806D1640 = p;
            return;
        }
    }
}

extern "C++" void fn_8017E824(const char *name) {
    GXDrawDone();
    while (lbl_806D1640 != 0) {
        RemoveNode(lbl_806D1640);
    }
    if (lbl_806D1618 != 0) {
        delete lbl_806D1618;
        lbl_806D1618 = 0;
    }
    SetCourseScene3D(0);
    if (lbl_806D1620 != 0) {
        delete lbl_806D1620;
        lbl_806D1620 = 0;
    }
    if (lbl_806CFB7C >= 0) {
        TransparentDraw_RemoveByOwner(lbl_806CFB7C);
        lbl_806CFB7C = -1;
    }
    if (name == 0) {
        return;
    }
    lbl_806D1618 = new Scene3D(name);
    lbl_806D1620 = new clNormal3D(name, 0);
    clNormal3D_SetFlags(lbl_806D1620, 0x40000000, 0);
    if (lbl_806D1618 == 0 || lbl_806D1620 == 0) {
        return;
    }
    clNormal3D_SetScale(lbl_806D1620, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    SetCourseScene3D(lbl_806D1618);
    lbl_806CFB7C = SceneDrawList_RegisterArchive(lbl_806D1620->archive, 4);
    if (lbl_806D1614 == 1) {
        lbl_80677D00.x = 0.0f;
        lbl_80677D0C.x = 0.0f;
        lbl_80677D00.y = 500.0f;
        lbl_80677D00.z = 0.0f;
        lbl_80677D0C.y = -1.0f;
        lbl_80677D0C.z = 0.0f;
        lbl_806D161C = 1.570796f;
    } else {
        lbl_80677D00.x = 0.0f;
        lbl_80677D00.y = 0.0f;
        lbl_80677D00.z = 200.0f;
        lbl_80677D0C.x = 0.0f;
        lbl_80677D0C.y = 0.0f;
        lbl_80677D0C.z = -1.0f;
        lbl_806D161C = 0.0f;
    }
    HSD_CObj *cobj = lbl_806D1618->cobj;
    if (cobj != 0) {
        Vec3f at;
        at.x = 200.0f * lbl_80677D0C.x + lbl_80677D00.x;
        at.y = 200.0f * lbl_80677D0C.y + lbl_80677D00.y;
        at.z = 200.0f * lbl_80677D0C.z + lbl_80677D00.z;
        HSD_CObjSetEyePosition(cobj, &lbl_80677D00);
        HSD_CObjSetInterest(cobj, &at);
        HSD_CObjSetRoll(cobj, lbl_806D161C);
    }
    lbl_806D1624 = 0.0f;
    lbl_806CFB80 = 1.0f;
    lbl_806CFB84 = 1;
    if (lbl_806D1620->archive != 0) {
        void *arc = Archive_GetCurrent(lbl_806D1620->archive);
        DebugPrintf(lbl_80376B78, name);
        for (int i = 0;; i++) {
            const char *s = HSD_ArchiveGetPublicName(arc, i);
            if (s == 0) {
                break;
            }
            DebugPrintf(lbl_806D91C0, s);
        }
        DebugPrintf(lbl_806D91C8);
    }
}

}

namespace view4 {
struct clPathNode {
    char pad[0x34];
    clPathNode *next;
    void Append(clPathNode *n);
};

void clPathNode::Append(clPathNode *n) {
    if (next == 0) {
        next = n;
    } else {
        next->Append(n);
    }
}

}

namespace view3 {

struct clPathNode {
    Vec3f a;
    Vec3f b;
    Vec3f c;
    Vec3f d;
    int x30;
    clPathNode *next;

    clPathNode() {
        next = 0;
        a.x = 0.0f;
        a.y = 0.0f;
        a.z = 0.0f;
        b.x = 0.0f;
        b.y = 0.0f;
        b.z = 0.0f;
        c.x = 0.0f;
        c.y = 0.0f;
        c.z = 0.0f;
        d.x = 0.0f;
        d.y = 0.0f;
        d.z = 0.0f;
        x30 = 0;
    }
    void Append(clPathNode *n);
};

extern "C++" {
extern clPathNode *lbl_806D163C;
extern clPathNode *lbl_806D1640;
}

extern "C++" int fn_8017E6A8(void) {
    clPathNode *n = new clPathNode;
    if (n != 0) {
        if (lbl_806D163C == 0) {
            lbl_806D163C = n;
        } else {
            lbl_806D163C->Append(n);
        }
        lbl_806D1640 = n;
        return 1;
    }
    return 0;
}

}

namespace view2 {

static inline void MapDebugEditOrPrint(const char *base, MapDebugInput *input, unsigned char left) {
    Vec3f *point;
    clPathNode *sel;
    clPathNode *node;
    int i;
    if (left) {
        if (lbl_806D163C) {
                DebugPrintf(base + 0x8C0);
                DebugPrintf(base + 0x8F8);
                node = lbl_806D163C;
                while (node) {
                    DebugPrintf(lbl_806D9194);
                    for (i = 0, point = node->points; i < 4; i++, point++) {
                        DebugPrintf(base + 0x91C, point->x, point->y, point->z);
                    }
                    DebugPrintf(base + 0x934);
                    DebugPrintf(lbl_806D919C);
                    node = node->next;
                }
                DebugPrintf(lbl_806D91A4);
                DebugPrintf(base + 0x8C0);
        }
    } else {
            sel = lbl_806D1640;
            if (input->Pressed(2)) {
                if (sel) {
                    sel->index++;
                    if (sel->index > 3) sel->index = 0;
                    lbl_80677D00.x = sel->points[sel->index].x;
                    lbl_80677D00.z = sel->points[sel->index].z;
                }
            } else if (input->Held(1)) {
                if (sel) {
                    float axis = input->AxisX();
                    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
                        sel->points[sel->index].x += lbl_806D91A8 * (lbl_806D9190 * axis);
                    }
                    axis = input->AxisY();
                    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
                        sel->points[sel->index].z -= lbl_806D91A8 * (lbl_806D9190 * axis);
                    }
                }
            } else MapDebugMoveCamera(input);
    }
}

extern "C++" void fn_8017DF00() {
    const char *base = lbl_80376220;
    if (lbl_806D1618 == 0 || lbl_806D1620 == 0) return;
    unsigned char right;
    unsigned char left;
    right = 0;
    left = 0;
    MapDebugInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Right() > lbl_806D9188) {
        if (lbl_806D1634 == 0) right = 1;
        lbl_806D1634++;
    } else lbl_806D1634 = 0;
    if (input->Left() > lbl_806D9188) {
        if (lbl_806D1638 == 0) left = 1;
        lbl_806D1638++;
    } else lbl_806D1638 = 0;
    if (lbl_806D1628 == 0) return;
    if (lbl_806D1628 == 1) {
        if (input->Pressed(8)) lbl_806CFB84 = !lbl_806CFB84;
        MapDebugMoveCamera(input);
        float amount = input->Right();
        if (amount > lbl_806D9188) {
            Vec3f delta;
            delta.x = lbl_80677D0C.x * amount;
            delta.y = lbl_80677D0C.y * amount;
            delta.z = lbl_80677D0C.z * amount;
            lbl_80677D00.x += lbl_806D9190 * delta.x;
            lbl_80677D00.y += lbl_806D9190 * delta.y;
            lbl_80677D00.z += lbl_806D9190 * delta.z;
        }
        amount = input->Left();
        if (amount > lbl_806D9188) {
            Vec3f delta;
            delta.x = lbl_80677D0C.x * amount;
            delta.y = lbl_80677D0C.y * amount;
            delta.z = lbl_80677D0C.z * amount;
            lbl_80677D00.x -= lbl_806D9190 * delta.x;
            lbl_80677D00.y -= lbl_806D9190 * delta.y;
            lbl_80677D00.z -= lbl_806D9190 * delta.z;
        }
    } else if (lbl_806D1628 == 2) {
        if (input->Pressed(8)) {
            if (fn_8017E6A8()) {
                clPathNode *node = lbl_806D1640;
                node->points[0].x = lbl_80677D00.x;
                node->points[0].z = lbl_80677D00.z;
                node->points[1].x = lbl_80677D00.x;
                node->points[1].z = lbl_80677D00.z;
                node->points[2].x = lbl_80677D00.x;
                node->points[2].z = lbl_80677D00.z;
                node->points[3].x = lbl_80677D00.x;
                node->points[3].z = lbl_80677D00.z;
            }
        } else if (input->Pressed(4)) {
            MapDebugRemoveNode(lbl_806D1640);
            MapDebugSelectStart();
        } else if (right) {
            if (lbl_806D1640) {
                if (lbl_806D1640->next == 0) lbl_806D1640 = lbl_806D163C;
                else lbl_806D1640 = lbl_806D1640->next;
            }
            MapDebugSelectStart();
        } else {
            MapDebugEditOrPrint(base, input, left);
        }
    }
    void *camera = lbl_806D1618->cobj;
    if (camera) {
        Vec3f interest;
        interest.x = lbl_806D91AC * lbl_80677D0C.x + lbl_80677D00.x;
        interest.y = lbl_806D91AC * lbl_80677D0C.y + lbl_80677D00.y;
        interest.z = lbl_806D91AC * lbl_80677D0C.z + lbl_80677D00.z;
        HSD_CObjSetEyePosition(camera, &lbl_80677D00);
        HSD_CObjSetInterest(camera, &interest);
    }
}

}

namespace view1 {
unsigned long strlen(const char *);
char *strstr(const char *, const char *);
char *strchr(const char *, int);
int strcmp(const char *, const char *);
void *memcpy(void *, const void *, unsigned long);

extern "C++" {
char *strstr(const char *, const char *);
extern const char lbl_806D917C[3], lbl_806D9180[5];
extern const char *lbl_804917E0[37];
extern void *lbl_806D165C;
extern int lbl_806CFB7C;
void *Archive_GetCurrent(void *);
const char *HSD_ArchiveGetPublicName(void *, int);
void HSD_JObjClearFlagsAll(HSD_JObj *, unsigned int);
void HSD_JObjSetFlagsAll(HSD_JObj *, unsigned int);
void *fn_80180670(const char *, int);
void *fn_801816AC(const char *);
void fn_801804CC(void *, const char *);
void fn_80180458(void *);
void fn_801805AC(void *, int (*)(int,int,unsigned int,int,unsigned int));
void fn_801814C8();
void fn_8017E824(const char *);
void fn_8017DF00();
void OverlayText(int,int,int,const char *,...);
void fn_8017FF10(int,int,const char *,...);
void TransparentDraw_SortAndDispatch();
void CObj_DebugVizPathFlush(MapDebugCamera *);
void clNormal3D_Exec(clNormal3D *);
void Object_RenderJObjTree(clNormal3D *,int);
void GXDrawDone();
void Object_DtorWithGXSync(clNormal3D *,int);
void TransparentDraw_RemoveByOwner(int);
void SceneDrawList_Reset();
void SetCourseScene3D(int);
void fn_80181998(Vec3f *,Vec3f *,Vec3f *,Vec3f *,int,int,int,int,int);
void fn_80181B7C(Vec3f *,Vec3f *,int,int,int,int,int);
void fn_80181D28(Vec3f *,int,int,int,int,int);
}

extern "C++" int fn_8017D660(int,int,unsigned int,int,unsigned int);

static inline void MapDebugListFiles(const char *base) {
                void *menu = lbl_806D165C;
                if (menu == 0) {
                    menu = fn_801816AC(base + 0x7D0);
                    if (menu == 0) return;
                    fn_801805AC(menu, fn_8017D660);
                }
                fn_80180458(menu);
                DVDDir dir;
                DVDDirEntry entry;
                if (DVDOpenDir(lbl_806D917C, &dir) != 1) return;
                while (DVDReadDir(&dir, &entry)) {
                    if (entry.isDir == 0) {
                        int filter = lbl_806D1630;
            if (filter != 0) {
                if (filter <= 26) {
                    char upper = filter + 0x40;
                    char lower = filter + 0x60;
                    if (entry.name[0] != upper && entry.name[0] != lower) continue;
                } else if (filter <= 36) {
                    char digit = filter + 0x15;
                    if (entry.name[0] != digit) continue;
                }
            }
                        if (strstr(entry.name, lbl_806D9180)) fn_801804CC(menu, entry.name);
                    }
                }
                DVDCloseDir(&dir);
}

static inline unsigned char MapDebugFindFile(char *dst, unsigned int index) {
    DVDDir dir;
    DVDDirEntry entry;
    if (dst == 0) return 0;
    unsigned int count = 0;
    if (DVDOpenDir(lbl_806D917C, &dir) != 1) return 0;
    while (DVDReadDir(&dir, &entry)) {
        if (entry.isDir == 0) {
            int filter = lbl_806D1630;
            if (filter != 0) {
                if (filter <= 26) {
                    char upper = filter + 0x40;
                    char lower = filter + 0x60;
                    if (entry.name[0] != upper && entry.name[0] != lower) continue;
                } else if (filter <= 36) {
                    char digit = filter + 0x15;
                    if (entry.name[0] != digit) continue;
                }
            }
            if (strstr(entry.name, lbl_806D9180)) {
                if (count == index) {
                    strcpy(dst, entry.name);
                    DVDCloseDir(&dir);
                    return 1;
                }
                count++;
            }
        }
    }
    DVDCloseDir(&dir);
    return 0;
}

static inline void MapDebugDrawPath() {
                clPathNode *node = lbl_806D163C;
                while (node) {
                    if (node == lbl_806D1640) {
                        fn_80181998(&node->points[0],&node->points[1],&node->points[2],&node->points[3],255,255,255,63,1);
                        fn_80181B7C(&node->points[0],&node->points[1],255,255,255,127,1);
                        fn_80181B7C(&node->points[1],&node->points[2],255,255,255,127,1);
                        fn_80181B7C(&node->points[2],&node->points[3],255,255,255,127,1);
                        fn_80181B7C(&node->points[3],&node->points[0],255,255,255,127,1);
                        fn_80181D28(&node->points[node->index],255,0,0,255,1);
                    } else fn_80181998(&node->points[0],&node->points[1],&node->points[2],&node->points[3],255,255,255,63,1);
                    node = node->next;
                }
}

extern "C++" int fn_8017D660(int event, int unused, unsigned int item, int unused2, unsigned int selection) {
    const char *base = lbl_80376220;
    switch (event) {
    case 0:
        switch (selection) {
        case 9:
            if (lbl_806CFB85) {
                char filename[0x100];
                if (MapDebugFindFile(filename, item)) fn_8017E824(filename);
            }
            break;
        case 11: fn_801814C8(); break;
        case 3:
            if (lbl_806D1620 && *(void **)((char *)lbl_806D1620 + 0x24)) {
                void *archive = Archive_GetCurrent(*(void **)((char *)lbl_806D1620 + 0x24));
                void *menu = fn_80180670(base + 0x798, 0);
                if (menu) {
                    lbl_806D162C = 1;
                    for (int i = 0; ; i++) {
                        if (i == 0) fn_801804CC(menu, base + 0x7A8);
                        else {
                            const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                            if (name == 0) break;
                            if (strcmp(name, base + 0x7B4) != 0) fn_801804CC(menu, name);
                        }
                    }
                }
            }
            break;
        case 4: {
            void *menu = fn_80180670(base + 0x7C0, 0);
            if (menu) {
                lbl_806D162C = 2;
                for (int i = 0; i < 37; i++) fn_801804CC(menu, lbl_804917E0[i]);
            }
            break;
        }
        }
        return 0;
    case 1:
        switch (lbl_806D162C) {
        case 1:
            if (lbl_806D1620 && *(void **)((char *)lbl_806D1620 + 0x24)) {
                void *archive = Archive_GetCurrent(*(void **)((char *)lbl_806D1620 + 0x24));
                if (selection == 0) {
                    for (int i = 1; ; i++) {
                        const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                        if (name == 0) break;
                        if (strcmp(name, base + 0x7B4) != 0)
                            HSD_JObjClearFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                    }
                } else {
                    for (int i = 1; ; i++) {
                        const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                        if (name == 0) break;
                        if (strcmp(name, base + 0x7B4) != 0) {
                            if ((unsigned int)i == selection)
                                HSD_JObjClearFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                            else HSD_JObjSetFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                        }
                    }
                }
            }
            break;
        case 2:
            if (selection < 37) {
                lbl_806D1630 = selection;
                MapDebugListFiles(base);
            }
            break;
        }
        lbl_806D162C = 0;
        return 0;
    case 3: fn_8017DF00(); return 0;
    case 4:
        OverlayText(1,0,25,base + 0x7DC);
        switch (lbl_806D1628) {
        case 0:
            fn_8017FF10(0,26,base + 0x7F4);
            fn_8017FF10(0,27,base + 0x814);
            fn_8017FF10(0,28,base + 0x838);
            fn_8017FF10(0,29,base + 0x850);
            break;
        case 1:
            fn_8017FF10(0,0,base + 0x86C,lbl_80677D00.x,lbl_80677D00.z);
            fn_8017FF10(0,26,base + 0x87C);
            fn_8017FF10(0,27,base + 0x8A0);
            fn_8017FF10(0,28,base + 0x8B0);
            break;
        case 2:
            fn_8017FF10(0,0,base + 0x86C,lbl_80677D00.x,lbl_80677D00.z);
            break;
        }
        if (lbl_806D1618 && lbl_806D1620 && lbl_806D1618->Begin() == 1) {
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(lbl_806D1618);
            if (lbl_806CFB84) clNormal3D_Exec(lbl_806D1620);
            Object_RenderJObjTree(lbl_806D1620, 7);
            if (lbl_806D1628 == 2) {
                MapDebugDrawPath();
            }
            lbl_806D1618->End();
        }
        return 0;
    case 2:
        GXDrawDone();
        while (lbl_806D1640) MapDebugRemoveNode(lbl_806D1640);
        if (lbl_806D1620) {
            Object_DtorWithGXSync(lbl_806D1620,1);
            lbl_806D1620 = 0;
        }
        if (lbl_806CFB7C >= 0) {
            TransparentDraw_RemoveByOwner(lbl_806CFB7C);
            lbl_806CFB7C = -1;
        }
        SceneDrawList_Reset();
        if (lbl_806D1618) {
            delete lbl_806D1618;
            lbl_806D1618 = 0;
        }
        SetCourseScene3D(0);
        if (lbl_806CFB85 == 0) {
            if (lbl_806CFBA1 != 1) lbl_806CFBA1 = 1;
            lbl_806CFB85 = 1;
        }
        return 0;
    }
    return 0;
}

}

namespace view0 {

extern "C++" {
extern VObject *lbl_806D15FC;
extern unsigned char lbl_806CFBA1;
extern int g_characterId;
extern char g_playerData[0x1DC];
extern int lbl_806D1644, lbl_806D1648;
extern int g_cupId, g_longRoundFlag, g_courseVariantIdx;
extern const char lbl_80376220[];
extern float lbl_806D9080;
void ItemUse_ResetAllKartUseSlots();
int RankSlot_AppendOrUpdate(unsigned char,int,int,void *,unsigned char,unsigned char,int,unsigned char,float,float,int);
VObject *fn_8014CEAC();
VObject *fn_8015B6D0();
VObject *fn_8014F6A4();
VObject *fn_80160238();
VObject *fn_80162C3C();
VObject *fn_8015BE44();
VObject *fn_8015CB5C(int);
VObject *fn_80163804(int,int);
VObject *fn_80165C04(int,int);
void fn_80202C34(int);
void fn_80202B48(int);
void *fn_80180670(const char *,int);
void fn_801804CC(void *,const char *);
void fn_801814C8();
void OperationClock_Commit();
void RaceFlow_ResetState_FullColdInit();
void SetReverseRoundFlag(int);
extern const char lbl_806D9000[7];
extern const char lbl_806D9008[7];
extern const char lbl_806D9010[7];
extern const char lbl_806D9018[7];
extern const char lbl_806D9020[7];
extern const char lbl_806D9028[7];
extern const char lbl_806D9030[7];
extern const char lbl_806D9038[7];
extern const char lbl_806D9040[7];
extern const char lbl_806D9048[7];
extern const char lbl_806D9050[7];
extern const char lbl_806D9058[7];
extern const char lbl_806D9060[7];
extern const char lbl_806D9068[7];
extern const char lbl_806D9070[7];
extern const char lbl_806D9078[7];
extern const char lbl_806D9084[6];
extern const char lbl_806D908C[6];
extern const char lbl_806D9094[6];
extern const char lbl_806D909C[6];
extern const char lbl_806D90A4[6];
extern const char lbl_806D90AC[6];
extern const char lbl_806D90B4[3];
extern const char lbl_806D90B8[3];
extern const char lbl_806D90BC[3];
extern const char lbl_806D90C0[3];
extern const char lbl_806D90C4[3];
extern const char lbl_806D90C8[3];
extern const char lbl_806D90CC[5];
extern const char lbl_806D90D4[5];
extern const char lbl_806D90DC[5];
extern const char lbl_806D90E4[8];
extern const char lbl_806D90EC[6];
extern const char lbl_806D90F4[5];
extern const char lbl_806D90FC[8];
extern const char lbl_806D9104[8];
extern const char lbl_806D910C[6];
extern const char lbl_806D9114[8];
extern const char lbl_806D911C[5];
extern const char lbl_806D9124[7];
extern const char lbl_806D912C[7];
extern const char lbl_806D9134[7];
extern const char lbl_806D913C[7];
extern const char lbl_806D9144[7];
extern const char lbl_806D914C[7];
extern const char lbl_806D9154[8];
extern const char lbl_806D915C[8];
extern const char lbl_806D9164[7];
extern const char lbl_806D916C[8];
extern const char lbl_806D9174[7];
extern const char lbl_806D917C[2];
extern const char lbl_806D9180[5];
extern const char lbl_806D9194[5];
extern const char lbl_806D919C[6];
extern const char lbl_806D91A4[4];
extern const char lbl_806D91C0[5];
extern const char lbl_806D91C8[2];
extern const char lbl_806D91CC[8];
extern const char lbl_806D91D4[2];
extern const char lbl_806D91D8[8];
extern const char lbl_806D91E0[6];
extern const char lbl_806D91E8[6];
extern const char lbl_806D91F0[6];
extern const char lbl_806D91F8[6];
}

static inline void ClearScene() {
    if (lbl_806D15FC) {
        delete lbl_806D15FC;
        lbl_806D15FC = 0;
    }
    if (lbl_806CFBA1 != 1) lbl_806CFBA1 = 1;
}
static inline void SetScene(VObject *scene) {
    lbl_806D15FC = scene;
    if (lbl_806CFBA1 != 0) lbl_806CFBA1 = 0;
}

static inline void SelectCharacterMenu(const char *base) {
    void *menu = fn_80180670(base + 0x6C8, 1);
    if (menu) {
        fn_801804CC(menu, lbl_806D9124);
        fn_801804CC(menu, lbl_806D912C);
        fn_801804CC(menu, lbl_806D9134);
        fn_801804CC(menu, lbl_806D913C);
        fn_801804CC(menu, lbl_806D9144);
        fn_801804CC(menu, lbl_806D914C);
        lbl_806D1644 = 1;
    }
}

static inline int SelectSubmenu(int item, int selection, const char *base) {
    int mode;
    switch (item) {
    case 3: SetScene(fn_8015CB5C(selection)); return 0;
    case 4:
        switch (lbl_806D1644) {
        case 0: {
            lbl_806D1648 = selection;
            void *menu = fn_80180670(base + 0x688, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90DC);
                fn_801804CC(menu, lbl_806D90E4);
                lbl_806D1644 = 1;
            }
            break;
        }
        case 1: {
            mode = selection == 1 ? 1 : 0;
            OperationClock_Commit();
            RaceFlow_ResetState_FullColdInit();
            SetScene(fn_80163804(lbl_806D1648, mode));
            break;
        }
        }
        return 0;
    case 9:
    case 10:
        switch (lbl_806D1644) {
        case 0: {
            g_cupId = selection + 1;
            void *menu = fn_80180670(base + 0x5D8, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90EC);
                fn_801804CC(menu, lbl_806D90F4);
                lbl_806D1644 = 1;
            }
            break;
        }
        case 1: {
            g_longRoundFlag = selection;
            void *menu = fn_80180670(base + 0x694, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90FC);
                fn_801804CC(menu, lbl_806D9104);
                fn_801804CC(menu, lbl_806D910C);
                fn_801804CC(menu, base + 0x6A4);
                lbl_806D1644 = 2;
            }
            break;
        }
        case 2: {
            g_courseVariantIdx = selection;
            void *menu = fn_80180670(base + 0x6B0, 1);
            if (menu) {
                fn_801804CC(menu, base + 0x6BC);
                fn_801804CC(menu, lbl_806D9114);
                lbl_806D1644 = 3;
            }
            break;
        }
        case 3: SetReverseRoundFlag(selection); break;
        }
        return 0;
    case 11:
        switch (lbl_806D1644) {
        case 0:
            lbl_806D1648 = selection;
            switch (selection) {
            case 2: {
                void *menu = fn_80180670(base + 0x6C8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D911C);
                    fn_801804CC(menu, base + 0x6D8);
                    fn_801804CC(menu, base + 0x6E8);
                    fn_801804CC(menu, base + 0x6F8);
                    fn_801804CC(menu, base + 0x708);
                    fn_801804CC(menu, base + 0x718);
                    fn_801804CC(menu, base + 0x728);
                    lbl_806D1644 = 1;
                }
                break;
            }
            case 7: {
                SelectCharacterMenu(base);
                break;
            }
            default: SetScene(fn_80165C04(selection, selection)); break;
            }
            break;
        case 1:
            switch (lbl_806D1648) {
            case 2:
            case 7: SetScene(fn_80165C04(lbl_806D1648, selection)); break;
            }
            break;
        }
        return 0;
    }
    return 0;
}

extern "C++" int fn_8017CE1C(int event, int unused, int item, int unused2, int selection) {
    const char *base = lbl_80376220;
    switch (event) {
    case 0:
        switch (selection) {
        case 1: {
            ClearScene();
            int character = g_characterId;
            switch (item) {
            case 0:
                ItemUse_ResetAllKartUseSlots();
                for (int i = 0; i < 6; i++) {
                    if (i == 0) RankSlot_AppendOrUpdate(1,0,character,0,0,0,-1,1,0.0f,0.0f,-1);
                    else RankSlot_AppendOrUpdate(0,6,character,0,0,0,-1,1,0.0f,0.0f,-1);
                }
                SetScene(fn_8014CEAC());
                return 0;
            case 1:
                g_playerData[0x1B8] = character;
                SetScene(fn_8015B6D0()); return 0;
            case 2: SetScene(fn_8014F6A4()); return 0;
            case 3: {
                void *menu = fn_80180670(base + 0x5C8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D9084);
                    fn_801804CC(menu, lbl_806D908C);
                    fn_801804CC(menu, lbl_806D9094);
                    fn_801804CC(menu, lbl_806D909C);
                    fn_801804CC(menu, lbl_806D90A4);
                    fn_801804CC(menu, lbl_806D90AC);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 4: {
                void *menu = fn_80180670(base + 0x5D8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D9084);
                    fn_801804CC(menu, lbl_806D908C);
                    fn_801804CC(menu, lbl_806D9094);
                    fn_801804CC(menu, lbl_806D909C);
                    fn_801804CC(menu, lbl_806D90A4);
                    fn_801804CC(menu, lbl_806D90AC);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 5: SetScene(fn_80160238()); return 0;
            case 6: SetScene(fn_80162C3C()); return 0;
            case 7: SetScene(fn_8015BE44()); return 0;
            case 8:
                fn_80202C34(0); fn_80202B48(0);
                if (lbl_806CFBA1 != 0) lbl_806CFBA1 = 0;
                return 0;
            case 9:
            case 10: {
                void *menu = fn_80180670(base + 0x5E4, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D90B4);
                    fn_801804CC(menu, lbl_806D90B8);
                    fn_801804CC(menu, lbl_806D90BC);
                    fn_801804CC(menu, lbl_806D90C0);
                    fn_801804CC(menu, lbl_806D90C4);
                    fn_801804CC(menu, lbl_806D90C8);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 11: {
                void *menu = fn_80180670(base + 0x5F4, 1);
                if (menu) {
                    fn_801804CC(menu, base + 0x604);
                    fn_801804CC(menu, base + 0x610);
                    fn_801804CC(menu, base + 0x61C);
                    fn_801804CC(menu, base + 0x630);
                    fn_801804CC(menu, base + 0x63C);
                    fn_801804CC(menu, base + 0x648);
                    fn_801804CC(menu, lbl_806D90CC);
                    fn_801804CC(menu, base + 0x654);
                    fn_801804CC(menu, base + 0x664);
                    fn_801804CC(menu, base + 0x670);
                    fn_801804CC(menu, base + 0x67C);
                    fn_801804CC(menu, lbl_806D90D4);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            }
            return 0;
        }
        case 11: fn_801814C8(); break;
        }
        return 0;
    case 1: return SelectSubmenu(item, selection, base);
    case 3: return 0;
    case 4: return 0;
    case 2: ClearScene(); return 0;
    }
    return 0;
}

}


extern "C" void OSReport(const char *, ...);
// fakematch: uncalled diagnostic member preserves the original pooled labels,
// as clLineManager::PrintLines; its code and exception entry are dead-stripped.
void clMiyazaki::PrintPool(const char *format) {
    OSReport(format, "Ending Select");
    OSReport(format, "Type Select");
    OSReport(format, "Stage Select");
    OSReport(format, "Parts Select");
    OSReport(format, "Result GP");
    OSReport(format, "Result TA");
    OSReport(format, "Result Challenge");
    OSReport(format, "SpriteTest");
    OSReport(format, "TitleTest");
    OSReport(format, "GetItemTest");
    OSReport(format, "NextChallenge");
    OSReport(format, "YNWindow");
    OSReport(format, "MsgWindow");
    OSReport(format, "TARanking");
    OSReport(format, "ModeSelect");
    OSReport(format, "TimeZone Select");
    OSReport(format, "MIDNIGHT");
    OSReport(format, "Dir Select");
    OSReport(format, "Straight");
    OSReport(format, "Select State");
    OSReport(format, "Success Cups:1");
    OSReport(format, "Success Cups:2");
    OSReport(format, "Success Cups:3");
    OSReport(format, "Success Cups:4");
    OSReport(format, "Success Cups:5");
    OSReport(format, "Success Cups:6");
    OSReport(format, "Accolade");
    OSReport(format, "CardBrowse");
    OSReport(format, "PlayDemo");
    OSReport(format, "GetTitle");
    OSReport(format, "NextRace");
    OSReport(format, "CourceAdj");
    OSReport(format, "BattleWait");
    OSReport(format, "PartsTest");
    OSReport(format, "Symbol Select");
    OSReport(format, "AllSymbol");
    OSReport(format, "scene_data");
    OSReport(format, "Filter Select");
    OSReport(format, "ModelViewer");
    OSReport(format, " START  : Switch Mode");
    OSReport(format, "  X     : Draw Symbol Select");
    OSReport(format, "  Y     : FileList Filter Select");
    OSReport(format, "  R     : Load Model ");
    OSReport(format, "  B     : Exit ModelViewer");
    OSReport(format, "  %4.4f %4.4f");
    OSReport(format, "  Y     : Animetion Enable/Disable");
    OSReport(format, "  AX/Y  : Move");
    OSReport(format, "  L/R   : Zoom");
    OSReport(format, "//=================================================\n");
    OSReport(format, "static const stAreaData Area[] = {\n");
    OSReport(format, "    { %ff, %ff, %ff },\n");
    OSReport(format, "    AREA_FLAG_EXACT, 0.0f, 0.0f\n");
    OSReport(format, "%s SymbolList\n");
    OSReport(format, "Accel  : Play");
    OSReport(format, "Stream player");
    OSReport(format, "+--------------------+");
    OSReport(format, "|                    |");
    OSReport(format, " Volume:%d");
    OSReport(format, " Pitch :%d");
    OSReport(format, "Handle : Change Parameter");
    OSReport(format, "Voice player : MARIO");
    OSReport(format, "Voice player : LUIGI");
    OSReport(format, "Voice player : WARIO");
    OSReport(format, "Voice player : PEACH");
    OSReport(format, "Voice player : KOOPA");
    OSReport(format, "Voice player : KINOPIO");
    OSReport(format, "Voice player : DONKEY");
    OSReport(format, "Voice player : YOSHI");
    OSReport(format, "Voice player : PACMAN");
    OSReport(format, "Voice player : MSPACMAN");
    OSReport(format, "Voice player : MONSTER");
    OSReport(format, "Voice player : WALUIGI");
    OSReport(format, "Voice player : MAMETCH");
    OSReport(format, "LAUGHING");
    OSReport(format, "FX player : %s");
    OSReport(format, "Chara Select");
    OSReport(format, "MSPACMAN");
    OSReport(format, "Camera Type");
    OSReport(format, "Main Menu");
    OSReport(format, "SoundTest:FX");
    OSReport(format, "SoundTest:Voice");
    OSReport(format, "SoundTest:Stream");
    OSReport(format, "ConsoleTest");
    OSReport(format, "teSingleton<clMenuInput>");
    OSReport(format, "clMenuInput");
    OSReport(format, "clSceneInterface");
}

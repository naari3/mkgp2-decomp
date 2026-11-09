#include "game/miyazakiconsole/miyazakiconsole.h"
#include "game/miyazakiconsole/console_directory_private.h"
extern "C" {
int DVDOpenDir(const char *, DVDDir *);
int DVDReadDir(DVDDir *, DVDDirEntry *);
int DVDCloseDir(DVDDir *);
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
extern "C" int fn_8017F538(unsigned int msg,void *,int cursor,int,unsigned int sub) {
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

#ifndef CONSOLE_SOUND_PRIVATE_H
#define CONSOLE_SOUND_PRIVATE_H
#include "game/miyazakiconsole/miyazakiconsole.h"
extern "C" {
extern const char lbl_80376220[];
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
static inline int MenuBottom(Menu *m) {
    if (m==0) return 0;
    if (m->count<9) return m->count+3;
    return 12;
}
static inline void SoundMenuDraw(const char *s) {
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+2,s+0x988);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+3,s+0x9a0);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+4,s+0x9a0);
    fn_8017FF10(lbl_806D166C+15,lbl_806D1670+5,s+0x988);
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+3,s+0x9b8,lbl_806CFB78);
    fn_8017FF10(lbl_806D166C+16,lbl_806D1670+4,s+0x9c4,lbl_806CFB7A);
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
        fn_8017FF10(x,y+bottom,s+0x968);
    }
    {
        Menu *m=lbl_806D165C;
        int x=lbl_806D166C;
        int y=lbl_806D1670;
        int bottom=MenuBottom(m);
        fn_8017FF10(x,y+(bottom+1),s+0x9d0);
    }
}
#endif

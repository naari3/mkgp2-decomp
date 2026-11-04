#include "game/miyazakiconsole/console_sound_private.h"

extern "C" int fn_8017F1E8(int msg, void *, int arg, int, unsigned int sub) {
    const char *s=lbl_80376220;
    arg += ((const unsigned int *)(s+0x4c8))[lbl_806D1608*2];
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
        SoundMenuDraw(s);
        return 0;
    case 2:
        fn_801920D4();
        lbl_806CFB70=-1;
        return 0;
    }
    return 0;
}

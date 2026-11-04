#include "game/miyazakiconsole/miyazakiconsole.h"
#include "game/miyazakiconsole/console_ids_private.h"
extern "C" {
extern const char lbl_80376220[];
extern const char *lbl_8049178C[21];
extern int lbl_806D1610;
extern unsigned char lbl_806CFB78, lbl_806D160C;
extern unsigned short lbl_806CFB7A;
int sprintf(char *, const char *, ...);
Menu *fn_801816AC(const char *);
void fn_801805AC(Menu *, void *);
void fn_801804CC(Menu *, const char *);
void fn_8017EC90();
unsigned int fn_801915DC(unsigned int);
}
extern "C" void fn_8017EFFC(unsigned int kind) {
    char title[64];
    const char *strings = lbl_80376220;
    lbl_806D1610 = kind;
    switch(kind) {
    case 0: sprintf(title, strings+0x9ec); break;
    case 1: sprintf(title, strings+0xa04); break;
    case 2: sprintf(title, strings+0xa1c); break;
    case 3: sprintf(title, strings+0xa34); break;
    case 4: sprintf(title, strings+0xa4c); break;
    case 5: sprintf(title, strings+0xa64); break;
    case 6: sprintf(title, strings+0xa7c); break;
    case 7: sprintf(title, strings+0xa94); break;
    case 8: sprintf(title, strings+0xaac); break;
    case 9: sprintf(title, strings+0xac4); break;
    case 10: sprintf(title, strings+0xadc); break;
    case 11: sprintf(title, strings+0xaf4); break;
    case 12: sprintf(title, strings+0xb0c); break;
    }
    Menu *menu = fn_801816AC(title);
    fn_801805AC(menu, (void *)fn_8017EC90);
    for (unsigned int i=0; i<21; i++) fn_801804CC(menu, lbl_8049178C[i]);
    if (lbl_806D1610==4) fn_801804CC(menu, strings+0xb24);
    lbl_806CFB78 = (fn_801915DC(((const Table *)(strings+0x57c))->At(lbl_806D1610)) >> 1) & 0x7f;
    lbl_806CFB7A = 0x2000;
    lbl_806D160C = 0;
}

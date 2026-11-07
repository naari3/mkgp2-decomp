#include "game/HudFlow24CtorPrivate.h"
extern "C" {
extern const float lbl_806DBF18,lbl_806DBF1C,lbl_806DBF24;
extern char g_playerData[0x1dc];
extern int g_characterId,g_gameMode;
unsigned char Sci2Card_GetByteFlag1224();
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
int fn_801F8E58();
void fn_801F9014(TextManager *,const char *,...);
void fn_801F93D0(TextManager *,float,float);
void TexMgr_Apply(TextManager *);
}
extern "C" {
extern char lbl_806DBEE0[];
extern char lbl_803EF668[];
extern char lbl_806DBEE8[];
extern char lbl_806DBEF0[];
extern char lbl_806DBEF8[];
extern char lbl_803EF674[];
extern char lbl_803EF680[];
extern char lbl_803EF68C[];
extern char lbl_803EF698[];
extern char lbl_803EF6A4[];
extern char lbl_803EF6B0[];
extern char lbl_803EF6BC[];
extern char lbl_803EF6C8[];
extern char lbl_803EF6D4[];
extern char lbl_803EF6E0[];
extern char lbl_803EF6EC[];
extern char lbl_803EF6F8[];
extern char lbl_803EF704[];
extern char lbl_803EF710[];
extern char lbl_806DBF00[];
extern char lbl_803EF71C[];
extern char lbl_806DBF08[];
extern char lbl_803EF728[];
extern char lbl_806DBF10[];
extern char lbl_803EF734[];
extern char lbl_803EF740[];
extern char lbl_806D0840[],lbl_806D0848[];
void fn_80245B10(); void fn_80245850(); void fn_8024584C(); void fn_80245834();
}
static const char *internationalLabels[13] = {lbl_806DBEE0,lbl_803EF668,lbl_806DBEE8,lbl_806DBEF0,lbl_806DBEF8,lbl_803EF674,lbl_803EF680,lbl_803EF68C,lbl_803EF698,lbl_803EF6A4,lbl_803EF6B0,lbl_803EF6BC,lbl_803EF6C8};
static const char *japaneseLabels[13] = {lbl_803EF6D4,lbl_803EF6E0,lbl_803EF6EC,lbl_803EF6F8,lbl_803EF704,lbl_803EF710,lbl_806DBF00,lbl_803EF71C,lbl_806DBF08,lbl_803EF728,lbl_806DBF10,lbl_803EF734,lbl_803EF740};
static void *hudTypeInfo[3] = {lbl_806D0840,0,0};
static void *hudVtable[6] = {lbl_806D0848,0,(void*)fn_80245B10,(void*)fn_80245850,(void*)fn_8024584C,(void*)fn_80245834};
static inline int SetHudVtable(HudFlow24 *self, int a) {
    self->vtable = hudVtable;
    return a;
}
HudFlow24::HudFlow24(int a) : arg(SetHudVtable(this,a)),sprite(-1),state(1),
    x(new FlowFaderF(lbl_806DBF18)),y(new FlowFaderF(lbl_806DBF18)) {
    text = new TextManager;
    handle = fn_801F8E58();
    x.p->Set(lbl_806DBF24,lbl_806DBF18,7);
    y.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
    if (Sci2Card_GetByteFlag1224() == 1) {
        fn_801F9014(text,g_playerData);
    } else {
        int character = g_characterId;
        const char *s = isJapanese() == 0 ? internationalLabels[character] : japaneseLabels[character];
        TexMgr_SetTexture(text,s);
    }
    if (ServiceEnable_Get() && !ServiceValue_Get() && Sci2Card_GetByteFlag1224())
        state = 0;
    if (g_gameMode == 2) {
        state += 2;
        fn_801F8FCC(text,0);
    } else fn_801F8FCC(text,1);
    text->visible=0;
    fn_801F93D0(text,lbl_806DBF1C,lbl_806DBF1C);
    fn_801F8E90(text);
    TexMgr_Apply(text);
}

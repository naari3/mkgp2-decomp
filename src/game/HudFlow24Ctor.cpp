#include "game/HudFlow24Private.h"
extern "C" {
extern const float lbl_806DBF18,lbl_806DBF1C,lbl_806DBF24;
extern char g_playerData[0x1dc];
extern int g_characterId,g_gameMode;
extern const HudFlowLabels lbl_804EE7C8;
unsigned char Sci2Card_GetByteFlag1224();
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
int fn_801F8E58();
void fn_801F9014(TextManager *,const char *,...);
void fn_801F93D0(TextManager *,float,float);
void TexMgr_Apply(TextManager *);
}
HudFlow24::HudFlow24(int a) : arg(a),sprite(-1),state(1),
    x(new FlowFaderF(lbl_806DBF18)),y(new FlowFaderF(lbl_806DBF18)) {
    text = new TextManager;
    handle = fn_801F8E58();
    x.p->Set(lbl_806DBF24,lbl_806DBF18,7);
    y.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
    if (Sci2Card_GetByteFlag1224() == 1) {
        fn_801F9014(text,g_playerData);
    } else {
        int character = g_characterId;
        const char *s;
        if (!isJapanese()) s=lbl_804EE7C8.international[character];
        else s=lbl_804EE7C8.japanese[character];
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

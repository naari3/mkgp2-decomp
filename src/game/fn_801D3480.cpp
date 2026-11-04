/* Sprite animation browser debug overlay. */
#include "game/SpriteBrowser_private.h"
extern "C" {
extern const char clFlowCupBattle[];
extern const char *const lbl_806DA028;
extern const char *const lbl_806DA02C;
extern const float lbl_806DA030, lbl_806DA034, lbl_806DA038, lbl_806DA03C;
void *GetInputManager();
BrowserInput *InputMgr_GetPlayer(void *, int);
void OverlayText(int, int, int, const char *, ...);
int fn_8019FE58(BrowserSprite *);
float fn_8019FEBC(BrowserSprite *);
float fn_8019FED8(BrowserSprite *);
unsigned char fn_8019FF50(BrowserSprite *);
void fn_801A0004(BrowserSprite *);
void fn_8011FA98();
}
extern "C" void fn_801D3480(SpriteBrowser *self) {
    const char *s = clFlowCupBattle;
    const char *states[2];
    states[0] = lbl_806DA028;
    states[1] = lbl_806DA02C;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->left() <= lbl_806DA030) {
        OverlayText(2, 0, 0, s + 0x1C);
        OverlayText(2, 0, 1, s + 0x30, self->animation, fn_8019FE58(self->sprite));
        OverlayText(2, 0, 2, s + 0x40, fn_8019FED8(self->sprite), fn_8019FEBC(self->sprite));
        OverlayText(2, 0, 3, s + 0x58, states[fn_8019FF50(self->sprite)]);
        self->sprite->SetPos(lbl_806DA034, lbl_806DA038);
    } else {
        self->sprite->SetPos(lbl_806DA03C, lbl_806DA03C);
    }
    fn_801A0004(self->sprite);
    fn_8011FA98();
}

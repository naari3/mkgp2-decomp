#include "CardPrintFlowView.h"
inline TextManager::~TextManager() {}
extern "C" {
extern const float lbl_806DBFA0, lbl_806DBFA4, lbl_806DBFA8, lbl_806DBFAC;
extern const float lbl_806DBFB0, lbl_806DBFB4, lbl_806DBFB8, lbl_806DBFBC;
extern const char lbl_806DBFC0[4];
struct PrintErrorCaption { int code; int texture; };
extern PrintErrorCaption lbl_803EFD6C[];
void fn_8011FAFC(ResCtrl *, int);
const char *GetTextureByIdAndLang(int, int);
void *fn_801F8E58();
void fn_801F8A34(void *, TextManager *, int);
void fn_8024B77C(CardPrintFlow *self) {
    int error = self->error - 100;
    if (error < 0) error = 0;
    if (error > 6) error = 0;
    ResCtrl ctrl;
    ctrl.mode = 2;
    ctrl.SetSize(lbl_806DBFA4, lbl_806DBFA8);
    ctrl.Show(lbl_806DBFAC, lbl_806DBFB0, lbl_806DBFA0);
    ctrl.SetColor(255);
    fn_8011FAFC(&ctrl, 6);
    TextManager text;
    fn_801F8FCC(&text, 1);
    text.visible = 1;
    text.scale = lbl_806DBFB4;
    text.color = ~0U;
    fn_801F93EC(&text, lbl_806DBFAC, lbl_806DBFB0);
    TexMgr_SetTexture(&text, GetTextureByIdAndLang(153, -1));
    fn_801F8E90(&text);
    fn_801F8A34(fn_801F8E58(), &text, 7);
    fn_801F93EC(&text, lbl_806DBFAC, lbl_806DBFB8);
    TexMgr_SetTexture(&text, GetTextureByIdAndLang(lbl_803EFD6C[error].texture, -1));
    fn_801F8E90(&text);
    fn_801F8A34(fn_801F8E58(), &text, 7);
    fn_801F93EC(&text, lbl_806DBFAC, lbl_806DBFBC);
    TexMgr_SetTexture(&text, lbl_806DBFC0, lbl_803EFD6C[error].code);
    fn_801F8E90(&text);
    fn_801F8A34(fn_801F8E58(), &text, 7);
}
}

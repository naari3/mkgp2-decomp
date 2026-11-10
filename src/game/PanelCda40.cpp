#define PANEL_CDA40_DIRECT_BEGIN
#include "game/PanelCda40Private.h"
#pragma exceptions on
extern "C" void fn_801CDA40(CdaPanelView *p) {
    fn_801D895C(p->payload.object,p->scale);
    fn_801D878C(p->payload.object);
}
extern "C" void fn_801CDA7C(CdaPanelView *p) { p->x=lbl_806D9E20; p->y=lbl_806D9E20; }
CdaSpriteDerived::~CdaSpriteDerived() { vt=lbl_8049B1AC; }
extern "C" void fn_801CDB00(CdaPanelView *p) {
    ResCtrl ctrl;
    ctrl.mode=2;
    ctrl.SetSize(lbl_806D9E7C,lbl_806D9E80);
    ctrl.Show(lbl_806D9E30,lbl_806D9E34,lbl_806D9E24);
    unsigned int color=CdaColor(p->payload.rgb[0],p->payload.rgb[1],p->payload.rgb[2],(unsigned char)(lbl_806D9E78*p->scale));
    ctrl.SetColor(color);
    fn_8011FAFC(&ctrl,p->layer);
}
CdaHolder::~CdaHolder() throw() { delete p; }
CdaList::~CdaList() {}
CdaHolderDerived::~CdaHolderDerived() { vt=GpTextPanel_vtable_8049B18C; }

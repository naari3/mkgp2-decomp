#include "game/HudSelectionPrivate.h"
#include "game/HudFlow24CtorPrivate.h"

/* One TU: HudSelectionUpdate/Create/Destroy + HudFlow24 ctor (0x80245850..0x80245E50), .data 0x804EE7C8..0x804EE870 */
extern "C" void fn_80245850(HudSelection *self);
extern "C" HudSelection *fn_80245B10(HudSelection *self, short flag);
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
extern char HudSelectionUpdate_rodata_803EF668[];
extern char lbl_806DBEE8[];
extern char lbl_806DBEF0[];
extern char lbl_806DBEF8[];
extern char HudSelectionUpdate_rodata_803EF674[];
extern char HudSelectionUpdate_rodata_803EF680[];
extern char HudSelectionUpdate_rodata_803EF68C[];
extern char HudSelectionUpdate_rodata_803EF698[];
extern char HudSelectionUpdate_rodata_803EF6A4[];
extern char HudSelectionUpdate_rodata_803EF6B0[];
extern char HudSelectionUpdate_rodata_803EF6BC[];
extern char HudSelectionUpdate_rodata_803EF6C8[];
extern char HudSelectionUpdate_rodata_803EF6D4[];
extern char HudSelectionUpdate_rodata_803EF6E0[];
extern char HudSelectionUpdate_rodata_803EF6EC[];
extern char HudSelectionUpdate_rodata_803EF6F8[];
extern char HudSelectionUpdate_rodata_803EF704[];
extern char HudSelectionUpdate_rodata_803EF710[];
extern char lbl_806DBF00[];
extern char HudSelectionUpdate_rodata_803EF71C[];
extern char lbl_806DBF08[];
extern char HudSelectionUpdate_rodata_803EF728[];
extern char lbl_806DBF10[];
extern char HudSelectionUpdate_rodata_803EF734[];
extern char HudSelectionUpdate_rodata_803EF740[];
extern char lbl_806D0840[],HudSelectionUpdate_data_806D0848[];
void fn_8024584C(); void fn_80245834();
}
static const char *internationalLabels[13] = {lbl_806DBEE0,HudSelectionUpdate_rodata_803EF668,lbl_806DBEE8,lbl_806DBEF0,lbl_806DBEF8,HudSelectionUpdate_rodata_803EF674,HudSelectionUpdate_rodata_803EF680,HudSelectionUpdate_rodata_803EF68C,HudSelectionUpdate_rodata_803EF698,HudSelectionUpdate_rodata_803EF6A4,HudSelectionUpdate_rodata_803EF6B0,HudSelectionUpdate_rodata_803EF6BC,HudSelectionUpdate_rodata_803EF6C8};
static const char *japaneseLabels[13] = {HudSelectionUpdate_rodata_803EF6D4,HudSelectionUpdate_rodata_803EF6E0,HudSelectionUpdate_rodata_803EF6EC,HudSelectionUpdate_rodata_803EF6F8,HudSelectionUpdate_rodata_803EF704,HudSelectionUpdate_rodata_803EF710,lbl_806DBF00,HudSelectionUpdate_rodata_803EF71C,lbl_806DBF08,HudSelectionUpdate_rodata_803EF728,lbl_806DBF10,HudSelectionUpdate_rodata_803EF734,HudSelectionUpdate_rodata_803EF740};
static void *hudTypeInfo[3] = {lbl_806D0840,0,0};
static void *hudVtable[6] = {HudSelectionUpdate_data_806D0848,0,(void*)fn_80245B10,(void*)fn_80245850,(void*)fn_8024584C,(void*)fn_80245834};

extern "C" void fn_80245850(HudSelection *self) {
 switch(self->state) {
 case -1:
  if(g_countdownPhase<=3) self->state=0;
  return;
 case 0:
  self->position.p->Step();
  if(self->position.p->Done()) { self->state=1; self->position.p->Set(lbl_806DBF18,lbl_806DBF18,1); }
  break;
 case 1:
  if(g_countdownPhase<=2) { self->alpha.p->Set(lbl_806DBF1C,lbl_806DBF20,4); self->state=2; }
  break;
 case 2:
  if(self->alpha.p->Done() && self->alpha.p->Value()==lbl_806DBF1C) self->state=3;
  break;
 case 4:
  self->position.p->Step();
  if(self->position.p->Done()) { self->state=5; return; }
  break;
 case 5:return;
 default:return;
 case 3:break;
 }
 if(self->countdown>0) {
  if(--self->countdown<=0) {
   self->countdown=0; self->state=4;
   self->position.p->Set(lbl_806DBF18,lbl_806DBF24,7);
  }
 }
 float value=self->position.p->Value();
 fn_801F93EC(self->text,HudSelectionUpdate_rodata_803EF75C[self->selection].x-value,HudSelectionUpdate_rodata_803EF75C[self->selection].y);
 float alpha=self->alpha.p->Value();
 fn_801F93D0(self->text,alpha,alpha);
 fn_801F8A34(self->context,self->text,self->field08);
 self->alpha.p->Step();
 if(self->alpha.p->Done()) {
  float v=self->alpha.p->Value();
  if(lbl_806DBF20==v) self->alpha.p->Set(lbl_806DBF20,lbl_806DBF1C,4);
  else if(lbl_806DBF1C==v) self->alpha.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
 }
}


extern "C" HudSelection *fn_80245AC4(int value) { return (HudSelection *)new HudFlow24(value); }

extern "C" HudSelection *fn_80245B10(HudSelection *self, short flag) {
 if (self) {
  self->vptr=hudVtable;
  if(self->text) MemoryManager_TimedFree(self->text);
  fn_801F8E54(); self->context=0;
  self->alpha.~VHolder<FlowFaderF>();
  self->position.~VHolder<FlowFaderF>();
  self->HudSelectionBase::~HudSelectionBase();
  if(flag>0) MemoryManager_TimedFree(self);
 }
 return self;
}

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

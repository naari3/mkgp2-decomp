/* Target-observed layout; live Ghidra types unavailable. Native local lifetime. */
struct PopupResCtrl {
    char pad00[8]; int mode; char pad0C[4]; unsigned char visible;
    char pad11[3]; float x,y,z,width,height; char pad28[12];
    int a,b,c,d; char pad44[0x14];
    PopupResCtrl(); ~PopupResCtrl() {}
};
struct Popup {
    char pad00[0xb4]; signed char state; char padB5[0x9b];
    float alpha; char pad154[0x1c]; void *sprite; char pad174[12]; unsigned int timer;
};
extern "C" {
void fn_80121E10(PopupResCtrl *);
void *SpriteHandle_CreateDefault(PopupResCtrl *,int);
void SpriteHandle_Destroy(void *);
void DrawEffect_Free(void *);
void SpriteHandle_SetCornerAlpha(void *,unsigned char);
void SpriteHandle_RecomputeCull(void *);
extern const float lbl_806D5020,lbl_806D5024,lbl_806D5028,lbl_806D502C,lbl_806D5030,lbl_806D5034,lbl_806D5038,lbl_806D503C;
void VfxSpritePopup_TickType0(Popup *p) {
 switch(p->state) {
 case 0: {
    PopupResCtrl r;
    fn_80121E10(&r);
    r.mode=2; r.visible=1;
    r.x=lbl_806D5020; r.y=lbl_806D5024; r.z=lbl_806D5028;
    r.width=lbl_806D502C; r.height=lbl_806D5030;
    r.a=0; r.b=0; r.c=0; r.d=0;
    p->sprite=SpriteHandle_CreateDefault(&r,0);
    p->alpha=lbl_806D5034; p->timer=22; ++p->state;
    break;
 }
 case 1: break;
 }
 if(p->timer) --p->timer;
 if(p->timer==0) { SpriteHandle_Destroy(p->sprite); DrawEffect_Free(p); }
 else {
    float step, limit, alpha;
    alpha=p->alpha; step=lbl_806D5038; limit=1.0f;
    p->alpha=alpha+step;
    if(limit<p->alpha) p->alpha=limit;
    SpriteHandle_SetCornerAlpha(p->sprite,(unsigned char)(int)(lbl_806D503C*p->alpha));
    SpriteHandle_RecomputeCull(p->sprite);
 }
}
void VfxSpritePopup_TickType1(Popup *p) {
 switch(p->state) {
 case 0: {
    PopupResCtrl r;
    fn_80121E10(&r);
    r.mode=2; r.visible=1;
    r.x=lbl_806D5020; r.y=lbl_806D5024; r.z=lbl_806D5028;
    r.width=lbl_806D502C; r.height=lbl_806D5030;
    r.a=0; r.b=0; r.c=0; r.d=0;
    p->sprite=SpriteHandle_CreateDefault(&r,0);
    p->alpha=lbl_806D5034; p->timer=22; ++p->state;
    break;
 }
 case 1: break;
 }
 if(p->timer) --p->timer;
 if(p->timer==0) { SpriteHandle_Destroy(p->sprite); DrawEffect_Free(p); }
 else {
    float step, limit, alpha;
    alpha=p->alpha; step=lbl_806D5038; limit=1.0f;
    p->alpha=alpha+step;
    if(limit<p->alpha) p->alpha=limit;
    SpriteHandle_SetCornerAlpha(p->sprite,(unsigned char)(int)(lbl_806D503C*p->alpha));
    SpriteHandle_RecomputeCull(p->sprite);
 }
}
}

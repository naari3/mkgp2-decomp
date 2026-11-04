/* Private views for the assigned card-flow methods. */
#ifndef CXC_CARD_FLOW_H
#define CXC_CARD_FLOW_H
struct CardInput {
    virtual void v0(); virtual void v1(); virtual float v2();
    virtual void v3(); virtual float v4(); virtual float v5();
    virtual unsigned char Pressed(int);
};
struct CardFader { int unk0; short duration, time; };
struct CardSeq {
    virtual void v8(); virtual void Tick();
    int count;
};
struct CardMode { int pad[2]; int light; };
struct CardStep {
    char pad0[0xC]; int done; CardSeq *seq; CardFader *fader; int state, result;
};
static inline void CardFadeTick(CardFader *f) {
    f->time++;
    short d = f->duration;
    if (f->time >= d) f->time = d;
}
extern "C" {
extern const int lbl_806DA860;
extern int lbl_806D00C8, lbl_806D00D0, lbl_806D00D8, lbl_806D00E0, lbl_806D00F8, lbl_806D0100;
void *GetInputManager();
CardInput *InputMgr_GetPlayer(void *, int);
CardMode *fn_801DAEC0();
void fn_801FA864(CardStep *);
void fn_801FA6A4(CardStep *);
void fn_80203EA0();
void fn_8020A7CC(CardFader *, int, int, int);
void *fn_801F4DC0(void *, int);
char *fn_80271340(void *, int, void *, void *, int);
void fn_801FEF18(void *, int);
void fn_80202A5C(int);
void fn_802043B8(void *, int);
void fn_801FFFF4(void *);
void fn_80201148(void *);
int fn_80203E30();
}
#endif

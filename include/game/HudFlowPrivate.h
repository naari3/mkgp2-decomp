#ifndef GAME_HUDFLOWPRIVATE_H
#define GAME_HUDFLOWPRIVATE_H
struct HudDeleteView { virtual ~HudDeleteView(); };
struct HudChild { virtual void Destroy(); virtual void Stop(); };
struct HudRoot {
    HudRoot(); ~HudRoot();
    void *vptr; int field4; void *hostVptr; int fieldC;
    int state; HudChild *child;
};
struct HudFlow : HudRoot { HudFlow(); };
struct HudEnterView {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void f6(); virtual void Enter(int);
};
struct HudConfig { unsigned char mode; char pad1[11]; unsigned char flag; char padD[3]; int index; };
struct HudSmall { char opaque[0x18]; HudSmall(); };
extern "C" {
extern void *HudFlow_data_804EEB20[];
extern int g_cupId, g_roundIndex;
extern unsigned char g_raceEnded, lbl_806D17F0;
extern void *lbl_806D1A60;
HudConfig *fn_8024F588();
void fn_8024F43C(HudConfig *);
void fn_8024F530();
unsigned char fn_8019083C(int);
void fn_801909A4(int);
void ClSound_PlayBgmStream(int,int);
int fn_801932F8();
void clStream_setVolume(int,int);
void fn_8021A0D0(void *); void fn_8021A0DC(void *); void fn_8021A0B0(void *); void fn_80219FF4(void *);
void *ItemDisplay_GetOrCreate(); void ItemDisplay_Stop(void *);
HudChild *fn_8014CEAC(); HudChild *fn_80160238(); HudChild *fn_80223500(); HudChild *fn_802253B0(); HudChild *fn_8024CA18(); HudChild *fn_8015CB5C(int);
void fn_801DC870(int); unsigned char has_title_changed();
void MemoryManager_TimedFree(void *);
void dtor_80249274(HudRoot *, int);
}
#endif


#ifndef GAME_SCENE_8016234C_PRIVATE_H
#define GAME_SCENE_8016234C_PRIVATE_H

/* Result-to-credit scene transition, including the credit panel's new guard. */
struct CreditPrefix162 {
    int p0;
    unsigned char done;
    char pad5[0x14 - 5];
};
struct CreditBase162 : CreditPrefix162 {
    CreditBase162(int);
    virtual ~CreditBase162();
    virtual void V0C();
    virtual void V10();
    virtual void Update();
    virtual void Draw();
    char pad18[0x84 - 0x18];
};

extern "C" {
void fn_80147574(void *, int);
int CreditMgr_GetCreditCount(int);
int CreditMgr_GetCoinsPerCredit(int);
void CreditMgr_SetActiveSlot(int);
extern unsigned char lbl_80598A60[0x2a];
}
struct CreditChild162 : CreditBase162 {
    int credits;
    unsigned char noCredits, expired, multiple, changed, confirmed;
    CreditChild162() : CreditBase162(0) {
        fn_80147574(this, 1200);
        credits = CreditMgr_GetCreditCount(1);
        changed = 0;
        int coins = CreditMgr_GetCoinsPerCredit(1);
        if (coins > 1 && coins != credits) changed = 1;
        noCredits = 0;
        expired = 0;
        multiple = lbl_80598A60[0x27];
        confirmed = 0;
        CreditMgr_SetActiveSlot(1);
    }
    virtual ~CreditChild162();
};

struct ItemTransform162 { float x, y, z, scale; };
struct Transition162 {
    int vt;
    unsigned char done;
    char pad5[3];
    CreditBase162 *panel;
    int padC;
    unsigned char active;
    char pad11[3];
    int phase;
    float timer;
    unsigned char service;
    char pad1D[3];
    int a, b, c, d, item;
};

extern "C" {
extern const float lbl_806D8880, lbl_806D8884, lbl_806D8888, lbl_806D888C, lbl_806D8890, lbl_806D8894;
extern const float lbl_806D8898, lbl_806D889C, lbl_806D88A0, lbl_806D88A4;
extern const char lbl_806D88A8[8];
extern const float lbl_806D88B0, lbl_806D88B4, lbl_806D88B8, lbl_806D88BC;
extern const float lbl_806D88C0, lbl_806D88C4, lbl_806D88C8;
int fn_8013BEF4(int, int, int);
const char *fn_8013C100(int, int, int);
const char *fn_8013C204(int, int);
int Item_GetDescriptorField8(int);
int Item_GetDescriptorFieldC(int);
ItemTransform162 *fn_8013BEC8(int);
int Item_GetDescriptorField0(int, int);
int GetTextureByIdAndLang(int, int);
int fn_8023DAA8(int);
#ifdef __MWERKS__
void fn_801695E0(int, int, int, float, float, float);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801695E0(int, int, float, float, float, int);
static inline void fn_801695E0_Reordered(int a0, int a1, int a2, float a3, float a4, float a5) { fn_801695E0(a0, a1, a3, a4, a5, a2); }
#define fn_801695E0 fn_801695E0_Reordered
#endif
#ifdef __MWERKS__
void fn_801698B4(int, int, int, float, float);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801698B4(int, int, float, float, int);
static inline void fn_801698B4_Reordered(int a0, int a1, int a2, float a3, float a4) { fn_801698B4(a0, a1, a3, a4, a2); }
#define fn_801698B4 fn_801698B4_Reordered
#endif
void fn_80168798(int, const char *, float, float, float, ...);
void fn_80168D84(int, int, float, float, float, ...);
void fn_80168B90(int, int, float, float, float, float, float, float, ...);
void fn_801699D8(int, int);
void RumbleUpdate();
}

#endif

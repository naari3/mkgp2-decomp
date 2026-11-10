#ifndef GAME_FLOW_CARD_CHECK_PAGES_PRIVATE_H
#define GAME_FLOW_CARD_CHECK_PAGES_PRIVATE_H
/* Private layouts and declarations shared by the scene-update and page TUs. */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

#include "game/types/Vec2.h"

struct Sprite {
    int id;
    int prio;
    int i8;
    float x, y;
    float sx, sy;
};

struct TextMgr {
    float x, y;
    char pad08[0x10];
    int visible;
    int field1C;
    unsigned int color;
    char pad24[0x22C - 0x24];
    float scale;
    TextMgr();
    ~TextMgr() {}
};

struct PlayerData {
    char pad00[0xE];
    unsigned short stamps;
    unsigned short stamps2;
    char pad12[0xA8-0x12];
    unsigned char unlocked[61];
    char padE5[0x198-0xE5];
    signed char cardCount;
    char pad199[4];
    unsigned char datePage, dateMode;
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual float Stick();
    virtual float v5();
    virtual void v6();
    virtual void v7();
    virtual unsigned int Held(int mask);
};

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0xF];
    int pageInput;
    int cardState;
    int i1C;
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
};

class clIndicator {
public:
    char pad[0x20];
    clIndicator(int a, int b, int c, int d, int e);
    ~clIndicator();
};

extern "C" {
extern PlayerData g_playerData;
extern InputState *g_pInputState;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
int fn_8023D844(int group, int slot);
void fn_8019FF6C(Sprite *s, int flag);
const char *fn_8023DAA8(int item);
const char *fn_8023D938(int item, int kind);
void fn_801699D8(int a, int b);
void SetRumbleMode(int a, int b, int c);
void fn_801FE390(void);
void fn_801FE348(void);
void fn_801FE36C(void);
void SetScreenBrightness(float b);
void fn_801B7EF8(void);
void fn_8023CD54(clIndicator *ind);
void fn_8023CDA8(clIndicator *ind);
void fn_8023CD3C(clIndicator *ind, float x, float y);
void fn_8023CD24(clIndicator *ind, float x, float y);
void fn_8023CCF8(clIndicator *ind, float x, float y);
void fn_8023CCCC(clIndicator *ind, float x, float y);
int PlayerData_ResolveUnlockedIdByIndex(PlayerData *pd, int idx);
int Item_GetDescriptorField0(int item, int a);
int Item_GetDescriptorFieldC(int item);
void fn_80120A08(int id);
void PreloadResource(int id);
void SetSyncTarget(int target);
void InitBGM(void);
void SetupBgSprites(int on);
void fn_801B8918(int id);
void fn_801B8874(int id);
void InitRumbleController(int on);
void fn_801A0004(Sprite *s);
void Sprite_SetAnimTime(Sprite *s, float t);
int Sprite_AdvanceAnim(Sprite *s, float dt);
void *fn_801F8E58(void);
void fn_801F8A34(void *list, TextMgr *tm, int prio);
void fn_801F93EC(TextMgr *tm, float x, float y);
void fn_801F9518(TextMgr *tm);
void fn_801F95A0(TextMgr *tm);
void fn_801F8E90(TextMgr *tm);
void TexMgr_SetTexture(TextMgr *tm, const char *fmt, ...);
const char *GetTextureByIdAndLang(int id, int lang);
int isJapanese(void);
extern unsigned char lbl_806D12E4[4];
unsigned char fn_801D5C88(PlayerData *pd, int cc);
int fn_801D59A0(PlayerData *pd, int cc, int cup);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int h);
void SpriteHandle_SetActiveFlag(int h, int flag);
void fn_8023CCA0(clIndicator *ind, int on);
void fn_8023CC74(clIndicator *ind, int on);
void fn_8011FAB8(void);
void fn_801A1280(void);
void SpriteHandle_RecomputeCull(int h);
void fn_8011F804(int h, float x, float y);
void SpriteGroup_CreateOrInit(Sprite ***slot, const int *ids, int flag, float x, float y);
void SpriteAnimHandle_Destroy(Sprite **h, int flag);
void SpriteAnimParamBlock_SetAnimParamCached(Sprite **h, int oldParam, int newParam);
}


#include "game/FlowCardCheckUnlock_private.h"



extern "C" const Vec2 lbl_806DB780;
extern "C" const float lbl_806DB7A0;
extern "C" const float lbl_806DB7AC;
extern "C" const char lbl_806DB7F8[4];
extern "C" const char lbl_806DB818[5];
extern "C" {
void fn_80121E10(ResCtrl *ctrl);
void SpriteAnimParamBlock_Reload(Sprite **group, int id);
void fn_8023CEB4(clIndicator *ind);
void fn_8023CFD4(clIndicator *ind);
void fn_801F9014(TextMgr *text, const void *data, ...);
void fn_801F93D0(TextMgr *text, float sx, float sy);
int GetCoinMilage(void *pd);
const char *get_title_name_global(void *mgr);
extern void *lbl_806D10A0;
extern const char lbl_806DB824[1];
extern const char lbl_806DB82C[1];
extern const char lbl_806DB850[4];
extern const char lbl_806DB87C[4];
extern const float lbl_806DB828;
extern const float lbl_806DB830;
extern const float lbl_806DB834;
extern const float lbl_806DB838;
extern const float lbl_806DB83C;
extern const float lbl_806DB840;
extern const float lbl_806DB844;
extern const float lbl_806DB848;
extern const float lbl_806DB84C;
extern const float lbl_806DB854;
extern const float lbl_806DB858;
extern const float lbl_806DB85C;
extern const float lbl_806DB860;
extern const float lbl_806DB864;
extern const float lbl_806DB868;
extern const float lbl_806DB86C;
extern const float lbl_806DB870;
extern const float lbl_806DB874;
extern const float lbl_806DB878;
extern const float lbl_806DB880;
extern const float lbl_806DB884;
}

class clFlowCCBattle;
class clFlowCCGP;
class clFlowCCCharaItem;
class clFlowCCItem;
class clFlowCCDate;


class clFlowCCBattle : public clFlowCCInterface {
public:
    int blink;
    float grid[101];
    Sprite **grp[3];
    TextMgr *text[7];

    clFlowCCBattle();
    virtual ~clFlowCCBattle();
    virtual int Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn();
    virtual void OnHidden();
};

class clFlowCCGP : public clFlowCCInterface {
public:
    int cc;
    unsigned char first;
    Sprite **grp[9];
    TextMgr *text[4];
    int handles[2];

    clFlowCCGP(int cc);
    virtual ~clFlowCCGP();
    virtual int Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn();
    virtual void OnHidden();
};

class clFlowCCCharaItem : public clFlowCCInterface {
public:
    int which, field20, field24, field28;
    float slots[2][5];
    unsigned char first;
    Sprite **grp[11];
    TextMgr *text[8];
    int resId, paramId;

    void Select(int delta);
    clFlowCCCharaItem(int which);
    virtual ~clFlowCCCharaItem();
    virtual int Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn();
    virtual void OnHidden();
};

class clFlowCCItem : public clFlowCCInterface {
public:
    int field1C, field20;
    int resId, paramId;
    unsigned char first;
    clIndicator *indicator;
    Sprite **grp[7];
    TextMgr *text[8];
    int handle;
    int handles[60];
    ResCtrl cards[60];

    void PositionSelection();
    void Select(int delta);
    clFlowCCItem();
    virtual ~clFlowCCItem();
    virtual int Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn();
    virtual void SlideOut();
    virtual void OnHidden();
};

class clFlowCCDate : public clFlowCCInterface {
public:
    unsigned char field1C, field1D, field1E;
    int field20;
    clIndicator *indicator;
    Sprite **grp[6];
    TextMgr *text[12];

    clFlowCCDate();
    virtual ~clFlowCCDate();
    virtual int Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn();
    virtual void OnHidden();
};

#include "game/singleton.h"

static inline InputState *input_state() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline PlayerData *GetPlayerData() {
    return &g_playerData;
}


#endif

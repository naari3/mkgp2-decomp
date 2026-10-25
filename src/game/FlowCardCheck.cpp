/*
 * 0x80232884..0x802379F8: clFlowCardCheck, the "card check" scene that pages
 * through the data stored on the player's IC card, and its pages
 * (clFlowCCInterface): battle stamps, GP results, character / item records,
 * item collection and play dates.
 * Owns .rodata 0x803DB6E0..0x803DC0C0, .data 0x804EE3A8..0x804EE520 and
 * .sdata 0x806D0650..0x806D0728.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct Vec2 {
    float x, y;
};

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
    char pad1C[0x22C - 0x1C];
    float scale;
    TextMgr();
    ~TextMgr() {}
};

struct PlayerData {
    char pad00[0xE];
    unsigned short stamps;
    unsigned short stamps2;
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual float Stick();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual unsigned int Held(int mask);
};

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0x13];
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
unsigned char Sprite_AdvanceAnim(Sprite *s, float dt);
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
int fn_801D59A0(PlayerData *pd, int cc);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int h);
void SpriteHandle_RecomputeCull(int h);
void fn_8011F804(int h, float x, float y);
void SpriteGroup_CreateOrInit(Sprite ***slot, const int *ids, int flag, float x, float y);
void SpriteAnimHandle_Destroy(Sprite **h, int flag);
void SpriteAnimParamBlock_SetAnimParamCached(Sprite **h, int oldParam, int newParam);
}

class clFlowProcess {
public:
    clFlowProcess();
    virtual ~clFlowProcess();
    virtual int Update();
    virtual void Draw();
};

class clFlowCCInterface {
public:
    clFlowCCInterface() : dir(0), inTimer(0), outTimer(0), active(0) {
        slide = -1000.0f;
        f8 = 0.0f;
    }
    virtual ~clFlowCCInterface() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Unk14() = 0;
    virtual void SlideIn(int t) {}
    virtual void SlideOut(int t) {}
    virtual void OnShown() {}
    virtual void OnHidden() {}

    float slide;
    float f8;
    int dir;
    int inTimer;
    int outTimer;
    unsigned char active;

    void Open(int t) {
        inTimer = t;
        active = 1;
        dir = 1;
        SlideIn(t);
    }
    void Close(int t) {
        outTimer = t;
        dir = 0;
        SlideOut(t);
    }
    unsigned char IsIdle() {
        unsigned char r = 0;
        if (inTimer == 0 && outTimer == 0) {
            r = 1;
        }
        return r;
    }
    void UpdateSlide() {
        if (IsIdle() != 1) {
            int t = 0;
            if (inTimer > 0) {
                if (--inTimer == 0) {
                    OnShown();
                }
            } else if (outTimer > 0) {
                if (--outTimer == 0) {
                    active = 0;
                    OnHidden();
                }
                t = 18 - outTimer;
            }
            float d = 1000.0f;
            if (dir == 0) {
                d = -1000.0f;
            }
            slide = d * (t / 18.0f);
        }
    }
};

static int kDateGrp0[] = {0x151};
static int kDateGrp1[] = {0x152};
static int kDateGrp2a[] = {0x166};
static int kDateGrp3a[] = {0x163};
static int kDateGrp2b[] = {0x165};
static int kDateGrp3b[] = {0x164};
static int kDateGrp4[] = {0x162};
static int kDateGrp5[] = {0x161};
static int kItemGrp0[] = {0x151};
static int kItemGrp1[] = {0x153};
static int kItemGrp2[] = {0x17};
static int kItemGrp3[] = {0x15};
static int kItemGrp4[] = {0x16};
static int kCharaGrp0[] = {0x151};
static int kCharaGrp1[] = {0x153};
static int kCharaGrp2[] = {0x17};
static int kCharaGrp3[] = {0x15};
static int kCharaGrp4[] = {0x16};
static int kCharaGrp5[] = {0x15F};
static int kCharaGrp6[] = {0x15E};
static int kCharaGrp7[] = {0x15E};
static int kCharaGrp8[] = {0x15E};
static int kCharaGrp9[] = {0x15E};
static int kCharaGrp10[] = {0x15E};
static int kGPGrp0[] = {0x151};
static int kGPGrp1[] = {0x15D};
static int kGPGrp2[] = {0x158};
static int kGPGrp3[] = {0x15C};
static int kGPGrp4[] = {0x156};
static int kGPGrp5[] = {0x155};
static int kGPGrp6[] = {0x159};
static int kGPGrp7[] = {0x157};
static int kGPGrp8a[] = {0x15B};
static int kGPGrp8b[] = {0x15A};
static int kBattleGrp0[] = {0x151};
static int kBattleGrp1[] = {0x154};
static int kBattleGrp2[] = {0x18};

static const Vec2 kJpTitlePos = {430.0f, 100.0f};
static const char *kCCNames[3] = {"50cc", "100cc", "150cc"};

static const unsigned int kPageTables[300] = {0x00000000, 0x00000000, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x000000C8, 0x00000040, 0x00000000, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB};
static const int kCards[5][12] = {{0x00000006, 0x00000002, 0x00000001, 0x00000000, 0x00000007, 0x00000003, 0x0000000B, 0x00000008, 0x0000000A, 0x00000009, 0x0000000D, 0x0000000C}, {0x00000004, 0x00000005, 0x0000002A, 0x0000000F, 0x0000001E, 0x0000000E, 0x00000016, 0x00000017, 0x0000002C, 0x0000001B, 0x0000002B, 0x0000003B}, {0x00000026, 0x00000028, 0x00000027, 0x0000003A, 0x00000025, 0x00000010, 0x00000029, 0x0000002D, 0x00000013, 0x00000019, 0x0000001D, 0x00000014}, {0x00000018, 0x0000001F, 0x00000023, 0x00000022, 0x00000021, 0x00000012, 0x0000001C, 0x00000020, 0x00000015, 0x00000024, 0x0000001A, 0x00000011}, {0x0000002E, 0x00000036, 0x00000030, 0x00000032, 0x00000035, 0x00000039, 0x00000037, 0x00000038, 0x00000031, 0x00000034, 0x0000002F, 0x00000033}};
static const unsigned int kDateTabA[12] = {0x43A00000, 0x437A0000, 0x43A00000, 0x437A0000, 0x43A98000, 0x438F0000, 0x43E20000, 0x438E8000, 0x43A98000, 0x43BD0000, 0x43E20000, 0x43BD0000};
static const unsigned int kDateTabB[109] = {0x43C70000, 0x42C80000, 0x42080000, 0x42C80000, 0x42A40000, 0x43320000, 0x42A40000, 0x43890000, 0x42A40000, 0x43B88000, 0x43930000, 0x43320000, 0x43E38000, 0x42D00000, 0x429C0000, 0x43120000, 0x429C0000, 0x43720000, 0x429C0000, 0x43A88000, 0x43910000, 0x43120000, 0x43E00000, 0x43A78000, 0x43A00000, 0x437A0000, 0x43A00000, 0x437A0000, 0x42080000, 0x43240000, 0x44160000, 0x43240000, 0x42AC0000, 0x431A0000, 0x42AC0000, 0x431A0000, 0x42AC0000, 0x431A0000, 0x43C70000, 0x42C80000, 0x42040000, 0x42C60000, 0x43E38000, 0x42D00000, 0x434B0000, 0x42CE0000, 0x42FA0000, 0x43A40000, 0x43A28000, 0x43A60000, 0x43A28000, 0x43B10000, 0x43A28000, 0x43BC0000, 0x42AC0000, 0x43000000, 0x432A0000, 0x43540000, 0x437E0000, 0x43940000, 0x43A90000, 0x43BE0000, 0x43D30000, 0x43E80000, 0x43FD0000, 0x44090000, 0x431A0000, 0x43390000, 0x43580000, 0x43770000, 0x438B0000, 0x43A00000, 0x437A0000, 0x43A00000, 0x437A0000, 0x432D0000, 0x43120000, 0x43EB8000, 0x43120000, 0x432D0000, 0x43500000, 0x43EB8000, 0x43500000, 0x432D0000, 0x43878000, 0x43EB8000, 0x43878000, 0xC4200000, 0xC3F00000, 0xC4200000, 0xC3F00000, 0xC4200000, 0xC3F00000, 0x43C70000, 0x42C80000, 0x42040000, 0x42C60000, 0x43E38000, 0x42D00000, 0x43940000, 0x42CE0000, 0x42FA0000, 0x43A40000, 0x43A28000, 0x43A60000, 0x43A28000, 0x43B10000, 0x43A28000, 0x43BC0000};
static const unsigned int kCharaTabA[24] = {0x00001D23, 0x00001D24, 0x00001D27, 0x00001ECD, 0x00001D2F, 0x00001ECD, 0x00001D2C, 0x00001ECD, 0x00001D2D, 0x00001ECD, 0x00001D26, 0x00001ECD, 0x00001D2E, 0x00001ECD, 0x00001D28, 0x00001ECD, 0x00001D25, 0x00001D2B, 0x00001D29, 0x00001ECD, 0x00001D2A, 0x00001ECD, 0x00001ECD, 0x00001ECD};
static const unsigned int kCharaTabB[20] = {0x00000000, 0x00000003, 0x00000004, 0x00000005, 0x00000002, 0x0000000B, 0x00000006, 0x00000007, 0x00000008, 0x0000000A, 0x0000000C, 0xFFFFFFFF, 0x43120000, 0x43500000, 0x43878000, 0x000013B9, 0x000013BA, 0x000013BB, 0x000013BC, 0x000013BD};
static const Vec2 kGPGrpPos[9] = {{320.0f, 250.0f}, {176.0f, 160.0f}, {465.0f, 160.0f}, {176.0f, 228.0f}, {465.0f, 228.0f}, {176.0f, 296.0f}, {465.0f, 296.0f}, {176.0f, 364.0f}, {465.0f, 364.0f}};
static const Vec2 kGPTextPos[4] = {{398.0f, 100.0f}, {32.0f, 99.0f}, {230.0f, 99.0f}, {455.0f, 104.0f}};
static const Vec2 kGPHandlePos[2] = {{320.0f, 250.0f}, {40.0f, 102.0f}};
static const int kGPRankParams[4][2] = {{0x15D7, 0x2467}, {0x15D8, 0x2469}, {0x15D9, 0x246B}, {0x15DA, 0x246D}};
static const int kGPCupAnim[8] = {0x15DB, 0x15DD, 0x15DF, 0x15E1, 0x15E3, 0x15E5, 0x15E7, 0x15E9};
static const int kGPCupIds[8] = {7, 1, 8, 2, 3, 4, 5, 6};
static const Vec2 kBattleGrpPos[3] = {{320.0f, 250.0f}, {320.0f, 250.0f}, {-640.0f, -240.0f}};
static const Vec2 kBattleTextPos[7] = {{398.0f, 100.0f}, {33.0f, 99.0f}, {54.0f, 380.0f}, {213.0f, 380.0f}, {366.0f, 380.0f}, {512.0f, 380.0f}, {455.0f, 104.0f}};
class clFlowCCBattle;
class clFlowCCGP;
class clFlowCCCharaItem;
class clFlowCCItem;
class clFlowCCDate;

class clFlowCardCheck : public clFlowProcess {
public:
    unsigned char stickLatch;
    int page;
    int prevPage;
    int timer;
    int state;
    float bright;
    int result;
    clIndicator *indicator;
    clFlowCCInterface *pages[8];

    clFlowCardCheck();
    virtual ~clFlowCardCheck();
    virtual int Update();
    virtual void Draw();
};

class clFlowCCBattle : public clFlowCCInterface {
public:
    int blink;
    float grid[101];
    Sprite **grp[3];
    TextMgr *text[7];

    clFlowCCBattle();
    virtual ~clFlowCCBattle();
    virtual void Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn(int t);
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
    virtual void Update();
    virtual void Draw();
    virtual void Unk14();
    virtual void SlideIn(int t);
    virtual void OnHidden();
};

class clFlowCCCharaItem : public clFlowCCInterface {
public:
    clFlowCCCharaItem(int which);
    virtual ~clFlowCCCharaItem();
    virtual void Update();
    virtual void Draw();
    virtual void Unk14();
};

class clFlowCCItem : public clFlowCCInterface {
public:
    clFlowCCItem();
    virtual ~clFlowCCItem();
    virtual void Update();
    virtual void Draw();
    virtual void Unk14();
};

class clFlowCCDate : public clFlowCCInterface {
public:
    clFlowCCDate();
    virtual ~clFlowCCDate();
    virtual void Update();
    virtual void Draw();
    virtual void Unk14();
};

static inline InputState *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

static inline PlayerData *GetPlayerData() {
    return &g_playerData;
}

static inline int CardRes(PlayerData *pd, int i) {
    return Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, kCards[i / 12][i % 12]), 0);
}

void clFlowCardCheck::Draw() {
    clFlowCCInterface *p = pages[page];
    if (p != 0 && p->active == 1) {
        p->Draw();
    }
    if (prevPage >= 0) {
        p = pages[prevPage];
        if (p != 0 && p->active == 1) {
            p->Draw();
        }
    }
    fn_8023CD54(indicator);
}

int clFlowCardCheck::Update() {
    InputState *in = input_state();
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        pages[0] = new clFlowCCDate();
        pages[page]->Open(18);
        state = 2;
        fn_801699D8(0, 1);
        fn_801699D8(1, 1);
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Stick() >= 0.5f) {
            stickLatch = 1;
        }
        break;
    case 2:
        if (in->cardState == 3) {
            SetRumbleMode(1, 1, 1);
            fn_801FE390();
            if (prevPage < 0) {
                prevPage = page;
                pages[page]->Close(18);
                if (++page >= 8) {
                    page = 0;
                }
                if (pages[page] == 0) {
                    switch (page) {
                    case 0:
                        pages[page] = new clFlowCCDate();
                        break;
                    case 1:
                        pages[page] = new clFlowCCItem();
                        break;
                    case 2:
                        pages[page] = new clFlowCCCharaItem(0);
                        break;
                    case 3:
                        pages[page] = new clFlowCCCharaItem(1);
                        break;
                    case 4:
                        pages[page] = new clFlowCCGP(0);
                        break;
                    case 5:
                        pages[page] = new clFlowCCGP(1);
                        break;
                    case 6:
                        pages[page] = new clFlowCCGP(2);
                        break;
                    case 7:
                        pages[page] = new clFlowCCBattle();
                        break;
                    }
                }
                pages[page]->Open(18);
                timer = 18;
            }
        }
        if (prevPage >= 0) {
            clFlowCCInterface *p = pages[prevPage];
            if (p != 0) {
                if (p->active == 0) {
                    if (p != 0) {
                        delete p;
                        pages[prevPage] = 0;
                    }
                    prevPage = -1;
                }
            } else {
                prevPage = -1;
            }
        }
        {
            void *mgr = GetInputManager();
            if (InputMgr_GetPlayer(mgr, 0)->Stick() < 0.5f) {
                stickLatch = 0;
            }
            if (InputMgr_GetPlayer(mgr, 0)->Held(0x2000) ||
                (InputMgr_GetPlayer(mgr, 0)->Stick() >= 0.5f && stickLatch == 0) || bright <= 0.0f) {
                bright = -1.0f;
                fn_801FE348();
                state = 3;
                fn_801699D8(0, 0);
                fn_801699D8(1, 0);
            }
        }
        break;
    case 3:
        state = 0;
        result = 11;
        break;
    }
    for (int i = 0; i < 8; i++) {
        clFlowCCInterface *p = pages[i];
        if (p != 0 && p->active == 1) {
            p->Update();
        }
    }
    fn_8023CDA8(indicator);
    bright -= 1.0f / 60.0f;
    if (bright < 0.0f) {
        bright = -1.0f;
    }
    SetScreenBrightness(bright);
    fn_801B7EF8();
    return result;
}

clFlowCardCheck::~clFlowCardCheck() {
    SetScreenBrightness(-1.0f);
    PlayerData *pd = &g_playerData;
    for (int i = 0; i < 60; i++) {
        fn_80120A08(CardRes(pd, i));
    }
    for (int i = 0; i < 8; i++) {
        if (pages[i] != 0) {
            delete pages[i];
            pages[i] = 0;
        }
    }
    if (indicator != 0) {
        delete indicator;
        indicator = 0;
    }
}

clFlowCardCheck::clFlowCardCheck()
    : stickLatch(0), page(0), prevPage(-1), timer(0), state(0), bright(30.0f), result(-1), indicator(0) {
    PlayerData *pd = &g_playerData;
    pages[0] = 0;
    pages[1] = 0;
    pages[2] = 0;
    pages[3] = 0;
    pages[4] = 0;
    pages[5] = 0;
    pages[6] = 0;
    pages[7] = 0;
    SetSyncTarget(9);
    if (input_state()) {
        InputState *in = input_state();
        in->enabled = 1;
        in->cardState = 0;
        in->i1C = 0;
    }
    InitBGM();
    SetupBgSprites(1);
    fn_801B8918(0x1AD7);
    fn_801B8874(0x1AD7);
    SetScreenBrightness(bright);
    pages[0] = 0;
    pages[1] = 0;
    pages[2] = 0;
    pages[3] = 0;
    pages[4] = 0;
    pages[5] = 0;
    pages[6] = 0;
    pages[7] = 0;
    for (int i = 0; i < 60; i++) {
        PreloadResource(CardRes(pd, i));
    }
    indicator = new clIndicator(0x74, 0x14, 0x186F, 0x1871, 5);
    fn_8023CD3C(indicator, 383.0f, 450.0f);
    fn_8023CD24(indicator, 193.0f, 454.0f);
    fn_8023CCF8(indicator, 451.0f, 450.0f);
    fn_8023CCCC(indicator, 265.0f, 450.0f);
    fn_8023CDA8(indicator);
    InitRumbleController(1);
}

void clFlowCCBattle::Unk14() {}
void clFlowCCBattle::OnHidden() {}
void clFlowCCBattle::SlideIn(int t) {}

void clFlowCCBattle::Draw() {
    for (int i = 0; i < 2; i++) {
        if (grp[i] != 0) {
            fn_801A0004(*grp[i]);
        }
    }
    void *list = fn_801F8E58();
    for (int i = 0; i < 7; i++) {
        fn_801F8A34(list, text[i], 4);
    }
    float x;
    float y = 219.0f;
    for (int row = 0; row < 5; row++) {
        x = 34.0f;
        for (int col = 0; col < 20; col++) {
            int idx = row * 20 + col;
            if (g_playerData.stamps <= idx) {
                return;
            }
            Sprite *s = *grp[2];
            s->x = x + slide;
            s->y = y;
            Sprite_SetAnimTime(*grp[2], grid[idx]);
            fn_801A0004(*grp[2]);
            x += 30.0f;
        }
        y += 32.0f;
    }
}

void clFlowCCBattle::Update() {
    InputPlayer &pl = *InputMgr_GetPlayer(GetInputManager(), 0);
    UpdateSlide();
    if (IsIdle() != 1) {
        for (int i = 0; i < 3; i++) {
            const Vec2 &p = kBattleGrpPos[i];
            if (grp[i] != 0) {
                (*grp[i])->x = p.x + slide;
            }
        }
        for (int i = 0; i < 7; i++) {
            const Vec2 &p = kBattleTextPos[i];
            fn_801F93EC(text[i], p.x + slide, p.y);
        }
        if (isJapanese()) {
            fn_801F93EC(text[0], kJpTitlePos.x + slide, kJpTitlePos.y);
            fn_801F93EC(text[2], text[2]->x, 4.0f + text[2]->y);
            fn_801F93EC(text[4], text[4]->x, 4.0f + text[4]->y);
        }
    }
    if (++blink >= 0) {
        if (blink == 16) {
            blink = -120;
            grid[100] = 0.0f;
        } else {
            grid[100] = 0.0165f * blink;
        }
    }
    for (int y = 4; y >= 0; y--) {
        for (int x = 19; x >= 0; x--) {
            int src = 100;
            if (y > 0) {
                src = x + (y - 1) * 20;
            } else if (x > 0) {
                src = (x - 1) + y * 20;
            }
            grid[x + y * 20] = grid[src];
        }
    }
    for (int i = 0; i < 3; i++) {
        if (grp[i] != 0) {
            Sprite_AdvanceAnim(*grp[i], 0.0165f);
        }
    }
}

clFlowCCBattle::~clFlowCCBattle() {
    for (int i = 0; i < 7; i++) {
        if (i < 6) {
            fn_801F9518(text[i]);
        } else {
            fn_801F95A0(text[i]);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (grp[i] != 0) {
            SpriteAnimHandle_Destroy(grp[i], 1);
            grp[i] = 0;
        }
    }
    for (int i = 0; i < 7; i++) {
        if (text[i] != 0) {
            delete text[i];
            text[i] = 0;
        }
    }
    for (int i = 0; i < 10; i++) {
        fn_80120A08(i + 0x15A6);
        fn_80120A08(i + 0x159B);
    }
}

clFlowCCBattle::clFlowCCBattle() : blink(0) {
    PlayerData *pd = &g_playerData;
    grp[0] = 0;
    grp[1] = 0;
    grp[2] = 0;
    for (int i = 0; i < 101; i++) {
        grid[i] = 0.0f;
    }
    SpriteGroup_CreateOrInit(&grp[0], kBattleGrp0, 0, kBattleGrpPos[0].x, kBattleGrpPos[0].y);
    SpriteGroup_CreateOrInit(&grp[1], kBattleGrp1, 0, kBattleGrpPos[1].x, kBattleGrpPos[1].y);
    SpriteGroup_CreateOrInit(&grp[2], kBattleGrp2, 0, kBattleGrpPos[2].x, kBattleGrpPos[2].y);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x159D, 0x1ED3);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x159C, 0x1ED1);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x159B, 0x1ECF);
    short d;
    d = pd->stamps < 100 ? 0x1ECD : pd->stamps / 100 % 10 + 0x159B;
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x1ED3, d);
    d = pd->stamps < 10 ? 0x1ECD : pd->stamps / 10 % 10 + 0x159B;
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x1ED1, d);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x1ECF, pd->stamps % 10 + 0x159B);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x15B0, 0x1ECD);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x15A8, 0x1ECD);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x15A7, 0x1ECD);
    SpriteAnimParamBlock_SetAnimParamCached(grp[1], 0x15A6, 0x1ECD);
    for (int i = 0; i < 7; i++) {
        text[i] = new TextMgr();
    }
    text[0]->visible = 1;
    text[1]->visible = 1;
    text[2]->visible = 1;
    text[3]->visible = 1;
    text[4]->visible = 1;
    text[5]->visible = 1;
    text[6]->visible = 0;
    TexMgr_SetTexture(text[0], "8/8");
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x82, -1));
    TexMgr_SetTexture(text[2], GetTextureByIdAndLang(0x83, -1));
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x84, -1), pd->stamps + pd->stamps2);
    TexMgr_SetTexture(text[4], GetTextureByIdAndLang(0x85, -1));
    TexMgr_SetTexture(text[5], GetTextureByIdAndLang(0x86, -1), pd->stamps);
    TexMgr_SetTexture(text[6], GetTextureByIdAndLang(0x79, -1));
    text[0]->scale = -6.0f;
    text[6]->scale = -1.0f;
    text[1]->scale = -2.0f;
    text[2]->scale = -1.0f;
    text[3]->scale = -1.0f;
    text[4]->scale = -1.0f;
    text[5]->scale = -1.0f;
    int i;
    for (i = 0; i < 7; i++) {
        fn_801F93EC(text[i], kBattleTextPos[i].x, kBattleTextPos[i].y);
    }
    if (isJapanese()) {
        text[2]->visible = 0;
        text[4]->visible = 0;
        fn_801F93EC(text[0], kJpTitlePos.x, kJpTitlePos.y);
    }
    for (i = 0; i < 7; i++) {
        fn_801F8E90(text[i]);
    }
}

void clFlowCCGP::Unk14() {}
void clFlowCCGP::OnHidden() {}
void clFlowCCGP::SlideIn(int t) {}

void clFlowCCGP::Draw() {
    for (int i = 0; i < 9; i++) {
        if (grp[i] != 0) {
            fn_801A0004(*grp[i]);
        }
    }
    void *list = fn_801F8E58();
    for (int i = 0; i < 4; i++) {
        fn_801F8A34(list, text[i], 4);
    }
    ResCtrl rc;
    rc.resId = fn_801D5C88(&g_playerData, cc) == 1 ? 0x15F4 : 0x1ECD;
    rc.Show(kGPHandlePos[1].x + slide, kGPHandlePos[1].y, 1.0f);
    fn_8011FAFC(&rc, 4);
}

void clFlowCCGP::Update() {
    PlayerData *pd = &g_playerData;
    InputPlayer *pl = InputMgr_GetPlayer(GetInputManager(), 0);
    UpdateSlide();
    if (IsIdle() == 1) {
        if (first == 1) {
            first = 0;
        }
    } else {
        for (int i = 0; i < 9; i++) {
            if (grp[i] != 0) {
                const Vec2 &p = kGPGrpPos[i];
                (*grp[i])->x = p.x + slide;
            }
        }
        for (int i = 0; i < 4; i++) {
            const Vec2 &p = kGPTextPos[i];
            fn_801F93EC(text[i], p.x + slide, p.y);
        }
        for (int i = 0; i < 2; i++) {
            const Vec2 &p = kGPHandlePos[i];
            fn_8011F804(handles[i], p.x + slide, p.y);
        }
        if (fn_801D5C88(pd, cc) == 1) {
            fn_801F93EC(text[1], 79.0f + slide, 99.0f);
            fn_801F93EC(text[2], 274.0f + slide, 99.0f);
        }
        if (isJapanese()) {
            fn_801F93EC(text[2], 45.0f + text[2]->x, text[2]->y);
            fn_801F93EC(text[0], kJpTitlePos.x + slide, kJpTitlePos.y);
        }
    }
    for (int i = 0; i < 9; i++) {
        if (grp[i] != 0) {
            Sprite_AdvanceAnim(*grp[i], 0.0165f);
        }
    }
    for (int i = 0; i < 2; i++) {
        SpriteHandle_RecomputeCull(handles[i]);
    }
}

clFlowCCGP::~clFlowCCGP() {
    for (int i = 0; i < 2; i++) {
        SpriteHandle_Destroy(handles[i]);
    }
    if (cc == 2) {
        for (int i = 0; i < 4; i++) {
            if (i < 3) {
                fn_801F9518(text[i]);
            } else {
                fn_801F95A0(text[i]);
            }
        }
        PlayerData *pd = &g_playerData;
        if (fn_801D5C88(pd, 0) == 1 || fn_801D5C88(pd, 1) == 1 || fn_801D5C88(pd, 2) == 1) {
            fn_80120A08(0x15F4);
        }
    }
    fn_80120A08(0x15FD);
    fn_80120A08(0x15D7);
    fn_80120A08(0x15DB);
    for (int i = 0; i < 9; i++) {
        if (grp[i] != 0) {
            SpriteAnimHandle_Destroy(grp[i], 1);
            grp[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (text[i] != 0) {
            delete text[i];
            text[i] = 0;
        }
    }
}

clFlowCCGP::clFlowCCGP(int cc) : cc(cc), first(1) {
    PlayerData *pd = &g_playerData;
    grp[0] = 0;
    grp[1] = 0;
    grp[2] = 0;
    grp[3] = 0;
    grp[4] = 0;
    grp[5] = 0;
    grp[6] = 0;
    grp[7] = 0;
    grp[8] = 0;
    SpriteGroup_CreateOrInit(&grp[0], kGPGrp0, 0, kGPGrpPos[0].x, kGPGrpPos[0].y);
    SpriteGroup_CreateOrInit(&grp[1], kGPGrp1, 0, kGPGrpPos[1].x, kGPGrpPos[1].y);
    SpriteGroup_CreateOrInit(&grp[2], kGPGrp2, 0, kGPGrpPos[2].x, kGPGrpPos[2].y);
    SpriteGroup_CreateOrInit(&grp[3], kGPGrp3, 0, kGPGrpPos[3].x, kGPGrpPos[3].y);
    SpriteGroup_CreateOrInit(&grp[4], kGPGrp4, 0, kGPGrpPos[4].x, kGPGrpPos[4].y);
    SpriteGroup_CreateOrInit(&grp[5], kGPGrp5, 0, kGPGrpPos[5].x, kGPGrpPos[5].y);
    SpriteGroup_CreateOrInit(&grp[6], kGPGrp6, 0, kGPGrpPos[6].x, kGPGrpPos[6].y);
    SpriteGroup_CreateOrInit(&grp[7], kGPGrp7, 0, kGPGrpPos[7].x, kGPGrpPos[7].y);
    if (lbl_806D12E4[this->cc] == 1) {
        SpriteGroup_CreateOrInit(&grp[8], kGPGrp8a, 0, kGPGrpPos[8].x, kGPGrpPos[8].y);
    } else {
        SpriteGroup_CreateOrInit(&grp[8], kGPGrp8b, 0, kGPGrpPos[8].x, kGPGrpPos[8].y);
    }
    int sub = 1;
    if (fn_801D5C88(pd, this->cc) == 1) {
        sub = 6;
    }
    for (int i = 0; i < 8; i++) {
        if (kGPCupIds[i] != 6 || lbl_806D12E4[this->cc] != 0) {
            int rank = fn_801D59A0(pd, this->cc) - sub;
            if (rank < -1) {
                rank = -1;
            }
            int idx = i + 1;
            int j;
            for (j = 3; j > rank; j--) {
                SpriteAnimParamBlock_SetAnimParamCached(grp[idx], kGPRankParams[j][0], 0x1ECD);
                SpriteAnimParamBlock_SetAnimParamCached(grp[idx], kGPRankParams[j][1], 0x1ECD);
            }
            int m = rank;
            if (rank >= 4) {
                m = 3;
            }
            for (j = m; j >= 0; j--) {
                SpriteAnimParamBlock_SetAnimParamCached(grp[idx], kGPRankParams[j][1], 0x15EB);
            }
            if (rank >= 4) {
                SpriteAnimParamBlock_SetAnimParamCached(grp[idx], 0x15C8, 0x15FD);
                SpriteAnimParamBlock_SetAnimParamCached(grp[idx], kGPCupAnim[i], kGPCupAnim[i] + 1);
            }
        }
    }
    handles[1] = -1;
    ResCtrl rc;
    rc.resId = 0x1599;
    rc.Show(kGPHandlePos[0].x, kGPHandlePos[0].y, 1.0f);
    handles[0] = SpriteHandle_CreateDefault(&rc, 4);
    for (int i = 0; i < 4; i++) {
        text[i] = new TextMgr();
    }
    text[0]->visible = 1;
    text[1]->visible = 1;
    text[2]->visible = 1;
    text[3]->visible = 0;
    TexMgr_SetTexture(text[0], "%d/8", this->cc + 5);
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x81, -1));
    TexMgr_SetTexture(text[2], kCCNames[this->cc]);
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x79, -1));
    text[0]->scale = -6.0f;
    text[3]->scale = -1.0f;
    text[1]->scale = -2.0f;
    text[2]->scale = -6.0f;
    int i;
    for (i = 0; i < 4; i++) {
        fn_801F93EC(text[i], kGPTextPos[i].x, kGPTextPos[i].y);
    }
    if (fn_801D5C88(pd, this->cc) == 1) {
        fn_801F93EC(text[1], 79.0f, 99.0f);
        fn_801F93EC(text[2], 274.0f, 99.0f);
    }
    if (isJapanese()) {
        fn_801F93EC(text[0], kJpTitlePos.x, kJpTitlePos.y);
        fn_801F93EC(text[2], 45.0f + text[2]->x, text[2]->y);
        text[1]->scale = -4.0f;
    }
    for (i = 0; i < 4; i++) {
        fn_801F8E90(text[i]);
    }
}

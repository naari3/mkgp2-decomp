#include "game/FlowCardCheckPages_private.h"

clFlowCCInterface::~clFlowCCInterface() {}

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

extern "C" const Vec2 lbl_806DB780;
extern "C" const float lbl_806DB7A0;
extern "C" const float lbl_806DB7AC;
extern "C" const char lbl_806DB7F8[4];
extern "C" const char lbl_806DB818[5];
extern "C" const char *FlowCardCheck_nm2_data_804EE3A8[3];
#define kCCNames FlowCardCheck_nm2_data_804EE3A8

static const unsigned int kPageTables[300] = {0x00000000, 0x00000000, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x000000C8, 0x00000040, 0x00000000, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB};
static const int kCards[5][12] = {{0x00000006, 0x00000002, 0x00000001, 0x00000000, 0x00000007, 0x00000003, 0x0000000B, 0x00000008, 0x0000000A, 0x00000009, 0x0000000D, 0x0000000C}, {0x00000004, 0x00000005, 0x0000002A, 0x0000000F, 0x0000001E, 0x0000000E, 0x00000016, 0x00000017, 0x0000002C, 0x0000001B, 0x0000002B, 0x0000003B}, {0x00000026, 0x00000028, 0x00000027, 0x0000003A, 0x00000025, 0x00000010, 0x00000029, 0x0000002D, 0x00000013, 0x00000019, 0x0000001D, 0x00000014}, {0x00000018, 0x0000001F, 0x00000023, 0x00000022, 0x00000021, 0x00000012, 0x0000001C, 0x00000020, 0x00000015, 0x00000024, 0x0000001A, 0x00000011}, {0x0000002E, 0x00000036, 0x00000030, 0x00000032, 0x00000035, 0x00000039, 0x00000037, 0x00000038, 0x00000031, 0x00000034, 0x0000002F, 0x00000033}};
static const Vec2 kDateTabA[6] = {{320.0f, 250.0f}, {320.0f, 250.0f}, {339.0f, 286.0f}, {452.0f, 285.0f}, {339.0f, 378.0f}, {452.0f, 378.0f}};
static const Vec2 kDateTextPos[12] = {{398.0f, 100.0f}, {34.0f, 100.0f}, {82.0f, 178.0f}, {82.0f, 274.0f}, {82.0f, 369.0f}, {294.0f, 178.0f}, {455.0f, 104.0f}, {78.0f, 146.0f}, {78.0f, 242.0f}, {78.0f, 337.0f}, {290.0f, 146.0f}, {448.0f, 335.0f}};
static const Vec2 kItemGrpPos[7] = {{320.0f, 250.0f}, {320.0f, 250.0f}, {34.0f, 164.0f}, {600.0f, 164.0f}, {86.0f, 154.0f}, {86.0f, 154.0f}, {86.0f, 154.0f}};
static const Vec2 kItemTextPos[8] = {{398.0f, 100.0f}, {33.0f, 99.0f}, {455.0f, 104.0f}, {203.0f, 103.0f}, {125.0f, 328.0f}, {325.0f, 332.0f}, {325.0f, 354.0f}, {325.0f, 376.0f}};
static const float kItemX[12] = {86.0f, 128.0f, 170.0f, 212.0f, 254.0f, 296.0f, 338.0f, 380.0f, 422.0f, 464.0f, 506.0f, 548.0f};
static const float kItemY[5] = {154.0f, 185.0f, 216.0f, 247.0f, 278.0f};
static const Vec2 kCharaGrpPos[11] = {{320.0f, 250.0f}, {320.0f, 250.0f}, {173.0f, 146.0f}, {471.0f, 146.0f}, {173.0f, 208.0f}, {471.0f, 208.0f}, {173.0f, 271.0f}, {471.0f, 271.0f}, {-640.0f, -480.0f}, {-640.0f, -480.0f}, {-640.0f, -480.0f}};
static const Vec2 kCharaTextPos[8] = {{398.0f, 100.0f}, {33.0f, 99.0f}, {455.0f, 104.0f}, {296.0f, 103.0f}, {125.0f, 328.0f}, {325.0f, 332.0f}, {325.0f, 354.0f}, {325.0f, 376.0f}};
static const int kCharaTabA[2][6][2] = {{{0x00001D23, 0x00001D24}, {0x00001D27, 0x00001ECD}, {0x00001D2F, 0x00001ECD}, {0x00001D2C, 0x00001ECD}, {0x00001D2D, 0x00001ECD}, {0x00001D26, 0x00001ECD}}, {{0x00001D2E, 0x00001ECD}, {0x00001D28, 0x00001ECD}, {0x00001D25, 0x00001D2B}, {0x00001D29, 0x00001ECD}, {0x00001D2A, 0x00001ECD}, {0x00001ECD, 0x00001ECD}}};
static const int kCharaGroups[2][6] = {{0x00000000, 0x00000003, 0x00000004, 0x00000005, 0x00000002, 0x0000000B}, {0x00000006, 0x00000007, 0x00000008, 0x0000000A, 0x0000000C, 0xFFFFFFFF}};
static const float kCharaY[3] = {146.0f, 208.0f, 271.0f};
static const int kCharaParams[5] = {0x000013B9, 0x000013BA, 0x000013BB, 0x000013BC, 0x000013BD};
static const Vec2 kGPGrpPos[9] = {{320.0f, 250.0f}, {176.0f, 160.0f}, {465.0f, 160.0f}, {176.0f, 228.0f}, {465.0f, 228.0f}, {176.0f, 296.0f}, {465.0f, 296.0f}, {176.0f, 364.0f}, {465.0f, 364.0f}};
static const Vec2 kGPTextPos[4] = {{398.0f, 100.0f}, {32.0f, 99.0f}, {230.0f, 99.0f}, {455.0f, 104.0f}};
static const Vec2 kGPHandlePos[2] = {{320.0f, 250.0f}, {40.0f, 102.0f}};
static const int kGPRankParams[4][2] = {{0x15D7, 0x2467}, {0x15D8, 0x2469}, {0x15D9, 0x246B}, {0x15DA, 0x246D}};
static const int kGPCupAnim[8] = {0x15DB, 0x15DD, 0x15DF, 0x15E1, 0x15E3, 0x15E5, 0x15E7, 0x15E9};
static const int kGPCupIds[8] = {7, 1, 8, 2, 3, 4, 5, 6};
static const Vec2 kBattleGrpPos[3] = {{320.0f, 250.0f}, {320.0f, 250.0f}, {-640.0f, -240.0f}};
static const Vec2 kBattleTextPos[7] = {{398.0f, 100.0f}, {33.0f, 99.0f}, {54.0f, 380.0f}, {213.0f, 380.0f}, {366.0f, 380.0f}, {512.0f, 380.0f}, {455.0f, 104.0f}};

#define kDateGrpPos kDateTabA
#define kCharaFrames kCharaTabA

static inline int CardRes(PlayerData *pd, int i) {
    return Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, kCards[i / 12][i % 12]), 0);
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
void clFlowCCBattle::SlideIn() {}

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

int clFlowCCBattle::Update() {
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
            fn_801F93EC(text[0], lbl_806DB780.x + slide, lbl_806DB780.y);
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
            int dst = x + y * 20;
            int src = 100;
            if (y > 0) {
                src = x + (y - 1) * 20;
            } else if (x > 0) {
                src = (x - 1) + y * 20;
            }
            grid[dst] = grid[src];
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
    TexMgr_SetTexture(text[0], lbl_806DB7F8);
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
        fn_801F93EC(text[0], lbl_806DB780.x, lbl_806DB780.y);
    }
    for (i = 0; i < 7; i++) {
        fn_801F8E90(text[i]);
    }
}

void clFlowCCGP::Unk14() {}
void clFlowCCGP::OnHidden() {}
void clFlowCCGP::SlideIn() {}

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

int clFlowCCGP::Update() {
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
            fn_801F93EC(text[0], lbl_806DB780.x + slide, lbl_806DB780.y);
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
    int i;
    for (i = 0; i < 8; i++) {
        if (kGPCupIds[i] != 6 || lbl_806D12E4[this->cc] != 0) {
            int rank = fn_801D59A0(pd, this->cc, kGPCupIds[i]) - sub;
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
    for (i = 0; i < 4; i++) {
        text[i] = new TextMgr();
    }
    text[0]->visible = 1;
    text[1]->visible = 1;
    text[2]->visible = 1;
    text[3]->visible = 0;
    TexMgr_SetTexture(text[0], lbl_806DB818, this->cc + 5);
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x81, -1));
    TexMgr_SetTexture(text[2], kCCNames[this->cc]);
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x79, -1));
    text[0]->scale = -6.0f;
    text[3]->scale = -1.0f;
    text[1]->scale = -2.0f;
    text[2]->scale = -6.0f;
    for (int positionIndex = 0; positionIndex < 4; positionIndex++) {
        fn_801F93EC(text[positionIndex], kGPTextPos[positionIndex].x, kGPTextPos[positionIndex].y);
    }
    if (fn_801D5C88(pd, this->cc) == 1) {
        fn_801F93EC(text[1], 79.0f, 99.0f);
        fn_801F93EC(text[2], 274.0f, 99.0f);
    }
    if (isJapanese()) {
        fn_801F93EC(text[0], lbl_806DB780.x, lbl_806DB780.y);
        fn_801F93EC(text[2], 45.0f + text[2]->x, text[2]->y);
        text[1]->scale = -4.0f;
    }
    for (i = 0; i < 4; i++) {
        fn_801F8E90(text[i]);
    }
}

void clFlowCCCharaItem::Unk14() {}
void clFlowCCCharaItem::OnHidden() {}
void clFlowCCCharaItem::SlideIn() {}
void clFlowCCItem::Unk14() {}
void clFlowCCItem::OnHidden() {}
void clFlowCCDate::Unk14() {}
void clFlowCCDate::SlideIn() {}

void clFlowCCItem::SlideOut() {
    for (int id = 0x1ECD; id < 0x23CD; id += 2) {
        fn_80120A08(id);
    }
}

void clFlowCCItem::SlideIn() {
    for (int i = 0; i < 60; i++) {
        SpriteHandle_SetActiveFlag(handles[i], 1);
    }
    SpriteHandle_SetActiveFlag(handle, 1);
}

void clFlowCCDate::OnHidden() {
    if (indicator != 0) {
        fn_8023CCA0(indicator, 0);
        fn_8023CC74(indicator, 0);
    }
}

void clFlowCCCharaItem::Draw() {
    for (int i = 0; i < 11; i++) {
        if (grp[i] != 0) {
            fn_801A0004(*grp[i]);
        }
    }
    void *list = fn_801F8E58();
    for (int i = 0; i < 8; i++) {
        fn_801F8A34(list, text[i], 4);
    }
}

void clFlowCCDate::Draw() {
    for (int i = 0; i < 6; i++) {
        if (grp[i] != 0) {
            fn_801A0004(*grp[i]);
        }
    }
    fn_8011FAB8();
    fn_801A1280();
    void *list = fn_801F8E58();
    for (int i = 0; i < 12; i++) {
        fn_801F8A34(list, text[i], 4);
    }
    if (indicator != 0) {
        fn_8023CD54(indicator);
    }
}

#include "game/SpriteAnimTraversal_private.h"

extern "C" unsigned char fn_8019FF8C(Sprite *s, int key, SpriteAnimSample *out);

void clFlowCCItem::Draw() {
    for (int i = 0; i < 7; i++) {
        if (grp[i] != 0) fn_801A0004(*grp[i]);
    }
    void *list = fn_801F8E58();
    for (int i = 0; i < 8; i++) fn_801F8A34(list, text[i], 4);
}

clFlowCCItem::~clFlowCCItem() {
    for (int i = 0; i < 8; i++) {
        if (i < 2) fn_801F9518(text[i]);
        else fn_801F95A0(text[i]);
    }
    for (int i = 0; i < 7; i++) {
        if (grp[i] != 0) { SpriteAnimHandle_Destroy(grp[i], 1); grp[i] = 0; }
    }
    for (int i = 0; i < 8; i++) {
        if (text[i] != 0) { delete text[i]; text[i] = 0; }
    }
    SpriteHandle_Destroy(handle);
    for (int i = 0; i < 60; i++) SpriteHandle_Destroy(handles[i]);
    fn_80120A08(0x1E3D);
    if (indicator != 0) { delete indicator; indicator = 0; }
}

clFlowCCDate::~clFlowCCDate() {
    PlayerData *pd = &g_playerData;
    pd->datePage = field1C;
    pd->dateMode = field1D;
    for (int i = 0; i < 12; i++) {
        if (i < 6) fn_801F9518(text[i]);
        else fn_801F95A0(text[i]);
    }
    for (int i = 0; i < 6; i++) {
        if (grp[i] != 0) { SpriteAnimHandle_Destroy(grp[i], 1); grp[i] = 0; }
    }
    for (int i = 0; i < 12; i++) {
        if (text[i] != 0) { delete text[i]; text[i] = 0; }
    }
    if (indicator != 0) { delete indicator; indicator = 0; }
    fn_80120A08(0x15F7);
    fn_80120A08(0x15F6);
    fn_80120A08(0x1ECD);
}

clFlowCCCharaItem::~clFlowCCCharaItem() {
    PlayerData *pd = &g_playerData;
    if (which == 1) {
        for (int id = 0x1ECD; id <= 0x23CD; id += 2) fn_80120A08(id);
    }
    for (int i = 0; i < 6; i++) {
        if ((int)kCharaGroups[which][i] == -1) {
            fn_80120A08((short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, fn_8023D844(0, 0)), 0));
        } else {
            for (int j = 0; j < 5; j++) {
                int index = fn_8023D844(kCharaGroups[which][i], j + 1);
                fn_80120A08((short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, index), 0));
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        fn_80120A08(kCharaFrames[which][i][0]);
        fn_80120A08(kCharaFrames[which][i][1]);
    }
    for (int i = 0; i < 11; i++) {
        if (grp[i] != 0) { SpriteAnimHandle_Destroy(grp[i], 1); grp[i] = 0; }
    }
    for (int i = 0; i < 8; i++) {
        if (text[i] != 0) { delete text[i]; text[i] = 0; }
    }
}

inline void clFlowCCItem::PositionSelection() {
    float x = kItemX[field1C];
    float y = kItemY[field20];
    { Sprite *sprite = *grp[4]; sprite->x = x; sprite->y = y; }
    { Sprite *sprite = *grp[5]; sprite->x = x; sprite->y = y; }
    { Sprite *sprite = *grp[6]; sprite->x = x; sprite->y = y; }
    fn_8011F804(handle, lbl_806DB834, y);
}

void clFlowCCItem::Select(int delta) {
    if (delta != 0) {
        PlayerData *pd = &g_playerData;
        do {
            field1C += delta;
            if (field1C < 0) { field1C = 11; --field20; }
            if (field1C > 11) { field1C = 0; ++field20; }
            if (field20 < 0) field20 = 4;
            if (field20 > 4) field20 = 0;
        } while (pd->unlocked[kCards[field20][field1C]] != 1);
        int item = PlayerData_ResolveUnlockedIdByIndex(pd, kCards[field20][field1C]);
        int res = (short)Item_GetDescriptorField0(item, 0);
        SpriteAnimParamBlock_SetAnimParamCached(grp[4], resId, res);
        fn_8019FF6C(*grp[4], 1);
        PositionSelection();
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], resId, res);
        TexMgr_SetTexture(text[4], fn_8023DAA8(item));
        TexMgr_SetTexture(text[5], fn_8023D938(item, 0));
        TexMgr_SetTexture(text[6], fn_8023D938(item, 1));
        TexMgr_SetTexture(text[7], fn_8023D938(item, 2));
        int param = Item_GetDescriptorFieldC(item);
        int anim = -1;
        if (param >= 0) anim = param + 0x1E1D;
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], paramId, anim);
        resId = res;
        paramId = anim;
    }
}

int clFlowCCCharaItem::Update() {
    InputPlayer *pl = InputMgr_GetPlayer(GetInputManager(), 0);
    UpdateSlide();
    if (IsIdle() == 1) {
        if (first == 1) { first = 0; field28 = -1; Select(1); }
        InputState *in = SINGLETON_INSTANCE(g_pInputState);
        int old = field24;
        Select(in->pageInput);
        if (old != field24) fn_801FE36C();
    } else {
        for (int i = 0; i < 11; i++) {
            Sprite **group = grp[i];
            if (group != 0) { float x = kCharaGrpPos[i].x; (*group)->x = x + slide; }
        }
        for (int i = 0; i < 8; i++) {
            const Vec2 &p = kCharaTextPos[i];
            fn_801F93EC(text[i], p.x + slide, p.y);
        }
        if (isJapanese()) {
            fn_801F93EC(text[0], lbl_806DB780.x + slide, lbl_806DB780.y);
            fn_801F93EC(text[3], lbl_806DB828 + slide, kItemTextPos[3].y);
        }
    }
    for (int i = 0; i < 11; i++) {
        if (grp[i] != 0) Sprite_AdvanceAnim(*grp[i], 0.0165f);
    }
}

static inline void ProcessItemInput(clFlowCCItem *page) {
    int delta = input_state()->pageInput;
    page->Select(delta);
    if (delta != 0) fn_801FE36C();
}

int clFlowCCItem::Update() {
    InputPlayer *pl = InputMgr_GetPlayer(GetInputManager(), 0);
    UpdateSlide();
    if (IsIdle() == 1) {
        if (first == 0) {
            first = 1;
            (*grp[4])->prio = 6;
            (*grp[5])->prio = 6;
            (*grp[6])->prio = 6;
            ResCtrl rc;
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 12; col++) {
                    int i = row * 12 + col;
                    SpriteHandle_Destroy(handles[i]);
                    handles[i] = SpriteHandle_CreateDefault(&cards[i], 5);
                }
            }
            fn_80121E10(&rc);
            rc.tail[0] = 1; rc.tail[1] = 1; rc.tail[2] = 1;
            rc.resId = 0x1E3D;
            rc.Show(lbl_806DB834, lbl_806DB838, 1.0f);
            rc.scaleX = lbl_806DB83C; rc.scaleY = 1.0f;
            SpriteHandle_Destroy(handle);
            handle = SpriteHandle_CreateDefault(&rc, 6);
        }
        ProcessItemInput(this);
    } else {
        for (int i = 0; i < 7; i++) {
            Sprite **group = grp[i];
            if (group != 0) { float x = kItemGrpPos[i].x; (*group)->x = x + slide; }
        }
        for (int i = 0; i < 8; i++) {
            const Vec2 &p = kItemTextPos[i];
            fn_801F93EC(text[i], p.x + slide, p.y);
        }
        if (isJapanese()) {
            fn_801F93EC(text[0], lbl_806DB780.x + slide, lbl_806DB780.y);
            fn_801F93EC(text[3], lbl_806DB828 + slide, kItemTextPos[3].y);
        }
        for (int row = 0; row < 5; row++) {
            float y = kItemY[row];
            for (int col = 0; col < 12; col++) {
                float x = kItemX[col];
                fn_8011F804(handles[row * 12 + col], x + slide, y);
            }
        }
        fn_8011F804(handle, lbl_806DB834 + slide, lbl_806DB838);
        fn_8023CD24(indicator, lbl_806DB840 + slide, lbl_806DB844);
        fn_8023CCCC(indicator, lbl_806DB840 + slide, lbl_806DB848);
    }
    for (int i = 0; i < 7; i++) {
        if (grp[i] != 0) Sprite_AdvanceAnim(*grp[i], 0.0165f);
    }
    SpriteHandle_RecomputeCull(handle);
    for (int i = 0; i < 60; i++) SpriteHandle_RecomputeCull(handles[i]);
    fn_8023CDA8(indicator);
}

clFlowCCItem::clFlowCCItem() : field1C(0), field20(0), resId(0x13B9), paramId(0x1E1D), first(0), indicator(0) {
    PlayerData *pd = &g_playerData;
    grp[0] = 0; grp[1] = 0; grp[2] = 0; grp[3] = 0;
    grp[4] = 0; grp[5] = 0; grp[6] = 0;
    indicator = new clIndicator(-1, 0x4A, -1, 0x1875, 4);
    fn_8023CD24(indicator, lbl_806DB840 + slide, lbl_806DB844);
    fn_8023CCCC(indicator, lbl_806DB840 + slide, lbl_806DB848);
    SpriteGroup_CreateOrInit(&grp[0], kItemGrp0, 0, kItemGrpPos[0].x, kItemGrpPos[0].y);
    SpriteGroup_CreateOrInit(&grp[1], kItemGrp1, 0, kItemGrpPos[1].x, kItemGrpPos[1].y);
    SpriteGroup_CreateOrInit(&grp[4], kItemGrp2, 1, kItemGrpPos[4].x, kItemGrpPos[4].y);
    SpriteGroup_CreateOrInit(&grp[5], kItemGrp3, 1, kItemGrpPos[5].x, kItemGrpPos[5].y);
    SpriteGroup_CreateOrInit(&grp[6], kItemGrp4, 1, kItemGrpPos[6].x, kItemGrpPos[6].y);
    int i = 0;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 12; col++) {
            int i = row * 12 + col;
            int res = 0x1422;
            if (pd->unlocked[kCards[row][col]] == 1) res = Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, kCards[row][col]), 0);
            fn_80121E10(&cards[i]);
            cards[i].resId = res;
            float y;
            float x;
            x = kItemX[col];
            y = kItemY[row];
            cards[i].Show(x, y, 1.0f);
            cards[i].colors[0] = 0xC3CDF0FF; cards[i].colors[1] = 0xC3CDF0FF;
            cards[i].colors[2] = 0xC3CDF0FF; cards[i].colors[3] = 0xC3CDF0FF;
            cards[i].scaleX = lbl_806DB84C; cards[i].scaleY = lbl_806DB84C;
            handles[i] = SpriteHandle_CreateDefault(&cards[i], 4);
        }
    }
    ResCtrl rc;
    rc.tail[0] = 1; rc.tail[1] = 1; rc.tail[2] = 1;
    rc.resId = 0x1E3D;
    rc.Show(lbl_806DB834, lbl_806DB838, 1.0f);
    rc.scaleX = lbl_806DB83C; rc.scaleY = 1.0f;
    handle = SpriteHandle_CreateDefault(&rc, 4);
    for (i = 0; i < 8; i++) text[i] = new TextMgr();
    text[0]->visible = 1; text[1]->visible = 1;
    text[2]->visible = 0; text[3]->visible = 0; text[4]->visible = 0;
    text[5]->visible = 0; text[6]->visible = 0; text[7]->visible = 0;
    TexMgr_SetTexture(text[0], lbl_806DB850);
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x7E, -1));
    TexMgr_SetTexture(text[2], GetTextureByIdAndLang(0x79, -1));
    int count = 0;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 12; col++) if (pd->unlocked[kCards[row][col]] == 1) ++count;
    }
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x7F, -1), count, 60);
    TexMgr_SetTexture(text[4], lbl_806DB82C);
    TexMgr_SetTexture(text[5], lbl_806DB82C);
    TexMgr_SetTexture(text[6], lbl_806DB82C);
    TexMgr_SetTexture(text[7], lbl_806DB82C);
    text[0]->scale = -6.0f; text[2]->scale = -1.0f; text[1]->scale = -2.0f;
    text[3]->scale = -1.0f; text[4]->scale = -1.0f;
    fn_801F93EC(text[0], kItemTextPos[0].x, kItemTextPos[0].y);
    fn_801F93EC(text[1], kItemTextPos[1].x, kItemTextPos[1].y);
    fn_801F93EC(text[2], kItemTextPos[2].x, kItemTextPos[2].y);
    fn_801F93EC(text[3], kItemTextPos[3].x, kItemTextPos[3].y);
    fn_801F93EC(text[4], kItemTextPos[4].x, kItemTextPos[4].y);
    fn_801F93EC(text[5], kItemTextPos[5].x, kItemTextPos[5].y);
    fn_801F93EC(text[6], kItemTextPos[6].x, kItemTextPos[6].y);
    fn_801F93EC(text[7], kItemTextPos[7].x, kItemTextPos[7].y);
    if (isJapanese()) {
        fn_801F93EC(text[0], lbl_806DB780.x, lbl_806DB780.y);
        fn_801F93EC(text[3], lbl_806DB828, kItemTextPos[3].y);
        text[1]->scale = lbl_806DB830;
    }
    for (i = 0; i < 8; i++) fn_801F8E90(text[i]);
    field1C = -1;
    Select(1);
}

static inline void SetCharaGroupForPlayer(Sprite **group, const int &which, int index, PlayerData *pd) {
    int id = kCharaGroups[which][index];
    unsigned char special = 0;
    if ((which == 1 && index == 5) || id < 0) special = 1;
    if (!special) {
        for (int j = 0; j < 5; j++) {
            int res = 0x1422;
            int unlocked = fn_8023D844(id, j + 1);
            if (pd->unlocked[unlocked] == 1) res = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, unlocked), 0);
            SpriteAnimParamBlock_SetAnimParamCached(group, kCharaParams[j], res);
        }
    } else {
        int res = 0x1422;
        if (pd->unlocked[fn_8023D844(0, 0)] == 1) res = 0x140A;
        SpriteAnimParamBlock_SetAnimParamCached(group, 0x13B9, res);
        SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BA, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BB, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BC, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BD, 0x1ECD);
    }
    SpriteAnimParamBlock_SetAnimParamCached(group, 0x1D23, kCharaFrames[which][index][0]);
    SpriteAnimParamBlock_SetAnimParamCached(group, 0x1D24, kCharaFrames[which][index][1]);
}

static inline void SetCharaGroup(Sprite **group, const int &which, int index) {
    PlayerData *pd = &g_playerData;
    SetCharaGroupForPlayer(group, which, index, pd);
}

/* Unused slots on the sentinel character row do not contain cards. */
static inline unsigned int CharaCardState(PlayerData *pd, int group, const int &slot) {
    if (group == -1 && slot >= 1) return 0;
    return pd->unlocked[fn_8023D844(group, slot + 1)];
}

void clFlowCCCharaItem::Select(int delta) {
    Sprite **group;
    int id_;
    unsigned char special_;
    if (delta != 0 && field20 != 0) {
        int oldGroup = field24;
        unsigned char special = 0;
        int max = 30;
        if (kCharaGroups[which][5] == -1) max = 26;
        int oldSlot = field28;
        PlayerData *pd = &g_playerData;
        int n;
        for (n = 0; n < max; n++) {
            field28 += delta;
            if (field28 < 0) { field28 = 4; --field24; }
            if (field28 > 4) { field28 = 0; ++field24; }
            if (field24 > 5) field24 = 0;
            if (field24 < 0) field24 = 5;
            int id = kCharaGroups[which][field24];
            if (id == -1) {
                if (field28 == 0 && pd->unlocked[60] == 1) { special = 1; break; }
            } else {
                if (CharaCardState(pd, id, field28) == 1) break;
            }
        }
        if (oldGroup == field24 && oldSlot == field28) return;
        if (n >= max) {
            if (oldSlot < 0) {
                TexMgr_SetTexture(text[4], lbl_806DB824);
                TexMgr_SetTexture(text[5], lbl_806DB824);
                TexMgr_SetTexture(text[6], lbl_806DB824);
                TexMgr_SetTexture(text[7], lbl_806DB824);
                SpriteAnimParamBlock_SetAnimParamCached(grp[1], resId, 0x1ECD);
                SpriteAnimParamBlock_SetAnimParamCached(grp[1], paramId, 0x1ECD);
            }
            return;
        }
        int item = !special
            ? PlayerData_ResolveUnlockedIdByIndex(pd, fn_8023D844(kCharaGroups[which][field24], field28 + 1))
            : PlayerData_ResolveUnlockedIdByIndex(pd, 60);
        short res = Item_GetDescriptorField0(item, 0);
        SpriteAnimParamBlock_SetAnimParamCached(grp[8], resId, res);
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], resId, res);
        TexMgr_SetTexture(text[4], fn_8023DAA8(item));
        TexMgr_SetTexture(text[5], fn_8023D938(item, 0));
        TexMgr_SetTexture(text[6], fn_8023D938(item, 1));
        TexMgr_SetTexture(text[7], fn_8023D938(item, 2));
        int anim = Item_GetDescriptorFieldC(item);
        int newParam = -1;
        if (anim >= 0) newParam = anim + 0x1E1D;
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], paramId, newParam);
        resId = res;
        paramId = newParam;
        float x = slots[field24 % 2][field28];
        float y = kCharaY[field24 / 2];
        { Sprite *sprite = *grp[8]; sprite->x = x; sprite->y = y; }
        { Sprite *sprite = *grp[9]; sprite->x = x; sprite->y = y; }
        { Sprite *sprite = *grp[10]; sprite->x = x; sprite->y = y; }
        if (oldGroup != field24) {
            SpriteAnimParamBlock_Reload(grp[oldGroup + 2], 0x15E);
            SpriteAnimParamBlock_Reload(grp[field24 + 2], 0x15F);
            group = grp[oldGroup + 2];
            id_ = kCharaGroups[which][oldGroup];
            special_ = 0;
            if ((which == 1 && oldGroup == 5) || id_ < 0) special_ = 1;
            if (!special_) {
            for (int j = 0; j < 5; j++) {
            int res = 0x1422;
            int unlocked = fn_8023D844(id_, j + 1);
            if (pd->unlocked[unlocked] == 1) res = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(pd, unlocked), 0);
            SpriteAnimParamBlock_SetAnimParamCached(group, kCharaParams[j], res);
            }
            } else {
            int res = 0x1422;
            if (pd->unlocked[fn_8023D844(0, 0)] == 1) res = 0x140A;
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x13B9, res);
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BA, 0x1ECD);
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BB, 0x1ECD);
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BC, 0x1ECD);
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x13BD, 0x1ECD);
            }
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x1D23, kCharaFrames[which][oldGroup][0]);
            SpriteAnimParamBlock_SetAnimParamCached(group, 0x1D24, kCharaFrames[which][oldGroup][1]);
            SetCharaGroupForPlayer(grp[field24 + 2], which, field24, pd);
        }
    }
}

clFlowCCCharaItem::clFlowCCCharaItem(int which) : which(which), field20(0), field24(0), field28(0), first(1), resId(0x13B9), paramId(0x1E1D) {
    PlayerData *pd = &g_playerData;
    for (int i = 0; i < 11; i++) grp[i] = 0;
    SpriteGroup_CreateOrInit(&grp[0], kCharaGrp0, 0, kCharaGrpPos[0].x, kCharaGrpPos[0].y);
    SpriteGroup_CreateOrInit(&grp[1], kCharaGrp1, 0, kCharaGrpPos[1].x, kCharaGrpPos[1].y);
    SpriteGroup_CreateOrInit(&grp[8], kCharaGrp2, 1, kCharaGrpPos[8].x, kCharaGrpPos[8].y);
    SpriteGroup_CreateOrInit(&grp[9], kCharaGrp3, 1, kCharaGrpPos[9].x, kCharaGrpPos[9].y);
    SpriteGroup_CreateOrInit(&grp[10], kCharaGrp4, 1, kCharaGrpPos[10].x, kCharaGrpPos[10].y);
    SpriteGroup_CreateOrInit(&grp[2], kCharaGrp5, 0, kCharaGrpPos[2].x, kCharaGrpPos[2].y);
    SpriteGroup_CreateOrInit(&grp[3], kCharaGrp6, 0, kCharaGrpPos[3].x, kCharaGrpPos[3].y);
    SpriteGroup_CreateOrInit(&grp[4], kCharaGrp7, 0, kCharaGrpPos[4].x, kCharaGrpPos[4].y);
    SpriteGroup_CreateOrInit(&grp[5], kCharaGrp8, 0, kCharaGrpPos[5].x, kCharaGrpPos[5].y);
    SpriteGroup_CreateOrInit(&grp[6], kCharaGrp9, 0, kCharaGrpPos[6].x, kCharaGrpPos[6].y);
    SpriteGroup_CreateOrInit(&grp[7], kCharaGrp10, 0, kCharaGrpPos[7].x, kCharaGrpPos[7].y);
    SpriteAnimSample out;
    fn_8019FF8C(*grp[2], 0x13B9, &out);
    slots[0][0] = out.x;
    fn_8019FF8C(*grp[2], 0x13BA, &out);
    slots[0][1] = out.x;
    fn_8019FF8C(*grp[2], 0x13BB, &out);
    slots[0][2] = out.x;
    fn_8019FF8C(*grp[2], 0x13BC, &out);
    slots[0][3] = out.x;
    fn_8019FF8C(*grp[2], 0x13BD, &out);
    slots[0][4] = out.x;
    fn_8019FF8C(*grp[3], 0x13B9, &out);
    slots[1][0] = out.x;
    fn_8019FF8C(*grp[3], 0x13BA, &out);
    slots[1][1] = out.x;
    fn_8019FF8C(*grp[3], 0x13BB, &out);
    slots[1][2] = out.x;
    fn_8019FF8C(*grp[3], 0x13BC, &out);
    slots[1][3] = out.x;
    fn_8019FF8C(*grp[3], 0x13BD, &out);
    slots[1][4] = out.x;
    for (int i = 0; i < 6; i++) {
        int group = i + 2;
        Sprite **sprites = grp[group];
        SetCharaGroup(sprites, this->which, i);
    }
    int i;
    for (i = 0; i < 8; i++) text[i] = new TextMgr();
    text[0]->visible = 1; text[1]->visible = 1;
    text[2]->visible = 0; text[3]->visible = 0; text[4]->visible = 0;
    text[5]->visible = 0; text[6]->visible = 0; text[7]->visible = 0;
    TexMgr_SetTexture(text[0], lbl_806DB818, this->which == 0 ? 3 : 4);
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x80, -1));
    TexMgr_SetTexture(text[2], GetTextureByIdAndLang(0x79, -1));
    for (int group = 0; group < 13; group++) {
        if (group != 1 && group != 9) {
            for (int j = 0; j < 5; j++) if (pd->unlocked[fn_8023D844(group, j + 1)] == 1) ++field20;
        }
    }
    if (pd->unlocked[fn_8023D844(0, 0)] == 1) ++field20;
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x7F, -1), field20, 56);
    TexMgr_SetTexture(text[4], lbl_806DB82C);
    TexMgr_SetTexture(text[5], lbl_806DB82C);
    TexMgr_SetTexture(text[6], lbl_806DB82C);
    TexMgr_SetTexture(text[7], lbl_806DB82C);
    text[0]->scale = -6.0f; text[2]->scale = -1.0f; text[1]->scale = -2.0f;
    text[3]->scale = -1.0f; text[4]->scale = -1.0f;
    fn_801F93EC(text[0], kCharaTextPos[0].x, kCharaTextPos[0].y);
    fn_801F93EC(text[1], kCharaTextPos[1].x, kCharaTextPos[1].y);
    fn_801F93EC(text[2], kCharaTextPos[2].x, kCharaTextPos[2].y);
    fn_801F93EC(text[3], kCharaTextPos[3].x, kCharaTextPos[3].y);
    fn_801F93EC(text[4], kCharaTextPos[4].x, kCharaTextPos[4].y);
    fn_801F93EC(text[5], kCharaTextPos[5].x, kCharaTextPos[5].y);
    fn_801F93EC(text[6], kCharaTextPos[6].x, kCharaTextPos[6].y);
    fn_801F93EC(text[7], kCharaTextPos[7].x, kCharaTextPos[7].y);
    if (field20 == 0) {
        TexMgr_SetTexture(text[4], lbl_806DB824);
        TexMgr_SetTexture(text[5], lbl_806DB824);
        TexMgr_SetTexture(text[6], lbl_806DB824);
        TexMgr_SetTexture(text[7], lbl_806DB824);
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], resId, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(grp[1], paramId, 0x1ECD);
    }
    if (isJapanese()) {
        fn_801F93EC(text[3], lbl_806DB828, kItemTextPos[3].y);
        fn_801F93EC(text[0], lbl_806DB780.x, lbl_806DB780.y);
        text[1]->scale = lbl_806DB830;
    }
    for (i = 0; i < 8; i++) fn_801F8E90(text[i]);
    field28 = -1;
    Select(1);
}

static inline void PositionOffsetText(TextMgr *text, const Vec2 &position, float offset, float slide) {
    float x = offset + position.x;
    fn_801F93EC(text, x + slide, position.y);
}

int clFlowCCDate::Update() {
    InputPlayer *pl = InputMgr_GetPlayer(GetInputManager(), 0);
    UpdateSlide();
    if (IsIdle() == 1) {
        unsigned char changed = 0;
        if (pl->v5() >= lbl_806DB7A0 && field1E == 0) {
            field1E = 1;
            if (field1C == 0) {
                field1C = 1;
                changed = 1;
                SpriteAnimParamBlock_Reload(grp[2], 0x166);
                SpriteAnimParamBlock_Reload(grp[3], 0x163);
            } else {
                field1C = 0;
                changed = 1;
                SpriteAnimParamBlock_Reload(grp[2], 0x165);
                SpriteAnimParamBlock_Reload(grp[3], 0x164);
            }
        }
        if (changed) fn_801FE390();
        if (pl->v5() <= lbl_806DB854) field1E = 0;
        int delta = input_state()->pageInput;
        unsigned char pageChanged = 0;
        if (delta < 0 && field1D == 0) {
            field1D = 1;
            pageChanged = 1;
            SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x15F6, 0x15F8);
            SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x15F9, 0x15F7);
            SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x1ECD, 0x15D2);
            SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x15D2, 0x1ECD);
        } else if (delta > 0 && field1D == 1) {
            field1D = 0;
            pageChanged = 1;
            SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x15F8, 0x15F6);
            SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x15F7, 0x15F9);
            SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x15D2, 0x1ECD);
            SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x1ECD, 0x15D2);
        }
        if (pageChanged) { fn_801FE390(); field20 = 120; }
    } else {
        for (int i = 0; i < 6; i++) {
            Sprite **group = grp[i];
            if (group != 0) { float x = kDateGrpPos[i].x; (*group)->x = x + slide; }
        }
        for (int i = 0; i < 12; i++) {
            const Vec2 &p = kDateTextPos[i];
            fn_801F93EC(text[i], p.x + slide, p.y);
        }
        if (isJapanese()) {
            fn_801F93EC(text[0], lbl_806DB780.x + slide, lbl_806DB780.y);
            PositionOffsetText(text[11], kDateTextPos[11], lbl_806DB858, slide);
        }
        fn_8023CD3C(indicator, lbl_806DB85C + slide, lbl_806DB860);
        fn_8023CD24(indicator, lbl_806DB85C + slide, lbl_806DB864);
        fn_8023CCF8(indicator, lbl_806DB868 + slide, lbl_806DB86C);
        fn_8023CCCC(indicator, lbl_806DB868 + slide, lbl_806DB870);
    }
    if (field20 > 105) {
        unsigned char alpha = lbl_806DB874 - lbl_806DB874 * ((field20 - lbl_806DB878) / lbl_806DB858);
        text[11]->color = 0xFFFFFF00 | alpha;
    } else if (field20 > 15) {
        text[11]->color = 0xFFFFFFFF;
    } else if (field20 > 0) {
        unsigned char alpha = lbl_806DB874 * (field20 / lbl_806DB858);
        text[11]->color = 0xFFFFFF00 | alpha;
    } else {
        text[11]->color = 0xFFFFFF00;
    }
    if (field20 > 0) --field20;
    for (int i = 0; i < 6; i++) {
        if (grp[i] != 0) Sprite_AdvanceAnim(*grp[i], 0.0165f);
    }
    if (indicator != 0) fn_8023CDA8(indicator);
}


clFlowCCDate::clFlowCCDate() : field1C(1), field1D(1), field1E(0), field20(0), indicator(0) {
    int i;
    indicator = new clIndicator(0x75, 0x4A, 0x1875, 0x1875, 6);
    fn_8023CD3C(indicator, lbl_806DB85C, lbl_806DB860);
    fn_8023CD24(indicator, lbl_806DB85C, lbl_806DB864);
    fn_8023CCF8(indicator, lbl_806DB868, lbl_806DB86C);
    fn_8023CCCC(indicator, lbl_806DB868, lbl_806DB870);
    fn_8023CEB4(indicator);
    fn_8023CFD4(indicator);
    grp[0] = 0; grp[1] = 0; grp[2] = 0;
    grp[3] = 0; grp[4] = 0; grp[5] = 0;
    PlayerData *pd = &g_playerData;
    field1C = pd->datePage;
    field1D = pd->dateMode;
    SpriteGroup_CreateOrInit(&grp[0], kDateGrp0, 0, kDateGrpPos[0].x, kDateGrpPos[0].y);
    SpriteGroup_CreateOrInit(&grp[1], kDateGrp1, 0, kDateGrpPos[1].x, kDateGrpPos[1].y);
    if (field1C == 1) {
        SpriteGroup_CreateOrInit(&grp[2], kDateGrp2a, 0, kDateGrpPos[2].x, kDateGrpPos[2].y);
        SpriteGroup_CreateOrInit(&grp[3], kDateGrp3a, 0, kDateGrpPos[3].x, kDateGrpPos[3].y);
    } else {
        SpriteGroup_CreateOrInit(&grp[2], kDateGrp2b, 0, kDateGrpPos[2].x, kDateGrpPos[2].y);
        SpriteGroup_CreateOrInit(&grp[3], kDateGrp3b, 0, kDateGrpPos[3].x, kDateGrpPos[3].y);
    }
    SpriteGroup_CreateOrInit(&grp[4], kDateGrp4, 0, kDateGrpPos[4].x, kDateGrpPos[4].y);
    SpriteGroup_CreateOrInit(&grp[5], kDateGrp5, 0, kDateGrpPos[5].x, kDateGrpPos[5].y);
    if (field1D == 1) {
        SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x15F9, 0x15F7);
        SpriteAnimParamBlock_SetAnimParamCached(grp[5], 0x15D2, 0x1ECD);
    } else {
        SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x15F8, 0x15F6);
        SpriteAnimParamBlock_SetAnimParamCached(grp[4], 0x15D2, 0x1ECD);
    }
    for (i = 0; i < 12; i++) text[i] = new TextMgr();
    text[0]->visible = 1; text[1]->visible = 1; text[2]->visible = 1;
    text[3]->visible = 1; text[4]->visible = 1; text[5]->visible = 1;
    text[6]->visible = 0; text[7]->visible = 0; text[8]->visible = 0;
    text[9]->visible = 0; text[10]->visible = 0; text[11]->visible = 0;
    TexMgr_SetTexture(text[0], lbl_806DB87C);
    TexMgr_SetTexture(text[1], GetTextureByIdAndLang(0x76, -1));
    fn_801F9014(text[2], pd);
    TexMgr_SetTexture(text[3], GetTextureByIdAndLang(0x77, -1), pd->cardCount);
    TexMgr_SetTexture(text[4], GetTextureByIdAndLang(0x78, -1), GetCoinMilage(pd));
    TexMgr_SetTexture(text[5], get_title_name_global(SINGLETON_INSTANCE(lbl_806D10A0)));
    TexMgr_SetTexture(text[6], GetTextureByIdAndLang(0x79, -1));
    TexMgr_SetTexture(text[7], GetTextureByIdAndLang(0x7A, -1));
    TexMgr_SetTexture(text[8], GetTextureByIdAndLang(0x7B, -1));
    TexMgr_SetTexture(text[9], GetTextureByIdAndLang(0x7C, -1));
    TexMgr_SetTexture(text[10], GetTextureByIdAndLang(0x7D, -1));
    TexMgr_SetTexture(text[11], GetTextureByIdAndLang(0x4B, -1));
    text[0]->scale = -6.0f;
    text[6]->scale = -1.0f;
    text[11]->scale = !isJapanese() ? -1.0f : lbl_806DB880;
    for (int i = 0; i < 12; i++) fn_801F93EC(text[i], kDateTextPos[i].x, kDateTextPos[i].y);
    if (isJapanese()) {
        fn_801F93EC(text[0], lbl_806DB780.x, lbl_806DB780.y);
        fn_801F93EC(text[11], lbl_806DB858 + kDateTextPos[11].x, kDateTextPos[11].y);
        fn_801F93D0(text[5], lbl_806DB884, lbl_806DB884);
    }
    for (i = 0; i < 12; i++) fn_801F8E90(text[i]);
}

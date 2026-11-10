/* this unit defines the pool objects that anon_8021F088_private.h declares under other types */
#define ANON_8021F088_POOL_OWNER
#include "game/anon_8021F088_nm_8021F508_private.h"

/* Coin mileage animation, display poses, and diagnostic resource pool. */
static const float kCoinAnimation[258] = {
    0.0f, 0.0f, 0.0f, 1.0f, 0.7f, 0.9f, 0.0f, 0.0f,
    500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f,
    4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f,
    5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f,
    2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f,
    3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f,
    500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f,
    4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f,
    5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f,
    2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f,
    3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f,
    500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f,
    4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f,
    1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f,
    5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f,
    2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f,
    3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f,
    500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f,
    4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f,
    5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f,
    2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f,
    3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f,
    500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f,
    4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f,
    1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f,
    5000.0f, 83.333336f,
};
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define kBaseName lbl_803C6C18
#define kCounters lbl_803C6B70
#define kDigitPositions lbl_803C6BD4
#define kDigits lbl_803C6BC4
#define kLastItem lbl_803C6C70
#define kLineY lbl_803C6A24
#define kNextCoin lbl_803C6C2C
#define kNoItem lbl_803C6C58
#define kOrigin CoinResultScene_Init_rodata_803C6A18
#define kSceneName lbl_803C6C04
#define kWork lbl_803C6B84
#endif
SHARED_STATIC const float kOrigin[3] = {
    0.0f, 0.0f, 0.0f,
};
SHARED_STATIC const float kLineY[5] = {
    102.5f, 161.5f, 221.5f, 299.5f, 265.5f,
};
static const ItemPose kItemPoses[13] = {
    {335.0f, 272.0f, {28.0f, -31.0f, -12.0f}, 0.0125f},
    {340.0f, 281.0f, {30.0f, -40.0f, -14.0f}, 0.013f},
    {346.0f, 257.0f, {26.0f, -28.0f, -8.0f}, 0.014f},
    {335.0f, 265.0f, {26.0f, -30.0f, -12.0f}, 0.013f},
    {329.0f, 277.0f, {25.0f, -34.0f, -12.0f}, 0.016f},
    {327.0f, 295.0f, {30.0f, -35.0f, -14.0f}, 0.0155f},
    {318.0f, 300.0f, {27.0f, -35.0f, -12.0f}, 0.013f},
    {323.0f, 277.0f, {25.0f, -34.0f, -14.0f}, 0.016f},
    {323.0f, 289.0f, {25.0f, -32.0f, -12.0f}, 0.0145f},
    {332.0f, 280.0f, {29.0f, -36.0f, -14.0f}, 0.0125f},
    {324.0f, 279.0f, {25.0f, -28.0f, -10.0f}, 0.0145f},
    {322.0f, 284.0f, {29.0f, -30.0f, -14.0f}, 0.0125f},
    {347.0f, 273.0f, {25.0f, -34.0f, -12.0f}, 0.015f},
};
// Zero-valued aggregate defaults from the original resource pool.
SHARED_STATIC const int kCounters[5] = {
    0, 0, 0, 0, 0,
};
SHARED_STATIC const int kWork[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
SHARED_STATIC const int kDigits[4] = {
    0, 0, 0, 0,
};
SHARED_STATIC const float kDigitPositions[12] = {
    268.5f, 213.5f, 158.5f, 103.5f, 360.5f, 305.5f, 250.5f, -100.0f,
    375.0f, 328.0f, 286.0f, 244.0f,
};
SHARED_STATIC const char kSceneName[] = "clCSSceneCoinMilage";
SHARED_STATIC const char kBaseName[] = "clSceneInterface";
SHARED_STATIC const char kNextCoin[] = "Next coin is %d, num : %d, afterCoin : %d\n";
SHARED_STATIC const char kNoItem[] = "Can't get item struct.";
SHARED_STATIC const char kLastItem[] = "Have last item.";
static const char kItemError[] = "Get Item Scene Error!!, %s - %d\n";
static const char kSourceName[] = "csSceneCoinMilage.cpp";

void ItemWnd::Setup(int n, MilageItem *e) {
    if (e != 0) {
        coins = n;
        entry = e;
        state = 1;
        timer = 0;
        sub = 0;
        if (e->type == 1) {
            itemId = fn_8021620C();
            if (itemId <= 0) {
                DebugPrintf(kItemError, kSourceName, 950);
                state = 0;
                return;
            }
            KartPose *pose = fn_8013BE98(itemId);
            if (kart) {
                delete kart;
                kart = 0;
            }
            kart = new Model(ItemRes_LookupByKey_Thunk(itemId), 1);
            fn_8013D738(kart, lbl_806DB190, lbl_806DB194);
            fn_8013D660(kart, lbl_806DB1CC, lbl_806DB1D0);
            fn_8013D634(kart, lbl_806DB1D4 * pose->pos[0], lbl_806DB1D4 * pose->pos[1], lbl_806DB1D4 * pose->pos[2]);
            fn_8013D59C(kart, lbl_806DB1D8 * pose->rot[0], lbl_806DB1D8 * pose->rot[1], lbl_806DB1D8 * pose->rot[2]);
            float s = lbl_806DB1D4 * pose->scale;
            fn_8013D608(kart, s, s, s);
            TextSprite tmp;
            tmp.visible = 0;
            TexMgr_SetTexture(&tmp, fn_8023DAA8(itemId));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 0));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 1));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 2));
            TexMgr_Apply(&tmp);
        } else if (e->type == 3 || e->type == 4) {
            int k = fn_80216960(entry->id);
            if (item) {
                delete item;
                item = 0;
            }
            item = new ItemModel(k, 2, 0, 1);
            fn_8021A7BC(item, kItemPoses[k].x, kItemPoses[k].y);
            fn_8021A578(item, lbl_806DB1D8 * kItemPoses[k].rot[0], lbl_806DB1D8 * kItemPoses[k].rot[1],
                        lbl_806DB1D8 * kItemPoses[k].rot[2]);
            fn_8021A660(item, kItemPoses[k].scale, kItemPoses[k].scale, kItemPoses[k].scale);
            fn_8021A430(item, lbl_806DB190);
        }
    }
}


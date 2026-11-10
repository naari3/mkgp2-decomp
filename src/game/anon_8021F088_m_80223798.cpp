#include "game/anon_8021F088_private.h"

clCSSceneCoinMilage::clCSSceneCoinMilage()
    : numCoins(0), model(new Model(CoinResultScene_Init_rodata_803C6CD0, 1)), x3d0(0), perfectCoins(0), hasPerfect(0), hasBonus1(0),
      hasBonus2(0), counter(0), itemIndex(-1), state(0), sub(0), timer(0), wait(0), sum(0), wnd(0), next(0) {
    if (!IsCardValid()) {
        state = 8;
        done = 1;
        return;
    }
    if (g_cupId >= 9) {
        AddCoinsFromExtraStage();
    } else if (g_gameMode != 1) {
        CalcEarnedCoins();
    }
    fn_8021651C(g_playerData);
    AddCoinMilage(g_playerData, GetEarnedCoins());
    SetInput(1);
    ItemDisplay_GetOrCreate();
    {
        ItemDisplay *d = ItemDisplay_GetOrCreate();
        d->mode = 2;
    }
    fn_8013DBF8();
    lines[0] = 0;
    lines[1] = 0;
    lines[2] = 0;
    lines[3] = 0;
    perfect = 0;
    for (int i = 0; i < 30; i++) {
        coins[i].x = (rand() % 6400) / lbl_806DB250;
        coins[i].y = lbl_806DB2B4;
        coins[i].z = (rand() % 500) / lbl_806DB2B8;
        coins[i].vy = lbl_806DB2C0 * (rand() % 300) + lbl_806DB2BC;
        coins[i].rot = rand() % 360;
        coins[i].bounced = 0;
        coins[i].vx = lbl_806DB190;
        float v = lbl_806DB2C0 * (rand() % 1600 - 800);
        if (v >= lbl_806DB190) {
            v += lbl_806DB194;
        } else {
            v -= lbl_806DB194;
        }
        coins[i].vrot = v;
    }
    int c = fn_802161CC();
    counter = c;
    x3d0 = c;
    milage = GetCoinMilage(g_playerData);
    perfectCoins = fn_802161F4();
    earned = fn_802161FC();
    if (g_gameMode == 1) {
        bonus1 = fn_802161DC();
        bonus2 = fn_802161D4();
    } else if (g_gameMode == 0) {
        bonus1 = fn_802161EC();
        bonus2 = GetCoinCount();
    } else {
        bonus1 = fn_802161EC();
        bonus2 = -1;
    }
    if (bonus1 >= 0) {
        hasBonus1 = 1;
    }
    if (bonus2 >= 0) {
        hasBonus2 = 1;
    }
    if (perfectCoins > 0) {
        hasPerfect = 1;
    }
    fn_8013D59C(model, lbl_806DB1D8 * CoinResultScene_Init_rodata_803C6A18[0], lbl_806DB1D8 * CoinResultScene_Init_rodata_803C6A18[1], lbl_806DB1D8 * CoinResultScene_Init_rodata_803C6A18[2]);
    fn_8013D608(model, lbl_806DB2C4, lbl_806DB2C4, lbl_806DB2C4);
    fn_8013D4B0(model, lbl_806DB194);
    fn_8013D738(model, lbl_806DB190, lbl_806DB194);
    FadeObj *fill = new FilterNode;
    fill->tracks[0].Set(lbl_806DB194, lbl_806DB190, lbl_806DB198);
    nodes.push_back(fill);
    itemIndex = fn_80216988(x3d0);
    wnd = new ItemWnd;
    next = new NextWnd;
    TextSprite tmp;
    tmp.visible = 1;
    TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6C, -1));
    TexMgr_Apply(&tmp);
    TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x72, -1));
    TexMgr_Apply(&tmp);
    if (g_gameMode == 1) {
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x71, -1));
        TexMgr_Apply(&tmp);
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x70, -1));
        TexMgr_Apply(&tmp);
    } else {
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6E, -1));
        TexMgr_Apply(&tmp);
        TexMgr_SetTexture(&tmp, GetTextureByIdAndLang(0x6F, -1));
        TexMgr_Apply(&tmp);
    }
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_8020F3F0();
    fn_8020F38C(0);
}

#pragma inline_max_size(240)

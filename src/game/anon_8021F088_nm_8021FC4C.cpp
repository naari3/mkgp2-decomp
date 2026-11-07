#include "game/anon_8021F088_private.h"
#include "game/singleton.h"

#pragma auto_inline off
void clCSSceneCoinMilage::StateLines() {
    bool pressed = SINGLETON_INSTANCE(g_pInputState)->held == 1;
    switch (sub) {
    case 0:
        if (timer == 10) {
            lines[0] = new clGetCoinLine(GetTextureByIdAndLang(0x6C, -1), earned, lbl_803C6A24[0], model);
            nodes.push_back((FadeObj *&)lines[0]);
        }
        if (timer >= 140) {
            timer = 0;
            sub = hasPerfect == 1 ? 1 : 2;
        }
        break;
    case 1:
        if (timer == 1) {
            perfect = new clCoinPerfect(perfectCoins);
            nodes.push_back((FadeObj *&)perfect);
            lines[0]->Bump(perfectCoins);
        }
        if (timer == 75) {
            perfect->tracks[0].Set(lbl_806DB194, lbl_806DB190, lbl_806DB1F8);
        }
        if (timer >= 100) {
            timer = 0;
            sub++;
        }
        break;
    case 2:
        if (timer == 1) {
            if (hasBonus1 == 0) {
                timer = 0;
                sub = hasBonus2 == 1 ? 3 : 4;
                break;
            }
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x70, -1) : GetTextureByIdAndLang(0x6E, -1);
            lines[1] = new clGetCoinLine(tex, bonus1, lbl_803C6A24[1], model);
            lines[1]->rot = ((clGetCoinLine *)nodes.at(1))->rot;
            nodes.push_back((FadeObj *&)lines[1]);
        }
        if (timer >= 140) {
            timer = 0;
            sub = hasBonus2 == 1 ? 3 : 4;
        }
        break;
    case 3:
        if (timer == 1) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x71, -1) : GetTextureByIdAndLang(0x6F, -1);
            lines[2] = new clGetCoinLine(tex, bonus2, lbl_803C6A24[2], model);
            lines[2]->rot = ((clGetCoinLine *)nodes.at(1))->rot;
            nodes.push_back((FadeObj *&)lines[2]);
        }
        if (timer >= 140) {
            timer = 0;
            sub++;
        }
        break;
    case 4:
        if (timer == 1) {
            int n = Total();
            lines[3] = new clGetSumLine(n, hasPerfect, lbl_803C6A24[hasBonus2 == 1 ? 3 : 4]);
            nodes.push_back((FadeObj *&)lines[3]);
        }
        if (timer >= 140) {
            timer = 0;
            sub++;
        }
        break;
    case 5:
        if (timer >= 60 || pressed == 1) {
            timer = 0;
            wait = 0;
            sub = 0;
            state = 3;
        }
        return;
    }
    if (SINGLETON_INSTANCE(g_pInputState)->held == 1) {
        if (lines[0] == 0) {
            lines[0] = new clGetCoinLine(GetTextureByIdAndLang(0x6C, -1), earned, lbl_803C6A24[0], model);
            nodes.push_back((FadeObj *&)lines[0]);
        }
        if (hasPerfect == 1) {
            if (perfect == 0) {
                lines[0]->Bump(perfectCoins);
            } else {
                perfect->tracks[0].Set(lbl_806DB190, lbl_806DB190, lbl_806DB194);
            }
        }
        if (hasBonus1 == 1 && lines[1] == 0) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x70, -1) : GetTextureByIdAndLang(0x6E, -1);
            lines[1] = new clGetCoinLine(tex, bonus1, lbl_803C6A24[1], model);
            lines[1]->rot = lines[0]->rot;
            nodes.push_back((FadeObj *&)lines[1]);
        }
        if (hasBonus2 == 1 && lines[2] == 0) {
            const char *tex = g_gameMode == 1 ? GetTextureByIdAndLang(0x71, -1) : GetTextureByIdAndLang(0x6F, -1);
            lines[2] = new clGetCoinLine(tex, bonus2, lbl_803C6A24[2], model);
            lines[2]->rot = lines[0]->rot;
            nodes.push_back((FadeObj *&)lines[2]);
        }
        if (lines[3] == 0) {
            int n = Total();
            lines[3] = new clGetSumLine(n, hasPerfect, lbl_803C6A24[hasBonus2 == 1 ? 3 : 4]);
            nodes.push_back((FadeObj *&)lines[3]);
        }
        clGetCoinLine *l;
        int i;
        for (i = 0; i < 4; i++) {
            l = lines[i];
            if (l != 0) {
                l->tracks[3].Set(lbl_806DB21C, lbl_806DB21C, lbl_806DB1E0);
                l->timer = 80;
                l->value += l->add;
                l->add = 0;
                l->flash = 0;
            }
        }
        timer = 0;
        wait = 0;
        sub = 0;
        state = 3;
    }
}
#pragma auto_inline reset


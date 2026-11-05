#include "game/MenuDispatch_private.h"
#pragma fp_contract off
extern "C" int MenuScene_Dispatch(MenuOwnerView *self) {
    if (self->finished) return 4;
    if (GetInput()) CGameCoin_ProcessInput(GetInput());
    fn_801A1280();
    fn_8020F290();
    fn_801DAEC0();
    fn_801DABFC();
    int next = -1;
    if (self->child) next = self->child->Update();
    if (next != -1) {
        GXDrawDone();
        delete self->child;
        self->child = 0;
        fn_80121210();
        clRom_PurgeAll();
        switch (next) {
        case 2:
            self->child = new MenuEntryScene;
            break;
        case 7:
            self->child = new MenuTitleScene;
            break;
        case 6:
            self->child = new MenuAttractScene;
            break;
        case 49:
            self->child = new MenuUnknown8020E0E0Scene;
            break;
        case 48:
            self->child = new MenuUnknown8020D850Scene;
            break;
        case 9:
            self->child = new MenuCardScene;
            break;
        case 11:
            self->child = new MenuClassScene;
            break;
        case 13:
            self->child = new MenuFrameSelectionScene;
            break;
        case 15:
            self->child = new MenuKartScene;
            break;
        case 19:
            self->child = new MenuFigureScene;
            break;
        case 21:
            self->child = new MenuCupScene;
            break;
        case 27:
            self->child = new MenuRoundScene;
            break;
        case 23:
            self->child = new MenuCourseScene;
            break;
        case 25:
            self->child = new MenuCourseScene;
            break;
        case 34:
            self->child = new MenuItemSelectScene;
            break;
        case 33:
            self->child = new MenuItemScene;
            break;
        case 37:
            self->child = new MenuGpPleaseScene;
            break;
        case 38:
            self->child = new MenuTaPleaseScene;
            break;
        case 39:
            self->child = new Menuranking_displayScene;
            break;
        case 42: self->finished = 1; break;
        case 0: case 1: default: break;
        }
    }
    if (lbl_806CFD60 != -1) {
        if (lbl_806D17F8) Sprite_AdvanceAnim(lbl_806D17F8, lbl_806D9924);
        if (lbl_806D17FC) {
            if (lbl_806CFD60 == 0) {
                if (!Sprite_AdvanceAnim(lbl_806D17FC, lbl_806D9924)) {
                    Sprite_SetupAnim(lbl_806D17FC, 0x4C, 1, 0);
                    fn_8019FF6C(lbl_806D17FC, 1);
                    ++lbl_806CFD60;
                }
            } else if (lbl_806CFD60 == 1) Sprite_AdvanceAnim(lbl_806D17FC, lbl_806D9924);
        }
    }
    if (lbl_806D1800) {
        unsigned char active = Sprite_AdvanceAnim(lbl_806D1800, lbl_806D9924);
        if (lbl_806D1808 == 0 && !active) {
            Sprite_SetupAnim(lbl_806D1800, 0x1DD, 0, 0);
            Sprite_SetAnimParam(lbl_806D1800, 0x1AD4, (short)lbl_806D1804);
            fn_801A0550(lbl_806D1800);
            Sprite *sprite = lbl_806D1800;
            sprite->x = lbl_806D98F8;
            sprite->y = lbl_806D98FC;
            fn_8019FF6C(lbl_806D1800, 1);
            ++lbl_806D1808;
        }
        if (lbl_806D1808 == 2 && !active) {
            Sprite_Destroy(lbl_806D1800, 1);
            lbl_806D1800 = 0;
            lbl_806D1808 = 0;
        }
    }
    if (lbl_806D180C) {
        unsigned char active = Sprite_AdvanceAnim(lbl_806D180C, lbl_806D9924);
        if (lbl_806D1818 == 0 && !active) {
            if (lbl_806D1814 == 13) {
                Sprite_SetupAnim(lbl_806D180C, 0x167, 1, 0);
                Sprite_SetAnimParam(lbl_806D180C, 0x1D3E, lbl_806D181A);
            }
            if (lbl_806D1814 == 21) {
                if (lbl_806D1819) Sprite_SetupAnim(lbl_806D180C, 0x18E, 1, 0);
                else Sprite_SetupAnim(lbl_806D180C, 0x184, 1, 0);
            }
            fn_8019FF6C(lbl_806D180C, 1);
            ++lbl_806D1818;
        }
        if (lbl_806D1818 == 2) {
            ++lbl_806D1810;
            if (lbl_806D1814 == 13 && !active) {
                Sprite_SetupAnim(lbl_806D180C, 0x150, 1, 0);
                Sprite *sprite = lbl_806D180C;
                sprite->x = lbl_806D98E8;
                sprite->y = lbl_806D9928;
                fn_8019FF6C(lbl_806D180C, 1);
            }
            if (lbl_806D1814 == 21) {
                int frame = lbl_806D1810;
                float scale;
                float y;
                y = lbl_806D98EC + lbl_806D9930 * (float)frame;
                scale = lbl_806D98E0 + lbl_806D992C * (float)frame;
                lbl_806D180C->y = y;
                *(float *)((char *)lbl_806D180C + 0x18) = scale;
                if (lbl_806D1810 >= 10) ++lbl_806D1818;
            }
            if (lbl_806D1814 == 27) {
                *(float *)((char *)lbl_806D180C + 0x18) = lbl_806D9934 * (float)lbl_806D1810;
                if (lbl_806D1810 >= 10) ++lbl_806D1818;
            }
        }
        if (lbl_806D1818 == 4 && !active) {
            Sprite_Destroy(lbl_806D180C, 1);
            lbl_806D180C = 0;
            lbl_806D1810 = 0;
            lbl_806D1818 = 0;
        }
    }
    fn_801B7EF8();
    if (lbl_806D1820) {
        int coins = CreditMgr_GetCoinCount(0, lbl_806D1824);
        int cost = CreditMgr_GetCoinsPerCredit(lbl_806D1824);
        int coinTens = coins / 10;
        int coinUnits = coins % 10;
        int costTens = cost / 10;
        int costUnits = cost % 10;
        if (cost != -1) {
            if (coinTens != 0) {
                *lbl_806D1828 = 0x1D63 + coinTens;
                *lbl_806D182C = 0x1D63 + coinUnits;
            } else {
                *lbl_806D1828 = -1;
                *lbl_806D182C = 0x1D63 + coinUnits;
            }
            if (costTens != 0) {
                *lbl_806D1830 = 0x1D63 + costTens;
                *lbl_806D1834 = 0x1D63 + costUnits;
            } else {
                *lbl_806D1830 = 0x1D63 + costUnits;
                *lbl_806D1834 = -1;
            }
        }
    }
    if (lbl_806D184C > 0) {
        lbl_806D1848 += 0.125;
        if (lbl_806D1848 >= 1.0f) {
            lbl_806D1848 = 1.0f;
            lbl_806D184C = 0;
        }
    }
    if (lbl_806D184C < 0) {
        lbl_806D1848 -= 0.08333333333333333;
        if (lbl_806D1848 <= 0.0f) {
            lbl_806D1848 = 0.0f;
            lbl_806D184C = 0;
        }
    }
    if (lbl_806D1848 > lbl_806D9890) {
        if (lbl_806D1840) Sprite_AdvanceAnim(lbl_806D1840, lbl_806D9924);
        if (lbl_806D1844) Sprite_AdvanceAnim(lbl_806D1844, lbl_806D9924);
    }
    if (lbl_806D184F) {
        if (lbl_806D1858 < 5) ++lbl_806D1858;
    }
    if (lbl_806D1850) {
        if (lbl_806D1858 > 0) --lbl_806D1858;
        if (lbl_806D1858 == 0) lbl_806D1850 = 0;
    }
    return -2;
}

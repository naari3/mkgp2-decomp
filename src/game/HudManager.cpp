/*
 * HUD manager part factory and draw passes @ 0x80253294..0x80253658.
 *
 * The manager (see HUD_Init.c) owns a FlowSceneList at +0x00 and 23 HUD
 * part slots at +0x10. CreatePart builds the part for one slot, DrawMasked
 * draws the parts selected by a bit mask, DrawAll draws everything.
 */

#include "game/HudManager.h"

extern "C" {
extern int g_gameMode;
HudPart *fn_8022B9FC(int mode, int layer);
HudPart *fn_8023FB4C(int mode, int layer);
HudPart *fn_802499F4(int layer);
HudPart *fn_80246B78(int mode, int layer);
HudPart *fn_802524C8(int layer);
HudPart *fn_80215DE4(int layer);
HudPart *fn_80252D90(int layer);
HudPart *fn_80219900(int mode, int layer);
HudPart *fn_8023BB6C(int layer);
HudPart *fn_80243A24(int layer);
HudPart *fn_80245AC4(int layer);
HudPart *fn_80246150(int layer);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
unsigned char Sci2Card_GetByteFlag1224(void);
HudTask *fn_80254330(FlowSceneList *list, int id);
void fn_8011F870(int flags);
void fn_8011F994(int mode);
void fn_801493B0(HudTask *task);
void fn_8011FAB8(void);
}

HudPart *HudManager::CreatePart(int idx, unsigned char force) {
    int gm = g_gameMode;
    switch (idx) {
    case 0:
        if (force) {
            return fn_8022B9FC(mode, 0);
        }
        if (gm == 2) {
            return fn_8022B9FC(mode, 0);
        }
        return 0;
    case 6:
        return fn_802524C8(1);
    case 3:
        return fn_8023FB4C(gm, 1);
    case 5:
        return fn_80246B78(gm, 1);
    case 1:
        return 0;
    case 2:
        return 0;
    case 10:
        return fn_80219900(gm, 1);
    case 11:
        if (force) {
            return fn_8023BB6C(1);
        }
        return fn_8023BB6C(1);
    case 4:
        if (force) {
            return fn_802499F4(1);
        }
        if (gm == 1) {
            return 0;
        }
        return fn_802499F4(1);
    case 7:
        return 0;
    case 8:
        return fn_80215DE4(1);
    case 9:
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            if (Sci2Card_GetByteFlag1224()) {
                return fn_80252D90(1);
            }
            return 0;
        }
        return 0;
    case 12:
        if (force) {
            return fn_80243A24(1);
        }
        if (gm == 1) {
            return 0;
        }
        return fn_80243A24(1);
    case 21:
        return fn_80245AC4(4);
    case 22:
        return fn_80246150(4);
    }
    return 0;
}

void HudManager::DrawMasked(unsigned int mask) {
    int flags;
    for (int i = 0; i < 23; i++) {
        if ((mask & (1 << i)) && parts[i]) {
            parts[i]->Draw();
        }
    }
    flags = 0;
    if (mask & 1) {
        flags |= 1;
    }
    if (mask & 0x601FFE) {
        flags |= 2;
    }
    if (mask & 0xEE000) {
        flags |= 0x10;
    }
    fn_8011F870(flags);
    if (mask & 0x10000) {
        HudTask *t = fn_80254330(list.p, 0x10);
        if (t && t->Ready()) {
            t->Draw();
            switch (style) {
            case 0:
                fn_8011F994(5);
                fn_801493B0(t);
                fn_8011F994(6);
                break;
            case 2:
                fn_8011F994(5);
                fn_8011F994(6);
                break;
            case 1:
            default:
                fn_8011F994(5);
                fn_8011F994(6);
                break;
            }
        }
    }
}

void HudManager::DrawAll() {
    for (int i = 0; i < 23; i++) {
        if (parts[i]) {
            parts[i]->Draw();
        }
    }
    list.p->Draw();
    fn_8011FAB8();
}

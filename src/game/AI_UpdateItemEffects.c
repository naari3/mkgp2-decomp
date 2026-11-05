#include "AI_ItemEffects_private.h"

static inline void ResetEffects(AIItemController *self, int category) {
    self->timer52 = 0;
    self->timer1B = 0;
    self->timer1D = 0;
    self->timer1A = 0;
    self->timer22 = 0;
    self->speedTimer = 0;
    self->timer1C = 0;
    self->timer55 = 0;
    self->timer75 = 0;
    self->timer23 = 0;
    self->category = category;
}

void AI_UpdateItemEffects(AIItemController *self) {
    void *catalog;
    int category;
    void *bus;
    if (!self->holder) return;
    if (self->restoreTimer > 0) {
        --self->restoreTimer;
        if (self->restoreTimer <= 0) {
            self->restoreTimer = 0;
            if (self->restoreItem != 0) ItemHolder_SetItem(self->holder, self->restoreItem, 1);
            self->restoreItem = 0;
        }
    }
    bus = self->driver->bus;
    if (self->cooldown > 0) {
        --self->cooldown;
        ItemEffectBus_OrMask(bus, 0x80000000000000ULL);
    } else ItemEffectBus_ClearMask(bus, 0x80000000000000ULL);
    ItemHolder_Update(self->holder);
    bus = self->driver->bus;
    catalog = fn_801DB8F0();
    category = ItemHolder_GetEffectCategory(self->holder);
    if (self->category != category) {
        switch (fn_801DB800(fn_801DB8F0(), category)) {
        case 14:
            ResetEffects(self, category);
            self->timer52 = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 82);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 82, 1);
            break;
        case 15:
            ResetEffects(self, category);
            self->timer1B = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 27);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 27, 1);
            break;
        case 16:
            ResetEffects(self, category);
            self->timer23 = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 35);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 35, 1);
            break;
        case 17:
            ResetEffects(self, category);
            self->timer1D = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 29);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 29, 1);
            break;
        case 18:
            ResetEffects(self, category);
            self->timer1C = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 28);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 28, 1);
            break;
        case 19:
            ResetEffects(self, category);
            self->timer1A = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 26);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 26, 1);
            break;
        case 20:
            ResetEffects(self, category);
            self->timer22 = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 34);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 34, 1);
            break;
        case 21:
            ResetEffects(self, category);
            self->timer55 = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 85);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 85, 1);
            break;
        case 22:
            ResetEffects(self, category);
            self->timer55 = fn_801DB8A4(catalog, category);
            ItemEffectBus_ApplyItemConfirm(bus, 117);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 117, 1);
            break;
        case 23:
            ResetEffects(self, category);
            self->speedTimer = fn_801DB8A4(catalog, category);
            break;
        case 1:
            ResetEffects(self, -1);
            ItemEffectBus_ApplyItemConfirm(bus, 0x17);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 0x17, 1);
            fn_801EC7F0(self->movement, 1);
            break;
        case 24:
            fn_801DEF94(self->steering);
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 0x26);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 0x26, 1);
            self->timer26 = 30;
            break;
        case 25:
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 153);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 153, 1);
            self->timer99 = 600;
            break;
        case 26:
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 154);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 154, 1);
            self->timer9A = 600;
            break;
        case 27:
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 140);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 140, 1);
            self->timer8C = 300;
            break;
        case 28:
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 155);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 155, 1);
            self->timer9B = 600;
            break;
        case 29:
            self->category = category;
            ItemEffectBus_ApplyItemConfirm(bus, 157);
            TornadoEffect_ApplyItemVisual_Compact(self->visual, 157, 1);
            self->timer9D = 600;
            break;
        }
    }
    if (self->timer52 > 0) {
        --self->timer52;
        if (self->timer52 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 82);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 82);
            self->category = -1;
        }
    }
    if (self->timer1B > 0) {
        --self->timer1B;
        if (self->timer1B <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 27);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 27);
            self->category = -1;
        }
    }
    if (self->timer23 > 0) {
        --self->timer23;
        if (self->timer23 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 35);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 35);
            self->category = -1;
        }
    }
    if (self->timer1D > 0) {
        --self->timer1D;
        if (self->timer1D <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 29);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 29);
            self->category = -1;
        }
    }
    if (self->timer1C > 0) {
        --self->timer1C;
        if (self->timer1C <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 28);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 28);
            self->category = -1;
        }
    }
    if (self->timer1A > 0) {
        --self->timer1A;
        if (self->timer1A <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 26);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 26);
            self->category = -1;
        }
    }
    if (self->timer22 > 0) {
        --self->timer22;
        if (self->timer22 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 34);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 34);
            self->category = -1;
        }
    }
    if (self->timer55 > 0) {
        --self->timer55;
        if (self->timer55 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 85);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 85);
            self->category = -1;
        }
    }
    if (self->timer75 > 0) {
        --self->timer75;
        if (self->timer75 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 117);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 117);
            self->category = -1;
        }
    }
    if (self->speedTimer > 0) {
        --self->speedTimer;
        if (self->speedTimer > 0) self->speed = lbl_806DA398;
        else {
            self->speed = lbl_806DA390;
            self->category = -1;
        }
        fn_801EC7E8(self->movement, self->speed);
    }
    if (self->timer26 > 0) {
        --self->timer26;
        if (self->timer26 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 38);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 38);
            self->category = -1;
        }
    }
    if (self->timer99 > 0) {
        --self->timer99;
        if (self->timer99 <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 153);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 153);
            self->category = -1;
        }
    }
    if (self->timer9A > 0) {
        --self->timer9A;
        if (self->timer9A <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 154);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 154);
            self->category = -1;
        }
    }
    if (self->timer8C > 0) {
        --self->timer8C;
        if (self->timer8C <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 140);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 140);
            self->category = -1;
        }
    }
    if (self->timer9B > 0) {
        --self->timer9B;
        if (self->timer9B <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 155);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 155);
            self->category = -1;
        }
    }
    if (self->timer9D > 0) {
        --self->timer9D;
        if (self->timer9D <= 0) {
            ItemEffectBus_ApplyItemEventClear(bus, 157);
            TornadoEffect_ApplyItemVisual_Primary(self->visual, 157);
            self->category = -1;
        }
    }
}

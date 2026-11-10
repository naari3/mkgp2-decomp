/* Kart item roulette: queued pickups, selection, HUD feedback and item use.
 * The two switches intentionally retain the per-item presentation mapping. */
#include "game/ItemBoxProcessPickupPrivate.h"

static inline unsigned char IsBusy(PickupState *self, void *car) {
    if (KartMovement_GetCurrentItemId(CarObject_GetRenderObj(car)) != -1) return 1;
    if (self->timer != 0) return 1;
    return 0;
}
static inline void ClearLights(void) {
    if (lbl_80598A60[0x44] == 1) StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
    if (lbl_80598A60[0x45] == 1) StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
}
static inline void SetLights(void) {
    if (lbl_80598A60[0x44] == 1) StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
    if (lbl_80598A60[0x45] == 1) StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
}
static inline void GiveItem(PickupState *self, void *car, int item) {
    if (IsBusy(self, car) == 1) return;
    self->slots[3].itemId = item;
    self->slots[4].uses = 1;
    self->slot = 3;
    self->lastSlot = 3;
    self->timer = 1;
    self->active = 1;
    self->state = 1;
    switch (self->slots[3].itemId) {
    case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f: case 0x80:
    case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
        self->state = 3; break;
    }
}
static inline unsigned char UseItem(PickupState *self, void *car, int slot, float value) {
    if (self->slots[slot+1].uses <= 0) return 0;
    if (!ItemUse_Gateway(car, self->slots[slot].itemId, value)) return 0;
    self->cooldown = 30;
    self->visible = 1;
    return 1;
}

void ItemBox_ProcessPickup(PickupState *self, void *car, int unused, void *input, int frame, float value) {
    void *kart = CarObject_GetRenderObj(car);
    if (self->queuedItem >= 0 && !IsBusy(self, car)) {
        GiveItem(self, car, self->queuedItem);
        self->queuedItem = -1;
    }
    if (self->cooldown > 0) {
        self->cooldown--;
        if (!(self->cooldown & 1)) self->visible = 1;
        else self->visible = 0;
        if (self->cooldown <= 0) {
            self->cooldown = 0;
            if (self->playSE == 1) ClearLights();
        } else if (self->playSE != 0) {
            if (self->visible == 1) SetLights();
            else ClearLights();
        }
    }
    if (self->hud) fn_8023E324(self->hud, frame);
    if (self->timer > 0) {
        if (g_gameMode != 2 || g_isCommHost != 0) {
            if (self->timer > 1 && self->spinning && Input_IsItemButtonPressed(input)) {
                self->lastSlot = (self->timer / 3) % (lbl_806CF110 == 1 ? 3 : 5);
                self->result = self->lastSlot;
                self->timer = 1;
                self->spinning = 0;
            }
        } else if (self->result >= 0) {
            self->lastSlot = self->result;
            self->timer = 1;
            self->spinning = 0;
        }
        if (--self->timer == 0) {
            int item;
            int count;
            self->slot = self->lastSlot;
            if (self->state == -2) {
                switch (self->slots[self->slot].itemId) {
                case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f: case 0x80:
                case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
                    count = 3; break;
                default: count = 1; break;
                }
                self->state = count;
            }
            if (KartMovement_EquipItem(kart, self->slots[self->slot].itemId) == 1) {
                self->cooldown = 0;
                if (self->playSE == 1) ClearLights();
                self->visible = 1;
                if (self->playSE == 1) SetLights();
                KartItem_PlaySE_0x09(car);
            } else self->timer = 1;
            if (self->hud) {
                fn_8023E154(self->hud);
                item = self->slots[self->slot].itemId;
                count = self->state;
                switch (item) {
                case 0x7b: item = ItemBox_ProcessPickup_data_803F9D10[count + -1]; break;
                case 0x7c: item = ItemBox_ProcessPickup_data_803F9D10[count + 2]; break;
                case 0x7d: item = ItemBox_ProcessPickup_data_803F9D10[count + 5]; break;
                case 0x7e: item = ItemBox_ProcessPickup_data_803F9D10[count + 8]; break;
                case 0x7f: item = ItemBox_ProcessPickup_data_803F9D10[count + 11]; break;
                case 0x80: item = ItemBox_ProcessPickup_data_803F9D10[count + 14]; break;
                case 0x81: item = ItemBox_ProcessPickup_data_803F9D10[count + 17]; break;
                case 0x82: item = ItemBox_ProcessPickup_data_803F9D10[count + 20]; break;
                case 0x83: item = ItemBox_ProcessPickup_data_803F9D10[count + 23]; break;
                case 0x84: item = ItemBox_ProcessPickup_data_803F9D10[count + 26]; break;
                case 0x85: item = ItemBox_ProcessPickup_data_803F9D10[count + 29]; break;
                case 0x86: item = ItemBox_ProcessPickup_data_803F9D10[count + 32]; break;
                case 0x87: item = ItemBox_ProcessPickup_data_803F9D10[count + 35]; break;
                }
                fn_8023E1E4(self->hud, item, 0);
            }
            if (self->playSE && self->active) {
                fn_8016C394(0x4d);
                SoundMgr_PlaySE(0x4e);
                self->active = 0;
            }
            self->spinning = 0;
        } else {
            int slot = (self->timer / 3) % (lbl_806CF110 == 1 ? 3 : 5);
            if (self->hud) {
                int item = self->slots[slot].itemId;
                switch (item) {
                case 0x7b: item = ItemBox_ProcessPickup_data_803F9D10[2]; break;
                case 0x7c: item = ItemBox_ProcessPickup_data_803F9D10[5]; break;
                case 0x7d: item = ItemBox_ProcessPickup_data_803F9D10[8]; break;
                case 0x7e: item = ItemBox_ProcessPickup_data_803F9D10[11]; break;
                case 0x7f: item = ItemBox_ProcessPickup_data_803F9D10[14]; break;
                case 0x80: item = ItemBox_ProcessPickup_data_803F9D10[17]; break;
                case 0x81: item = ItemBox_ProcessPickup_data_803F9D10[20]; break;
                case 0x82: item = ItemBox_ProcessPickup_data_803F9D10[23]; break;
                case 0x83: item = ItemBox_ProcessPickup_data_803F9D10[26]; break;
                case 0x84: item = ItemBox_ProcessPickup_data_803F9D10[29]; break;
                case 0x85: item = ItemBox_ProcessPickup_data_803F9D10[32]; break;
                case 0x86: item = ItemBox_ProcessPickup_data_803F9D10[35]; break;
                case 0x87: item = ItemBox_ProcessPickup_data_803F9D10[38]; break;
                }
                fn_8023E1E4(self->hud, item, 0);
            }
        }
    } else {
        self->result = -1;
        if (KartItem_GetCarObjectState_2bc(car) != 1 && self->slot >= 0 && Input_IsItemButtonPressed(input)) {
            if (UseItem(self, car, self->slot, value) == 1) {
                self->state--;
                if (self->state <= 0) {
                    self->slot = -1;
                    if (self->hud) fn_8023E1E4(self->hud, -1, 0);
                } else self->timer = 1;
            }
        }
    }
}

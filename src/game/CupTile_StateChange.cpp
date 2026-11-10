#include "game/CupTileState_private.h"

extern "C" int CupTile_StateChange(CupTileOwner *self, int index, int state) {
    CupTileSlot *slot = &self->slots[index];
    if (state == 1) { if (slot->state != 0) return 0; }
    else { if (slot->state == 0) return 0; }
    slot->state = state;
    slot->timer = 0;
    slot->frame = 0;
    switch (state) {
    case 1:
        if (!slot->sprite) slot->sprite = new TileSprite(52, 0, 0);
        else Sprite_SetupAnim(slot->sprite, 52, 0, 0);
        if (self->mode == 0 && index == 7 && self->unlock154 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else if (self->mode == 1 && index == 7 && self->unlock155 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index].id);
        Sprite_SetAnimParam(slot->sprite, 0x1780, clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(clFlowCup_data_8049AD58[index].x, lbl_806D9C80 + clFlowCup_data_8049AD58[index].y);
        slot->sprite->Scale(lbl_806D9C70);
        break;
    case 2:
        if (!slot->sprite) slot->sprite = new TileSprite(384, 0, 0);
        else Sprite_SetupAnim(slot->sprite, 384, 0, 0);
        if (self->mode == 0 && index == 7 && self->unlock154 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else if (self->mode == 1 && index == 7 && self->unlock155 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index].id);
        Sprite_SetAnimParam(slot->sprite, 0x1780, clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(clFlowCup_data_8049AD58[index].x, lbl_806D9C80 + clFlowCup_data_8049AD58[index].y);
        slot->sprite->Scale(lbl_806D9C70);
        fn_8019FF6C(slot->sprite, 1);
        break;
    case 3:
        if (!slot->sprite) slot->sprite = new TileSprite(49, 0, 0);
        else Sprite_SetupAnim(slot->sprite, 49, 0, 0);
        if (self->mode == 0 && index == 7 && self->unlock154 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else if (self->mode == 1 && index == 7 && self->unlock155 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index].id);
        Sprite_SetAnimParam(slot->sprite, 0x1780, clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(clFlowCup_data_8049AD58[index].x, lbl_806D9C80 + clFlowCup_data_8049AD58[index].y);
        slot->sprite->Scale(lbl_806D9C70);
        break;
    case 4:
        if (!slot->sprite) slot->sprite = new TileSprite(50, 0, 0);
        else Sprite_SetupAnim(slot->sprite, 50, 0, 0);
        if (self->mode == 0 && index == 7 && self->unlock154 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else if (self->mode == 1 && index == 7 && self->unlock155 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index].id);
        Sprite_SetAnimParam(slot->sprite, 0x1780, clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(clFlowCup_data_8049AD58[index].x, lbl_806D9C84 + clFlowCup_data_8049AD58[index].y);
        slot->sprite->Scale(lbl_806D9C88);
        fn_8019FF6C(slot->sprite, 1);
        break;
    case 5:
        if (!slot->sprite) slot->sprite = new TileSprite(51, 0, 0);
        else Sprite_SetupAnim(slot->sprite, 51, 0, 0);
        if (self->mode == 0 && index == 7 && self->unlock154 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else if (self->mode == 1 && index == 7 && self->unlock155 == 0)
            Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index + 1].id);
        else Sprite_SetAnimParam(slot->sprite, 0x1777, clFlowCup_data_8049AD58[index].id);
        Sprite_SetAnimParam(slot->sprite, 0x1780, clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(clFlowCup_data_8049AD58[index].x, lbl_806D9C84 + clFlowCup_data_8049AD58[index].y);
        slot->sprite->Scale(lbl_806D9C88);
        break;
    case 6: fn_8019FF6C(slot->sprite, 0); break;
    }
    return 1;
}

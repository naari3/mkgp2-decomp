#include "game/CupTileState_private.h"

extern "C" int fn_801C9288(RoundTileOwner *self, int index, int state) {
    RoundTileSlot *slot = &self->slots[index];
    CupTileInfo *positions = lbl_8049AE70.positions;
    RoundTileParams (*params)[4] = lbl_8049AE70.params;
    int (*animations)[3] = lbl_8049AE70.animations;
    short *cups = lbl_8049AE70.cups;
    if (state == 1) { if (slot->state != 0) return 0; }
    else { if (slot->state == 0) return 0; }
    slot->state = state;
    slot->timer = 0;
    slot->frame = 0;
    switch (state) {
    case 1: {
        int anim;
        RoundTileParams *param;
        CupTileInfo *pos;
        pos = &positions[index];
        param = &params[cups[g_cupId]][index];
        anim = animations[0][slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    case 2: {
        CupTileInfo *pos = &positions[index];
        RoundTileParams *param = &params[cups[g_cupId]][index];
        int anim = animations[5][slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 3: {
        CupTileInfo *pos = &positions[index];
        RoundTileParams *param = &params[cups[g_cupId]][index];
        int anim = animations[4][slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    case 4: {
        CupTileInfo *pos = &positions[index];
        RoundTileParams *param = &params[cups[g_cupId]][index];
        int anim = animations[3][slot->variant];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(1.0f);
        fn_8019FF6C(slot->sprite, 1);
        break;
    }
    case 5: {
        CupTileInfo *pos = &positions[index];
        RoundTileParams *param = &params[cups[g_cupId]][index];
        int anim = animations[2][slot->variant];
        float offset = lbl_806D9D40;
        if (index == 2 || index == 4) offset = -lbl_806D9D40;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(1.0f);
        break;
    }
    case 6: {
        CupTileInfo *pos = &positions[index];
        RoundTileParams *param = &params[cups[g_cupId]][index];
        int anim = animations[1][slot->variant];
        float offset = lbl_806D9D38;
        if (index == 2 || index == 4) offset = -lbl_806D9D38;
        if (!slot->sprite) slot->sprite = new TileSprite(anim, 0, 0);
        else Sprite_SetupAnim(slot->sprite, anim, 0, 0);
        switch (slot->variant) {
        case 0:
            Sprite_SetAnimParam(slot->sprite, 0x1951, pos->id);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 1:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        case 2:
            Sprite_SetAnimParam(slot->sprite, 0x194C, pos->sub);
            Sprite_SetAnimParam(slot->sprite, 0x19B0, param->alternate);
            break;
        }
        Sprite_SetAnimParam(slot->sprite, 0x1A1E, param->id);
        fn_801A0550(slot->sprite);
        slot->sprite->Position(pos->x, pos->y + offset);
        slot->sprite->Scale(0.7f);
        break;
    }
    }
    return 1;
}

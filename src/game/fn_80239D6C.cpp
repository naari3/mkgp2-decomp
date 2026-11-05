#include "game/ItemSelectPresentationPrivate.h"
extern "C" void fn_80239D6C(ItemSelectPresentation *self) {
    SpriteGroup_CreateOrInit(&self->groups[0], lbl_806D073C, 0, lbl_806DB8DC, lbl_806DB940);
    SpriteGroup_CreateOrInit(&self->groups[1], lbl_806D0740, 0, lbl_806DB944, lbl_806DB948);
    SpriteGroup_CreateOrInit(&self->groups[2], lbl_806D0744, 0, lbl_806DB94C, lbl_806DB948);
    SpriteGroup_CreateOrInit(&self->groups[3], lbl_806D0748, 0, lbl_806DB950, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[4], lbl_806D074C, 0, lbl_806DB8DC, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[5], lbl_806D0750, 0, lbl_806DB958, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[6], lbl_806D0754, 1, lbl_806DB95C, lbl_806DB960);
    self->groups[0]->sprite->layer = 6;
    self->groups[1]->sprite->layer = 6;
    self->groups[2]->sprite->layer = 6;
    self->groups[3]->sprite->layer = 6;
    self->groups[4]->sprite->layer = 6;
    self->groups[5]->sprite->layer = 6;
    self->groups[6]->sprite->layer = 6;
    PresentationScale(self->groups[2]->sprite, lbl_806DB964);
    PresentationScale(self->groups[6]->sprite, lbl_806DB910);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[3], 0x13b9, self->resources[0]);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[4], 0x13b9, self->resources[1]);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[5], 0x13b9, self->resources[2]);
    SpriteAnimSample pos;
    unsigned char *player = g_playerData;
    for (int i = 0; i < 3; i++) {
        int group = i + 3;
        self->groups[group]->sprite->alpha = lbl_806DB888;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x13b9, self->resources[i]);
        int item = PlayerData_ResolveUnlockedIdByIndex(player, self->itemIndices[i]);
        int field = Item_GetDescriptorFieldC(item);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1e1d, field < 0 ? -1 : field + 0x1e1d);
        field = Item_GetDescriptorField8(item);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x17a4, field < 0 ? -1 : field + 0x17a3);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ecd, &pos);
        fn_801F93EC(self->texts[i][0], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ecf, &pos);
        fn_801F93EC(self->texts[i][1], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ed1, &pos);
        fn_801F93EC(self->texts[i][2], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ed3, &pos);
        fn_801F93EC(self->texts[i][3], pos.x, pos.y);
        TexMgr_SetTexture(self->texts[i][0], fn_8023DAA8(item));
        TexMgr_SetTexture(self->texts[i][1], Item_GetLocalizedAsset(item, 0));
        TexMgr_SetTexture(self->texts[i][2], Item_GetLocalizedAsset(item, 1));
        TexMgr_SetTexture(self->texts[i][3], Item_GetLocalizedAsset(item, 2));
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ecf, 0x1ecd);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ed1, 0x1ecd);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ed3, 0x1ecd);
        *(unsigned int *)(self->texts[i][0]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][1]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][2]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][3]->data + 0x20) = 0xffffff00;
    }
    PresentationParams(self);
    self->timer = 0;
    self->phase = 1;
}

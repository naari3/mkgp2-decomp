#include "game/ItemSelectRefillPrivate.h"
extern "C" {
extern const int ItemSelectState_rodata_803DC180[6][10];
const char *Item_GetLocalizedAsset(int, int);
void TexMgr_SetTexture(TextManager *, const char *, ...);
void TexMgr_Apply(TextManager *);
}
static inline int ChoiceCharacter() {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    return character;
}
extern "C" RefillChoice *fn_8023B1A8(RefillChoice *self) {
    self->phase = 0;
    self->timer = 0;
    self->row = 0;
    self->column = 0;
    self->active = 0;
    self->selected = 0;
    self->done = 1;
    self->resource = 0x13b9;
    self->count = 0;
    self->groups[0] = 0;
    self->groups[1] = 0;
    self->groups[2] = 0;
    self->groups[3] = 0;
    self->slots[0][0] = -1;
    self->slots[0][1] = -1;
    self->slots[1][0] = -1;
    self->slots[1][1] = -1;
    self->slots[2][0] = -1;
    self->slots[2][1] = -1;
    self->text[0] = 0;
    self->text[1] = 0;
    self->text[2] = 0;
    self->text[3] = 0;
    TextManager text;
    unsigned char *player = g_playerData;
    int row;
    int column;
    for (row = 0; row < 6; ++row) {
        for (column = 0; column < 11; ++column) {
            int character = ChoiceCharacter();
            int id;
            if (column >= 10) id = fn_8023D844(character, row);
            else id = ItemSelectState_rodata_803DC180[row][column];
            if (player[id + 0xa8] == 1) {
                int descriptor = PlayerData_ResolveUnlockedIdByIndex(player, id);
                TexMgr_SetTexture(&text, Item_GetLocalizedAsset(descriptor, 0));
                TexMgr_Apply(&text);
                TexMgr_SetTexture(&text, Item_GetLocalizedAsset(descriptor, 1));
            }
        }
    }
    return self;
}

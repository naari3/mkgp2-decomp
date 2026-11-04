#include "game/ItemSelectRefillPrivate.h"
extern "C" {
extern const int lbl_803DC180[6][10];
void fn_8019FF6C(RefillSprite *, int);
}
static inline int ChoiceItem(RefillChoice *self) {
    int character = g_characterId;
    int row = self->row;
    int column = self->column;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    return lbl_803DC180[row][column];
}
static inline unsigned char ChoiceOccupied(RefillChoice *self) {
    unsigned char occupied = 0;
    if (self->slots[0][0] == self->column && self->slots[0][1] == self->row) occupied = 1;
    else if (self->slots[1][0] == self->column && self->slots[1][1] == self->row) occupied = 1;
    return occupied;
}
extern "C" void fn_8023AA0C(RefillChoice *self, int step) {
    if (step) {
        unsigned char *player = g_playerData;
        unsigned char occupied;
        do {
            self->column += step;
            if (self->column < 0) { self->column = 10; --self->row; }
            if (self->column > 10) { self->column = 0; ++self->row; }
            if (self->row < 0) self->row = 5;
            if (self->row > 5) self->row = 0;
            occupied = ChoiceOccupied(self);
        } while (occupied == 1);
        self->done = player[ChoiceItem(self) + 0xa8];
        int resource = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,
            ChoiceItem(self)), 0);
        if (!self->done) resource = 0x1422;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[1], self->resource, resource);
        fn_8019FF6C(self->groups[1]->sprite, 1);
        self->resource = resource;
    }
}

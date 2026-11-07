#ifndef GAME_ITEMSELECTCHOICEUPDATEPRIVATE_H
#define GAME_ITEMSELECTCHOICEUPDATEPRIVATE_H
#include "game/ItemSelectState.h"
struct RefillSprite {
    int field0, layer, field8;
    float x, y, sx, sy, field1c, alpha;
};
struct RefillGroup { RefillSprite *sprite; };
struct RefillChoice {
    RefillGroup *groups[4];
    TextManager *text[4];
    int phase, timer, row, column;
    unsigned char active, selected, done, pad33;
    int resource, count;
    int slots[3][2];
};
extern "C" {
extern const int lbl_803DC180[6][10];
extern unsigned char g_playerData[];
extern int g_characterId;
void fn_8023AA0C(RefillChoice *, int);
int fn_8023D844(int, int);
int PlayerData_ResolveUnlockedIdByIndex(void *, int);
int Item_GetDescriptorField0(int, void *);
void SpriteAnimParamBlock_Reload(void *, int);
void SpriteAnimParamBlock_SetAnimParamCached(void *, int, int);
void SpriteHandle_SetActiveFlag(int, int);
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
#endif

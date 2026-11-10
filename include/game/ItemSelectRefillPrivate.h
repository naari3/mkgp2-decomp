#ifndef GAME_ITEMSELECTREFILLPRIVATE_H
#define GAME_ITEMSELECTREFILLPRIVATE_H
#include "game/ItemSelectState.h"
#include "game/types/RefillSprite.h"
#include "game/types/RefillGroup.h"
struct RefillChoice {
    RefillGroup *groups[4];
    TextManager *text[4];
    int phase, timer, row, column;
    unsigned char active, selected, done, pad33;
    int resource, count;
    int slots[3][2];
};
struct RefillLayout {
    char pad00[0xc0];
    int items[6][10];
    float x[11], y[6];
    int resources[3];
};
extern "C" {
extern const RefillLayout ItemSelectState_rodata_803DC0C0;
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
static inline int RefillItem(const RefillLayout *layout, int column, int row) {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    const int (*items)[10] = layout->items;
    return items[row][column];
}
#endif

#ifndef GAME_TYPES_ITEMSHOWCASE_H
#define GAME_TYPES_ITEMSHOWCASE_H

#include "game/types/ShowAnim.h"
#include "game/types/ShowModel.h"
#include "game/types/ShowShellA.h"
#include "game/types/ShowShellB.h"

struct ItemShowcase {
    int timer;
    int itemId;
    ShowModel *model;
    bool loaded;
    float glow;
    float alpha;
    ShowAnim *anim;
    ShowShellA *shellA;
    ShowShellB *shellB;
    ItemShowcase(int t);
    ~ItemShowcase();
    void Draw();
    int Update();
};

#endif /* GAME_TYPES_ITEMSHOWCASE_H */

#ifndef GAME_TYPES_PARTSLIST_H
#define GAME_TYPES_PARTSLIST_H

#include "game/types/PartsNode.h"
#include "game/types/clMapEffectParts.h"

struct PartsList {
    PartsNode *head;

    PartsList() {
        head = 0;
    }

    ~PartsList();
    int Add(int kind, int prio, clMapEffectParts *parts);
    clMapEffectParts *Find(unsigned int kind);
    void Update();
    void Draw(int mask);
    void SetHidden(int mask, unsigned char hide);
};

#endif /* GAME_TYPES_PARTSLIST_H */

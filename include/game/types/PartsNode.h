#ifndef GAME_TYPES_PARTSNODE_H
#define GAME_TYPES_PARTSNODE_H

#include "game/types/clMapEffectParts.h"

struct PartsNode {
    int kind;
    int prio;
    clMapEffectParts *parts;
    unsigned char done;
    PartsNode *next;

    PartsNode(int kind, int prio, clMapEffectParts *parts) {
        this->kind = kind;
        this->prio = prio;
        this->parts = parts;
        done = 0;
        next = 0;
    }

    int Append(int kind, int prio, clMapEffectParts *parts) {
        if (parts) {
            if (next) {
                next->Append(kind, prio, parts);
            } else {
                next = new PartsNode(kind, prio, parts);
            }
            return 1;
        }
        return 0;
    }

    ~PartsNode();
    clMapEffectParts *Find(unsigned int kind);
    void Update();
    void Draw(int mask);
    void SetHidden(int mask, unsigned char hide);
};

#endif /* GAME_TYPES_PARTSNODE_H */

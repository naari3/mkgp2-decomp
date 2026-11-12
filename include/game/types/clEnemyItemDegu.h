#ifndef GAME_TYPES_CLENEMYITEMDEGU_H
#define GAME_TYPES_CLENEMYITEMDEGU_H
#include "game/types/clEnemyItemInterface.h"
struct AIDriver; struct AITornado;
class clEnemyItemDegu : public clEnemyItemInterface {
public:
    virtual ~clEnemyItemDegu();
    virtual void Update();
    virtual void SetTarget(unsigned int);
    virtual void ResetTarget();
    virtual bool CanUse();
    virtual int IsEnabled();
    clEnemyItemDegu(AIDriver *, AITornado *, int, int);
    unsigned int GetItemType();
    unsigned int HasItem();
    unsigned int GetEffectCategory();
    void Cancel();
    void SetItem(int, int);
    unsigned char IsIdle();
    void Tick();
    inline void Equip(int);
};
#endif

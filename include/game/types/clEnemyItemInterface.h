#ifndef GAME_TYPES_CLENEMYITEMINTERFACE_H
#define GAME_TYPES_CLENEMYITEMINTERFACE_H
struct KartDriver;
class clEnemyItemInterface {
public:
    virtual ~clEnemyItemInterface() {}
    virtual void Update() = 0;
    virtual void SetTarget(unsigned int) = 0;
    virtual void ResetTarget() = 0;
    virtual bool CanUse() = 0;
    virtual int IsEnabled() = 0;
    KartDriver *kart;
    int x8, xC, x10, selfId, targetId, pendingItem, state, cooldown, grantedItem;
    inline clEnemyItemInterface(unsigned int, int, int, int);
};
#endif

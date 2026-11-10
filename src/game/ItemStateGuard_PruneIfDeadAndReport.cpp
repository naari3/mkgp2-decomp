class GuardedItem {
public:
    virtual void Destroy();
    virtual unsigned char IsAlive();
};

#include "game/types/ItemStateGuard.h"

extern "C" int ItemStateGuard_PruneIfDeadAndReport(ItemStateGuard *guard) {
    if (guard->active == 0) {
        return 0;
    }
    if (!guard->active->IsAlive()) {
        guard->active->Destroy();
        guard->active = 0;
        return 0;
    }
    return 1;
}

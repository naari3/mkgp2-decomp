#include "game/types/ItemStateGuard.h"

unsigned char ItemStateGuard_IsActive(ItemStateGuard *guard) {
    return guard->active != 0;
}

#ifndef GAME_FN_801D5F74_PRIVATE_H
#define GAME_FN_801D5F74_PRIVATE_H

#include "game/PlayerDataProgressPrivate.h"

/* The same table records as PlayerUnlockTablesPendingPrivate.h, without its
 * opaque declaration of lbl_8039C718: this TU owns the actual constant pool. */
#include "game/types/UnlockRemap.h"
#include "game/types/UnlockGrant.h"
typedef struct UnlockCategory { const int *ids; int count; } UnlockCategory;
typedef struct UnlockCategories {
    int first[3];
    UnlockCategory categories[7];
} UnlockCategories;

#endif

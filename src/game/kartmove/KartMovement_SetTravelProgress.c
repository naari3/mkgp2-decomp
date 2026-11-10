#include "game/types/SpeedTable.h"

#include "game/types/KartMove.h"

void KartMovement_SetTravelProgress(KartMove *k, float p) {
    if (p > k->tables[k->table].maxProgress) {
        p = k->tables[k->table].maxProgress;
    }
    k->progress = p;
}

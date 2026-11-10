typedef struct SpeedTable {
    void *pts;
    int count;
    float maxProgress;
    unsigned char pad[0xc];
} SpeedTable;

#include "game/types/KartMove.h"

void KartMovement_SetTravelProgress(KartMove *k, float p) {
    if (p > k->tables[k->table].maxProgress) {
        p = k->tables[k->table].maxProgress;
    }
    k->progress = p;
}

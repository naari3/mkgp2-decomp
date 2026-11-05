#include "game/EnemyFace_private.h"

void TireSprite_Draw(TireSprite *s);

static inline void *TireDrawManager() {
    void *p = lbl_806D10AC;
    if (p == 0) p = 0;
    return p;
}

void TireSprite_Queue(TireSprite *s) {
    if (s && s->visible && !(s->alpha <= 0.0f)) {
        void *man = TireDrawManager();
        clDrawMan_AddSorted_DepthRange(man, TireSprite_Draw, s, s->px, s->py - 1.0f, s->pz, 0.0f);
    }
}

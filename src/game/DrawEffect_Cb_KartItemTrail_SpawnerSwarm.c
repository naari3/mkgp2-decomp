#include "game/DrawEffectAccess.h"

typedef struct SwarmWork {
    void *owner;                 /* 0x0CC */
    unsigned char pad04[0x0C];
    unsigned char *children[16]; /* 0x0DC */
    void *driver;                /* 0x11C */
} SwarmWork;

extern void DrawEffect_Cb_KartItemTrail_4Phase(unsigned char *self);

void DrawEffect_Cb_KartItemTrail_SpawnerSwarm(unsigned char *self)
{
    SwarmWork *work = (SwarmWork *)(self + 0xCC);
    int i;

    switch (STATE) {
    case 0:
        for (i = 0; i < 12; i++) {
            work->children[i] = DrawEffect_SpawnDirect(DrawEffect_Cb_KartItemTrail_4Phase);
            if (work->children[i] != 0) {
                *(int *)(work->children[i] + 0x10) = I(0x10);
                Vec3_Copy((Vec *)(work->children[i] + 0x120), V(0x8C));
                work->children[i][0x190] = i % 4;
            }
        }
        STATE++;
        break;
    case 1:
        break;
    }
    for (i = 0; i < 16; i++) {
        if (work->children[i] != 0) {
            Vec3_Copy((Vec *)(work->children[i] + 0x120), V(0x8C));
        }
    }
    if (FINISHED) {
        for (i = 0; i < 16; i++) {
            if (work->children[i] != 0) {
                *(void **)(work->children[i] + 0x11C) = work->driver;
                *(void **)(work->children[i] + 0xCC) = work->owner;
                Vec3_Copy((Vec *)(work->children[i] + 0xA4), V(0xA4));
                work->children[i][0xC9] = U8(0xC9);
                work->children[i] = 0;
            }
        }
        DrawEffect_Free(self);
    }
}

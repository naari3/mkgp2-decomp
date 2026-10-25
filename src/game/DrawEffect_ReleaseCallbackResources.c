/* DrawEffect_ReleaseCallbackResources (0x800B542C): flags every child
 * effect held by a kart effect controller as finished (1, or 2 for the
 * paired trail slots) and frees the controller. */
#include "game/DrawEffectAccess.h"

#define RELEASE(o, v)                                  \
    do {                                               \
        if (P(o) != 0) {                               \
            *(signed char *)(P(o) + 0xC9) = (v);       \
        }                                              \
        P(o) = 0;                                      \
    } while (0)

typedef struct TrailPair {
    unsigned char *a;
    unsigned char *pad;
    unsigned char *b;
} TrailPair;

void DrawEffect_ReleaseCallbackResources(unsigned char *self)
{
    int i;

    if (self == 0) {
        return;
    }
    RELEASE(0x118, 1);
    RELEASE(0x11C, 1);
    RELEASE(0x128, 1);
    RELEASE(0x12C, 1);
    RELEASE(0x134, 1);
    RELEASE(0x13C, 1);
    RELEASE(0x140, 1);
    RELEASE(0x144, 1);
    RELEASE(0x148, 1);
    RELEASE(0x150, 1);
    RELEASE(0x154, 1);
    RELEASE(0x158, 1);
    RELEASE(0x15C, 1);
    for (i = 0; i < 3; i++) {
        TrailPair *t = (TrailPair *)(self + 0x164 + i * 4);
        if (t->a != 0) {
            *(signed char *)(t->a + 0xC9) = 2;
        }
        if (t->b != 0) {
            *(signed char *)(t->b + 0xC9) = 2;
        }
        t->a = 0;
        t->b = 0;
    }
    RELEASE(0x17C, 1);
    RELEASE(0x184, 1);
    RELEASE(0x190, 1);
    DrawEffect_Free(self);
}

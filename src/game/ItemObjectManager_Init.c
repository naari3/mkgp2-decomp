/* Item-object slot pool initialization, 0x800D81E0 (168 bytes).
 * clNormal3D allocation cleanup is emitted by the C++ new expression.
 */
#include "game/types/size_t.h"
#pragma cplusplus on
#include "game/ObjViewA70C_private.h"

void *operator new(size_t);
void operator delete(void *);
extern "C" {
void *memset(void *, int, unsigned long);
void AnimStatePool_ZeroInit(void);
void ItemHitRegistry_Reset(void);
extern void *lbl_8041BC00[];
extern unsigned char g_itemObjectManager[];

/* Each slot is reset independently before the shared model is created. */
static inline void ResetSlots(unsigned char *slot) {
    int i = 0;
    do {
        memset(slot, 0, 0x1EC);
        ++i;
        slot += 0x1EC;
    } while (i < 256);
}

void ItemObjectManager_Init(void) {
    ResetSlots(g_itemObjectManager);
    *(clNormal3D **)(g_itemObjectManager + 0x1EC00) = new clNormal3D(lbl_8041BC00[0xAB4 / 4], 1);
    AnimStatePool_ZeroInit();
    *(int *)(g_itemObjectManager + 0x1EC04) = 0;
    ItemHitRegistry_Reset();
}
}

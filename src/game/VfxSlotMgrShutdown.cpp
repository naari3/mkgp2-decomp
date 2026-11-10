/* Standalone pool shutdown, real C++ virtual delete. */
struct Slot { signed char active; char reserved[0x1CB]; };
#include "game/types/Resource.h"
extern "C" { void VfxSlot_Release(void*); void fn_8022B1C8();
extern Slot g_drawEffectSlots[512]; extern Resource *g_normal3DWrapMgr; }
extern "C" void VfxSlotMgr_Shutdown() {
    for(int i=0;i<512;++i) {
        Slot *slot=&g_drawEffectSlots[i];
        VfxSlot_Release((char*)slot+0x14);
        slot->active=0;
    }
    delete g_normal3DWrapMgr;
    g_normal3DWrapMgr=0;
    fn_8022B1C8();
}

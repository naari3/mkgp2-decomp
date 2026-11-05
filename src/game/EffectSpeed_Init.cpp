#include "game/EffectSpeedInitPrivate.h"
SpeedInitOwner::SpeedInitOwner(void *p)
 : kart(p), field04(0), field08(0), field10(0), field14(0), field18(0), active(0),
   scale(new(lbl_802EE510,0x95) SpeedInitScale(this)),
   mue(new(lbl_802EE510,0x96) SpeedInitMue(this)) {
    if (active) active->Reset();
    active=0;
    field18=0;
    void *render=CarObject_GetRenderObj(kart);
    ItemEffectBus_ClearMask(*(void **)((char *)render+0x304), 0ULL);
}

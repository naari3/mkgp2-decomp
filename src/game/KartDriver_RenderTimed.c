/* Automatic cleanup uses the canonical cross-TU ScopedTimer destructor.
 * TU-scoped metadata names the automatic cleanup records at their target addresses. */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
int KartDriver_Render(void *driver, int mode, int context);
extern const float lbl_806D25E0;
}

#include "game/types/ScopedTimer.h"

extern "C" void KartDriver_RenderTimed(void *driver, int mode, int context)
{
    ScopedTimer timer(23);
    KartDriver_Render(driver, mode, context);
}
#pragma cplusplus off

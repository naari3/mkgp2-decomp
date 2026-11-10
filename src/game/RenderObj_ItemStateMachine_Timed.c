/* Automatic cleanup uses the canonical cross-TU ScopedTimer destructor.
 * TU-scoped metadata names the automatic cleanup records at their target addresses. */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
int RenderObj_ItemStateMachine(void *obj, int arg, float a, float b);
extern const float lbl_806D25E0;
}

#include "game/types/ScopedTimer.h"

extern "C" int RenderObj_ItemStateMachine_Timed(void *obj, int arg, float a, float b)
{
    ScopedTimer timer(22);
    return RenderObj_ItemStateMachine(obj, arg, a, b);
}
#pragma cplusplus off

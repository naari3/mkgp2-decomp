#include "game/TestMenuPage.h"

#include "game/Scene_801670FC_private.h"

extern "C" {
extern char Scene_801670FC_rodata_8036A37C[];
void fn_80120A08(int);
#ifdef __MWERKS__
void fn_801698B4(void *, float, float, int, unsigned int);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801698B4(void *, int, float, float, unsigned int);
static inline void fn_801698B4_Reordered(void *a0, float a1, float a2, int a3, unsigned int a4) { fn_801698B4(a0, a3, a1, a2, a4); }
#define fn_801698B4 fn_801698B4_Reordered
#endif
void fn_80168EFC(void *, char *, float, float, ...);
#pragma exceptions on
void fn_801670FC(SoundDebugScene *self) {
    if (self->quit == 1) { self->done = 1; return; }
    if (InputMgr_GetPlayer(GetInputManager(), 0)->StickRight() > 0.7f) {
        if (self->repeat < 0) self->repeat = 0;
        else if (++self->repeat > 20) self->repeat = 18;
    } else if (InputMgr_GetPlayer(GetInputManager(), 0)->StickLeft() > 0.7f) {
        if (self->repeat > 0) self->repeat = 0;
        else if (--self->repeat < -20) self->repeat = -18;
    } else self->repeat = 0;
    int step = 0;
    if (self->repeat == 1 || self->repeat == 20) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000)) step = 10;
        else step = 1;
    }
    if (self->repeat == -1 || self->repeat == -20) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000)) step = -10;
        else step = -1;
    }
    int old = self->soundId;
    self->soundId += step;
    if (self->soundId <= -1) self->soundId = 0x2aff;
    if (self->soundId >= 0x2b00) self->soundId = 0;
    if (old != self->soundId) fn_80120A08(old);
    fn_801698B4(self->text, 320.0f, 240.0f, self->soundId, 0);
    fn_80168EFC(self->text, Scene_801670FC_rodata_8036A37C, 20.0f, 20.0f, self->soundId);
}
#pragma exceptions reset
}




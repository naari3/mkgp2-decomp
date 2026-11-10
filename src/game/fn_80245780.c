#include "game/types/HudSprite2457.h"
extern unsigned int lbl_804EE7B8[];
void fn_80120A08(int);
void MemoryManager_TimedFree(void *);
HudSprite2457 *fn_80245780(HudSprite2457 *self, short flags) {
    if (self) {
        self->vtable=lbl_804EE7B8;
        fn_80120A08(0x1CB6);
        if (flags>0) MemoryManager_TimedFree(self);
    }
    return self;
}

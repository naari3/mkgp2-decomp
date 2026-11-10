extern "C" void MemoryManager_TimedFree(void *p);

#include "game/types/FlowObject.h"

#include "game/types/FlowDispatcher.h"

/* 0x8002C554: deleting destructor of the flow dispatcher. */
extern "C" FlowDispatcher *FlowDispatcher_Dtor(FlowDispatcher *self, short flag)
{
    if (self != 0) {
        if (self->current != 0) {
            delete self->current;
        }
        if (self->next != 0) {
            delete self->next;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

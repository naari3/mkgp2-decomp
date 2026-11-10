/* CardTaskManager destructor: delete every queued task, free the queue,
 * then the manager itself when called as a deleting destructor. */
#pragma cplusplus on

class CardTask {
public:
    virtual void Run();
    virtual ~CardTask();
};

#include "game/types/CardTaskEntry.h"

#include "game/types/CardTaskManager.h"

extern "C" void MemoryManager_Free(void *p);
extern "C" void MemoryManager_TimedFree(void *p);

extern "C" CardTaskManager *CardTaskManager_Dtor(CardTaskManager *self, short flag)
{
    int i;

    if (self != 0) {
        if (self->entries != 0) {
            for (i = 0; i < self->count; i++) {
                delete self->entries[i].task;
            }
        }
        MemoryManager_Free(self->entries);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

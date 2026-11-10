#include "game/types/c_region.h"
C_REGION_BEGIN
/* Run the current card task. When it finishes (2), fails (4) or aborts (5)
 * the manager moves on to the next one; after the last task it lingers a
 * few frames. Returns 2 while busy, 3 on abort, 0 when done. */
C_REGION_END
#pragma cplusplus on

class CardTask {
public:
    virtual void Render();
    virtual ~CardTask();
    virtual void Start();
    virtual int IsDone();
    virtual int Tick();
    virtual void Finish();

    int state; /* 0x04 */
};

#include "game/types/CardTaskEntry.h"

#include "game/types/CardTaskManager.h"

extern "C" void ServiceButtonExtra_Set(int value);

extern "C" int CardTaskManager_Tick(CardTaskManager *self)
{
    int state;
    CardTask *task;

    self->frame++;
    if (self->current >= self->count) {
        self->linger--;
        return self->linger <= 0 ? 0 : 2;
    }
    task = self->entries[self->current].task;
    task->state = task->Tick();
    state = task->state;
    if (state == 2 || state == 4 || state == 5) {
        task->Finish();
        ServiceButtonExtra_Set(0);
        if (state == 5) {
            return 3;
        }
        self->current++;
        if (self->current < self->count) {
            self->entries[self->current].task->Start();
        }
    }
    return 2;
}

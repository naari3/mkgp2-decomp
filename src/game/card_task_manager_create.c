/* Build the enabled card-task queue and start its first task. */
#pragma cplusplus on
#pragma exceptions on

#include "game/CardTaskManagerCreatePrivate.h"

extern "C" CardTaskFactory g_cardTaskFactories[];
extern "C" void *FUN_8003b120(unsigned long);

static inline void AddTask(CardTaskManager *self, CardTask *task, int kind)
{
    self->entries[self->count].task = task;
    self->entries[self->count].kind = kind;
    self->count++;
}
static inline void Initialize(CardTaskManager *self)
{
    self->count = 0;
    self->entries = (CardTaskEntry *)FUN_8003b120(32);
    self->entries[0].task = 0;
    self->entries[1].task = 0;
    self->entries[2].task = 0;
    self->entries[3].task = 0;
}
extern "C" CardTaskManager *card_task_manager_create(CardTaskManager *self,
    unsigned char welcome, unsigned char card, unsigned char other)
{
    self->entries = 0;
    self->count = 0;
    self->current = 0;
    self->frame = 0;
    self->linger = 60;
    Initialize(self);
    if (welcome == 1) AddTask(self, g_cardTaskFactories[0].create(), 0);
    AddTask(self, g_cardTaskFactories[1].create(), 1);
    if (card == 1) AddTask(self, g_cardTaskFactories[2].create(), 2);
    if (other == 1) AddTask(self, g_cardTaskFactories[3].create(), 3);
    self->entries[self->current].task->Start();
    return self;
}
#pragma exceptions reset

#ifndef GAME_CARD_TASK_MANAGER_CREATE_PRIVATE_H
#define GAME_CARD_TASK_MANAGER_CREATE_PRIVATE_H

/* Private view of the task ABI, shared in shape with CardTaskManager_Tick. */
class CardTask {
public:
    virtual void Render();
    virtual ~CardTask();
    virtual void Start();
};
struct CardTaskEntry {
    CardTask *task;
    int kind;
};
struct CardTaskManager {
    CardTaskEntry *entries;
    int count;
    int current;
    int frame;
    int linger;
};
struct CardTaskFactory {
    CardTask *(*create)();
    void *other;
};

#endif

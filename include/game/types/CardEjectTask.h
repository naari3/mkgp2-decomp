#ifndef GAME_TYPES_CARDEJECTTASK_H
#define GAME_TYPES_CARDEJECTTASK_H

/* Declare before including (each user already does): FlowTask, TextManager */

struct CardEjectTask : FlowTask {
    TextManager *texts;
    CardEjectTask(int id);
    ~CardEjectTask();
    virtual void _key3();
};

#endif /* GAME_TYPES_CARDEJECTTASK_H */

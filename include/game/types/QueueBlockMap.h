#ifndef GAME_TYPES_QUEUEBLOCKMAP_H
#define GAME_TYPES_QUEUEBLOCKMAP_H

/* Declare before including (each user already does): SteeringRing */

struct QueueBlockMap : SteeringRing {
    QueueBlockMap() {
        capacity = 0;
        count = 0;
        head = 0;
        data = 0;
    }
    ~QueueBlockMap() {
        if (this) {
            if (data) MemoryManager_TimedFree(data);
        }
    }
};

#endif /* GAME_TYPES_QUEUEBLOCKMAP_H */

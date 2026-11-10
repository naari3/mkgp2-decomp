#ifndef GAME_TYPES_PATHMANAGER_H
#define GAME_TYPES_PATHMANAGER_H

/* Declare before including (each user already does): CarObject */

struct PathManager {
    unsigned char data[0x4E8];
    PathManager(void *pathKey, CarObject *car, void *renderObj, float *x, float *y, float *z);
};

#endif /* GAME_TYPES_PATHMANAGER_H */

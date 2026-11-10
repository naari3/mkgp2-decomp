#ifndef GAME_TYPES_SYNCWAITER_H
#define GAME_TYPES_SYNCWAITER_H

struct SyncWaiter {
    char pad00[0x14];
    virtual ~SyncWaiter();
    virtual void v0C();
    virtual void v10();
    virtual void Update();
    virtual void Draw();
    char pad18[0x4C - 0x18];
    SyncWaiter();
};

#endif /* GAME_TYPES_SYNCWAITER_H */

#ifndef GAME_TYPES_JOBTASK_H
#define GAME_TYPES_JOBTASK_H

struct JobTask {
    virtual void v0();
    virtual void Kill();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
};

#endif /* GAME_TYPES_JOBTASK_H */

#ifndef GAME_TYPES_CLJOBRUNNER_H
#define GAME_TYPES_CLJOBRUNNER_H

struct clJobRunner {
    clJobRunner();
    virtual int Update() = 0;
    virtual void Draw() = 0;
    virtual ~clJobRunner();
};

#endif /* GAME_TYPES_CLJOBRUNNER_H */

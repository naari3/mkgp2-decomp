#ifndef GAME_TYPES_CLJOBRUNNER_H
#define GAME_TYPES_CLJOBRUNNER_H

struct clJobRunner {
    clJobRunner();
    virtual int Update();
    virtual void Draw();
    virtual ~clJobRunner();
};

#endif /* GAME_TYPES_CLJOBRUNNER_H */

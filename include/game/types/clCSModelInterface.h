#ifndef GAME_TYPES_CLCSMODELINTERFACE_H
#define GAME_TYPES_CLCSMODELINTERFACE_H

struct clCSModelInterface {
    virtual ~clCSModelInterface() {}
    virtual void Draw();
    clCSModelInterface() {}
};

#endif

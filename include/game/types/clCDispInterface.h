#ifndef GAME_TYPES_CLCDISPINTERFACE_H
#define GAME_TYPES_CLCDISPINTERFACE_H

struct clCDispInterface {
    virtual ~clCDispInterface() {}
    int id;
    clCDispInterface() {
        id = -1;
    }
};

#endif /* GAME_TYPES_CLCDISPINTERFACE_H */

#ifndef GAME_TYPES_CLCALLBACK_H
#define GAME_TYPES_CLCALLBACK_H

class clCallback {
public:
    clCallback() {}
    virtual ~clCallback();
    virtual void Exec() = 0;
};

#endif

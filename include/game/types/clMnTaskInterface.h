#ifndef GAME_TYPES_CLMNTASKINTERFACE_H
#define GAME_TYPES_CLMNTASKINTERFACE_H

/* Shared menu task ancestry. The implementations live in their original TUs. */
struct clYTaskInterface {
    virtual ~clYTaskInterface();
    int id;
    int field08;
    int field0C;
};

struct clMnTaskInterface : clYTaskInterface {
    clMnTaskInterface(int id);
    virtual ~clMnTaskInterface();
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif

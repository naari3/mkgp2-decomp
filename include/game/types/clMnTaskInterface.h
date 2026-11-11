#ifndef GAME_TYPES_CLMNTASKINTERFACE_H
#define GAME_TYPES_CLMNTASKINTERFACE_H

struct clYTaskInterface {
    virtual ~clYTaskInterface();
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    int id;
    int field08;
    int field0C;
    clYTaskInterface(int n) : id(n), field08(0), field0C(0) {}
};
inline clYTaskInterface::~clYTaskInterface() {}

struct clMnTaskInterface : clYTaskInterface {
    clMnTaskInterface(int id);
    virtual ~clMnTaskInterface();
};

#endif

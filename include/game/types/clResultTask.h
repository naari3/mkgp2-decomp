#ifndef GAME_TYPES_CLRESULTTASK_H
#define GAME_TYPES_CLRESULTTASK_H

extern "C" void MemoryManager_TimedFree(void *p);

/* The three task slots are declared in each base: their key functions live elsewhere. */
class clYTaskInterface {
public:
    virtual ~clYTaskInterface() {}
    virtual void Delete();
    virtual void Update();
    virtual void Draw();
    int id;
    int f8;
    int fC;
    clYTaskInterface(int i) : id(i), f8(0), fC(0) {}
};

class clCTaskInterface : public clYTaskInterface {
public:
    clCTaskInterface(int i) : clYTaskInterface(i) {}
    virtual ~clCTaskInterface() {}
    virtual void Delete();
    virtual void Update();
    virtual void Draw();
    static void operator delete(void *p) { MemoryManager_TimedFree(p); }
};


#endif

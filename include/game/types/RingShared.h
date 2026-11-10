#ifndef GAME_TYPES_RINGSHARED_H
#define GAME_TYPES_RINGSHARED_H

struct RingShared {
    char *ptr;
    unsigned long *refs;
    RingShared(void *p) { init(p); }
    void init(void *p) {
        ptr=(char *)p; refs=0;
        try { if(ptr) refs=new unsigned long(1); }
        catch(...) { MemoryManager_Free(ptr); throw; }
    }
    ~RingShared();
};

#endif /* GAME_TYPES_RINGSHARED_H */

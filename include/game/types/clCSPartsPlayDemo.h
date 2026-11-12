#ifndef GAME_TYPES_CLCSPARTS_PLAY_DEMO_H
#define GAME_TYPES_CLCSPARTS_PLAY_DEMO_H
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
struct clCSSceneAttract {
    struct clTaskInterface {
        virtual ~clTaskInterface() {}
        virtual void Destroy();
        virtual void Update();
        virtual void Draw();
        virtual unsigned char Done();
    };
};
struct CourseLoader {
    char opaque[0x5C];
    CourseLoader(void *, int);
};
struct clCSPartsPlayDemo : clCSSceneAttract::clTaskInterface {
    virtual ~clCSPartsPlayDemo();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    virtual unsigned char Done();
    CourseLoader *loader;
    unsigned char done;
    clCSPartsPlayDemo(void *desc) {
        done = 0;
        loader = new CourseLoader(desc, 0);
        if (loader == 0) done = 1;
    }
};
#endif

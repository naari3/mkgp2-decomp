#ifndef GAME_TYPES_CLCSSCENEPLAYDEMO_H
#define GAME_TYPES_CLCSSCENEPLAYDEMO_H
#include "game/types/clSceneInterface.h"
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
struct CourseLoaderScene {
    char opaque[0x5C];
    CourseLoaderScene(void *, void *);
};
struct clCSScenePlayDemo : clSceneInterface {
    virtual ~clCSScenePlayDemo();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    void PrintClassName();
    CourseLoaderScene *loader;
    clCSScenePlayDemo(void *desc, void *arg) {
        done = 0;
        loader = new CourseLoaderScene(desc, arg);
        if (loader == 0) done = 1;
    }
};
#endif

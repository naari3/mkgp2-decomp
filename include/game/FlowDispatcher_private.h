#ifndef FLOW_DISPATCHER_PRIVATE_H
#define FLOW_DISPATCHER_PRIVATE_H
#include "game/types/FlowObject.h"
struct FlowEntry {
    FlowObject *(*create)();
    const char *name;
    int field8;
};
struct FlowDispatcher {
    FlowEntry *entries;
    int currentIndex;
    FlowObject *current;
    int count;
    FlowObject *menu;
    int overlay;
    float average[3];
    float total[3];
    int frames;
    int cleanupTag;
};
extern "C" {
extern char lbl_802E89A0[];
extern const char lbl_806D2264[4];
void DebugPrintf(const char *, ...);
void SpriteHandlePool_GC();
void fn_80121210();
void SceneFlow_DefaultGetZero(int);
void SceneFlow_InitCleanupList();
void SceneFlow_SetCleanupTag(int);
int HeapStats_DumpForTag(const char *, int);
}
#endif

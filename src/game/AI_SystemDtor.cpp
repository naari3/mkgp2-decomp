#include "game/AIPairPrivate.h"
class AIOwnedController {
public:
    virtual void v8();
    virtual ~AIOwnedController();
};
struct AISystemOwner { void *storage; };
extern "C" {
extern AIOwnedController *Read_U32[8];
extern AIPairRecord lbl_806793D8[8];
extern const float lbl_806DA3F4;
extern void *lbl_806D1928;
extern void *g_pathSystem;
void fn_801DE7DC();
void fn_801DB928();
void fn_801DC630();
void fn_801DC5C0();
void fn_801DE15C();
void fn_801DE6E8();
void fn_801DB8BC();
void MemoryManager_TimedFree(void *);
}
static inline void ResetRecord(AIPairRecord *p) {
    p->driver = 0;
    p->kartId = -1;
    p->field08 = 0;
    p->waypoint = 0;
    p->field1C = 0;
    p->field20 = lbl_806DA3F4;
    p->nearestKart = -1;
    p->nearestDriver = 0;
    p->distanceSquared = lbl_806DA3F4;
    p->field24 = 0;
    p->field28 = -1;
}
extern "C" AISystemOwner *AI_SystemDtor(AISystemOwner *self, short deleting) {
    if (self) {
        for (int i = 7; i >= 0; --i) {
            if (Read_U32[i]) {
                delete Read_U32[i];
                Read_U32[i] = 0;
            }
        }
        for (int i = 0; i < 8; ++i) ResetRecord(&lbl_806793D8[i]);
        fn_801DE7DC();
        fn_801DB928();
        fn_801DC630();
        fn_801DC5C0();
        fn_801DE15C();
        fn_801DE6E8();
        fn_801DB8BC();
        lbl_806D1928 = 0;
        g_pathSystem = 0;
        if (self) MemoryManager_TimedFree(self->storage);
        if (deleting > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

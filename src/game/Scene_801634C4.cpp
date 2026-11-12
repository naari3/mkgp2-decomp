/* Deferred generation: definitions are in reverse target order.
 * RTTI names remain in the original replay configuration pool. */
#include "game/types/clCSPartsPlayDemo.h"
extern "C" void fn_80163C68(void *);
extern "C" unsigned char fn_80163EF4(void *);
extern "C" void fn_801638B4(void *, int);

extern "C" clCSPartsPlayDemo *fn_80163614(void *desc) {
    return new clCSPartsPlayDemo(desc);
}
void clCSPartsPlayDemo::Destroy() { delete this; }
unsigned char clCSPartsPlayDemo::Done() { return done; }
clCSPartsPlayDemo::~clCSPartsPlayDemo() {
    if (loader) fn_801638B4(loader, 1);
}
void clCSPartsPlayDemo::Update() {
    if (!done && loader) {
        if (fn_80163EF4(loader) == 1) done = 1;
    }
}
void clCSPartsPlayDemo::Draw() {
    if (!done && loader) fn_80163C68(loader);
}

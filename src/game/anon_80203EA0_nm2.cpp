#include "game/FlowScene.h"
#include <list>

/* SceneListImpl::Draw (fn_80204218).  The scene list is a
 * std::list<FlowTask *> from the genuine MSL C++ header
 * (docs/notes/msl_cpp.md): `it = erase(it)` converts the
 * list<void const *> iterator back, which gives the two stack copies no
 * hand-written list reproduced.  The other units of this TU still use the
 * hand-written DoublyLinkedList layout from FlowScene.h, so this unit
 * declares the same object with the real container. */
struct SceneListStd {
    virtual ~SceneListStd();
    virtual void Update();
    virtual void Draw();
    std::list<FlowTask *> entries;
};

void SceneListStd::Draw() {
    std::list<FlowTask *>::iterator it = entries.begin();
    while (it != entries.end()) {
        FlowTask *t = *it;
        bool run;
        if (t->field08 > 0) {
            run = 0;
            t->field08--;
        } else {
            if (t->field0C == 1) {
                t->field0C = 2;
            }
            run = t->field0C <= 0;
        }
        if (run) {
            t->Draw();
        }
        if (t->field0C >= 2) {
            t->Finish();
            it = entries.erase(it);
        } else {
            ++it;
        }
    }
}

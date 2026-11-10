#include "game/FadeLogoDraw_private.h"
#include <list>

/* TaskListImpl::Draw (fn_8020F080).  The task list is a std::list<PopupTask *>
 * from the genuine MSL C++ header (docs/notes/msl_cpp.md): `it = erase(it)`
 * converts the list<void const *> iterator back, which gives the two stack
 * copies no hand-written list reproduced.  The other units of this TU still
 * use the hand-written TaskEntries layout from the private header, so this
 * unit declares the same object with the real container. */
struct TaskListStd {
    virtual ~TaskListStd();
    virtual void Update();
    virtual void Draw();
    std::list<PopupTask *> entries;
};

void TaskListStd::Draw() {
    std::list<PopupTask *>::iterator it = entries.begin();
    while (it != entries.end()) {
        if ((*it)->CanDraw()) {
            (*it)->Draw();
        }
        if ((*it)->field0C >= 2) {
            (*it)->Finish();
            it = entries.erase(it);
        } else {
            ++it;
        }
    }
}

#include "game/singleton.h"

class clItemBoxResponder {
public:
    virtual void Respond() = 0;
    virtual ~clItemBoxResponder();
    clItemBoxResponder(void *owner);

    void *owner;
    int registered;
};

extern "C" {
extern void *lbl_806D10D0;
void clItemBoxManager_UnregisterResponder(void *, clItemBoxResponder *);
void clItemBoxManager_RegisterResponder(void *, clItemBoxResponder *);
}
void operator delete(void *);

clItemBoxResponder::~clItemBoxResponder() {
    if (SINGLETON_INSTANCE(lbl_806D10D0) != 0) {
        clItemBoxManager_UnregisterResponder(SINGLETON_INSTANCE(lbl_806D10D0), this);
    }
}

clItemBoxResponder::clItemBoxResponder(void *owner) {
    this->owner = owner;
    registered = 0;
    if (SINGLETON_INSTANCE(lbl_806D10D0) == 0) {
        return;
    }
    clItemBoxManager_RegisterResponder(SINGLETON_INSTANCE(lbl_806D10D0), this);
}

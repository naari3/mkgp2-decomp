/*
 * Small owner objects with a single owned task at +0x10 @ 0x801FE8B8..0x801FEA70.
 */

#include "game/FlowScene.h"

struct OwnerBase {
    virtual ~OwnerBase() {}
    int field04;
    int field08;
    int field0C;
};

struct TaskOwnerA : OwnerBase {
    VHolder<VObject> task;
    virtual void _key();
    ~TaskOwnerA();
};

struct OwnerBaseB {
    virtual ~OwnerBaseB() {}
    int field04;
    int field08;
    int field0C;
};

struct TaskOwnerB : OwnerBaseB {
    VHolder<VObject> task;
    virtual void _key();
    ~TaskOwnerB();
};

TaskOwnerA::~TaskOwnerA() {
}

TaskOwnerB::~TaskOwnerB() {
}

/* clAttract tail of ZoneList; kept as a separate nondeferred unit so its
 * class action follows the area-family tables without changing text order. */
#include "game/types/size_t.h"
extern "C" void *fn_8014F6A4(void);
void *operator new(size_t);
void operator delete(void*);
struct ModeTaskBase {
    virtual ~ModeTaskBase();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

struct ModeTask : ModeTaskBase {
    unsigned char done;
};

#include "game/types/clJobRunner.h"

struct clAttract : clJobRunner {
    ModeTask *task;
    clAttract() { task = (ModeTask *)fn_8014F6A4(); }
    virtual int Update();
    virtual void Draw();
    virtual ~clAttract();
};

void clAttract::Draw() {
    if (task) {
        task->Draw();
    }
}

int clAttract::Update() {
    if (task) {
        if (task->done) {
            task->Finish();
            task = 0;
        } else {
            task->Update();
        }
    }
    return -2;
}

clAttract::~clAttract() {
    if (task) {
        task->Finish();
        task = 0;
    }
}

extern "C" clAttract *fn_80124064(void) {
    return new clAttract;
}


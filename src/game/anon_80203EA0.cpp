#include "game/FlowScene.h"
#include "game/FlowMsgPopup.h"

/*
 * Message popup service (0x80203EA0..0x80204474): open/close entry points,
 * service init/shutdown, the SceneListImpl task list and the FlowTask
 * base ctor/dtor.
 */

extern "C" {
void DebugPrintf(const char *fmt, ...);
void PreloadResource(int id);
void fn_80120A08(int id);
extern const char lbl_803C250C[];
extern const char lbl_803C2528[];

int fn_80203EA0(void);
int fn_80203F5C(int msg);
void fn_802040B0(void);
void fn_80204130(int layer);
}

int fn_80203EA0(void) {
    return CloseMsgPopup();
}

int fn_80203F5C(int msg) {
    return OpenMsgPopup(msg);
}

void fn_802040B0(void) {
    lbl_806D0250.cur = -1;
    lbl_806D0250.pending = -1;
    if (lbl_806D19E8) {
        delete lbl_806D19E8;
        lbl_806D19E8 = 0;
    }
    lbl_806D19EC = 0;
    fn_80120A08(0x72F);
    fn_80120A08(0x731);
    DebugPrintf(lbl_803C250C);
}

void fn_80204130(int layer) {
    DebugPrintf(lbl_803C2528);
    if (lbl_806D19E8 == 0) {
        lbl_806D19E8 = new SceneListImpl;
    }
    lbl_806D19EC = layer;
    PreloadResource(0x72F);
    PreloadResource(0x731);
}

void SceneListImpl::Sort() {
    ListIter a;
    a.node = entries.first;
    ListIter last;
    last.node = entries.last;
    while (a.node != last.node) {
        ListIter b;
        b.node = a.node->next;
        while (b.node != entries.End()) {
            FlowTask *ta;
            FlowTask *tb;
            tb = b.node->task;
            ta = a.node->task;
            if ((unsigned int)ta->id > (unsigned int)tb->id) {
                a.node->task = tb;
                b.node->task = ta;
            }
            b.node = b.node->next;
        }
        a.node = a.node->next;
    }
}

void SceneListImpl::Draw() {
    ListNode *end = entries.End();
    ListIter it;
    it.node = entries.first;
    while (it.node != end) {
        FlowTask *t = it.node->task;
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
            it = Remove(it);
        } else {
            it.node = it.node->next;
        }
    }
}

void SceneListImpl::Update() {
    Sort();
    ListIter it;
    it.node = entries.End()->next;
    while (it.node != entries.End()) {
        FlowTask *t = it.node->task;
        if (t->CanUpdate()) {
            t->Update();
        }
        it.node = it.node->next;
    }
}

void SceneListImpl::Kill(unsigned int id) {
    ListIter it;
    it.node = entries.first;
    while (it.node != entries.End()) {
        FlowTask *t = it.node->task;
        if (id == (unsigned int)t->id) {
            t->field0C = 1;
        }
        it.node = it.node->next;
    }
}

FlowTask::~FlowTask() {}

FlowTask::FlowTask(int id_) : FlowRoot(id_) {}

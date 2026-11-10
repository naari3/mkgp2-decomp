/*
 * 0x8020E3D0..0x8020F220: fading logo task (resource 0x2AFA) and the task
 * list that runs it.
 */

#include "game/FadeLogoTaskListOwner.h"

#pragma auto_inline off

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    float Value();
};

#include "game/types/FadeKeyBase.h"

#include "game/types/FadeKey.h"

struct FadeSeq {
    virtual ~FadeSeq();
    virtual bool Done();
    virtual void Update();
    bool loop;
    FadeKey *head;
    FadeKey *cur;
    Tween *tween;
    FadeSeq(FadeKey *h, bool l);
};

struct FadeTaskBase : PopupTask {
    int layer;
    FadeTaskBase(int layer_, int id_) : PopupTask(id_), layer(layer_) {}
    virtual ~FadeTaskBase() {}
    virtual void _keyFB();
};

struct FadeLogo : FadeTaskBase {
    virtual void _keyF();
    VHolder<FadeKey> key1;
    VHolder<FadeSeq> seq1;
    VHolder<FadeKey> key2;
    VHolder<FadeSeq> seq2;
    VHolder<FadeKey> key3;
    VHolder<FadeSeq> seq3;
    FadeLogo(int layer_, int id_);
    ~FadeLogo();
    void Finish();
    void Update();
    void Draw();
};

extern "C" {
extern const float lbl_806DACD8;
extern const float lbl_806DACDC;
extern const float lbl_806DACE0;
extern const float lbl_806DACE4;
extern const float lbl_806DACE8;
extern const float lbl_806DACEC;
extern const float lbl_806DACF0;
extern const float lbl_806DACF4;
extern const float lbl_806DACF8;
void fn_8011FAFC(ResCtrl *ctrl, int layer);
}

FadeLogoScene::~FadeLogoScene() {
}

void FadeLogo::Draw() {
}

void FadeLogo::Update() {
    ResCtrl rc;
    rc.resId = 0x2AFA;
    rc.Show(lbl_806DACD8, seq1.p->tween->Value(), lbl_806DACDC);
    rc.SetScaleXY(seq2.p->tween->Value(), seq3.p->tween->Value());
    fn_8011FAFC(&rc, layer);
    seq1.p->Update();
    seq2.p->Update();
    seq3.p->Update();
    if (seq1.p->Done()) {
        field0C = 1;
    }
}

void FadeLogo::Finish() {
    delete this;
}

FadeLogo::FadeLogo(int layer_, int id_) : FadeTaskBase(layer_, id_) {
    key1.Reset(new FadeKey(11, lbl_806DACE0, lbl_806DACE4));
    key1.p->Append(8, lbl_806DACE8);
    key1.p->Append(7, lbl_806DACE4);
    key1.p->Append(0x5A, lbl_806DACE4);
    key2.Reset(new FadeKey(11, lbl_806DACDC, lbl_806DACEC));
    key2.p->Append(8, lbl_806DACF0);
    key2.p->Append(7, lbl_806DACDC);
    key2.p->Append(0x5A, lbl_806DACDC);
    key3.Reset(new FadeKey(11, lbl_806DACDC, lbl_806DACF4));
    key3.p->Append(8, lbl_806DACF8);
    key3.p->Append(7, lbl_806DACDC);
    key3.p->Append(0x5A, lbl_806DACDC);
    seq1.Reset(new FadeSeq(key1.p, false));
    seq2.Reset(new FadeSeq(key2.p, false));
    seq3.Reset(new FadeSeq(key3.p, false));
}

TaskListOwner::~TaskListOwner() throw() {
    delete p;
}

TaskListImpl::~TaskListImpl() {
    KillAll();
}

/* fakematch (out-of-line base dtor): the original emitted the weak copy of
 * the inline ~TaskListBase() (fn_8020EC70) here, right after
 * ~TaskListImpl(), because this TU owned the TaskListBase vtable. That
 * vtable lives in unowned .data, so the natural code
 *     virtual ~TaskListBase() { KillAll(); entries.Clear(); }
 * has no out-of-line copy here. This twin class has the same layout and
 * body, and its vtable reference is renamed to lbl_804ECAC0. */
struct TaskListBaseCopy {
    virtual void _key();
    virtual ~TaskListBaseCopy();
    TaskEntries entries;
};

TaskListBaseCopy::~TaskListBaseCopy() {
    ((TaskListBase *)this)->KillAll();
    entries.Clear();
}

static inline void MarkTasksFinished(TaskNode *n, TaskNode *end) {
    for (; n != end; n = n->next) {
        n->task->field0C = 1;
    }
}

void TaskListBase::KillAll() {
    MarkTasksFinished(entries.first, entries.End());
    while (entries.count > 0) {
        Update();
        Draw();
    }
}

bool TaskListBase::Add(PopupTask *task, int delay) {
    if (task == 0) {
        return false;
    }
    TaskNode *n = entries.first;
    TaskNode *end = (TaskNode *)&entries.last;
    while (n != end) {
        PopupTask *t = n->task;
        if (t != 0 && task->id < t->id) {
            break;
        }
        n = n->next;
    }
    task->field08 = delay;
    TaskIter it(n);
    entries.Insert(it, task);
    return true;
}

FadeLogo::~FadeLogo() {
}

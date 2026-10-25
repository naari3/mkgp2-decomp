/*
 * 0x8020E3D0..0x8020F220: fading logo task (resource 0x2AFA) and the task
 * list that runs it.
 */

#include "game/FadeLogo.h"

#pragma auto_inline off

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    float Value();
};

struct FadeKeyBase {
    virtual ~FadeKeyBase();
    int dur;
    FadeKeyBase(int d) : dur(d) {}
};

struct FadeKey : FadeKeyBase {
    float from;
    float to;
    VHolder<FadeKey> next;
    FadeKey(int d, float f, float t) : FadeKeyBase(d), from(f), to(t) {}
    ~FadeKey();
    void Append(int dur, float to);
};

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
};

struct FadeLogo : FadeTaskBase {
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

inline FadeLogoScene::FadeLogoScene(int layer_, int id_) : PopupTask(id_), layer(layer_), list(new TaskListImpl) {
    TaskListImpl *l = list.p;
    l->Add(new FadeLogo(layer_, 0), 0);
}

extern "C" FadeLogoScene *fn_8020E3D0(int layer, int id) {
    return new FadeLogoScene(layer, id);
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

TaskListImpl::~TaskListImpl() {
    KillAll();
}

void TaskListBase::KillAll() {
    TaskNode *end = entries.End();
    TaskNode *n;
    for (n = entries.first; n != end; n = n->next) {
        n->task->field0C = 1;
    }
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
    TaskNode *end = entries.End();
    while (n != end) {
        PopupTask *t = n->task;
        if (t != 0 && task->id < t->id) {
            break;
        }
        n = n->next;
    }
    task->field08 = delay;
    entries.Insert(TaskIter(n), task);
    return true;
}

FadeLogo::~FadeLogo() {
}

void TaskListImpl::Sort() {
    TaskIter a;
    a.node = entries.first;
    TaskIter last;
    last.node = entries.last;
    while (a.node != last.node) {
        TaskIter b;
        b.node = a.node->next;
        while (b.node != entries.End()) {
            PopupTask *ta;
            PopupTask *tb;
            tb = b.node->task;
            ta = a.node->task;
            if (ta->id > tb->id) {
                a.node->task = tb;
                b.node->task = ta;
            }
            b.node = b.node->next;
        }
        a.node = a.node->next;
    }
}

void TaskListImpl::Draw() {
    TaskNode *end = entries.End();
    TaskIter it;
    it.node = entries.first;
    while (it.node != end) {
        if (it.node->task->CanDraw()) {
            it.node->task->Draw();
        }
        if (it.node->task->field0C >= 2) {
            it.node->task->Finish();
            it = Remove(it);
        } else {
            it.node = it.node->next;
        }
    }
}

void TaskListImpl::Update() {
    Sort();
    TaskIter it;
    it.node = entries.End()->next;
    while (it.node != entries.End()) {
        PopupTask *t = it.node->task;
        if (t->CanUpdate()) {
            t->Update();
        }
        it.node = it.node->next;
    }
}

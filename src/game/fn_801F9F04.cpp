#include "game/FlowScene.h"
#include "game/types/clSceneInterface.h"
#include "game/types/clMnTaskInterface.h"

extern "C" {
extern int lbl_806D19B8, lbl_806D0108, lbl_806D00C8;
void SetSyncTarget(int); void *fn_801F8E58();
void fn_80207DA8(int); void fn_80204130(int); void PreloadResource(int);
char *fn_80271340(void *, int, void *, void *, int);
void fn_802040B0(); void fn_80207D38(); void fn_801F8E54();
void fn_8011FAB8(); void fn_80203BEC(); void fn_80207810();
void HSD_StateInvalidate(int); void fn_80203C24(); void fn_80207848();
}
struct clMnCardT0 : clMnTaskInterface {
    VHolder<FlowSceneList> seq;
    VHolder<FlowFaderI> fade;
    int state, result;
    virtual ~clMnCardT0();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    void Start();
    void Advance();
    clMnCardT0() : clMnTaskInterface(0), seq(new SceneListImpl), fade(new FlowFaderI), state(0), result(0) {
        PreloadResource(0x1ECD); PreloadResource(0x72F); PreloadResource(0x734); PreloadResource(0x730);
        fade.p->Set(0, 0, 1);
    }
};

struct CardInput {
    virtual void v0(); virtual void v1(); virtual float v2();
    virtual void v3(); virtual float v4(); virtual float v5();
    virtual unsigned char Pressed(int);
};
struct CardMode { int pad[2]; int light; };
struct StepSeq { void Add(void *, int); };
struct Obj801FA6A4 { char pad[0x48]; Obj801FA6A4(int,int); };
struct Obj801FA864 { char pad[0x48]; Obj801FA864(int,int); };
extern "C" {
extern const int lbl_806DA860;
extern int lbl_803BFF40[], lbl_806D00D0, lbl_806D00D8, lbl_806D00E0, lbl_806D00F0, lbl_806D00F8, lbl_806D0100;
void *GetInputManager(); CardInput *InputMgr_GetPlayer(void *,int);
CardMode *fn_801DAEC0(); void fn_80203EA0();
void fn_8020A7CC(void *,int,int,int);
void fn_801FEF18(void *,int); void fn_80202A5C(int);
void fn_802043B8(void *,int); void fn_801FFFF4(void *); void fn_80201148(void *); int fn_80203E30();
char *fn_801FE404(); int Sci2Card_GetUnpackStatusCode(); unsigned char Sci2Card_GetReceiptTestFlag();
void fn_80203F5C(int); void *fn_801FC1E0(int); unsigned char ServiceValue_Get();
void *fn_801FF00C(int,int); void *fn_8020007C(int,int,int); void *fn_802011D0(int,int); void *fn_801FB634(int);
void fn_80120A08(int);
}

struct clMnCard : clSceneInterface {
    virtual ~clMnCard();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    VHolder<FlowSceneList> seq;
    int step;
    clMnCard() : seq(new SceneListImpl), step(0) {
        SetSyncTarget(9); lbl_806D19B8 = 0;
        fn_801F8E58(); fn_80207DA8(6); fn_80204130(7);
        FlowSceneList *list = seq.p;
        fn_801F4DF0(list, (FlowTask *)new clMnCardT0, 0);
        FlowTask *task = fn_801F4DC0(seq.p, 0);
        if (task) {
            int n = step;
            *(int *)((char *)dynamic_cast<clMnCardT0 *>((clMnTaskInterface *)task) + 0x1C) = n;
        }
    }
};

void clMnCardT0::Finish() { delete this; }
clMnCardT0::~clMnCardT0() {
    fn_801F4D3C(seq.p);
    fn_80120A08(0x72F); fn_80120A08(0x734); fn_80120A08(0x730);
}
void clMnCardT0::Start() { clMnCardT0 *self = this;

    int mode;
    void *p;

    if (ServiceValue_Get()) {
        fn_8020A7CC(self->fade.p, 0, 0x78, 0x78);
        fn_80203F5C(9);
        self->state = 1;
        return;
    }
    mode = *(int *)(fn_801FE404() + 0x16C);
    {
        StepSeq *seq = (StepSeq *)self->seq.p;
        seq->Add(fn_801FF00C(0, 8), 0);
    }
    p = fn_801F4DC0(self->seq.p, 8);
    if (p != 0) {
        fn_801FEF18(fn_80271340(p, 0, &lbl_806D00D0, &lbl_806D00C8, 0), lbl_803BFF40[0] + 1);
    }
    {
        StepSeq *seq = (StepSeq *)self->seq.p;
        seq->Add(fn_8020007C(0, 0, 9), 0x32);
    }
    {
        StepSeq *seq = (StepSeq *)self->seq.p;
        seq->Add(fn_802011D0(0, 0xA), 0x32);
    }
    if (mode == 2) {
        StepSeq *seq = (StepSeq *)self->seq.p;
        seq->Add(fn_801FB634(2), 0x28);
    } else if (Sci2Card_GetUnpackStatusCode() == 5) {
        /* Reusing the dead mode slot reproduces the original register choice. */
        mode = (int)self->seq.p;
        ((StepSeq *)mode)->Add(new Obj801FA864(0, 4), 0x28);
    } else {
        StepSeq *seq = (StepSeq *)self->seq.p;
        seq->Add(fn_801FB634(2), 0x28);
    }
    fn_8020A7CC(self->fade.p, 0, 0x3C, 0x3C);
    self->state = 2;
}

void clMnCardT0::Advance() { clMnCardT0 *self = this;

    void *p = fn_801F4DC0(self->seq.p, 2);
    if (p) self->result = *(int *)(fn_80271340(p, 0, &lbl_806D00F0, &lbl_806D00C8, 0) + 0x24);
    int n = 0;
    if (p) n = *(int *)(fn_80271340(p, 0, &lbl_806D00F0, &lbl_806D00C8, 0) + 0x20);
    void *o = fn_801F4DC0(self->seq.p, 8);
    if (o) fn_801FEF18(fn_80271340(o, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n);
    if (!p) {
        p = (void *)*(int *)(fn_801FE404() + 0x16C);
        if (self->result == 0) {
            if (Sci2Card_GetUnpackStatusCode() == 5) {
                if ((int)p == 2) self->state = 8;
                else {
                    p = self->seq.p;
                    ((StepSeq *)p)->Add(new Obj801FA6A4(0, 4), 0);
                    fn_80202A5C(0x10);
                    self->state = 5;
                }
            } else self->state = 8;
        } else if ((int)p == 2) self->state = 8;
        else if (Sci2Card_GetReceiptTestFlag()) {
            fn_8020A7CC(self->fade.p, 0, 0x78, 0x78);
            fn_80203F5C(10);
            self->state = 1;
        } else {
            p = self->seq.p;
            ((StepSeq *)p)->Add(fn_801FC1E0(3), 0);
            self->state = 4;
            fn_80202A5C(0x11);
        }
    }
}

void clMnCardT0::Update() { clMnCardT0 *self = this;

    int n4;
    void *p4;
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (self->state) {
    case 0: Start(); break;
    case 1:
        if (input->Pressed(lbl_806DA860)) { CardMode *m = fn_801DAEC0(); m->light = 0; }
        else { CardMode *m = fn_801DAEC0(); m->light = 1; }
        self->fade.p->Step();
        if (input->Pressed(lbl_806DA860) || self->fade.p->b >= self->fade.p->a) {
            fn_80203EA0(); self->state = 8;
        }
        break;
    case 2:
        self->fade.p->Step();
        if (self->fade.p->b >= self->fade.p->a) {
            fn_8020A7CC(self->fade.p, 0, 0, 1);
            if (fn_801F4DC0(self->seq.p, 4)) {
                self->state = 5; fn_80202A5C(0x10);
            } else { self->state = 3; fn_80202A5C(0x12); }
        }
        break;
    case 3: Advance(); break;
    case 4: {
        p4 = fn_801F4DC0(self->seq.p, 3);
        if (p4) self->result = *(int *)(fn_80271340(p4, 0, &lbl_806D00F8, &lbl_806D00C8, 0) + 0x24);
        n4 = 0;
        if (p4) n4 = *(int *)(fn_80271340(p4, 0, &lbl_806D00F8, &lbl_806D00C8, 0) + 0x20);
        void *q = fn_801F4DC0(self->seq.p, 8);
        if (q) fn_801FEF18(fn_80271340(q, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n4);
        if (!p4) self->state = 8;
        break;
    }
    case 5: {
        int n;
        void *p = fn_801F4DC0(self->seq.p, 4);
        if (p) self->result = *(int *)(fn_80271340(p, 0, &lbl_806D0100, &lbl_806D00C8, 0) + 0x24);
        n = 0;
        if (p) n = *(int *)(fn_80271340(p, 0, &lbl_806D0100, &lbl_806D00C8, 0) + 0x20);
        void *q = fn_801F4DC0(self->seq.p, 8);
        if (q) fn_801FEF18(fn_80271340(q, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n);
        if (!p) self->state = 8;
        break;
    }
    case 8: {
        fn_802043B8(self->seq.p, 8);
        void *p = fn_801F4DC0(self->seq.p, 9);
        if (p) fn_801FFFF4(fn_80271340(p, 0, &lbl_806D00D8, &lbl_806D00C8, 0));
        p = fn_801F4DC0(self->seq.p, 10);
        if (p) fn_80201148(fn_80271340(p, 0, &lbl_806D00E0, &lbl_806D00C8, 0));
        fn_80203EA0(); self->state = 9;
        break;
    }
    case 9:
        if (self->seq.p->entries.count <= 0 && fn_80203E30() == -1) { self->field0C = 1; self->state = -1; }
        break;
    }
    self->seq.p->Update();
}

void clMnCardT0::Draw() { seq.p->Draw(); }

clMnCard::~clMnCard() {
    fn_801F4D3C(seq.p);
    fn_802040B0(); fn_80207D38(); fn_801F8E54();
}
extern "C" clMnCard *fn_801FA024() { return new clMnCard; }
void clMnCard::Destroy() { delete this; }
void clMnCard::Update() {
    if (done == 0) {
        FlowTask *p = fn_801F4DC0(seq.p, 0);
        if (p != 0) {
            step = *(int *)((char *)dynamic_cast<clMnCardT0 *>((clMnTaskInterface *)p) + 0x1C);
        }
        if (seq.p->entries.count <= 0) done = 1;
        seq.p->Update();
        fn_80207848(); fn_80203C24();
    }
}
void clMnCard::Draw() {
    if (done == 0) {
        seq.p->Draw();
        fn_80207810(); fn_80203BEC(); fn_8011FAB8(); HSD_StateInvalidate(-1);
    }
}

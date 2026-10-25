#include "game/FlowYesNo.h"

/*
 * Two-choice selector task and its blinking cursor (0x80204474..0x802052E0).
 */

void YesNoTask::Draw() {
    list.p->Draw();
}

void YesNoTask::Update() {
    FlowTask *t0 = fn_801F4DC0(list.p, 0);
    YesNoButtonL *l = dynamic_cast<YesNoButtonL *>(t0);
    FlowTask *t1 = fn_801F4DC0(list.p, 1);
    YesNoButtonR *r = dynamic_cast<YesNoButtonR *>(t1);
    int sel = choice;
    if (l && r) {
        YESNO_SET_SELECTED(l, sel == 0);
        YESNO_SET_SELECTED(r, sel != 0);
    }
    FlowTask *c = fn_801F4DC0(list.p, 0xA);
    if (c) {
        YesNoCursor *cur = dynamic_cast<YesNoCursor *>(c);
        cur->visible = sel == 0;
    }
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
}

extern "C" void fn_80204740(VObject *obj) {
    delete obj;
}

extern "C" YesNoTask *fn_80204778(int kind, unsigned char defYes, int layer, int id) {
    return new YesNoTask(kind, defYes, layer, id);
}

YesNoTask::~YesNoTask() {}

YesNoTask::YesNoTask(int kind_, unsigned char defYes, int layer_, int id)
    : FlowTask(id), list(new SceneListImpl), layer(layer_), kind(kind_), choice(defYes == 0), field20(0) {
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new YesNoButtonL(kind_, layer_), 0);
    }
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new YesNoButtonR(kind_, layer_), 0);
    }
    {
        YesNoButton *b = dynamic_cast<YesNoButton *>(fn_801F4DC0(list.p, 0));
        if (b) {
            if (kind_ == 0xD) {
                b->x = lbl_806DAB44;
                b->y = lbl_806DAB48;
            } else {
                b->x = lbl_806DAB44;
                b->y = lbl_806DAB4C;
            }
            b->SetSelected(choice == 0);
        }
    }
    {
        YesNoButton *b = dynamic_cast<YesNoButton *>(fn_801F4DC0(list.p, 1));
        if (b) {
            if (kind_ == 0xD) {
                b->x = lbl_806DAB50;
                b->y = lbl_806DAB48;
            } else {
                b->x = lbl_806DAB50;
                b->y = lbl_806DAB4C;
            }
            b->SetSelected(choice != 0);
        }
    }
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new YesNoCursor(layer_), 0x14);
    }
    FlowTask *c = fn_801F4DC0(list.p, 0xA);
    if (c) {
        bool v = choice == 0;
        dynamic_cast<YesNoCursor *>(c)->visible = v;
    }
}

void YesNoCursor::Draw() {
    list.p->Draw();
}

static inline void SpawnSpark(FlowSceneList *l, int id, int layer, float x, float y, unsigned char flag) {
    fn_801F4DF0(l, new YesNoSpark(id, layer, x, y, flag), 0);
}

void YesNoCursor::Update() {
    int t = fn_8020A788(timer.p);
    if (t % 15 == 0) {
        int id = (t / 15) * 2;
        FlowSceneList *l = list.p;
        float px = x;
        unsigned char f = visible;
        float py = y;
        int lay = layer;
        fn_801F4DF0(l, new YesNoSpark(id, lay, px, py, f), 0);
    }
    list.p->Update();
    timer.p->Step();
    if (timer.p->Done()) {
        timer.p->b = 0;
    }
}

extern "C" void fn_802051B0(VObject *obj) {
    delete obj;
}

YesNoCursor::~YesNoCursor() {
    fn_801F4D3C(list.p);
    fn_80120A08(0x8A3);
}

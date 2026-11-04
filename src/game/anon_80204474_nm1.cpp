#include "game/FlowYesNo.h"

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

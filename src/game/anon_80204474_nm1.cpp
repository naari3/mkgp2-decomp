#include "game/FlowYesNoRescue.h"

/* Use the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D02A0[8];
extern unsigned char YesNoButtonL_RTTI_806D02C0[8];
extern unsigned char YesNoButtonR_RTTI_806D02C8[8];
extern unsigned char YesNoCursor_RTTI_806D02B8[8];
}

static inline YesNoButtonL *CastYesNoButtonL(FlowTask *task) {
    return (YesNoButtonL *)fn_80271340(task, 0, YesNoButtonL_RTTI_806D02C0, FlowTask_RTTI_806D02A0, 0);
}

static inline YesNoButtonR *CastYesNoButtonR(FlowTask *task) {
    return (YesNoButtonR *)fn_80271340(task, 0, YesNoButtonR_RTTI_806D02C8, FlowTask_RTTI_806D02A0, 0);
}

static inline YesNoCursor *CastYesNoCursor(FlowTask *task) {
    return (YesNoCursor *)fn_80271340(task, 0, YesNoCursor_RTTI_806D02B8, FlowTask_RTTI_806D02A0, 0);
}


void YesNoTask::Update() {
    FlowTask *t0 = fn_801F4DC0(list.p, 0);
    YesNoButtonL *l = CastYesNoButtonL(t0);
    FlowTask *t1 = fn_801F4DC0(list.p, 1);
    YesNoButtonR *r = CastYesNoButtonR(t1);
    int sel = choice;
    if (l && r) {
        YESNO_SET_SELECTED(l, sel == 0);
        YESNO_SET_SELECTED(r, sel != 0);
    }
    FlowTask *c = fn_801F4DC0(list.p, 0xA);
    if (c) {
        YesNoCursor *cur = CastYesNoCursor(c);
        cur->visible = sel == 0;
    }
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
}

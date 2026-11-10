#include "game/FlowYesNoRescue.h"

/* Use the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D02A0[8];
extern unsigned char YesNoCursor_RTTI_806D02B8[8];
extern unsigned char YesNoButton_RTTI_806D02B0[8];
}

static inline YesNoCursor *CastYesNoCursor(FlowTask *task) {
    return (YesNoCursor *)fn_80271340(task, 0, YesNoCursor_RTTI_806D02B8, FlowTask_RTTI_806D02A0, 0);
}

static inline YesNoButton *CastYesNoButton(FlowTask *task) {
    return (YesNoButton *)fn_80271340(task, 0, YesNoButton_RTTI_806D02B0, FlowTask_RTTI_806D02A0, 0);
}


YesNoTask::~YesNoTask() {}

YesNoTask::YesNoTask(int kind_, unsigned char defYes, int layer_, int id)
    : FlowTask(id), list(new SceneListImpl), layer(layer_), kind(kind_), choice(defYes ? 0 : 1), field20(0) {
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new YesNoButtonL(kind_, layer_), 0);
    }
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new YesNoButtonR(kind_, layer_), 0);
    }
    {
        YesNoButton *b = CastYesNoButton(fn_801F4DC0(list.p, 0));
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
        YesNoButton *b = CastYesNoButton(fn_801F4DC0(list.p, 1));
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
        CastYesNoCursor(c)->visible = v;
    }
}

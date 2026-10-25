#include "game/FlowYesNo.h"

/*
 * YesNoButton base ctor and the yes/no popup service (0x80207324..0x80207E3C):
 * open/close entry points, option queries and service init/shutdown.
 */

extern "C" {
void DebugPrintf(const char *fmt, ...);
int fn_80202E4C(int msg);
int fn_80202E20(int msg);
const char *fn_80202D70(int msg, int line);
const char *fn_80202CC0(int msg, int line);
YesNoTask *fn_80204778(int kind, unsigned char defYes, int layer, int id);
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB98;
extern const float lbl_806DABA4;
extern const char lbl_803C2764[];
extern const char lbl_803C2780[];
extern FlowSceneList *lbl_806D19F8;
extern int lbl_806D19FC;

void fn_80207760(bool show);
void fn_80207810(void);
void fn_80207848(void);
int fn_80207880(void);
int fn_802078B4(void);
int fn_802078F8(void);
int fn_80207AD8(int kind, unsigned char defYes);
int fn_80207B28(unsigned char v);
unsigned char fn_80207C64(void);
int fn_80207CC4(int choice);
void fn_80207D38(void);
void fn_80207DA8(int layer);
}

YesNoButton::YesNoButton(int kind_, bool flag, int layer_, int id)
    : FlowTask(id), layer(layer_), kind(kind_), state(0), fade(new FlowFaderF(lbl_806DAB10)), x(lbl_806DAB10),
      y(lbl_806DABA4), field34(lbl_806DAB10), field38(lbl_806DAB10), scale(lbl_806DAB20), scaleX(lbl_806DAB20),
      scaleY(lbl_806DAB20), alpha(0xFF), selected(0), appear(new FlowFaderF(lbl_806DAB10)),
      offX(new FlowFaderF(lbl_806DAB10)), offY(new FlowFaderF(lbl_806DAB10)), alphaF(new FlowFaderI),
      pulse(new FlowFaderF(lbl_806DAB10)), zoomX(new FlowFaderF(lbl_806DAB10)), zoomY(new FlowFaderF(lbl_806DAB10)) {
    PreloadResource(0x72F);
    PreloadResource(0x72E);
    if (flag) {
        field18 = fn_80202E4C(kind_);
        text0 = fn_80202D70(kind_, 0);
        text1 = fn_80202D70(kind_, 1);
    } else {
        field18 = fn_80202E20(kind_);
        text0 = fn_80202CC0(kind_, 0);
        text1 = fn_80202CC0(kind_, 1);
    }
    scale = lbl_806DAB10;
    scaleX = scale;
    scaleY = scale;
    alpha = 0xFF;
    fn_8020A734(fade.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A734(appear.p, 0xF, lbl_806DAB10, lbl_806DAB98);
    fn_8020A734(offX.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A734(offY.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A7CC(alphaF.p, 0xFF, 0xFF, 1);
    if (selected) {
        fn_8020A734(pulse.p, 1, lbl_806DAB20, lbl_806DAB20);
    } else {
        fn_8020A734(pulse.p, 1, lbl_806DAB18, lbl_806DAB18);
    }
    fn_8020A734(zoomX.p, 1, lbl_806DAB20, lbl_806DAB20);
    fn_8020A734(zoomY.p, 1, lbl_806DAB20, lbl_806DAB20);
}

void fn_80207760(bool show) {
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        YesNoTask *task = dynamic_cast<YesNoTask *>(t);
        YesNoButtonL *l = dynamic_cast<YesNoButtonL *>(fn_801F4DC0(task->list.p, 0));
        YesNoButtonR *r = dynamic_cast<YesNoButtonR *>(fn_801F4DC0(task->list.p, 1));
        l->field6D = show;
        r->field70 = show;
    }
}

void fn_80207810(void) {
    if (lbl_806D19F8) {
        lbl_806D19F8->Draw();
    }
}

void fn_80207848(void) {
    if (lbl_806D19F8) {
        lbl_806D19F8->Update();
    }
}

int fn_80207880(void) {
    return fn_801F4DC0(lbl_806D19F8, 0) != 0;
}

int fn_802078B4(void) {
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        t->field0C = 1;
        return 1;
    }
    return 0;
}

static inline void CloseButton(YesNoButton *b) {
    if (b && b->state <= 1) {
        if (b->selected) {
            fn_8020A734(b->appear.p, 5, lbl_806DAB20, lbl_806DAB18);
            fn_8020A734(b->offX.p, 0xA, lbl_806DAB10, lbl_806DAB10);
            fn_8020A734(b->offY.p, 0xA, lbl_806DAB10, lbl_806DAB10);
            fn_8020A7CC(b->alphaF.p, 0xFF, 0xFF, 0xA);
        } else {
            fn_8020A734(b->appear.p, 0xA, lbl_806DAB20, lbl_806DAB10);
        }
        b->state = 2;
    }
}

int fn_802078F8(void) {
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        YesNoTask *task = dynamic_cast<YesNoTask *>(t);
        YesNoButtonL *l = dynamic_cast<YesNoButtonL *>(fn_801F4DC0(task->list.p, 0));
        YesNoButtonR *r = dynamic_cast<YesNoButtonR *>(fn_801F4DC0(task->list.p, 1));
        CloseButton(l);
        CloseButton(r);
        ((SceneListImpl *)task->list.p)->Kill(0xA);
        return 1;
    }
    return 0;
}

int fn_80207AD8(int kind, unsigned char defYes) {
    if (lbl_806D19F8 == 0) {
        return 0;
    }
    fn_801F4DF0(lbl_806D19F8, fn_80204778(kind, defYes, lbl_806D19FC, 0), 0);
    return 1;
}

int fn_80207B28(unsigned char v) {
    if (lbl_806D19F8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        YesNoTask *task = dynamic_cast<YesNoTask *>(t);
        task->field20 = v;
        YesNoButtonL *l = dynamic_cast<YesNoButtonL *>(fn_801F4DC0(task->list.p, 0));
        if (l) {
            if (l->field6C != v) {
                if (v) {
                    fn_8020A7CC(l->fader70.p, 0, 0xFF, 0x14);
                    fn_8020A734(l->fader74.p, 0xF, lbl_806DAB34, lbl_806DAB38);
                    fn_8020A734(l->fader78.p, 0xF, lbl_806DAB34, lbl_806DAB3C);
                } else {
                    fn_8020A7CC(l->fader70.p, 0, 0, 1);
                    fn_8020A734(l->fader74.p, 1, lbl_806DAB40, lbl_806DAB40);
                    fn_8020A734(l->fader78.p, 1, lbl_806DAB40, lbl_806DAB40);
                }
            }
            l->field6C = v;
        }
        return 1;
    }
    return 0;
}

unsigned char fn_80207C64(void) {
    if (lbl_806D19F8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        return dynamic_cast<YesNoTask *>(t)->field20;
    }
    return 0;
}

int fn_80207CC4(int choice) {
    if (lbl_806D19F8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19F8, 0);
    if (t) {
        dynamic_cast<YesNoTask *>(t)->choice = choice;
        return 1;
    }
    return 0;
}

void fn_80207D38(void) {
    if (lbl_806D19F8) {
        delete lbl_806D19F8;
        lbl_806D19F8 = 0;
    }
    lbl_806D19FC = 0;
    fn_80120A08(0x72E);
    fn_80120A08(0x74C);
    DebugPrintf(lbl_803C2764);
}

void fn_80207DA8(int layer) {
    DebugPrintf(lbl_803C2780);
    if (lbl_806D19F8 == 0) {
        lbl_806D19F8 = new SceneListImpl;
    }
    lbl_806D19FC = layer;
    PreloadResource(0x72E);
    PreloadResource(0x74C);
}

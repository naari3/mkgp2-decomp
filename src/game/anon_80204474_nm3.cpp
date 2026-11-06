#include "game/YesNoCursorUpdate_private.h"

static inline void SpawnSpark(FlowSceneList *l, int id, int layer, float x, float y, unsigned char flag) {
    fn_801F4DF0(l, new YesNoSpark(id, layer, x, y, flag), 0);
}

void YesNoCursor::Update() {
    int t = fn_8020A788(timer.p);
    if (t % 15 == 0) {
        int id = (t / 15) * 2;
        FlowSceneList *l;
        bool f;
        int lay;
        float px;
        float py;
        l = list.p;
        lay = layer;
        f = visible;
        py = y;
        px = x;
        fn_801F4DF0(l, new YesNoSpark(id, lay, px, py, f), 0);
    }
    list.p->Update();
    timer.p->Step();
    if (timer.p->Done()) {
        timer.p->b = 0;
    }
}

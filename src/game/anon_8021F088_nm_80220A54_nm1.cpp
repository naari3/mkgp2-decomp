#include "game/anon_8021F088_private.h"

static inline void DrawNodes(PtrVec<FadeObj *> &nodes) {
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Render();
    }
}

void clCSSceneCoinMilage::Draw() {
    fn_8011FAB8();
    fn_801A1280();
    if (state == 4) {
        wnd->Draw();
    }
    if (state == 5) {
        next->Draw();
    }
    DrawNodes(nodes);
    if (state == 1) {
        for (int i = 0; i < numCoins; i++) {
            fn_8013D634(model, 0.0f, 0.0f, coins[i].z);
            fn_8013D660(model, coins[i].x, coins[i].y);
            fn_8013D59C(model, 0.0f, lbl_806DB1D8 * coins[i].rot, 0.0f);
            model->Draw();
        }
    }
}

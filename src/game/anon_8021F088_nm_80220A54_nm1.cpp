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
        void *mgr;
        ItemWnd *window;
        int digitIndex;
        int textIndex;
        int spriteIndex;
        window = wnd;
        for (spriteIndex = 0; spriteIndex < 3; ++spriteIndex) {
            if (window->spr[spriteIndex]) {
                fn_801A0004(window->spr[spriteIndex]);
            }
        }
        mgr = fn_801F8E58();
        for (textIndex = 0; textIndex < 7; ++textIndex) {
            fn_801F8A34(mgr, &window->texts[textIndex], 5);
        }
        for (digitIndex = 0; digitIndex < 4; ++digitIndex) {
            fn_8011FAFC(&window->digits[digitIndex], 5);
        }
        fn_8011FAFC(&window->label, window->labelLayer);
        fn_8011FAFC(&window->fade, 3);
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

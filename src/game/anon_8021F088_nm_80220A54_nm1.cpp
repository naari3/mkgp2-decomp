#include "game/anon_8021F088_private.h"

static inline void DrawItemTexts(ItemWnd *window) {
    int i;
    void *mgr = fn_801F8E58();
    for (i = 0; i < 7; ++i) {
        fn_801F8A34(mgr, &window->texts[i], 5);
    }
}

void clCSSceneCoinMilage::Draw() {
    FadeObj **it;
    FadeObj *node;
    fn_8011FAB8();
    fn_801A1280();
    if (state == 4) {
        ItemWnd *window;
        int digitIndex;
        int spriteIndex;
        window = wnd;
        for (spriteIndex = 0; spriteIndex < 3; ++spriteIndex) {
            if (window->spr[spriteIndex]) {
                fn_801A0004(window->spr[spriteIndex]);
            }
        }
        DrawItemTexts(window);
        for (digitIndex = 0; digitIndex < 4; ++digitIndex) {
            fn_8011FAFC(&window->digits[digitIndex], 5);
        }
        fn_8011FAFC(&window->label, window->labelLayer);
        fn_8011FAFC(&window->fade, 3);
    }
    if (state == 5) {
        next->Draw();
    }
    for (it = nodes.begin(); it != nodes.end(); it++) {
        node = *it;
        node->Render();
    }
    if (state == 1) {
        for (int i = 0; i < numCoins; i++) {
            fn_8013D634(model, 0.0f, 0.0f, coins[i].z);
            fn_8013D660(model, coins[i].x, coins[i].y);
            fn_8013D59C(model, 0.0f, lbl_806DB1D8 * coins[i].rot, 0.0f);
            model->Draw();
        }
    }
}

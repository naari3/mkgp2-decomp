#include "game/Scene_8016234CPrivate.h"


static inline void DrawCredit162(Transition162 *s, float alpha) {
    fn_801695E0(0, fn_8013BEF4(s->a, s->c, s->d), 0, 104.0f, 113.0f, alpha);
    const char *first = fn_8013C100(s->a, s->c, -1);
    const char *second = fn_8013C204(s->b, -1);
    fn_80168798(0, lbl_806D88A8, 185.0f, 93.0f, alpha, second, first);
    if (s->service && s->item != 0) {
        int special = (s->item >= 159) ? 1 : 0;
        int descriptor = Item_GetDescriptorField8(s->item);
        Item_GetDescriptorFieldC(s->item);
        ItemTransform162 *transform = fn_8013BEC8(descriptor);
        fn_801695E0(0, Item_GetDescriptorField0(s->item, 0), 0, 281.0f, 134.0f, alpha);
        if (special) fn_801695E0(0, 0x7c5, 0, 301.0f, 120.0f, alpha);
        fn_80168D84(0, GetTextureByIdAndLang(0x4c, -1), 332.0f, 121.0f, alpha);
        if (transform) {
            fn_80168B90(0, fn_8023DAA8(s->item), 332.0f, 141.0f, transform->x, transform->y, transform->z, transform->scale * alpha);
        } else {
            fn_80168D84(0, fn_8023DAA8(s->item), 332.0f, 141.0f, alpha);
        }
    }
}

extern "C" void fn_8016234C(Transition162 *s) {
    float t;
    if (s->done) return;
    if (s->phase == 99) { s->done = 1; return; }
    switch (s->phase) {
    case 0:
        fn_801698B4(0, 0x8a9, 0, 640.0f * (1.0f - s->timer / 30.0f) + 284.0f, 46.0f);
        if (s->timer >= 30.0f) { s->phase = 1; s->timer = 0.0f; }
        break;
    case 1:
        {
            t = s->timer / 30.0f;
            DrawCredit162(s, t);
        }
        fn_801698B4(0, 0x8a9, 0, 284.0f, 46.0f);
        if (s->timer >= 30.0f) {
            s->phase = 2;
            s->timer = 0.0f;
            if (!s->panel) {
                fn_801699D8(0, 1);
                s->panel = new CreditChild162;
            }
        }
        break;
    case 2:
        {
            DrawCredit162(s, lbl_806D8888);
        }
        fn_801698B4(0, 0x8a9, 0, 284.0f, 46.0f);
        if (s->panel) {
            s->panel->Update();
            if (s->panel->done) { s->phase = 3; s->timer = 0.0f; }
        } else { s->phase = 3; s->timer = 0.0f; }
        break;
    case 3: {
        t = s->timer / 30.0f;
        DrawCredit162(s, 1.0f - t);
        fn_801698B4(0, 0x8a9, 0, 284.0f - 640.0f * t, 46.0f);
        if (s->timer >= 30.0f) { s->phase = 99; s->timer = 0.0f; }
        break;
    }
    }
    if (s->panel) s->panel->Draw();
    RumbleUpdate();
    s->timer += 1.0f;
    if (!s->active) s->active = 1;
}

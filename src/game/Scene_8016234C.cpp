#include "game/Scene_8016234CPrivate.h"

extern "C" void fn_8016234C(Transition162 *s) {
    if (s->done) return;
    if (s->phase == 99) { s->done = 1; return; }
    switch (s->phase) {
    case 0:
        fn_801698B4(0, 0x8a9, 0, lbl_806D8884 * (lbl_806D8888 - s->timer / lbl_806D888C) + lbl_806D8880, lbl_806D8890);
        if (s->timer >= lbl_806D888C) { s->phase = 1; s->timer = lbl_806D8894; }
        break;
    case 1:
        {
            float alpha = s->timer / lbl_806D888C;
            fn_801695E0(0, fn_8013BEF4(s->a, s->c, s->d), 0, lbl_806D8898, lbl_806D889C, alpha);
            const char *first = fn_8013C100(s->a, s->c, -1);
            const char *second = fn_8013C204(s->b, -1);
            fn_80168798(0, lbl_806D88A8, lbl_806D88A0, lbl_806D88A4, alpha, second, first);
            if (s->service && s->item != 0) {
                bool special = s->item >= 159;
                int descriptor = Item_GetDescriptorField8(s->item);
                Item_GetDescriptorFieldC(s->item);
                ItemTransform162 *transform = fn_8013BEC8(descriptor);
                fn_801695E0(0, Item_GetDescriptorField0(s->item, 0), 0, lbl_806D88B0, lbl_806D88B4, alpha);
                if (special) fn_801695E0(0, 0x7c5, 0, lbl_806D88B8, lbl_806D88BC, alpha);
                fn_80168D84(0, GetTextureByIdAndLang(0x4c, -1), lbl_806D88C0, lbl_806D88C4, alpha);
                if (transform) {
                    fn_80168B90(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, transform->x, transform->y, transform->z, transform->scale * alpha);
                } else {
                    fn_80168D84(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, alpha);
                }
            }
        }
        fn_801698B4(0, 0x8a9, 0, lbl_806D8880, lbl_806D8890);
        if (s->timer >= lbl_806D888C) {
            s->phase = 2;
            s->timer = lbl_806D8894;
            if (!s->panel) {
                fn_801699D8(0, 1);
                s->panel = new CreditChild162;
            }
        }
        break;
    case 2:
        {
            fn_801695E0(0, fn_8013BEF4(s->a, s->c, s->d), 0, lbl_806D8898, lbl_806D889C, lbl_806D8888);
            const char *first = fn_8013C100(s->a, s->c, -1);
            const char *second = fn_8013C204(s->b, -1);
            fn_80168798(0, lbl_806D88A8, lbl_806D88A0, lbl_806D88A4, lbl_806D8888, second, first);
            if (s->service && s->item != 0) {
                bool special = s->item >= 159;
                int descriptor = Item_GetDescriptorField8(s->item);
                Item_GetDescriptorFieldC(s->item);
                ItemTransform162 *transform = fn_8013BEC8(descriptor);
                fn_801695E0(0, Item_GetDescriptorField0(s->item, 0), 0, lbl_806D88B0, lbl_806D88B4, lbl_806D8888);
                if (special) fn_801695E0(0, 0x7c5, 0, lbl_806D88B8, lbl_806D88BC, lbl_806D8888);
                fn_80168D84(0, GetTextureByIdAndLang(0x4c, -1), lbl_806D88C0, lbl_806D88C4, lbl_806D8888);
                if (transform) {
                    fn_80168B90(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, transform->x, transform->y, transform->z, transform->scale * lbl_806D8888);
                } else {
                    fn_80168D84(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, lbl_806D8888);
                }
            }
        }
        fn_801698B4(0, 0x8a9, 0, lbl_806D8880, lbl_806D8890);
        if (s->panel) {
            s->panel->Update();
            if (s->panel->done) { s->phase = 3; s->timer = lbl_806D8894; }
        } else { s->phase = 3; s->timer = lbl_806D8894; }
        break;
    case 3: {
        float t = s->timer / lbl_806D888C;
        float alpha = lbl_806D8888 - t;
        fn_801695E0(0, fn_8013BEF4(s->a, s->c, s->d), 0, lbl_806D8898, lbl_806D889C, alpha);
        const char *first = fn_8013C100(s->a, s->c, -1);
        const char *second = fn_8013C204(s->b, -1);
        fn_80168798(0, lbl_806D88A8, lbl_806D88A0, lbl_806D88A4, alpha, second, first);
        if (s->service && s->item != 0) {
            bool special = s->item >= 159;
            int descriptor = Item_GetDescriptorField8(s->item);
            Item_GetDescriptorFieldC(s->item);
            ItemTransform162 *transform = fn_8013BEC8(descriptor);
            fn_801695E0(0, Item_GetDescriptorField0(s->item, 0), 0, lbl_806D88B0, lbl_806D88B4, alpha);
            if (special) fn_801695E0(0, 0x7c5, 0, lbl_806D88B8, lbl_806D88BC, alpha);
            fn_80168D84(0, GetTextureByIdAndLang(0x4c, -1), lbl_806D88C0, lbl_806D88C4, alpha);
            if (transform) {
                fn_80168B90(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, transform->x, transform->y, transform->z, transform->scale * alpha);
            } else {
                fn_80168D84(0, fn_8023DAA8(s->item), lbl_806D88C0, lbl_806D88C8, alpha);
            }
        }
        fn_801698B4(0, 0x8a9, 0, lbl_806D8880 - lbl_806D8884 * t, lbl_806D8890);
        if (s->timer >= lbl_806D888C) { s->phase = 99; s->timer = lbl_806D8894; }
        break;
    }
    }
    if (s->panel) s->panel->Draw();
    RumbleUpdate();
    s->timer += lbl_806D8888;
    if (!s->active) s->active = 1;
}

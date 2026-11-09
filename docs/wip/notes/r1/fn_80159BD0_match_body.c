struct ItemColor {
    float r;
    float g;
    float b;
    float a;
};

struct WidgetView {
    int layer;
    char pad4[4];
    float x;
    float y;
    float alpha;
};

static inline void Widget_SetLayer(Widget *w, int layer)
{
    if (layer >= 0 && layer < 8) {
        ((WidgetView *)w)->layer = layer;
    }
}

static inline void Widget_SetPos(Widget *w, float x, float y)
{
    ((WidgetView *)w)->x = x;
    ((WidgetView *)w)->y = y;
}

static inline void Widget_SetAlpha(Widget *w, float a)
{
    ((WidgetView *)w)->alpha = a;
}

static inline int Item_IsSpecial(int id)
{
    return id >= 0x9f;
}

static inline unsigned int Item_NameSprite(int n)
{
    int r;
    if (n < 0) {
        r = -1;
    } else {
        r = n + 0x4f3;
    }
    return r;
}

extern "C" void fn_80159BD0(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float rowY2;

    if (isJapanese() == 1) {
        fn_80168D84(layer, optionText614, F3CC + x, rowY = F3D0 + y, alpha, self->count, 0x3c);
        fn_80168798(layer, F4D8, F3D4 + x, rowY, alpha);
        fn_80168D84(layer, F3E4, F3DC + x, F3E0 + y, alpha);
    } else {
        fn_80168798(layer, optionText638, F3CC + x, rowY = F3D0 + y, alpha, self->count);
        fn_80168D84(layer, optionText64C, (F4DC + x) - F4E0, rowY2 = F3E0 + y, alpha, 0x3c);
        fn_80168798(layer, F4D8, F3EC + x, rowY, alpha);
        fn_80168D84(layer, F3F0, F3DC + x, rowY2, alpha);
    }
    int idx;
    int j;
    int i;
    int page = self->value / 12;
    unsigned char special;
    for (i = 0; i < 5; i++) {
        float cy = y + (F4E8 * i + F4E4);
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            float cx = x + (F4F0 * j + F4EC);
            fn_801695E0(layer, 0x7cf, 0, cx, cy, alpha);
            int id = PlayerData_GetUnlockedItemIdByIndex_U8(idx);
            special = Item_IsSpecial(id);
            if (i == page) {
                if (self->value != idx) {
                    if (self->target->unlocked[idx]) {
                        fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, F4F4, F4F4, alpha);
                        if (special) {
                            fn_80169334(layer, 0x7c5, 0, F3B8 + cx, cy - F4F8, F4F4, F4F4, alpha);
                        }
                    } else {
                        fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, F4F4, F4F4, alpha);
                    }
                }
            } else {
                if (self->target->unlocked[idx]) {
                    fn_8016918C(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, F4F4, F4F4, F414, F414, F414, alpha);
                    if (special) {
                        fn_8016918C(layer, 0x7c5, 0, F3B8 + cx, cy - F4F8, F4F4, F4F4, F414, F414, F414, alpha);
                    }
                } else {
                    fn_8016918C(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, F4F4, F4F4, F414, F414, F414, alpha);
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            if (self->value != idx && self->target->unlocked[idx]) {
                if (self->equipped == PlayerData_GetUnlockedItemIdByIndex_U8(idx)) {
                    float rx = F4F0 * j + F4EC;
                    float ry = F4E8 * i + F4E4;
                    if (i == page) {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, F4F4, F4F4, F3B0, F3B0, F3B0, alpha);
                    } else {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, F4F4, F4F4, F414, F414, F414, alpha);
                    }
                }
            }
        }
    }
    float py;
    float px = F4FC + x;
    py = F490 + y;
    fn_801695E0(layer, 0x641, 0, px, py, alpha);
    if (self->value >= 0) {
        float selX;
        float selY;
        float sx;
        float cy2;
        float cx2;
        float tx;
        float sy;
        int id = PlayerData_GetUnlockedItemIdByIndex_U8(self->value);
        special = Item_IsSpecial(id);
        selX = F4F0 * (self->value % 12) + F4EC;
        selY = F4E8 * (self->value / 12) + F4E4;
        int nameId = Item_GetDescriptorFieldC(id);
        int kind = Item_GetDescriptorField8(id);
        int spr = Item_NameSprite(nameId);
        ItemColor *col = fn_8013BEC8(kind);
        Widget_SetLayer(self->w40, layer);
        Widget_SetPos(self->w40, F500 + x, F504 + y);
        Widget_SetAlpha(self->w40, alpha);
        self->w40->Draw();
        float t = self->blink2;
        if (t < F428) {
            sx = F4F4 + F508 * t / F428;
            sy = F4F4 + F50C * t / F428;
        } else if (t < F408) {
            float d = t - F428;
            sx = F514 * d / 4.0f + F510;
            sy = F51C - F520 * d / 4.0f;
        } else if (t < F43C) {
            float d = t - F408;
            sx = F524 - F514 * d / 4.0f;
            sy = F520 * d / 4.0f + F510;
        } else if (t < F528) {
            float d = t - F43C;
            sx = F510 - F508 * d / F430;
            sy = F51C - F52C * d / F430;
        } else if (t < F3B4) {
            float d = t - F528;
            sx = F4F4 - F530 * d / F430;
            sy = F534 - F52C * d / F430;
        } else if (t < F538) {
            float d = t - F3B4;
            sx = F53C + F540 * d / F544;
            sy = F524 - F548 * d / F544;
        } else {
            float d = t - F538;
            sx = F54C + F514 * d / F550;
            sy = F554 + F558 * d / F550;
        }
        cx2 = x + selX;
        cy2 = y + selY;
        fn_80169334(layer, 0x7cf, 0, cx2, cy2, sx, sy, alpha);
        if (self->target->unlocked[self->value]) {
            fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx2, cy2, sx, sy, alpha);
            if (special) {
                fn_80169334(layer, 0x7c5, 0, F55C * sx + cx2, cy2 - F408 * sy, sx, sy, alpha);
            }
            if (self->equipped == id) {
                fn_80169334(layer, 0x7d3, 0, cx2, cy2, sx, sy, alpha);
            }
            fn_801695E0(layer, spr, 0, px - F560, F3B0 + py, alpha);
            fn_801695E0(layer, Item_GetDescriptorField0(id, 0), 0, px - F564, F434 + py, alpha);
            if (special) {
                fn_801695E0(layer, 0x7c5, 0, px - F55C, py - F430, alpha);
            }
            if (col) {
                fn_80168B90(layer, fn_8023DAA8(id), px - F568, py - F56C, col->r, col->g, col->b, col->a * alpha);
            } else {
                fn_80168D84(layer, fn_8023DAA8(id), px - F568, py - F56C, alpha);
            }
            fn_80168D84(layer, fn_8023D938(id, 0), tx = F544 + px, py - F39C, alpha);
            fn_80168D84(layer, fn_8023D938(id, 1), tx, py - F550, alpha);
            fn_80168D84(layer, fn_8023D938(id, 2), tx, F570 + py, alpha);
        } else {
            fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx2, cy2, sx, sy, alpha);
        }
    }
}

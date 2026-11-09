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
        fn_80168D84(layer, optionText614, 35.0f + x, rowY = 112.0f + y, alpha, self->count, 0x3c);
        fn_80168798(layer, F4D8, 388.0f + x, rowY, alpha);
        fn_80168D84(layer, F3E4, 436.0f + x, 114.0f + y, alpha);
    } else {
        fn_80168798(layer, optionText638, 35.0f + x, rowY = 112.0f + y, alpha, self->count);
        fn_80168D84(layer, optionText64C, (280.0f + x) - 16.0f, rowY2 = 114.0f + y, alpha, 0x3c);
        fn_80168798(layer, F4D8, 366.0f + x, rowY, alpha);
        fn_80168D84(layer, F3F0, 436.0f + x, rowY2, alpha);
    }
    int idx;
    int j;
    int i;
    int page = self->value / 12;
    unsigned char special;
    for (i = 0; i < 5; i++) {
        float cy = y + (34.0f * i + 155.0f);
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            float cx = x + (46.0f * j + 65.0f);
            fn_801695E0(layer, 0x7cf, 0, cx, cy, alpha);
            int id = PlayerData_GetUnlockedItemIdByIndex_U8(idx);
            special = Item_IsSpecial(id);
            if (i == page) {
                if (self->value != idx) {
                    if (self->target->unlocked[idx]) {
                        fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, 0.75f, 0.75f, alpha);
                        if (special) {
                            fn_80169334(layer, 0x7c5, 0, 15.0f + cx, cy - 10.5f, 0.75f, 0.75f, alpha);
                        }
                    } else {
                        fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, 0.75f, 0.75f, alpha);
                    }
                }
            } else {
                if (self->target->unlocked[idx]) {
                    fn_8016918C(layer, Item_GetDescriptorField0(id, 0), 0, cx, cy, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    if (special) {
                        fn_8016918C(layer, 0x7c5, 0, 15.0f + cx, cy - 10.5f, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    }
                } else {
                    fn_8016918C(layer, Item_GetDescriptorField0(0, 0), 0, cx, cy, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 12; j++) {
            idx = i * 12 + j;
            if (self->value != idx && self->target->unlocked[idx]) {
                if (self->equipped == PlayerData_GetUnlockedItemIdByIndex_U8(idx)) {
                    float rx = 46.0f * j + 65.0f;
                    float ry = 34.0f * i + 155.0f;
                    if (i == page) {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, 0.75f, 0.75f, 1.0f, 1.0f, 1.0f, alpha);
                    } else {
                        fn_8016918C(layer, 0x7d3, 0, x + rx, y + ry, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    }
                }
            }
        }
    }
    float py;
    float px = 317.0f + x;
    py = 368.0f + y;
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
        selX = 46.0f * (self->value % 12) + 65.0f;
        selY = 34.0f * (self->value / 12) + 155.0f;
        int nameId = Item_GetDescriptorFieldC(id);
        int kind = Item_GetDescriptorField8(id);
        int spr = Item_NameSprite(nameId);
        ItemColor *col = fn_8013BEC8(kind);
        Widget_SetLayer(self->w40, layer);
        Widget_SetPos(self->w40, 599.0f + x, 356.0f + y);
        Widget_SetAlpha(self->w40, alpha);
        self->w40->Draw();
        float t = self->blink2;
        if (t < 10.0f) {
            sx = 0.75f + 0.28f * t / 10.0f;
            sy = 0.75f + 0.58f * t / 10.0f;
        } else if (t < 14.0f) {
            float d = t - 10.0f;
            sx = 0.12f * d / 4.0f + 1.03f;
            sy = 1.33f - 0.3f * d / 4.0f;
        } else if (t < 18.0f) {
            float d = t - 14.0f;
            sx = 1.15f - 0.12f * d / 4.0f;
            sy = 0.3f * d / 4.0f + 1.03f;
        } else if (t < 24.0f) {
            float d = t - 18.0f;
            sx = 1.03f - 0.28f * d / 6.0f;
            sy = 1.33f - 0.09f * d / 6.0f;
        } else if (t < 30.0f) {
            float d = t - 24.0f;
            sx = 0.75f - 0.1f * d / 6.0f;
            sy = 1.24f - 0.09f * d / 6.0f;
        } else if (t < 42.0f) {
            float d = t - 30.0f;
            sx = 0.65f + 0.03f * d / 12.0f;
            sy = 1.15f - 0.34f * d / 12.0f;
        } else {
            float d = t - 42.0f;
            sx = 0.68f + 0.12f * d / 3.0f;
            sy = 0.71f + 0.04f * d / 3.0f;
        }
        cx2 = x + selX;
        cy2 = y + selY;
        fn_80169334(layer, 0x7cf, 0, cx2, cy2, sx, sy, alpha);
        if (self->target->unlocked[self->value]) {
            fn_80169334(layer, Item_GetDescriptorField0(id, 0), 0, cx2, cy2, sx, sy, alpha);
            if (special) {
                fn_80169334(layer, 0x7c5, 0, 20.0f * sx + cx2, cy2 - 14.0f * sy, sx, sy, alpha);
            }
            if (self->equipped == id) {
                fn_80169334(layer, 0x7d3, 0, cx2, cy2, sx, sy, alpha);
            }
            fn_801695E0(layer, spr, 0, px - 104.0f, 1.0f + py, alpha);
            fn_801695E0(layer, Item_GetDescriptorField0(id, 0), 0, px - 40.0f, 8.0f + py, alpha);
            if (special) {
                fn_801695E0(layer, 0x7c5, 0, px - 20.0f, py - 6.0f, alpha);
            }
            if (col) {
                fn_80168B90(layer, fn_8023DAA8(id), px - 192.0f, py - 29.0f, col->r, col->g, col->b, col->a * alpha);
            } else {
                fn_80168D84(layer, fn_8023DAA8(id), px - 192.0f, py - 29.0f, alpha);
            }
            fn_80168D84(layer, fn_8023D938(id, 0), tx = 12.0f + px, py - 25.0f, alpha);
            fn_80168D84(layer, fn_8023D938(id, 1), tx, py - 3.0f, alpha);
            fn_80168D84(layer, fn_8023D938(id, 2), tx, 19.0f + py, alpha);
        } else {
            fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, cx2, cy2, sx, sy, alpha);
        }
    }
}

# scenelist-optionmenu-c24

Source: Codex worker c24_a13_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_80158CE4 best natural draft 98.39161% (1144B), without opt_common_subs off or other optimization pragmas. Existing current TU declarations suffice; remove only its own manual extab/index when testing. Residual is five aligned scheduling/addition rows at the course-mode icon call; DrawCourseMode inline produces byte-identical residual.

```cpp
static inline void DrawSpriteScaled(int layer, int id, float x, float y, float scale, float alpha)
{
    fn_80169334(layer, id, 0, x, y, scale, scale, alpha);
}

extern "C" void fn_80158CE4(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float bx;
    float by;
    float px;
    float dy;
    int i;
    int j;

    if (isJapanese() == 1) {
        float rowY;
        fn_80168D84(layer, lbl_80367E24, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D83D8, lbl_806D83D4 + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    } else {
        float rowY;
        fn_80168798(layer, lbl_80367E38, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D83D8, lbl_806D83EC + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    }
    bx = lbl_806D83F8 + x;
    by = lbl_806D83FC + y;
    for (i = 0; i < 4; i++) {
        px = lbl_806D8398 + (lbl_806D8400 * (float)i + bx);
        DrawSpriteScaled(layer, 0x7db, px, by, 0.85f, alpha);
        if (self->time[i] > lbl_806D8394) {
            fn_801695E0(layer, 0x7dc, 0, px - lbl_806D8408, by - lbl_806D840C, alpha);
            fn_801695E0(layer, i + 0x7dd, 0, lbl_806D8410 + px, by - lbl_806D840C, alpha);
            DrawSpriteScaled(layer, self->course[i] + 0x76c, px - lbl_806D83B0, by - lbl_806D83B8, 0.5f, alpha);
            if (self->kind[i] == 2) {
                DrawSpriteScaled(layer, 0x7b0, lbl_806D83B4 + px, by - lbl_806D8418, 0.4f, alpha);
            }
            fn_801695E0(layer, (self->course[i] << 1) + self->mode[i] + 0x7e4, 0, px - lbl_806D83B0,
                        lbl_806D83B8 + by, alpha);
            if (self->isNew[i] != 0) {
                if (isJapanese() == 1) {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - lbl_806D8420, lbl_806D8424 + by,
                                alpha);
                } else {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - lbl_806D8428, lbl_806D8424 + by,
                                alpha);
                }
            }
            dy = lbl_806D842C + by;
            px -= lbl_806D8424;
            for (j = 0; j < 8; j++) {
                fn_801695E0(layer, fn_80167744(7 - j, self->time[i]) + 0x1ecd, 0, lbl_806D8428 * (float)j + px, dy,
                            alpha);
            }
        } else {
            fn_80168D84(layer, lbl_806D8438, px - lbl_806D8430, by - lbl_806D8434, alpha);
            fn_80168D84(layer, lbl_806D8440, px - lbl_806D843C, lbl_806D8428 + by, alpha);
        }
    }
}
```

## c24_a13_20261109
Source: Codex worker c24_a13_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_8015915C best natural draft 99.64286% (1400B), five semantic inline draw regions. Residual is23 register rows: heading/legend/digit rowY, second baseX, digit xoris vs address scratch, and scroll comparison operands in grid. Do not repeat branch-local rowY + named second baseX refinement; it worsened to99.52857%. Remove only own manual EH/index when testing.

```cpp
static inline void DrawVersusHeading(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float baseX;
    int i;
    int id;
    if (isJapanese() == 1) {
        fn_80168D84(layer, optionText578, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D8450, lbl_806D83D4 + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    } else {
        fn_80168798(layer, optionText58C, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D8450, lbl_806D83EC + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    }
}

static inline void DrawVersusDigits(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float baseX;
    int i;
    int id;
    rowY = lbl_806D8454 + y;
    baseX = lbl_806D8458 + x;
    for (i = 0; i < 3; i++) {
        fn_801695E0(layer, self->digitsA[i] + 0x3F7, 0, lbl_806D845C * i + baseX, rowY, alpha);
    }
    baseX = lbl_806D83D4 + x;
    for (i = 0; i < 3; i++) {
        fn_801695E0(layer, self->digitsB[i] + 0x3F7, 0, lbl_806D845C * i + baseX, rowY, alpha);
    }
}

static inline void DrawVersusLegend(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float baseX;
    int i;
    int id;
    if (isJapanese() == 1) {
        fn_80168798(layer, lbl_806D8468, lbl_806D8460 + x, rowY = lbl_806D8464 + y, alpha);
        fn_80168798(layer, lbl_806D8474, lbl_806D8470 + x, rowY, alpha);
    } else {
        fn_80168798(layer, lbl_806D847C, lbl_806D8460 + x, rowY = lbl_806D8464 + y, alpha);
        fn_80168798(layer, lbl_806D8480, lbl_806D8470 + x, rowY, alpha);
    }
}

static inline void DrawVersusGrid(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float baseX;
    int i;
    int id;
    float colX = lbl_806D83CC + x;
    rowY = lbl_806D8484 + y;
    for (i = 0; i < 100; i++) {
        int col = i % 20;
        int row = i / 20;
        float px = lbl_806D83B4 * col + colX;
        float py = lbl_806D8424 * row + rowY;
        id = 0x647;
        if (i < self->wins) {
            int k = col + row;
            id = 0x654;
            if (k <= self->scroll) {
                int v = ((self->scroll - k) * 4 + self->scrollTimer) / 4;
                if (v < 6) {
                    id = v + 0x654;
                }
            }
        } else {
            if (row & 1) {
                id = 0x649;
            }
            const int *p = optionThresholds;
            for (int j = 0; j < 17; j++, p++) {
                if (i + 1 == *p) {
                    id--;
                    if ((i + 1) % 10 == 0) {
                        id = i / 10 + 0x64A;
                    }
                    break;
                }
            }
        }
        fn_801695E0(layer, id, 0, px, py, alpha);
    }
}

static inline void DrawVersusTotals(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;
    float baseX;
    int i;
    int id;
    if (isJapanese() == 1) {
        fn_80168404(layer, optionText5A0, lbl_806D8488 + x, rowY = lbl_806D848C + y, lbl_806D8390, lbl_806D83B0, alpha,
                    self->wins + self->losses);
        fn_80168404(layer, optionText5B8, lbl_806D8490 + x, rowY, lbl_806D8390, lbl_806D83B0, alpha, self->wins);
    } else {
        fn_80168798(layer, optionText5CC, lbl_806D8488 + x, rowY = lbl_806D848C + y, alpha);
        fn_80168798(layer, lbl_806D8498, lbl_806D8494 + x, rowY, alpha, self->wins + self->losses);
        fn_80168798(layer, optionText5DC, lbl_806D8490 + x, rowY, alpha);
        fn_80168798(layer, lbl_806D84A4, lbl_806D84A0 + x, rowY, alpha, self->wins);
    }
}

extern "C" void fn_8015915C(OptionMenu *self, int layer, float x, float y, float alpha)
{
    DrawVersusHeading(self, layer, x, y, alpha);
    DrawVersusDigits(self, layer, x, y, alpha);
    DrawVersusLegend(self, layer, x, y, alpha);
    DrawVersusGrid(self, layer, x, y, alpha);
    DrawVersusTotals(self, layer, x, y, alpha);
}
```

## c24_a13_20261109
Source: Codex worker c24_a13_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_80159BD0 full natural draft, H2 best93.65444%, 2824B versus target2836B; frameE0 versusF0. NOT accepted source. Requires private WidgetBase fields int layer/reserved; float x/y/alpha (still20B), and OptionMenu pad68[4] replaced by int selectedAlias. Correct prototypes: int Item_GetDescriptorField0(int,int); int Item_GetDescriptorField8(int); int Item_GetDescriptorFieldC(int); int PlayerData_GetUnlockedItemIdByIndex_U8(int); float *fn_8013BEC8(int); void fn_80168B90(int,const char*,float,float,float,float,float,float,...); void fn_8016918C(int,int,int,float,float,float,float,float,float,float,float); const char *fn_8023D938(int,int); const char *fn_8023DAA8(int). Existing canonical CourseTables lookup confirms16-byte RGBA entry. H2 literal/postprocess collisions must be diagnosed before treating remaining instruction differences as allocator-only. H1 without literal changes was90.12271%/2880B; H3 styled DrawItemIcon/DrawTintedItemIcon helpers92.963326%/2824B. No source retained in TU.

```cpp
extern "C" void fn_80159BD0(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float px, py;
    float detailX, detailY;
    float sx, sy;
    float rowY;
    if (isJapanese() == 1) {
        fn_80168D84(layer, optionText614, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha, self->count, 60);
        fn_80168798(layer, lbl_806D84D8, lbl_806D83D4 + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    } else {
        fn_80168798(layer, optionText638, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha, self->count);
        float unitY = lbl_806D83E0 + y;
        fn_80168D84(layer, optionText64C, lbl_806D84DC + x - lbl_806D84E0, unitY, alpha, 60);
        fn_80168798(layer, lbl_806D84D8, lbl_806D83EC + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC + x, unitY, alpha);
    }
    int selectedRow = self->value / 12;
    for (int row = 0; row < 5; row++) {
        py = y + (lbl_806D84E8 * row + lbl_806D84E4);
        for (int col = 0; col < 12; col++) {
            px = x + (lbl_806D84F0 * col + lbl_806D84EC);
            int index = row * 12 + col;
            fn_801695E0(layer, 0x7cf, 0, px, py, alpha);
            int item = (unsigned char)PlayerData_GetUnlockedItemIdByIndex_U8(index);
            unsigned char special = item >= 159;
            if (row == selectedRow) {
                if (self->value != index) {
                    if (self->target->unlocked[index]) {
                        fn_80169334(layer, Item_GetDescriptorField0(item, 0), 0, px, py, 0.75f, 0.75f, alpha);
                        if (special) fn_80169334(layer, 0x7c5, 0, lbl_806D83B8 + px, py - lbl_806D84F8, 0.75f, 0.75f, alpha);
                    } else {
                        fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, px, py, 0.75f, 0.75f, alpha);
                    }
                }
            } else {
                if (self->target->unlocked[index]) {
                    fn_8016918C(layer, Item_GetDescriptorField0(item, 0), 0, px, py, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                    if (special) fn_8016918C(layer, 0x7c5, 0, lbl_806D83B8 + px, py - lbl_806D84F8, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                } else {
                    fn_8016918C(layer, Item_GetDescriptorField0(0, 0), 0, px, py, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                }
            }
        }
    }
    for (int row = 0; row < 5; row++) {
        py = lbl_806D84E8 * row + lbl_806D84E4;
        for (int col = 0; col < 12; col++) {
            int index = row * 12 + col;
            if (self->value != index && self->target->unlocked[index] && self->selectedAlias == (unsigned char)PlayerData_GetUnlockedItemIdByIndex_U8(index)) {
                px = lbl_806D84F0 * col + lbl_806D84EC;
                if (row == selectedRow) {
                    fn_8016918C(layer, 0x7d3, 0, x + px, y + py, 0.75f, 0.75f, 1.0f, 1.0f, 1.0f, alpha);
                } else {
                    fn_8016918C(layer, 0x7d3, 0, x + px, y + py, 0.75f, 0.75f, 0.5f, 0.5f, 0.5f, alpha);
                }
            }
        }
    }
    detailX = lbl_806D84FC + x;
    detailY = lbl_806D8490 + y;
    fn_801695E0(layer, 0x641, 0, detailX, detailY, alpha);
    if (self->value >= 0) {
        int item = (unsigned char)PlayerData_GetUnlockedItemIdByIndex_U8(self->value);
        unsigned char special = item >= 159;
        px = lbl_806D84F0 * (self->value % 12) + lbl_806D84EC;
        py = lbl_806D84E8 * (self->value / 12) + lbl_806D84E4;
        int descriptor = Item_GetDescriptorFieldC(item);
        int color = Item_GetDescriptorField8(item);
        int title = -1;
        if (descriptor >= 0) title = descriptor + 0x4f3;
        float *rgba = fn_8013BEC8(color);
        if (layer >= 0 && layer < 8) self->w40->layer = layer;
        self->w40->x = lbl_806D8500 + x;
        self->w40->y = lbl_806D8504 + y;
        self->w40->alpha = alpha;
        self->w40->Draw();
        float t = self->blink2;
        if (t < lbl_806D8428) {
            sx = lbl_806D84F4 + lbl_806D8508 * t / lbl_806D8428;
            sy = lbl_806D84F4 + lbl_806D850C * t / lbl_806D8428;
        } else if (t < lbl_806D8408) {
            float dt = t - lbl_806D8428;
            sx = lbl_806D8510 + (lbl_806D8514 * dt) * lbl_806D8518;
            sy = lbl_806D851C - (lbl_806D8520 * dt) * lbl_806D8518;
        } else if (t < lbl_806D843C) {
            float dt = t - lbl_806D8408;
            sx = lbl_806D8524 - (lbl_806D8514 * dt) * lbl_806D8518;
            sy = lbl_806D8510 + (lbl_806D8520 * dt) * lbl_806D8518;
        } else if (t < lbl_806D8528) {
            float dt = t - lbl_806D843C;
            sx = lbl_806D8510 - lbl_806D8508 * dt / lbl_806D8430;
            sy = lbl_806D851C - lbl_806D852C * dt / lbl_806D8430;
        } else if (t < lbl_806D83B4) {
            float dt = t - lbl_806D8528;
            sx = lbl_806D84F4 - lbl_806D8530 * dt / lbl_806D8430;
            sy = lbl_806D8534 - lbl_806D852C * dt / lbl_806D8430;
        } else if (t < lbl_806D8538) {
            float dt = t - lbl_806D83B4;
            sx = lbl_806D853C + lbl_806D8540 * dt / lbl_806D8544;
            sy = lbl_806D8524 - lbl_806D8548 * dt / lbl_806D8544;
        } else {
            float dt = t - lbl_806D8538;
            sx = lbl_806D854C + lbl_806D8514 * dt / lbl_806D8550;
            sy = lbl_806D8554 + lbl_806D8558 * dt / lbl_806D8550;
        }
        px = x + px;
        py = y + py;
        fn_80169334(layer, 0x7cf, 0, px, py, sx, sy, alpha);
        if (self->target->unlocked[self->value]) {
            fn_80169334(layer, Item_GetDescriptorField0(item, 0), 0, px, py, sx, sy, alpha);
            if (special) fn_80169334(layer, 0x7c5, 0, lbl_806D855C * sx + px, py - lbl_806D8408 * sy, sx, sy, alpha);
            if (self->selectedAlias == item) fn_80169334(layer, 0x7d3, 0, px, py, sx, sy, alpha);
            fn_801695E0(layer, title, 0, detailX - lbl_806D8560, lbl_806D83B0 + detailY, alpha);
            fn_801695E0(layer, Item_GetDescriptorField0(item, 0), 0, detailX - lbl_806D8564, lbl_806D8434 + detailY, alpha);
            if (special) fn_801695E0(layer, 0x7c5, 0, detailX - lbl_806D855C, detailY - lbl_806D8430, alpha);
            if (rgba) {
                fn_80168B90(layer, fn_8023DAA8(item), detailX - lbl_806D8568, detailY - lbl_806D856C, rgba[0], rgba[1], rgba[2], rgba[3] * alpha);
            } else {
                fn_80168D84(layer, fn_8023DAA8(item), detailX - lbl_806D8568, detailY - lbl_806D856C, alpha);
            }
            float textX = lbl_806D8544 + detailX;
            fn_80168D84(layer, fn_8023D938(item, 0), textX, detailY - lbl_806D839C, alpha);
            fn_80168D84(layer, fn_8023D938(item, 1), textX, detailY - lbl_806D8550, alpha);
            fn_80168D84(layer, fn_8023D938(item, 2), textX, lbl_806D8570 + detailY, alpha);
        } else {
            fn_80169334(layer, Item_GetDescriptorField0(0, 0), 0, px, py, sx, sy, alpha);
        }
    }
}


/* ---- formerly OptionMenuDraw.cpp ---- */
```

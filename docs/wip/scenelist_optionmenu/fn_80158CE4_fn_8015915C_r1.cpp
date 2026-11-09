extern "C" void fn_80158CE4(OptionMenu *self, int layer, float x, float y, float alpha)
{
    float rowY;

    if (isJapanese() == 1) {
        fn_80168D84(layer, lbl_80367E24, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D83D8, lbl_806D83D4 + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    } else {
        fn_80168798(layer, lbl_80367E38, lbl_806D83CC + x, rowY = lbl_806D83D0 + y, alpha);
        fn_80168798(layer, lbl_806D83D8, lbl_806D83EC + x, rowY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC + x, lbl_806D83E0 + y, alpha);
    }
    float colX = lbl_806D83F8 + x;
    float slotY = lbl_806D83FC + y;
    for (int i = 0; i < 4; i++) {
        float px = lbl_806D8398 + (lbl_806D8400 * i + colX);
        fn_80169334(layer, 0x7DB, 0, px, slotY, 0.85f, 0.85f, alpha);
        if (self->time[i] > lbl_806D8394) {
            fn_801695E0(layer, 0x7DC, 0, px - lbl_806D8408, slotY - lbl_806D840C, alpha);
            fn_801695E0(layer, i + 0x7DD, 0, lbl_806D8410 + px, slotY - lbl_806D840C, alpha);
            fn_80169334(layer, self->course[i] + 0x76C, 0, px - lbl_806D83B0, slotY - lbl_806D83B8, 0.5f, 0.5f,
                        alpha);
            if (self->kind[i] == 2) {
                fn_80169334(layer, 0x7B0, 0, lbl_806D83B4 + px, slotY - lbl_806D8418, 0.4f, 0.4f, alpha);
            }
            fn_801695E0(layer, self->course[i] * 2 + self->mode[i] + 0x7E4, 0, px - lbl_806D83B0, lbl_806D83B8 + slotY,
                        alpha);
            if (self->isNew[i]) {
                if (isJapanese() == 1) {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - lbl_806D8420, lbl_806D8424 + slotY, alpha);
                } else {
                    fn_80168D84(layer, GetTextureByIdAndLang(0x39, -1), px - lbl_806D8428, lbl_806D8424 + slotY, alpha);
                }
            }
            float digitY = lbl_806D842C + slotY;
            px -= lbl_806D8424;
            for (int j = 0; j < 8; j++) {
                fn_801695E0(layer, fn_80167744(7 - j, self->time[i]) + 0x1ECD, 0, lbl_806D8428 * j + px, digitY,
                            alpha);
            }
        } else {
            fn_80168D84(layer, lbl_806D8438, px - lbl_806D8430, slotY - lbl_806D8434, alpha);
            fn_80168D84(layer, lbl_806D8440, px - lbl_806D843C, lbl_806D8428 + slotY, alpha);
        }
    }
}

extern "C" void fn_8015915C(OptionMenu *self, int layer, float x, float y, float alpha)
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
    rowY = lbl_806D8454 + y;
    baseX = lbl_806D8458 + x;
    for (i = 0; i < 3; i++) {
        fn_801695E0(layer, self->digitsA[i] + 0x3F7, 0, lbl_806D845C * i + baseX, rowY, alpha);
    }
    baseX = lbl_806D83D4 + x;
    for (i = 0; i < 3; i++) {
        fn_801695E0(layer, self->digitsB[i] + 0x3F7, 0, lbl_806D845C * i + baseX, rowY, alpha);
    }
    if (isJapanese() == 1) {
        fn_80168798(layer, lbl_806D8468, lbl_806D8460 + x, rowY = lbl_806D8464 + y, alpha);
        fn_80168798(layer, lbl_806D8474, lbl_806D8470 + x, rowY, alpha);
    } else {
        fn_80168798(layer, lbl_806D847C, lbl_806D8460 + x, rowY = lbl_806D8464 + y, alpha);
        fn_80168798(layer, lbl_806D8480, lbl_806D8470 + x, rowY, alpha);
    }
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


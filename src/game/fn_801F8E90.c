typedef struct TextLabel {
    char pad00[8];
    float offsetX;
    char pad0C[0xC];
    int size;
    int align;
    char pad20[4];
    unsigned short text[0x104];
    float spacing;
} TextLabel;

extern int isJapanese(void);
extern const float lbl_806DA758;
extern const float lbl_806DA768;

void fn_801F8E90(TextLabel *label) {
    float width = 0.0f;
    float spacing = label->spacing;
    float narrow;
    float full;
    int i;

    if (isJapanese() == 0) {
        narrow = 12.0f;
        full = 16.0f;
        if (label->size == 1) {
            full = 24.0f;
            narrow = lbl_806DA768 * full;
        }
    } else {
        narrow = 10.0f;
        full = lbl_806DA758;
        if (label->size == 1) {
            full = 20.0f;
            narrow = lbl_806DA768 * full;
        }
    }
    for (i = 0; label->text[i] != 0xFFFF && i < 0x100; i++) {
        width += full;
        width += spacing;
    }
    if (label->text[i - 1] < 0x28E) {
        width -= full;
    } else {
        width -= narrow;
    }
    width -= 2.0f * spacing;
    switch (label->align) {
    case 1:
        label->offsetX = 0.5f * -width;
        break;
    case 2:
        label->offsetX = -width;
        break;
    default:
        label->offsetX = 0.0f;
        break;
    }
}

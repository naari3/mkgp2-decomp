typedef struct Label {
    char pad00[0xC];
    float x;
    float y;
} Label;

static inline void Label_SetPos(Label *l, float x, float y) {
    l->x = x;
    l->y = y;
}

typedef struct ClassSelect {
    char pad00[5];
    unsigned char extraMode;
    char pad06[6];
    int cursor;
    char pad10[0xC];
    int showHelp;
    char pad20[0xC];
    Label *help;
    Label *items[3];
    Label *title;
    char pad40[4];
    Label *arrowL;
    Label *arrowR;
} ClassSelect;

extern void fn_801A0004(Label *label);
extern void fn_801A1174(int id, int a, int b, int c, int d);
extern void fn_801A1128(float x, float y);
extern void fn_801A0DF0(void);

void fn_801C2238(ClassSelect *self) {
    if (self->title != 0) {
        fn_801A0004(self->title);
    }
    if (self->showHelp != 0) {
        fn_801A1174(0x166F, 5, 0, 0, 0);
        fn_801A1128(320.0f, 378.0f);
        fn_801A0DF0();
        if (self->help != 0) {
            fn_801A0004(self->help);
        }
    }
    if (self->extraMode) {
        if (self->cursor != 1 && self->items[1] != 0) {
            fn_801A0004(self->items[1]);
        }
        if (self->cursor != 2 && self->items[2] != 0) {
            fn_801A0004(self->items[2]);
        }
    } else {
        if (self->cursor != 0 && self->items[0] != 0) {
            fn_801A0004(self->items[0]);
        }
        if (self->cursor != 1 && self->items[1] != 0) {
            fn_801A0004(self->items[1]);
        }
        if (self->cursor != 2 && self->items[2] != 0) {
            fn_801A0004(self->items[2]);
        }
    }
    if (self->items[self->cursor] != 0) {
        fn_801A0004(self->items[self->cursor]);
    }
    if (self->arrowL != 0) {
        fn_801A0004(self->arrowL);
    }
    if (self->arrowR != 0) {
        fn_801A0004(self->arrowR);
    }
    if (self->title != 0) {
        Label_SetPos(self->title, 320.0f, 374.0f);
    }
}

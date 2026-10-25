typedef struct Sprite Sprite;
typedef struct ResCtrl ResCtrl;

typedef struct OptSprite {
    Sprite *sprite;
    unsigned char visible;
} OptSprite;

typedef struct LayeredCtrl {
    char pad0[0x58];
    int layer;
} LayeredCtrl;

typedef struct LinkBanner {
    int state;
    int pad4;
    char ctrl0[0x58];
    char ctrl1[0x58];
    char ctrl2[0x58];
} LinkBanner;

typedef struct ItemSlot {
    Sprite *sprite;
    int pad4;
} ItemSlot;

typedef struct ItemSelectView {
    char pad000[8];
    int selected;
    char pad00C[0x24 - 0xC];
    ItemSlot items[18];
    Sprite *bg;
    Sprite *frame;
    Sprite *title;
    Sprite *cursor;
    Sprite *arrowL;
    Sprite *arrowR;
    char pad0CC[0xD4 - 0xCC];
    char fade[0x12C - 0xD4];
    Sprite *help;
    Sprite *timer;
    OptSprite *badge;
    Sprite *extra0;
    Sprite *extra1;
    unsigned char showExtra0;
    unsigned char showExtra1;
    char pad142[2];
    LayeredCtrl *players[4];
    LinkBanner *banner;
} ItemSelectView;

extern int g_gameMode;
extern void fn_801A0004(Sprite *s);
extern void fn_8011FAFC(void *ctrl, int layer);

void fn_801CF188(ItemSelectView *self)
{
    LinkBanner *b;
    int i;
    int j;

    if (self->bg != 0) {
        fn_801A0004(self->bg);
    }
    if (self->frame != 0) {
        fn_801A0004(self->frame);
    }
    if (self->arrowL != 0) {
        fn_801A0004(self->arrowL);
    }
    if (self->title != 0) {
        fn_801A0004(self->title);
    }
    if (self->cursor != 0) {
        fn_801A0004(self->cursor);
    }
    if (self->arrowR != 0) {
        fn_801A0004(self->arrowR);
    }
    if (self->help != 0) {
        fn_801A0004(self->help);
    }
    if (self->timer != 0) {
        fn_801A0004(self->timer);
    }
    fn_8011FAFC(self->fade, 5);
    if (self->badge != 0 && self->badge->visible) {
        fn_801A0004(self->badge->sprite);
    }
    for (i = 0; i < 18; i++) {
        if (i != self->selected && self->items[i].sprite != 0) {
            fn_801A0004(self->items[i].sprite);
        }
    }
    if (self->items[self->selected].sprite != 0) {
        fn_801A0004(self->items[self->selected].sprite);
    }
    if (self->extra0 != 0 && self->showExtra0) {
        fn_801A0004(self->extra0);
    }
    if (self->extra1 != 0 && self->showExtra1) {
        fn_801A0004(self->extra1);
    }
    if (g_gameMode == 2) {
        for (j = 0; j < 4; j++) {
            fn_8011FAFC(self->players[j], self->players[j]->layer);
        }
        b = self->banner;
        if (b != 0 && b->state != 3) {
            fn_8011FAFC(b->ctrl0, 6);
            fn_8011FAFC(b->ctrl1, 6);
            fn_8011FAFC(b->ctrl2, 6);
        }
    }
}

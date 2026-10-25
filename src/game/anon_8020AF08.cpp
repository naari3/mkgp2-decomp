/*
 * 0x8020AF08..0x8020B4F8: item showcase (spinning item model / shell
 * effect with a sparkle animation set) shown on the item get screen.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct ShowModel {
    ShowModel(void *res, int flag);
    virtual ~ShowModel();
    char pad[0x20 - 0x4];
};

struct ShowShellA {
    char pad[0x10];
    ShowShellA(int layer, float x, float y, float scale);
    ~ShowShellA();
};

struct ShowShellB {
    char pad[0xC];
    ShowShellB(int layer, float x, float y, float scale);
    ~ShowShellB();
};

struct ShowAnim {
    char pad[0x70];
    ShowAnim(int res, int a, int b, const void *data, int c);
    ~ShowAnim();
};

struct ShowAnimSet {
    char a[0x18C];
    char b[0x4D0 - 0x18C];
    char c[0x6B8 - 0x4D0];
};

struct ShowXform {
    float pos[3];
    float rot[3];
    float scale;
};

extern "C" {
extern int g_humanPlayerCount;
extern const struct ShowAnimSet lbl_803C2E50;
extern const float lbl_806DAC08;
extern const float lbl_806DAC0C;
extern const float lbl_806DAC10;
extern const float lbl_806DAC14;
extern const float lbl_806DAC18;
extern const float lbl_806DAC1C;
extern const float lbl_806DAC20;
extern const float lbl_806DAC30;
extern const float lbl_806DAC34;
extern const float lbl_806DAC38;
extern const float lbl_806DAC3C;

void fn_8011FAB8(void);
void fn_80120A08(int res);
void PreloadResource(int res);
void *ItemRes_LookupByKey_Thunk(int key);
void fn_80169334(int a, int res, int b, float x, float y, float sx, float sy, float alpha);
void fn_8013D4B0(ShowModel *m, float alpha);
void fn_8013D50C(ShowModel *m, float r, float g, float b, float alpha);
void fn_8013D59C(ShowModel *m, float x, float y, float z);
void fn_8013D608(ShowModel *m, float x, float y, float z);
void fn_8013D634(ShowModel *m, float x, float y, float z);
void fn_8013D660(ShowModel *m, float x, float y);
void fn_8013D738(ShowModel *m, float a, float b);
void fn_8013D940(int layer);
void fn_8013DA00(void);
void fn_8013DAC8(ShowModel *m, int layer);
void fn_8013DB9C(void);
void fn_8013DBF8(void);
ShowXform *fn_8013BE98(void);
void fn_8014D1E0(ShowShellA *s, float alpha);
void fn_8014D250(ShowShellA *s);
void fn_8014D2AC(ShowShellA *s);
void fn_8014CEE8(ShowShellB *s, float alpha);
void fn_8014CF44(ShowShellB *s);
void fn_8014CFA0(ShowShellB *s);
void fn_8013AB74(ShowAnim *a, int layer, int frame);
void fn_8013AE20(ShowAnim *a, float x, float y, float alpha);
void fn_8013B300(ShowAnim *a, int frame);
void fn_8013B4FC(ShowAnim *a, int frame);
void fn_8013B7A8(ShowAnim *a, ShowAnim *next);
}

struct ItemShowcase {
    int timer;
    int itemId;
    ShowModel *model;
    bool loaded;
    float glow;
    float alpha;
    ShowAnim *anim;
    ShowShellA *shellA;
    ShowShellB *shellB;
    ItemShowcase(int t);
    ~ItemShowcase();
    void Draw();
    int Update();
};

ItemShowcase::~ItemShowcase() {
    if (model != 0) {
        delete model;
    }
    if (shellA != 0) {
        delete shellA;
    }
    if (shellB != 0) {
        delete shellB;
    }
    fn_8013DB9C();
    if (loaded) {
        fn_80120A08(0xBFF);
    }
    fn_80120A08(0x96A);
    if (anim != 0) {
        delete anim;
    }
}

void ItemShowcase::Draw() {
    if (timer != 0) {
        if (loaded) {
            fn_8011FAB8();
        }
        if (model != 0) {
            fn_8013D940(7);
        }
        if (shellA != 0) {
            fn_8014D250(shellA);
            fn_8013D940(7);
        }
        if (shellB != 0) {
            fn_8014CF44(shellB);
            fn_8013D940(7);
        }
        fn_8013DA00();
        if (anim != 0) {
            fn_8013AB74(anim, 4, -1);
        }
        fn_8011FAB8();
    }
}

int ItemShowcase::Update() {
    if (timer == 0) {
        return 1;
    }
    timer--;
    if (timer < 20.0f) {
        fn_8013B300(anim, -1);
        glow -= 0.05f;
        if (glow < 0.0f) {
            glow = 0.0f;
        }
        alpha -= 0.05f;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
    } else {
        glow += 0.05f;
        if (1.0f < glow) {
            glow = 1.0f;
        }
        alpha += 0.05f;
        if (1.0f < alpha) {
            alpha = 1.0f;
        }
    }
    if (loaded) {
        fn_80169334(0, 0xBFF, 0, lbl_806DAC18, lbl_806DAC1C, lbl_806DAC20, lbl_806DAC20, glow);
    }
    if (model != 0) {
        fn_8013D4B0(model, alpha);
        fn_8013DAC8(model, 7);
    }
    if (shellA != 0) {
        fn_8014D1E0(shellA, alpha);
        fn_8014D2AC(shellA);
    }
    if (shellB != 0) {
        fn_8014CEE8(shellB, alpha);
        fn_8014CFA0(shellB);
    }
    if (anim != 0) {
        fn_8013AE20(anim, 0.0f, 0.0f, alpha);
    }
    return 0;
}

ItemShowcase::ItemShowcase(int t) {
    const ShowAnimSet *data = &lbl_803C2E50;
    timer = 0;
    itemId = 0;
    model = 0;
    loaded = false;
    glow = lbl_806DAC10;
    alpha = lbl_806DAC10;
    shellA = 0;
    shellB = 0;
    anim = 0;
    itemId = g_humanPlayerCount;
    if (itemId <= 0) {
        return;
    }
    timer = t;
    glow = lbl_806DAC10;
    fn_8013DBF8();
    int id = itemId;
    if (id == 0x9B) {
        shellA = new ShowShellA(7, lbl_806DAC18, lbl_806DAC30, lbl_806DAC34);
        fn_8014D1E0(shellA, alpha);
    } else if (id == 0x9D) {
        shellB = new ShowShellB(7, lbl_806DAC18, lbl_806DAC30, lbl_806DAC34);
        fn_8014CEE8(shellB, alpha);
    } else {
        ShowXform *xf = fn_8013BE98();
        model = new ShowModel(ItemRes_LookupByKey_Thunk(itemId), 1);
        fn_8013D738(model, lbl_806DAC10, lbl_806DAC14);
        fn_8013D660(model, lbl_806DAC18, lbl_806DAC30);
        fn_8013D634(model, lbl_806DAC34 * xf->pos[0], lbl_806DAC34 * xf->pos[1], lbl_806DAC34 * xf->pos[2]);
        fn_8013D59C(model, lbl_806DAC38 * xf->rot[0], lbl_806DAC38 * xf->rot[1], lbl_806DAC38 * xf->rot[2]);
        float s = lbl_806DAC34 * xf->scale;
        fn_8013D608(model, s, s, s);
        if (itemId == 0x81) {
            fn_8013D50C(model, lbl_806DAC3C, lbl_806DAC3C, lbl_806DAC3C, alpha);
        } else {
            fn_8013D4B0(model, alpha);
        }
    }
    PreloadResource(0xBFF);
    loaded = true;
    PreloadResource(0x96A);
    anim = new ShowAnim(0x96A, 0, 1, data->a, 0);
    fn_8013B7A8(anim, new ShowAnim(0x96A, 0, 1, data->b, 0));
    fn_8013B7A8(anim, new ShowAnim(0x96A, 0, 1, data->c, 0));
    fn_8013B4FC(anim, -1);
}

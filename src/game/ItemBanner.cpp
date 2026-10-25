/*
 * Result item banner @ 0x8024F618..0x802506F8.
 *
 * ItemBanner (vtable lbl_804EF0A0) owns an ItemIcon (vtable lbl_804EF0B8,
 * four sprites) and a BannerFlash (vtable lbl_804EF0AC, one sprite).
 */

#include "game/FlowCountdown.h"

extern "C" {
extern const float lbl_806DC088;
extern const float lbl_806DC08C;
extern const float lbl_806DC090;
extern const float lbl_806DC094;
extern const float lbl_806DC098;
extern const float lbl_806DC09C;
extern const float lbl_806DC0A0;
extern const float lbl_806DC0A4;
extern const unsigned char lbl_806DCF70[2];
extern int lbl_803F0A70[][2];
extern float lbl_803F0A90[][2];
void *SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(void *sprite);
void SpriteHandle_SetActiveFlag(void *sprite, int active);
void SpriteHandle_RecomputeCull(void *sprite);
void SpriteHandle_SetCornerAlpha(void *sprite, unsigned char alpha);
void SpriteLayer_SetResource(void *sprite, int id);
void fn_8011F804(void *sprite, float x, float y);
void fn_8011F744(void *sprite, float sx, float sy);
int ItemAlias_DestToSource(int item, int *out);
void fn_80120A08(int id);
}

struct BannerFlash {
    virtual ~BannerFlash();
    unsigned char active;
    float x;
    float y;
    void *sprite;
    int frame;
    int loop;
    int loops;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    BannerFlash()
        : active(0), x(lbl_806DC090), y(lbl_806DC094), frame(0), loop(0), loops(6),
          scale(new FlowFaderF(lbl_806DC088)), fade(new FlowFaderI) {
        fn_8020A734(scale.p, 0xD, lbl_806DC088, lbl_806DC08C);
        fn_8020A7CC(fade.p, 0, 0xFF, 0xD);
        {
            ResCtrl rc;
            rc.resId = isJapanese() == 0 ? 0x155C : 0xD7C;
            rc.SetColor(0xFFFFFF00);
            sprite = SpriteHandle_CreateDefault(&rc, 3);
        }
    }
    void Update();
    virtual void _key();
};

struct ItemIcon {
    virtual ~ItemIcon();
    unsigned char active;
    float x;
    float y;
    void *sprites[4];
    int item;
    int kind;
    int frame;
    int loop;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade0;
    VHolder<FlowFaderI> fade1;
    ItemIcon();
    void Update();
    void Show(int item);
    virtual void _key();
};

struct ItemBanner {
    virtual ~ItemBanner();
    VHolder<ItemIcon> icon;
    VHolder<BannerFlash> flash;
    ItemBanner();
    void Update();
    void Show(int item);
    virtual void _key();
};

ItemIcon::ItemIcon()
    : active(0), x(lbl_806DC090), y(lbl_806DC094), item(0), kind(-1), frame(0), loop(0),
      scale(new FlowFaderF(lbl_806DC088)), fade0(new FlowFaderI), fade1(new FlowFaderI) {
    int i;
    fn_8020A734(scale.p, 0xD, lbl_806DC0A4, lbl_806DC098);
    fn_8020A7CC(fade0.p, 0, 0xFF, 0xD);
    fn_8020A7CC(fade1.p, 0, 0, 9);
    {
        ResCtrl rc;
        fn_80121E10(&rc);
        rc.SetColor(0xFFFFFF00);
        rc.resId = isJapanese() == 0 ? 0x1557 : 0xD77;
        sprites[0] = SpriteHandle_CreateDefault(&rc, 3);
        sprites[2] = SpriteHandle_CreateDefault(&rc, 3);
        rc.mode = 3;
        sprites[1] = SpriteHandle_CreateDefault(&rc, 3);
        sprites[3] = SpriteHandle_CreateDefault(&rc, 3);
    }
    for (i = 0; i < 4; i++) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

ItemIcon::~ItemIcon() {
    for (int i = 0; i < 4; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

void ItemIcon::Show(int id) {
    int tmp;
    int src = ItemAlias_DestToSource((unsigned char)id, &tmp);
    if (src != 0x2E && src != 0x2F && src != 0x30 && src != 0x31) {
        for (int i = 0; i < 4; i++) {
            SpriteHandle_SetActiveFlag(sprites[i], 0);
            SpriteHandle_RecomputeCull(sprites[i]);
        }
        active = 0;
    } else if (!active) {
        int vis;
        active = 1;
        item = src;
        frame = 0;
        loop = 0;
        fn_8020A734(scale.p, 0xD, lbl_806DC0A4, lbl_806DC098);
        fn_8020A7CC(fade0.p, 0, 0xFF, 0xD);
        fn_8020A7CC(fade1.p, 0, 0, 9);
        kind = -1;
        switch (item) {
        case 0x2E:
            kind = 0;
            break;
        case 0x2F:
            kind = 1;
            break;
        case 0x30:
            kind = 3;
            break;
        case 0x31:
            kind = 2;
            break;
        case 0xB9:
            kind = 0;
            break;
        case 0xBA:
            kind = 1;
            break;
        case 0xBB:
            kind = 3;
            break;
        case 0xBC:
            kind = 2;
            break;
        }
        vis = 0;
        if (kind >= 0) {
            int jp;
            vis = 1;
            jp = isJapanese() != 0;
            SpriteLayer_SetResource(sprites[2], lbl_803F0A70[kind][jp]);
            SpriteLayer_SetResource(sprites[3], lbl_803F0A70[kind][jp]);
        }
        SpriteHandle_SetActiveFlag(sprites[2], vis);
        SpriteHandle_SetActiveFlag(sprites[3], vis);
    }
}

void ItemIcon::Update() {
    int i;
    if (!active) {
        for (i = 0; i < 4; i++) {
            SpriteHandle_SetActiveFlag(sprites[i], 0);
            SpriteHandle_RecomputeCull(sprites[i]);
        }
        return;
    }
    {
        float py, px, t;
        t = fn_8020A6CC(scale.p);
        px = lbl_806DC09C * t + x;
        py = lbl_806DC0A0 * t + y;
        unsigned char alpha[2] = {0, 0};
        alpha[0] = fn_8020A788(fade0.p);
        alpha[1] = fn_8020A788(fade1.p);
        for (i = 0; i <= 1; i++) {
            fn_8011F804(sprites[i], px, py);
            fn_8011F744(sprites[i], t, t);
            SpriteHandle_SetCornerAlpha(sprites[i], alpha[i]);
            SpriteHandle_SetActiveFlag(sprites[i], 1);
        }
        if (kind >= 0) {
            float qy, qx;
            qx = t * lbl_803F0A90[kind][0] + x;
            qy = t * lbl_803F0A90[kind][1] + y;
            for (i = 2; i <= 3; i++) {
                fn_8011F804(sprites[i], qx, qy);
                fn_8011F744(sprites[i], t, t);
                SpriteHandle_SetCornerAlpha(sprites[i], alpha[i - 2]);
            }
        }
    }
    scale.p->Step();
    fade0.p->Step();
    fade1.p->Step();
    if (loop == 0) {
        if (fade1.p->Done()) {
            if (frame == 9) {
                fn_8020A7CC(fade1.p, 0, 0xFF, 4);
            } else if (frame == 0xD) {
                fn_8020A7CC(fade1.p, 0xFF, 0, 4);
            }
        }
        frame++;
        if (frame >= 0x18) {
            frame = 0;
            loop++;
        }
    } else {
        if (fade1.p->Done()) {
            if (frame == 3) {
                fn_8020A7CC(fade1.p, 0, 0xFF, 5);
            } else if (frame == 8) {
                fn_8020A7CC(fade1.p, 0xFF, 0, 4);
            }
        }
        frame++;
        if (frame >= 0x14) {
            frame = 0;
            loop++;
        }
    }
    if (loop > 6) {
        active = 0;
    }
    for (int i = 0; i < 4; i++) {
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

BannerFlash::~BannerFlash() {
    SpriteHandle_Destroy(sprite);
}

void BannerFlash::Update() {
    if (active) {
        float px = x;
        float py = y;
        float s = fn_8020A6CC(scale.p);
        fn_8011F804(sprite, px, py);
        fn_8011F744(sprite, s, s);
        SpriteHandle_SetCornerAlpha(sprite, fn_8020A788(fade.p));
        scale.p->Step();
        fade.p->Step();
        if (loop == 0) {
            if (frame == 0xD) {
                fn_8020A734(scale.p, 7, lbl_806DC08C, lbl_806DC098);
            } else if (frame == 0x14) {
                fn_8020A7CC(fade.p, 0xFF, 0, 4);
            }
            frame++;
            if (frame >= 0x18) {
                frame = 0;
                loop++;
            }
        } else {
            if (frame == 0) {
                fn_8020A734(scale.p, 7, lbl_806DC098, lbl_806DC08C);
                fn_8020A7CC(fade.p, 0, 0xFF, 7);
            } else if (frame == 7) {
                fn_8020A734(scale.p, 7, lbl_806DC08C, lbl_806DC098);
                fn_8020A7CC(fade.p, 0xFF, 0, 4);
            }
            frame++;
            if (frame >= 0x14) {
                frame = 0;
                loop++;
            }
        }
        if (loop > loops) {
            active = 0;
            SpriteHandle_SetActiveFlag(sprite, 0);
            SpriteHandle_RecomputeCull(sprite);
        }
        SpriteHandle_RecomputeCull(sprite);
    }
}

ItemBanner::ItemBanner() : icon(new ItemIcon), flash(new BannerFlash) {
    if (isJapanese() == 0) {
        PreloadResource(0x1557);
    } else {
        PreloadResource(0xD77);
    }
}

ItemBanner::~ItemBanner() {
    if (isJapanese() == 0) {
        fn_80120A08(0x1557);
    } else {
        fn_80120A08(0xD77);
    }
}

void ItemBanner::Show(int id) {
    BannerFlash *f = flash.p;
    if (id == -1) {
        f->active = 0;
        SpriteHandle_SetActiveFlag(f->sprite, 0);
        SpriteHandle_RecomputeCull(f->sprite);
    } else {
        if (!f->active) {
            f->active = 1;
            f->frame = 0;
            f->loop = 0;
            f->loops = 6;
            fn_8020A734(f->scale.p, 0xD, lbl_806DC088, lbl_806DC08C);
            fn_8020A7CC(f->fade.p, 0, 0xFF, 0xD);
        }
        SpriteHandle_SetActiveFlag(f->sprite, f->active);
    }
    icon.p->Show(id);
}

void ItemBanner::Update() {
    flash.p->Update();
    icon.p->Update();
}

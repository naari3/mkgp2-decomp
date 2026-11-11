#include "game/types/sjis_word.h"
#include "game/types/clTitleDisp2.h"

static inline void UpdateSprites(clTitleDisp2 *hud) {
    if (hud->title >= 0) {
        float off, x, y, s;
        off = fn_8020A6CC(hud->slide.p);
        y = lbl_806DC140.y;
        x = lbl_806DC140.x - off;
        s = fn_8020A6CC(hud->scale.p);
        fn_8011F744(hud->sprites[0], s, s);
        fn_8011F804(hud->sprites[0], x, y);
        SpriteHandle_SetActiveFlag(hud->sprites[0], 1);
        {
            s *= lbl_806DC148[isJapanese()];
            for (int i = 1; i < hud->count; i++) {
                x = hud->xs[i - 1] - off;
                fn_8011F744(hud->sprites[i], s, s);
                fn_8011F804(hud->sprites[i], x, lbl_806DC140.y);
                SpriteHandle_SetActiveFlag(hud->sprites[i], 1);
            }
        }
    }

}

clTitleDisp2::clTitleDisp2(int layer_)
    : layer(layer_), count(0), state(-1), title(-1), field78(0), field7C(-1),
      slide(new FlowFaderF(lbl_806DC160)), scale(new FlowFaderF(lbl_806DC160)) {
    int i;
    fn_8020A734(scale.p, 1, lbl_806DC158, lbl_806DC158);
    title = g_playerData[0x19B];
    field78 = g_playerData[0x19C];
    field7C = g_playerData[0x1B1];
    if (title < 0) {
        DebugPrintf("Cancel !!\n");
        return;
    }
    strncpy(name, get_title_name_global(GetRankLog()), 0x200);
    fn_8020A734(slide.p, 7, lbl_806DC164, lbl_806DC160);
    for (i = 0; i < 24; i++) {
        sprites[i] = 0;
    }
    {
        char *p = name;
        int n = 0;
        while (*p != 0) {
            if (SJIS_WORD(p) & 0x8000) {
                p++;
            }
            p++;
            n++;
        }
        count = n + 1;
    }
    {
        ResCtrl rc;
        rc.resId = 0xBC7;
        if (g_gameMode == 2) {
            int buf = GetDisplayBufferIndex();
            if (buf >= 0 && buf <= 3) {
                rc.resId = buf + 0xBC7;
            }
        }
        sprites[0] = SpriteHandle_CreateDefault(&rc, layer);
    }
    {
        ResCtrl rc;
        const float *ps = &lbl_806DC148[isJapanese()];
        const float *pw = &lbl_806DC150[isJapanese()];
        float w = *pw;
        float span = lbl_806DC168 * (float)(count - 1);
        float x = (lbl_806DC140.x - span * w) + lbl_806DC168 * w;
        {
            GlyphText text;
            int j;
            TexMgr_SetTexture(text.tm(), name);
            for (i = 1, j = 0; i < count; i++, j++) {
                int code;
                float s;
                fn_80121E10(&rc);
                code = text.glyphs[j];
                if (code == 0xFFFF) {
                    break;
                }
                s = *ps;
                rc.resId = TitleNameHud_nm1_data_804EF1F0[code].resId;
                rc.scaleX = s;
                rc.scaleY = s;
                xs[j] = x;
                x += *pw;
                sprites[i] = SpriteHandle_CreateDefault(&rc, layer);
            }
            for (j = 0; j < count; j++) {
                SpriteHandle_SetActiveFlag(sprites[j], 0);
                SpriteHandle_RecomputeCull(sprites[j]);
            }
        }
    }
}


clTitleDisp2::~clTitleDisp2() {
    for (int i = 0; i < count; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

extern "C" clTitleDisp2 *fn_80252D90(int layer) {
    return new clTitleDisp2(layer);
}


extern "C" void fn_80252D6C() { PreloadResource(3015); }
extern "C" void fn_80252D48() { fn_80120A08(3015); }

void clTitleDisp2::Update() {
    if (title < 0) {
        return;
    }
    switch (state) {
    case -1:
        if (g_countdownPhase <= 3) {
            state = 0;
        }
        return;
    case 0:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            fn_8020A734(scale.p, 4, lbl_806DC158, lbl_806DC15C);
            state = 2;
        }
        break;
    case 2:
        if (scale.p->Done()) {
            if (lbl_806DC158 == fn_8020A6CC(scale.p)) {
                state = 3;
            }
        }
        break;
    case 3:
        break;
    case 4:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            return;
        }
        break;
    case 5:
        return;
    default:
        return;
    }
    if (id > 0) {
        id--;
        if (id <= 0) {
            id = 0;
            state = 4;
            fn_8020A734(slide.p, 7, lbl_806DC160, lbl_806DC164);
        }
    }
    UpdateSprites(this);
    for (int j = 0; j < count; j++) {
        SpriteHandle_RecomputeCull(sprites[j]);
    }
    scale.p->Step();
    if (scale.p->Done()) {
        float v = fn_8020A6CC(scale.p);
        if (lbl_806DC15C == v) {
            fn_8020A734(scale.p, 4, lbl_806DC15C, lbl_806DC158);
        } else if (lbl_806DC158 == v) {
            fn_8020A734(scale.p, 1, lbl_806DC158, lbl_806DC158);
        }
    }
}

void clTitleDisp2::Draw() {
}


void clTitleDisp2::SetDelay(int n) {
    if (state < 4) {
        id = n + 1;
    }
}

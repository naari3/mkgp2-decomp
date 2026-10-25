/*
 * Player title name HUD part: ctor, dtor and factory @ 0x80252D90..0x80253294.
 * Update/Draw/SetDelay live in TitleNameHudUpdate.cpp; the resource
 * preload/free helpers in between are fn_80252D48.c and fn_80252D6C.c.
 */

#include "game/TitleNameHud.h"

TitleNameHud::TitleNameHud(int layer_)
    : layer(layer_), count(0), state(-1), title(-1), field78(0), field7C(-1),
      slide(new FlowFaderF(lbl_806DC160)), scale(new FlowFaderF(lbl_806DC160)) {
    int i;
    fn_8020A734(scale.p, 1, lbl_806DC158, lbl_806DC158);
    title = g_playerData[0x19B];
    field78 = g_playerData[0x19C];
    field7C = g_playerData[0x1B1];
    if (title < 0) {
        DebugPrintf(lbl_803F1194);
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
            if (*(unsigned short *)p & 0x8000) {
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
        float x = (lbl_806DC140.x - *pw * (lbl_806DC168 * (float)(count - 1))) + lbl_806DC168 * *pw;
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
                rc.resId = lbl_804EF1F0[code].resId;
                rc.scaleX = s;
                rc.scaleY = s;
                xs[j] = x;
                x += *pw;
                sprites[i] = SpriteHandle_CreateDefault(&rc, layer);
            }
        }
    }
    for (int k = 0; k < count; k++) {
        SpriteHandle_SetActiveFlag(sprites[k], 0);
        SpriteHandle_RecomputeCull(sprites[k]);
    }
}

TitleNameHud::~TitleNameHud() {
    for (int i = 0; i < count; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

#pragma dont_inline on
extern "C" TitleNameHud *fn_80252D90(int layer) {
    return new TitleNameHud(layer);
}
#pragma dont_inline reset

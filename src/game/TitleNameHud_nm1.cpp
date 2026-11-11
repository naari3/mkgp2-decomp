#include "game/types/sjis_word.h"
#include "game/TitleNameHud_nm1.h"

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


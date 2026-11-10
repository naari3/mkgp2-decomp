#include "game/Scene_8016303CPrivate.h"

extern "C" void fn_8016303C(CreditLabels162 *__restrict s) {
    const char *strings = Scene_8016303C_rodata_80369288;
    fn_801473DC(s, 0, 0x737, 0, lbl_806D88CC, lbl_806D88D0, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    if (s->credits > 0) {
        if (isJapanese() == 1) {
            if (s->changed) {
                LABEL(s, 0, strings + 0x460, lbl_806D8890);
                COUNT_LABEL(s, strings + 0x470, lbl_806D88D8);
            } else {
                LABEL(s, 0, strings + 0x460, lbl_806D8890);
                COUNT_LABEL(s, strings + 0x484, lbl_806D88D8);
            }
        } else if (s->multiple) {
            if (s->changed) {
                COUNT_LABEL(s, strings + 0x49c, lbl_806D8890);
                LABEL(s, 0, strings + 0x4a8, lbl_806D88D8);
            } else {
                COUNT_LABEL(s, lbl_806D88DC, lbl_806D8890);
                LABEL(s, 0, strings + 0x4a8, lbl_806D88D8);
            }
        } else {
            if (s->changed) {
                COUNT_LABEL(s, strings + 0x4bc, lbl_806D8890);
                LABEL(s, 0, strings + 0x4a8, lbl_806D88D8);
            } else {
                COUNT_LABEL(s, strings + 0x4d0, lbl_806D8890);
                LABEL(s, 0, strings + 0x4a8, lbl_806D88D8);
            }
        }
    } else {
        if (isJapanese() == 1) {
            if (s->credits < 0) {
                LABEL(s, 0, strings + 0x4e0, lbl_806D8890);
                LABEL(s, 0, strings + 0x4f4, lbl_806D88D8);
            }
        } else {
            TEXTURE(s, 0, GetTextureByIdAndLang(0x4f, -1), lbl_806D88E4);
        }
    }
    fn_801473DC(s, 1, 0x73d, 0, lbl_806D88CC, lbl_806D88D0, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    TEXTURE(s, 1, GetTextureByIdAndLang(0x50, -1), lbl_806D88E8);
}

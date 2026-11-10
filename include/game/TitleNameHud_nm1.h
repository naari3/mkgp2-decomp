#ifndef GAME_TITLENAMEHUD_NM1_H
#define GAME_TITLENAMEHUD_NM1_H

/*
 * Player title name HUD part @ 0x802529C8..0x80253294 (vtable TitleNameHud_vtable_804F202C).
 *
 * Shows a badge (resource 0xBC7, or 0xBC7 + display buffer in mode 2)
 * followed by one glyph sprite per character of the player's title name.
 * The glyph codes come from laying the name out in a temporary TextManager.
 */

#include "game/FlowScene.h"

#include "game/types/Vec2.h"

#include "game/types/GlyphInfo.h"

/* Stack TextManager built by TexMgr_Init; glyph codes start at +0x24. */
struct GlyphText {
    char pad000[0x24];
    unsigned short glyphs[(0x230 - 0x24) / 2];
    GlyphText();
    ~GlyphText() {}
    TextManager *tm() { return (TextManager *)this; }
};

struct RankLog;

extern "C" {
extern const Vec2 lbl_806DC140;
extern const float lbl_806DC148[2];
extern const float lbl_806DC150[2];
extern const float lbl_806DC158;
extern const float lbl_806DC15C;
extern const float lbl_806DC160;
extern const float lbl_806DC164;
extern const float lbl_806DC168;
extern const char lbl_803F1194[];
extern const GlyphInfo TitleNameHud_nm1_data_804EF1F0[];
extern unsigned char g_playerData[];
extern RankLog *lbl_806D10A0;
extern int g_countdownPhase;
extern int g_gameMode;
const char *get_title_name_global(RankLog *log);
char *strncpy(char *dst, const char *src, unsigned long n);
int GetDisplayBufferIndex(void);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
void fn_80121E10(ResCtrl *ctrl);
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
float fn_8020A6CC(FlowFader *fader);
void PreloadResource(int id);
void fn_80120A08(int id);
void DebugPrintf(const char *fmt, ...);
}

static inline RankLog *GetRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

#include "game/types/HudPart.h"

#include "game/types/TitleNameHud.h"

#endif

/* Tachometer_RenderDigits @ 0x800AB324 (0x398 bytes). */
extern void SpriteHandle_RecomputeCull(int h);
extern void SpriteHandle_SetActiveFlag(int h, unsigned char on);
extern void SpriteLayer_SetResource(int h, int res);

extern void fn_8011F744(int h, float sx, float sy);

extern void fn_8011F804(int h, float x, float y);

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1468;
extern unsigned int FLOAT_806d146c;
extern unsigned int FLOAT_806d1474;
extern int g_gameMode;
extern unsigned int g_tachometer_displaySpeed;
extern unsigned char g_tachometer_isInitialized;
extern unsigned int Tachometer_bss_806D1459;
extern const float lbl_806D4E48;
extern const float lbl_806D4E4C;
extern const float lbl_806D4E50;
extern const float lbl_806D4E54;
extern const float lbl_806D4E58;
extern const float lbl_806D4E5C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
extern unsigned int Tachometer_data_80411E20[];
extern unsigned int Tachometer_bss_805D3320[];

/* --- function index (1 fns, .text 0x800AB324..0x800AB6BC) ---
 * [  0] 0x800AB324 size:0x398   global Tachometer_RenderDigits
 */

#define TACH_UNIT (*(unsigned char *)&Tachometer_bss_806D1459) /* 1 = raw, else scaled */

static inline int Tach_GlyphRes(int glyph) {
    if (glyph < 0 || glyph >= 38) {
        return 0;
    }
    return ((int (*)[2])Tachometer_data_80411E20)[glyph][TACH_UNIT];
}

#pragma exceptions on
int Tachometer_RenderDigits(void) {
    int speed;
    int i;
    float y1;
    float x1;
    float x2;
    float y2;
    float x3;
    float y3;

    if (!g_tachometer_isInitialized) {
        return 0;
    }
    if (g_gameMode != 2) {
        float v;
        if (TACH_UNIT == 1) {
            v = TACH_F(g_tachometer_displaySpeed) * lbl_806D4E48;
        } else {
            float q = TACH_F(g_tachometer_displaySpeed) / lbl_806D4E4C;
            v = q * lbl_806D4E48;
        }
        speed = v;

        x1 = TACH_F(FLOAT_806d1468) + s_tachPos[2].x - TACH_F(FLOAT_806d1474);
        y1 = TACH_F(FLOAT_806d146c) + s_tachPos[2].y;
        SpriteLayer_SetResource(Tachometer_bss_805D3320[2], Tach_GlyphRes(s_tachGlyph[speed % 10]));
        fn_8011F804(Tachometer_bss_805D3320[2], x1, y1);
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[2], 1);

        x2 = TACH_F(FLOAT_806d1468) + s_tachPos[1].x - TACH_F(FLOAT_806d1474);
        y2 = TACH_F(FLOAT_806d146c) + s_tachPos[1].y;
        SpriteLayer_SetResource(Tachometer_bss_805D3320[3], Tach_GlyphRes(s_tachGlyph[speed / 10 % 10]));
        fn_8011F804(Tachometer_bss_805D3320[3], x2, y2);
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[3], 1);

        x3 = TACH_F(FLOAT_806d1468) + s_tachPos[0].x - TACH_F(FLOAT_806d1474);
        y3 = TACH_F(FLOAT_806d146c) + s_tachPos[0].y;
        SpriteLayer_SetResource(Tachometer_bss_805D3320[4], Tach_GlyphRes(s_tachGlyph[speed / 100 % 10]));
        fn_8011F804(Tachometer_bss_805D3320[4], x3, y3);
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[4], 1);

        fn_8011F804(Tachometer_bss_805D3320[0], lbl_806D4E50 + TACH_F(FLOAT_806d1468) - TACH_F(FLOAT_806d1474),
                    lbl_806D4E54 + TACH_F(FLOAT_806d146c));
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[0], 1);
        fn_8011F804(Tachometer_bss_805D3320[1], lbl_806D4E58 + TACH_F(FLOAT_806d1468) - TACH_F(FLOAT_806d1474),
                    lbl_806D4E5C + TACH_F(FLOAT_806d146c));
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[1], 1);
        for (i = 0; i < 5; i++) {
            fn_8011F744(Tachometer_bss_805D3320[i], TACH_F(FLOAT_806cf25c), TACH_F(FLOAT_806cf25c));
            SpriteHandle_RecomputeCull(Tachometer_bss_805D3320[i]);
        }
    }
    return 1;
}
#pragma exceptions reset
#undef TACH_UNIT

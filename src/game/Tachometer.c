/* === extracted from auto_03_800AB17C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1474;
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_coinTier;
extern unsigned char g_tachometer_isInitialized;

/* --- function index (3 fns, .text 0x800AB17C..0x800AB220) ---
 * [  0] 0x800AB17C size:0x20    global Tachometer_SetMaxSpeedRef
 * [  1] 0x800AB19C size:0x20    global Tachometer_SetDisplaySpeedRef
 * [  2] 0x800AB1BC size:0x64    global Tachometer_SetCoinCount
 */

/* --- forward decls --- */
int Tachometer_SetMaxSpeedRef(float value);
int Tachometer_SetDisplaySpeedRef(float value);
int Tachometer_SetCoinCount(int count);

/* --- asm function bodies (.text order = fn address order) --- */
int Tachometer_SetMaxSpeedRef(float value) { /* 0x800AB17C size:0x20 */
    if (!g_tachometer_isInitialized) return 0;
    *(float *)&FLOAT_806cf25c = value;
    return 1;
}

int Tachometer_SetDisplaySpeedRef(float value) { /* 0x800AB19C size:0x20 */
    if (!g_tachometer_isInitialized) return 0;
    *(float *)&FLOAT_806d1474 = value;
    return 1;
}

int Tachometer_SetCoinCount(int count) { /* 0x800AB1BC size:0x64 */
    if (!g_tachometer_isInitialized) return 0;
    g_tachometer_coinCount = count;
    if (count <= 0) g_tachometer_coinTier = 0;
    else if (count < 5) g_tachometer_coinTier = 1;
    else if (count < 10) g_tachometer_coinTier = 2;
    else g_tachometer_coinTier = 3;
    return 1;
}

typedef struct TachGlyphPos { int id; float x; float y; } TachGlyphPos;
#pragma force_active on
unsigned int Tachometer_data_80411E20[76] = { 0xbcb, 0xbcb, 0x9f0, 0x9ca, 0xbba, 0xb68, 0x9f2, 0x9cc, 0x9f3, 0x9cd, 0x9f4, 0x9ce, 0x9f5, 0x9cf, 0x9f6, 0x9d0, 0x9f7, 0x9d1, 0x9f8, 0x9d2, 0x9f9, 0x9d3, 0x9fa, 0x9d4, 0x9fb, 0x9d5, 0x9fc, 0x9d6, 0x9fd, 0x9d7, 0x9fe, 0x9d8, 0x9ff, 0x9d9, 0xa00, 0x9da, 0xa01, 0x9db, 0xa02, 0x9dc, 0xa03, 0x9dd, 0xa04, 0x9de, 0xa05, 0x9df, 0xa06, 0x9e0, 0xa07, 0x9e1, 0xa08, 0x9e2, 0xa09, 0x9e3, 0xa0a, 0x9e4, 0xbb0, 0xb5e, 0xbb1, 0xb5f, 0xbb2, 0xb60, 0xbb3, 0xb61, 0xbb4, 0xb62, 0xbb5, 0xb63, 0xbb6, 0xb64, 0xbb7, 0xb65, 0xbb8, 0xb66, 0xbb9, 0xb67 };
static TachGlyphPos s_tachPos[40] = {
{ 27, 530.0f, 443.0f },
{ 27, 553.0f, 443.0f },
{ 27, 576.0f, 443.0f },
{ 1, 573.0f, 381.0f },
{ 1, 579.0f, 381.0f },
{ 1, 585.0f, 381.0f },
{ 1, 591.0f, 381.0f },
{ 1, 597.0f, 381.0f },
{ 1, 603.0f, 381.0f },
{ 1, 609.0f, 381.0f },
{ 1, 615.0f, 381.0f },
{ 1, 621.0f, 381.0f },
{ 3, 480.0f, 457.0f },
{ 4, 480.0f, 450.0f },
{ 5, 482.0f, 443.0f },
{ 6, 483.0f, 435.0f },
{ 7, 486.0f, 429.0f },
{ 8, 489.0f, 423.0f },
{ 9, 493.0f, 417.0f },
{ 10, 498.0f, 412.0f },
{ 11, 502.0f, 407.0f },
{ 12, 508.0f, 402.0f },
{ 13, 513.0f, 398.0f },
{ 14, 519.0f, 395.0f },
{ 15, 525.0f, 392.0f },
{ 16, 532.0f, 389.0f },
{ 17, 538.0f, 387.0f },
{ 18, 545.0f, 386.0f },
{ 19, 551.0f, 385.0f },
{ 20, 559.0f, 384.0f },
{ 21, 566.0f, 384.0f },
{ 22, 573.0f, 383.0f },
{ 23, 579.0f, 383.0f },
{ 24, 585.0f, 383.0f },
{ 25, 591.0f, 383.0f },
{ 26, 597.0f, 383.0f },
{ 26, 603.0f, 383.0f },
{ 26, 609.0f, 383.0f },
{ 26, 615.0f, 383.0f },
{ 26, 621.0f, 383.0f }
};
static int s_tachGlyph[10] = { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
#pragma force_active reset
/* The remaining address-ordered members of the Tachometer unit. */
#include "Tachometer_UpdateDisplaySpeed.inc"
#include "Tachometer_RenderDigits.inc"
#include "Tachometer_Destroy.inc"
#include "Tachometer_Init.inc"

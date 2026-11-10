/* Tachometer_Init @ 0x800AB77C (size 0x1DC): C++ island. The three ResCtrl
 * locals have an empty inline dtor (dtor_80082960), which gives the extab
 * its destroy-local actions. */

extern void PreloadResource(int id);
extern unsigned int g_ccClass;
extern int Tachometer_Init_bss_806D145C;
extern const float lbl_806D4E78;
extern const float lbl_806D4E7C;
extern const float lbl_806D4E80;
extern unsigned char lbl_80598A60[];
#define TACH_IDX (*(unsigned char *)&Tachometer_bss_806D1459)
typedef struct TachResTable { int body[4]; int needle[4]; char pad20[0xE0 - 0x20]; int digit[4]; } TachResTable;
#define TACH_RES (*(TachResTable *)Tachometer_data_80411E20)
#define TACH_ZERO (*(const float *)&lbl_806D4E68)

#pragma cplusplus on
extern "C" int SpriteHandle_CreateDefault(void *ctrl, int layer);

struct ResCtrl {
    int resId;
    char pad[0x54];
    ResCtrl();
    ~ResCtrl() {}
};

#pragma exceptions on
extern "C" int Tachometer_Init(void)
{
    int i;
    int *needle;
    int *digit;

    if (g_tachometer_isInitialized == 1) {
        return 0;
    }
    g_tachometer_isInitialized = 1;
    TACH_IDX = lbl_80598A60[0x26];
    Tachometer_Init_bss_806D145C = (g_ccClass == 0) ? 0 : 6;
    g_tachometer_coinTier = 0;
    g_tachometer_coinCount = 0;
    *(float *)&FLOAT_806d1468 = TACH_ZERO;
    *(float *)&FLOAT_806d146c = TACH_ZERO;
    *(float *)&g_tachometer_maxDisplaySpeed = lbl_806D4E78;
    *(float *)&g_tachometer_displaySpeed = TACH_ZERO;
    *(float *)&FLOAT_806d1474 = TACH_ZERO;
    *(float *)&FLOAT_806cf25c = lbl_806D4E7C;
    Tachometer_UpdateDisplaySpeed(TACH_ZERO, lbl_806D4E80);
    PreloadResource(TACH_RES.body[TACH_IDX]);
    needle = TACH_RES.needle;
    PreloadResource(needle[TACH_IDX]);
    digit = TACH_RES.digit;
    PreloadResource(digit[TACH_IDX]);
    {
        ResCtrl rc;
        rc.resId = TACH_RES.body[TACH_IDX];
        Tachometer_bss_805D3320[1] = (unsigned int)SpriteHandle_CreateDefault(&rc, 4);
    }
    {
        ResCtrl rc;
        rc.resId = needle[TACH_IDX];
        Tachometer_bss_805D3320[0] = (unsigned int)SpriteHandle_CreateDefault(&rc, 4);
    }
    {
        ResCtrl rc;
        rc.resId = digit[TACH_IDX];
        for (i = 2; i < 5; i++) {
            Tachometer_bss_805D3320[i] = (unsigned int)SpriteHandle_CreateDefault(&rc, 4);
        }
    }
    for (i = 0; i < 5; i++) {
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[i], 0);
        SpriteHandle_RecomputeCull(Tachometer_bss_805D3320[i]);
    }
    return 1;
}
#pragma exceptions reset
#pragma cplusplus reset

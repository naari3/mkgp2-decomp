typedef struct WeatherSystem {
    unsigned char kind;
    unsigned char variant;
    unsigned char pad2[2];
    const int *bgmList;
    int x8;
    int xc;
    unsigned char x10;
    unsigned char pad11[3];
    float x14;
    unsigned char x18;
    unsigned char pad19[3];
    float x1c;
    int x20;
    float x24;
    float x28;
    unsigned char x2c;
    unsigned char pad2d[3];
    int x30;
} WeatherSystem;

extern unsigned int g_cupId;
extern unsigned char g_weatherSystemInitialized;
extern const int kBgmIdList_Cup1[2];
extern const int kBgmIdList_Cup2[2];
extern const int kBgmIdList_Cup3[2];
extern const int kBgmIdList_Cup4[2];
extern const int kBgmIdList_Cup5[2];
extern const int kBgmIdList_Cup6[2];
extern const int kBgmIdList_Cup7[2];
extern const int kBgmIdList_Cup8[2];
extern const int kBgmIdList_CupsExtra[2];
extern const int kBgmIdList_DefaultFallback[2];
extern const float kWeatherInitFloatA;
extern const float kWeatherInitFloatB;
extern unsigned char WeatherSystem_PickVariant(int x);

WeatherSystem *WeatherSystem_Init(WeatherSystem *w, unsigned char kind) {
    w->kind = kind;
    w->variant = WeatherSystem_PickVariant(-1);
    switch (g_cupId) {
    case 1: w->bgmList = kBgmIdList_Cup1; break;
    case 2: w->bgmList = kBgmIdList_Cup2; break;
    case 3: w->bgmList = kBgmIdList_Cup3; break;
    case 4: w->bgmList = kBgmIdList_Cup4; break;
    case 5: w->bgmList = kBgmIdList_Cup5; break;
    case 6: w->bgmList = kBgmIdList_Cup6; break;
    case 7: w->bgmList = kBgmIdList_Cup7; break;
    case 8: w->bgmList = kBgmIdList_Cup8; break;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        w->bgmList = kBgmIdList_CupsExtra; break;
    }
    if (w->bgmList == 0) w->bgmList = kBgmIdList_DefaultFallback;
    w->x8 = 0;
    w->xc = 0;
    w->x10 = 0;
    w->x14 = kWeatherInitFloatA;
    w->x18 = 0;
    w->x1c = kWeatherInitFloatA;
    w->x20 = 0;
    w->x24 = kWeatherInitFloatA;
    w->x28 = kWeatherInitFloatB;
    w->x2c = 0;
    w->x30 = -1;
    g_weatherSystemInitialized = 1;
    return w;
}

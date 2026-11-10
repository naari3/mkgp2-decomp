extern float g_dvdLastReadSec;
extern float g_dvdMaxReadSec;

float DVDLoad_GetMaxReadSec(void) {
    return g_dvdMaxReadSec;
}

float DVDLoad_GetLastReadSec(void) {
    return g_dvdLastReadSec;
}

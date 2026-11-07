#ifndef GAME_WARP_DASH_INIT_PRIVATE_H
#define GAME_WARP_DASH_INIT_PRIVATE_H
#include "game/WarpZoneVectorPrivate.h"
struct WarpZoneList : WarpZoneVectorStorage { ~WarpZoneList(); };
struct WarpRawZone { unsigned char data[0x4c]; };
struct WarpInitValue : WarpZoneValue { WarpInitValue(const WarpRawZone *); };
struct WarpZoneSource { const WarpRawZone *zones; int count; };
struct WarpDashManager {
    WarpZoneList warp, dash;
    unsigned char ready;
    WarpDashManager(int, unsigned char, unsigned char, unsigned char);
};
extern "C" {
void DebugPrintf(const char *, ...);
void WarpZoneVector_Reserve(WarpZoneVectorStorage *, unsigned long);
void WarpZoneVector_Insert(WarpZoneVectorStorage *, WarpZoneValue *, unsigned long, const WarpZoneValue *);
}
#endif

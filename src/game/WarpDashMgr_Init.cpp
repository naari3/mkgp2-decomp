/* Warp/dash manager constructor; preserves member and local C++ lifetimes. */
#include "game/WarpDashInitPrivate.h"

WarpDashManager::WarpDashManager(int course, unsigned char first, unsigned char second, unsigned char alternate) : ready(0) {
    const char *pool = lbl_80326CB0;
    const WarpZoneSource *table = ((const WarpZoneSource *const (*)[2])(pool + 0x1660))[course][alternate != 0];
    if (table) {
        int index = 0;
        if (!first) index = 2;
        if (second == 1) ++index;
        const WarpRawZone *zones = table[index].zones;
        int count = table[index].count;
        if (zones) {
            DebugPrintf(pool + 0x1770, index, count);
            WarpZoneVector_Reserve(&warp, count);
            const WarpRawZone *cursor = zones;
            for (int i = 0; i < count; ++cursor, ++i) {
                WarpInitValue value(cursor);
                WarpZoneVector_Insert(&warp, warp.data + warp.count, 1, &value);
            }
        }
    }
    table = ((const WarpZoneSource *const (*)[2])(pool + 0x16e8))[course][alternate != 0];
    if (table) {
        int index = 0;
        if (!first) index = 2;
        if (second == 1) ++index;
        const WarpRawZone *zones = table[index].zones;
        int count = table[index].count;
        if (zones) {
            DebugPrintf(pool + 0x1794, index, count);
            WarpZoneVector_Reserve(&dash, count);
            const WarpRawZone *cursor = zones;
            for (int i = 0; i < count; ++cursor, ++i) {
                WarpInitValue value(cursor);
                WarpZoneVector_Insert(&dash, dash.data + dash.count, 1, &value);
            }
        }
    }
    ready = 1;
}

/*
 * WeatherSystem_PickVariant @ 0x80193264 (size 0x94, .text).
 *
 * Pure-function weather variant picker. Returns one byte describing the
 * atmosphere animation to apply.
 *   forcedId == -1 : consult fn_800991F4 gate + g_playerData[0xC] fallback.
 *                    Gate returns 0 -> 0x5F (default overcast).
 *   forcedId ==  0 : 0x00  (clear)
 *   forcedId ==  1 : 0x50  (cloudy)
 *   forcedId ==  2 : 0x5F  (overcast / default)
 *   forcedId ==  3 : 0x73  (rain)
 *   forcedId ==  4 : 0x7F  (thunder)
 *   anything else  : 0x5F
 *
 * Caller: WeatherSystem_Init (and replacements) seeds state[+0x01].
 *
 * TU sits in `game` lib (CW 1.3.2). The function has an extab/extabindex
 * entry (large-frame flag set) so the source is wrapped with
 * `#pragma exceptions on` to let CW auto-emit them.
 */

extern unsigned char fn_800991F4(void);
extern unsigned char g_playerData[0x1DC];

#pragma exceptions on
unsigned char WeatherSystem_PickVariant(int forcedId) {
    if (forcedId < 0) {
        if ((fn_800991F4() & 0xFF) == 0) {
            return 0x5F;
        }
        forcedId = g_playerData[0xC];
    }
    switch (forcedId) {
    case 0:
        return 0x00;
    case 1:
        return 0x50;
    case 3:
        return 0x73;
    case 4:
        return 0x7F;
    case 2:
    default:
        return 0x5F;
    }
}
#pragma exceptions reset

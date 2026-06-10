/*
 * JVS analog input calibration setters @ 0x8003951C..0x800395EC.
 *
 * Three small clInputJAMMA calibration entry points. Each takes the raw
 * ADC sample captured during the calibration pass and derives the center
 * point + usable range for the corresponding analog channel, then logs
 * the result through DebugPrintf:
 *
 *   - JvsInput_SetBrakeCalibration    ("clInputJAMMA::L %d %d")
 *     center = raw + 0x800, range fixed at 0x4000
 *   - JvsInput_SetAccelCalibration    ("clInputJAMMA::R %d %d")
 *     center = raw + 0x800, range fixed at 0x4000
 *   - JvsInput_SetSteeringCalibration ("clInputJAMMA::AX %d %d")
 *     center = raw, range +0x5000 (mirrored to -0x5000 when raw + 0x5000
 *     overflows past the signed maximum)
 *
 * CW 1.3.2, -Cpp_exceptions on (each function auto-emits an 8-byte extab
 * body + extabindex entry, matching the three single-function reversed
 * extab groups at extab 0x80005E30..0x80005E48 / extabindex
 * 0x8001FA84..0x8001FAA8).
 */

extern void DebugPrintf(const char *fmt, ...);

extern char lbl_802E9904[]; /* "clInputJAMMA::L %d %d" */
extern char lbl_802E991C[]; /* "clInputJAMMA::R %d %d" */
extern char lbl_802E9934[]; /* "clInputJAMMA::AX %d %d" */

extern int g_brakeCenterRaw;
extern int g_brakeRange;
extern int g_accelCenterRaw;
extern int g_accelRange;
extern int g_steeringCenterRaw;
extern int g_steeringMaxRange;

#pragma exceptions on
void JvsInput_SetBrakeCalibration(int raw) {
    g_brakeCenterRaw = raw + 0x800;
    g_brakeRange = 0x4000;
    DebugPrintf(lbl_802E9904, g_brakeCenterRaw, 0x4000);
}

void JvsInput_SetAccelCalibration(int raw) {
    g_accelCenterRaw = raw + 0x800;
    g_accelRange = 0x4000;
    DebugPrintf(lbl_802E991C, g_accelCenterRaw, 0x4000);
}

void JvsInput_SetSteeringCalibration(int raw) {
    int range = 0x5000;
    g_steeringCenterRaw = raw;
    if (raw > raw + 0x5000) {
        range = -0x5000;
    }
    g_steeringMaxRange = range;
    DebugPrintf(lbl_802E9934, raw, range);
}
#pragma exceptions reset

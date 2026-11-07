/* Default analog calibration values, reconstructed from target assembly. */
extern void JvsInput_ClearBuffers(void);
extern void DebugPrintf(const char *, ...);
/* Original calibration message pool, with natural four-byte alignment. */
const char lbl_802E98E0[0xD] = "clInputJAMMA";
const char lbl_802E98F0[0x11] = "clInputInterface";
const char lbl_802E9904[0x17] = "clInputJAMMA::L %d %d\n";
const char lbl_802E991C[0x17] = "clInputJAMMA::R %d %d\n";
const char lbl_802E9934[0x18] = "clInputJAMMA::AX %d %d\n";
extern int g_steeringCenterRaw;
extern int g_steeringMaxRange;
extern int g_accelCenterRaw;
extern int g_accelRange;
extern int g_brakeCenterRaw;
extern int g_brakeRange;

void JvsInput_ResetCalibration(void)
{
    JvsInput_ClearBuffers();
    g_steeringCenterRaw = 0x7724;
    g_steeringMaxRange = 0x5000;
    DebugPrintf(lbl_802E9934, g_steeringCenterRaw, 0x5000);
    g_accelRange = 0x5000;
    g_accelCenterRaw = 0x88B8;
    DebugPrintf(lbl_802E991C, g_accelCenterRaw, 0x5000);
    g_brakeCenterRaw = 0x7148;
    g_brakeRange = 0x5000;
    DebugPrintf(lbl_802E9904, g_brakeCenterRaw, 0x5000);
}

/* Default analog calibration values, reconstructed from target assembly. */
extern void JvsInput_ClearBuffers(void);
extern void DebugPrintf(const char *, ...);
/* Base of the observed contiguous string pool; offsets name its messages. */
extern const char lbl_802E98E0[];
extern int g_steeringCenterRaw;
extern int g_steeringMaxRange;
extern int g_accelCenterRaw;
extern int g_accelRange;
extern int g_brakeCenterRaw;
extern int g_brakeRange;

void JvsInput_ResetCalibration(void)
{
    const char *messages = lbl_802E98E0;
    JvsInput_ClearBuffers();
    g_steeringCenterRaw = 0x7724;
    g_steeringMaxRange = 0x5000;
    DebugPrintf(messages + 0x54, g_steeringCenterRaw, 0x5000);
    g_accelRange = 0x5000;
    g_accelCenterRaw = 0x88B8;
    DebugPrintf(messages + 0x3C, g_accelCenterRaw, 0x5000);
    g_brakeCenterRaw = 0x7148;
    g_brakeRange = 0x5000;
    DebugPrintf(messages + 0x24, g_brakeCenterRaw, 0x5000);
}

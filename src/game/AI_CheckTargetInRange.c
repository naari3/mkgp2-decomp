typedef struct ItemTargeting {
    int mode;
    float range;
    float angle;
} ItemTargeting;

extern ItemTargeting g_itemTargetingTable[];
extern const float FLOAT_defaultBonus;
extern const float FLOAT_deg2rad;
extern const float lbl_806DA2A8;
extern float fn_800D3184(void *from, void *to);
extern float Vec3_HorizontalYawTo(void *from, void *to);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);

int AI_CheckTargetInRange(int item, void *from, void *to, float heading) {
    float diff;

    if (item < 0 || item > 0x115) {
        return 0;
    }
    switch (g_itemTargetingTable[item].mode) {
    case -1:
        if (g_itemTargetingTable[item].range < FLOAT_defaultBonus) {
            return 1;
        }
        if (fn_800D3184(from, to) < g_itemTargetingTable[item].range) {
            return 1;
        }
        break;
    case 0:
    case 1:
        if (fn_800D3184(from, to) < g_itemTargetingTable[item].range) {
            if (g_itemTargetingTable[item].mode == 0) {
                diff = FAbs_FloatAsDouble(BuildOrientationFromYaw(Vec3_HorizontalYawTo(from, to) - heading));
            } else {
                diff = FAbs_FloatAsDouble(BuildOrientationFromYaw(Vec3_HorizontalYawTo(from, to) - (lbl_806DA2A8 + heading)));
            }
            if (diff < FLOAT_deg2rad * g_itemTargetingTable[item].angle) {
                return 1;
            }
        }
        break;
    }
    return 0;
}

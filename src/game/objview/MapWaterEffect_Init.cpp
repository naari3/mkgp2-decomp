struct GroupParams { const char *model; void *items; int count; };
struct Group { Group *next; void *model; void *items; Group(GroupParams *); };
struct WaterBase {
    WaterBase() {}
    virtual ~WaterBase();
};
extern "C" {
extern const char lbl_8037D220[];
extern unsigned int g_cupId;
extern int g_longRoundFlag;
void DebugPrintf(const char *, ...);
void fn_80195CD4(Group *, Group *);
}
struct MapWaterEffect : WaterBase {
    Group *groups;
    int type;
    MapWaterEffect();
    virtual ~MapWaterEffect();
};
MapWaterEffect::MapWaterEffect() {
    DebugPrintf(lbl_8037D220 + 0x620);
    groups = 0;
    type = g_cupId;
    GroupParams *params = 0;
    int count = 0;
    switch (g_cupId) {
    case 2:
        if (g_longRoundFlag == 0) {
            params = (GroupParams *)(lbl_8037D220 + 0x584);
            count = 1;
        } else {
            params = (GroupParams *)(lbl_8037D220 + 0x5a4);
            count = 1;
        }
        break;
    case 10:
        params = (GroupParams *)(lbl_8037D220 + 0x584);
        count = 1;
        break;
    case 8:
        if (g_longRoundFlag == 1) {
            params = (GroupParams *)(lbl_8037D220 + 0x5d4);
            count = 1;
        }
        break;
    }
    if (params == 0 || count == 0) return;
    for (int i = 0; i < count; i++) {
        Group *g = new Group(&params[i]);
        if (groups) fn_80195CD4(groups, g);
        else groups = g;
    }
}

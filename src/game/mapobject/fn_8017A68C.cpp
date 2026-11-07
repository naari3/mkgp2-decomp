#include "game/MapSwitchBoundsPrivate.h"

struct SwitchConstantPool {
    SwitchVec bounds[2];
    char jungleHigh[0x1C];
    char jungleLow[0x1C];
    char seahouseHigh[0x20];
    char seahouseLow[0x20];
};

static const SwitchConstantPool switchConstants[1] = {{
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    "MR_highway_jungle_hi_joint",
    "MR_highway_jungle_low_joint",
    "MR_highway_seahouse_hi_joint",
    "MR_highway_seahouse_low_joint"
}};

static inline void AppendSwitchPair(SwitchList *list, HSD_JObj *shown,
                                    HSD_JObj *hidden, const char *messages) {
    if (shown && hidden) list->Append(new SwitchNode(shown, hidden, messages));
}

SwitchList::SwitchList(void *root) {
        const char *messages=(const char *)switchConstants;
        head=0;
        if (!root) return;
        switch (g_cupId) {
        case 0: break;
        case 1:
            if (g_longRoundFlag==1) {
                AppendSwitchPair(this, ResolveJointByName(root,messages+0x34),
                                 ResolveJointByName(root,messages+0x18), messages);
                AppendSwitchPair(this, ResolveJointByName(root,messages+0x70),
                                 ResolveJointByName(root,messages+0x50), messages);
            } else {
                HSD_JObjClearFlags(ResolveJointByName(root,messages+0x34),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,messages+0x18),0x10);
                HSD_JObjClearFlags(ResolveJointByName(root,messages+0x70),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,messages+0x50),0x10);
            }
            break;
        }
    }

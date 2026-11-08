#include "game/MapSwitchBoundsPrivate.h"

static const char jungleHigh[] = "MR_highway_jungle_hi_joint";
static const char jungleLow[] = "MR_highway_jungle_low_joint";
static const char seahouseHigh[] = "MR_highway_seahouse_hi_joint";
static const char seahouseLow[] = "MR_highway_seahouse_low_joint";

static inline void AppendSwitchPair(SwitchList *list, HSD_JObj *shown,
                                    HSD_JObj *hidden) {
    if (shown && hidden) list->Append(new SwitchNode(shown, hidden));
}

SwitchList::SwitchList(void *root) {
        head=0;
        if (!root) return;
        switch (g_cupId) {
        case 2:
        case 3:
            break;
        case 1:
            if (g_longRoundFlag==1) {
                AppendSwitchPair(this, ResolveJointByName(root,jungleLow),
                                 ResolveJointByName(root,jungleHigh));
                AppendSwitchPair(this, ResolveJointByName(root,seahouseLow),
                                 ResolveJointByName(root,seahouseHigh));
            } else {
                HSD_JObjClearFlags(ResolveJointByName(root,jungleLow),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,jungleHigh),0x10);
                HSD_JObjClearFlags(ResolveJointByName(root,seahouseLow),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,seahouseHigh),0x10);
            }
            break;
        }
    }

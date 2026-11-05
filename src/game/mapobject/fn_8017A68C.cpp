#include "game/MapSwitchBoundsPrivate.h"

static inline void AppendSwitchPair(SwitchList *list, HSD_JObj *shown,
                                    HSD_JObj *hidden, const char *messages) {
    if (shown && hidden) list->Append(new SwitchNode(shown, hidden, messages));
}

SwitchList::SwitchList(void *root) {
        const char *messages=lbl_80371E98;
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

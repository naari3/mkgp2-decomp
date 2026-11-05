#include "game/MapSwitchBoundsPrivate.h"

SwitchList::SwitchList(void *root) {
        const char *messages=lbl_80371E98;
        head=0;
        if (!root) return;
        switch (g_cupId) {
        case 0: break;
        case 1:
            if (g_longRoundFlag==1) {
                HSD_JObj *a=ResolveJointByName(root,messages+0x18);
                HSD_JObj *b=ResolveJointByName(root,messages+0x34);
                if (b && a) Append(new SwitchNode(b,a,messages));
                HSD_JObj *c=ResolveJointByName(root,messages+0x50);
                HSD_JObj *d=ResolveJointByName(root,messages+0x70);
                if (d && c) Append(new SwitchNode(d,c,messages));
            } else {
                HSD_JObjClearFlags(ResolveJointByName(root,messages+0x34),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,messages+0x18),0x10);
                HSD_JObjClearFlags(ResolveJointByName(root,messages+0x70),0x10);
                HSD_JObjSetFlags(ResolveJointByName(root,messages+0x50),0x10);
            }
            break;
        }
    }

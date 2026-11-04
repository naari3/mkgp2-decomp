#include "game/FlowScene.h"
#include "game/FlowMsgPopup.h"

/*
 * Message popup service (0x80203EA0..0x80204474): open/close entry points,
 * service init/shutdown, the SceneListImpl task list and the FlowTask
 * base ctor/dtor.
 */

extern "C" {
void DebugPrintf(const char *fmt, ...);
void PreloadResource(int id);
void fn_80120A08(int id);
extern const char lbl_803C250C[];
extern const char lbl_803C2528[];

int fn_80203EA0(void);
int fn_80203F5C(int msg);
void fn_802040B0(void);
void fn_80204130(int layer);
}

int fn_80203F5C(int msg) {
    return OpenMsgPopup(msg);
}

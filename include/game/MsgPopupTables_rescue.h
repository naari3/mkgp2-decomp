#ifndef GAME_MSGPOPUPTABLES_RESCUE_H
#define GAME_MSGPOPUPTABLES_RESCUE_H
#define FLOWMSGPOPUP_NO_SERVICE_HELPERS
#define SCENELISTIMPL_EXTERNAL_VTABLE
/*
 * Class-selector list lifetime and message tables @ 0x80202BCC..0x8020314C.
 */

#define MSGPOPUP_INLINE_DTOR
#include "game/FlowMsgPopup.h"

extern "C" {
extern FlowSceneList *lbl_806D19E0;
extern int lbl_806D19E4;
extern int lbl_806D19F0;
extern const int lbl_803C210C[14];
extern const int lbl_803C20D4[14];
extern const int lbl_803C1650[30];
extern unsigned char lbl_80598A60[0x2A];
void fn_80120A08(int id);
void PreloadResource(int id);
}


#endif

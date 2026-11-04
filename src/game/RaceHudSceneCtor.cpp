/* HUD scene lifetime: scene-list base, local input and message singleton. */
#include "game/RaceHudSceneCtorPrivate.h"
RaceHudScene::RaceHudScene() : position(-1),state(0) {
    if(!GetInput()) CreateHudInput();
    if(GetInput()) {
        InputState *in=GetInput();
        in->enabled=1; in->held=0; in->edge=0;
    }
    fn_801DAEC0();
    fn_801DAEC0()->SetActive(1);
    fn_801DAEC0()->SetOther(1);
    fn_8021A354();
    ItemDisplay_GetOrCreate();
    lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new ItemMsgWnd);
}

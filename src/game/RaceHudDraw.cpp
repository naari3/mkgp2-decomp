/* Deferred generation: definitions are in reverse target-address order. */
#include "game/singleton.h"
#include "game/types/clResultType01.h"
#include "game/RaceHudMethodsPrivate.h"
clResultInterface::clResultInterface() : state(-1),child(0) {
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
clResultInterface::~clResultInterface() {
    if(lbl_806D1A88) { fn_80232550(lbl_806D1A88,1); lbl_806D1A88=0; }
    fn_8011F86C(); fn_801DAEC0()->SetOther(0);
    fn_801DAE54(); fn_8021A2B4(); ItemDisplay_Destroy();
}
void clResultInterface::Update() {
    if(GetInput()) { InputState *in=g_pInputState; CGameCoin_ProcessInput(SINGLETON_INSTANCE(in)); }
    if(!this->done) {
        fn_8021A1C4(lbl_806D1A60);
        ItemDisplay_Update(ItemDisplay_GetOrCreate());
        if(!this->child) {
            if(this->state == -1) this->done=1;
            else this->Enter(this->state);
        }
        if(this->child) {
            if(!((SceneBase *)this->child)->done) ((SceneBase *)this->child)->Update();
            else this->Leave(this->state);
        }
        if(fn_801FD924(&static_cast<ResultListOwner &>(*this))) {
            if(this->child) this->Leave(this->state);
            this->state=7;
        }
        fn_801FD830(&static_cast<ResultListOwner &>(*this));
        fn_801DABFC(fn_801DAEC0());
    }
}
void clResultInterface::Draw() {
    if (!this->done) {
        fn_8021A17C(lbl_806D1A60);
        if (this->child && !((SceneBase *)this->child)->done) ((SceneBase *)this->child)->Draw();
        fn_8020AC34(ItemDisplay_GetOrCreate());
        ItemMsgWnd *msg=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new ItemMsgWnd);
        fn_802321F8(msg);
        fn_801FD800(&static_cast<ResultListOwner &>(*this));
        for(int i=0;i<=7;++i) { fn_8011F994(i); fn_8013D940(i); }
    }
}

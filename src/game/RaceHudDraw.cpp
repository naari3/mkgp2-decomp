#include "game/RaceHudMethodsPrivate.h"
extern "C" void fn_80249054(HudMethodScene *self) {
    if (!self->done) {
        fn_8021A17C(lbl_806D1A60);
        if (self->child && !self->child->done) self->child->Draw();
        fn_8020AC34(ItemDisplay_GetOrCreate());
        ItemMsgWnd *msg=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new ItemMsgWnd);
        fn_802321F8(msg);
        fn_801FD800(&self->host);
        for(int i=0;i<=7;++i) { fn_8011F994(i); fn_8013D940(i); }
    }
}

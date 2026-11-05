#include "game/ItemUseEffectPrivate.h"
ItemUseEffect::ItemUseEffect(ItemUseOwner *o, int id, void *c)
 : owner(o), context(c), state(0), item(fn_8023DBEC(id)),
 cat568(ItemUseStats_GetCountCat5_6_8(owner->stats)),
 cat79(ItemUseStats_GetCountCat7_9(owner->stats)),
 bananas(ItemUseStats_GetCountBanana(owner->stats)),
 shells(ItemUseStats_GetCountShell(owner->stats)), category(0),
 x(0.0f), y(0.0f), scale(1.0f), fade(new FlowFaderF(0.0f)),
 alpha(new FlowFaderI), size(new FlowFaderF(0.0f)), color(new FlowFaderI),
 flash(new FlowFaderI), offset(new FlowFaderF(0.0f)), burst(0) {
 fade.p->Set(0.0f, lbl_806DBEC0,8);
 alpha.p->Set(255,255,8);
 size.p->Set(0.0f,lbl_806DBEC0,8);
 color.p->Set(255,255,8);
 flash.p->Set(0,0,1);
 offset.p->Set(0.0f,0.0f,1);
}

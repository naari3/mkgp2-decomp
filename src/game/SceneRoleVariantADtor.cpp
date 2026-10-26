#include "game/SceneRoleVariantA.h"

inline VariantABase::~VariantABase() {
    fn_801F4D3C(list.p);
    fn_8020AAD4(ItemDisplay_GetOrCreate());
    fn_80120A08(0x72f);
    fn_80120A08(0x734);
    fn_80120A08(0x730);
}

VariantAOwner::~VariantAOwner() {}

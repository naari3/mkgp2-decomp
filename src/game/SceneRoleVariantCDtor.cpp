#include "game/SceneRoleVariantCPrivate.h"
inline SceneRoleVariantCBase::~SceneRoleVariantCBase()
{
    fn_801F4D3C(list.p);
    fn_8020AAD4(ItemDisplay_GetOrCreate());
    fn_80120A08(0x72F);
    fn_80120A08(0x734);
    fn_80120A08(0x730);
}
SceneRoleVariantC::~SceneRoleVariantC() {}

#include "game/types/ItemEffectCallback.h"

#include "game/types/ItemEffectState.h"

extern ItemEffectCallback lbl_803F1C68;
extern const float lbl_806D2F58;

/* 0x8007B74C: reset an item effect state to its defaults. */
void ItemEffectState_DefaultInit(ItemEffectState *st, int owner)
{
    st->owner = owner;
    st->type = -1;
    st->target = -1;
    st->cb = lbl_803F1C68;
    st->picked = 0;
    st->scale = lbl_806D2F58;
    st->index = -1;
    st->flags = 0;
}

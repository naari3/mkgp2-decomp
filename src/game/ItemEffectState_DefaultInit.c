typedef struct ItemEffectCallback {
    int a;
    int b;
    int c;
} ItemEffectCallback;

typedef struct ItemEffectState {
    int slot;
    int target;
    int owner;
    ItemEffectCallback cb;
    int timer;
    float scale;
    int index;
    int flags;
} ItemEffectState;

extern ItemEffectCallback lbl_803F1C68;
extern const float lbl_806D2F58;

/* 0x8007B74C: reset an item effect state to its defaults. */
void ItemEffectState_DefaultInit(ItemEffectState *st, int owner)
{
    st->owner = owner;
    st->slot = -1;
    st->target = -1;
    st->cb = lbl_803F1C68;
    st->timer = 0;
    st->scale = lbl_806D2F58;
    st->index = -1;
    st->flags = 0;
}

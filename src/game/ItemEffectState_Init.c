typedef struct ItemEffectCallback {
    int a;
    int b;
    int c;
} ItemEffectCallback;

typedef struct ItemEffectState {
    int type;
    int target;
    int owner;
    ItemEffectCallback cb;
    void *picked;
    float scale;
    int index;
    int flags;
} ItemEffectState;

extern ItemEffectCallback lbl_803F1C68;
extern ItemEffectCallback lbl_803FE078[];
extern const float lbl_806D2F58;

/* 0x8007B44C */
void *ItemEffectMgr_GetPickedSlot(ItemEffectState *st)
{
    if (st->picked == 0) {
        return 0;
    }
    return &st->picked;
}

/* 0x8007B468: init an item effect state and pick its tick callback. */
void ItemEffectState_Init(ItemEffectState *st, int type)
{
    ItemEffectCallback *tbl = lbl_803FE078;

    st->picked = 0;
    st->scale = lbl_806D2F58;
    st->index = -1;
    st->flags = 0;
    st->type = type;
    st->target = -1;
    switch (st->type) {
    case 1:
        st->cb = tbl[0];
        break;
    case 9:
        st->cb = tbl[1];
        break;
    case 6:
        st->cb = tbl[2];
        break;
    default:
        st->cb = lbl_803F1C68;
        break;
    }
}

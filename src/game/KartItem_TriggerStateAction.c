typedef struct KartItem KartItem;

void fn_801737F0(void *state);

void KartItem_TriggerStateAction(KartItem *item) {
    fn_801737F0(*(void **)((char *)item + 0x29c));
}

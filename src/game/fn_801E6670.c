extern int KartItem_CancelIfNotForced(void *item);
extern void fn_801E9094(void *holder);

int fn_801E6670(char *self) {
    int result = KartItem_CancelIfNotForced(*(void **)(self + 0x10));
    fn_801E9094(*(void **)(self + 0x24));
    return result;
}

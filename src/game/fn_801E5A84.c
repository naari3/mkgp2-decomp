extern const float lbl_806DA388;
extern unsigned char PathFollower_IsItemLocked(void *follower);

int fn_801E5A84(char *self, float *a, float *b, float *c) {
    int item;

    *a = lbl_806DA388;
    *b = lbl_806DA388;
    *c = lbl_806DA388;
    if (*(unsigned char *)(*(char **)(self + 0x10) + 0x2B8) == 1) {
        return 0;
    }
    if (*(void **)(self + 0x24) == 0) {
        return 0;
    }
    if (PathFollower_IsItemLocked(*(void **)(self + 0x2C))) {
        return 0;
    }
    item = *(int *)(self + 0xA8);
    if (item == 0x9B) {
        return 0;
    }
    if (item == 0x8C) {
        return 0;
    }
    if (item == 0x9A) {
        return 0;
    }
    if (item == 0x9D) {
        return 0;
    }
    *(unsigned char *)(self + 0x94) = 1;
    return 1;
}

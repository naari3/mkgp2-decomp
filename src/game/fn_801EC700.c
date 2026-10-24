extern int fn_801DBA58(void *follower);

int fn_801EC700(char *self) {
    void *follower = *(void **)(self + 0x4);
    if (follower != 0) {
        return fn_801DBA58(follower);
    }
    return -1;
}

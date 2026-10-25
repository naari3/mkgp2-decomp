extern int fn_801DBA34(void *p);

typedef struct Holder_801EC698 {
    int unk0;
    void *follower;
} Holder_801EC698;

int fn_801EC698(const Holder_801EC698 *self) {
    if (self->follower != 0) {
        return fn_801DBA34(self->follower);
    }
    return -1;
}

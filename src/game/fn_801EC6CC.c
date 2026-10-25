extern int fn_801DBA34(void *p);

typedef struct Holder_801EC6CC {
    int unk0;
    void *follower;
} Holder_801EC6CC;

int fn_801EC6CC(const Holder_801EC6CC *self) {
    if (self->follower != 0) {
        return fn_801DBA34(self->follower);
    }
    return -1;
}

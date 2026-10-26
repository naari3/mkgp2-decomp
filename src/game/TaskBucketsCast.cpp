struct BucketTask {
    virtual void _key();
    virtual void Update();
    virtual void Draw();
};
struct TaskBucket {
    void *allocation;
    unsigned int count;
    BucketTask **start;
    BucketTask **End() { return start + count; }
};
extern "C" {
extern char lbl_806D07D8[8], lbl_806D07D0[8];
void *fn_80271340(void *, int, void *, void *, int);
void fn_80240810(void *, int);
void fn_8023FE74(TaskBucket *self, int group, int value) {
    if (group < 0) return;
    TaskBucket *bucket = &self[group];
    if ((unsigned int)group >= bucket->count) return;
    for (BucketTask **it = bucket->start; it != bucket->End(); ++it) {
        void *p = fn_80271340(*it, 0, lbl_806D07D8, lbl_806D07D0, 0);
        if (p) fn_80240810(p, value);
    }
}
}

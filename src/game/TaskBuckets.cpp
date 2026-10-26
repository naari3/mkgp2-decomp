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
void fn_8023FF18(TaskBucket *self, int group) {
    TaskBucket *bucket = &self[group];
    if (bucket->count != 0) {
        for (BucketTask **it = bucket->start; it != bucket->End(); ++it) (*it)->Draw();
    }
}
int fn_8023FF90(TaskBucket *self, int group) {
    TaskBucket *bucket = &self[group];
    if (bucket->count == 0) return 0;
    for (BucketTask **it = bucket->start; it != bucket->End(); ++it) (*it)->Update();
    return 1;
}
void fn_80240014(TaskBucket *self) {
    BucketTask **it;
    TaskBucket *bucket = self;
    int i = 0;
    do {
        if (bucket->count != 0) {
            for (it = bucket->start; it != bucket->End(); ++it) (*it)->Update();
        }
        ++i;
        ++bucket;
    } while (i < 32);
}
}

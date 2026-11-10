#include "game/types/BucketTask.h"
#include "game/types/TaskBucket.h"
extern "C" {
extern char lbl_806D07D8[8], lbl_806D07D0[8];
void *fn_80271340(void *, int, void *, void *, int);
void fn_80240810(void *, int);
void fn_8023FE74(TaskBucket *self, int group, int value) {
    if (group < 0 || (unsigned int)group >= self[group].count) return;
    TaskBucket *bucket = &self[group];
    for (BucketTask **it = bucket->start; it != bucket->End(); ++it) {
        void *p = fn_80271340(*it, 0, lbl_806D07D8, lbl_806D07D0, 0);
        if (p) fn_80240810(p, value);
    }
}
}

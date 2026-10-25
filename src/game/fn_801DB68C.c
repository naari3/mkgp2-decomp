extern void *lbl_806CF010;
extern void OSFreeToHeap(void *heap, void *p);
extern void MemoryManager_TimedFree(void *);

void *fn_801DB68C(char *self, short flag) {
    if (self != 0) {
        if (*(void **)(self + 0x88) != 0) {
            OSFreeToHeap(lbl_806CF010, *(void **)(self + 0x88));
            *(void **)(self + 0x88) = 0;
        }
        if (*(void **)(self + 0x0) != 0) {
            OSFreeToHeap(lbl_806CF010, *(void **)(self + 0x0));
            *(void **)(self + 0x0) = 0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

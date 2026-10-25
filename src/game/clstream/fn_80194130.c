extern void *lbl_806CF010;
extern void *OSAllocFromHeap(void *heap, unsigned long size);

void *fn_80194130(unsigned long size) {
    return OSAllocFromHeap(lbl_806CF010, size);
}

extern void *lbl_806CF010;
extern void OSFreeToHeap(void *heap, void *ptr);

void fn_80194108(void *ptr) {
    OSFreeToHeap(lbl_806CF010, ptr);
}

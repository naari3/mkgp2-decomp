extern void *lbl_806CF010;
extern void OSFreeToHeap(void *heap, void *ptr);
extern void MemoryManager_TimedFree(void *p);

typedef struct HeapBuffer {
    int size;
    void *data;
} HeapBuffer;

HeapBuffer *fn_801F98E8(HeapBuffer *self, short flag) {
    if (self != 0) {
        if (self->data != 0) {
            OSFreeToHeap(lbl_806CF010, self->data);
            self->data = 0;
            self->size = 0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

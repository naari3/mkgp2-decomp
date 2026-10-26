/* Deleting destructor: destroys the flag model. */
typedef struct JyugemuFlag {
    void *model; /* 0x00 */
} JyugemuFlag;

extern void Object_DtorWithGXSync(void *model, int del);
extern void MemoryManager_TimedFree(void *p);

JyugemuFlag *Jyugemu_ReverseFlag_Dtor(JyugemuFlag *self, short flag)
{
    if (self != 0) {
        Object_DtorWithGXSync(self->model, 1);
        self->model = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

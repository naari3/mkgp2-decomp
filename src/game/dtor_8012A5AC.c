/* dtor_8012A5AC: deleting destructor of a two-model preview holder. */
typedef struct PreviewModels {
    void *vtbl;
    void *body;
    void *extra;
} PreviewModels;

extern char lbl_8048E34C[];
extern void Object_DtorWithGXSync(void *obj, int del);
extern void MemoryManager_TimedFree(void *p);

PreviewModels *dtor_8012A5AC(PreviewModels *self, short flag)
{
    if (self != 0) {
        self->vtbl = lbl_8048E34C;
        Object_DtorWithGXSync(self->body, 1);
        Object_DtorWithGXSync(self->extra, 1);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_TimedFree(void *p);

void *fn_8012491C(void **self, short flag)
{
    if (self != 0) {
        if (*self != 0) {
            Object_DtorWithGXSync(*self, 1);
        }
        *self = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

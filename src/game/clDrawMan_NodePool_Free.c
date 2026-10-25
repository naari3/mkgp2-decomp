extern void MemoryManager_TimedFree(void *p);

/* 0x80079BD0: deleting destructor of a clDrawMan NodePool array (trivial dtor). */
void *clDrawMan_NodePool_Free(void *self, short flag)
{
    if (self != 0 && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}

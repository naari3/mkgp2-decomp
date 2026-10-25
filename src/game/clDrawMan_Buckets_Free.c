extern void MemoryManager_TimedFree(void *p);

/* 0x80079C0C: deleting destructor of a clDrawMan Buckets array (trivial dtor). */
void *clDrawMan_Buckets_Free(void *self, short flag)
{
    if (self != 0 && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}

extern void MemoryManager_TimedFree(void *this);

#pragma exceptions on
void *dtor_801F8214(void *this, short flag) {
    if (this != 0 && flag > 0) {
        MemoryManager_TimedFree(this);
    }
    return this;
}
#pragma exceptions reset

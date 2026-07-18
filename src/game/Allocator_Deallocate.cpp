extern "C" void MemoryManager_TimedFree(void *ptr);

extern "C" void Allocator_Deallocate(void *allocator, void *ptr, int count)
{
    MemoryManager_TimedFree(ptr);
}

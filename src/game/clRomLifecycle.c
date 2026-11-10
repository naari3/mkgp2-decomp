/* Observed intrusive archive owner layout, not a complete runtime class. */
struct RomLifecycle;
extern "C" {
extern RomLifecycle* g_romListHead;
extern RomLifecycle* g_romListTail;
extern int g_romActiveCount;
void HSD_ArchiveFree(void* archive);
void HSD_Free(void* block);
}

struct RomLifecycle {
    int references;
    char pad4[4];
    RomLifecycle* previous;
    RomLifecycle* next;
    void* archive;
    unsigned char rawBlock;

    ~RomLifecycle()
    {
        --g_romActiveCount;
        if (archive != 0) {
            if (rawBlock == 0) {
                HSD_ArchiveFree(archive);
            } else {
                HSD_Free(archive);
            }
        }
        if (previous == 0) {
            g_romListHead = next;
        } else {
            previous->next = next;
        }
        if (next == 0) {
            g_romListTail = previous;
        } else {
            next->previous = previous;
        }
    }
};

extern "C" int clRom_PurgeAll(void)
{
    int count = 0;
    RomLifecycle* cursor = g_romListHead;
    while (cursor != 0) {
        RomLifecycle* next = cursor->next;
        delete cursor;
        cursor = next;
        ++count;
    }
    return count;
}

extern "C" void clRom_Release(RomLifecycle* self)
{
    if (self != 0) {
        --self->references;
        if (self->references <= 0) {
            delete self;
        }
    }
}

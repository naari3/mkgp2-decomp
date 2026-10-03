/* Observed intrusive archive owner layout, not a complete runtime class. */
struct RomLifecycle;
extern "C" {
extern RomLifecycle* lbl_806D0FE0;
extern RomLifecycle* lbl_806D0FE4;
extern int lbl_806D0FE8;
void fn_802DC964(void* archive);
void fn_802DB2D4(void* block);
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
        --lbl_806D0FE8;
        if (archive != 0) {
            if (rawBlock == 0) {
                fn_802DC964(archive);
            } else {
                fn_802DB2D4(archive);
            }
        }
        if (previous == 0) {
            lbl_806D0FE0 = next;
        } else {
            previous->next = next;
        }
        if (next == 0) {
            lbl_806D0FE4 = previous;
        } else {
            next->previous = previous;
        }
    }
};

extern "C" int clRom_PurgeAll(void)
{
    int count = 0;
    RomLifecycle* cursor = lbl_806D0FE0;
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

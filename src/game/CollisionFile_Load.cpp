/* CollisionFile_Load @ 0x801F9954 is the CECollision constructor.
 * Native member initialization plus the inline type-count helper recover
 * the shared zero and indexed table walk. Remaining mismatch: the two
 * loop increments are scheduled in the opposite order (99.74419%). */
#pragma opt_strength_reduction off
extern "C" {
#include "game/CollisionFile_Load_private.h"

}

struct CECollision {
    u32 size;
    void *data;
    void *collision;
    CECollision(const char *path);
};

extern "C" {

typedef struct CollisionTypeEntry {
    const char *name;
    u32 type;
} CollisionTypeEntry;

extern CollisionTypeEntry CollisionFile_Load_rodata_803BF3D0[];
extern int CollisionFile_Load_bss_806D19A8;
extern void *lbl_806CF010;
extern void OSFreeToHeap(void *, void *);
extern void *OSAllocFromHeap(void *, u32);
extern void DVDLoad_WaitIfSamePage(u32);
extern void DVDLoad_RecordOpStart(u32);
extern void *CollisionFile_FixupPointers(void *);

}

static inline int CountCollisionTypes(const CollisionTypeEntry *types) {
    int count = 0;
    int i = 0;
    while (types[i].name != 0) { i++; count++; }
    return count;
}

CECollision::CECollision(const char *path) : size(0), data(0), collision(0) {
    CECollision *self = this;
    CollisionDVDFileInfo file;
    u32 length;
    u32 last;
    int result;
    CollisionFile_Load_bss_806D19A8 = CountCollisionTypes(CollisionFile_Load_rodata_803BF3D0);
    if (DVDOpen(path, &file)) {
        length = (file.length + 31) & ~31;
        if (self->data) {
            OSFreeToHeap(lbl_806CF010, self->data);
            self->data = 0;
        }
        if (!self->data) {
            self->data = OSAllocFromHeap(lbl_806CF010, length);
            self->size = length;
        }
        last = file.startAddr + file.length - 1;
        DVDLoad_WaitIfSamePage(file.startAddr);
        result = DVDReadPrio(&file, self->data, length, 0, 2);
        DVDLoad_RecordOpStart(last);
        if (result >= 0) {
            self->collision = CollisionFile_FixupPointers(self->data);
            goto close;
        }
    }
    if (self->data) {
        OSFreeToHeap(lbl_806CF010, self->data);
        self->data = 0;
        self->size = 0;
    }
    self->collision = 0;
close:
    while (!DVDClose(&file)) {}
    return;
}

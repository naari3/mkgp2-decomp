/* CollisionFile_Load @ 0x801F9954: really the CECollision/DemoCollision
 * ctor (see extab_user_renames.json). C++ (cmplwi pointer tests) at the
 * default compiler; strength reduction off keeps the lwzx table walk.
 * NonMatching: the shared zero register (target reuses count's r6 for the
 * three member stores) and one add operand order. */
#pragma opt_strength_reduction off
extern "C" {
#include "game/CollisionFile_Load_private.h"

typedef struct CollisionFile {
    u32 size;
    void *data;
    void *collision;
} CollisionFile;

typedef struct CollisionTypeEntry {
    const char *name;
    u32 type;
} CollisionTypeEntry;

extern CollisionTypeEntry lbl_803BF3D0[];
extern int lbl_806D19A8;
extern void *lbl_806CF010;
extern void OSFreeToHeap(void *, void *);
extern void *OSAllocFromHeap(void *, u32);
extern void DVDLoad_WaitIfSamePage(u32);
extern void DVDLoad_RecordOpStart(u32);
extern void *CollisionFile_FixupPointers(void *);

CollisionFile *CollisionFile_Load(CollisionFile *self, const char *path) {
    CollisionDVDFileInfo file;
    u32 length;
    u32 last;
    int result;
    int count;
    count = 0;
    self->size = 0;
    self->data = 0;
    self->collision = 0;
    for (; lbl_803BF3D0[count].name != 0; count++) {}
    lbl_806D19A8 = count;
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
        last = file.length - 1;
        last += file.startAddr;
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
    return self;
}

}

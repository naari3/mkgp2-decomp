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

extern const char *lbl_803BF3D0[];
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
    self->size = 0;
    self->data = 0;
    self->collision = 0;
    for (count = 0; lbl_803BF3D0[count * 2] != 0; count++) {}
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


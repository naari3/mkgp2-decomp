/* Course path-table constructor; memory-table and file loading paths. */
#include "game/CoursePathTablePrivate.h"

inline unsigned char CourseLookup::LoadMemory(const void *source, unsigned long size, const char *pool) {
    if (!source) return 0;
    keys = FUN_8003b120(size);
    memcpy(keys, source, size);
    DebugPrintf(pool + 0x578, source, size);
    unsigned long *base = (unsigned long *)keys;
    unsigned long *cursor = base;
    int count = 0;
    while (*cursor) {
        DebugPrintf(pool + 0x528, *cursor);
        ++cursor; ++count;
    }
    DebugPrintf(pool + 0x534, count);
    values = (int *)FUN_8003b120(count * sizeof(int));
    cursor = base;
    for (int i = 0; i < count; ++cursor, ++i) {
        *cursor = (unsigned long)base + *cursor;
        values[i] = Path_CountWaypointsAndSnapGround((void *)*cursor);
    }
    return 1;
}

static inline unsigned char LoadMemoryTable(CourseLookup *self, int course, int variant, int alternate, const char *pool) {
    const CoursePathSource (*sources)[2][2] = (const CoursePathSource (*)[2][2])(pool + 0x3dc);
    const void *source;
    unsigned long size;
    if (!alternate) {
        source = sources[course][variant][0].data;
        size = sources[course][variant][0].size;
    } else {
        source = sources[course][variant][1].data;
        size = sources[course][variant][1].size;
    }

    return self->LoadMemory(source, size, pool);
}

static inline void LoadFileTable(CourseLookup *self, int course, int variant, int alternate, const char *pool) {
    const char *(*files)[2][2] = (const char *(*)[2][2])(pool + 0x34c);
    const char *file;
    if (!alternate) file = files[course][variant][0];
    else file = files[course][variant][1];
    if (file) {
        unsigned long size = (FUN_8007e344(file) + 31) & ~31;
        self->keys = FUN_8003b120(size);
        DebugPrintf(pool + 0x598, file, size);
        FUN_8007dfe4(file, self->keys, size, 0, 0);
        unsigned long *base = (unsigned long *)self->keys;
        int count = 0;
        unsigned long *cursor = base;
        while (*cursor) {
            DebugPrintf(pool + 0x528, *cursor);
            ++cursor; ++count;
        }
        DebugPrintf(pool + 0x534, count);
        self->values = (int *)FUN_8003b120(count * sizeof(int));
        cursor = base;
        for (int i = 0; i < count; ++cursor, ++i) {
            *cursor = (unsigned long)base + *cursor;
            self->values[i] = Path_CountWaypointsAndSnapGround((void *)*cursor);
        }
    }
}

CourseLookup::CourseLookup(int course, int variant, int alternate) : keys(0) {
    const char *pool = lbl_803285C0;
    if (LoadMemoryTable(this, course, variant, alternate, pool) != 1) {
        LoadFileTable(this, course, variant, alternate, pool);
    }
}

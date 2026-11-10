#include "game/types/port_hooks.h"
/* Course path-table constructor; memory-table and file loading paths. */
#include "game/CoursePathTablePrivate.h"
static const char pathFile0[] = "mr_highway_short_line.bin";
static const char pathFile1[] = "mr_highway_short_b_line.bin";
static const char pathFile2[] = "mr_highway_long_line.bin";
static const char pathFile3[] = "mr_highway_long_b_line.bin";
static const char pathFile4[] = "dk_jungle_short_line.bin";
static const char pathFile5[] = "dk_jungle_short_b_line.bin";
static const char pathFile6[] = "dk_jungle_long_line.bin";
static const char pathFile7[] = "dk_jungle_long_b_line.bin";
static const char pathFile8[] = "wc_dcity_short_line.bin";
static const char pathFile9[] = "wc_dcity_short_b_line.bin";
static const char pathFile10[] = "wc_dcity_long_line.bin";
static const char pathFile11[] = "wc_dcity_long_b_line.bin";
static const char pathFile12[] = "pc_land_short_line.bin";
static const char pathFile13[] = "pc_land_short_b_line.bin";
static const char pathFile14[] = "pc_land_long_line.bin";
static const char pathFile15[] = "pc_land_long_b_line.bin";
static const char pathFile16[] = "kp_castle_short_line.bin";
static const char pathFile17[] = "kp_castle_short_b_line.bin";
static const char pathFile18[] = "kp_castle_long_line.bin";
static const char pathFile19[] = "kp_castle_long_b_line.bin";
static const char pathFile20[] = "rb_road_short_line.bin";
static const char pathFile21[] = "rb_road_short_b_line.bin";
static const char pathFile22[] = "rb_road_long_line.bin";
static const char pathFile23[] = "rb_road_long_b_line.bin";
static const char pathFile24[] = "yi_land_short_line.bin";
static const char pathFile25[] = "yi_land_short_b_line.bin";
static const char pathFile26[] = "yi_land_long_line.bin";
static const char pathFile27[] = "yi_land_long_b_line.bin";
static const char pathFile28[] = "dn_stadium_short_line.bin";
static const char pathFile29[] = "dn_stadium_short_b_line.bin";
static const char pathFile30[] = "dn_stadium_long_line.bin";
static const char pathFile31[] = "dn_stadium_long_b_line.bin";
static const char *const pathFiles[9][2][2] = {
 {{0,0},{0,0}},
 {{pathFile0,pathFile1},{pathFile2,pathFile3}},
 {{pathFile4,pathFile5},{pathFile6,pathFile7}},
 {{pathFile8,pathFile9},{pathFile10,pathFile11}},
 {{pathFile12,pathFile13},{pathFile14,pathFile15}},
 {{pathFile16,pathFile17},{pathFile18,pathFile19}},
 {{pathFile20,pathFile21},{pathFile22,pathFile23}},
 {{pathFile24,pathFile25},{pathFile26,pathFile27}},
 {{pathFile28,pathFile29},{pathFile30,pathFile31}},
};
extern "C" const unsigned char CourseData_LoadPathTable_data_80412158[];
static const CoursePathSource pathSources[9][2][2] = {
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{CourseData_LoadPathTable_data_80412158,0x00007C4C},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
 {{{0,0x00000000},{0,0x00000000}},{{0,0x00000000},{0,0x00000000}}},
};
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define lineClass lbl_80328ABC
#define lineSingleton lbl_80328ACC
#endif
SHARED_STATIC const char lineClass[] = "clLineManager";
SHARED_STATIC const char lineSingleton[] = "teSingleton<clLineManager>";
static const char lineFormat[] = "line %08x\n";
static const char countFormat[] = "------------------------------------------- line data member %d\n";
static const char memoryFormat[] = "line data raw is %s size %d\n";
static const char fileFormat[] = "line data load file is %s size %d\n";


inline unsigned char CourseLookup::LoadMemory(const void *source, unsigned long size, const char *pool) {
    if (!source) return 0;
    keys = FUN_8003b120(size);
    memcpy(keys, source, size);
    DebugPrintf(memoryFormat, source, size);
    unsigned long *base = (unsigned long *)keys;
    unsigned long *cursor = base;
    int count = 0;
    while (*cursor) {
        DebugPrintf(lineFormat, *cursor);
        ++cursor; ++count;
    }
    DebugPrintf(countFormat, count);
    values = (int *)FUN_8003b120(count * sizeof(int));
    for (int i = 0; i < count; ++i) {
        base[i] = (unsigned long)base + base[i];
        values[i] = Path_CountWaypointsAndSnapGround((void *)base[i]);
    }
    return 1;
}

static inline unsigned char LoadMemoryTable(CourseLookup *self, int course, int variant, int alternate, const char *pool) {

    const void *source;
    unsigned long size;
    if (!alternate) {
        source = pathSources[course][variant][0].data;
        size = pathSources[course][variant][0].size;
    } else {
        source = pathSources[course][variant][1].data;
        size = pathSources[course][variant][1].size;
    }

    return self->LoadMemory(source, size, pool);
}

static inline void LoadFileData(CourseLookup *self, const char *file, unsigned long &size) {
    if (file) {
        size = (FUN_8007e344(file) + 31) & ~31;
        self->keys = FUN_8003b120(size);
        DebugPrintf(fileFormat, file, size);
        FUN_8007dfe4(file, self->keys, size, 0, 0);
        PORT_DATA_LOADED(PORT_DATA_PATH_TABLE, self->keys, size);
        unsigned long *base = (unsigned long *)self->keys;
        int count = 0;
        while (base[count]) {
            DebugPrintf(lineFormat, base[count]);
            ++count;
        }
        DebugPrintf(countFormat, count);
        self->values = (int *)FUN_8003b120(count * sizeof(int));
        for (int i = 0; i < count; ++i) {
            base[i] = (unsigned long)base + base[i];
            self->values[i] = Path_CountWaypointsAndSnapGround((void *)base[i]);
        }
    }
}

static inline void LoadFileTable(CourseLookup *self, int course, int variant, int alternate, const char *pool) {

    const char *file;
    unsigned long size;
    if (alternate == 0) file = pathFiles[course][variant][0];
    else file = pathFiles[course][variant][1];
    LoadFileData(self, file, size);
}

CourseLookup::CourseLookup(int course, int variant, int alternate) : keys(0) {
    const char *pool = pathFile0;
    if (LoadMemoryTable(this, course, variant, alternate, pool) != 1) {
        LoadFileTable(this, course, variant, alternate, pool);
    }
}

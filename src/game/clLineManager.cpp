/* Course path-table constructor; memory-table and file loading paths. */
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
extern "C" {
extern void *g_courseData;
void *FUN_8003b120(unsigned long);
void *memcpy(void *, const void *, unsigned long);
void DebugPrintf(const char *, ...);
int Path_CountWaypointsAndSnapGround(void *);
unsigned long FUN_8007e344(const char *);
void FUN_8007dfe4(const char *, void *, unsigned long, int, int);
void MemoryManager_Free(void *);
}
template <class T> struct teSingleton {
    teSingleton() { g_courseData = this; }
    virtual ~teSingleton();
};
class clLineManager;
/* fakematch (deferred codegen order): the natural code is the inline
 * `virtual ~teSingleton() {}` in the template; the specialization is an
 * ordinary function, which deferred mode emits last, where the original has
 * it (docs/notes/rtti_classes.md). */
template <> teSingleton<clLineManager>::~teSingleton() {}
class clLineManager : public teSingleton<clLineManager> {
public:
    void *keys;
    int *values;
    clLineManager(int, int, int);
    virtual ~clLineManager();
    inline void SetupLines();
    void PrintLines();
    inline unsigned char LoadMemory(const void *, unsigned long, const char *);
};
struct CoursePathSource { const void *data; unsigned long size; };
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
/* Not const: the original keeps it in .data, and the loader copies it. */
extern "C" { unsigned char CourseData_LoadPathTable_data_80412158[0x7C4C] = {
#include "game/clLineManager_kp_castle_short_line.inc"
}; }
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
static inline void *CourseData_Current() {
    if (g_courseData == 0) return 0;
    return g_courseData;
}
extern "C" void *CourseData_GetOrCreate(int first, int second, int third) {
    DebugPrintf("create line manager\n");
    if (CourseData_Current() == 0) {
        new clLineManager(first, second, third);
    }
    return CourseData_Current();
}

extern "C" void *CourseData_GetPath(void *p, int idx) {
    if (idx < 0) goto bad;
    if (idx < 6) goto good;
bad:
    return 0;
good:
    return ((void **)*(void **)((char *)p + 4))[idx];
}

extern "C" void *CourseData_GetDefaultPathKey(void *p) {
    return *(void **)((char *)*(void **)((char *)p + 4) + 0x18);
}

extern "C" int CourseData_ResolveByKey(void *p, unsigned int key) {
    unsigned int *keys = ((unsigned int **)p)[1];
    int i = 0;
    while (*keys != 0) {
        if (*keys == key) {
            return ((int **)p)[2][i];
        }
        keys++;
        i++;
    }
    return -1;
}

clLineManager::~clLineManager() {
    MemoryManager_Free(values);
    MemoryManager_Free(keys);
}



static inline unsigned char LoadMemoryTable(clLineManager *self, int course, int variant, int alternate, const char *pool);
static inline void LoadFileData(clLineManager *self, const char *file, unsigned long &size);
static inline void LoadFileTable(clLineManager *self, int course, int variant, int alternate, const char *pool);
clLineManager::clLineManager(int course, int variant, int alternate) : keys(0) {
    const char *pool = pathFile0;
    if (LoadMemoryTable(this, course, variant, alternate, pool) != 1) {
        LoadFileTable(this, course, variant, alternate, pool);
    }
}

/* Nothing calls this and the linker drops it, as it must have dropped
 * something like it from the original: the string pool has "line %08x" and
 * the member count text before the two load messages, and under deferred
 * code generation only a function defined after the constructor can put
 * them there (docs/notes/rtti_classes.md). The body is a guess. */
void clLineManager::PrintLines() {
    unsigned long *base = (unsigned long *)keys;
    int count = 0;
    while (base[count]) {
        DebugPrintf("line %08x\n", base[count]);
        ++count;
    }
    DebugPrintf("------------------------------------------- line data member %d\n", count);
}

static inline void LoadFileTable(clLineManager *self, int course, int variant, int alternate, const char *pool) {

    const char *file;
    unsigned long size;
    if (alternate == 0) file = pathFiles[course][variant][0];
    else file = pathFiles[course][variant][1];
    LoadFileData(self, file, size);
}


static inline void LoadFileData(clLineManager *self, const char *file, unsigned long &size) {
    if (file) {
        size = (FUN_8007e344(file) + 31) & ~31;
        self->keys = FUN_8003b120(size);
        DebugPrintf("line data load file is %s size %d\n", file, size);
        FUN_8007dfe4(file, self->keys, size, 0, 0);
        self->SetupLines();
    }
}

static inline unsigned char LoadMemoryTable(clLineManager *self, int course, int variant, int alternate, const char *pool) {

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

inline unsigned char clLineManager::LoadMemory(const void *source, unsigned long size, const char *pool) {
    if (!source) return 0;
    keys = FUN_8003b120(size);
    memcpy(keys, source, size);
    DebugPrintf("line data raw is %s size %d\n", source, size);
    SetupLines();
    return 1;
}

inline void clLineManager::SetupLines() {
    unsigned long *base = (unsigned long *)keys;
    int count = 0;
    while (base[count]) {
        DebugPrintf("line %08x\n", base[count]);
        ++count;
    }
    DebugPrintf("------------------------------------------- line data member %d\n", count);
    values = (int *)FUN_8003b120(count * sizeof(int));
    for (int i = 0; i < count; ++i) {
        base[i] = (unsigned long)base + base[i];
        values[i] = Path_CountWaypointsAndSnapGround((void *)base[i]);
    }
}

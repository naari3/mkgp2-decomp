/* Indivisible lookup group. Only observed vptr and pointer fields are modeled.
 * The external constructor publishes this through g_courseData itself. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);
extern "C" {
void MemoryManager_Free(void *);
void DebugPrintf(const char *, ...);
extern void *g_courseData;
extern const char lbl_80328B7C[];
}

struct CourseLookupBase {
    virtual void key();
    virtual ~CourseLookupBase() {}
};
struct CourseLookup : CourseLookupBase {
    void *keys;
    void *values;
    virtual void key();
    CourseLookup(int, int, int);
    ~CourseLookup();
};

CourseLookup::~CourseLookup() {
    MemoryManager_Free(values);
    MemoryManager_Free(keys);
}
#pragma cplusplus off

int CourseData_ResolveByKey(void *p, unsigned int key) {
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

void *CourseData_GetDefaultPathKey(void *p) {
    return *(void **)((char *)*(void **)((char *)p + 4) + 0x18);
}

void *CourseData_GetPath(void *p, int idx) {
    if (idx < 0) goto bad;
    if (idx < 6) goto good;
bad:
    return 0;
good:
    return ((void **)*(void **)((char *)p + 4))[idx];
}

#pragma cplusplus on
static inline void *CourseData_Current() {
    if (g_courseData == 0) return 0;
    return g_courseData;
}
extern "C" void *CourseData_GetOrCreate(int first, int second, int third) {
    DebugPrintf(lbl_80328B7C);
    if (CourseData_Current() == 0) {
        new CourseLookup(first, second, third);
    }
    return CourseData_Current();
}

#pragma cplusplus off

#if 0
/* Complete strong base draft (probe 1: exact 72B standalone instructions).
 * Its non-inline spelling prevented the derived base cleanup from inlining. */
#pragma cplusplus on
struct CourseLookupBaseDraft {
    virtual void key();
    virtual ~CourseLookupBaseDraft();
};
CourseLookupBaseDraft::~CourseLookupBaseDraft() {}
#pragma cplusplus off
#endif

#pragma cplusplus on
extern "C" {
extern void *lbl_80419DBC[];
void MemoryManager_TimedFree(void *);
}

/* Standalone deleting destructor of CourseLookupBase (CW does not keep the
 * inline one): reset the vtable, then free when flag > 0. */
extern "C" CourseLookupBase *dtor_800ABF10(CourseLookupBase *self, short flag)
{
    if (self) {
        *(void **)self = lbl_80419DBC;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma cplusplus off

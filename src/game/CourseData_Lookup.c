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

/* The inline base lifetime is exact in the derived destructor, but CW does
 * not retain its standalone definition. Keep the existing standalone fallback
 * and its original EH; it is not counted as genuine C++ progress. */
extern unsigned int lbl_80419DBC[];
extern void MemoryManager_TimedFree(void *);
asm void dtor_800ABF10(void);
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_dtor_800ABF10[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_800ABF10 = {
    (void *)&dtor_800ABF10, 0x00000048, (void *)extab_dtor_800ABF10
};

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

asm void dtor_800ABF10(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq dtor_800ABF10_L_800ABF40
    lis r5, lbl_80419DBC@ha
    extsh. r0, r4
    addi r0, r5, lbl_80419DBC@l
    stw r0, 0x0(r31)
    ble dtor_800ABF10_L_800ABF40
    bl MemoryManager_TimedFree
    dtor_800ABF10_L_800ABF40:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

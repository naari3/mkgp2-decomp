#ifndef GAME_COURSE_PATH_TABLE_PRIVATE_H
#define GAME_COURSE_PATH_TABLE_PRIVATE_H
extern "C" {
extern void *g_courseData;
extern const char lbl_803285C0[];
void *FUN_8003b120(unsigned long);
void *memcpy(void *, const void *, unsigned long);
void DebugPrintf(const char *, ...);
int Path_CountWaypointsAndSnapGround(void *);
unsigned long FUN_8007e344(const char *);
void FUN_8007dfe4(const char *, void *, unsigned long, int, int);
}
struct CourseLookupBase {
    CourseLookupBase() { g_courseData = this; }
    virtual void key();
    virtual ~CourseLookupBase();
};
struct CourseLookup : CourseLookupBase {
    void *keys;
    int *values;
    virtual void key();
    CourseLookup(int, int, int);
    ~CourseLookup();
    inline unsigned char LoadMemory(const void *, unsigned long, const char *);
};
struct CoursePathSource { const void *data; unsigned long size; };
#endif

extern void *g_courseData;
extern void CourseData_GetDefaultPathKey(void *);

#pragma exceptions on
void CourseData_GetDefaultPathKey_Safe(void) {
    void *ptr;
    if ((ptr = g_courseData) == 0) {
        ptr = 0;
    }
    CourseData_GetDefaultPathKey(ptr);
}
#pragma exceptions reset

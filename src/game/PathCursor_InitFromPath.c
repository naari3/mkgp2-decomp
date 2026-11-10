/* Initialise a path cursor onto the path with the given key. */
#include "game/types/PathCursor.h"

extern void *g_courseData;
extern void *CourseData_ResolveByKey(void *courseData, void *key);

PathCursor *PathCursor_InitFromPath(PathCursor *self, void *key)
{
    self->path = 0;
    self->segment = -1;
    self->key = key;
    if (key != 0) {
        self->path = CourseData_ResolveByKey(g_courseData == 0 ? 0 : g_courseData, key);
    }
    self->progress = 0;
    return self;
}

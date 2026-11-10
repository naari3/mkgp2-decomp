extern void MemoryManager_TimedFree(void *p);
extern void PathCursor_Free(void *self, short flag);

#include "game/types/PathParticipant.h"

typedef struct PathParticipantArray {
    PathParticipant karts[8];
    unsigned char pad_4C0[0x14];
    unsigned char active[8];
} PathParticipantArray;

/* 0x8003D158: deleting destructor; detaches all eight karts first. */
PathParticipantArray *PathParticipantArray_Dtor(PathParticipantArray *self, short flag)
{
    int i;

    if (self != 0) {
        for (i = 0; i < 8; i++) {
            self->karts[i].node = -1;
            self->active[i] = 0;
        }
        PathCursor_Free(self, -1);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern int PathManager_HasPathLoaded(void *mgr);

#include "game/types/PathCursor.h"

/* 0x8003CEE4: forget the path node of kart `kart` (0..7). */
void Path_ResetCursorForKart(PathCursor *cursors, int kart)
{
    if (PathManager_HasPathLoaded(cursors) && kart >= 0 && kart < 8) {
        cursors[kart].node = -1;
    }
}

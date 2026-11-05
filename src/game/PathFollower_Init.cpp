#include <game/PathFollowerPrivate.h>

PathFollower::PathFollower(FollowerDriver *owner, int id)
{
    driver = owner;
    index = id;
    selection = driver->path;
    path = PathVariant_Select(selection);
    void *data = PathData_GetByContext(PathFollower_EnsureGlobalAlloc(), path);
    if (cursor.p) {
        PathCursor_ResetToPath(cursor.p, data);
    } else {
        cursor.Assign(new FollowerCursor(data));
    }
    Vec3 position;
    Mtx44_GetTranslation_RowMajor(&position, KartDriver_GetKartRootMtx(driver));
    FollowerLocate(cursor.p, &position);
    Waypoint_Advance(cursor.p);
    mode = -1;
    cooldown = 0;
    requested = -1;
}

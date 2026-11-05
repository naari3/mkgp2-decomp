#ifndef GAME_PATHFOLLOWERPRIVATE_H
#define GAME_PATHFOLLOWERPRIVATE_H
#include <game/PathCursor.h>

struct FollowerDriver {
    char pad[0x23C];
    int path;
    int lap;
};
struct FollowerCursor : PathCursor {
    FollowerCursor(void *);
    ~FollowerCursor();
};
struct FollowerCursorOwner {
    FollowerCursor *p;
    FollowerCursorOwner() : p(0) {}
    ~FollowerCursorOwner() throw() { delete p; }
    void Assign(FollowerCursor *value) throw() {
        if (p != value) {
            delete p;
            p = value;
        }
    }
};
struct PathFollower {
    FollowerDriver *driver;
    int index;
    int path;
    FollowerCursorOwner cursor;
    int cooldown;
    int selection;
    int mode;
    int requested;
    PathFollower(FollowerDriver *, int);
};

extern "C" {
int PathVariant_Select(int);
void *PathFollower_EnsureGlobalAlloc(void);
void *PathData_GetByContext(void *, int);
void PathCursor_ResetToPath(PathCursor *, void *);
void *KartDriver_GetKartRootMtx(FollowerDriver *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, const void *);
int Waypoint_FindNearest(PathCursor *, int, float, float, float, float);
void PathCursor_SetIndex(PathCursor *, int);
void Waypoint_Advance(PathCursor *);
extern const float lbl_806DA290;
}

static inline void FollowerLocate(PathCursor *cursor, Vec3 *position)
{
    PathCursor_SetIndex(cursor, Waypoint_FindNearest(cursor, 0, position->x,
                        position->y, position->z, lbl_806DA290));
}
#endif

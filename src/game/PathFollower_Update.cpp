#include <game/PathFollowerPrivate.h>

struct FollowerInput {
    char pad[8];
    int steering;
    char tail[0x2C];
};
extern "C" {
extern int g_gameMode, g_totalLaps;
extern const int lbl_806D1898;
extern FollowerInput lbl_806793D8[];
int fn_801DC9FC(int, int);
int fn_801DC9D4(int);
int fn_801DC9AC(int);
}

static inline void ResetFollower(PathFollower *self)
{
    void *data = PathData_GetByContext(PathFollower_EnsureGlobalAlloc(), self->path);
    if (self->cursor.p) {
        PathCursor_ResetToPath(self->cursor.p, data);
    } else {
        self->cursor.Assign(new FollowerCursor(data));
    }
    Vec3 position;
    Mtx44_GetTranslation_RowMajor(&position, KartDriver_GetKartRootMtx(self->driver));
    FollowerLocate(self->cursor.p, &position);
    Waypoint_Advance(self->cursor.p);
}

extern "C" void PathFollower_Update(PathFollower *self)
{
    if (g_gameMode != 0) return;
    if (self->cooldown > 0) {
        self->cooldown--;
        return;
    }
    if (self->requested != -1) {
        self->path = self->requested;
        ResetFollower(self);
        self->requested = -1;
        self->cooldown = lbl_806D1898;
    }
    FollowerInput *input = &lbl_806793D8[self->index];
    switch (self->mode) {
    case 0:
        if (input->steering < 0) {
            self->mode = -1;
            self->selection = -1;
        }
        return;
    case 1:
        if (input->steering > 0) {
            self->mode = -1;
            self->selection = -1;
        }
        return;
    case 2:
        if (g_totalLaps - self->driver->lap != 0) {
            self->mode = -1;
            self->selection = -1;
        }
        return;
    case 3:
        if (g_totalLaps - 1 != g_totalLaps - self->driver->lap) {
            self->mode = -1;
            self->selection = -1;
        }
        return;
    case 4:
        if (g_totalLaps - self->driver->lap != 1) {
            self->mode = -1;
            self->selection = -1;
        }
        return;
    }
    int candidate = fn_801DC9FC(self->selection, -1);
    while (candidate != -1) {
        switch (fn_801DC9D4(candidate)) {
        case 0:
            if (input->steering > 0) {
                self->mode = 0;
                self->path = fn_801DC9AC(candidate);
                ResetFollower(self);
                self->cooldown = lbl_806D1898;
                return;
            }
            break;
        case 1:
            if (input->steering < 0) {
                self->mode = 1;
                self->path = fn_801DC9AC(candidate);
                ResetFollower(self);
                self->cooldown = lbl_806D1898;
                return;
            }
            break;
        case 2:
            if (g_totalLaps - self->driver->lap == 0) {
                self->mode = 2;
                self->path = fn_801DC9AC(candidate);
                ResetFollower(self);
                self->cooldown = lbl_806D1898;
                return;
            }
            break;
        case 3:
            if (g_totalLaps - 1 == g_totalLaps - self->driver->lap) {
                self->mode = 3;
                self->path = fn_801DC9AC(candidate);
                ResetFollower(self);
                self->cooldown = lbl_806D1898;
                return;
            }
            break;
        case 4:
            if (g_totalLaps - self->driver->lap == 1) {
                self->mode = 4;
                self->path = fn_801DC9AC(candidate);
                ResetFollower(self);
                self->cooldown = lbl_806D1898;
                return;
            }
            break;
        }
        candidate = fn_801DC9FC(self->selection, candidate);
    }
    if (self->selection != self->driver->path) {
        self->selection = self->driver->path;
        self->path = PathVariant_Select(self->selection);
        ResetFollower(self);
    }
}

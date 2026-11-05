#include "game/RivalMarkerPrivate.h"
#pragma fp_contract off
static inline void SetPosition(RivalMarker *p, float x, float y) { p->x = x; p->y = y; }

extern "C" void fn_80243464(RivalMarkerHud *self) {
    float fade = fn_8020A6CC(self->fade);
    void *player = GetPlayerCarObject();
    if (player) {
        RivalPosition position;
        float *matrix = CarObject_GetTransformMatrix(player);
        position.x = matrix[12];
        position.y = matrix[13];
        position.z = matrix[14];
        RivalPath *path = self->path;
        int total = Path_GetTotalCount(path);
        int nearest = Waypoint_FindNearest(path, 0, position.x, position.y, position.z, lbl_806DBE80);
        float playerDistance = fn_80243074(self, nearest, &position);
        int delta[8];
        float y = lbl_806DBE84 + fade;
        for (int i = 0; i < 8; ++i) {
            unsigned char active = 0;
            if (self->karts[i]) {
                RivalPosition other;
                float *m = KartDriver_GetKartRootMtx(self->karts[i]);
                other.x = m[3];
                other.y = m[7];
                other.z = m[11];
                int otherNearest = Waypoint_FindNearest(path, 0, other.x, other.y, other.z, lbl_806DBE80);
                float otherDistance = fn_80243074(self, otherNearest, &other);
                delta[i] = nearest - otherNearest;
                while (delta[i] >= total) delta[i] -= total;
                while (delta[i] <= -total) delta[i] += total;
                if (CarObject_GetRenderObj(player)->lap < self->karts[i]->lap && delta[i] < 0) delta[i] += total;
                float ratio = (lbl_806DBE9C - (otherDistance - playerDistance)) / lbl_806DBE9C;
                float x = lbl_806DBE98 * ratio;
                float scale = lbl_806DBE8C * (lbl_806DBE90 - (float)(delta[i] - 1) / lbl_806DBE88);
                x = x + lbl_806DBEA0;
                scale = scale + lbl_806DBE94;
                self->markers[i]->scale = scale;
                if (delta[i] <= 30 && delta[i] >= 1 && x >= lbl_806DBEA0 && x <= lbl_806DBEA4 && self->karts[i]->active != 0) active = 1;
                SetPosition(self->markers[i], x, y);
                if (!self->active) active = 0;
                self->markers[i]->active = active;
            } else {
                delta[i] = 5000;
            }
        }
        self->order[0] = 0;
        self->order[1] = 1;
        self->order[2] = 2;
        self->order[3] = 3;
        self->order[4] = 4;
        self->order[5] = 5;
        self->order[6] = 6;
        self->order[7] = 7;
        int a, b;
        for (int i = 0; i < 7; ++i) {
            for (int j = i; j < 8; ++j) {
                a = self->order[i];
                b = self->order[j];
                if (delta[a] < delta[b]) {
                    self->order[i] = b;
                    self->order[j] = a;
                }
            }
        }
    }
}

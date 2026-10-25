#include "game/mapobject/mapobject.h"

void clModelM::Update() {
    Vec3f d;
    t += path->speed;
    if (t >= 1.0f) {
        t -= 1.0f;
        index++;
        if (index >= path->count) {
            index = 0;
        }
        LoadSegment();
    }
    prevPos = pos;
    fn_80181EA4(&p0, &p1, &p2, &pos, t);
    Vec3_Subtract(&pos, &prevPos, &d);
    if (0.0f != d.x || 0.0f != d.y || 0.0f != d.z) {
        heading = atan2(d.x, d.z);
    }
    UpdateFrame();
}

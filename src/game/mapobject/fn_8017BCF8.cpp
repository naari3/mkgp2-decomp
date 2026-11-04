#include "game/mapobject/mapobject.h"

clModelM::clModelM(clNormal3D *obj, ModelDef *d) : clModel(obj, d) {
    path = (ModelPath *)d->param;
    index = 0;
    t = 0.0f;
    LoadSegment();
    pos = p0;
    prevPos = pos;
    heading = 0.0f;
}

#include "game/mapobject/mapobject17b_private.h"

extern "C" void fn_8017BC24(clModel *, clModel *);

clModelGroup::clModelGroup(const ModelEntry *entry) {
    next = 0;
    models = 0;
    obj = 0;
    obj = new clNormal3D(entry->desc, 0);
    clNormal3D_SetScale(obj, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    for (int i = 0; ; i++) {
        ModelDef *d = &entry->defs[i];
        if (d->type == -1) break;
        clModel *m;
        switch (d->type) {
        case 1: m = new clModelP(obj, d); break;
        case 2: m = new clModelPR(obj, d); break;
        case 3: m = new clModelM(obj, d); break;
        default: m = new clModel(obj, d); break;
        }
        if (models) fn_8017BC24(models, m);
        else models = m;
    }
}

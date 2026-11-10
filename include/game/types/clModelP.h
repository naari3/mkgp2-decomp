#ifndef GAME_TYPES_CLMODELP_H
#define GAME_TYPES_CLMODELP_H

#include "game/types/ModelDef.h"
#include "game/types/Vec3f.h"

/* Declare before including (each user already does): clModel, clNormal3D */

class clModelP : public clModel {
public:
    Vec3f *param;
    virtual void Draw();

    clModelP(clNormal3D *obj, ModelDef *d) : clModel(obj, d) {
        param = (Vec3f *)d->param;
    }
};

#endif /* GAME_TYPES_CLMODELP_H */

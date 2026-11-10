#ifndef GAME_TYPES_CLMODELPR_H
#define GAME_TYPES_CLMODELPR_H

#include "game/types/ModelDef.h"
#include "game/types/ModelParam.h"

/* Declare before including (each user already does): clModel, clNormal3D */

class clModelPR : public clModel {
public:
    ModelParam *param;
    virtual void Draw();

    clModelPR(clNormal3D *obj, ModelDef *d) : clModel(obj, d) {
        param = (ModelParam *)d->param;
        if (def->flags & 0x18) {
            Mtx m;
            Mtx r;
            PSMTXRotRad(m, 'Z', param->rotZ);
            PSMTXRotRad(r, 'X', param->rotX);
            PSMTXConcat(m, r, m);
            PSMTXRotRad(r, 'Y', param->rotY);
            PSMTXConcat(m, r, m);
            offset.x = 0.0f;
            offset.y = 0.0f;
            offset.z = 0.0f;
            float h = def->height;
            float half = 0.5f * h;
            if (def->flags & 8) {
                offset.x += m[0][1] * h;
                offset.y += m[1][1] * h;
                offset.z += m[2][1] * h;
            }
            if (def->flags & 0x10) {
                offset.x += m[0][1] * half;
                offset.y += m[1][1] * half;
                offset.z += m[2][1] * half;
            }
        }
    }
};

#endif /* GAME_TYPES_CLMODELPR_H */

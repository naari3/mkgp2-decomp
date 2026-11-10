#include "game/EnemyFace_private.h"

void clEFaceModel::Trigger(int arg) {
    sub->Reset(arg);
    for (int i = 0; i < 2; i++) {
        clNormal3D_SetScale(models[i], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    }
    state = 0;
}

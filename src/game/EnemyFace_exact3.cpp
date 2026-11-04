#include "game/EnemyFace_private.h"

void EnemyFace_Preload() {
    PreloadResource(0xC2F);
    PreloadResource(0xC30);
    PreloadResource(0xC31);
    PreloadResource(0xC29);
    PreloadResource(0xC49);
    PreloadResource(0xC32);
}

clEnemyFace *EnemyFace_Create(void *path, int param) {
    return new clEnemyFace(path, param);
}

clEnemyFace::~clEnemyFace() {
    for (int i = 3; i >= 0; i--) {
        if (faces[i]) {
            delete faces[i];
            faces[i] = 0;
            delete icons[i];
            icons[i] = 0;
            delete rings[i];
            rings[i] = 0;
        }
    }
}

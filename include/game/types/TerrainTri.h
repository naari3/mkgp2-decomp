#ifndef GAME_TYPES_TERRAINTRI_H
#define GAME_TYPES_TERRAINTRI_H

typedef struct TerrainTri {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    float v[3][3];
    float edgeNormal[3][3];
    unsigned int wallEdges;
    unsigned char pad_5C[4];
    float plane[4];
} TerrainTri;

#endif /* GAME_TYPES_TERRAINTRI_H */

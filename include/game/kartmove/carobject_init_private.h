#ifndef GAME_KARTMOVE_CAROBJECT_INIT_PRIVATE_H
#define GAME_KARTMOVE_CAROBJECT_INIT_PRIVATE_H

#include "game/kartmove/carobject_private.h"

struct MovementSettings {
    int field08;
    float field0c, field10, field14, field18, field1c;
    unsigned char field20, field21;
    bool field22;
    unsigned char field23;
    int field24, field28;
    MovementSettings(int, int, bool);
};

struct MovementState {
    CarTrivial vector;
    float scale, value;
    MovementState(float, float);
};

struct CarMovementInit {
    void *owner;
    unsigned char *config;
    MovementSettings settings;
    float field2c;
    unsigned char field30, pad31[7];
    float field38, field3c;
    InitVec pos, prev;
    Matrix44 orientation, previous, matrixD8, matrix118;
    InitVec v158, v164, v170, v17c, v188, v194, v1a0;
    MovementState state;
    float field1c0, pad1c4, yaw;
    float field1cc, field1d0, pad1d4;
    float field1d8, field1dc, field1e0, field1e4, field1e8;
    InitVec v1ec, v1f8;
    Matrix44 matrix204;
    unsigned char field244, field245, field246, pad247;
    int field248;
    float field24c, field250;
    unsigned char flags[4];
    CarElem elems[4];
    float wheelValues[4];
    InitVec v298, v2a4, v2b0;
    unsigned char field2bc, field2bd, field2be, pad2bf;
    int field2c0, field2c4, field2c8, pad2cc, pad2d0;
    float field2d4, field2d8;
    unsigned char field2dc, pad2dd[3];
    float field2e0, field2e4, field2e8, field2ec, field2f0, field2f4, field2f8;
    unsigned char field2fc, field2fd, field2fe, pad2ff;
    float field300;
    InitVec v304, v310;
    int pad31c;
    void *field320;
    CarMovementInit(void *, unsigned char *, void *, float, float, float);
};

typedef char CarMovementInitSizeCheck[(sizeof(CarMovementInit) == 0x324) ? 1 : -1];


#endif

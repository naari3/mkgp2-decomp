#ifndef GAME_TYPES_CLENEMYRUNINTERFACE_H
#define GAME_TYPES_CLENEMYRUNINTERFACE_H

#include "game/types/Vec3f.h"
#include "game/types/PathUserHolder.h"

/* The base owns the path and the 0x198-byte enemy-run state. Member types
 * and offsets follow the existing EnemyRunState constructor view. */
class clEnemyRunInterface {
public:
    clEnemyRunInterface(int owner, int driver, int kart, int pathIndex, int character);
    virtual ~clEnemyRunInterface() {
        driverId = 0;
        ownerId = 0;
    }
    virtual float CalcSteering(float input);

    PathUserHolder user;
    int ownerId,driverId,kartId,pathId,characterId;
    char reserved1C[0x30];
    Vec3f position,previous;
    unsigned char active;
    char reserved65[3];
    float speed,smoothYaw,targetYaw,smoothPitch,targetPitch,yaw,roll,matrixYaw;
    unsigned char enabled;
    char reserved89[3];
    float field8C,field90,field94,field98;
    unsigned char field9C,reverse;
    char reserved9E[2];
    int cooldown;
    unsigned char fieldA4,fieldA5;
    char reservedA6[2];
    Vec3f vectorA8,vectorB4;
    int fieldC0,fieldC4,fieldC8;
    Vec3f push,collision;
    float world[16];
    int field124,field128;
    Vec3f vector12C;
    unsigned char field138;
    char reserved139[3];
    float scale,field140,field144;
    int field148,field14C,field150;
    float field154;
    int field158;
    float field15C;
    int field160,field164;
    float field168;
    unsigned char airborne;
    char reserved16D[3];
    Vec3f field170,velocity;
    unsigned char field188;
    char reserved189[3];
    int field18C,field190;
    float field194;
};

#endif

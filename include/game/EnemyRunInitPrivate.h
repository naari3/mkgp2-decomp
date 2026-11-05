#ifndef GAME_ENEMY_RUN_INIT_PRIVATE_H
#define GAME_ENEMY_RUN_INIT_PRIVATE_H
#include "game/PhysicsCollisionPrivate.h"
#include "game/FlowScene.h"
struct EnemyRunPath {
    char storage[0x20];
    EnemyRunPath(int,int);
    ~EnemyRunPath();
};
struct EnemyRunMatrix {
    float m[16];
    void identity() {
        for(int i=0;i<16;i++) m[i]=0.0f;
        m[0]=m[5]=m[10]=m[15]=1.0f;
    }
    EnemyRunMatrix &operator*=(const EnemyRunMatrix &b) {
        EnemyRunMatrix result;
        int n=0;
        for(int i=0;i<4;i++) {
            const float *column=b.m;
            for(int j=0;j<4;j++,column++) {
                float value=m[i*4]*column[0];
                value+=m[i*4+1]*column[4];
                value+=m[i*4+2]*column[8];
                value+=m[i*4+3]*column[12];
                result.m[n+j]=value;
            }
            n+=4;
        }
        for(int i=0;i<16;i++) m[i]=result.m[i];
        return *this;
    }
};
struct EnemyRunState {
    void *vtable;
    VHolder<EnemyRunPath> path;
    int ownerId,driverId,kartId,pathId,characterId;
    char reserved1C[0x30];
    PhysicsCollisionVec position,previous;
    unsigned char active;
    char reserved65[3];
    float speed,smoothYaw,targetYaw,smoothPitch,targetPitch,yaw,roll,matrixYaw;
    unsigned char enabled;
    char reserved89[3];
    float field8C,field90,field94,field98;
    unsigned char field9C,avoiding;
    char reserved9E[2];
    int cooldown;
    unsigned char fieldA4,fieldA5;
    char reservedA6[2];
    PhysicsCollisionVec vectorA8,vectorB4;
    int fieldC0,fieldC4,fieldC8;
    PhysicsCollisionVec push,collision;
    EnemyRunMatrix world;
    int field124,field128;
    PhysicsCollisionVec vector12C;
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
    PhysicsPlainVec field170,velocity;
    unsigned char field188;
    char reserved189[3];
    int field18C,field190;
    float field194;
    EnemyRunState(int,int,int,int,int);
};
#endif

#ifndef GAME_SMOOTHING_PRIVATE_H
#define GAME_SMOOTHING_PRIVATE_H
#include "game/PhysicsCollisionPrivate.h"

struct SmoothingMatrix {
    float m[16];
    void identity() {
        float zero=lbl_806DA42C;
        float one=lbl_806DA450;
        for (int i=0;i<16;i++) m[i]=zero;
        m[0]=m[5]=m[10]=m[15]=one;
    }
    SmoothingMatrix &operator*=(const SmoothingMatrix &b) {
        SmoothingMatrix out;
        int n=0;
        for(int i=0;i<4;i++) {
            for(int j=0;j<4;j++) {
                float sum=b.m[j]*m[i*4];
                sum+=b.m[4+j]*m[i*4+1];
                sum+=b.m[8+j]*m[i*4+2];
                sum+=b.m[12+j]*m[i*4+3];
                out.m[n+j]=sum;
            }
            n+=4;
        }
        for(int k=0;k<16;k++) m[k]=out.m[k];
        return *this;
    }
};
struct SmoothingState {
    char reserved0[0x4];
    void * path;
    char reserved8[0x8];
    int kartId;
    char reserved14[0x38];
    float positionX;
    float positionY;
    float positionZ;
    float previousX;
    float previousY;
    float previousZ;
    char reserved64[0x4];
    float speed;
    float smoothYaw;
    float targetYaw;
    float smoothPitch;
    float targetPitch;
    float yaw;
    char reserved80[0x4];
    float matrixYaw;
    char reserved88[0x5C];
    SmoothingMatrix world;
    char reserved124[0x18];
    float scale;
    char reserved140[0x2C];
    unsigned char airborne;
    char reserved16D[0xF];
    float velocityX;
    float velocityY;
    float velocityZ;
};
#endif

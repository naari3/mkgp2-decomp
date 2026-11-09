#ifndef GAME_PHYSICS_WALL_MATRIX_PRIVATE_H
#define GAME_PHYSICS_WALL_MATRIX_PRIVATE_H

#include "game/PhysicsCollisionPrivate.h"

/* Flat storage matches the 16-element matrix copies and indexed product. */
struct PhysicsWallMatrix {
    float m[16];
    PhysicsWallMatrix() {}
    PhysicsWallMatrix(const PhysicsWallMatrix &other) {
        for (int i = 0; i < 16; ++i) m[i] = other.m[i];
    }
    void identity() {
        m[15] = m[10] = m[5] = m[0] = 0.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;
        m[4] = 0.0f;
        m[6] = 0.0f;
        m[7] = 0.0f;
        m[8] = 0.0f;
        m[9] = 0.0f;
        m[11] = 0.0f;
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[0] = m[5] = m[10] = m[15] = lbl_806DA450;
    }
    PhysicsWallMatrix &operator*=(const PhysicsWallMatrix &b) {
        PhysicsWallMatrix result;
        const float *row=m;
        const float *column;
        float *output=result.m;
        const float *right=b.m;
        int n=0;
        for(int i=0;i<4;i++) {
            column=right;
            for(int j=0;j<4;j++,column++) {
                float value=row[0]*column[0];
                value+=row[1]*column[4];
                value+=row[2]*column[8];
                value+=row[3]*column[12];
                output[n+j]=value;
            }
            row+=4;
            n+=4;
        }
        for(int i=0;i<16;i++) m[i]=result.m[i];
        return *this;
    }
    PhysicsWallMatrix(float yaw) {
        identity();
        float cosine = (float)cos(yaw);
        float sine = (float)sin(yaw);
        m[0] = cosine;
        m[8] = sine;
        m[10] = cosine;
        m[2] = -sine;
    }
    void applyYaw(float yaw) {
        PhysicsWallMatrix rotation(yaw);
        rotation *= *this;
        *this = rotation;
    }
};
#endif

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
        m[15] = m[10] = m[5] = m[0] = lbl_806DA42C;
        m[1] = lbl_806DA42C;
        m[2] = lbl_806DA42C;
        m[3] = lbl_806DA42C;
        m[4] = lbl_806DA42C;
        m[6] = lbl_806DA42C;
        m[7] = lbl_806DA42C;
        m[8] = lbl_806DA42C;
        m[9] = lbl_806DA42C;
        m[11] = lbl_806DA42C;
        m[12] = lbl_806DA42C;
        m[13] = lbl_806DA42C;
        m[14] = lbl_806DA42C;
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
    void applyYaw(float yaw) {
        PhysicsWallMatrix rotation;
        rotation.identity();
        float cosine = (float)cos(yaw);
        float sine = (float)sin(yaw);
        rotation.m[0] = cosine;
        rotation.m[8] = sine;
        rotation.m[10] = cosine;
        rotation.m[2] = -sine;
        rotation *= *this;
        *this = rotation;
    }
};
#endif

/* 0x8019BF80: rebuild the kart's orientation matrix from its four ground
 * contact corners. */

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

struct Vec {
    float x, y, z;
    Vec() {}
    ~Vec() {}
};

typedef struct KartFrame {
    char pad0[0x44];
    float height;
    char pad48[0x58 - 0x48];
    float mtx[3][4];
    char pad88[0x8c - 0x88];
    float height2;
    char pad90[0x258 - 0x90];
    Vec3f cornerB;
    Vec3f cornerA;
    Vec3f cornerD;
    Vec3f cornerC;
} KartFrame;

extern "C" {
extern void QuadFrame_FromPackedCorners(Vec *corners, Vec *axes, float *h);
extern void Mtx34_Orthonormalize(float *mtx);
}

extern "C" void fn_8019BF80(KartFrame *k) {
    Vec c[4];
    Vec axes[3];
    float h;
    c[0].x = k->cornerA.x;
    c[0].y = k->cornerA.y;
    c[0].z = k->cornerA.z;
    c[1].x = k->cornerB.x;
    c[1].y = k->cornerB.y;
    c[1].z = k->cornerB.z;
    c[2].x = k->cornerC.x;
    c[2].y = k->cornerC.y;
    c[2].z = k->cornerC.z;
    c[3].x = k->cornerD.x;
    c[3].y = k->cornerD.y;
    c[3].z = k->cornerD.z;
    QuadFrame_FromPackedCorners(c, axes, &h);
    k->height = h;
    k->mtx[0][0] = axes[0].x;
    k->mtx[0][1] = axes[0].y;
    k->mtx[0][2] = axes[0].z;
    k->mtx[1][0] = axes[1].x;
    k->mtx[1][1] = axes[1].y;
    k->mtx[1][2] = axes[1].z;
    k->mtx[2][0] = axes[2].x;
    k->mtx[2][1] = axes[2].y;
    k->mtx[2][2] = axes[2].z;
    k->height2 = h;
    Mtx34_Orthonormalize(&k->mtx[0][0]);
}

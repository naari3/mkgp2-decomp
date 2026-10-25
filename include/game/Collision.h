#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

/* Sphere/box collision objects and their manager (0x80207E3C..0x80209330). */

struct Vec {
    float x, y, z;
};
typedef float Mtx[3][4];

extern "C" {
void PSMTXIdentity(Mtx m);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXRotRad(Mtx m, char axis, float rad);
void PSVECAdd(const Vec *a, const Vec *b, Vec *ab);
void PSVECScale(const Vec *src, Vec *dst, float scale);
float PSVECSquareDistance(const Vec *a, const Vec *b);
void Vec3_Subtract(const Vec *a, const Vec *b, Vec *out);
float Vec3_Magnitude(const Vec *v);
float Vec3_Dot(const Vec *a, const Vec *b);
}

/* Type 0 objects are spheres of the given radius, type 1 objects are rotated boxes. */
struct CollisionObject {
    unsigned char hit;
    CollisionObject *other;
    float depth;
    Vec normal;
    Vec contact;
    CollisionObject *next;
    int type;
    int field2C;
    float radius;
    Vec half;
    Vec rot;
    Vec pos;
    ~CollisionObject();
};

#endif

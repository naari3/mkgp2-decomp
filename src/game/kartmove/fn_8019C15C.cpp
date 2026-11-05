#include "game/kartmove/ground_private.h"
#include "game/kartmove/speed_private.h"

extern SuspensionParam lbl_804963F8[2];
extern const float lbl_806D9704, lbl_806D973C, lbl_806D9744;
extern const float lbl_806D9748, lbl_806D974C, lbl_806D9728;
extern const char lbl_8037DDC8[], lbl_8037DDD4[];
extern "C" {
unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *, float *, Vec3 *, int *, float);
float Terrain_GetTractionFactor(int);
float Terrain_GetSlipFactor(int);
float LUT_Cosine(float);
void DebugPrintf(const char *, ...);
}

static inline void TransformCorner(Vec3 *dst, Matrix44 *m, Vec3 *v) {
    float z, y, x;
    x = v->x; y = v->y; z = v->z;
    dst->x = m->m[3][0] + (z*m->m[2][0] + (m->m[0][0]*x + y*m->m[1][0]));
    dst->y = m->m[3][1] + (z*m->m[2][1] + (m->m[0][1]*x + y*m->m[1][1]));
    dst->z = m->m[3][2] + (z*m->m[2][2] + (x*m->m[0][2] + y*m->m[1][2]));
}

extern "C" void fn_8019C15C(MovementInit *k) {
    InitVec up;
    Vec3 normal;
    int terrain;
    float height;
    unsigned char contact = 0;
    float lift;
    float zero, uy, ux, uz;
    zero = lbl_806D96D0;
    lift = zero;
    k->v1a0.x = zero; k->v1a0.y = zero; k->v1a0.z = zero;
    uy = k->orientation.m[1][1]; uz = k->orientation.m[1][2]; ux = k->orientation.m[1][0];
    up.y = uy; up.x = ux; up.z = uz;
    unsigned char inverted;
    if (up.y < lbl_806D96D0) inverted = 1;
    else inverted = 0;
    if (Terrain_GetGroundHeightWithPenetration(&k->pos, &height, &normal, &terrain, lbl_806D973C) == 1) {
        k->field2c4 = terrain;
        k->field2c8 = terrain;
        if (k->field2bd == 0) {
            float traction = Terrain_GetTractionFactor(k->field2c8);
            float tractionB = Terrain_GetTractionFactor(k->field2c4);
            tractionB = tractionB + traction;
            traction = lbl_806D9704 * tractionB;
            float slip = Terrain_GetSlipFactor(k->field2c8);
            float slipB = Terrain_GetSlipFactor(k->field2c4);
            slipB = slipB + slip;
            k->field2f0 = lbl_806D9704 * slipB;
            if (k->field2f4 > traction) {
                k->v17c.x *= lbl_806D9728;
                k->v17c.y *= lbl_806D9728;
                k->v17c.z *= lbl_806D9728;
            }
            k->field2f4 = traction;
        }
    } else DebugPrintf(lbl_8037DDC8);
    for (int i = 0; i < 4; i++) {
        float h, compression;
        Vec3 n;
        Vec3 *corner = (Vec3 *)&k->elems[i];
        k->flags[i] = 1;
        TransformCorner(corner, &k->orientation, (Vec3 *)(k->config + 0x90 + i*12));
        h = lbl_806D96D0;
        if (Terrain_GetGroundHeightWithPenetration(corner, &h, &n, 0, lbl_806D9744) == 1) {
            if (!inverted) {
                float cy;
                float z;
                z = lbl_806D96D0; cy = corner->y;
                compression = cy - h;
                if (compression >= z) {
                    if (compression > lbl_804963F8[i >> 1].limit) {
                        compression = lbl_804963F8[i >> 1].limit;
                        k->flags[i] = 0;
                        h = corner->y;
                    } else {
                        contact = 1;
                        if (n.y > lbl_806D96D0) {
                            k->v1a0.x += n.x;
                            k->v1a0.y += n.y;
                            k->v1a0.z += n.z;
                        }
                    }
                } else { compression = lbl_806D96D0; contact = 1; }
            } else {
                compression = lbl_804963F8[i >> 1].limit;
                float clearance = lbl_806D9748 * LUT_Cosine(lbl_806D974C * up.y);
                float d = corner->y - h;
                if (d < clearance) {
                    float delta = clearance - d;
                    if (lift < delta) lift = delta;
                    h = corner->y;
                    k->flags[i] = 1;
                } else { k->flags[i] = 0; h = corner->y; }
            }
        } else {
            DebugPrintf(lbl_8037DDD4);
            h = ((Vec3 *)&k->elems[i])->y;
            compression = k->wheelValues[i];
        }
        ((Vec3 *)&k->elems[i])->y = h;
        k->wheelValues[i] = compression;
    }
    for (int j = 0; j < 4; j++) ((Vec3 *)&k->elems[j])->y += lift;
    if (contact == 1) {
        float one, z, value;
        value = k->v194.y; one = lbl_806D96D4; z = lbl_806D96D0;
        k->v194.y = value + one;
        if (k->v194.y > z) k->v194.y = z;
    }
    float len = k->v1a0.z*k->v1a0.z + (k->v1a0.x*k->v1a0.x + k->v1a0.y*k->v1a0.y);
    KART_SPEED_ROOT(len);
    if (len > lbl_806D96D0) {
        len = k->v1a0.z*k->v1a0.z + (k->v1a0.x*k->v1a0.x + k->v1a0.y*k->v1a0.y);
        KART_SPEED_ROOT(len);
        if (len <= lbl_806D96D0) {
            k->v1a0.z = lbl_806D96D0; k->v1a0.y = lbl_806D96D0; k->v1a0.x = lbl_806D96D0;
        } else {
            float scale = lbl_806D96D4 / len;
            k->v1a0.x *= scale; k->v1a0.y *= scale; k->v1a0.z *= scale;
        }
    } else {
        float x, y, z;
        z = k->orientation.m[1][2]; y = k->orientation.m[1][1]; x = k->orientation.m[1][0];
        k->v1a0.x = x; k->v1a0.y = y; k->v1a0.z = z;
    }
}

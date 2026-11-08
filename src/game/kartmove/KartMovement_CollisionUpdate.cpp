#include "game/kartmove/collision_private.h"

#pragma fp_contract off
static inline float LengthSquared(const CollisionVec& v) {
    return v.z*v.z + (v.x*v.x + v.y*v.y);
}
#pragma fp_contract on
static inline float Length(const CollisionVec& v) {
    float len = LengthSquared(v);
    KART_SPEED_ROOT(len);
    return len;
}
static inline void Normalize(CollisionVec& v) {
    float x = v.x, y = v.y, z = v.z;
    float len = LengthSquared(v);
    KART_SPEED_ROOT(len);
    if (len <= lbl_806D96D0) {
        v.z = lbl_806D96D0; v.y = lbl_806D96D0; v.x = lbl_806D96D0;
    } else {
        float scale = lbl_806D96D4 / len;
        x = v.x; y = v.y; z = v.z;
        x *= scale; y *= scale; z *= scale;
        v.x = x; v.y = y; v.z = z;
    }
}
struct CollisionMatrix {
    float m[16];
    void Identity() {
        m[15] = m[10] = m[5] = m[0] = lbl_806D96D0;
        m[4] = m[3] = m[2] = m[1] = lbl_806D96D0;
        m[9] = m[8] = m[7] = m[6] = lbl_806D96D0;
        m[14] = m[13] = m[12] = m[11] = lbl_806D96D0;
        m[0] = m[5] = m[10] = m[15] = lbl_806D96D4;
    }
    void Scale(float scale) {
        for (int row = 0; row < 3; ++row) {
            m[row*4] *= scale;
            m[row*4+1] *= scale;
            m[row*4+2] *= scale;
        }
    }
    void Transform(const Vec3& v, CollisionVec& out) const {
        out.x = m[12] + (v.z*m[8] + (m[0]*v.x + v.y*m[4]));
        out.y = m[13] + (v.z*m[9] + (m[1]*v.x + v.y*m[5]));
        out.z = m[14] + (v.z*m[10] + (v.x*m[2] + v.y*m[6]));
    }
    void Multiply(const CollisionMatrix& b) {
        float out[16];
        const float *row = m;
        const float *column;
        float *output = out;
        const float *right = b.m;
        int n = 0;
        for (int i = 0; i < 4; i++) {
            column = right;
            for (int j = 0; j < 4; j++, column++) {
                float value = row[0] * column[0];
                value += row[1] * column[4];
                value += row[2] * column[8];
                value += row[3] * column[12];
                output[n + j] = value;
            }
            row += 4;
            n += 4;
        }
        for (int i = 0; i < 16; ++i) m[i] = out[i];
    }
};
#pragma fp_contract off
static inline float PlainDot(const CollisionVec& a, const CollisionVec& b) {
    float x = a.x*b.x;
    float y = a.y*b.y;
    float z = a.z*b.z;
    return z + (x + y);
}
#pragma fp_contract on
static inline void RemoveNormal(Vec3& v, const Vec3& n) {
    float dot = v.z*n.z + (v.x*n.x + v.y*n.y);
    v.x -= n.x*dot; v.y -= n.y*dot; v.z -= n.z*dot;
}

extern "C" void KartMovement_CollisionUpdate(KartCollisionState* k) {
    CollisionVec previous(k->prevPos.x, k->prevPos.y, k->prevPos.z);
    Vec3 point, normal;
    int retries = 0;
    if (Terrain_RaycastWall(&previous, &k->pos, &point, &normal) == 1) {
        k->pos.x = point.x;
        k->pos.z = point.z;
    }
    CollisionVec forward(k->matrix[8], k->matrix[9], k->matrix[10]);
    Normalize(forward);
    CollisionVec up(k->matrix[4], k->matrix[5], k->matrix[6]);
    Normalize(up);
    float len = Length(up);
    float scale = lbl_806D9718 * (lbl_806D96D4 - len);
    up.x *= scale; up.y *= scale; up.z *= scale;
    unsigned char collided;
    do {
        collided = 0;
        for (int corner = 0; corner < 4; ++corner) {
            CollisionVec hitPoint, hitNormal, contact;
            CollisionMatrix transform;
            for (int j = 0; j < 16; ++j) transform.m[j] = k->matrix[j];
            transform.Scale(k->scale);
            const Vec3* local = &k->params->probes[corner];
            transform.Transform(*local, contact);
            if (Terrain_RaycastWall(&k->pos, &contact, &hitPoint, &hitNormal) != 1) continue;
            k->wallPoint.x = hitPoint.x; k->wallPoint.y = hitPoint.y; k->wallPoint.z = hitPoint.z;
            hitPoint.x -= contact.x; hitPoint.y -= contact.y; hitPoint.z -= contact.z;
            hitPoint.y = lbl_806D96D0;
            k->pos.x += hitPoint.x; k->pos.y += hitPoint.y; k->pos.z += hitPoint.z;
            k->matrix[12] = k->pos.x; k->matrix[14] = k->pos.z;
            if (corner < 2) {
                Saturate_Double(PlainDot(forward, hitNormal), lbl_806D9704, lbl_806D96D4);
                float yawChange = lbl_806D971C * k->steering;
                double angle = lbl_806D96F0 * yawChange;
                CollisionMatrix identity, rotation;
                identity.Identity(); rotation.Identity();
                k->yaw += yawChange;
                float c = (float)cos((float)angle);
                float s = (float)sin((float)angle);
                rotation.m[0] = c; rotation.m[8] = s; rotation.m[10] = c; rotation.m[2] = -s;
                rotation.Multiply(identity);
                identity = rotation;
                ((CollisionMatrix*)k->matrix)->Multiply(identity);
                k->matrix[12] = k->pos.x; k->matrix[13] = k->pos.y; k->matrix[14] = k->pos.z;
                float vx = k->velocity.x, vy = k->velocity.y, vz = k->velocity.z;
                k->velocity.x = identity.m[12] + (vz*identity.m[8] + (identity.m[0]*vx + vy*identity.m[4]));
                k->velocity.y = identity.m[13] + (vz*identity.m[9] + (identity.m[1]*vx + vy*identity.m[5]));
                k->velocity.z = identity.m[14] + (vz*identity.m[10] + (vx*identity.m[2] + vy*identity.m[6]));
                float groundHeight;
                if (Terrain_GetGroundHeightWithPenetration(&contact, &groundHeight, 0, 0, lbl_806D96D4) == 1) {
                    float height = groundHeight - contact.y;
                    if (height > lbl_806D9720 && height < lbl_806D9718 && k->groundSpeed > lbl_806D9724) {
                        float speed = lbl_806D9728*k->speed;
                        float maxSpeed = k->speedTable[k->speedClass].maxSpeed;
                        if (speed > maxSpeed) speed = maxSpeed;
                        k->speed = speed;
                        int count = 0;
                        if (k->grounded[0] == 1) count = 1;
                        if (k->grounded[1] == 1) ++count;
                        if (k->grounded[2] == 1) ++count;
                        if (k->grounded[3] == 1) ++count;
                        if (count > 1 && !(k->jumpTimer > lbl_806D96D0)) {
                            k->jumpTimer = lbl_806D9700 * (lbl_806D96D4-k->matrix[5]) + lbl_806D972C;
                            k->jumpNormal = *(Vec3*)&k->matrix[4];
                            RemoveNormal(k->velocity, k->jumpNormal);
                            k->acceleration.x = k->acceleration.y = k->acceleration.z = lbl_806D96D0;
                            k->jumpOrigin = k->pos;
                            k->jumping = 1;
                        }
                    }
                }
                k->frontHit = 1;
                CollisionVec n(hitNormal.x, hitNormal.y, hitNormal.z);
                if (k->hitTimer == 0) {
                    k->velocity.x *= k->wallDamping; k->velocity.y *= k->wallDamping; k->velocity.z *= k->wallDamping;
                    k->velocity.x += hitNormal.x; k->velocity.y += hitNormal.y; k->velocity.z += hitNormal.z;
                }
                n.x *= lbl_806D9730; n.y *= lbl_806D9730; n.z *= lbl_806D9730;
                float dot = k->velocity.z*n.z + (k->velocity.x*n.x + k->velocity.y*n.y);
                k->velocity.x -= n.x*dot; k->velocity.y -= n.y*dot; k->velocity.z -= n.z*dot;
                k->hitTimer = 15;
                if (k->speed > lbl_806D9734) {
                    float speed = lbl_806D9738*k->speed;
                    float maxSpeed = k->speedTable[k->speedClass].maxSpeed;
                    if (speed > maxSpeed) speed = maxSpeed;
                    k->speed = speed;
                }
            } else {
                k->rearHit = 1;
            }
            k->hit = 1;
            collided = 1;
            ++retries;
            k->angularVelocity.x = k->angularVelocity.y = k->angularVelocity.z = lbl_806D96D0;
            break;
        }
    } while (collided && retries < 16);
}

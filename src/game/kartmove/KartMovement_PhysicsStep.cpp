#include "game/kartmove/carobject_private.h"

extern const float lbl_806D96D0, lbl_806D96D4, lbl_806D9704;
extern const float lbl_806D973C, lbl_806D9740, lbl_806D974C;
extern const float lbl_806D9750, lbl_806D9754, lbl_806D9758, lbl_806D975C;
extern const float lbl_806D9760, lbl_806D9764, lbl_806D9768, lbl_806D976C;
extern const float lbl_806D9770, lbl_806D9774, lbl_806D9778, lbl_806D977C;
extern const float lbl_806D9780, lbl_806D9784, lbl_806D9788, lbl_806D978C;
extern const float lbl_806D9790, lbl_806D9794, lbl_806D9798, lbl_806D979C;
extern const float lbl_806D97A8;
extern const double lbl_806D96F0, lbl_806D96F8, lbl_806D97A0;

extern "C" {
void fn_8019EA8C(Vec3 *);
float fn_8019EA08(Vec3 *);
float fn_8019E9C0(Vec3 *, Vec3 *);
void fn_8019EC18(Matrix44 *, float);
void fn_8019EB9C(Matrix44 *, Vec3 *, Vec3 *);
void fn_8019ADF4(MovementInit *, Vec3 *);
float Saturate_Double(float, float, float);
float LUT_Cosine(float);
double asin(double);
void SpeedCurve_UpdateSpeedCap(void *, float);
float KartMovement_CalcSpeedWithCoinBonus(MovementInit *, unsigned char);
void fn_8019C6B4(MovementInit *);
void KartMovement_CollisionUpdate(MovementInit *);
void fn_8019C15C(MovementInit *);
void fn_8019C078(MovementInit *);
void fn_8019BF80(MovementInit *);
unsigned char Terrain_GetGroundHeight(Vec3 *, float *, void *, void *);
}

static inline float Param(MovementInit *k, int offset) {
    return *(float *)(k->config + offset);
}
static inline void Scale(Vec3 &v, float s) { v.x *= s; v.y *= s; v.z *= s; }
static inline void Add(Vec3 &v, const Vec3 &b) { v.x += b.x; v.y += b.y; v.z += b.z; }
static inline void Sub(Vec3 &v, const Vec3 &b) { v.x -= b.x; v.y -= b.y; v.z -= b.z; }
static inline void Copy(Vec3 &v, const Vec3 &b) { v.x = b.x; v.y = b.y; v.z = b.z; }
#pragma fp_contract off
static inline float Dot(const Vec3 &a, const Vec3 &b) {
    float x = a.x*b.x;
    float y = a.y*b.y;
    float z = a.z*b.z;
    return z + (x+y);
}
#pragma fp_contract reset
static inline float Abs(float v) { return __fabs(v); }
static inline void Clear(Vec3 &v) { v.x = lbl_806D96D0; v.y = lbl_806D96D0; v.z = lbl_806D96D0; }

static inline float SteeringMagnitude(float value) {
    double magnitude = __fabs(value);
    return (float)magnitude;
}

static inline int QuantizeSteering(float value) {
    return (int)(lbl_806D9750 * value);
}

static inline void ProjectSubtract(Vec3 &v, const Vec3 &b) {
    for (int i = 0; i < 3; ++i) (&v.x)[i] -= (&b.x)[i];
}
static inline void ProjectScale(Vec3 &v, float scale) {
    for (int i = 0; i < 3; ++i) (&v.x)[i] *= scale;
}
static inline void ProjectAdd(Vec3 &v, const Vec3 &b) {
    for (int i = 0; i < 3; ++i) (&v.x)[i] += (&b.x)[i];
}

static inline void ApplyDisplacement(MovementInit *k, Vec3 &displacement, float scale) {
    k->prev.Set(k->pos.x, k->pos.y, k->pos.z);
    Scale(displacement, scale);
    Add(k->pos, displacement);
}

extern "C" void KartMovement_PhysicsStep(MovementInit *k, unsigned char active,
                                         float steering, float throttle, float brake) {
    float force;
    float yawTurn;
    float turn;
    float grip = lbl_806D96D4;
    int airborne = 0;
    Scale((Vec3 &)k->v1ac, k->field1bc);
    k->field2dc = 0;
    if (k->field248 > 0) --k->field248;
    if (k->flags[0] == 0) airborne = 1;
    if (k->flags[1] == 0) ++airborne;
    if (k->flags[2] == 0) ++airborne;
    if (k->flags[3] == 0) ++airborne;
    if (airborne == 4) k->field2bd = 1;
    else {
        if (k->field2bd == 1) k->field2be = 1;
        else k->field2be = 0;
        k->field2bd = 0;
    }
    float quantized = (float)QuantizeSteering(steering) * lbl_806D9754;
    float absolute = Abs(quantized);
    if (absolute < lbl_806D9740) turn = lbl_806D96D0;
    else {
        float v = absolute - lbl_806D9740;
        if (quantized < lbl_806D96D0) v = -v;
        turn = lbl_806D9758 * v;
    }
    yawTurn = -turn;
    k->pad1c4 = yawTurn;
    if (k->field30 == 1) k->pad1c4 = -k->pad1c4;
    Scale(k->v1f8, lbl_806D975C);
    if (airborne != 4 && k->v2a4.y <= lbl_806D96D0) {
        InitVec velocity = k->v17c;
        fn_8019EA8C(&velocity);
        InitVec forward(k->orientation.m[2][0], k->orientation.m[2][1], k->orientation.m[2][2]);
        fn_8019EA8C(&forward);
        float blend = lbl_806D9704 * (1.0f + Dot(velocity, forward));
        Scale(k->v17c, blend * Param(k, 0x50) + (1.0f-blend)*Param(k, 0x54));
    }
    k->field1d0 = k->yaw;
    Matrix44 matrix;
    for (int i = 0; i < 16; ++i) ((float *)&matrix)[i] = ((float *)&k->orientation)[i];
    fn_8019EC18(&matrix, (float)(lbl_806D96F0 * (lbl_806D9760 * k->pad1c4)));
    matrix.m[3][0] = lbl_806D96D0; matrix.m[3][1] = lbl_806D96D0; matrix.m[3][2] = lbl_806D96D0;
    k->v158.x = lbl_806D96D0; k->v158.y = lbl_806D96D0;
    k->v158.z = lbl_806D96D4;
    fn_8019EB9C(&matrix, &k->v158, &k->v158);
    k->field14 = lbl_806D96D0;
    if (brake > lbl_806D96D0) {
        grip = lbl_806D96D4 - brake;
        if (throttle <= lbl_806D96D0) grip *= lbl_806D9704;
    }
    if (throttle > 0.0f) k->field14 = throttle;
    Copy(k->v170, k->v158);
    if (airborne != 4 && k->v2a4.y <= lbl_806D96D0) {
        float speed = k->field2d8 * (k->field21 == 0 ? k->field10 : -k->field10);
        Scale(k->v170, speed);
        float resistance = lbl_806D9764 * (lbl_806D96D4-grip);
        float normal = k->v1a0.z*k->v170.z + (k->v1a0.x*k->v170.x + k->v1a0.y*k->v170.y);
        k->v170.x -= k->v1a0.x * normal;
        k->v170.y -= k->v1a0.y * normal;
        k->v170.z -= k->v1a0.z * normal;
        k->v17c.x -= k->v17c.x * resistance;
        k->v17c.y -= k->v17c.y * resistance;
        k->v17c.z -= k->v17c.z * resistance;
    } else Scale(k->v170, fn_8019EA08(&k->v17c));
    if (!active) Clear(k->v170);
    Copy(k->v164, k->v170);
    Scale(k->v164, k->field2f4);
    Sub(k->v164, k->v17c);
    if (airborne != 4 && k->v2a4.y <= lbl_806D96D0) fn_8019ADF4(k, &k->v164);
    force = fn_8019EA08(&k->v164);
    float previousSpeed = fn_8019EA08(&k->v188);
    float response = k->field1d8;
    previousSpeed = Param(k, 0x18) * previousSpeed;
    force += response * previousSpeed;
    float targetSpeed = fn_8019EA08(&k->v170);
    if (fn_8019EA08(&k->v17c) > targetSpeed) force *= lbl_806D9768;
    float limit = k->field2f8 * (k->field38 + k->field2ec);
    float targetResponse, targetDamping;
    if (force > limit) {
        targetResponse = limit / force;
        targetResponse *= k->field3c;
        Scale(k->v188, targetResponse);
        float lower = Param(k, 0x2c) * k->field2f0;
        if (targetResponse <= lower) targetResponse = lower;
        targetDamping = Param(k, 8);
    } else {
        targetDamping = Param(k, 4);
        Scale(k->v188, lbl_806D96D0);
        targetResponse = lbl_806D96D4;
    }
    {
        InitVec velocity(k->v17c.x, k->v17c.y, k->v17c.z);
        velocity.y = lbl_806D96D0;
        fn_8019EA8C(&velocity);
        InitVec desired(k->v170.x, k->v170.y, k->v170.z);
        desired.y = lbl_806D96D0;
        fn_8019EA8C(&desired);
        float alignment = Dot(desired, velocity);
        if (alignment > lbl_806D96D0)
        {
            float correction = alignment*Param(k, 0x80);
            targetResponse = Saturate_Double(targetResponse + correction, Param(k, 0x2c)*k->field2f0, lbl_806D96D4);
        }
        if (k->field1d8 > targetResponse) {
            k->field1d8 -= Param(k, 0x34);
            if (k->field1d8 < targetResponse) k->field1d8 = targetResponse;
        } else {
            k->field1d8 += Param(k, 0x30);
            if (k->field1d8 > targetResponse) k->field1d8 = targetResponse;
        }
        if (k->field1dc > targetDamping) {
            k->field1dc -= Param(k, 0x38);
            if (k->field1dc < targetDamping) k->field1dc = targetDamping;
        } else {
            k->field1dc += Param(k, 0x38);
            if (k->field1dc > targetDamping) k->field1dc = targetDamping;
        }
        Scale(k->v164, k->field1d8);
        Add(k->v17c, k->v164);
    }
    if (airborne != 4 && k->v2a4.y <= lbl_806D96D0) {
        float current = fn_8019EA08(&k->v17c);
        float desiredSpeed = fn_8019EA08(&k->v170);
        k->field2fe = 1;
        if (current < desiredSpeed) k->field2fe = 0;
        if (k->field2fc == 1 && current < k->field2e4 + (desiredSpeed+Param(k, 0x84))) {
            InitVec velocity(k->v17c.x, k->v17c.y, k->v17c.z);
            InitVec desired(k->v170.x, k->v170.y, k->v170.z);
            {
                InitVec extra(desired.x, desired.y, desired.z);
                fn_8019EA8C(&extra);
                Scale(extra, Param(k, 0x84)+k->field2e4);
                Add(desired, extra);
                Scale(desired, lbl_806D9704+k->field2e8);
                Add(velocity, desired);
            }
            fn_8019EA8C(&velocity);
            Scale(velocity, lbl_806D9704*(current/desiredSpeed));
            Add(k->v17c, velocity);
        }
    }
    brake = Saturate_Double(k->field2f4 * LUT_Cosine(lbl_806D974C*(k->field1e0/lbl_806D9770)+lbl_806D976C)+lbl_806D96D4, lbl_806D9768, lbl_806D96D4);
    if (k->field2fc == 1 || k->field2fd == 1) brake *= lbl_806D9774*Param(k, 0x18);
    else {
        Saturate_Double(lbl_806D9768+k->field1d8, lbl_806D96D0, lbl_806D96D4);
        brake *= lbl_806D977C*(Param(k, 0x18)*k->field1d8) + lbl_806D9778*(lbl_806D96D4-k->field1d8);
    }
    {
        InitVec velocity(k->v17c.x, k->v17c.y, k->v17c.z);
        Scale(velocity, 1.0f / 60.0f);
        float angle = SteeringMagnitude(lbl_806D9760*k->pad1c4);
        float speed = fn_8019EA08(&velocity);
        if (angle > lbl_806D96D0 && speed > lbl_806D96D0) {
            float delta = (float)(lbl_806D96F8*(float)asin(speed/(brake/LUT_Cosine((float)(lbl_806D96F0*angle)))));
            if (k->field2bd == 1 || k->v2a4.y > lbl_806D96D0) delta = lbl_806D96D0;
            if (k->v2a4.y > lbl_806D96D0) delta += Abs(lbl_806D9784*yawTurn);
            k->field1d0 = k->yaw;
            if (k->pad1c4 > lbl_806D96D0) { k->yaw += delta; k->field1cc = delta; }
            else { k->yaw -= delta; k->field1cc = -delta; }
        }
    }
    if (k->v2a4.y > lbl_806D96D0) {
        k->v2a4.y += lbl_806D9788;
        if (k->v2a4.y < lbl_806D96D0) k->v2a4.y = lbl_806D96D0;
        k->v194.y = lbl_806D96D0;
    } else {
        if (airborne != 4) k->field2bc = 0;
        if (k->field2bc == 1 && k->v298.y >= k->orientation.m[3][1]) k->field2bc = 0;
    }
    if (airborne != 0 && k->v2a4.y <= lbl_806D96D0) {
        k->v194.y += lbl_806D978C;
        float magnitude = Abs(k->v194.y);
        if (magnitude > k->field2d4) k->v194.y *= k->field2d4 / magnitude;
    }
    {
    float dx = k->v17c.x;
    dx = lbl_806D9780*(lbl_806D9790*dx+dx);
    float dz = k->v17c.z;
    dz = lbl_806D9780*(lbl_806D9790*dz+dz);
    float dy = k->v2a4.y+(k->v17c.y+k->v194.y);
    dy = lbl_806D9780*(lbl_806D9790*dy+dy);
    InitVec displacement(dx, dy, dz);
    ApplyDisplacement(k, displacement, lbl_806D973C+k->field2e0);
    Add(k->pos, k->v310);
    Add(k->pos, (Vec3 &)k->v1ac);
    }
    Copy(k->v188, k->v17c);
    Scale(k->v188, Param(k, 0x60));
    if (k->field2bd == 0) {
        InitVec velocity(k->v17c.x, k->v17c.y, k->v17c.z);
        velocity.y = lbl_806D96D0;
        fn_8019EA8C(&velocity);
        InitVec desired(k->v170.x, k->v170.y, k->v170.z);
        desired.y = lbl_806D96D0;
        fn_8019EA8C(&desired);
        float angle = fn_8019E9C0(&velocity, &desired);
        angle = Saturate_Double(angle, lbl_806D9794, lbl_806D96D4);
        angle = (float)(lbl_806D96F8*(float)asin(angle));
        angle = Saturate_Double(angle, -Param(k, 0x6c), Param(k, 0x6c));
        if (Abs(angle) > Param(k, 0x64)) {
            k->field2dc = 1;
            if (k->field2fc == 1 || k->field2fd == 1) {
                float a = angle*Param(k, 0x70);
                float b = (angle-lbl_806D9704*angle)*(yawTurn*Param(k, 0x74));
                k->yaw -= a + b;
            } else {
                float correction = angle*(Param(k, 0x7c)*(Param(k, 0x78)+Abs(turn)));
                k->yaw -= correction;
            }
        } else if (lbl_806D96D0 == k->pad1c4) {
            float correction = angle*Param(k, 0x68);
            k->yaw += correction;
        }
    }
    {
    InitVec scaled(k->v17c.x, k->v17c.y, k->v17c.z);
    Scale(scaled, lbl_806D9780);
    if (active == 1) { k->field18 = lbl_806D9798*(lbl_806D96D4-grip); k->field1c = lbl_806D96D4; }
    else { k->field18 = lbl_806D96D0; k->field1c = lbl_806D979C; }
    {
        InitVec velocity = k->v17c;
        velocity.y = lbl_806D96D0;
        fn_8019EA8C(&velocity);
        InitVec forward(k->orientation.m[2][0], k->orientation.m[2][1], k->orientation.m[2][2]);
        forward.y = lbl_806D96D0;
        fn_8019EA8C(&forward);
        float speed = fn_8019EA08(&k->v17c);
        float factor = Saturate_Double((lbl_806D96D4+Dot(velocity, forward))*lbl_806D9704+lbl_806D9768, lbl_806D9704, lbl_806D96D4);
        SpeedCurve_UpdateSpeedCap(&k->field08, (float)(lbl_806D97A0*(speed*factor)));
    }
    }
    k->field1e0 = KartMovement_CalcSpeedWithCoinBonus(k, 0);
    {
        InitVec forward(k->orientation.m[2][0], k->orientation.m[2][1], k->orientation.m[2][2]);
        float sign = Dot(k->v17c, forward) > lbl_806D96D0 ? lbl_806D96D4 : lbl_806D9794;
        float invX = lbl_806D96D4/Param(k, 0x88);
        float invY = lbl_806D96D4/Param(k, 0x8c);
        k->field1e4 += sign*(lbl_806D9780*(invX*fn_8019EA08(&k->v17c)));
        float rotation = k->field2d8*(invY*(k->field21 == 0 ? k->field10 : -k->field10));
        float minimum = invY*fn_8019EA08(&k->v17c);
        if (Abs(rotation) < Abs(minimum)) rotation = minimum;
        if (active == 1) k->field1e8 += lbl_806D9780*rotation;
    }
    fn_8019C6B4(k);
    k->field244 = 0; k->field245 = 0; k->field246 = 0;
    KartMovement_CollisionUpdate(k);
    fn_8019C15C(k);
    Clear(k->v1f8);
    fn_8019C078(k);
    fn_8019BF80(k);
    unsigned char collision = k->field244;
    k->field244 = 0;
    KartMovement_CollisionUpdate(k);
    k->field244 = collision;
    for (int i = 0; i < 16; ++i) ((float *)&k->previous)[i] = ((float *)&k->orientation)[i];
    float offset = lbl_806D96D0;
    offset *= lbl_806D97A8;
    k->previous.m[3][1] = k->previous.m[3][1] - offset;
    {
    InitVec delta(k->pos.x, k->pos.y, k->pos.z);
    ProjectSubtract(delta, k->v298);
    InitVec projected(k->v2b0.x, k->v2b0.y, k->v2b0.z);
    ProjectScale(projected, -Dot(delta, k->v2b0));
    ProjectAdd(projected, k->pos);
    Copy(k->v298, projected);
    }
    float lift = fn_8019EA08(&k->v2a4);
    if (lift > lbl_806D96D0) {
        InitVec normal(k->v2b0.x, k->v2b0.y, k->v2b0.z);
        Scale(normal, lbl_806D9740*lift);
        Add(k->v298, normal);
        float height;
        if (Terrain_GetGroundHeight(&k->v298, &height, 0, 0) == 1 && height > k->v298.y) k->v298.y = height;
    }
    for (int i = 0; i < 16; ++i) ((float *)&k->matrixD8)[i] = ((float *)&k->orientation)[i];
    Clear(k->v310);
}

/* JumpDistanceMode_HandlePhysics: per-frame kart input/physics for the
 * jump-distance challenge (C++, compiled with -lang=c++). Float literals
 * (0.0f, 360.0f) are remapped to the shared .sdata2 labels by
 * tools/postprocess_sdata2.py; the literal form is needed so CW reloads them
 * instead of keeping one register across the angle-wrap loops.
 */
struct Vec3 { float x, y, z; };
struct XZ { float x, z; };
struct Rect { float minX, minZ, maxX, maxZ; };

struct Pad {
    virtual void v0();
    virtual void v1();
    virtual float GetSteer();
    virtual void v3();
    virtual float GetBrake();
    virtual float GetAccel();
    virtual void v6();
    virtual void v7();
    virtual int GetButton(int mask);
};

struct KartMove { char pad[0x1c8]; float heading; };
struct CarObject { char pad[0x28]; KartMove *move; };
struct GoalPlane { Vec3 *point; Vec3 normal; };

struct JumpDistanceMode {
    void *vtbl;
    int x4;
    CarObject *car;
    int xC;
    int x10;
    void *x14;
    void *camera;
    void *x1C;
    char pad20[0x18];
    GoalPlane *goal;
    char pad3C[0x14];
    int state;
    char pad54[0x14];
    float speed;
    char pad6C[0x1C];
    unsigned char reached;
};

extern "C" {
extern unsigned char g_raceEnded;
extern int g_reverseRoundFlag;
extern unsigned char lbl_806D1290;
extern const float lbl_806DAD70, lbl_806DAD7C, lbl_806DAD84, lbl_806DAD88, lbl_806DAD8C;
extern const float lbl_806DADAC, lbl_806DADB0, lbl_806DADB4, lbl_806DADB8, lbl_806DADBC;
extern const float lbl_806DADC0, lbl_806DADC4, lbl_806DADC8, lbl_806DADCC, lbl_806DADD0;
extern const XZ lbl_806DCF68;
extern const Rect lbl_803C3D64;
extern const Vec3 lbl_803C3D80;

void *GetInputManager(void);
Pad *InputMgr_GetPlayer(void *mgr, int idx);
unsigned char IsRaceStarted(void);
unsigned char NokoNokoChallenge_HandleBrakeInput(JumpDistanceMode *self, int brake);
void CarObject_ApplyInput(CarObject *car, unsigned char started, float steer, float brake, float accel);
void CarObject_FrameUpdate(CarObject *car, int buttons);
void *CarObject_GetRenderObj(CarObject *car);
unsigned char Input_IsItemButtonPressed(void);
unsigned char RenderObj_UseItem(void *ro, int a, int b);
void CarObject_ApplyDriftBoost(CarObject *car, int kind, float amount);
void fn_8023E1E4(void *p, int a, int b);
void fn_801699D8(int a, int b);
void KartItem_UpdateShadowBillboardAndViewport(CarObject *car, void *view, int a);
float KartMovement_GetVelocityMagnitude(void *ro);
float *KartMovement_GetVelocityPtr(void *ro);
float *KartDriver_GetKartRootMtx(void *ro);
void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
float Vec3_Dot(const Vec3 *a, const Vec3 *b);
void ChallengeGoalCamera_Update(void *cam, void *view, float *mtx);
}

static inline float WrapAngle(float a) {
    while (a >= 360.0f) {
        a -= 360.0f;
    }
    while (a < 0.0f) {
        a += 360.0f;
    }
    return a;
}

static inline unsigned char IsInFront(GoalPlane *goal, float *mtx) {
    Vec3 pos = lbl_803C3D80;
    Vec3 d;

    pos.x = mtx[3];
    pos.z = mtx[11];
    Vec3_Subtract(&pos, goal->point, &d);
    return Vec3_Dot(&d, &goal->normal) > lbl_806DAD7C ? 1 : 0;
}

static inline unsigned char InRect(const Rect *r, const XZ &p) {
    if (p.x < r->minX) {
        return 0;
    }
    if (p.x > r->maxX) {
        return 0;
    }
    if (p.z < r->minZ) {
        return 0;
    }
    if (p.z > r->maxZ) {
        return 0;
    }
    return 1;
}

extern "C" void JumpDistanceMode_HandlePhysics(JumpDistanceMode *self) {
    int braking;
    int buttons;
    GoalPlane *goal;
    Pad *pad;
    float steer;
    float accel;
    float brake;
    float goalSteer;
    float *mtx;

    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_raceEnded != 1 && self->state < 1) {
        steer = pad->GetSteer();
        accel = pad->GetAccel();
        if (lbl_806D1290 == 0) {
            brake = pad->GetBrake();
        } else {
            brake = lbl_806DADAC;
        }
        braking = 0;
        if (brake < lbl_806DAD88 && accel < lbl_806DAD88 && IsRaceStarted()) {
            braking = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(self, braking) == 1) {
            brake = lbl_806DAD70;
        }
        CarObject_ApplyInput(self->car, IsRaceStarted(), steer, brake, accel);
        buttons = 0;
        if (IsRaceStarted() == 1) {
            buttons = pad->GetButton(0xE7FF);
            pad->GetButton(0xE3FF);
            if (Input_IsItemButtonPressed() && RenderObj_UseItem(CarObject_GetRenderObj(self->car), 0, 0)) {
                CarObject_ApplyDriftBoost(self->car, 5, lbl_806DADB0);
                fn_8023E1E4(self->x1C, -1, 0);
                fn_801699D8(0, 0);
                fn_801699D8(1, 0);
            }
        }
        CarObject_FrameUpdate(self->car, buttons);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->x14, 0);
    } else if (self->state == 1 || self->state == 2) {
        CarObject_ApplyInput(self->car, 1, lbl_806DAD7C, lbl_806DAD7C, lbl_806DAD7C);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->x14, 0);
    } else if (self->state == 3) {
        float heading;

        if (KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car)) > self->speed) {
            self->speed = KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car));
        }
        steer = 0.0f;
        heading = self->car->move->heading;
        heading = WrapAngle(heading);
        if (g_reverseRoundFlag == 0) {
            if (heading <= lbl_806DADB8) {
                steer = lbl_806DADBC;
            } else if (heading >= lbl_806DADC0) {
                steer = lbl_806DAD8C;
            }
        } else {
            if (heading <= lbl_806DADC4 && heading >= lbl_806DADC8) {
                steer = lbl_806DADBC;
            } else if (heading >= lbl_806DAD84) {
                steer = lbl_806DAD8C;
            }
        }
        CarObject_ApplyInput(self->car, 1, steer, self->speed, lbl_806DAD7C);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->x14, 0);
        if (self->speed < lbl_806DADAC) {
            self->speed += lbl_806DADCC;
        }
    } else if (self->state == 4) {
        void *ro;

        goalSteer = 0.0f;
        ro = CarObject_GetRenderObj(self->car);
        goal = self->goal;
        if (IsInFront(goal, KartDriver_GetKartRootMtx(ro)) == 1) {
            if (g_reverseRoundFlag == 0) {
                goalSteer = 0.0f;
                if (KartMovement_GetVelocityPtr(CarObject_GetRenderObj(self->car))[2] > 0.0f) {
                    goalSteer = 0.0f;
                }
            } else {
                goalSteer = lbl_806DADD0;
                if (KartMovement_GetVelocityPtr(CarObject_GetRenderObj(self->car))[2] < 0.0f) {
                    goalSteer = 0.0f;
                }
            }
        }
        CarObject_ApplyInput(self->car, 1, goalSteer, self->speed > lbl_806DADAC ? lbl_806DADAC : self->speed, lbl_806DAD7C);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->x14, 0);
        if (self->speed > lbl_806DAD7C) {
            self->speed -= lbl_806DADCC;
        }
    } else {
        CarObject_ApplyInput(self->car, 1, lbl_806DAD7C, lbl_806DAD7C, lbl_806DAD7C);
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->camera, self->x14, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    {
        XZ p = lbl_806DCF68;

        p.x = mtx[3];
        p.z = mtx[11];
        if (InRect(&lbl_803C3D64, p) == 1) {
            self->reached = 1;
        }
    }
}

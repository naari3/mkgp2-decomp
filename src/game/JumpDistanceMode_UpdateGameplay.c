/* JumpDistanceMode_UpdateGameplay: jump-distance challenge state machine
 * (approach, takeoff, flight distance, landing, stop). C++ (-lang=c++).
 * Float literals in JD_sqrtf are remapped to the shared .sdata2 labels by
 * tools/postprocess_sdata2.py.
 */
struct Vec3 { float x, y, z; };
struct XZ { float x, z; };
struct Rect { float minX, minZ, maxX, maxZ; };

struct CarObject;
struct GoalPlane { Vec3 *point; Vec3 normal; };
struct JDLanding { unsigned char active; unsigned char slowed; char pad2[2]; int x4; int x8; };
struct JDCoins { char pad[8]; int base; int earned; };

struct JDMode {
    void *vtbl;
    int x4;
    CarObject *car;
    char padC[0x20];
    int *display;
    GoalPlane *goal;
    GoalPlane *goal2;
    int x38;
    JDLanding *landing;
    int *camState;
    unsigned char active;
    unsigned char reached;
    char pad46[2];
    int endDelay;
    int x4C;
    int state;
    float target;
    float distance;
    Vec3 last;
    float speed;
    char pad6C[8];
    float x74;
    int x78;
    JDCoins *coins;
    int coinIdx;
    int coinCount;
    unsigned char pastGoal;
};

extern "C" {
extern unsigned char g_raceEnded;
extern const float lbl_806DAD74, lbl_806DAD7C, lbl_806DADA0, lbl_806DADA4, lbl_806DADA8, lbl_806DADAC;
extern const XZ lbl_806DCF60;
extern const Rect lbl_803C3D54;
extern const Vec3 lbl_803C3D80;

unsigned char CarObject_IsAirborne(CarObject *car);
void *CarObject_GetRenderObj(CarObject *car);
float KartMovement_GetVelocityMagnitude(void *ro);
float *KartMovement_GetVelocityPtr(void *ro);
float *KartDriver_GetKartRootMtx(void *ro);
void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
float Vec3_Dot(const void *a, const Vec3 *b);
unsigned char Terrain_GetGroundHeight(Vec3 *pos, float *height, int a, int b);
unsigned char fn_8016C360(int id);
void SoundMgr_PlaySE(int id);
void fn_8016C1F8(int id, float v);
void JumpDistanceMode_PredictLanding(JDMode *self);
struct CoinStep { int threshold; int coins; };
struct CoinTable { CoinStep *steps; };
CoinTable *NokoNokoChallenge_GetCoinDivisor(void);
unsigned char IsCardValid(void);
}

static inline float JD_sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
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

static inline unsigned char InStartZone(float *mtx) {
    XZ p = lbl_806DCF60;

    p.x = mtx[3];
    p.z = mtx[11];
    return InRect(&lbl_803C3D54, p);
}

static inline unsigned char IsLeaving(JDMode *self) {
    void *ro = CarObject_GetRenderObj(self->car);
    GoalPlane *goal = self->goal;

    return InStartZone(KartDriver_GetKartRootMtx(ro)) == 0 ? 1 : (Vec3_Dot(KartMovement_GetVelocityPtr(ro), &goal->normal) < lbl_806DAD7C ? 1 : 0);
}

static inline void CheckTakeoff(JDMode *self) {
    void *ro;
    GoalPlane *goal;

    if (self->pastGoal == 0) {
        ro = CarObject_GetRenderObj(self->car);
        goal = self->goal;
        if (IsInFront(goal, KartDriver_GetKartRootMtx(ro)) == 1) {
            if (InStartZone(KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car))) == 1) {
                self->speed = KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car));
                JumpDistanceMode_PredictLanding(self);
                *self->camState = 2;
                self->state = 2;
            }
        }
    }
}

static inline float DistXZ(const Vec3 *a, const Vec3 *b) {
    return JD_sqrtf((a->x - b->x) * (a->x - b->x) + (a->z - b->z) * (a->z - b->z));
}

static inline unsigned char AddDistance(JDMode *self) {
    float *mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    Vec3 pos;
    float len;
    int shown;
    int *display;
    CoinTable *tbl;

    pos.x = mtx[3];
    pos.y = mtx[7];
    pos.z = mtx[11];
    len = DistXZ(&pos, &self->last);
    self->distance += lbl_806DADA0 * len / lbl_806DADA4;
    self->last = pos;
    display = self->display;
    shown = (int)self->distance;
    if (*display != shown) {
        SoundMgr_PlaySE(0x1B);
    }
    *display = shown;
    tbl = NokoNokoChallenge_GetCoinDivisor();
    if ((int)self->distance >= tbl->steps[self->coinIdx].threshold && tbl->steps[self->coinIdx].coins > 0) {
        self->coinCount = tbl->steps[self->coinIdx].coins;
        self->coins->earned = self->coinCount - self->coins->base;
        self->coinIdx++;
        return 1;
    }
    return 0;
}

extern "C" void JumpDistanceMode_UpdateGameplay(JDMode *self) {
    switch (self->state) {
    case 0:
        if (CarObject_IsAirborne(self->car) == 1) {
            if (IsLeaving(self) != 1) {
                float *mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
                Vec3 pos;
                float ground;

                pos.x = mtx[3];
                pos.y = mtx[7];
                pos.z = mtx[11];
                ground = lbl_806DAD7C;
                Terrain_GetGroundHeight(&pos, &ground, 0, 0);
                if (pos.y - ground >= lbl_806DADA8) {
                    JDLanding *landing;

                    self->last = pos;
                    landing = self->landing;
                    if (fn_8016C360(0x42) == 0) {
                        SoundMgr_PlaySE(0x42);
                        fn_8016C1F8(0x42, lbl_806DADAC);
                    }
                    landing->active = 1;
                    landing->x4 = landing->x8;
                    *self->camState = 1;
                    self->state = 1;
                    self->x74 = lbl_806DAD74;
                }
            }
        } else {
            {
            void *ro;
            GoalPlane *goal;
        
            if (self->pastGoal == 0) {
                ro = CarObject_GetRenderObj(self->car);
                goal = self->goal;
                if (IsInFront(goal, KartDriver_GetKartRootMtx(ro)) == 1) {
                    if (InStartZone(KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car))) == 1) {
                        self->speed = KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car));
                        JumpDistanceMode_PredictLanding(self);
                        *self->camState = 2;
                        self->state = 2;
                    }
                }
            }
                }
        }
        break;
    case 1:
        AddDistance(self);
        self->x74 += lbl_806DAD74;
        if (self->landing->slowed == 0) {
            *self->camState = 0;
            self->x74 = lbl_806DAD7C;
            self->state = 0;
        }
        {
    void *ro;
    GoalPlane *goal;

    if (self->pastGoal == 0) {
        ro = CarObject_GetRenderObj(self->car);
        goal = self->goal;
        if (IsInFront(goal, KartDriver_GetKartRootMtx(ro)) == 1) {
            if (InStartZone(KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car))) == 1) {
                self->speed = KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car));
                JumpDistanceMode_PredictLanding(self);
                *self->camState = 2;
                self->state = 2;
            }
        }
    }
        }
        break;
    case 2:
        if (CarObject_IsAirborne(self->car) == 0) {
            self->state = 3;
            *self->camState = 4;
            break;
        }
        AddDistance(self);
        break;
    case 3: {
        void *ro = CarObject_GetRenderObj(self->car);
        GoalPlane *goal = self->goal2;

        if (IsInFront(goal, KartDriver_GetKartRootMtx(ro)) == 1) {
            self->state = 4;
        }
        break;
    }
    case 4:
        if (lbl_806DAD7C == KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(self->car))) {
            *self->camState = 0;
            g_raceEnded = 1;
            self->reached = 1;
            if (IsCardValid() == 0) {
                self->reached = self->target < self->distance;
            }
            self->endDelay = 30;
            self->state = 5;
        }
        break;
    case 5:
        break;
    }
}

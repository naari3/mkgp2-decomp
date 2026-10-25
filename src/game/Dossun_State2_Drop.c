/* Dossun_State2_Drop (0x800ED010): drop state of the Dossun (Thwomp)
 * item. Sub-state 0 finds the ground under the item, sub-state 1 waits
 * until the item has fallen to it, sub-state 2 arms the landing timer and
 * fades the item out once it runs down. The kind (0xCB) picks the spin and
 * the drift of the falling item. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct DossunWork {
    unsigned char pad0[4];
    unsigned int timers[4];
    float groundY;
    float spinDir;
} DossunWork;

extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern float Vec3_ToYaw(const Vec *v);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern float AngleStepTowards_Shortest(float cur, float target, float step);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))

void Dossun_State2_Drop(unsigned char *self, DossunWork *w)
{
    switch (S8(0xC9)) {
    case 0:
        if (*(char *)(self + 0xCB) != 9) {
            ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &w->groundY, 0);
        } else {
            w->groundY = F(0xA4) - 60.0f;
        }
        self[0xC9]++;
    case 1:
        switch (S8(0xCB)) {
        case 4:
            self[0xC9]++;
            self[0xCA] = 0;
            break;
        case 9:
            if (F(0xA4) < w->groundY) {
                self[0xC9]++;
                self[0xCA] = 0;
            }
            break;
        case 0:
        case 5:
            if (60.0f + w->groundY < F(0xA4)) {
                self[0xC9]++;
                self[0xCA] = 0;
            }
            break;
        }
        break;
    case 2:
        switch (S8(0xCA)) {
        case 0:
            if (*(char *)(self + 0xCB) == 4) {
                if (1.570796f < FAbs_FloatAsDouble(BuildOrientationFromYaw(Vec3_ToYaw((Vec *)(self + 0xB8)) - F(0xB0)))) {
                    w->spinDir = -1.0f;
                } else {
                    w->spinDir = 1.0f;
                }
            }
            switch (S8(0xCB)) {
            case 4:
                w->timers[0] = 10;
                break;
            case 9:
                w->timers[0] = 0;
                break;
            case 0:
                w->timers[0] = 0;
                break;
            case 5:
                w->timers[0] = 0;
                break;
            }
            self[0xCA]++;
            break;
        case 1:
            break;
        }
        if (w->timers[0] == 0) {
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        break;
    }
    Item_DecayVelocityScalar(self, 5.0f);
    switch (S8(0xCB)) {
    case 4:
        F(0xBC) += -0.1f;
        break;
    case 9:
        F(0xBC) += -0.5f;
        break;
    case 0:
        F(0xBC) += 0.1f;
        break;
    case 5:
        F(0xBC) += 0.1f;
        break;
    }
    switch (S8(0xCB)) {
    case 4:
        F(0xAC) = BuildOrientationFromYaw(0.034906577f * w->spinDir + F(0xAC));
        break;
    case 9:
        F(0xAC) = AngleStepTowards_Shortest(F(0xAC), 0.0f, 0.017453289f);
        break;
    case 0:
        F(0xAC) = AngleStepTowards_Shortest(F(0xAC), 0.0f, 0.017453289f);
        break;
    case 5:
        F(0xAC) = AngleStepTowards_Shortest(F(0xAC), 0.0f, 0.017453289f);
        break;
    }
    F(0xB4) = AngleStepTowards_Shortest(F(0xB4), 0.0f, 0.017453289f);
}

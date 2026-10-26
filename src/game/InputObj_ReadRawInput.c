/* InputObj_ReadRawInput @ 0x800391B4..0x8003951C: converts the JVS analog
 * channels and switch bits of one player into the InputObj axes and button
 * masks.
 *
 * NonMatching: the unrolled button-map loop. The target walks the table
 * with one pointer (lwz 0 / lwzu 8) and loads the buttons address first;
 * every indexed, pointer, inline and do/while form tried peels the first
 * iteration into a separate base register. The rest matches. */

typedef struct InputObj {
    void *vtbl;
    int port;
    unsigned int pressedMask; /* 0x08 */
    unsigned int heldMask;    /* 0x0C */
    unsigned int prevMask;    /* 0x10 */
    int repeatA;              /* 0x14 */
    int repeatB;              /* 0x18 */
    float steering;           /* 0x1C */
    float accelerator;        /* 0x20 */
    float brake;              /* 0x24 */
} InputObj;

typedef struct RawButtonMap {
    unsigned int mask;
    unsigned int bit;
} RawButtonMap;

extern unsigned short g_jvsOperatorBits[16];
extern unsigned short g_jvsPlayerButtons[16];
extern RawButtonMap kRawGameMap_Raw0[5];
extern unsigned char lbl_80598A60[];
extern int g_steeringMaxRange;
extern int g_steeringCenterRaw;
extern int g_accelCenterRaw;
extern int g_accelRange;
extern int g_brakeCenterRaw;
extern int g_brakeRange;

void InputObj_ReadRawInput(InputObj *self)
{
    unsigned int bits;
    unsigned short op;
    int d;
    int i;
    float v;
    unsigned int prev;

    v = 0.0f;
    d = g_jvsOperatorBits[4] - g_steeringCenterRaw;
    if (d != 0) {
        v = (float)d / (float)g_steeringMaxRange;
    }
    if (v > 1.0f) {
        v = 1.0f;
    } else if (v < -1.0f) {
        v = -1.0f;
    }
    self->steering = v;

    v = 0.0f;
    d = g_jvsOperatorBits[5] - g_accelCenterRaw;
    if (d != 0) {
        v = (float)d / (float)g_accelRange;
    }
    if (v < 0.0f) {
        v = 0.0f;
    } else if (v > 1.0f) {
        v = 1.0f;
    }
    self->accelerator = v;

    v = 0.0f;
    d = g_jvsOperatorBits[6] - g_brakeCenterRaw;
    if (d != 0) {
        v = (float)d / (float)g_brakeRange;
    }
    if (v < 0.0f) {
        v = 0.0f;
    } else if (v > 1.0f) {
        v = 1.0f;
    }
    self->brake = v;

    bits = 0;
    prev = g_jvsPlayerButtons[self->port * 4];
    for (i = 0; i < 5; i++) {
        if (prev & kRawGameMap_Raw0[i].mask) {
            bits |= kRawGameMap_Raw0[i].bit;
        }
    }

    if (lbl_80598A60[0x44] == 1) {
        if (self->prevMask & 0x4000) {
            self->repeatA = 0x12;
        } else if (self->repeatA != 0) {
            self->repeatA--;
            if (bits & 0x4000) {
                bits &= ~0x4000;
            }
        }
    } else {
        bits &= ~0x4000;
    }

    if (lbl_80598A60[0x45] == 1) {
        if (self->prevMask & 0x8000) {
            self->repeatB = 0x12;
        } else if (self->repeatB != 0) {
            self->repeatB--;
            if (bits & 0x8000) {
                bits &= ~0x8000;
            }
        }
    } else {
        bits &= ~0x8000;
    }

    if (self->brake > 0.7f && (bits & 1)) {
        bits |= 0x80;
        bits &= ~1;
    }
    op = g_jvsOperatorBits[0];
    if (op & 0x4080) {
        bits |= 0x1000;
    }
    if ((op & 0x8000) || (g_jvsPlayerButtons[self->port * 4] & 0x40)) {
        bits |= 0x800;
    }
    if (self->accelerator > 0.7f) {
        bits |= 0x100;
    }
    if (self->brake > 0.7f) {
        bits |= 0x200;
    }
    if (self->steering > 0.6f) {
        bits |= 0x20;
    } else if (self->steering < -0.6f) {
        bits |= 0x10;
    }
    prev = self->prevMask;
    self->prevMask = bits;
    self->pressedMask = bits & (bits ^ prev);
    self->heldMask = bits;
}

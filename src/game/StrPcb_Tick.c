/*
 * StrPcb serial protocol ticks, 0x80036E7C..0x80037AB0:
 * StrPcb_StateTick, StrPcb_ParseResponse, StrPcb_InputTick,
 * StrPcb_OutputTick, StrPcb_TimerTick.
 */
#include "game/StrPcb.h"

typedef struct StrPcbChanStatus {
    int word0;
    int word4;
    int word8;
    int errorCount;
} StrPcbChanStatus;

extern u8 lbl_806D1000[3];
extern int lbl_806D1004;
extern int lbl_806D0FF8;
extern int lbl_806D0FFC;
extern unsigned int lbl_806D1008;
extern u8 lbl_80598500[0xC];
extern u8 lbl_8059850C[0x24];
extern const char lbl_802E9854[];
extern const char lbl_802E9874[];
extern const float lbl_806D23D8;
extern const float lbl_806D23E4;
extern const float lbl_806D23E8;
extern const float lbl_806D23F8;
extern const float lbl_806D23FC;

extern void *fn_8028B0B4(void);
extern void fn_8028B0D8(void *chan, StrPcbChanStatus *status);
extern int fn_8028A598(void *chan, int count, u8 *data);
extern int fn_80276C50(char *buf, const char *fmt, ...);
extern int fn_80293290(int chan, int *count);
extern u8 fn_8029321C(int chan);
extern int fn_80293338(int chan, u8 data);
extern int fn_80038798(int value, int min, int max);
extern float Saturate_Double(float value, float min, float max);
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void *memmove(void *dst, const void *src, unsigned long n);

#define OS_BUS_CLOCK (*(unsigned int *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))

static inline void StrPcb_SetCommError(StrPcbCmd *pcb)
{
    pcb->stickyError5C = 1;
    pcb->state20 = 4;
}

static inline void StrPcb_SetCommand2F(StrPcbCmd *pcb, u8 value)
{
    pcb->dirty18 = 1;
    pcb->command2F = value;
}

static inline void StrPcb_SendPacket(StrPcbCmd *pcb, u8 *data, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        if (fn_80293338(0, data[i]) != 0) {
            StrPcb_SetCommError(pcb);
            break;
        }
    }
}

static inline u8 StrPcb_IsIdle(StrPcbCmd *pcb)
{
    return pcb->state20 == 0;
}

static inline u8 StrPcb_IsRunning(StrPcbCmd *pcb)
{
    return pcb->state20 == 1;
}

static inline u8 StrPcb_ResponseTimedOut(void)
{
    if ((float)OSTicksToMicroseconds(OSGetTick() - lbl_806D100C) / lbl_806D23E4 >= lbl_806D23E8) {
        return 1;
    }
    return 0;
}

#pragma exceptions on
void StrPcb_StateTick(StrPcbCmd *pcb)
{
    StrPcbChanStatus status;
    void *chan;

    if (pcb->state20 == 4) {
        pcb->status24 &= 0x7F;
    }
    if (pcb->state60 == 1) {
        pcb->effectTimer64 = lbl_806D23D8;
        pcb->state60 = 2;
    } else if (pcb->state60 == 2) {
        pcb->effectTimer64 -= lbl_806D23DC;
        if (pcb->effectTimer64 <= lbl_806D23E0) {
            pcb->state60 = 3;
            pcb->effectTimer64 = lbl_806D23D8;
            pcb->status24 |= pcb->effectId;
        }
    } else if (pcb->state60 == 3) {
        pcb->effectTimer64 -= lbl_806D23DC;
        if (pcb->effectTimer64 <= lbl_806D23E0) {
            pcb->state60 = 4;
        }
    }
    if (pcb->intensityMode == 0) {
        pcb->status24 &= 0x7F;
    }
    pcb->statusSent25 = pcb->status24;
    chan = fn_8028B0B4();
    fn_8028B0D8(chan, &status);
    if (fn_8028A598(chan, 1, &pcb->status24) != 0 || status.errorCount >= 10) {
        pcb->commError26 = 1;
        pcb->stickyError5C = 1;
        pcb->state20 = 4;
        lbl_806D1000[0] = 'E';
        lbl_806D1000[1] = '2';
        lbl_806D1000[2] = '0';
        memcpy(pcb->errorCode, lbl_806D1000, 3);
    }
}

u8 StrPcb_ParseResponse(StrPcbCmd *pcb, u8 *__restrict resp)
{
    char badCMsg[0x100];
    char errorMsg[0x100];
    char badE0Msg[0x100];
    char badE1Msg[0x100];
    char badE2Msg[0x100];
    char unknownMsg[0x100];

    if (pcb->intensityMode == 0) {
        pcb->receivedPosData = 0x1FF;
        return 1;
    }
    if ((int)resp[0] == 'C') {
        if ((int)resp[1] == '0' && (int)resp[2] == '1') {
            pcb->state20 = 0;
            pcb->position10 = 0x1FF;
            pcb->position28 = 0x1FF;
            return 1;
        }
        if ((int)resp[1] == '0' && (int)resp[2] == '6') {
            pcb->state20 = 1;
            pcb->position10 = 0x1FF;
            pcb->position28 = 0x1FF;
            return 1;
        }
        fn_80276C50(badCMsg, lbl_802E9854, resp[0], resp[1], resp[2]);
        return 0;
    }
    if ((int)resp[0] == 'E') {
        fn_80276C50(errorMsg, lbl_802E9874, resp[0], resp[1], resp[2]);
        if ((int)resp[1] != '0' || (int)resp[2] != '0') {
            int i;
            for (i = 0; i < 3; i++) {
                pcb->errorCode[i] = resp[i];
            }
        }
        if ((int)resp[1] == '0') {
            switch ((int)resp[2]) {
            case '0':
                pcb->state20 = 0;
                pcb->position10 = 0x1FF;
                pcb->position28 = 0x1FF;
                break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '7':
            case '8':
                StrPcb_SetCommError(pcb);
                break;
            case '1':
            case '6':
            default:
                fn_80276C50(badE0Msg, lbl_802E9854, resp[0], resp[1], resp[2]);
                StrPcb_SetCommError(pcb);
                return 0;
            }
            return 1;
        }
        if ((int)resp[1] == '1') {
            switch ((int)resp[2]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
                StrPcb_SetCommError(pcb);
                break;
            default:
                fn_80276C50(badE1Msg, lbl_802E9854, resp[0], resp[1], resp[2]);
                StrPcb_SetCommError(pcb);
                return 0;
            }
            return 1;
        }
        if ((int)resp[1] == '2') {
            switch ((int)resp[2]) {
            case '0':
                StrPcb_SetCommError(pcb);
                break;
            default:
                fn_80276C50(badE2Msg, lbl_802E9854, resp[0], resp[1], resp[2]);
                StrPcb_SetCommError(pcb);
                return 0;
            }
            return 1;
        }
        return 0;
    }
    if ((int)resp[0] == 'H') {
        pcb->receivedPosData = (resp[1] << 8) | resp[2];
        pcb->positionAck27 = 1;
        return 1;
    }
    fn_80276C50(unknownMsg, lbl_802E9854, resp[0], resp[1], resp[2]);
    return 0;
}

#pragma auto_inline off
void StrPcb_InputTick(StrPcbCmd *pcb)
{
    int count;

    if (pcb->state20 == 4) {
        return;
    }
    lbl_806D0FFC = lbl_806D0FF8;
    if (fn_80293290(0, &count) == 0) {
        if (count > 0) {
            while (count-- > 0) {
                u8 c = fn_8029321C(0);

                lbl_806D1000[lbl_806D1004++] = lbl_8059850C[lbl_806D0FF8++] = c;
                if (lbl_806D1004 >= 3) {
                    if (StrPcb_ParseResponse(pcb, lbl_806D1000) == 1) {
                        lbl_806D1004 = 0;
                        lbl_806D100C = OSGetTick();
                    } else {
                        memmove(lbl_806D1000, lbl_806D1000 + 1, 2);
                        if (pcb->intensityMode == 0) {
                            lbl_806D1000[0] = 'H';
                            lbl_806D1000[1] = '0';
                            lbl_806D1000[2] = '0';
                        }
                        lbl_806D1004--;
                    }
                }
                if (lbl_806D0FF8 >= 0x24) {
                    lbl_806D0FF8 = 0;
                }
            }
        } else if (count < 0) {
            StrPcb_SetCommError(pcb);
        }
    } else {
        StrPcb_SetCommError(pcb);
    }
    if (StrPcb_ResponseTimedOut() == 1) {
        StrPcb_SetCommError(pcb);
    }
}

#pragma auto_inline reset

void StrPcb_OutputTick(StrPcbCmd *pcb)
{
    int i;
    int delta;

    if (pcb->state20 == 4 || pcb->stickyError5C == 1) {
        StrPcb_StateTick(pcb);
        return;
    }
    if (pcb->positionAck27 == 0) {
        pcb->position10 = pcb->position28;
    } else {
        pcb->position28 = pcb->position10;
    }
    pcb->positionAck27 = 0;
    lbl_806D1008 = OSGetTick();
    delta = fn_80038798(pcb->positionTarget + pcb->counter14, 0, 0x3FF);
    delta = fn_80038798(delta - pcb->position10, lbl_806D23F8 * pcb->value48, lbl_806D23FC * pcb->value48);
    if (pcb->state20 == 1) {
        delta = 0;
    }
    pcb->position10 += delta;
    lbl_80598500[2] = pcb->position10;
    lbl_80598500[3] = (pcb->position10 >> 8) & 0x3F;
    if (pcb->value34 > 0) {
        pcb->value34--;
        if (pcb->value34 % pcb->value38 == 0) {
            pcb->timer30 = -pcb->timer30;
        }
        StrPcb_SetCommand2F(pcb, pcb->timer30);
        pcb->value40 = 0;
        if (pcb->value34 <= 0) {
            StrPcb_SetCommand2F(pcb, 0);
        }
    } else if (pcb->value40 > 0) {
        pcb->value40--;
        StrPcb_SetCommand2F(pcb, pcb->timer3C);
        if (pcb->value40 <= 0) {
            StrPcb_SetCommand2F(pcb, 0);
        }
    }
    if (pcb->state20 == 0) {
        pcb->value48 += pcb->value4C;
        if (pcb->value4C < 0.0f && pcb->value48 <= 0.0f) {
            pcb->status24 &= 0x7F;
            pcb->state20 = 3;
        }
    }
    if (pcb->state20 == 1) {
        pcb->status24 &= 0x7F;
    }
    pcb->value48 = Saturate_Double(pcb->value48, lbl_806D23E0, lbl_806D2400);
    lbl_80598500[4] = pcb->intensityScale * (pcb->command2D * pcb->value48);
    if (pcb->intensityScale <= lbl_806D23E0) {
        lbl_80598500[6] = 0;
    } else {
        lbl_80598500[6] = pcb->command2E * pcb->value48;
    }
    lbl_80598500[8] = pcb->intensityScale * ((signed char)pcb->command2F * pcb->value48);
    StrPcb_StateTick(pcb);
    if (pcb->state20 != 4 && pcb->dirty18 != 0) {
        StrPcb_SendPacket(pcb, lbl_80598500, 10);
    }
    if (pcb->intensityMode != 0) {
        StrPcb_InputTick(pcb);
    }
}

int StrPcb_TimerTick(StrPcbCmd *pcb)
{
    if (pcb->intensityMode == 0) {
        return 1;
    }
    if (pcb->value54-- <= 0) {
        pcb->state20 = 4;
        pcb->stickyError5C = 1;
        return 2;
    }
    if (pcb->value50 == 0) {
        if (pcb->value54 % 60 == 1) {
            StrPcb_ForceRun(pcb);
        } else if (StrPcb_IsIdle(pcb) == 1) {
            pcb->value50 = 1;
            pcb->value54 = 3600;
            StrPcb_ResetNeutralDefault(pcb);
        }
    } else {
        if (pcb->value54 % 60 == 0 && StrPcb_IsIdle(pcb) == 1) {
            StrPcb_ResetNeutralDefault(pcb);
        }
        if (StrPcb_IsRunning(pcb) == 1) {
            return 1;
        }
    }
    return 0;
}
#pragma exceptions reset

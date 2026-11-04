#include "game/SpriteVoicePrivate.h"
extern unsigned char VoiceQueue_Push(short, short, unsigned char, unsigned char);
extern int g_currentVoiceStreamHandle, g_goalFanfarePlayerIndex;
extern unsigned int g_voiceTickCounter;
extern signed char lbl_806D17B4;
extern int lbl_806D17C0;
/* Each timestamp spans its named high word and the adjacent low word. */
extern OSTime lbl_806D17E0, lbl_806D17E8;
extern const float lbl_806D9804, lbl_806D9814, lbl_806D9818;
extern short lbl_80496C38[14], lbl_80496C8C[52];

static inline short SelectEvent(int character, int id) {
    short *normal = lbl_80496C38;
    short *special = lbl_80496C8C;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

void fn_801A5DC0(void) {
    unsigned char pushed = 0;
    OSTime now = OSGetTime();
    int i;
    signed char phase;
    int next, distance;
    if (g_currentVoiceStreamHandle == -1) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].active && g_raceEntryArray[i].state == 3) {
                if (g_voiceTickCounter % 3 == 0) pushed = VoiceQueue_Push(0x188, -1, 0, 1);
                else if (g_voiceTickCounter % 3 == 1) pushed = VoiceQueue_Push(0x223, -1, 0, 1);
                else pushed = VoiceQueue_Push(0x224, -1, 0, 1);
                break;
            }
        }
    }
    if (!pushed && g_currentVoiceStreamHandle == -1) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].active && g_raceEntryArray[i].present) {
                if (g_raceEntryArray[g_goalFanfarePlayerIndex].kind == 0x24)
                    pushed = VoiceQueue_Push(0x228, -1, 0, 1);
                if (g_raceEntryArray[g_goalFanfarePlayerIndex].rank == 1)
                    pushed = VoiceQueue_Push(0x225, -1, 0, 1);
                if (g_raceEntryArray[g_goalFanfarePlayerIndex].rank == 2)
                    pushed = VoiceQueue_Push(0x226, -1, 0, 1);
                if (g_raceEntryArray[g_goalFanfarePlayerIndex].rank == 3)
                    pushed = VoiceQueue_Push(0x227, -1, 0, 1);
                break;
            }
        }
    }
    if (!pushed && g_currentVoiceStreamHandle == -1) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].active && g_raceEntryArray[i].state == 5) {
                if (g_voiceTickCounter % 2 == 0) pushed = VoiceQueue_Push(0x229, -1, 0, 1);
                else pushed = VoiceQueue_Push(0x22A, -1, 0, 1);
                break;
            }
        }
    }
    phase = lbl_806D17B4;
    if (phase == 0 || phase == 1) {
        if (lbl_806D17C0 != g_raceEntryArray[g_goalFanfarePlayerIndex].player) {
            if ((float)OSTicksToMilliseconds(now - lbl_806D17E0) / lbl_806D9804 >= lbl_806D9814) {
                if (!pushed && g_currentVoiceStreamHandle == -1) {
                    if (phase == 0) {
                        if (g_voiceTickCounter % 2 == 0) pushed = VoiceQueue_Push(0x22B, -1, 0, 1);
                        else pushed = VoiceQueue_Push(0x22C, -1, 0, 1);
                    } else {
                        if (g_voiceTickCounter % 3 == 0) pushed = VoiceQueue_Push(0x22D, -1, 0, 1);
                        else if (g_voiceTickCounter % 3 == 1) pushed = VoiceQueue_Push(0x22E, -1, 0, 1);
                        else pushed = VoiceQueue_Push(0x22F, -1, 0, 1);
                    }
                }
                lbl_806D17B4++;
                lbl_806D17E0 = now;
                lbl_806D17C0 = g_raceEntryArray[g_goalFanfarePlayerIndex].player;
            }
        } else if (phase == 0) {
            lbl_806D17E0 = now;
        }
    }
    if (!pushed && g_currentVoiceStreamHandle == -1) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].active && g_raceEntryArray[i].f60) {
                if (g_voiceTickCounter % 3 == 0) pushed = VoiceQueue_Push(0x230, -1, 0, 1);
                else if (g_voiceTickCounter % 3 == 1) pushed = VoiceQueue_Push(0x231, -1, 0, 1);
                else pushed = VoiceQueue_Push(0x232, -1, 0, 1);
                break;
            }
        }
    }
    if (!pushed && g_currentVoiceStreamHandle == -1) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].active && g_raceEntryArray[i].f64) {
                VoiceQueue_Push(SelectEvent(g_raceEntryArray[i].character, g_raceEntryArray[i].id), -1, 0, 1);
                if (g_voiceTickCounter % 2 == 0) pushed = VoiceQueue_Push(0x233, -1, 0, 1);
                else pushed = VoiceQueue_Push(0x234, -1, 0, 1);
                break;
            }
        }
    }
    next = g_raceEntryArray[g_goalFanfarePlayerIndex].player + 1;
    if (g_gameMode == 0) {
        if (next > 4) next = -1;
    } else if (next > 6) next = -1;
    distance = 0;
    if (g_raceEntryArray[g_goalFanfarePlayerIndex].player != 0)
        distance = g_raceEntryArray[g_goalFanfarePlayerIndex].distance;
    if (next != -1) distance += g_raceEntryArray[next].distance;
    if (distance <= 0) {
        if ((float)OSTicksToMilliseconds(now - lbl_806D17E8) / lbl_806D9804 >= lbl_806D9818 &&
            !pushed && g_currentVoiceStreamHandle == -1) {
            if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x235, -1, 0, 1);
            else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x236, -1, 0, 1);
            else VoiceQueue_Push(0x237, -1, 0, 1);
        }
        lbl_806D17E8 = now;
    } else {
        lbl_806D17E8 = now;
    }
}

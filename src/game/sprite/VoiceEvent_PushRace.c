#include "game/VoiceEventPushRacePrivate.h"

#define PUSH(id) SpriteVoice_Push((id), -1, 0, 1)
#define SELECT(entry) RaceEvent_Select((entry)->character, (entry)->id, tables)

/* Announce the active player's race events while keeping short queues and
 * spacing repeated contact and general race commentary. */
unsigned char VoiceEvent_PushRace(void) {
    short *tables = lbl_80496C38;
    OSTime now;
    int i;
    if (g_currentRaceEventPlayer == -1) return 0;
    now = OSGetTime();
    if ((float)OSTicksToMilliseconds(now - RaceEvent_Time(lbl_806D17CC, lbl_806D17C8)) / 1000.0f >= 10.0f) {
        g_currentRaceEventPlayer = -1;
        return 0;
    }

    if (g_raceEntryArray[g_currentRaceEventPlayer].state == 2) {
        if (RaceEvent_QueueTime(tables) < 3.0f) {
            PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
            PUSH(0x24B);
        }
        lbl_806D17D4 = (unsigned int)now;
        lbl_806D17D0 = (unsigned long long)now >> 32;
        return 1;
    }
    if (g_raceEntryArray[g_currentRaceEventPlayer].state == 3) {
        if (RaceEvent_QueueTime(tables) < 3.0f) {
            PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
            PUSH(0x24C);
        }
        lbl_806D17D4 = (unsigned int)now;
        lbl_806D17D0 = (unsigned long long)now >> 32;
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (*(int *)((char *)&g_raceEntryArray[i] + 0x28) == g_currentRaceEventPlayer) {
            if (RaceEvent_QueueTime(tables) < 3.0f) {
                if ((float)OSTicksToMilliseconds(now - RaceEvent_Time(lbl_806D17DC, lbl_806D17D8)) / 1000.0f >= lbl_806D9828) {
                    PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
                    PUSH(0x24D);
                    lbl_806D17DC = (unsigned int)now;
                    lbl_806D17D8 = (unsigned long long)now >> 32;
                }
            }
            lbl_806D17D4 = (unsigned int)now;
            lbl_806D17D0 = (unsigned long long)now >> 32;
            return 1;
        }
    }
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].state == 5 &&
            *(unsigned int *)((char *)&g_raceEntryArray[i] + 0x10) ==
            *(unsigned int *)((char *)&g_raceEntryArray[g_currentRaceEventPlayer] + 0x44)) {
            if (RaceEvent_QueueTime(tables) < 3.0f) {
                PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
                PUSH(0x24E);
            }
            lbl_806D17D4 = (unsigned int)now;
            lbl_806D17D0 = (unsigned long long)now >> 32;
            return 1;
        }
    }
    if (g_raceEntryArray[g_currentRaceEventPlayer].present && g_raceEntryArray[g_currentRaceEventPlayer].kind != 0x99) {
        if (RaceEvent_QueueTime(tables) < 3.0f) {
            PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
            PUSH(0x24F);
        }
        lbl_806D17D4 = (unsigned int)now;
        lbl_806D17D0 = (unsigned long long)now >> 32;
        return 1;
    }
    if (g_raceEntryArray[g_currentRaceEventPlayer].f60 && !RaceEvent_Queued(0x250)) {
        if (RaceEvent_QueueTime(tables) < 3.0f) {
            PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
            PUSH(0x250);
        }
        lbl_806D17D4 = (unsigned int)now;
        lbl_806D17D0 = (unsigned long long)now >> 32;
        return 1;
    }
    if ((float)OSTicksToMilliseconds(now - RaceEvent_Time(lbl_806D17D4, lbl_806D17D0)) / 1000.0f >= lbl_806D982C) {
        if (!RaceEvent_Queued(0x251) && !RaceEvent_Queued(0x252) && !RaceEvent_Queued(0x253)) {
            if (RaceEvent_QueueTime(tables) < 3.0f) {
                PUSH(SELECT(&g_raceEntryArray[g_currentRaceEventPlayer]));
                if (g_voiceTickCounter % 3 == 0) PUSH(0x251);
                else if (g_voiceTickCounter % 3 == 1) PUSH(0x252);
                else PUSH(0x253);
            }
        }
        lbl_806D17D4 = (unsigned int)now;
        lbl_806D17D0 = (unsigned long long)now >> 32;
    }
    return 1;
}

#include "game/RaceAnnouncerTickPrivate.h"

static inline short TickCharacter(RaceVoiceData *data, int character, int id) {
    short voice = 0x43;
    short *normal = data->normal;
    short *special = data->special;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

#define ME g_raceEntryArray[g_taMinLapPlayerIndex]
#define PUSH(id) TickPush(id)
#define CHARACTER(e) TickCharacter(data, (e)->character, (e)->id)
#define SOLO_CHARACTER() TickCharacter(data, ME.character, -1)

unsigned char RaceAnnouncer_TickAndEnqueue(void) {
    RaceVoiceEntry *byRank[8];
    int second;
    int third;
    int i;
    int gap;
    int mode;
    RaceVoiceEntry *other;
    float remaining;
    RaceVoiceData *data = &lbl_80496C38;

    if (lbl_806D1770) return 1;
    if (g_currentVoiceSubId != -1) return 0;
    if (!IsRaceStarted()) return 0;
    if (g_lastPlayerIndexCrossingCheckpoint == -1) return 0;

    mode = g_gameMode;
    if (mode == 0) {
        if (g_lastPlayerCurrentCheckpoint != g_goalTriggerCheckpoint) return 0;
        remaining = TickRemaining(data->clips);
        if (remaining < lbl_806D9818) {
            switch (ME.player) {
            case 0:
                other = RaceVoice_FindByRank(1);
                if (other) {
                    if (other->distance >= 7) {
                        TickPushFirst(0x1BA);
                        PUSH(SOLO_CHARACTER());
                        PUSH(0x1BF);
                    } else if (other->distance <= 0) {
                        TickPushFirst(0x1B8);
                        PUSH(SOLO_CHARACTER());
                        PUSH(0x1C2);
                    } else {
                        TickPushFirst(0x1BA);
                        PUSH(SOLO_CHARACTER());
                        PUSH(0x1C0);
                    }
                } else {
                    TickPushFirst(0x1BA);
                    PUSH(SOLO_CHARACTER());
                    PUSH(0x1C0);
                }
                break;
            case 1:
                TickPushFirst(0x1B8);
                PUSH(SOLO_CHARACTER());
                if (ME.distance <= 0) PUSH(0x1C2);
                else PUSH(0x1C3);
                break;
            default:
                TickPushFirst(0x1BA);
                PUSH(SOLO_CHARACTER());
                PUSH(0x1C4);
                break;
            }
        }
        lbl_806D1770 = 1;
        return 0;
    }

    if (g_lastPlayerCurrentCheckpoint != g_goalTriggerCheckpoint) return 0;
    for (i = 0; i < 8; i++) byRank[i] = RaceVoice_FindByRank(i);

    if (byRank[0]->active && byRank[1]->active && byRank[2]->active &&
        byRank[1]->distance + byRank[2]->distance <= 0) {
        PUSH(0x1BA);
        PUSH(0x1BB);
        lbl_806D1770 = 1;
        return 0;
    }
    if (byRank[0]->active && byRank[1]->active && byRank[1]->distance <= 0) {
        PUSH(0x1B8);
        PUSH(CHARACTER(byRank[0]));
        PUSH(CHARACTER(byRank[1]));
        PUSH(0x1B9);
        lbl_806D1770 = 1;
        return 0;
    }
    if (byRank[0]->active && byRank[1]->active && byRank[2]->active && byRank[3]->active &&
        (byRank[3]->distance + byRank[2]->distance) + byRank[1]->distance < 2) {
        PUSH(0x1BC);
        PUSH(0x1BD);
        lbl_806D1770 = 1;
        return 0;
    }

    gap = -1;
    if (byRank[1]->active && byRank[2]->active) {
        gap = byRank[2]->distance;
        second = 1;
        third = 2;
    } else if (byRank[2]->active && byRank[3]->active) {
        gap = byRank[3]->distance;
        second = 2;
        third = 3;
    } else if (byRank[1]->active && byRank[3]->active) {
        gap = byRank[2]->distance + byRank[3]->distance;
        second = 1;
        third = 3;
    }
    if (gap != -1 && gap <= 0) {
        PUSH(0x1B8);
        PUSH(CHARACTER(byRank[second]));
        PUSH(CHARACTER(byRank[third]));
        PUSH(0x1BE);
        lbl_806D1770 = 1;
        return 0;
    }
    if ((byRank[0]->active || byRank[1]->active) && byRank[1]->distance > 0 && byRank[1]->distance <= 3) {
        PUSH(0x1B8);
        PUSH(0x1B5);
        PUSH(CHARACTER(byRank[0]));
        PUSH(0x1B7);
        PUSH(CHARACTER(byRank[1]));
        lbl_806D1770 = 1;
        return 0;
    }
    if (byRank[0]->active && byRank[1]->distance >= 7) {
        PUSH(0x1BA);
        PUSH(CHARACTER(byRank[0]));
        PUSH(0x1BF);
        lbl_806D1770 = 1;
        return 0;
    }
    if (byRank[0]->active) {
        PUSH(0x1BA);
        PUSH(CHARACTER(byRank[0]));
        PUSH(0x1C0);
        lbl_806D1770 = 1;
        return 0;
    }
    PUSH(0x1BA);
    PUSH(0x1C1);
    lbl_806D1770 = 1;
    return 0;
}
